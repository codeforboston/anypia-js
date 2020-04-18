// $Id: DeathDialog.h 1.7.1.1 2012/03/08 06:55:01EST 277133 Development 277133(2012/03/08 06:55:46EST) $
//
// Header file for dialog to ask for information about family members.

#if !defined(AFX_DEATHDIALOG_H__3F423312_30E9_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_DEATHDIALOG_H__3F423312_30E9_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "pia.h"
#include "PiadataArray.h"

// {group:Anypia Classes}
// Description: The dialog that asks for information about family members.
//
// Remarks: The dialog that asks for information about family members.
class DeathDialog : public CDialog
{
public:
   DeathDialog(CWnd* pParent = NULL);
   void auxiliaryOK();
   void survivorOK();
// Dialog Data
	//{{AFX_DATA(DeathDialog)
	enum { IDD = IDD_DEATH };
	CString	m_jbirth;
	CString	m_jonset;
	CString	m_jent;
	int		m_lifetype;
	int		m_survivortype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DeathDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

public:
   // Description: Date of birth for each family member.
   boost::gregorian::date m_jbirthtemp[PiaDataArray::MAXFAMSIZE];
   // Description: Date of disability onset for each family member.
   boost::gregorian::date m_jonsettemp[PiaDataArray::MAXFAMSIZE];
   // Description: Major bic code for each family member.
   char m_isurv[PiaDataArray::MAXFAMSIZE];
   // Description: Minor bic code for each family member.
   //
   // Remarks: '2' if young spouse, '6' if divorced spouse, //   ' ' otherwise.
   char m_young[PiaDataArray::MAXFAMSIZE];
   // Description: Date of entitlement for each family member.
   DateMoyr m_jenttemp[PiaDataArray::MAXFAMSIZE];
   // Description: Type of benefit.
   WorkerData::ben_type m_ioasdi;
   // Description: Family member currently being worked on (0-9).
   int m_fammem;
   // Description: Size of family (1-10).
   int m_famsize;
   bool check();
   void setupdata();

protected:

	// Generated message map functions
	//{{AFX_MSG(DeathDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnAgedWid();
	afx_msg void OnDisabWid();
	afx_msg void OnMother();
	afx_msg void OnChildSurv();
	afx_msg void OnAgedspouse();
	afx_msg void OnChildLife();
	afx_msg void OnYoungspouse();
	afx_msg void OnPrevbenie();
	afx_msg void OnNextbenie();
	afx_msg void OnDivAgedWid();
	afx_msg void OnDivAgedspouse();
	afx_msg void OnDivDisabWid();
	afx_msg void OnFamilyHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEATHDIALOG_H__3F423312_30E9_11D1_B873_00A0249F5E63__INCLUDED_)
