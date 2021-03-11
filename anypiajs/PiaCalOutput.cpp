#include "PiaCalOutput.h"

#include <sstream>

#include "NumPunct.h"
#include "oactcnst.h"

#include "piaout/PiaPageOut.h"

// #include "piaout/Summary1Page.h"
// #include "piaout/Summary2Page.h"
// #include "piaout/Summary3Page.h"
// #include "piaout/PiaTable1Page.h"
// #include "piaout/PiaTable2Page.h"
// #include "piaout/WageInd1Page.h"
#include "DateFormatter.h"
#include "bendpia.h"
#include "WageInd.h"
#include "ProjectConfigs.rc"

#include <vector>
#include <iostream>

using namespace json;


std::string PiaCalOutput::GetPIAMethodType(const PiaMethod* pMethod)
{
    std::string strType;

    switch(pMethod->getMethod()){
    case PiaMethod::OLD_START:
        strType = "OLD_START";
        break;
    case PiaMethod::PIA_TABLE:
        strType = "PIA_TABLE";
        break;
    case PiaMethod::WAGE_IND:
        strType = "WAGE_IND";
        break;
    case PiaMethod::TRANS_GUAR:
        strType = "TRANS_GUAR";
        break;
    case PiaMethod::SPEC_MIN:
        strType = "SPEC_MIN";
        break;
    case PiaMethod::REIND_WID:
        strType = "REIND_WID";
        break;
    case PiaMethod::FROZ_MIN:
        strType = "FROZ_MIN";
        break;
    case PiaMethod::CHILD_CARE:
        strType = "CHILD_CARE";
        break;
    case PiaMethod::DIB_GUAR:
        strType = "DIB_GUAR";
        break;
    case PiaMethod::WAGE_IND_NON_FREEZE:
        strType = "WAGE_IND_NON_FREEZE";
        break;
    case PiaMethod::NO_PIA_TYPE:
        strType = "NO_PIA_TYPE";
        break;
    default:
        strType = "Invalid";
    }

    return strType;

	return pMethod->getTitle();
}

PiaCalOutput::PiaCalOutput(const PiaCalAny& piaCal) :
    m_piaCal(piaCal),
    m_workerData(piaCal.workerData),
    m_piaData(piaCal.piaData),
    m_piaParams(piaCal.piaParams),
    m_pWageIndNonFreeze(piaCal.wageIndNonFreeze),
	m_pMethod(piaCal.highPiaMethod)
{
	
}

std::string PiaCalOutput::ToJson(const PiaCalAny &piaCal)
{
    PiaCalOutput output(piaCal);

    json::JSON results;
    results["Earnings"] = output.GetEarnings();
    results["Calculation"] = output.GetBenefit();
    results["App"] = output.GetAppInfo();
    //output.AddBenfit(results);
    //results["PIAValue"] = output.GetPIAValue();

    std::stringstream ss;
    ss << results;
    return ss.str();
}

void PiaCalOutput::PrintPageDetails(const PiaCalAny &piaCal)
{
    std::vector<PiaPageOut *> pages;

    // pages.push_back(new Summary1Page(piaCal));
    //pages.push_back(new Summary2Page(*piacal));
    // pages.push_back(new Summary3Page(piaCal));
    // pages.push_back(new PiaTable1Page(piaCal));
    // pages.push_back(new PiaTable2Page(piaCal));
    // pages.push_back(new WageInd1Page(piaCal));

    for (size_t i = 0; i < pages.size(); ++i)
    {
        PiaPageOut *page = pages[i];
        page->setPageNum(i);
        page->prepareHeader();
        page->tableHead2();
        page->prepareStrings();
        page->print(std::cout);
        std::cout << std::endl;
    }
}

std::string PiaCalOutput::GetWindwfallType(const PiaCalAny& piaCal) 
{
    std::string strResult;

    switch (piaCal.highPiaMethod->getWindfall())
    {
    case PiaMethod::WindfallElimType::NOWINDFALLELIM:
        strResult = "N/A";
        break;
    case PiaMethod::WindfallElimType::HAS30YEARS:
        strResult = "30Years";
        break;
    case PiaMethod::WindfallElimType::ONEHALFPENSION:
        strResult = "HalfPension";
        break;
    case PiaMethod::WindfallElimType::REDUCEDPERC:
        strResult = "ReducedPerc";
        break;
    default:
        strResult = "Invalid";
    }

    return strResult;
}

