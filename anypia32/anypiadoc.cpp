// Implementation of the <see cref="CAnypia32Doc"/> class.
//
// $Id: anypiadoc.cpp 1.101.1.6 2016/12/07 08:15:22EST 277133 Development  $

#if defined(_WIN32)
#pragma warning(disable:4786)
#endif
#include "stdafx.h"
#include "Anypia32.h"
#include <sstream>
#include <fstream>
#include <utility>  // for rel_ops

#include "AnypiaDoc.h"
#include "WorkerDialog.h"
#include "PebesDialog.h"
#include "NonPebesDialog.h"
#include "DisabDialog.h"
#include "DeathDialog.h"
#include "QctotDialog.h"
#include "AssumptionsDialog.h"
#include "BiprojDialog.h"
#include "AwprojDialog.h"
#include "CuprojDialog.h"
#include "WageBaseDialog.h"
#include "EarningsDialog.h"
#include "BaseyearDialog.h"
#include "FoinfoDialog.h"
#include "HistAmtReviewDialog.h"
#include "HistAmtModifyDialog.h"
#include "HistAmtUpdateDialog.h"
#include "HistAmtClearDialog.h"
#include "ConfigDialog.h"
#include "ScreenDialog.h"
#include "Milserv.h"
#include "pia.h"
#include "PiaException.h"
#include "TaxRatesPL.h"
#include "ConfigNonFile.h"
#include "SecondaryArray.h"
#include "WorkerDataArray.h"
#include "WageBase.h"
#include "DebugCase.h"
#include "DateFormatter.h"
#include "TaxData.h"
#include "UserAssumptions.h"
#include "EarnProject.h"
#include "piaparmsAny.h"
#include "PiaCalAny.h"
#include "AwbiDataNonFile.h"
#include "FieldOfficeInfoNonFile.h"
#include "piareadAny.h"
#include "piawriteAny.h"
#if defined(DEBUGCASE)
#include "Trace.h"
#endif

using namespace std;
#if !defined(__SGI_STL_INTERNAL_RELOPS)
using namespace std::rel_ops;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CAnypia32Doc, CDocument)

BEGIN_MESSAGE_MAP(CAnypia32Doc, CDocument)
	//{{AFX_MSG_MAP(CAnypia32Doc)
	ON_COMMAND(ID_DIALOGS_PEBESINFO, OnDialogsPebesinfo)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_PEBESINFO, OnUpdateDialogsPebesinfo)
	ON_COMMAND(ID_DIALOGS_NONPEBESINFO, OnDialogsNonpebesinfo)
	ON_COMMAND(ID_DIALOGS_WORKERINFO, OnDialogsWorkerinfo)
	ON_COMMAND(ID_DIALOGS_DISABILITYINFO, OnDialogsDisabilityinfo)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_DISABILITYINFO, OnUpdateDialogsDisabilityinfo)
	ON_COMMAND(ID_DIALOGS_SURVIVORINFO, OnDialogsSurvivorinfo)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_SURVIVORINFO, OnUpdateDialogsSurvivorinfo)
	ON_COMMAND(ID_DIALOGS_SUMMARYQCS, OnDialogsSummaryqcs)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_SUMMARYQCS, OnUpdateDialogsSummaryqcs)
	ON_COMMAND(ID_DIALOGS_ASSUMPTIONS, OnDialogsAssumptions)
	ON_COMMAND(ID_DIALOGS_BENEFITINCREASES, OnDialogsBenefitincreases)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_BENEFITINCREASES, OnUpdateDialogsBenefitincreases)
	ON_COMMAND(ID_DIALOGS_AVERAGEWAGEINCREASES, OnDialogsAveragewageincreases)
	ON_COMMAND(ID_DIALOGS_CATCHUPINCREASES, OnDialogsCatchupincreases)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_CATCHUPINCREASES, OnUpdateDialogsCatchupincreases)
	ON_COMMAND(ID_DIALOGS_WAGEBASES, OnDialogsWagebases)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_WAGEBASES, OnUpdateDialogsWagebases)
	ON_COMMAND(ID_DIALOGS_ANNUALEARNINGSINFO, OnDialogsAnnualearningsinfo)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_ASSUMPTIONS, OnUpdateDialogsAssumptions)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_AVERAGEWAGEINCREASES, OnUpdateDialogsAveragewageincreases)
	ON_COMMAND(ID_SETUP_COMPUTATIONYEAR, OnSetupComputationyear)
	ON_COMMAND(ID_SETUP_FIELDOFFICEINFO, OnSetupFieldofficeinfo)
	ON_COMMAND(ID_SETUP_AVERAGEWAGEINCREASES_SET1, OnSetupAveragewageincreasesSet1)
	ON_COMMAND(ID_SETUP_AVERAGEWAGEINCREASES_SET2, OnSetupAveragewageincreasesSet2)
	ON_COMMAND(ID_SETUP_AVERAGEWAGEINCREASES_SET3, OnSetupAveragewageincreasesSet3)
	ON_COMMAND(ID_SETUP_AVERAGEWAGEINCREASES_SET4, OnSetupAveragewageincreasesSet4)
	ON_COMMAND(ID_SETUP_BENEFITINCREASES_SET1, OnSetupBenefitincreasesSet1)
	ON_COMMAND(ID_SETUP_BENEFITINCREASES_SET2, OnSetupBenefitincreasesSet2)
	ON_COMMAND(ID_SETUP_BENEFITINCREASES_SET3, OnSetupBenefitincreasesSet3)
	ON_COMMAND(ID_SETUP_BENEFITINCREASES_SET4, OnSetupBenefitincreasesSet4)
	ON_COMMAND(ID_SETUP_CATCHUPINCREASES_SET1, OnSetupCatchupincreasesSet1)
	ON_COMMAND(ID_SETUP_CATCHUPINCREASES_SET2, OnSetupCatchupincreasesSet2)
	ON_COMMAND(ID_SETUP_CATCHUPINCREASES_SET3, OnSetupCatchupincreasesSet3)
	ON_COMMAND(ID_SETUP_CATCHUPINCREASES_SET4, OnSetupCatchupincreasesSet4)
	ON_COMMAND(ID_SETUP_HISTORICALAMOUNTS_MODIFY, OnSetupHistoricalamountsModify)
	ON_COMMAND(ID_SETUP_HISTORICALAMOUNTS_REVIEW, OnSetupHistoricalamountsReview)
	ON_COMMAND(ID_SETUP_HISTORICALAMOUNTS_UPDATE, OnSetupHistoricalamountsUpdate)
	ON_UPDATE_COMMAND_UI(ID_SETUP_HISTORICALAMOUNTS_MODIFY, OnUpdateSetupHistoricalamountsModify)
	ON_UPDATE_COMMAND_UI(ID_SETUP_CATCHUPINCREASES_SET1, OnUpdateSetupCatchupincreasesSet1)
	ON_UPDATE_COMMAND_UI(ID_SETUP_CATCHUPINCREASES_SET2, OnUpdateSetupCatchupincreasesSet2)
	ON_UPDATE_COMMAND_UI(ID_SETUP_CATCHUPINCREASES_SET3, OnUpdateSetupCatchupincreasesSet3)
	ON_UPDATE_COMMAND_UI(ID_SETUP_CATCHUPINCREASES_SET4, OnUpdateSetupCatchupincreasesSet4)
	ON_COMMAND(ID_DIALOGS_MILITARYSERVICE, OnDialogsMilitaryservice)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_MILITARYSERVICE, OnUpdateDialogsMilitaryservice)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_ANNUALEARNINGSINFO, OnUpdateDialogsAnnualearningsinfo)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_COMMAND(ID_VIEW_SCREEN_SETTINGS, OnViewScreenSettings)
	ON_COMMAND(ID_FILE_RUN, OnFileRun)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_NONPEBESINFO, OnUpdateDialogsNonpebesinfo)
	ON_COMMAND(ID_SETUP_HISTORICALAMOUNTS_CLEAR, OnSetupHistoricalamountsClear)
	ON_UPDATE_COMMAND_UI(ID_SETUP_HISTORICALAMOUNTS_CLEAR, OnUpdateSetupHistoricalamountsClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/// <summary>Constructor.</summary>
CAnypia32Doc::CAnypia32Doc() : hasrr3750(false)
{
   CString stemp;  // temporary string

   try {
   // The Anypia program asks for qcs through 1977 as a lump sum
   WorkerData::setQcLumpYear(1977);
   config = new ConfigNonFile();
   configIni = new ConfigIni();
   configIni->read();
   config->setTopMargin(configIni->getTopMargin());
   config->setLeftMargin(configIni->getLeftMargin());
   config->setLongOutput(configIni->getLongOutput());
   config->setScreenPoints(configIni->getScreenPoints());
   config->setPrinterPoints(configIni->getPrinterPoints());
   baseyear = new BaseYearNonFile();
   baseyearStored = baseyear->getYear();
   WorkerDataGeneral::setMaxyear(YEAR2095);
   workerData = new WorkerData();
   widowDataArray = new WorkerDataArray();
   piadata = new PiaData();
   widowArray = new PiaDataArray();
   secondaryArray = new SecondaryArray();
   userAssumptions = new UserAssumptions(workerData->getMaxyear());
   earnProject = new EarnProject(YEAR2095);
   pebs = new Pebs;
   piaread = new PiaReadAny(*workerData, *widowDataArray, *widowArray,
      *userAssumptions, *secondaryArray, *earnProject, *pebs);
   piawrite = new PiaWriteAny(*workerData, *widowDataArray, *widowArray,
      *userAssumptions, *secondaryArray, *earnProject, *pebs);
   awbidat = new AwbiDataNonFile(baseyear->getYear(),
      workerData->getMaxyear());
   awbidatIni = new AwbiDataIni(baseyear->getYear(), workerData->getMaxyear());
   for (int i = awbidat->getLastYear() + 1; i < workerData->getMaxyear(); i++) {
      awbidatIni->setLastYear(i);
      try {
         awbidatIni->read();
      } catch (PiaException&) {
         awbidatIni->setLastYear(i - 1);
         break;
      }
      awbidat->setLastYear(i);
      awbidat->cpiinc[i - 1] = awbidatIni->cpiinc[i - 1];
      awbidat->fq[i - 2] = awbidatIni->fq[i - 2];
      awbidat->baseOasdi[i] = awbidatIni->baseOasdi[i];
      awbidat->base77[i] = awbidatIni->base77[i];
      awbidat->baseHi[i] = awbidatIni->baseHi[i];
   }
   baseyearIni = new BaseYearIni();
   baseyearIni->read();
   try {
      BaseYear::yearCheck(baseyearIni->getYear());
      if (baseyearIni->getYear() <= awbidat->getLastYear())
         baseyear->setYear(baseyearIni->getYear());
   } catch (PiaException&) {
      // do not reset base year
   }
   userAssumptions->setIstart(baseyear->getYear());
   awincIni = new AwincIni(baseyear->getYear() - 1, workerData->getMaxyear());
   biprojIni = new BiprojIni(baseyear->getYear(), workerData->getMaxyear());
   cachupIni = new CatchupIni(baseyear->getYear());
   assumptions = new AssumptionsNonFile(baseyear->getYear(),
      workerData->getMaxyear());
   lawChange = new LawChangeArray(baseyear->getYear(),
      workerData->getMaxyear(), "");
   piaparms = new PiaParamsAny(baseyear->getYear(), workerData->getMaxyear(),
      *awbidat, *lawChange);
   piaparms->setHistFqinc();
   for (int j = 1; j <= 4; j++) {
      try {
         // throws an exception if there are no stored average wage increases
         awincIni->read(j);
         // does not get here unless there were stored average wage increases
         assumptions->awincProj.setData(j, awincIni->awinc);
         assumptions->awincProj.setTitle(j, awincIni->getTitle());
      } catch (exception&) {
         // done with average wage increases
      }
      try {
         // throws an exception if there are no stored benefit increases
         biprojIni->read(j);
         // does not get here unless there were stored benefit increases
         assumptions->biProj.setData(j, biprojIni->theData);
         assumptions->biProj.setTitle(j, biprojIni->getTitle());
      } catch (exception&) {
         // done with benefit increases
      }
      try {
         // throws an exception if there are no stored catchup benefit increases
         cachupIni->read(j);
         // does not get here unless there were stored catchup benefit increases
         assumptions->catchupDoc.setData(j, cachupIni->catchup);
         assumptions->catchupDoc.allownonzero[j - 1] = true;
      } catch (exception&) {
         // done with catch-up benefit increases
      }
   }
   userAssumptions->setIaltbi(AssumptionType::FLAT);
   userAssumptions->setIaltaw(AssumptionType::FLAT);
   userAssumptions->setIbasch(1);
   taxes = new TaxData(workerData->getMaxyear());
   taxrates = new TaxRatesPL(workerData->getMaxyear());
   piacal = new PiaCalAny(*workerData, *piadata, *widowDataArray, *widowArray,
      *piaparms, *userAssumptions, *secondaryArray, *lawChange, *pebs,
      *earnProject);
   piacal->calculate1(*assumptions);
   foinfo = new FieldOfficeInfoNonFile();
   foinfo->setData();
   foinfoIni = new FieldOfficeInfoIni();
   foinfoIni->read();
   if (!foinfoIni->getFieldOfficeName().empty())
      foinfo->setFieldOfficeName(foinfoIni->getFieldOfficeName());
   if (!foinfoIni->getFieldOfficeTitle().empty())
      foinfo->setFieldOfficeTitle(foinfoIni->getFieldOfficeTitle());
   if (!foinfoIni->getAddress(0).empty())
      foinfo->setAddress(0, foinfoIni->getAddress(0));
   if (!foinfoIni->getAddress(1).empty())
      foinfo->setAddress(1, foinfoIni->getAddress(1));
   if (!foinfoIni->getAddress(2).empty())
      foinfo->setAddress(2, foinfoIni->getAddress(2));
   if (!foinfoIni->getAddress(3).empty())
      foinfo->setAddress(3, foinfoIni->getAddress(3));
   pPiaOut = new PiaOut(*piacal, *taxes);
   pebsOut = new PebsOut(*workerData, *piadata, *foinfo, *pebs, *piaparms, *taxes,
      *earnProject);
   if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
      piacal->pebsOabCal();
      pebsOut->setPageNum();
      pebsOut->pebsWorkerInfo.prepareStrings();
   }
   else {
      pPiaOut->setPageNum(*piacal);
      pPiaOut->summary1Page.prepareStrings();
   }
   valid = FALSE;
   } catch (PiaException& e) {
      stemp = e.what();
      stemp += " in CAnypia32Doc::CAnypia32Doc()";
      AfxMessageBox(stemp);
   }
}

