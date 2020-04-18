// $Id: anypiabdoc.cpp 1.25 2012/03/13 08:40:42EDT 277133 Development  $
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
#include "anypiabdoc.h"
#include "genfile.h"
#include "PiadataArray.h"
#include "UserAssumptions.h"
#include "SecondaryArray.h"
#include "EarnProject.h"
#include "piaparmsAny.h"
#include "wrkrdata.h"
#include "WorkerDataArray.h"
#include "PiaTable.h"
#include "Path.h"
#include "DateFormatter.h"
#ifdef DETAILS
#include "outfile.h"
#include "OutFile80.h"
#include "TaxData.h"
#endif
// uncomment the following line to use one file with multiple cases (anypiab);
// otherwise the program expects multiple files, each with one case (anypiac)
// #define ONEBIGFILE

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
AnypiabDoc::AnypiabDoc()
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
AnypiabDoc::~AnypiabDoc()
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
int AnypiabDoc::calculate()
{
   ifstream in;  // stream with case to read
   char ernfil[80];  // name of file with stored case
   int ierr = 0;  // error indicator
   int rval = 0;
   Genfile outfile("output");  // output file name
   ofstream out;  // output stream
   string infile;  // input file name

#ifdef DETAILS
   OutFile80 outfl("details");
   outfl.openout();
#endif

   //infile.setTitle("benefit calculation data");
   try {
      outfile.openout(out);
   } catch (PiaException e) {
      cerr << e.what() << endl;
      return(1);
   }
   userAssumptions->setIstart(piaparms->getIstart());

#if defined(ONEBIGFILE)
   // read one file with multiple cases
   cin >> ernfil;
   infile = Path::changeExtension(ernfil, "pia");
   in.clear();
   in.open(infile.c_str());
   if (in.fail()) {
      cerr << "Unable to open input file "
         << infile << endl;
      return(1);
   }
   while (!in.fail() && ierr == 0) {
#else
   // read multiple files, each with one case
   while (cin >> ernfil) {
      infile = Path::changeExtension(ernfil, "pia");
      in.clear();
      in.open(infile.c_str());
      if (in.fail()) {
         cerr << "Unable to open input file "
            << infile << endl;
         return(1);
      }
#endif
      try {
         cout << "Reading benefit calculation data from "
            << infile << endl;
         workerData->deleteContents();
         piaData->deleteContents();
         earnProject->deleteContents();
         widowDataArray->deleteContents();
         widowPiaDataArray->deleteContents();
         secondaryArray->deleteContents();
         ierr = piaread->read(in);
#ifndef ONEBIGFILE
         in.close();
#endif
         if (ierr == 0 || ierr == PIA_IDS_READEOF || 
             ierr == PIA_IDS_READMORE) {
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
           savecase(out);
           //nonins(out);
           //if (workerData->getJoasdi() == WorkerData::DISABILITY)
           //   disinsout(out);
#ifdef DETAILS
           // print detailed results for each non-statement case
           if (workerData->getJoasdi() != WorkerData::PEBS_CALC) {
              piaOut->onePage.setPageNum(1);
              piaOut->onePage.prepareStrings();
              piaOut->onePage.print(outfl);
           }
#endif
         } else {
           PiaException e(ierr);
           cerr << workerData->getIdString() << ": ";
           cerr << e.what() << " in file read" << endl;
		   rval = 2;
         }
      // no problem with calculation
      } catch (PiaException e) {
         cerr << workerData->getIdString() << ": ";
         cerr << e.what() << " in calculation" << endl;
		   rval = 2;
         // continue with next case
      }
   }
#ifdef ONEBIGFILE
   in.close();
#endif
   out.close();
#ifdef DETAILS
   outfl.closeout();
#endif
   return(rval);
}

// Description: Writes out 1 line of results, if a primary beneficiary or a
//   Social Security Statement.  If there are family members, there is an
//   additional line for each family member.
//
// Arguments:
//   out: Output stream.
void AnypiabDoc::savecase( std::ofstream& out )
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
         // Uncomment the following for an output of AME for requests.
         //if (piacal->wageInd != static_cast<WageInd*>(0)) {
         //   out << setw(8) << piacal->wageInd->getAme();
         //} else {
         //   out << setw(8) << 0.0;
         //}
         //if (piacal->piaTable != static_cast<PiaTable*>(0)) {
         //   out << setw(8) << piacal->piaTable->getAme();
         //} else {
         //   out << setw(8) << 0.0;
         //}
         //if (piacal->oldStart != static_cast<OldStart*>(0)) {
         //   out << setw(8) << piacal->oldStart->getAme();
         //} else {
         //   out << setw(8) << 0.0;
         //}
         out << " ";
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
		 out << setprecision(2)  << setfill(' ');
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
void AnypiabDoc::nonins( std::ofstream& out )
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
void AnypiabDoc::disinsout( std::ofstream& out )
{
   if (!piaData->disInsCode.isDisabilityInsured()) {
      out << "Preceding case not disability insured" << endl;
   }
}