JSON PiaCalOutput::GetAppInfo()
{
    JSON result;

    result["Name"] = PROJECT_NAME;
    result["Description"] = PROJECT_DESC;
    result["Version"] = PROJECT_VER;

    return result;
}


JSON PiaCalOutput::GetEarnings()
{
    JSON result;

    const int i3 = m_workerData.getTotalize() ? m_piaData.getIbeginTotal() : m_piaData.getIbeginAll();
    const int i4 = m_workerData.getTotalize() ? m_piaData.getIendTotal() : m_piaData.getIendAll();

    for (int i1 = i3; i1 <= i4; ++i1)
    {

        std::string strYear;
        double dAnnual = 0;
        double dMax = 0.0;
        double dAmountQc = 0.0;
        int iCoverage = 0;

        strYear = PunctFacet::getYear(i1);

        if (m_piaData.getIbeginAll() != YEAR50 || i1 != YEAR50 ||
            m_workerData.getTotalize())
        {
            dAnnual = m_piaData.earnOasdiLimited[i1];
        }
        else
        {
            dAnnual = m_piaData.getEarnTotal50(PiaData::EARN_NO_TOTALIZATION);
        }

        dMax = m_piaParams.getBaseOasdi(i1);

        if (i1 > m_workerData.getQcLumpYear() || m_workerData.hasQcsByYear())
        {
            if (i1 > m_workerData.getQcLumpYear() && i1 > YEAR50)
            {
                dAmountQc = m_piaParams.qcamt[i1];
            }

            if (i1 > YEAR50)
            {
                iCoverage = m_piaData.qcov.get(i1);
            }
            else
            {
                if (i1 < YEAR50)
                {
                }
                else
                {
                    iCoverage = m_piaData.getQcTotal50();
                }
            }
        }

        JSON earning;

        earning["Annual"] = dAnnual;
        earning["Max"] = dMax;
        earning["AmountQC"] = dAmountQc;
        earning["QtrsCoverage"] = iCoverage;

        result[strYear] = earning;
    }

    return result;
}

json::JSON PiaCalOutput::GetComputationYears() 
{
    JSON results;

    results["BaseYear"] = m_piaData.getEligYearNonFreeze() - 2;
    results["DiDropoutYears"] = m_piaData.compPeriodNewNonFreeze.getDiYears();
    results["DropoutYears"] = m_piaData.compPeriodNewNonFreeze.getNDrop();
    results["ElapsedYears"] = m_piaData.compPeriodNewNonFreeze.getNElapsed();
    results["Total"] = m_piaData.compPeriodNewNonFreeze.getN();

    return results;
}

json::JSON PiaCalOutput::GetAIME() 
{
    JSON results;

    double dTheoretical;
    double dAME;
    double dSumHighNYears;
    int iElapsedYears;
    int iNumComputationYears;
    int iNumDropoutYears;

    // Theoretical
    dTheoretical = m_piaCal.highPiaMethod->getAmeTotal();
    // AME
    dAME = m_piaCal.highPiaMethod->getAme();
    // HighNYearsTotal
    dSumHighNYears = m_piaCal.highPiaMethod->getftearn();

        //Elapsed
    iElapsedYears = m_piaData.compPeriodNewNonFreeze.getNElapsed();
    //Drop
    iNumDropoutYears = m_piaData.compPeriodNewNonFreeze.getNDrop();
    //N
    iNumComputationYears = m_piaData.compPeriodNewNonFreeze.getN();

    results["Theoretical"] = dTheoretical;
    results["AME"] = dAME;
    results["SumHighNYears"] = dSumHighNYears;
    results["ElapsedYears"] = iElapsedYears;
    results["NumDropoutYears"] = iNumDropoutYears;
    results["NumComputationYears"] = iNumComputationYears;

    return results;
}