/// <summary>Destructor.</summary>
CAnypia32Doc::~CAnypia32Doc()
{
   delete pebsOut;
   delete pPiaOut;
   delete foinfoIni;
   delete foinfo;
   delete piacal;
   delete pebs;
   delete taxrates;
   delete taxes;
   delete piaparms;
   delete lawChange;
   delete assumptions;
   delete cachupIni;
   delete biprojIni;
   delete awincIni;
   delete baseyearIni;
   delete awbidatIni;
   delete awbidat;
   delete piawrite;
   delete piaread;
   delete userAssumptions;
   delete secondaryArray;
   delete widowArray;
   delete piadata;
   delete workerData;
   delete baseyear;
   delete configIni;
   delete config;
   delete earnProject;
   delete widowDataArray;
}

/// <summary>Initialize a new document.</summary>
BOOL CAnypia32Doc::OnNewDocument()
{
   if (!CDocument::OnNewDocument())
      return FALSE;

   // TODO: add reinitialization code here
   // (SDI documents will reuse this document)
   return TRUE;
}

/// <summary>Save current case with specified pathname.</summary>
//
// Arguments:
//   pszPathName: Specified pathname.
BOOL CAnypia32Doc::OnSaveDocument( const char* pszPathName )
{
   try {
      // check primary data and set primary factors
      piacal->dataCheck(workerData->getEntDate());
      // check auxiliary data and set auxiliary factors
      piacal->dataCheckAux(*widowDataArray, *widowArray, *secondaryArray);
   } catch (PiaException& e) {
      AfxMessageBox(e.getNumber());
      return FALSE;
   }
   try {
      ofstream out;  // output stream for saving case
      out.open(pszPathName, ios::out);
      if (!out.is_open()) {
         throw PiaException(PIA_IDS_GENFILE1);
      }
      out.setf(ios::fixed,ios::floatfield);
      BeginWaitCursor();
      piawrite->write(out);
      out.close();
      EndWaitCursor();
      SetModifiedFlag(FALSE);  // back to unmodified
      return TRUE;  // success
   } catch (PiaException&) {
      CString cstring;  // temporary string
      AfxFormatString1(cstring, PIA_IDS_OUTFILE, CString(pszPathName));
      AfxMessageBox(cstring);
      return FALSE;
   }
}

/// <summary>Open a case with specified pathname.</summary>
//
// Arguments:
//   pszPathName: Specified pathname.
BOOL CAnypia32Doc::OnOpenDocument( const char* pszPathName )
{
   ifstream in;  // output stream for saving case

   in.open(pszPathName, ios::in);
   if (!in.is_open()) {
      CString cstring;  // temporary string
      AfxFormatString1(cstring, PIA_IDS_OPENERR, CString(pszPathName));
      AfxMessageBox(cstring);
      return FALSE;
   }
   DeleteContents();
   SetModifiedFlag(TRUE);  //dirty during read
   BeginWaitCursor();
   try {
      piaread->read(in);
      in.close();
      EndWaitCursor();
      if (userAssumptions->getIaltaw() == AssumptionType::ALTERN_IIA || 
          userAssumptions->getIaltaw() == AssumptionType::PEBS_ASSUM) {
         userAssumptions->setIaltaw(AssumptionType::FLAT);
      }
      if (userAssumptions->getIaltbi() == AssumptionType::ALTERN_IIA || 
          userAssumptions->getIaltbi() == AssumptionType::PEBS_ASSUM) {
         userAssumptions->setIaltbi(AssumptionType::FLAT);
      }
      SetModifiedFlag(FALSE);  // back to unmodified
      piadata->setBirthDateMinus1(workerData->getBirthDate());
      OnFileRun();
      return TRUE;  // success
   } catch (PiaException& e)  {
      AfxMessageBox(e.getNumber());
      if (e.getNumber() == PIA_IDS_READERR) {
         OnNewDocument();
         return TRUE;
      }
      else {
         return FALSE;
      }
   }
}

/// <summary>Deletes contents of case.</summary>
void CAnypia32Doc::DeleteContents()
{
   workerData->deleteContents();
   piadata->deleteContents();
   earnProject->deleteContents();
   widowDataArray->deleteContents();
   widowArray->deleteContents();
   secondaryArray->deleteContents();
   userAssumptions->setIaltaw(AssumptionType::FLAT);
   userAssumptions->setIaltbi(AssumptionType::FLAT);
   if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
      piacal->pebsOabCal();
      pebsOut->pebsWorkerInfo.prepareStrings();
   }
   else {
      pPiaOut->summary1Page.prepareStrings();
   }
   valid = FALSE;
}

/// <summary>Serialization.</summary>
//
// Arguments:
//   ar: Archive to serialize to.
void CAnypia32Doc::Serialize( CArchive& ar )
{
   if (ar.IsStoring())
   {
      // TODO: add storing code here
   }
   else
   {
      // TODO: add loading code here
   }
}

/////////////////////////////////////////////////////////////////////////////
// CAnypia32Doc diagnostics

#ifdef _DEBUG
/// <summary>Checks for validity.</summary>
void CAnypia32Doc::AssertValid() const
{
   CDocument::AssertValid();
}

