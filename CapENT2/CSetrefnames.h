#pragma once


// CSetrefnames ダイアログ

class CSetrefnames : public CDialogEx
{
	DECLARE_DYNAMIC(CSetrefnames)

public:
	CSetrefnames(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CSetrefnames();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETREFNAMES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString m_ref0;
	CString m_ref1;
	CString m_ref2;
	CString m_ref3;
	CString m_ref4;
	CString m_ref5;
//	CEdit m_ref6;
//	CEdit m_ref7;
//	CEdit m_ref8;
//	CEdit m_ref9;
	CString m_ref6;
	CString m_ref7;
	CString m_ref8;
//	CString m_rerf9;
	CString m_ref9;
};