json::JSON PiaCalOutput::GetBenefit()
{
    JSON results;

    double dInsuranceAmnt;
    double dMaxFamBen;
    double dBenAmnt;

    results["Type"] = GetPIAMethodType(m_pMethod); // change this to one string
                                                    // BaseIndexYear

    results["ComputationYears"] = GetComputationYears();

    results["InsuranceAmount"] = m_piaData.highPia.get();
    results["MaxFamilyBenefit"] = m_piaData.highMfb.get();
    results["Benefit"] = m_piaData.roundedBenefit.get();

    results["AIME"] = GetAIME();

    if (const WageInd* pWageInd = dynamic_cast<const WageInd*>(m_pMethod)) {
        AddWageBenefit(results, pWageInd, m_workerData);
    }

    return results;
}

void PiaCalOutput::AddWageBenefit(json::JSON& parent, const WageInd * pWageInd, const WorkerDataGeneral& workerData)
{
    const int iCpiYear = pWageInd->getCpiYear(PiaMethod::FIRST_YEAR);

    JSON piaBendPoints = JSON::Make(JSON::Class::Array);

    piaBendPoints.append(pWageInd->bendPia[1]);
    piaBendPoints.append(pWageInd->bendPia[2]);

    JSON mfbBendPoints = JSON::Make(JSON::Class::Array);
    mfbBendPoints.append(pWageInd->bendMfb[1]);
    mfbBendPoints.append(pWageInd->bendMfb[2]);
    mfbBendPoints.append(pWageInd->bendMfb[3]);

    JSON piaEligibility = JSON::Make(JSON::Class::Array);

    for (int i = 0; i < 3; ++i)
    {
        JSON entry;

        entry["Percent"] = pWageInd->percPia[i];
        entry["Amount"] = pWageInd->portionAime[i];

        //piaEligibility.append(entry);
        piaEligibility[std::to_string(i)] = entry;
    }

    double dTotal;
    if ((pWageInd->getWindfall() == PiaMethod::HAS30YEARS ||
      pWageInd->getWindfall() == PiaMethod::NOWINDFALLELIM) &&
      !workerData.getTotalize())
    {
        dTotal = pWageInd->piaElig[iCpiYear];
    }
    else {
        if (pWageInd->getWindfall() == PiaMethod::REDUCEDPERC ||
          pWageInd->getWindfall() == PiaMethod::ONEHALFPENSION)
        {
            dTotal = pWageInd->getPiaWindfall().get();
        }
        else
        {
            dTotal = pWageInd->getPiaEligTotal().get();
        }
    }
    piaEligibility["Total"] = dTotal;


    JSON piaAfterWindfall;

    if (pWageInd->getWindfall() == PiaMethod::REDUCEDPERC)
    {
        for (int i = 0; i < 3; ++i)
        {
            JSON entry;
            entry["Percent"] = pWageInd->percWind[i];
            entry["Amount"] = pWageInd->portionAime[i];

            piaAfterWindfall[std::to_string(i)] = entry;
        }
    }
    else
    {
        JSON entry;
        entry["PIAWindfall"] = pWageInd->getPiaWindfall().get();
        entry["PublicPension"] = workerData.getPubpen() * 0.5;
    }



    piaAfterWindfall["Total"] = pWageInd->piaElig[iCpiYear];

    JSON noncoveredPension;

    float fMonthlyPension;
    if (workerData.getReservist() &&
        workerData.getBenefitDate().getYear() > 1994) {
        fMonthlyPension = workerData.getPubpenReservist();
    }
    else {
        fMonthlyPension = workerData.getPubpen();
    }

    noncoveredPension["MonthlyPension"] = fMonthlyPension;
    // noncoveredPension["EntitlementDate"] = DateFormatter::toString(workerData.getPubpenDate(),"s");

    parent["YearsOfCoverageForWindfall"] = pWageInd->getYearsTotal();
    parent["PIABendPoints"] = piaBendPoints;
    parent["MFBBendPoints"] = mfbBendPoints;
    parent["PIAEligibility"] = piaEligibility;
    parent["PIAAfterWindwfall"] = piaAfterWindfall;
    parent["NoncoveredPosion"] = noncoveredPension;
}
