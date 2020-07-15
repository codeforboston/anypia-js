#include "PiaCalOutput.h"
#include "json.hpp"
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

#include <vector>
#include <iostream>

using namespace json;

namespace PiaCalOutput
{
    json::JSON GetEarnings(const PiaCalAny &piacal)
    {
        json::JSON result;

        const WorkerDataGeneral &workerData = piacal.workerData;
        const PiaData &piaData = piacal.piaData;
        const PiaParams &piaParams = piacal.piaParams;

        const int i3 = workerData.getTotalize() ? piaData.getIbeginTotal() : piaData.getIbeginAll();
        const int i4 = workerData.getTotalize() ? piaData.getIendTotal() : piaData.getIendAll();

        for (int i1 = i3; i1 <= i4; ++i1)
        {

            std::string strYear;
            double dAnnual = 0;
            double dMax = 0.0;
            double dAmountQc = 0.0;
            int iCoverage = 0;

            strYear = PunctFacet::getYear(i1);

            if (piaData.getIbeginAll() != YEAR50 || i1 != YEAR50 ||
                workerData.getTotalize())
            {
                dAnnual = piaData.earnOasdiLimited[i1];
            }
            else
            {
                dAnnual = piaData.getEarnTotal50(PiaData::EARN_NO_TOTALIZATION);
            }

            dMax = piaParams.getBaseOasdi(i1);

            if (i1 > workerData.getQcLumpYear() || workerData.hasQcsByYear())
            {
                if (i1 > workerData.getQcLumpYear() && i1 > YEAR50)
                {
                    dAmountQc = piaParams.qcamt[i1];
                }

                if (i1 > YEAR50)
                {
                    iCoverage = piaData.qcov.get(i1);
                }
                else
                {
                    if (i1 < YEAR50)
                    {
                    }
                    else
                    {
                        iCoverage = piaData.getQcTotal50();
                    }
                }
            }

            json::JSON earning;

            earning["Annual"] = dAnnual;
            earning["Max"] = dMax;
            earning["AmountQC"] = dAmountQc;
            earning["QtrsCoverage"] = iCoverage;

            result[strYear] = earning;
        }

        return result;
    }

    json::JSON GetPIAValue(const PiaCalAny& piaCal)
    {
        const WorkerDataGeneral &workerData = piaCal.workerData;
        const PiaData &piaData = piaCal.piaData;
        const PiaParams &piaParams = piaCal.piaParams;

        std::string strBirthdate;
        double dInsuranceAmnt;
        double dMaxFamBen;
        double dBenAmnt;
        double dAME;

        strBirthdate = DateFormatter::toString(workerData.getBirthDate(), "s");
        dInsuranceAmnt = piaData.highPia.get();

        dMaxFamBen = piaData.highMfb.get();
        dBenAmnt = piaData.roundedBenefit.get();

        dAME = piaCal.highPiaMethod->getAme();

        json::JSON results;
        results["Birthdate"] = strBirthdate;
        results["InsuranceAmount"] = dInsuranceAmnt;
        results["MaxFamilyBenefit"] = dMaxFamBen;
        results["Benefit"] = dBenAmnt;
        results["AME"] = dAME;

        return results;
    }

    std::string ToJson(const PiaCalAny &piaCal)
    {
        json::JSON results;
        results["Earnings"] = GetEarnings(piaCal);
        results["PIAValue"] = GetPIAValue(piaCal);

        std::stringstream ss;
        ss << results;
        return ss.str();
    }

    void PrintPageDetails(const PiaCalAny &piaCal)
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
} // namespace PiaCalOutput