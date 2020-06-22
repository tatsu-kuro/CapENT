#pragma once
#include "afxwin.h"


// CGetNewID ダイアログ

class CGetNewID : public CDialogEx
{
	DECLARE_DYNAMIC(CGetNewID)

public:
	CGetNewID(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CGetNewID();

// ダイアログ データ
	enum { IDD = IDD_GETNEWID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedStartcap();
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
	CButton m_ac;
//	CButton m_start;
	CButton m_cancel;
	CButton m_ok;

	CBitmap bmp_button_start;
	CBitmap bmp_button_curplay;
	CBitmap bmp_button_alllist;

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
	CStatic m_id;
//	CStatic m_currentid;
	afx_msg void OnBnClickedButton0();
	int m_IDnum;
	void DispNum(int num);
	afx_msg void OnPaint();
	void DispNum_sub(CStatic *id,int num);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
//	int idw;
//	int idh;
	CButton m_startcap;
	afx_msg void OnBnClickedStartcap();
	CStatic m_hist1;
	CStatic m_hist2;
	CStatic m_hist3;
	CStatic m_hist4;
	CStatic m_hist5;
	CStatic m_hist10;
	CStatic m_hist6;
	CStatic m_hist7;
	CStatic m_hist8;
	CStatic m_hist9;
	int m_hist;
	afx_msg void OnStnClickedHist1();
	afx_msg void OnStnClickedHist2();
	afx_msg void OnStnClickedHist3();
	afx_msg void OnStnClickedHist4();
	afx_msg void OnStnClickedHist5();
	afx_msg void OnStnClickedHist6();
	afx_msg void OnStnClickedHist7();
	afx_msg void OnStnClickedHist8();
	afx_msg void OnStnClickedHist9();
	afx_msg void OnStnClickedHist10();
	afx_msg void OnBnClickedCancel();
	int m_record_setid_find;
	CButton m_find;
	afx_msg void OnBnClickedFind();
};
