// $Id: anypiadoc.h 1.19.1.2 2012/03/12 14:21:17EDT 277133 Development  $
//
// Interface of the CAnypia32Doc class.

#include "pia.h"
#include "config.h"
#include "piaout/PiaOut.h"
#include "piaout/PebsOut.h"
#include "outdc.h"
#include "BaseyearIni.h"
#include "FoinfoIni.h"
#include "AwbidatIni.h"
#include "AwincIni.h"
#include "BiprojIni.h"
#include "CachupIni.h"
#include "ConfigIni.h"
#include "BisetDialog.h"
#include "AwsetDialog.h"
#include "CusetDialog.h"
#if defined(DEBUGCASE)
#include "StrmoutLog.h"
#endif
class TaxRates;
class PiaParamsAny;
class BaseYearNonFile;
class FieldOfficeInfoNonFile;
class PiaReadAny;
class PiaWriteAny;

#if !defined(AFX_ANYPIA32DOC_H__560E66FA_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_ANYPIA32DOC_H__560E66FA_2E0D_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef PiaData * Piadataptr;
typedef Secondary * Secondaryptr;

// Description: The document class for the Anypia32 benefit
// calculation program.
class CAnypia32Doc : public CDocument
{
protected:
   CAnypia32Doc();
   DECLARE_DYNCREATE(CAnypia32Doc)

public:
   // Description: Basic worker data.
   WorkerData* workerData;
   // Description: Pia calculation data.
   PiaData* piadata;
   // Description: Widow and other family members' basic data.
   WorkerDataArray* widowDataArray;
   // Description: Widow and other family members' calculation data.
   PiaDataArray* widowArray;
   // Description: Secondary benefits.
   SecondaryArray* secondaryArray;
   // Description: Historical average wages and benefit increases.
   AwbiData* awbidat;
   // Description: Projected average wage and benefit increases.
   AssumptionsNonFile* assumptions;
   // Description: User assumptions.
   UserAssumptions* userAssumptions;
   // Description: Benefit calculation parameters.
   PiaParamsAny* piaparms;
   // Description: Configuration.
   Config* config;
   // Description: Computation year.
   BaseYearNonFile* baseyear;
   // Description: Benefit calculation functions.
   PiaCalAny* piacal;
   // Description: Taxes paid.
   TaxData* taxes;
   // Description: Tax rates.
   TaxRates* taxrates;
   // Description: Law change parameters.
   LawChangeArray* lawChange;
   // Description: Statement information.
   Pebs* pebs;
   // Description: Field office information.
   FieldOfficeInfoNonFile* foinfo;
   // Description: Non-Statement output.
   PiaOut* pPiaOut;
   // Description: Read case from disk.
   PiaReadAny* piaread;
   // Description: Write case to disk.
   PiaWriteAny* piawrite;
   // Description: Statement output.
   PebsOut* pebsOut;
   // Description: Computation year stored in the Registry.
   BaseYearIni* baseyearIni;
   // Description: Field office information stored in the Registry.
   FieldOfficeInfoIni* foinfoIni;
   // Description: Historical amounts stored in the Registry.
   AwbiDataIni* awbidatIni;
   // Description: Average wage increases stored in the Registry.
   AwincIni* awincIni;
   // Description: Benefit increases stored in the Registry.
   BiprojIni* biprojIni;
   // Description: Catch-up increases stored in the Registry.
   CatchupIni* cachupIni;
   // Description: Configuration stored in the Registry.
   ConfigIni* configIni;
   // Description: Projected earnings data.
   EarnProject* earnProject;
#if defined(DEBUGCASE)
   StrmoutLog outlog;
#endif

private:
   // Description: True if calculated results are valid.
   bool valid;
   void setdata(BisetDialog& dlg);
   void savedata(BisetDialog& dlg);
   void setdata(AwsetDialog& dlg);
   void savedata(AwsetDialog& dlg);
   void setdata(CusetDialog& dlg);
   void savedata(CusetDialog& dlg);
   // Description: Computation year stored in source libraries.
   int  baseyearStored;
   // Description: True if any pre-1951 railroad earnings.
   bool hasrr3750;

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnypia32Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CAnypia32Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
   bool isValid();
   BOOL OnOpenDocument( const char* pszPathName );
   BOOL OnSaveDocument( const char* pszPathName );
   void DeleteContents();
   int AssumptionTypeToDialog( int assumtype );
   int DialogToAssumptionType( int dialog );

// Generated message map functions (protected)
protected:
	//{{AFX_MSG(CAnypia32Doc)
	afx_msg void OnDialogsPebesinfo();
	afx_msg void OnUpdateDialogsPebesinfo(CCmdUI* pCmdUI);
	afx_msg void OnDialogsNonpebesinfo();
	afx_msg void OnDialogsWorkerinfo();
	afx_msg void OnDialogsDisabilityinfo();
	afx_msg void OnUpdateDialogsDisabilityinfo(CCmdUI* pCmdUI);
	afx_msg void OnDialogsSurvivorinfo();
	afx_msg void OnUpdateDialogsSurvivorinfo(CCmdUI* pCmdUI);
	afx_msg void OnDialogsSummaryqcs();
	afx_msg void OnUpdateDialogsSummaryqcs(CCmdUI* pCmdUI);
	afx_msg void OnDialogsAssumptions();
	afx_msg void OnDialogsBenefitincreases();
	afx_msg void OnUpdateDialogsBenefitincreases(CCmdUI* pCmdUI);
	afx_msg void OnDialogsAveragewageincreases();
	afx_msg void OnDialogsCatchupincreases();
	afx_msg void OnUpdateDialogsCatchupincreases(CCmdUI* pCmdUI);
	afx_msg void OnDialogsWagebases();
	afx_msg void OnUpdateDialogsWagebases(CCmdUI* pCmdUI);
	afx_msg void OnDialogsAnnualearningsinfo();
	afx_msg void OnUpdateDialogsAssumptions(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDialogsAveragewageincreases(CCmdUI* pCmdUI);
	afx_msg void OnSetupComputationyear();
	afx_msg void OnSetupFieldofficeinfo();
	afx_msg void OnSetupAveragewageincreasesSet1();
	afx_msg void OnSetupAveragewageincreasesSet2();
	afx_msg void OnSetupAveragewageincreasesSet3();
	afx_msg void OnSetupAveragewageincreasesSet4();
	afx_msg void OnSetupBenefitincreasesSet1();
	afx_msg void OnSetupBenefitincreasesSet2();
	afx_msg void OnSetupBenefitincreasesSet3();
	afx_msg void OnSetupBenefitincreasesSet4();
	afx_msg void OnSetupCatchupincreasesSet1();
	afx_msg void OnSetupCatchupincreasesSet2();
	afx_msg void OnSetupCatchupincreasesSet3();
	afx_msg void OnSetupCatchupincreasesSet4();
	afx_msg void OnSetupHistoricalamountsModify();
	afx_msg void OnSetupHistoricalamountsReview();
	afx_msg void OnSetupHistoricalamountsUpdate();
	afx_msg void OnUpdateSetupHistoricalamountsModify(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetupCatchupincreasesSet1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetupCatchupincreasesSet2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetupCatchupincreasesSet3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetupCatchupincreasesSet4(CCmdUI* pCmdUI);
	afx_msg void OnDialogsMilitaryservice();
	afx_msg void OnUpdateDialogsMilitaryservice(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDialogsAnnualearningsinfo(CCmdUI* pCmdUI);
	afx_msg void OnFilePageSetup();
	afx_msg void OnViewScreenSettings();
	afx_msg void OnFileRun();
	afx_msg void OnUpdateDialogsNonpebesinfo(CCmdUI* pCmdUI);
	afx_msg void OnSetupHistoricalamountsClear();
	afx_msg void OnUpdateSetupHistoricalamountsClear(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// Description: Returns true if results shown are valid.
//
// Returns: True if results shown are valid.
inline bool CAnypia32Doc::isValid()
   { return(valid); }

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYPIA32DOC_H__560E66FA_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