/// <summary>Dumps out document.</summary>
void CAnypia32Doc::Dump(CDumpContext& dc) const
{
   CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnypia32Doc commands

/// <summary>Respond to Social Security Statement Info menu choice.</summary>
void CAnypia32Doc::OnDialogsPebesinfo()
{
   //PebesDialog dlg;

   //dlg.m_istart = userAssumptions->getIstart();
   //dlg.m_ageplan = pebs->getAgePlan();
   //dlg.m_beginpebes = workerData->getIbegin();
   //dlg.m_birthyear = workerData->getBirthDate().year();
   //dlg.m_birthdate = workerData->getBirthDate();
   //dlg.m_deathdate = workerData->getDeathDate();
   //dlg.m_nonpenpebesdate = CString(DateFormatter::toString(
   //   workerData->getPubpenDate(), "s").c_str());

   //if (pebs->getMonthnow() == 0)
   //   pebs->setMonthnow();
   //dlg.m_imonth = pebs->getMonthnow() - 1;
   //dlg.m_nonpen = workerData->getPubpen();
   //int ret = (int)dlg.DoModal();
   //if (ret == IDOK) {
   //   if (dlg.m_ageplan != pebs->getAgePlan()) {
   //      pebs->setAgePlan(dlg.m_ageplan);
   //      valid = FALSE;
   //      SetModifiedFlag(TRUE);
   //   }
   //   if (dlg.m_beginpebes != workerData->getIbegin()) {
   //      workerData->setIbegin(dlg.m_beginpebes);
   //      valid = FALSE;
   //      SetModifiedFlag(TRUE);
   //   }
   //   if (dlg.m_imonth + 1 != pebs->getMonthnow()) {
   //      pebs->setMonthnow(dlg.m_imonth + 1);
   //      valid = FALSE;
   //      SetModifiedFlag(TRUE);
   //   }
   //   if (workerData->getPubpen() != dlg.m_nonpen) {
   //      workerData->setPubpen((float)dlg.m_nonpen);
   //      valid = FALSE;
   //      SetModifiedFlag(TRUE);
   //   }
   //   if (workerData->getPubpenDate() != dlg.m_nonpendatetemp) {
   //      if (dlg.m_nonpen == 0.0) {
   //         workerData->deletePubpenDate();
   //         valid = FALSE;
   //         SetModifiedFlag(TRUE);
   //      } else {
   //         workerData->setPubpenDate(dlg.m_nonpendatetemp);
   //         valid = FALSE;
   //         SetModifiedFlag(TRUE);
   //      }
   //   }
   //   earnProject->setPebsData(userAssumptions->getIstart(),
   //      workerData->getIbegin());
   //   workerData->setPebsData();
   //   workerData->setPebsEarn(userAssumptions->getIstart());
   //   piacal->pebsOabCal();
   //   pebsOut->pebsWorkerInfo.prepareStrings();
   //   UpdateAllViews(NULL);
   //}
}

/// <summary>Update Social Security Statement Info menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsPebesinfo( CCmdUI* pCmdUI )
{
   //// do not allow for non-PEBES calculation
   //if (workerData->getJoasdi() != WorkerData::PEBS_CALC) {
   //   pCmdUI->Enable(false);
   //   return;
   //}
   //// do not allow if date of birth has not been set yet
   //try {
   //   if (!workerData->getBirthDate().is_not_a_date()) {
   //      workerData->birth1Check(userAssumptions->getIstart());
   //   } else {
   //     pCmdUI->Enable(false);
   //     return;
   //   }
   //} catch (PiaException&) {
   //   pCmdUI->Enable(false);
   //   return;
   //}
   //pCmdUI->Enable(true);
}

/// <summary>Handle Supplemental Worker Info menu choice.</summary>
void CAnypia32Doc::OnDialogsNonpebesinfo() 
{
   NonPebesDialog dlg;

   dlg.m_birthyear = workerData->getBirthDate().year();
   dlg.m_joasdi = workerData->getJoasdi();
   dlg.m_ent = CString(DateFormatter::toString(
      workerData->getEntDate(), "s").c_str());
   dlg.m_bendate = CString(DateFormatter::toString(
      workerData->getBenefitDate(), "s").c_str());
   dlg.m_backtype = earnProject->getProjback();
   dlg.m_bback = ((earnProject->getProjback() > 0) &&
      workerData->getIndearn());
   dlg.m_fwrdtype = earnProject->getProjfwrd();
   dlg.m_bfwrd = ((earnProject->getProjfwrd() > 0) &&
      workerData->getIndearn());
   dlg.m_indearn = workerData->getIndearn();
   dlg.m_bnonpen = PiaCal::getPubpenEnable(*workerData);
   dlg.m_birthdate = workerData->getBirthDate();
   dlg.m_deathdate = workerData->getDeathDate();
   dlg.M_nonpendate = CString(DateFormatter::toString(
      workerData->getPubpenDate(), "s").c_str());
   if (dlg.m_bback) {
      dlg.m_begin = earnProject->getFirstYear();
      // correct initialization of getIbegin() if necessary
      dlg.m_backyear = (workerData->getIbegin() == 0) ?
         YEAR37 : workerData->getIbegin();
      dlg.m_backperc = earnProject->getPercback();
   }
   else {
      // leave m_backyear and m_backperc at current values for user
      dlg.m_begin = workerData->getIbegin();
   }
   if (dlg.m_bfwrd) {
      dlg.m_end = earnProject->getLastYear();
      // correct initialization of getIend() if necessary
      dlg.m_fwrdyear = (workerData->getIend() == 0) ?
         YEAR2095 : workerData->getIend();
      dlg.m_fwrdperc = earnProject->getPercfwrd();
   }
   else {
      // leave m_fwrdyear and m_fwrdperc at current values for user
      dlg.m_end = workerData->getIend();
   }
   dlg.m_recalc = workerData->getRecalc();
   dlg.m_nonpen = workerData->getPubpen();
   dlg.m_valdi = workerData->getValdi();
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      // do not use entitlement date in a survivor case
      if (workerData->getJoasdi() != WorkerData::SURVIVOR) {
         if (workerData->getEntDate() != dlg.enttemp) {
            workerData->setEntDate(dlg.enttemp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      bool brecalc = (dlg.m_recalc == TRUE);
      if (workerData->getRecalc() != brecalc) {
         workerData->setRecalc(brecalc);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      // use benefit date if recalculation or a survivor
      if (workerData->getRecalc() ||
         workerData->getJoasdi() == WorkerData::SURVIVOR) {
         if (workerData->getBenefitDate() != dlg.bendttemp) {
            workerData->setBenefitDate(dlg.bendttemp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      else {
         workerData->setBenefitDate();
      }
      // Always check to see if first year should be set in earnProject
      if (workerData->getIndearn() &&
         earnProject->getFirstYear() != dlg.m_begin) {
         earnProject->setFirstYear(dlg.m_begin);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_bback) {
         if (workerData->getIbegin() != dlg.m_backyear) {
            workerData->setIbegin(dlg.m_backyear);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (earnProject->getPercback() != dlg.m_backperc) {
            earnProject->setPercback(dlg.m_backperc);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      else {
         if (dlg.m_indearn && workerData->getIbegin() != dlg.m_begin) {
            workerData->setIbegin(dlg.m_begin);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      // Always check to see if last year should be set in earnProject
      if (workerData->getIndearn() &&
         earnProject->getLastYear() != dlg.m_end) {
         earnProject->setLastYear(dlg.m_end);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_bfwrd) {
         if (workerData->getIend() != dlg.m_fwrdyear) {
            workerData->setIend(dlg.m_fwrdyear);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (earnProject->getPercfwrd() != dlg.m_fwrdperc) {
            earnProject->setPercfwrd(dlg.m_fwrdperc);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      else {
         if (dlg.m_indearn && workerData->getIend() != dlg.m_end) {
            workerData->setIend(dlg.m_end);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      if (dlg.m_bback) {
         if (dlg.m_backtype != earnProject->getProjback()) {
            earnProject->setProjback(dlg.m_backtype);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      if (dlg.m_bfwrd) {
         if (dlg.m_fwrdtype != earnProject->getProjfwrd()) {
            earnProject->setProjfwrd(dlg.m_fwrdtype);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      if (workerData->getPubpen() != dlg.m_nonpen) {
         workerData->setPubpen((float)dlg.m_nonpen);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_valdi != workerData->getValdi()) {
         workerData->setValdi(dlg.m_valdi);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (workerData->getPubpenDate() != dlg.m_nonpendatetemp) {
         if (dlg.m_nonpen == 0.0) {
            workerData->deletePubpenDate();
            valid = FALSE;
            SetModifiedFlag(TRUE);
         } else {
            workerData->setPubpenDate(dlg.m_nonpendatetemp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      pPiaOut->summary1Page.prepareStrings();
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Non-Statement Info menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsNonpebesinfo( CCmdUI* pCmdUI )
{
   // do not allow for PEBES calculation
   if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
      pCmdUI->Enable(false);
      return;
   }
   // do not allow if date of birth has not been set yet
   try {
      if (!workerData->getBirthDate().is_not_a_date()) {
         workerData->birth2Check();
      } else {
         pCmdUI->Enable(false);
         return;
      }
   } catch (PiaException&) {
      pCmdUI->Enable(false);
      return;
   }
   pCmdUI->Enable(true);
}

/// <summary>Handle Basic Worker Info menu choice.</summary>
void CAnypia32Doc::OnDialogsWorkerinfo() 
{
   WorkerDialog dlg;

   dlg.m_dob = CString(DateFormatter::toString(workerData->getBirthDate(), "s").c_str());
   dlg.m_death = CString(DateFormatter::toString(workerData->getDeathDate(), "s").c_str());
   dlg.m_mqge = workerData->getMqge();
   dlg.m_blind = workerData->getBlindind();
   dlg.m_deemed = workerData->getDeemedind();
   dlg.m_totalize = workerData->getTotalize();
   dlg.m_indearn = !workerData->getIndearn();
   dlg.m_indrr = workerData->getIndrr();
   dlg.m_rryear1 = workerData->railRoadData.getFirstYear();
   if (workerData->railRoadData.getEarn3750() > 0. || hasrr3750)
      dlg.m_rryear1 = 1950;
   dlg.m_rryear2 = workerData->railRoadData.getLastYear();
   if (dlg.m_rryear2 < 1950)
      dlg.m_rryear2 = 1950;
   dlg.m_indms = (workerData->milServDatesVec.getMSCount() > 0);
   dlg.m_mscount = workerData->milServDatesVec.getMSCount();
   dlg.m_nhaddr1 = CString(workerData->getNhaddr(0).c_str());
   dlg.m_nhaddr2 = CString(workerData->getNhaddr(1).c_str());
   dlg.m_nhaddr3 = CString(workerData->getNhaddr(2).c_str());
   dlg.m_nhname = CString(workerData->getNhname().c_str());
   dlg.m_ssn1 = CString(workerData->ssn.getPart1().c_str());
   dlg.m_ssn2 = CString(workerData->ssn.getPart2().c_str());
   dlg.m_ssn3 = CString(workerData->ssn.getPart3().c_str());
   dlg.m_fammem = widowArray->getFamSize();
   if (earnProject->getProjback() < 0)
      earnProject->setProjback(0);
   if (earnProject->getProjfwrd() < 0)
      earnProject->setProjfwrd(0);
   // sex is stored as male: 0, female: 1, but the dialog box uses
   // female: 0, male: 1
   dlg.m_sex = 1 - (int)workerData->getSex();
   dlg.m_bentype = (std::max)(workerData->getJoasdi() - 1, 0);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      if (workerData->getBirthDate() != dlg.m_dobtemp) {
         workerData->setBirthDate(dlg.m_dobtemp);
         piadata->setBirthDateMinus1(workerData->getBirthDate());
         piadata->ageEnt.deleteContents();
         piadata->ageBen.deleteContents();
         piadata->fullRetAge.deleteContents();
         piadata->earlyRetAge.deleteContents();
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      bool btemp = (dlg.m_mqge == TRUE);
      if (workerData->getMqge() != btemp) {
         workerData->setMqge(btemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      btemp = (dlg.m_blind == TRUE);
      if (workerData->getBlindind() != btemp) {
         workerData->setBlindind(btemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      btemp = (dlg.m_deemed == TRUE);
      if (workerData->getDeemedind() != btemp) {
         workerData->setDeemedind(btemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      btemp = (dlg.m_totalize == TRUE);
      if (workerData->getTotalize() != btemp) {
         workerData->setTotalize(btemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      btemp = (dlg.m_indearn == FALSE);
      if (workerData->getIndearn() != btemp) {
         workerData->setIndearn(btemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      btemp = (dlg.m_indrr == TRUE);
      if (workerData->getIndrr() != btemp) {
         workerData->setIndrr(btemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (workerData->getIndrr()) {
         if (dlg.m_rryear1 == 1950) {
            hasrr3750 = true;
            if (dlg.m_rryear2 > 1950)
               dlg.m_rryear1 = 1951;
            else
               dlg.m_rryear1 = YEAR37;
         }
         if (workerData->railRoadData.getFirstYear() != dlg.m_rryear1) {
            workerData->railRoadData.setFirstYear(dlg.m_rryear1);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (workerData->railRoadData.getLastYear() != dlg.m_rryear2) {
            workerData->railRoadData.setLastYear(dlg.m_rryear2);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      else {
         hasrr3750 = false;
         workerData->railRoadData.setEarn3750(0.);
         workerData->railRoadData.setQc3750(0);
      }
      if (dlg.m_indms) {
         if (dlg.m_mscount != workerData->milServDatesVec.getMSCount()) {
            workerData->milServDatesVec.setMSCount(dlg.m_mscount);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      else {
         if (workerData->milServDatesVec.getMSCount() > 0) {
            workerData->milServDatesVec.setMSCount(0);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      if (dlg.m_nhaddr1 != CString(workerData->getNhaddr(0).c_str())) {
         workerData->setNhaddr(0, string(dlg.m_nhaddr1));
         // still valid
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_nhaddr2 != CString(workerData->getNhaddr(1).c_str())) {
         workerData->setNhaddr(1, string(dlg.m_nhaddr2));
         // still valid
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_nhaddr3 != CString(workerData->getNhaddr(2).c_str())) {
         workerData->setNhaddr(2, string(dlg.m_nhaddr3));
         // still valid
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_nhname != CString(workerData->getNhname().c_str())) {
         workerData->setNhname(string(dlg.m_nhname));
         // still valid
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_ssn1 != CString(workerData->ssn.getPart1().c_str()) ||
         dlg.m_ssn2 != CString(workerData->ssn.getPart2().c_str()) ||
         dlg.m_ssn3 != CString(workerData->ssn.getPart3().c_str())) {
         workerData->ssn.setSsnFull(string((const char *)dlg.m_ssn1),
            string((const char *)dlg.m_ssn2), string((const char *)dlg.m_ssn3));
         // still valid
         SetModifiedFlag(TRUE);
      }
      // sex is stored as male: 0, female: 1, but the dialog box uses
      // female: 0, male: 1
      Sex::sex_type sextemp = (Sex::sex_type)(1 - dlg.m_sex);
      if (workerData->getSex() != sextemp) {
         workerData->setSex(sextemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (workerData->getJoasdi() != dlg.m_bentype + 1) {
         workerData->setJoasdi(dlg.m_bentype + 1);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (workerData->getJoasdi() != WorkerData::SURVIVOR) {
         workerData->deleteDeathDate();
      }
      else {
         // must have at least 1 survivor
         if (dlg.m_fammem < 1)
            dlg.m_fammem = 1;
         if (workerData->getDeathDate()!= dlg.m_deathtemp) {
            workerData->setDeathDate(dlg.m_deathtemp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
         // no family members for PEBS
         if (dlg.m_fammem > 0) {
            dlg.m_fammem = 0;
         }
         bool hasPebsAssumptions = true;
         if ((userAssumptions->getIaltaw() != AssumptionType::FLAT) &&
            (userAssumptions->getIaltaw() != AssumptionType::PEBS_ASSUM)) {
            hasPebsAssumptions = false;
            userAssumptions->setIaltaw( AssumptionType::FLAT);
         }
         if ((userAssumptions->getIaltbi() != AssumptionType::FLAT) &&
            (userAssumptions->getIaltbi() != AssumptionType::PEBS_ASSUM)) {
            hasPebsAssumptions = false;
            userAssumptions->setIaltbi( AssumptionType::FLAT);
         }
         if (!hasPebsAssumptions) {
            piacal->calculate1(*assumptions);
         }
         workerData->setRecalc(false);
         earnProject->setPebsData(userAssumptions->getIstart(),
            workerData->getIbegin());
         workerData->setPebsData();
      }
      if (widowArray->getFamSize() != dlg.m_fammem) {
         if (dlg.m_fammem < widowArray->getFamSize()) {
            for (int i = dlg.m_fammem; i < widowArray->getFamSize(); i++)
               secondaryArray->secondary[i]->deleteContents();
         }
         widowArray->setFamSize(dlg.m_fammem);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (workerData->getJoasdi() == WorkerData::DISABILITY &&
         workerData->getValdi() == 0)
         workerData->setValdi(1);
      if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
         piacal->pebsOabCal();
         pebsOut->pebsWorkerInfo.prepareStrings();
      }
      else {
         pPiaOut->summary1Page.prepareStrings();
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Disability Info menu choice.</summary>
void CAnypia32Doc::OnDialogsDisabilityinfo()
{
   DisabDialog dlg;

   dlg.m_valdi = workerData->getValdi();
   dlg.m_ioasdi = workerData->getJoasdi();
   dlg.m_birthDate = workerData->getBirthDate();
   dlg.m_deathDate = workerData->getDeathDate();
   dlg.m_entDate = workerData->getEntDate();
   dlg.m_benDate = workerData->getBenefitDate();
   const DisabPeriod disabPeriod0 = workerData->disabPeriod[0];
   const DisabPeriod disabPeriod1 = workerData->disabPeriod[1];
   dlg.m_onset = CString(DateFormatter::toString(
      disabPeriod0.getOnsetDate(), "s").c_str());
   dlg.m_dicess = CString(DateFormatter::toString(
      disabPeriod0.getCessationDate(), "s").c_str());
   dlg.m_pia = disabPeriod0.getCessationPia();
   dlg.m_mfb = disabPeriod0.getCessationMfb();
   dlg.m_waitpd = CString(DateFormatter::toString(
      disabPeriod0.getWaitperDate(), "s").c_str());
  if (workerData->getJoasdi() == WorkerDataGeneral::DISABILITY) {
    dlg.m_prrent = CString(DateFormatter::toString(
      workerData->getEntDate(), "s").c_str());
  }
  else {
    dlg.m_prrent = CString(DateFormatter::toString(
      disabPeriod0.getEntDate(), "s").c_str());
  }
   if (workerData->getValdi() > 1) {
      dlg.m_onset1 = CString(DateFormatter::toString(
         disabPeriod1.getOnsetDate(), "s").c_str());
      dlg.m_dicess1 = CString(DateFormatter::toString(
         disabPeriod1.getCessationDate(), "s").c_str());
      dlg.m_pia1 = disabPeriod1.getCessationPia();
      dlg.m_mfb1 = disabPeriod1.getCessationMfb();
      dlg.m_waitpd1 = CString(DateFormatter::toString(
         disabPeriod1.getWaitperDate(), "s").c_str());
      dlg.m_prrent1 = CString(DateFormatter::toString(
         disabPeriod1.getEntDate(), "s").c_str());
   }
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      if (dlg.m_onsettemp!= disabPeriod0.getOnsetDate()) {
         workerData->setOnsetDate(0, dlg.m_onsettemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_waitpdtemp != disabPeriod0.getWaitperDate()) {
         workerData->setWaitperDate(0, dlg.m_waitpdtemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_prrenttemp != disabPeriod0.getEntDate()) {
         workerData->setPriorentDateCheck(0, dlg.m_prrenttemp);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (workerData->needDiCess()) {
         if (dlg.m_dicesstemp != disabPeriod0.getCessationDate()) {
            workerData->setCessationDate(0, dlg.m_dicesstemp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_pia != disabPeriod0.getCessationPia()) {
            workerData->setCessationPia(0, dlg.m_pia);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_mfb != disabPeriod0.getCessationMfb()) {
            workerData->setCessationMfb(0, dlg.m_mfb);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      if (workerData->getValdi() > 1) {
         if (dlg.m_onset1temp != disabPeriod1.getOnsetDate()) {
            workerData->setOnsetDate(1, dlg.m_onset1temp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_waitpd1temp != disabPeriod1.getWaitperDate()) {
            workerData->setWaitperDate(1, dlg.m_waitpd1temp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_prrent1temp != disabPeriod1.getEntDate()) {
            workerData->setPriorentDateCheck(1, dlg.m_prrent1temp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_dicess1temp != disabPeriod1.getCessationDate()) {
            workerData->setCessationDate(1, dlg.m_dicess1temp);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_pia1 != disabPeriod1.getCessationPia()) {
            workerData->setCessationPia(1, dlg.m_pia1);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_mfb1 != disabPeriod1.getCessationMfb()) {
            workerData->setCessationMfb(1, dlg.m_mfb1);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      pPiaOut->summary1Page.prepareStrings();
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Disability Info menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsDisabilityinfo( CCmdUI* pCmdUI )
{
   try {
      // do not allow if date of birth has not been set yet
      if (!workerData->getBirthDate().is_not_a_date()) {
         workerData->birth2Check();
      } else {
         pCmdUI->Enable(false);
         return;
      }
      // do not allow if date of benefit has not been set yet or is invalid
      if (!workerData->getBenefitDate().isNotADate()) {
        workerData->benefitDate1Check();
      } else {
        pCmdUI->Enable(false);
        return;
      }
   } catch (PiaException&) {
      pCmdUI->Enable(false);
      return;
   }
   pCmdUI->Enable(workerData->getValdi() > 0);
}

/// <summary>Handle Family Members menu choice.</summary>
void CAnypia32Doc::OnDialogsSurvivorinfo()
{
   DeathDialog dlg;
   WorkerData* widowdatat;
   Secondary* secondaryt;
   dlg.m_ioasdi = workerData->getJoasdi();
   dlg.m_famsize = widowArray->getFamSize();
   for (int i = 0; i < widowArray->getFamSize(); i++) {
      widowdatat = widowDataArray->workerData[i];
      secondaryt = secondaryArray->secondary[i];
      dlg.m_jbirthtemp[i] = widowdatat->getBirthDate();
      dlg.m_jenttemp[i] = secondaryt->entDate;
      dlg.m_jonsettemp[i] = widowdatat->disabPeriod[0].getOnsetDate();
      dlg.m_isurv[i] = secondaryt->bic.getMajorBic();
      dlg.m_young[i] = secondaryt->bic.getMinorBic();
   }
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int i = 0; i < widowArray->getFamSize(); i++) {
         widowdatat = widowDataArray->workerData[i];
         secondaryt = secondaryArray->secondary[i];
         if (secondaryt->bic.getMajorBic() != dlg.m_isurv[i]) {
            secondaryt->bic.setMajorBic(dlg.m_isurv[i]);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (secondaryt->bic.getMinorBic() != dlg.m_young[i]) {
            secondaryt->bic.setMinorBic(dlg.m_young[i]);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (widowdatat->getBirthDate() != dlg.m_jbirthtemp[i]) {
            widowdatat->setBirthDate(dlg.m_jbirthtemp[i]);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (secondaryt->entDate != dlg.m_jenttemp[i]) {
            secondaryt->entDate = dlg.m_jenttemp[i];
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (secondaryt->bic.getMajorBic() == 'W') {
            if (widowdatat->disabPeriod[0].getOnsetDate() !=
               dlg.m_jonsettemp[i]) {
               widowdatat->setOnsetDate(0, dlg.m_jonsettemp[i]);
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
         }
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Family Info menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsSurvivorinfo( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(widowArray->getFamSize() > 0);
}

/// <summary>Handle Summary Qcs menu choice.</summary>
void CAnypia32Doc::OnDialogsSummaryqcs()
{
   QctotDialog dlg;

   dlg.m_qctd = workerData->getQctottd();
   dlg.m_qc51td = workerData->getQctot51td();
   dlg.m_bqc51td = (workerData->getIbegin() < 1951 &&
      workerData->getIend() > 1950);
   dlg.m_qcann = workerData->hasQcsByYear();
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      bool qcann = (dlg.m_qcann == TRUE);
      if (workerData->hasQcsByYear() != qcann) {
         workerData->setQcsByYear(qcann);
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      if (!qcann) {
         if (workerData->getQctottd() != dlg.m_qctd) {
            workerData->setQctd(dlg.m_qctd);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (dlg.m_bqc51td && workerData->getQctot51td() != dlg.m_qc51td) {
            workerData->setQc51td(dlg.m_qc51td);
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Summary QCs menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsSummaryqcs( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(workerData->getIbegin() < 1978 &&
      workerData->getIbegin() > 1936);
}

/// <summary>Converts an assumption type to a radio index.</summary>
//
// Arguments:
//   assumtype: AssumptionType to convert.
int CAnypia32Doc::AssumptionTypeToDialog( int assumtype )
{
   switch (assumtype) {
     case AssumptionType::ALTERN_I:
       return 0;
     case AssumptionType::ALTERN_IIB:
       return 1;
     case AssumptionType::ALTERN_III:  
       return 2;
     case AssumptionType::FLAT: 
       return 3;
     case AssumptionType::OTHER_ASSUM:
       return 4;
     case AssumptionType::PEBS_ASSUM:
     case AssumptionType::ALTERN_IIA:
     default: 
       return -1;
   }
}

/// <summary>Converts a radio index to an assumption type.</summary>
//
// Arguments:
//   dialog: Radio index to convert.
int CAnypia32Doc::DialogToAssumptionType( int dialog )
{
   switch (dialog) {
     case 0:
       return AssumptionType::ALTERN_I;
     case 1:
       return AssumptionType::ALTERN_IIB;
     case 2:
       return AssumptionType::ALTERN_III;  
     case 3:
       return AssumptionType::FLAT; 
     case 4:
       return AssumptionType::OTHER_ASSUM;
     default:
       return -1;
   }
}

/// <summary>Handle Assumptions menu choice.</summary>
void CAnypia32Doc::OnDialogsAssumptions()
{
   AssumptionsDialog dlg;
   dlg.m_ialtbi = AssumptionTypeToDialog(userAssumptions->getIaltbi());
   dlg.m_ialtaw = AssumptionTypeToDialog(userAssumptions->getIaltaw());
   for (int i = 0; i < 6; i++) {
      dlg.m_beninc[i] = CString(assumptions->getBenefitInc(i + 1).c_str());
      dlg.m_avgwage[i] = CString(assumptions->getAverageWage(i + 1).c_str());
   }
   dlg.m_bitext = CString(userAssumptions->titleBi.c_str());
   dlg.m_awtext = CString(userAssumptions->titleAw.c_str());
   dlg.m_bases = userAssumptions->getIbasch() - 1;
   dlg.m_cachup = (userAssumptions->getAnscch() == 'Y');
   dlg.m_bbases = workerData->need_bases(userAssumptions->getIstart());
   dlg.m_bpebes = (workerData->getJoasdi() == WorkerData::PEBS_CALC);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      if (userAssumptions->getIaltbi() != DialogToAssumptionType(dlg.m_ialtbi)) {
         userAssumptions->setIaltbi(DialogToAssumptionType(dlg.m_ialtbi));
         valid = false;
         SetModifiedFlag(TRUE);
      }
      if (DialogToAssumptionType(dlg.m_ialtbi) == AssumptionType::OTHER_ASSUM &&
         CString(userAssumptions->titleBi.c_str()) != dlg.m_bitext) {
         userAssumptions->titleBi = dlg.m_bitext;
         valid = false;
         SetModifiedFlag(TRUE);
      }
      if (userAssumptions->getIaltaw() != DialogToAssumptionType(dlg.m_ialtaw)) {
         userAssumptions->setIaltaw(DialogToAssumptionType(dlg.m_ialtaw));
         valid = false;
         SetModifiedFlag(TRUE);
      }
      if (DialogToAssumptionType(dlg.m_ialtaw) == AssumptionType::OTHER_ASSUM &&
         CString(userAssumptions->titleAw.c_str()) != dlg.m_awtext) {
         userAssumptions->titleAw = dlg.m_awtext;
         valid = false;
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_bases + 1 != userAssumptions->getIbasch()) {
         userAssumptions->setIbasch(dlg.m_bases + 1);
         valid = false;
         SetModifiedFlag(TRUE);
      }
      if (dlg.m_cachup && (userAssumptions->getAnscch() == 'N')) {
         userAssumptions->setAnscch('Y');
         valid = false;
         SetModifiedFlag(TRUE);
      }
      if (!dlg.m_cachup && (userAssumptions->getAnscch() == 'Y')) {
         userAssumptions->setAnscch('N');
         valid = false;
         SetModifiedFlag(TRUE);
      }
      piacal->calculate1(*assumptions);
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Assumptions menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsAssumptions( CCmdUI* pCmdUI )
{
  if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
    pCmdUI->Enable(TRUE);
  }
  else {
    const bool enableAssumptions =
      workerData->need_bi(userAssumptions->getIstart()) ||
      workerData->need_aw(userAssumptions->getIstart(),
      earnProject->need_aw(userAssumptions->getIstart(),
      workerData->getIend()));
    pCmdUI->Enable(enableAssumptions);
    if (!enableAssumptions) {
      userAssumptions->setIaltaw(AssumptionType::FLAT);
      userAssumptions->setIaltbi(AssumptionType::FLAT);
    }
  }
}

/// <summary>Handle Benefit Increases menu choice.</summary>
void CAnypia32Doc::OnDialogsBenefitincreases()
{
   BiprojDialog dlg;

   for (int i = 0; i <= BiprojNonFile::NUMPROJYEARS; i++) {
      int year = UserAssumptions::getIstart() + i;
      dlg.m_biproj[year] = userAssumptions->biproj[year];
   }
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int i = 0; i < BiprojNonFile::NUMPROJYEARS; i++) {
         int year = UserAssumptions::getIstart() + i;
         if (dlg.m_biproj[year] != userAssumptions->biproj[year]) {
            userAssumptions->biproj[year] = dlg.m_biproj[year];
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      const double ftemp = dlg.m_biproj[UserAssumptions::getIstart() +
         BiprojNonFile::NUMPROJYEARS];
      if (ftemp != userAssumptions->biproj[
         UserAssumptions::getIstart() + BiprojNonFile::NUMPROJYEARS]) {
         for (int i = UserAssumptions::getIstart() +
            BiprojNonFile::NUMPROJYEARS;
            i <= userAssumptions->biproj.getLastYear(); i++) {
            userAssumptions->biproj[i] = ftemp;
         }
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Benefit Increases menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsBenefitincreases( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(workerData->need_bi(UserAssumptions::getIstart()) &&
      userAssumptions->getIaltbi() == AssumptionType::OTHER_ASSUM);
}

/// <summary>Handle Average Wage Increases menu choice.</summary>
void CAnypia32Doc::OnDialogsAveragewageincreases()
{
   AwprojDialog dlg;

   for (int i = -1; i < AwincNonFile::NUMPROJYEARS; i++) {
      int year = UserAssumptions::getIstart() + i;
      dlg.m_awproj[year] = userAssumptions->awincproj[year];
   }
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int i = -1; i < AwincNonFile::NUMPROJYEARS - 1; i++) {
         int year = UserAssumptions::getIstart() + i;
         if (dlg.m_awproj[year] != userAssumptions->awincproj[year]) {
            userAssumptions->awincproj[year] = dlg.m_awproj[year];
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      double dtemp = dlg.m_awproj[UserAssumptions::getIstart() +
         AwincNonFile::NUMPROJYEARS - 1];
      if (dtemp != userAssumptions->awincproj[
         UserAssumptions::getIstart() + AwincNonFile::NUMPROJYEARS - 1]) {
         for (int i = UserAssumptions::getIstart() +
            AwincNonFile::NUMPROJYEARS - 1;
            i <= userAssumptions->awincproj.getLastYear(); i++) {
            userAssumptions->awincproj[i] = dlg.m_awult;
         }
         valid = FALSE;
         SetModifiedFlag(TRUE);
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Average Wage Increases menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsAveragewageincreases( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(workerData->need_aw(userAssumptions->getIstart(),
      earnProject->need_aw(userAssumptions->getIstart(),
      workerData->getIend())) &&
      userAssumptions->getIaltaw() == AssumptionType::OTHER_ASSUM);
}

/// <summary>Handle Catch-up Increases menu choice.</summary>
void CAnypia32Doc::OnDialogsCatchupincreases() 
{
   CuprojDialog dlg;

   dlg.m_cachup = userAssumptions->catchup;
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int i = dlg.m_cachup.getCstart();
      i < dlg.m_cachup.getCstart() + 10; i++) {
         for (int j = dlg.m_cachup.getCstart() + 2;
            j < dlg.m_cachup.getCstart() + 10; j++) {
            if (dlg.m_cachup.get(i, j) != userAssumptions->catchup.get(i, j)) {
               userAssumptions->catchup.set(i, j, dlg.m_cachup.get(i, j));
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
         }
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Catch-up Increases menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsCatchupincreases( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(userAssumptions->getAnscch() == 'Y');
}

/// <summary>Handle Wage Bases menu choice.</summary>
void CAnypia32Doc::OnDialogsWagebases()
{
   WageBaseDialog dlg;

   dlg.m_istartyear = UserAssumptions::getIstart() + 1;
   dlg.m_ilastyear = workerData->getEntDate().getYear();
   dlg.m_year = dlg.m_istartyear;
   for (int year = dlg.m_istartyear; year <= dlg.m_ilastyear; year++) {
      dlg.m_DAplwb[year] = userAssumptions->baseOasdi[year];
      dlg.m_DAolwb[year] = userAssumptions->base77[year];
   }
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int year = dlg.m_istartyear; year <= dlg.m_ilastyear; year++) {
         if (dlg.m_DAplwb[year] != userAssumptions->baseOasdi[year]) {
            userAssumptions->baseOasdi[year] = dlg.m_DAplwb[year];
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      for (int year = dlg.m_istartyear; year <= dlg.m_ilastyear; year++) {
         if (dlg.m_DAolwb[year] != userAssumptions->base77[year]) {
            userAssumptions->base77[year] = dlg.m_DAolwb[year];
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Wage Bases menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsWagebases( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(userAssumptions->getIbasch() == 2);
}

/// <summary>Handle Annual Earnings Info menu choice.</summary>
void CAnypia32Doc::OnDialogsAnnualearningsinfo()
{
   EarningsDialog dlg;

  try {
    dlg.m_istartyear = earnProject->getFirstYear();
    dlg.m_ilastyear = earnProject->getLastYear();
    dlg.m_istartyearrr = workerData->railRoadData.getFirstYear();
    if (workerData->railRoadData.getEarn3750() > 0. || hasrr3750)
      dlg.m_istartyearrr = 1950;
    dlg.m_ilastyearrr = workerData->railRoadData.getLastYear();
    if (dlg.m_istartyearrr == 1950 && dlg.m_ilastyearrr < 1950)
      dlg.m_ilastyearrr = 1950;
    dlg.m_qcbyyear = workerData->hasQcsByYear();
    dlg.m_mqge = workerData->getMqge();
    dlg.m_bpebes = (workerData->getJoasdi() == WorkerData::PEBS_CALC);
    dlg.m_indrr = workerData->getIndrr();
    dlg.m_indearn = workerData->getIndearn();
    if (dlg.m_indearn) {
      for (int i = dlg.m_istartyear; i <= dlg.m_ilastyear; i++) {
         dlg.m_DAoasdi[i] = earnProject->earnpebs[i];
         dlg.m_DAhi[i] = workerData->getEarnHi(i);
         dlg.m_IAearntype[i] = earnProject->getEarntype()[i];
         dlg.m_IAtaxtype[i] = (int)workerData->getTaxType(i);
         dlg.m_IAqc[i] = workerData->qc.get(i);
         dlg.m_DAbase[i] = piaparms->getBaseOasdi(i);
         dlg.m_DAfq[i] = piaparms->getFq(i);
         dlg.m_DAwaghigh[i] = piaparms->getWageHigh(i);
         dlg.m_DAwagmin[i] = piaparms->getWageMin(i);
         dlg.m_BAchildcare.setBit(i, workerData->childCareYears.getBit(i));
      }
    }
    if (dlg.m_indrr) {
      if (dlg.m_istartyearrr == 1950) {
        dlg.m_DArrearn[1950] = workerData->railRoadData.getEarn3750();
        dlg.m_IArrqc[1950] = workerData->railRoadData.getQc3750();
      }
      for (int yr = (std::max)(1951, dlg.m_istartyearrr);
        yr <= dlg.m_ilastyearrr; yr++) {
        dlg.m_DArrearn[yr] = workerData->railRoadData.earningsArray[yr];
      }
      for (int yr = (std::max)(1951, dlg.m_istartyearrr);
        yr <= (std::min)(1977, dlg.m_ilastyearrr); yr++) {
        dlg.m_IArrqc[yr] = workerData->railRoadData.qcArray.get(yr);
      }
    }
    int ret = (int)dlg.DoModal();
    if (ret == IDOK) {
      if (dlg.m_indearn) {
         for (int i = dlg.m_istartyear; i <= dlg.m_ilastyear; i++) {
            if (workerData->childCareYears.getBit(i) !=
               dlg.m_BAchildcare.getBit(i)) {
               workerData->childCareYears.setBit(i, dlg.m_BAchildcare.getBit(i));
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
            if (earnProject->earnpebs[i] != dlg.m_DAoasdi[i]) {
               earnProject->earnpebs[i] = dlg.m_DAoasdi[i];
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
            if (dlg.m_mqge && workerData->getEarnHi(i) != dlg.m_DAhi[i]) {
               workerData->setEarnHi(i, dlg.m_DAhi[i]);
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
            if (earnProject->getEarntype()[i] != dlg.m_IAearntype[i]) {
               earnProject->setEarntype(i, dlg.m_IAearntype[i]);
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
            if ((int)workerData->getTaxType(i) != dlg.m_IAtaxtype[i]) {
               workerData->setTaxType(i, dlg.m_IAtaxtype[i]);
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
            if (dlg.m_qcbyyear && i < 1978 &&
               workerData->qc.get(i) != dlg.m_IAqc[i]) {
               workerData->qc.set(i, dlg.m_IAqc[i]);
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
         }
      }
      if (dlg.m_indrr) {
         if (dlg.m_istartyearrr == 1950) {
            workerData->railRoadData.setEarn3750(dlg.m_DArrearn[1950]);
            workerData->railRoadData.setQc3750(dlg.m_IArrqc[1950]);
         }
         for (int i = (std::max)(1951, dlg.m_istartyearrr);
            i <= dlg.m_ilastyearrr; i++) {
            if (workerData->railRoadData.earningsArray[i] != dlg.m_DArrearn[i]) {
               workerData->railRoadData.earningsArray[i] = dlg.m_DArrearn[i];
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
            if (i < 1978 &&
            workerData->railRoadData.qcArray.get(i) != dlg.m_IArrqc[i]) {
               workerData->railRoadData.qcArray.set(i, dlg.m_IArrqc[i]);
               valid = FALSE;
               SetModifiedFlag(TRUE);
            }
         }
      }
      // set total QCs pre-1951 and 1951 to last qc year (1977)
      if (dlg.m_qcbyyear) {
         int qctdt = 0;
         int qc51tdt = 0;
         if (dlg.m_indearn) {
            qctdt = workerData->qc.accumulate(1937, workerData->lastQcyr(),
               0u);
            if (workerData->lastQcyr() > 1950) {
               qc51tdt = workerData->qc.accumulate(1951,
                  workerData->lastQcyr(), 0u);
            }
         }
         if (workerData->getQctottd() != qctdt)
            workerData->setQctd(qctdt);
         if (workerData->getQctot51td() != qc51tdt)
            workerData->setQc51td(qc51tdt);
      }
      if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
         piacal->pebsOabCal();
         pebsOut->pebsWorkerInfo.prepareStrings();
      }
      else {
         pPiaOut->summary1Page.prepareStrings();
      }
      UpdateAllViews(NULL);
    }
  } catch (PiaException& e) {
    ostringstream strm;
    strm << "Caught PiaException " << e.getNumber();
    AfxMessageBox(CString(strm.str().c_str()));
  }
}

/// <summary>Handle Computation Year menu choice.</summary>
void CAnypia32Doc::OnSetupComputationyear()
{
   BaseyearDialog dlg;

   dlg.baseyear = baseyear;
   dlg.m_ilastyear = awbidat->getLastYear();
   dlg.setdata();
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      if (baseyear->getYear() != dlg.m_baseyear || dlg.m_resetCompYear == true) {
         piaparms->setIstart(dlg.m_baseyear);
         piaparms->setData(*awbidat);
         piaparms->setHistFqinc();
         userAssumptions->zeroJalt();
         baseyear->setYear(dlg.m_baseyear);
         baseyearIni->setYear(dlg.m_baseyear);
         baseyearIni->write();
         userAssumptions->setIstart(dlg.m_baseyear);
         assumptions->setIstart(dlg.m_baseyear);
         piacal->calculate1(*assumptions);
         if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
            workerData->setPebsEarn(UserAssumptions::getIstart());
         }
         valid = FALSE;
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Field Office Info menu choice.</summary>
void CAnypia32Doc::OnSetupFieldofficeinfo()
{
   //FoinfoDialog dlg;

   //dlg.m_foname = CString(foinfo -> getFieldOfficeName().c_str());
   //dlg.m_fotitle = CString(foinfo -> getFieldOfficeTitle().c_str());
   //dlg.m_foaddr1 = CString(foinfo -> getAddress(0).c_str());
   //dlg.m_foaddr2 = CString(foinfo -> getAddress(1).c_str());
   //dlg.m_foaddr3 = CString(foinfo -> getAddress(2).c_str());
   //dlg.m_foaddr4 = CString(foinfo -> getAddress(3).c_str());
   //int ret = (int)dlg.DoModal();
   //if (ret == IDOK) {
   //   if (CString(foinfo->getFieldOfficeName().c_str()) != dlg.m_foname) {
   //      foinfo->setFieldOfficeName(string((const char *)dlg.m_foname));
   //      foinfoIni->setFieldOfficeName(string((const char *)dlg.m_foname));
   //      foinfoIni->savename = TRUE;
   //   }
   //   else
   //      foinfoIni->savename = FALSE;
   //   if (CString(foinfo->getFieldOfficeTitle().c_str()) != dlg.m_fotitle) {
   //      foinfo->setFieldOfficeTitle(string((const char *)dlg.m_fotitle));
   //      foinfoIni->setFieldOfficeTitle(string((const char *)dlg.m_fotitle));
   //      foinfoIni->savetitle = TRUE;
   //   }
   //   else
   //      foinfoIni -> savetitle = FALSE;
   //   if (CString(foinfo->getAddress(0).c_str()) != dlg.m_foaddr1) {
   //      foinfo->setAddress(0, string((const char *)dlg.m_foaddr1));
   //      foinfoIni->setAddress(0, string((const char *)dlg.m_foaddr1));
   //      foinfoIni->saveaddress1 = TRUE;
   //      }
   //   else
   //      foinfoIni->saveaddress1 = FALSE;
   //   if (CString(foinfo->getAddress(1).c_str()) != dlg.m_foaddr2) {
   //      foinfo -> setAddress(1, string((const char *)dlg.m_foaddr2));
   //      foinfoIni->setAddress(1, string((const char *)dlg.m_foaddr2));
   //      foinfoIni->saveaddress2 = TRUE;
   //      }
   //   else
   //      foinfoIni->saveaddress2 = FALSE;
   //   if (CString(foinfo->getAddress(2).c_str()) != dlg.m_foaddr3) {
   //      foinfo->setAddress(2, string((const char *)dlg.m_foaddr3));
   //      foinfoIni->setAddress(2, string((const char *)dlg.m_foaddr3));
   //      foinfoIni->saveaddress3 = TRUE;
   //      }
   //   else
   //      foinfoIni->saveaddress3 = FALSE;
   //   if (CString(foinfo->getAddress(3).c_str()) != dlg.m_foaddr4) {
   //      foinfo->setAddress(3, string((const char *)dlg.m_foaddr4));
   //      foinfoIni->setAddress(3, string((const char *)dlg.m_foaddr4));
   //      foinfoIni->saveaddress4 = TRUE;
   //   }
   //   else
   //      foinfoIni->saveaddress4 = FALSE;
   //   foinfoIni->write();
   //   UpdateAllViews(NULL);
   //}
}

/// <summary>Handle Stored Average Wage Increases Set 1 menu choice.</summary>
void CAnypia32Doc::OnSetupAveragewageincreasesSet1()
{
   AwsetDialog dlg;

   dlg.m_ialt = 1;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Stored Average Wage Increases Set 2 menu choice.</summary>
void CAnypia32Doc::OnSetupAveragewageincreasesSet2() 
{
   AwsetDialog dlg;

   dlg.m_ialt = 2;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Stored Average Wage Increases Set 3 menu choice.</summary>
void CAnypia32Doc::OnSetupAveragewageincreasesSet3() 
{
   AwsetDialog dlg;

   dlg.m_ialt = 3;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Stored Average Wage Increases Set 4 menu choice.</summary>
void CAnypia32Doc::OnSetupAveragewageincreasesSet4() 
{
   AwsetDialog dlg;

   dlg.m_ialt = 4;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Stored Benefit Increases Set 1 menu choice.</summary>
void CAnypia32Doc::OnSetupBenefitincreasesSet1()
{
   try {
      BisetDialog dlg;

      dlg.m_ialt = 1;
      setdata(dlg);
      int ret = (int)dlg.DoModal();
      if (ret == IDOK) {
         savedata(dlg);
         UpdateAllViews(NULL);
      }
   } catch (exception&) {
      AfxMessageBox("Exception in OnSetupBenefitincreasesSet1");
   }
}

/// <summary>Handle Stored Benefit Increases Set 2 menu choice.</summary>
void CAnypia32Doc::OnSetupBenefitincreasesSet2()
{
   try {
      BisetDialog dlg;

      dlg.m_ialt = 2;
      setdata(dlg);
      int ret = (int)dlg.DoModal();
      if (ret == IDOK) {
         savedata(dlg);
         UpdateAllViews(NULL);
      }
   } catch (exception&) {
      AfxMessageBox("Exception in OnSetupBenefitincreasesSet2");
   }
}

/// <summary>Handle Stored Benefit Increases Set 3 menu choice.</summary>
void CAnypia32Doc::OnSetupBenefitincreasesSet3()
{
   try {
      BisetDialog dlg;

      dlg.m_ialt = 3;
      setdata(dlg);
      int ret = (int)dlg.DoModal();
      if (ret == IDOK) {
         savedata(dlg);
         UpdateAllViews(NULL);
      }
   } catch (exception&) {
      AfxMessageBox("Exception in OnSetupBenefitincreasesSet3");
   }
}

/// <summary>Handle Stored Benefit Increases Set 4 menu choice.</summary>
void CAnypia32Doc::OnSetupBenefitincreasesSet4()
{
   try {
      BisetDialog dlg;

      dlg.m_ialt = 4;
      setdata(dlg);
      int ret = (int)dlg.DoModal();
      if (ret == IDOK) {
         savedata(dlg);
         UpdateAllViews(NULL);
      }
   } catch (exception&) {
      AfxMessageBox("Exception in OnSetupBenefitincreasesSet4");
   }
}

/// <summary>Handle Stored Catch-up Increases Set 1 menu choice.</summary>
void CAnypia32Doc::OnSetupCatchupincreasesSet1()
{
   CusetDialog dlg;

   dlg.m_ialt = 1;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Stored Catch-up Increases Set 2 menu choice.</summary>
void CAnypia32Doc::OnSetupCatchupincreasesSet2()
{
   CusetDialog dlg;

   dlg.m_ialt = 2;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Stored Catch-up Increases Set 3 menu choice.</summary>
void CAnypia32Doc::OnSetupCatchupincreasesSet3()
{
   CusetDialog dlg;

   dlg.m_ialt = 3;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Stored Catch-up Increases Set 4 menu choice.</summary>
void CAnypia32Doc::OnSetupCatchupincreasesSet4()
{
   CusetDialog dlg;

   dlg.m_ialt = 4;
   setdata(dlg);
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      savedata(dlg);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Historical Amounts Modify menu choice.</summary>
void CAnypia32Doc::OnSetupHistoricalamountsModify()
{
   HistAmtModifyDialog dlg;

   dlg.m_istartyear = baseyearStored + 1;
   dlg.m_ilastyear = awbidat->getLastYear();
   for (int i = dlg.m_istartyear; i <= dlg.m_ilastyear; i++) {
      dlg.m_DAwb[i] = awbidatIni->baseOasdi[i];
      dlg.m_DAwbold[i] = awbidatIni->base77[i];
      dlg.m_DAaw[i-2] = awbidatIni->fq[i-2];
      dlg.m_FAbi[i-1] = awbidatIni->cpiinc[i-1];
   }
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int i = dlg.m_istartyear; i <= dlg.m_ilastyear; i++) {
         awbidatIni->setLastYear(i);
         awbidatIni->baseOasdi[i] = dlg.m_DAwb[i];
         awbidatIni->base77[i] = dlg.m_DAwbold[i];
         awbidatIni->fq[i - 2] = dlg.m_DAaw[i - 2];
         awbidatIni->cpiinc[i - 1] = dlg.m_FAbi[i - 1];
         awbidatIni->write();
      }
      valid = FALSE;
      SetModifiedFlag(TRUE);
      UpdateAllViews(NULL);
   }
}

/// <summary>Handle Historical Amounts Review menu choice.</summary>
void CAnypia32Doc::OnSetupHistoricalamountsReview() 
{
   HistAmtReviewDialog dlg;

   dlg.m_istartyear = 1979;
   dlg.m_ilastyear = awbidat->getLastYear();
   for (int i = dlg.m_istartyear; i <= dlg.m_ilastyear; i++) {
      dlg.m_wb[i] = piaparms->getBaseOasdi(i);
      dlg.m_wbold[i] = piaparms->getBase77(i);
      dlg.m_fq[i-2] = piaparms->getFq(i-2);
      dlg.m_bi[i-1] = piaparms->getCpiinc(i-1);
   }
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      return;
   }
}

/// <summary>Handle Historical Amounts Update menu choice.</summary>
void CAnypia32Doc::OnSetupHistoricalamountsUpdate() 
{
   HistAmtUpdateDialog dlg;
   CString stemp;  // temporary string

   dlg.m_year = awbidat->getLastYear() + 1;
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      awbidat->setLastYear(dlg.m_year);
      awbidat->cpiinc[dlg.m_year - 1] = dlg.m_bi;
      awbidat->fq[dlg.m_year - 2] = dlg.m_aw;
      awbidat->baseOasdi[dlg.m_year] = dlg.m_wb;
      awbidat->base77[dlg.m_year] = dlg.m_wbold;
      awbidat->baseHi[dlg.m_year] = dlg.m_wbhi;
      awbidatIni->setLastYear(dlg.m_year);
      awbidatIni->cpiinc[dlg.m_year - 1] = dlg.m_bi;
      awbidatIni->fq[dlg.m_year - 2] = dlg.m_aw;
      awbidatIni->baseOasdi[dlg.m_year] = dlg.m_wb;
      awbidatIni->base77[dlg.m_year] = dlg.m_wbold;
      awbidatIni->baseHi[dlg.m_year] = dlg.m_wbhi;
      awbidatIni->write();
      valid = FALSE;
      SetModifiedFlag(TRUE);
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Historical Amounts Modify menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateSetupHistoricalamountsModify( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(awbidat->getLastYear() > baseyearStored);
}

/// <summary>Sets data in stored benefit increases dialog box.</summary>
//
// Arguments:
//   dlg: Stored benefit increases dialog box.
void CAnypia32Doc::setdata( BisetDialog& dlg )
{
   try {
      dlg.biprojIni = biprojIni;
      dlg.assumptions = assumptions;
      dlg.userAssumptions = userAssumptions;
      dlg.setdata();
   } catch (exception&) {
      AfxMessageBox("Exception in CAnypia32Doc::setdata(BisetDialog)");
   }
   try {
      dlg.m_cachup = assumptions->catchupDoc.allownonzero[dlg.m_ialt - 1];
   } catch (exception&) {
      AfxMessageBox("Exception setting dlg.m_cachup");
   }
}

/// <summary>Saves data in stored benefit increases dialog box.</summary>
//
// Arguments:
//   dlg: Stored benefit increases dialog box.
void CAnypia32Doc::savedata( BisetDialog& dlg )
{
   bool need_update = false;

   for (int i = UserAssumptions::getIstart();
      i <= UserAssumptions::getIstart() + BiprojNonFile::NUMPROJYEARS; i++) {
      if (dlg.m_biproj[i] != assumptions->biProj.theData[i])
         need_update = true;
   }
   if (dlg.m_biprojtitle != CString(assumptions->getBenefitInc(dlg.m_ialt).c_str())) {
      need_update = true;
   }
   if (need_update) {
      assumptions->biProj.setData(dlg.m_ialt, dlg.m_biproj);
      biprojIni->setFirstYear(baseyear->getYear());
      biprojIni->setData(dlg.m_ialt, dlg.m_biproj);
      assumptions->biProj.setTitle(dlg.m_ialt,
         string((const char *)dlg.m_biprojtitle));
      biprojIni->setTitle(dlg.m_ialt,
         string((const char *)dlg.m_biprojtitle));
      biprojIni->write(dlg.m_ialt);
      userAssumptions->zeroJalt();
      valid = FALSE;
      SetModifiedFlag(TRUE);
   }
   bool btemp = (dlg.m_cachup == TRUE);
   if (assumptions->catchupDoc.allownonzero[dlg.m_ialt - 1] != btemp) {
      assumptions->catchupDoc.allownonzero[dlg.m_ialt - 1] = btemp;
      assumptions->catchupDoc.catchup.deleteContents();
      if (assumptions->catchupDoc.allownonzero[dlg.m_ialt - 1] == false) {
         cachupIni->setData(dlg.m_ialt, assumptions->catchupDoc.catchup);
         cachupIni->clear();
      }
   }
}

/// <summary>Sets data in stored average wage increases dialog box.</summary>
//
// Arguments:
//   dlg: Stored average wage increases dialog box.
void CAnypia32Doc::setdata( AwsetDialog& dlg )
{
   try {
      dlg.awincIni = awincIni;
      dlg.assumptions = assumptions;
      dlg.userAssumptions = userAssumptions;
      dlg.setdata();
   } catch (exception&) {
      AfxMessageBox("Exception in CAnypia32Doc::setdata(AwsetDialog)");
   }
}

/// <summary>Saves data in stored average wage increases dialog box.</summary>
//
// Arguments:
//   dlg: Stored average wage increases dialog box.
void CAnypia32Doc::savedata( AwsetDialog& dlg )
{
   bool need_update = false;
    
   for (int i = UserAssumptions::getIstart() - 1;
      i <= UserAssumptions::getIstart() + 15; i++) {
      if (dlg.m_awproj[i] != assumptions->awincProj.awinc[i])
         need_update = true;
   }
   if (dlg.m_awprojtitle != CString(
         assumptions->getAverageWage(dlg.m_ialt).c_str())) {
      need_update = true;
   }
   if (need_update) {
      assumptions->awincProj.setData(dlg.m_ialt, dlg.m_awproj);
      awincIni->setFirstYear(baseyear->getYear() - 1);
      awincIni->setData(dlg.m_ialt, dlg.m_awproj);
      assumptions->awincProj.setTitle(dlg.m_ialt,
         string((const char *)dlg.m_awprojtitle));
      awincIni->setTitle(dlg.m_ialt, string((const char *)dlg.m_awprojtitle));
      awincIni->write(dlg.m_ialt);
      userAssumptions->zeroJalt();
      valid = FALSE;
      SetModifiedFlag(TRUE);
   }
}

/// <summary>Sets data in stored catch-up benefit increases dialog box.</summary>
//
// Arguments:
//   dlg: Stored catch-up benefit increases dialog box.
void CAnypia32Doc::setdata( CusetDialog& dlg )
{
   try {
      dlg.assumptions = assumptions;
      dlg.cachupIni = cachupIni;
      dlg.setdata();
   } catch (exception&) {
      AfxMessageBox("Exception in CAnypia32Doc::setdata(CusetDialog)");
   }
}

/// <summary>Saves data in stored benefit increases dialog box.</summary>
//
// Arguments:
//   dlg: Stored catch-up benefit increases dialog box.
void CAnypia32Doc::savedata( CusetDialog& dlg )
{
   bool need_update = false;
    
   for (int i = dlg.m_cachup.getCstart(); i < dlg.m_cachup.getCstart() + 15;
   i++) {
      for (int j = dlg.m_cachup.getCstart() + 2;
      j < dlg.m_cachup.getCstart() + 15; j++) {
         if (dlg.m_cachup.get(i, j) !=
            assumptions->catchupDoc.catchup.get(i, j))
            need_update = true;
      }
   }
   if (need_update) {
      cachupIni->setData(dlg.m_ialt, dlg.m_cachup);
      assumptions->catchupDoc.setData(dlg.m_ialt, dlg.m_cachup);
      cachupIni->write(dlg.m_ialt);
      valid = FALSE;
      SetModifiedFlag(TRUE);
   }
}

/// <summary>Update Catch-up Increases Set 1 menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateSetupCatchupincreasesSet1( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(assumptions->catchupDoc.allownonzero[0]);
}

/// <summary>Update Catch-up Increases Set 2 menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateSetupCatchupincreasesSet2( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(assumptions->catchupDoc.allownonzero[1]);
}

/// <summary>Update Catch-up Increases Set 3 menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateSetupCatchupincreasesSet3( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(assumptions->catchupDoc.allownonzero[2]);
}

/// <summary>Update Catch-up Increases Set 4 menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateSetupCatchupincreasesSet4( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(assumptions->catchupDoc.allownonzero[3]);
}

/// <summary>Handle Military Service menu choice.</summary>
void CAnypia32Doc::OnDialogsMilitaryservice()
{
   Milserv dlg;
    
   dlg.m_mscount = workerData->milServDatesVec.getMSCount();
   dlg.m_startdate1 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[0].startDate, "s").c_str());
   dlg.m_enddate1 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[0].endDate, "s").c_str());
   dlg.m_startdate2 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[1].startDate, "s").c_str());
   dlg.m_enddate2 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[1].endDate, "s").c_str());
   dlg.m_startdate3 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[2].startDate, "s").c_str());
   dlg.m_enddate3 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[2].endDate, "s").c_str());
   dlg.m_startdate4 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[3].startDate, "s").c_str());
   dlg.m_enddate4 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[3].endDate, "s").c_str());
   dlg.m_startdate5 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[4].startDate, "s").c_str());
   dlg.m_enddate5 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[4].endDate, "s").c_str());
   dlg.m_startdate6 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[5].startDate, "s").c_str());
   dlg.m_enddate6 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[5].endDate, "s").c_str());
   dlg.m_startdate7 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[6].startDate, "s").c_str());
   dlg.m_enddate7 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[6].endDate, "s").c_str());
   dlg.m_startdate8 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[7].startDate, "s").c_str());
   dlg.m_enddate8 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[7].endDate, "s").c_str());
   dlg.m_startdate9 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[8].startDate, "s").c_str());
   dlg.m_enddate9 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[8].endDate, "s").c_str());
   dlg.m_startdate10 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[9].startDate, "s").c_str());
   dlg.m_enddate10 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[9].endDate, "s").c_str());
   dlg.m_startdate11 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[10].startDate, "s").c_str());
   dlg.m_enddate11 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[10].endDate, "s").c_str());
   dlg.m_startdate12 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[11].startDate, "s").c_str());
   dlg.m_enddate12 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[11].endDate, "s").c_str());
   dlg.m_startdate13 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[12].startDate, "s").c_str());
   dlg.m_enddate13 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[12].endDate, "s").c_str());
   dlg.m_startdate14 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[13].startDate, "s").c_str());
   dlg.m_enddate14 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[13].endDate, "s").c_str());
   dlg.m_startdate15 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[14].startDate, "s").c_str());
   dlg.m_enddate15 = CString(DateFormatter::toString(
      workerData->milServDatesVec.msdates[14].endDate, "s").c_str());
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int i = 0; i < dlg.m_mscount; i++) {
         if (workerData->milServDatesVec.msdates[i].startDate !=
            dlg.msdates[i].startDate) {
            workerData->milServDatesVec.msdates[i].startDate =
               dlg.msdates[i].startDate;
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
         if (workerData->milServDatesVec.msdates[i].endDate !=
            dlg.msdates[i].endDate) {
            workerData->milServDatesVec.msdates[i].endDate =
               dlg.msdates[i].endDate;
            valid = FALSE;
            SetModifiedFlag(TRUE);
         }
      }
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Military Service menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsMilitaryservice( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(workerData->milServDatesVec.getMSCount() > 0);
}

/// <summary>Update Annual Earnings Info menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateDialogsAnnualearningsinfo( CCmdUI* pCmdUI )
{
   if (workerData->getIbegin() > 0) {
     pCmdUI->Enable(workerData->getEarnEnable());
   } else {
     pCmdUI->Enable(false);
   }
}

/// <summary>Set the report margins and font.</summary>
//
// Remarks: Called on File/Page Setup menu choice.
void CAnypia32Doc::OnFilePageSetup() 
{
   ConfigDialog dlg;

   configIni->saveScreenPoints = false;
   dlg.longOutput = config->getLongOutput();
   dlg.m_topmargin = config->getTopMargin();
   dlg.m_leftmargin = config->getLeftMargin();
   dlg.m_PrinterPoints = config->getPrinterPoints();
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      bool btemp = (dlg.longOutput == TRUE);
      if (config->getLongOutput() != btemp) {
         config->setLongOutput(btemp);
         configIni->setLongOutput(btemp);
         configIni->saveLongOutput = true;
      }
      else
         configIni->saveLongOutput = false;
      if (config->getTopMargin() != dlg.m_topmargin) {
         config->setTopMargin(dlg.m_topmargin);
         configIni->setTopMargin(dlg.m_topmargin);
         configIni->saveTopMargin = true;
      }
      else
         configIni->saveTopMargin = false;
      if (config->getLeftMargin() != dlg.m_leftmargin) {
         config->setLeftMargin(dlg.m_leftmargin);
         configIni->setLeftMargin(dlg.m_leftmargin);
         configIni->saveLeftMargin = true;
      }
      else
         configIni->saveLeftMargin = false;
      if (config->getPrinterPoints() != dlg.m_PrinterPoints) {
         config->setPrinterPoints(dlg.m_PrinterPoints);
         configIni->setPrinterPoints(dlg.m_PrinterPoints);
         configIni->savePrinterPoints = true;
      }
      else
         configIni->savePrinterPoints = false;
      configIni->write();
      UpdateAllViews(NULL);
   }
}

/// <summary>Set the screen font size.</summary>
//
// Remarks: Called on View/Font menu choice.
void CAnypia32Doc::OnViewScreenSettings() 
{
   ScreenDialog dlg;

   configIni->savePrinterPoints = false;
   configIni->saveTopMargin = false;
   configIni->saveLeftMargin = false;
   configIni->saveLongOutput = false;
   dlg.m_ScreenPoints = config->getScreenPoints();
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      if (config->getScreenPoints() != dlg.m_ScreenPoints) {
         config->setScreenPoints(dlg.m_ScreenPoints);
         configIni->setScreenPoints(dlg.m_ScreenPoints);
         configIni->saveScreenPoints = true;
      }
      else
         configIni->saveScreenPoints = false;
      configIni->write();
      UpdateAllViews(NULL);
   }
}

/// <summary>Calculate an estimate.</summary>
//
// Remarks: Called on File/Calculate Estimate menu choice.
void CAnypia32Doc::OnFileRun() 
{
   try {
      // find the date of entitlement to use to calculate the pia
      const DateMoyr entDate =
         (workerData->getJoasdi() == WorkerDataGeneral::SURVIVOR) ?
         secondaryArray->secondary[0]->entDate :
         workerData->getEntDate();
      // check primary data and set primary factors
      piacal->dataCheck(entDate);
      // check auxiliary data and set auxiliary factors
      piacal->dataCheckAux(*widowDataArray, *widowArray, *secondaryArray);
      // set assumptions
      piacal->calculate1(*assumptions);
      // compute regular pias and primary benefit
      piacal->calculate2(entDate);
      // compute any re-indexed widow(er) pias
      piacal->reindWidCalAll(*widowDataArray, *widowArray, *secondaryArray);
      // compute secondary benefits
      piacal->piaCal3(*widowArray, *secondaryArray);
      taxrates->taxCalAllYears(piadata->earnOasdiLimited,
         workerData->getTaxTypeArray(), taxes->taxesOasi, TaxRates::OASITF);
      taxrates->taxCalAllYears(piadata->earnOasdiLimited,
         workerData->getTaxTypeArray(), taxes->taxesDi, TaxRates::DITF);
      taxrates->taxCalAllYears(piadata->earnHiLimited,
         workerData->getTaxTypeArray(), taxes->taxesHi, TaxRates::HITF);
      taxes->oasdhiTaxCal();
      taxes->totalTaxCal();
      if (workerData->getJoasdi() == WorkerData::PEBS_CALC) {
         pebsOut->setPageNum();
         pebsOut->prepareStrings();
      }
      else {
         pPiaOut->setPageNum(*piacal);
         pPiaOut->prepareStrings();
      }
   } catch (PiaException& e) {
      AfxMessageBox(e.getNumber());
      return;
   }
   if (piadata->getFinsCode2() == '6') { 
      AfxMessageBox("Warning! You have selected a totalization benefit even though you do not have the required 6 qcs for it. The benefit estimate shown is hypothetical only.");
   } else {
      if (piadata->getFinsCode2() == '7' && 
         !(piadata->disInsCode == DisInsCode::TOTALIZED && 
           workerData->getJoasdi() == WorkerData::DISABILITY)) {
         AfxMessageBox("Warning! You have selected a totalization benefit even though you are insured for regular benefits. The benefit estimate shown is hypothetical only.");
      }
   }
   valid = TRUE;
   UpdateAllViews(NULL);
}

/// <summary>Menu choice to clear all historical amounts from Registry.
/// </summary>
void CAnypia32Doc::OnSetupHistoricalamountsClear()
{
   HistAmtClearDialog dlg;

   dlg.m_istartyear = baseyearStored + 1;
   dlg.m_ilastyear = awbidat->getLastYear();
   int ret = (int)dlg.DoModal();
   if (ret == IDOK) {
      for (int i = dlg.m_istartyear; i <= dlg.m_ilastyear; i++) {
         awbidatIni->setLastYear(i);
         awbidatIni->clear();
      }
      awbidat->setLastYear(baseyearStored);
      baseyear->setYear(baseyearStored);
      baseyearIni->clear();
      UpdateAllViews(NULL);
   }
}

/// <summary>Update Historical Amounts Clear menu choice.</summary>
//
// Arguments:
//   pCmdUI: Menu item to update.
void CAnypia32Doc::OnUpdateSetupHistoricalamountsClear( CCmdUI* pCmdUI )
{
   pCmdUI->Enable(awbidat->getLastYear() > baseyearStored);
}
