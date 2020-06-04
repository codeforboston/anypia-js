// $Id: anypiatestdoc.h 1.3 2005/12/01 11:15:05EST 277133 Exp  $
//
// Structures used by test version of anypiab.

#include <iostream>
#include "piadata.h"
#include "pebs.h"
#include "piaparms.h"
#include "piacal.h"


#include "piaout/PiaOut.h"
#include "BaseYearNonFile.h"
#include "AwbiDataNonFile.h"
#include "AssumptionsNonFile.h"
#include "LawChangeArray.h"
#include "piareadAny.h"
#include "PiaCalAny.h"
#include "PiaException.h"
class WorkerData;
class PiaData;
class WorkerDataArray;
class PiaDataArray;

class AnypiaTestDoc
{
   public:
      // base year.
      BaseYearNonFile *baseyear;
      // historical benefit increases and average wages
      AwbiDataNonFile *awbidat;
      PiaParamsAny *piaparms;  // piaparms class
      Assumptions *assumptions;  // pia parameter assumptions
      LawChangeArray *lawChange;  // law changes
      UserAssumptions *userAssumptions;  // user-specified assumptions
      SecondaryArray *secondaryArray;  // secondary benefit
      EarnProject *earnProject;  // projected earnings
      PiaReadAny *piaread;
      PiaCalAny *piacal;  // pia calculation functions
      Pebs *pebs;  // PEBES data
      // Basic worker data.
      WorkerData *workerData;
      // Worker's pia data.
      PiaData *piaData;
      // Widow and other family members' basic data.
      WorkerDataArray *widowDataArray;
      // Widow and other family members' pia data.
      PiaDataArray *widowPiaDataArray;
      TaxData *taxData;
      PiaOut *piaOut;
   public:
      AnypiaTestDoc();
      ~AnypiaTestDoc();
      std::string  calculate();
      void  savecase ( std::stringstream& out );
      void  nonins ( std::ofstream& out );
      void  disinsout ( std::ofstream& out );
};
