
// CapENT2Dlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#define CaptMode 0
#define PlayMode 1
#define Disp4Mode 2
#define Disp1Mode 3


// CCapENT2Dlg ダイアログ
class CCapENT2Dlg : public CDialogEx
{
// コンストラクション
public:
	CCapENT2Dlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_CAPENT2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;
	CToolTipCtrl m_tooltip;
	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	
	static UINT CaptureThread(LPVOID pParam);
	void CaptureThread(void);
	CWinThread* m_pCaptureThread;

	static UINT PlayThread(LPVOID pParam);
	void PlayThread(void);
	CWinThread* m_pPlayThread;


//	static UINT ChanThread(LPVOID pParam);
//	void ChanThread(void);
//	CWinThread* m_pChanThread;
	//struct BKUP {
		//int total;
	//	int fit;
	//	int total2;
	//	int fit2;
	//}backup;
	int IDnum;
	int IDnumold;
	int currentframe;
	int capturetime;
	int maxframenum;
	int trimposa,trimposb,sankakuzure;
	bool m_PlayloopEnable;
	bool m_CaploopEnable;
	bool m_PrevloopEnable;
	bool CaptureNowf;
	int KillRecordCnt;
	int KillPreviewCnt;
	CBitmap bmp_button_newid;
	CBitmap bmp_button_start;
	CBitmap bmp_button_trim;
	CBitmap bmp_button_stop;
	CBitmap bmp_button_stopdisp;
	CBitmap bmp_button_delete;
	CBitmap bmp_button_changeid;
	CBitmap bmp_ref;
	CBitmap bmp_backup;

	CBitmap bmp_menu;
	CBitmap bmp_retr;
	CBitmap bmp_stillcap;
	CBitmap bmp_deint;
	CBitmap bmp_deinton;
	CBitmap bmp_record;
	CBitmap bmp_exitbut;
	int lastdayretr;
	bool moviepausef;
	int SetFrame;
	char listaviselected[301];

	void SetCtrlPos();// int x, int y);
	afx_msg void OnDestroy();
	CButton m_ok;
	CButton m_stopcap;
	CStatic m_moviept;
	CButton m_cancel;
	CStatic m_timetrim;
	CButton m_cutmovie;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetButtons(int mode);
	afx_msg void OnBnClickedStopcap();
	int DispOneNum(CStatic *cs, int n, int x);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void DispSlider(int f);
	void DispOneFrame(char* fn, int n);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void PlayMovie(void);
	void DispTimeTrim(void);
	afx_msg void OnBnClickedCutmovie();
	void SetTrimName(char *playcapfn,char *playingfn,int n);
	void Set2refer(int ref);
	void DispRefer(int ref);
	CStatic m_pic0;
	CStatic m_pic1;
	CStatic m_pic2;
	CStatic m_pic3;
	CStatic m_pic4;
	CStatic m_pic5;
	CStatic m_pic6;
	CStatic m_pic7;
	CStatic m_pic8;
	CStatic m_pic9;
	void DispOne10(int n, char* fn);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void SetNewIDPics(int idn, int mode);
	void SetNewIDPics();
	int SetYmdPics(void);
	int SetAllPics(void);
	void PutOne2(char *fn);
	bool OnPaintf;
	CStatic m_picm0;
	CStatic m_picm1;
	CStatic m_picm2;
	CStatic m_picm3;
	CStatic m_picl;
	CStatic m_moview;
	void Disp10Pics(int offset);
	void Disp4Pics(int n);
	void DispOne4(CStatic *dc, char* fn);
	void DispLPic(char* fn);
	afx_msg void OnStnClickedPicl();
	void PlayDispPic(char* fn);
	CStatic m_delpic;
	void DeletePic(int fnn);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void DispDelWaku(void);
	CStatic m_delpicwaku;
	void SetIDsub(int pics);
	void DispNum(CStatic *id,int n1,int n2, int n3);//type, int num,char *txt);
	CStatic m_datacnt;
	void DayRetr(int flag);

	void SetYmd2Pic10(char* ymd);
//	void ChangeID(int fn);
	char chanfn1[301],chanfn2[301];
	int chanid,chanframes,chancurrentframe;
	afx_msg void OnPopupSetid();
	afx_msg void OnPopupDelete();
	afx_msg void OnPopupDatesearch();
	afx_msg void OnPopupCopy();
	afx_msg void OnPopupSetblank();
	afx_msg void OnPopupChangeid();
	void DispNum_sub(CStatic* waku, int id);
	afx_msg void OnPopupPrt2();
	afx_msg void OnPopupPrt4();
	afx_msg void OnPopupPrt2u();

	CButton m_stopdisp;
	afx_msg void OnBnClickedStopdisp();
	CStatic m_picmax;
	afx_msg void OnPopupRotate2();
	afx_msg void OnPopupRotate3();
	afx_msg void OnPopupSetbackup();
	afx_msg void OnPopupBackup();

	afx_msg void OnBnClickedOk();
	CButton m_stillcapbut;
	CButton m_deintbut;
	CButton m_record;
	CButton m_dayretr;
	CButton m_setid;
	CStatic m_setidwaku;

	afx_msg void OnClickedRecord();
	afx_msg void OnClickedStillcapbut();
	afx_msg void OnClickedDeintbut();
	afx_msg void OnClickedSetid();
	afx_msg void OnClickedDate();

	afx_msg void OnPop2S0();

	afx_msg void OnPop2S1();

	afx_msg void OnPop2S2();
	afx_msg void OnPop2S3();
	afx_msg void OnPop2S4();
	afx_msg void OnPop2S5();
	afx_msg void OnPop2S6();
	afx_msg void OnPop2S7();
	afx_msg void OnPop2S8();
	afx_msg void OnPop2S9();

	afx_msg void OnPopupS0();
	afx_msg void OnPopupS1();
	afx_msg void OnPopupS2();
	afx_msg void OnPopupS3();
	afx_msg void OnPopupS4();
	afx_msg void OnPopupS5();
	afx_msg void OnPopupS6();
	afx_msg void OnPopupS7();
	afx_msg void OnPopupS8();
	afx_msg void OnPopupS9();

	afx_msg void OnPopupSetrefname();
	CButton m_setrefer;
	afx_msg void OnClickedSetrefer();
	afx_msg void OnClickedBackupbut();
	CButton m_backupbut;
	CButton m_menu;
	afx_msg void OnClickedMenu();
	afx_msg void OnPopupRestore();
	afx_msg void OnPopupHelp();
	CButton m_exit;
	afx_msg void OnBnClickedExitbut();
	afx_msg void OnPopupAllfiles();

	CStatic m_totalcnt;
	CStatic m_daycnt;
	CButton m_deintonbut;
	afx_msg void OnClickedDeintonbut();
	afx_msg void OnPopupDeinteron();
	afx_msg void OnPopupDeinteroff();
	afx_msg void OnPopupCamera1();
	afx_msg void OnPopupCamera2();
	afx_msg void OnPopupCamera3();
	afx_msg void OnPopupCamera4();
	afx_msg void OnPopupCamera5();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
