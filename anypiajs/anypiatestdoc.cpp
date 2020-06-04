// $Id: anypiatestdoc.cpp 1.16 2012/03/13 08:40:42EDT 277133 Development  $
//
// This program reads a series of cases in standard anypia format, computes
// a primary insurance amount and associated data for each one, and prints
// the results to a file named "output".  The particular variables that are
// printed can be specified in function savecase, at the end of this file.

#if defined(_WIN32)
#pragma warning(disable:4786)
#endif
#include <fstream>
#include <iomanip>
#include "anypiatestdoc.h"
#include "genfile.h"
#include "PiadataArray.h"
#include "UserAssumptions.h"
#include "SecondaryArray.h"
#include "EarnProject.h"
#include "piaparmsAny.h"
#include "wrkrdata.h"
#include "WorkerDataArray.h"
#include "DateFormatter.h"
#ifdef DETAILS
#include "outfile.h"
#include "OutFile80.h"
#include "TaxData.h"
#endif

using namespace std;

#ifdef MSDOS
extern int   getopt   ( int, char **, char * );
#endif

extern char *optarg;  // option argument

#ifdef LAWCHG
#define ANYPIA "anypialc"
#else
#define ANYPIA "anypia"
#endif

// Description: Constructor.
AnypiaTestDoc::AnypiaTestDoc()
{
   WorkerData::setQcLumpYear(1977);
   WorkerDataGeneral::setMaxyear(YEAR2090);
   baseyear = new BaseYearNonFile();
   workerData = new WorkerData;
   piaData = new PiaData;
   widowDataArray = new WorkerDataArray;
   widowPiaDataArray = new PiaDataArray;
   userAssumptions = new UserAssumptions(YEAR2090);
   secondaryArray = new SecondaryArray();
   earnProject = new EarnProject(YEAR2090);
   pebs = new Pebs;
   piaread = new PiaReadAny(*workerData, *widowDataArray, *widowPiaDataArray,
      *userAssumptions, *secondaryArray, *earnProject, *pebs);
   //piaread->setEarnWidth(11);
   awbidat = new AwbiDataNonFile(baseyear->getYear(),
      WorkerData::getMaxyear());
   assumptions = new AssumptionsNonFile(baseyear->getYear(),
      WorkerData::getMaxyear());
   lawChange = new LawChangeArray(baseyear->getYear(),
      WorkerData::getMaxyear(), "");
   piaparms = new PiaParamsAny(baseyear->getYear(), WorkerData::getMaxyear(),
      *awbidat, *lawChange );
   piaparms->setHistFqinc();
   piacal = new PiaCalAny(*workerData, *piaData, *widowDataArray,
      *widowPiaDataArray, *piaparms, *userAssumptions, *secondaryArray,
      *lawChange, *pebs, *earnProject);
#ifdef DETAILS
   taxData = new TaxData(WorkerData::getMaxyear());
   piaOut = new PiaOut(*piacal, *taxData);
#endif
}

// Description: Destructor.
AnypiaTestDoc::~AnypiaTestDoc()
{
#ifdef DETAILS
   delete taxData;
   delete piaOut;
#endif
   delete piacal;
   delete piaparms;
   delete lawChange;
   delete assumptions;
   delete awbidat;
   delete pebs;
   delete piaread;
   delete earnProject;
   delete secondaryArray;
   delete userAssumptions;
   delete widowDataArray;
   delete widowPiaDataArray;
   delete piaData;
   delete workerData;
   delete baseyear;
}

// Description: Calculates benefits.
//
// Returns: Error code.
//      0 : No error.
//      1 : Error that stops file processing.
//      2 : Error that only affects some cases.  
std::string AnypiaTestDoc::calculate()
{
   int ierr = 0;  // error indicator
   int rval = 0;
   // Genfile outfile("output");  // output file name
   ofstream out;  // output stream
   stringstream ss;

#ifdef DETAILS
   OutFile80 outfl("details");
   outfl.openout();
#endif

   // try {
   //    outfile.openout(out);
   // } catch (PiaException e) {
   //    cerr << e.what() << endl;
   //    return(1);
   // }
   userAssumptions->setIstart(piaparms->getIstart());

   try {
      workerData->deleteContents();
      piaData->deleteContents();
      earnProject->deleteContents();
      widowDataArray->deleteContents();
      widowPiaDataArray->deleteContents();
      secondaryArray->deleteContents();
      workerData->ssn.setSsnFull("123450001");
      workerData->setSex(Sex::MALE);
      workerData->setBirthDate(boost::gregorian::date(1940,1,15));
      workerData->setJoasdi(WorkerDataGeneral::OLD_AGE);
      workerData->setEntDate(DateMoyr(7,2005));
      workerData->setBenefitDate();
      workerData->setIbegin(1962);
      workerData->setIend(2004);
      earnProject->setFirstYear(1962);
      earnProject->setLastYear(2004);
      earnProject->setProjback(1);
      earnProject->setPercback(0.00f);
     earnProject->setFirstYear(2004);
      workerData->setNhname("Sample 1");
      earnProject->setEarntype(2004, 1);
      userAssumptions->setIaltbi(2);
      userAssumptions->setIaltaw(2);
      userAssumptions->setIbasch(1);
      workerData->setQctd(64);
      workerData->setQc51td(64);
      DateMoyr entDate = (workerData->getJoasdi() == WorkerDataGeneral::SURVIVOR) ? 
         secondaryArray->secondary[0]->entDate : 
         workerData->getEntDate();
      piacal->dataCheck(entDate);
      piacal->dataCheckAux(*widowDataArray, *widowPiaDataArray,
         *secondaryArray);
      piacal->calculate1(*assumptions);
      // find the date of entitlement to use to calculate the pia
      // compute regular pias and primary benefit
      piacal->calculate2(entDate);
      piacal->reindWidCalAll(*widowDataArray, *widowPiaDataArray,
         *secondaryArray);
      piacal->piaCal3(*widowPiaDataArray, *secondaryArray);
      savecase(ss);
      //nonins(out);
      //if (workerData->getJoasdi() == WorkerData::DISABILITY)
      //   disinsout(out);
#ifdef DETAILS
      // print detailed results for each non-statement case
      if (workerData->getJoasdi() != WorkerData::PEBS_CALC) {
         piaOut->onePage.prepareStrings();
         piaOut->onePage.print(outfl);
      }
#endif
   // no problem with calculation
   } catch (PiaException e) {
      cout << e.what() << " in calculation" << endl;
      rval = 2;
      string strCal = "Invliad";
      // continue with next case
   }
#ifdef DETAILS
   outfl.closeout();
#endif

   return ss.str();
}

