#pragma once


// CTransDLG ダイアログ

class CTransDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CTransDLG)

public:
	CTransDLG(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CTransDLG();
	char title[100],ymd[20];


// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString str1;
	CString str2;
	CString str3;
	CString str4;
	CString str5;
//	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString str0;
//	afx_msg void OnBnClickedCancel();
//	CButton cancelCtrl;
	virtual void OnOK();
	CString str_timer;
	CButton okCtrl;
};
