// $Id: anypiabdoc.h 1.4 2005/12/01 11:15:05EST 277133 Exp  $
//
// Structures used by anypiab.

#include <iostream>
#include "pia.h"
#include "piaout/piaout.h"
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

class AnypiabDoc
{
   public:
      // base year.
      BaseYearNonFile *baseyear;
      AwbiDataNonFile *awbidat;  // historical benefit increases and average wages
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
      AnypiabDoc();
      ~AnypiabDoc();
      int  calculate();
      void  savecase ( std::ofstream& out );
      void  nonins ( std::ofstream& out );
      void  disinsout ( std::ofstream& out );
};
