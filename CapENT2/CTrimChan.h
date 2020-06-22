#pragma once


// CTrimChan ダイアログ

class CTrimChan : public CDialogEx
{
	DECLARE_DYNAMIC(CTrimChan)

public:
	CTrimChan(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CTrimChan();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIMCHAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString m_frames;
	int m_posa;
	int m_posb;
	char fn1[301];
	char fn2[301];
	int m_newid;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};
