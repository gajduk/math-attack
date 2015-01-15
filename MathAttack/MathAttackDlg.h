// MathAttackDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMathAttackDlg dialog
class CMathAttackDlg : public CDialog
{
private:
	int x[5];
	int y[5];
	bool postoi[5];
	int broj1[5];
	int broj2[5];
	int operacija[5];
	int rezultat[5];
	int brzina;
	bool izlez;
// Construction
public:
	CMathAttackDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MATHATTACK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_pogodeni;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL m_sobiranje;
	BOOL m_odzemanje;
	BOOL m_mnozenje;
	BOOL m_delenje;
	int vreme;
	afx_msg void OnBnClickedCancel();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void incSpeed();
	afx_msg void decSpeed();
	afx_msg void updateOperations();
	afx_msg void incFreq();
	afx_msg void decFreq();
	afx_msg void start();
	CString m_rez;
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
