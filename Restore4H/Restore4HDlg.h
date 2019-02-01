
// Restore4HDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CRestore4HDlg dialog
class CRestore4HDlg : public CDialogEx
{
// Construction
public:
	CRestore4HDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESTORE4H_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox DriveList;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnLbnSelchangeList2();
	// The pattern text you want to find in the disk
	CEdit StrInput;
	afx_msg void OnBnClickedRadio1();
	int PlainButton;
	// List of possible results
	CListBox OutputList;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	CEdit ProcessingBytes;
	// List of possible results
	CListBox ScanResultList;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CEdit StartPosition;
	CEdit EndPosition;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	// Choose option hex for input
	int HexInput;
};
