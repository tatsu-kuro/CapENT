#pragma once
#include "afxwin.h"


// CGetID ダイアログ

class CGetID : public CDialogEx
{
	DECLARE_DYNAMIC(CGetID)

public:
	CGetID(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CGetID();

// ダイアログ データ
	enum { IDD = IDD_GETID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedClearnum();
	afx_msg void OnBnClickedAllclearnum();
	virtual BOOL OnInitDialog();
	CButton m_ac;
	CButton m_num0;
	CButton m_num1;
	CButton m_num2;
	CButton m_num3;
	CButton m_num4;
	CButton m_num5;
	CButton m_num6;
	CButton m_num7;
	CButton m_num8;
	CButton m_num9;
	CButton m_c;
	CButton m_cancel;
	CButton m_ok;
	CStatic m_idold;
	CStatic m_id;
	afx_msg void OnPaint();
	void DispNum(int id);
	int oldIDnum;
	int m_IDnum;
	afx_msg void OnBnClickedButton0();
};