// Description: Writes out 1 line of results, if a primary beneficiary or a
//   Social Security Statement.  If there are family members, there is an
//   additional line for each family member.
//
// Arguments:
//   out: Output stream.
void AnypiaTestDoc::savecase( std::stringstream& out )
{
   char insCode = piaData->getFinsCode2();
   char insStat = 'T';
   if (insCode == '4' || insCode == '5' || insCode == '6' || insCode == '7') {
      insStat = 'F';
   }
   if ((workerData->getJoasdi() == WorkerData::DISABILITY) &&
      !piaData->disInsCode.isDisabilityInsured()) {
      insStat = 'F';
   }
   if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
      out << workerData->ssn.toString();
	   out << setprecision(0) << setfill(' ');
      out << setw(6) << pebs->getBenefitPebs(Pebs::PEBS_OAB_EARLY);
      out << setw(6) << pebs->getBenefitPebs(Pebs::PEBS_OAB_FULL);
      out << setw(6) << pebs->getBenefitPebs(Pebs::PEBS_OAB_DELAYED);
      out << setw(6) << pebs->getBenefitPebs(Pebs::PEBS_SURV);
      out << setw(6) << pebs->getPiaPebs(Pebs::PEBS_SURV);
      out << setw(6) << pebs->getMfbPebs(Pebs::PEBS_SURV);
      out << setw(6) << pebs->getPiaPebs(Pebs::PEBS_DISAB);
      out << setw(6) << pebs->getMfbPebs(Pebs::PEBS_DISAB);
      out << endl;
   }
   else {
      if (workerData->getJoasdi() != WorkerData::SURVIVOR) {
         out << workerData->ssn.toString();
         out << " " << DateFormatter::toString(workerData->getBirthDate(),"s");
		 out << setprecision(2) << setfill(' ');
         out << setw(8) << piaData->highPia.get();
         out << setw(8) << piaData->highMfb.get();
         out << setw(8) << piaData->roundedBenefit.get();
         out << " " ;
         out << piaData->ageBen.toString("f");
         out << " " << piaData->getPifc();
         // bic A for primary
         //out << " " << "A ";
         out << " " << insStat << endl;
      }
      for (int i = 0; i < piacal->widowArray.getFamSize(); i++) {
         out << workerData->ssn.toString();
         out << " "
            << DateFormatter::toString(widowDataArray->workerData[i]->getBirthDate(),"s");
		 out << setprecision(2) << setfill(' ');
         out << setw(8) << piaData->highPia.get();
         out << setw(8) << piaData->highMfb.get();
         Secondary *secondary = piacal->secondaryArray.secondary[i];
         out << setw(8) << secondary->getFullBenefit();
         out << setw(8) << secondary->getRoundedBenefit();
         out << " " << secondary->pifc.get();
         // bic from secondary record
         out << " " << secondary->bic.toString();
         out << " " << insStat << endl;
      }
   }
   if (piacal->oldStart != (OldStart*)0) {
      const OldStart* oldStart = piacal->oldStart;
      if (oldStart->getMethodOs() < 4 && workerData->getIbegin() >= 1950) {
         out << "Need annual pre-1951 earnings in prior case" << endl;
      }
   }
}

// Description: Writes out uninsured message.
//
// Arguments:
//   out: Output stream.
void AnypiaTestDoc::nonins( std::ofstream& out )
{
   switch (piaData->getFinsCode2())
   {
      case '2':
         out << "Preceding case only currently insured based on input data"
            << endl;
         break;
      case '4':
         out << "Preceding case not fully insured based on input data" << endl;
         break;
      case '5':
         out << "Preceding case not fully or totalization insured" << endl;
         break;
      case '6':
         out << "Preceding case not insured for totalization benefits" << endl;
         break;
      case '7':
         out << "Preceding case insured for regular benefits" << endl;
         break;
      default:
         break;
   }
}

// Description: Writes out disability uninsured message.
//
// Arguments:
//   out: Output stream.
void AnypiaTestDoc::disinsout( std::ofstream& out )
{
   if (!piaData->disInsCode.isDisabilityInsured()) {
      out << "Preceding case not disability insured" << endl;
   }
}
