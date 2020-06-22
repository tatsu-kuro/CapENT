
// CapENT2Dlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapENT2.h"
#include "CapENT2Dlg.h"
#include "CTransDLG.h"
#include "GetNewID.h"
#include "GetID.h"
#include "CSetrefnames.h"
#include "Dayretr.h"
#include "CTrimChan.h"
#include "afxdialogex.h"
#include <direct.h>
#include <sys/stat.h>
#include <afxwin.h>
//#include <opencv2/core.hpp>    // coreモジュールのヘッダーをインクルード
//#include <opencv2/highgui.hpp> // highguiモジュールのヘッダーをインクルード
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include <vector>r
#include "mmsystem.h"
#include <sys/stat.h> 
#include <ole2.h> // OLE2 Definitions
#pragma comment(lib,"winmm.lib")
using namespace cv;
using namespace std;//これでofstream ifstream が定義されていません　が出なくなる
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CapENT2_TOP
#include "CapENT2moromoro.h"
int uio_free ();
int uio_seldev ( int p1, int p2, int p3, int p4=0 );
int uio_getdevs ( int p1, int p2, int p3, int p4=0 );
int uio_inp ( int* p1, int p2, int p3, int p4=0 );
int uio_SendRecv(BYTE *sendData,BYTE *recvData);
int uio_out ( int p1, int p2, int p3, int p4=0 );
int uio_find();
UINT USB_RS232Thread( LPVOID dammy );

bool changeCSIZflag = false;
int usbio232=-1;
int cameran;
void DispBkUp(CDC *pDC, int f1, int t1, int x0, int y0, int mode);
#ifdef _DEBUG
#pragma comment(lib,"opencv_core2413d.lib")
#pragma comment(lib,"opencv_imgproc2413d.lib")
#pragma comment(lib,"opencv_highgui2413d.lib")
//#pragma comment(lib,"opencv_objdetect2413d.lib")
//#pragma comment(lib,"opencv_contrib2413d.lib")
//#pragma comment(lib,"opencv_features2d2413d.lib")
//#pragma comment(lib,"opencv_flann2413d.lib")
//#pragma comment(lib,"opencv_gpu2413d.lib")
//#pragma comment(lib,"opencv_legacy2413d.lib")
//#pragma comment(lib,"opencv_ts2413d.lib")
//#pragma comment(lib,"opencv_video2413d.lib")
#else
#pragma comment(lib,"opencv_core2413.lib")
#pragma comment(lib,"opencv_imgproc2413.lib")
#pragma comment(lib,"opencv_highgui2413.lib")
//#pragma comment(lib,"opencv_objdetect2413.lib")
//#pragma comment(lib,"opencv_contrib2413.lib")
//#pragma comment(lib,"opencv_features2d2413.lib")
//#pragma comment(lib,"opencv_flann2413.lib")
//#pragma comment(lib,"opencv_gpu2413.lib")
//#pragma comment(lib,"opencv_legacy2413.lib")
//#pragma comment(lib,"opencv_ts2413.lib")
//#pragma comment(lib,"opencv_video2413.lib")
#endif
void DrawDeinter(CStatic *pic,int mode,int src);
// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ
// AutoWrap() - Automation helper function...
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...) {
    // Begin variable-argument list...
    va_list marker;
    va_start(marker, cArgs);

    if(!pDisp) {
        MessageBox(NULL, "NULL IDispatch passed to AutoWrap()", "Error", 0x10010);
        _exit(0);
    }

    // Variables used...
    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char buf[200];
    char szName[200];

    
    // Convert down to ANSI
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
    
    // Get DISPID for name passed...
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if(FAILED(hr)) {
        sprintf_s(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
        MessageBox(NULL, buf, "AutoWrap()", 0x10010);
        _exit(0);
        return hr;
    }
    
    // Allocate memory for arguments...
    VARIANT *pArgs = new VARIANT[cArgs+1];
    // Extract arguments...
    for(int i=0; i<cArgs; i++) {
        pArgs[i] = va_arg(marker, VARIANT);
    }
    
    // Build DISPPARAMS
    dp.cArgs = cArgs;
    dp.rgvarg = pArgs;
    
    // Handle special-case for property-puts!
    if(autoType & DISPATCH_PROPERTYPUT) {
        dp.cNamedArgs = 1;
        dp.rgdispidNamedArgs = &dispidNamed;
    }
    
    // Make the call!
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
    if(FAILED(hr)) {
        sprintf_s(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
        MessageBox(NULL, buf, "AutoWrap()", 0x10010);
        _exit(0);
        return hr;
    }
    // End variable-argument section...
    va_end(marker);
    
    delete [] pArgs;
    
    return hr;
}


UINT USB_RS232Thread( LPVOID dammy )
{
	static int oldda=0;
	int newda;
	int dammycnt=0,sw,loop,sleep,latency;
	BYTE senddata[130],recvdata[130];
	Sleep(1000);
	while(usbio232>=0){
		dammycnt++;
		sscanf_s(ptxt[LOOP],"%d",&loop);
		if(loop<1)loop=1;
		else if(loop>2000)loop=2000;
		sscanf_s(ptxt[SLEE],"%d",&sleep);
		if(sleep<1)sleep=1;
		else if(sleep>2000)sleep=2000;
		sscanf_s(ptxt[LATE],"%d",&latency);
		if(latency<1)latency=1;
		else if(latency>2000)latency=2000;
		if(usbio232==0){//USB-IO
			uio_out(0,0xFF,0);
			uio_inp(&newda,0,0);
			newda=newda%2;
			if(oldda!=newda){
				if(newda==1)sw=1;
				else sw=0;
				oldda=newda;
//				if(((sw==1&&strstr(ptxt[ONOF],"ON"))||(sw==0 && strstr(ptxt[ONOF],"OFF")))&&dammycnt>5 ){
				if(sw==0&&dammycnt>5 ){
					Sleep(latency);
					keybd_event(0x0D,0,0,0);
					Sleep(sleep);
				}
			}
		}else if(usbio232>0&&usbio232<3){//usb-io2.0,usb-io2.0(aki)
			senddata[0]=0x20;
			senddata[1]=0x01;
			senddata[2]=0xFF;
			senddata[3]=0x02;
			senddata[4]=0xFF;
			senddata[63]=0;
			uio_SendRecv(senddata,recvdata);
			newda=recvdata[2];
			newda=newda%2;
			if(oldda!=newda){
				if(newda==1)sw=1;
				else sw=0;
				oldda=newda;
//				if(((sw==1&&strstr(ptxt[ONOF],"ON"))||(sw==0 && strstr(ptxt[ONOF],"OFF")))&&dammycnt>5 ){
				if(sw==0&&dammycnt>5 ){
					Sleep(latency);
					keybd_event(0x0D,0,0,0);
					Sleep(sleep);
				}
			}
		}else break;//ぬける
		Sleep(loop);
	}
	return 0;
};
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCapENT2Dlg ダイアログ



CCapENT2Dlg::CCapENT2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCapENT2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCapENT2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_STOPCAP, m_stopcap);
	DDX_Control(pDX, IDC_MOVIEPT, m_moviept);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_TIMETRIM, m_timetrim);
	DDX_Control(pDX, IDC_CUTMOVIE, m_cutmovie);
	//  DDX_Control(pDX, IDC_CAMNUM, m_camnum);
	DDX_Control(pDX, IDC_PIC0, m_pic0);
	DDX_Control(pDX, IDC_PIC1, m_pic1);
	DDX_Control(pDX, IDC_PIC2, m_pic2);
	DDX_Control(pDX, IDC_PIC3, m_pic3);
	DDX_Control(pDX, IDC_PIC4, m_pic4);
	DDX_Control(pDX, IDC_PIC5, m_pic5);
	DDX_Control(pDX, IDC_PIC6, m_pic6);
	DDX_Control(pDX, IDC_PIC7, m_pic7);
	DDX_Control(pDX, IDC_PIC8, m_pic8);
	DDX_Control(pDX, IDC_PIC9, m_pic9);
	DDX_Control(pDX, IDC_PICM0, m_picm0);
	DDX_Control(pDX, IDC_PICM1, m_picm1);
	DDX_Control(pDX, IDC_PICM2, m_picm2);
	DDX_Control(pDX, IDC_PICM3, m_picm3);
	DDX_Control(pDX, IDC_PICL, m_picl);
	DDX_Control(pDX, IDC_MOVIEW, m_moview);
	DDX_Control(pDX, IDC_DELPIC, m_delpic);
	DDX_Control(pDX, IDC_DELPICWAKU, m_delpicwaku);
	DDX_Control(pDX, IDC_DATACNT, m_datacnt);
	DDX_Control(pDX, IDC_STOPDISP, m_stopdisp);
	DDX_Control(pDX, IDC_PICLMAX, m_picmax);
	DDX_Control(pDX, IDC_STILLCAPBUT, m_stillcapbut);
	DDX_Control(pDX, IDC_DEINTBUT, m_deintbut);
	DDX_Control(pDX, IDC_RECORD, m_record);
	DDX_Control(pDX, IDC_DATE, m_dayretr);
	DDX_Control(pDX, IDC_SETID, m_setid);
	DDX_Control(pDX, IDC_SETIDWAKU, m_setidwaku);
	DDX_Control(pDX, IDC_SETREFER, m_setrefer);
	DDX_Control(pDX, IDC_BACKUPBUT, m_backupbut);
	DDX_Control(pDX, IDC_MENU, m_menu);
	DDX_Control(pDX, IDC_EXITBUT, m_exit);
	DDX_Control(pDX, IDC_TOTALCNT, m_totalcnt);
	DDX_Control(pDX, IDC_DAYCNT, m_daycnt);
	DDX_Control(pDX, IDC_DEINTONBUT, m_deintonbut);
}

BEGIN_MESSAGE_MAP(CCapENT2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOPCAP, &CCapENT2Dlg::OnBnClickedStopcap)
	ON_BN_CLICKED(IDCANCEL, &CCapENT2Dlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_CUTMOVIE, &CCapENT2Dlg::OnBnClickedCutmovie)
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_STN_CLICKED(IDC_PICL, &CCapENT2Dlg::OnStnClickedPicl)
	ON_WM_MOUSEWHEEL()
//	ON_STN_CLICKED(IDC_CAMNUM, &CCapENT2Dlg::OnClickedCamnum)
	ON_COMMAND(ID_POPUP_SETID, &CCapENT2Dlg::OnPopupSetid)
	ON_COMMAND(ID_POPUP_DELETE, &CCapENT2Dlg::OnPopupDelete)
	ON_COMMAND(ID_POPUP_DATESEARCH, &CCapENT2Dlg::OnPopupDatesearch)
	ON_COMMAND(ID_POPUP_COPY, &CCapENT2Dlg::OnPopupCopy)
	ON_COMMAND(ID_POPUP_SETBLANK, &CCapENT2Dlg::OnPopupSetblank)
	ON_COMMAND(ID_POPUP_CHANGEID, &CCapENT2Dlg::OnPopupChangeid)
	ON_COMMAND(ID_POPUP_PRT2, &CCapENT2Dlg::OnPopupPrt2)
	ON_COMMAND(ID_POPUP_PRT4, &CCapENT2Dlg::OnPopupPrt4)
	ON_COMMAND(ID_POPUP_PRT2U, &CCapENT2Dlg::OnPopupPrt2u)
	ON_BN_CLICKED(IDC_STOPDISP, &CCapENT2Dlg::OnBnClickedStopdisp)
//	ON_COMMAND(ID_POPUP_ROTATE2, &CCapENT2Dlg::OnPopupRotate2)
//	ON_COMMAND(ID_POPUP_ROTATE3, &CCapENT2Dlg::OnPopupRotate3)
	ON_COMMAND(ID_POPUP_SETBACKUP, &CCapENT2Dlg::OnPopupSetbackup)
	ON_COMMAND(ID_POPUP_BACKUP, &CCapENT2Dlg::OnPopupBackup)
	ON_BN_CLICKED(IDOK, &CCapENT2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RECORD, &CCapENT2Dlg::OnClickedRecord)
	ON_BN_CLICKED(IDC_STILLCAPBUT, &CCapENT2Dlg::OnClickedStillcapbut)
	ON_BN_CLICKED(IDC_DEINTBUT, &CCapENT2Dlg::OnClickedDeintbut)
	ON_BN_CLICKED(IDC_SETID, &CCapENT2Dlg::OnClickedSetid)
	ON_BN_CLICKED(IDC_DATE, &CCapENT2Dlg::OnClickedDate)
	ON_COMMAND(ID_POP2_S0, &CCapENT2Dlg::OnPop2S0)
	ON_COMMAND(ID_POP2_S1, &CCapENT2Dlg::OnPop2S1)
	ON_COMMAND(ID_POP2_S2, &CCapENT2Dlg::OnPop2S2)
	ON_COMMAND(ID_POP2_S3, &CCapENT2Dlg::OnPop2S3)
	ON_COMMAND(ID_POP2_S4, &CCapENT2Dlg::OnPop2S4)
	ON_COMMAND(ID_POP2_S5, &CCapENT2Dlg::OnPop2S5)
	ON_COMMAND(ID_POP2_S6, &CCapENT2Dlg::OnPop2S6)
	ON_COMMAND(ID_POP2_S7, &CCapENT2Dlg::OnPop2S7)
	ON_COMMAND(ID_POP2_S8, &CCapENT2Dlg::OnPop2S8)
	ON_COMMAND(ID_POP2_S9, &CCapENT2Dlg::OnPop2S9)
	ON_COMMAND(ID_POPUP_S0, &CCapENT2Dlg::OnPopupS0)
	ON_COMMAND(ID_POPUP_S1, &CCapENT2Dlg::OnPopupS1)
	ON_COMMAND(ID_POPUP_S2, &CCapENT2Dlg::OnPopupS2)
	ON_COMMAND(ID_POPUP_S3, &CCapENT2Dlg::OnPopupS3)
	ON_COMMAND(ID_POPUP_S4, &CCapENT2Dlg::OnPopupS4)
	ON_COMMAND(ID_POPUP_S5, &CCapENT2Dlg::OnPopupS5)
	ON_COMMAND(ID_POPUP_S6, &CCapENT2Dlg::OnPopupS6)
	ON_COMMAND(ID_POPUP_S7, &CCapENT2Dlg::OnPopupS7)
	ON_COMMAND(ID_POPUP_S8, &CCapENT2Dlg::OnPopupS8)
	ON_COMMAND(ID_POPUP_S9, &CCapENT2Dlg::OnPopupS9)
	ON_COMMAND(ID_POPUP_SETREFNAME, &CCapENT2Dlg::OnPopupSetrefname)
	ON_BN_CLICKED(IDC_SETREFER, &CCapENT2Dlg::OnClickedSetrefer)
	ON_BN_CLICKED(IDC_BACKUPBUT, &CCapENT2Dlg::OnClickedBackupbut)
	ON_BN_CLICKED(IDC_MENU, &CCapENT2Dlg::OnClickedMenu)
	ON_COMMAND(ID_POPUP_RESTORE, &CCapENT2Dlg::OnPopupRestore)
	ON_COMMAND(ID_POPUP_HELP, &CCapENT2Dlg::OnPopupHelp)	
	ON_BN_CLICKED(IDC_EXITBUT, &CCapENT2Dlg::OnBnClickedExitbut)
	ON_COMMAND(ID_POPUP_ALLFILES, &CCapENT2Dlg::OnPopupAllfiles)
	ON_BN_CLICKED(IDC_DEINTONBUT, &CCapENT2Dlg::OnClickedDeintonbut)
	ON_COMMAND(ID_POPUP_DEINTERON, &CCapENT2Dlg::OnPopupDeinteron)
	ON_COMMAND(ID_POPUP_DEINTEROFF, &CCapENT2Dlg::OnPopupDeinteroff)
	ON_COMMAND(ID_POPUP_CAMERA1, &CCapENT2Dlg::OnPopupCamera1)
	ON_COMMAND(ID_POPUP_CAMERA2, &CCapENT2Dlg::OnPopupCamera2)
	ON_COMMAND(ID_POPUP_CAMERA3, &CCapENT2Dlg::OnPopupCamera3)
	ON_COMMAND(ID_POPUP_CAMERA4, &CCapENT2Dlg::OnPopupCamera4)
	ON_COMMAND(ID_POPUP_CAMERA5, &CCapENT2Dlg::OnPopupCamera5)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// 画像を画像に貼り付ける関数
void paste(cv::Mat dst, cv::Mat src, int x, int y, int width, int height) {
	cv::Mat resized_img;
	cv::resize(src, resized_img, cv::Size(width, height));

	if (x >= dst.cols || y >= dst.rows) return;
	int w = (x >= 0) ? std::min(dst.cols - x, resized_img.cols) : std::min(std::max(resized_img.cols + x, 0), dst.cols);
	int h = (y >= 0) ? std::min(dst.rows - y, resized_img.rows) : std::min(std::max(resized_img.rows + y, 0), dst.rows);
	int u = (x >= 0) ? 0 : std::min(-x, resized_img.cols - 1);
	int v = (y >= 0) ? 0 : std::min(-y, resized_img.rows - 1);
	int px = std::max(x, 0);
	int py = std::max(y, 0);

	cv::Mat roi_dst = dst(cv::Rect(px, py, w, h));
	cv::Mat roi_resized = resized_img(cv::Rect(u, v, w, h));
	roi_resized.copyTo(roi_dst);
}

// 画像を画像に貼り付ける関数（サイズ指定を省略したバージョン）
void paste(cv::Mat dst, cv::Mat src, int x, int y) {
	paste(dst, src, x, y, src.rows, src.cols);
}
void MakeJpg4prt(int mode)
{
	int w,h;
	char fn[301];
	Mat dst,img1,img2,img3,img4;
	if(mode==0){//tate 2枚
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[0]);
		img1=imread(fn);
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[2]);
		img2=imread(fn);
		w=img1.cols;//size().width;
		h=img1.rows;//size().height;
		Mat img(2*h+10,w,img1.type());//CV_8UC3
		rectangle(img,Point(w,2*h+10),Point(0,0), CV_RGB (255,255,255),-1,CV_AA,0 );
		if(img1.data!=NULL)paste(img, img1, 0, 0,w,h);
		if(img2.data!=NULL)paste(img, img2, 0, 10+h,w,h);
		imwrite("2pics.jpg", img);
	}else if(mode==1){//upper 2
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[0]);
		img1=imread(fn);
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[1]);
		img2=imread(fn);
//		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[2]);
//		img3=imread(fn);
//		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[3]);
//		img4=imread(fn);
		w=img1.size().width;
		h=img1.size().height;
		//h2=h/2;
		Mat img(h+h+10,w+w+10,img1.type());
		rectangle(img,Point(2*w+10,2*h+10),Point(0,0), CV_RGB (255,255,255),-1,CV_AA,0 );
		if(img1.data!=NULL)paste(img, img1, 0  , h/2 ,w,h);
		if(img2.data!=NULL)paste(img, img2, 10+w,h/2 ,w,h);
//		if(img3.data!=NULL)paste(img, img3, 1  , 10+h,w,h);
//		if(img4.data!=NULL)paste(img, img4, 10+w, 10+h,w,h);
		imwrite("2pics_upper.jpg", img);
	}else if(mode==2){//all 4
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[0]);
		img1=imread(fn);
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[1]);
		img2=imread(fn);
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[2]);
		img3=imread(fn);
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[3]);
		img4=imread(fn);
		w=img1.size().width;
		h=img1.size().height;
		Mat img(h+h+10,w+w+10,img1.type());
		rectangle(img,Point(2*w+10,2*h+10),Point(0,0), CV_RGB (255,255,255),-1,CV_AA,0 );
		if(img1.data!=NULL)paste(img, img1, 0  , 0  ,w,h);
		if(img2.data!=NULL)paste(img, img2, 10+w, 0  ,w,h);
		if(img3.data!=NULL)paste(img, img3, 1  , 10+h,w,h);
		if(img4.data!=NULL)paste(img, img4, 10+w, 10+h,w,h);
		imwrite("4pics.jpg", img);
	}
//	GetTempPath(MAX_PATH,path);
//	AfxMessageBox(path);
}
// CCapENT2Dlg メッセージ ハンドラー
int GetDeviceN() {
	int i;
	for (i = 0; i < 10; i++) {
		VideoCapture capture(i);//デバイスのオープン
		if (!capture.isOpened()) {
			capture.release();
			return i;
		}
		capture.release();
		Sleep(200);
	}
	return i;
}
BOOL CCapENT2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// "バージョン情報..." メニューをシステム メニューに追加します。
	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	SetWindowText(Vertxt);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	cameran = GetDeviceN();
	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定
	LoadCon();
	IDnum=0;
	GetCurrentDirectory(300,CurDir);

	
	ShowWindow(SW_MAXIMIZE);
	grayRGB=GetSysColor(COLOR_BTNFACE);
	m_ok.ShowWindow(SW_HIDE);
	char nen[20];
	_mkdir("gazou");
	time_t now=time(NULL);
	struct tm tms;
	struct tm* tmp=&tms;
	localtime_s(tmp,&now);
	sprintf_s(nen,"gazou\\%i",tmp->tm_year+1900);//gazouの下に今日の年号フォルダを作る
	_mkdir(nen);
//	CRect rect;
//	GetClientRect(&rect);
	SetCtrlPos();// rect.right, rect.bottom);
	bmp_button_newid.LoadBitmapA(IDB_NEWIDBUTTON);
	m_setid.SetBitmap(bmp_button_newid);
	bmp_backup.LoadBitmapA(IDB_BACKUP);
	m_backupbut.SetBitmap(bmp_backup);
//	bmp_button_resetrec.LoadBitmapA(IDB_RESTARTBUTTON);
//	m_resetrec.SetBitmap(bmp_button_resetrec);
	bmp_record.LoadBitmapA(IDB_RECORD);
	m_record.SetBitmap(bmp_record);
	bmp_exitbut.LoadBitmapA(IDB_EXITBUT);
	m_exit.SetBitmap(bmp_exitbut);


//	bmp_button_exit.LoadBitmapA(IDB_EXITBUTTON);
//	m_cancel.SetBitmap(bmp_button_exit);
	bmp_button_stopdisp.LoadBitmapA(IDB_STOPDISP);
	m_stopdisp.SetBitmap(bmp_button_stopdisp);
	bmp_button_stop.LoadBitmapA(IDB_STOPBUTTON);
	m_stopcap.SetBitmap(bmp_button_stop);
	bmp_ref.LoadBitmapA(IDB_REF1);
	m_setrefer.SetBitmap(bmp_ref);
	bmp_menu.LoadBitmapA(IDB_MENU);
	m_menu.SetBitmap(bmp_menu);
//	bmp_ref3.LoadBitmapA(IDB_REF3);
//	m_ref3.SetBitmap(bmp_ref3);
//	bmp_ref4.LoadBitmapA(IDB_REF4);
//	m_ref4.SetBitmap(bmp_ref4);
	bmp_retr.LoadBitmapA(IDB_RETR);
	m_dayretr.SetBitmap(bmp_retr);
	bmp_button_delete.LoadBitmapA(IDB_DELETEBUTTON);
	m_delpic.SetBitmap(bmp_button_delete);
//	m_delpic.SetBitmap(bmp_button_newid);
	m_delpic.SetBitmap(bmp_button_delete);
	bmp_button_trim.LoadBitmapA(IDB_TRIMBUTTON);
	m_cutmovie.SetBitmap(bmp_button_trim);
	bmp_stillcap.LoadBitmapA(IDB_STILLCAP);
	m_stillcapbut.SetBitmap(bmp_stillcap);
//	bmp_deint.LoadBitmapA(IDB_DEINTBUT);
//	m_deintbut.SetBitmap(bmp_deint);
//	bmp_deinton.LoadBitmapA(IDB_DEINTONBUT);
//	m_deintonbut.SetBitmap(bmp_deinton);

	// TODO: 初期化をここに追加します。
	m_PrevloopEnable=false;
	m_PlayloopEnable=false;
	m_CaploopEnable=false;
	CaptureNowf=false;
	OnPaintf=false;
	strcpy_s(playingfn,100,"");
	strcpy_s(lastrecfn,100,"");
	strcpy_s(trimingfn,100,"");
	strcpy_s(listaviselected,100,"");
	allCnt=SetAllPics();
	dayCnt=-1;
	idCnt=0;
	picsflag=-1;
	lastdayretr=-1;//これで最後の日時検索データは今日となる
	chanid = 0;


	m_tooltip.Create(this);
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);
//	m_tooltip.AddTool(&m_chanid, "画像のID変更\n変更する画像をここにドラッグアンドドロップします");
	m_tooltip.AddTool(&m_exit, "枠の上に保存ファイル全件数");
	m_tooltip.AddTool(&m_dayretr, "日付で検索\n枠上部に検索合致数を表示しています");
	m_tooltip.AddTool(&m_setid, "ID検索もしくは変更\n現行IDを枠上部に表示しています\n枠の上には現行IDの画像数を表示しています");
	m_tooltip.AddTool(&m_deintbut, "キャプチャー画像のデインターレース処理をしません。");
	m_tooltip.AddTool(&m_deintonbut, "キャプチャー画像のデインターレース処理します\nONの設定でも動画はデインターレース処理せずに保存されます");
	m_tooltip.AddTool(&m_stopcap, "録画を終了し、録画した映像を最初から再生します\nF2キーと同等です");
	m_tooltip.AddTool(&m_stopdisp, "録画を終了し、現行IDの静止画を4枚表示します\nF3キーと同等です");
	m_tooltip.AddTool(&m_stillcapbut, "静止画をキャプチャーします\nEnterキーと同等です");
	m_tooltip.AddTool(&m_cutmovie, "再生スライドバーの左右黄色三角マークの間を切り取り保存します\n黄色三角マークはマウスでドラッグできます");
//	strcat_s(ptxt[REF1], "\n(1)クリックで表示\n(2)ここへ画像ドラッグアンドドロップで参照ファイルに設定");
//	m_tooltip.AddTool(&m_ref1, ptxt[REF1]);
//	strcat_s(ptxt[REF2], "\n(1)クリックで表示\n(2)ここへ画像ドラッグアンドドロップで参照ファイルに設定");
//	m_tooltip.AddTool(&m_ref2, ptxt[REF2]);
//	strcat_s(ptxt[REF3], "\n(1)クリックで表示\n(2)ここへ画像ドラッグアンドドロップで参照ファイルに設定");
//	m_tooltip.AddTool(&m_ref3, ptxt[REF3]);
//	strcat_s(ptxt[REF4], "\n(1)クリックで表示\n(2)ここへ画像ドラッグアンドドロップで参照ファイルに設定");
//	m_tooltip.AddTool(&m_ref4, ptxt[REF4]);// コントロールにツールヒントを割り当てる。
	//	m_tooltip.AddTool((CWnd*)m_ref3, _T("ボタン１"));
	SetButtons(CapENTmode = Disp4Mode);
	OnClickedRecord();
//	OnBnClickedRecordbutton();
//	Preview();
//	SetWindowText(Vertxt);
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}
void CCapENT2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
void CCapENT2Dlg::SetButtons(int mode)
{
	int swm[6][27] = {
		1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,1,1, 0,1,//1:capture
		1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1, 1,1,//2:play
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,0, 1,1,1,1,1, 1,1,1,0,0, 0,1,//3:4disp(picm0-3)
		1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,1, 1,1,1,1,1, 1,1,1,0,0, 0,1,//4:1disp(picl)
	};
	//0-9 10-13(picm mode:3) 14(picL mode:4 movie mode:2) 
	//15 delete
	//16-19 ref1-4
	//20 setid
	//21 dayretr
	//22 chanid
	//23 stillcap
	//24 deinter
	//25 cutmovie
	//26 record	
	m_cancel.ShowWindow(SW_HIDE);
	m_datacnt.ShowWindow(SW_SHOW);//常に表示
	m_stopcap.ShowWindow(mode == CaptMode ? SW_SHOW : SW_HIDE);//stop & play movie
	m_stopdisp.ShowWindow(mode == CaptMode ? SW_SHOW : SW_HIDE);//stop & disppic4
	m_moview.ShowWindow(mode == CaptMode || mode == PlayMode ? SW_SHOW : SW_HIDE);
//	m_camnum.ShowWindow(strstr(ptxt[CAMD], "1") && mode == CaptMode ? SW_SHOW : SW_HIDE);//configファイルを編集すると消せる
//	m_camnum.ShowWindow(mode == CaptMode ? SW_SHOW : SW_HIDE);//configファイルを編集すると消せる
	m_timetrim.ShowWindow(mode == CaptMode || mode == PlayMode ? SW_SHOW : SW_HIDE);
	m_moviept.ShowWindow(mode == PlayMode ? SW_SHOW : SW_HIDE);

	m_pic0.ShowWindow(swm[mode][0] ? SW_SHOW : SW_HIDE);
	m_pic1.ShowWindow(swm[mode][1] ? SW_SHOW : SW_HIDE);
	m_pic2.ShowWindow(swm[mode][2] ? SW_SHOW : SW_HIDE);
	m_pic3.ShowWindow(swm[mode][3] ? SW_SHOW : SW_HIDE);
	m_pic4.ShowWindow(swm[mode][4] ? SW_SHOW : SW_HIDE);
	m_pic5.ShowWindow(swm[mode][5] ? SW_SHOW : SW_HIDE);
	m_pic6.ShowWindow(swm[mode][6] ? SW_SHOW : SW_HIDE);
	m_pic7.ShowWindow(swm[mode][7] ? SW_SHOW : SW_HIDE);
	m_pic8.ShowWindow(swm[mode][8] ? SW_SHOW : SW_HIDE);
	m_pic9.ShowWindow(swm[mode][9] ? SW_SHOW : SW_HIDE);
	m_picm0.ShowWindow(swm[mode][10] ? SW_SHOW : SW_HIDE);
	m_picm1.ShowWindow(swm[mode][11] ? SW_SHOW : SW_HIDE);
	m_picm2.ShowWindow(swm[mode][12] ? SW_SHOW : SW_HIDE);
	m_picm3.ShowWindow(swm[mode][13] ? SW_SHOW : SW_HIDE);
	m_picl.ShowWindow(swm[mode][14] ? SW_SHOW : SW_HIDE);
	m_picmax.ShowWindow(swm[mode][14] ? SW_SHOW : SW_HIDE);
	m_delpic.ShowWindow(swm[mode][15] ? SW_SHOW : SW_HIDE);
	m_delpicwaku.ShowWindow(swm[mode][15] ? SW_SHOW : SW_HIDE);
	m_setrefer.ShowWindow(swm[mode][16] ? SW_SHOW : SW_HIDE);
	m_backupbut.ShowWindow(swm[mode][16] ? SW_SHOW : SW_HIDE);
	m_menu.ShowWindow(swm[mode][0] ? SW_SHOW : SW_HIDE);
	//	m_ref2.ShowWindow(swm[mode][17] ? SW_SHOW : SW_HIDE);
//	m_ref2waku.ShowWindow(swm[mode][17] ? SW_SHOW : SW_HIDE);
//	m_ref3.ShowWindow(swm[mode][18] ? SW_SHOW : SW_HIDE);
//	m_ref3waku.ShowWindow(swm[mode][18] ? SW_SHOW : SW_HIDE);
//	m_ref4.ShowWindow(swm[mode][19] ? SW_SHOW : SW_HIDE);
//	m_ref4waku.ShowWindow(swm[mode][19] ? SW_SHOW : SW_HIDE);
	m_setid.ShowWindow(swm[mode][20] ? SW_SHOW : SW_HIDE);
	m_setidwaku.ShowWindow(swm[mode][20] ? SW_SHOW : SW_HIDE);
	m_dayretr.ShowWindow(swm[mode][21] ? SW_SHOW : SW_HIDE);
//	m_dayretrwaku.ShowWindow(swm[mode][21] ? SW_SHOW : SW_HIDE);
//	m_chanid.ShowWindow(swm[mode][22] ? SW_SHOW : SW_HIDE);
//	m_chanidwaku.ShowWindow(swm[mode][22] ? SW_SHOW : SW_HIDE);
	m_stillcapbut.ShowWindow(swm[mode][23] ? SW_SHOW : SW_HIDE);
	m_deintbut.ShowWindow(swm[mode][24] ? SW_SHOW : SW_HIDE);
	m_deintonbut.ShowWindow(swm[mode][24] ? SW_SHOW : SW_HIDE);
	m_cutmovie.ShowWindow(swm[mode][25] ? SW_SHOW : SW_HIDE);
	m_record.ShowWindow(swm[mode][26] ? SW_SHOW : SW_HIDE);
	if (strstr(ptxt[INTE], "1")) {
		bmp_deint.LoadBitmapA(IDB_DEINTBUT);
		bmp_deinton.LoadBitmapA(IDB_DEINTON_CHECK);
	}
	else {
		bmp_deint.LoadBitmapA(IDB_DEINTBUT_CHECK);
		bmp_deinton.LoadBitmapA(IDB_DEINTONBUT);
	}
	m_deintbut.SetBitmap(bmp_deint);
	m_deintonbut.SetBitmap(bmp_deinton);
}
// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。


int CCapENT2Dlg::DispOneNum(CStatic *ms, int num, int src)
{

	int x0=0,y0=46,dx=10,dy=20;
	CDC MemDC,*pDC;
	CBitmap *pOldBmp,m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC=ms->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	//	if(src==SRCAND)pDC->FillSolidRect(0,0,38,38+20,grayRGB);//(255,255,255));//grayRGB);
	//	else pDC->FillSolidRect(0,0,38,38+20,RGB(255,255,255));//grayRGB);
	pDC->FillSolidRect(34,11,dx,dy,grayRGB);
	pDC->BitBlt(34,11,dx,dy,&MemDC,num*dx+x0,y0,SRCAND);//
	pDC->BitBlt(20,38,40,29, &MemDC, 388, 0, SRCAND);//camera illust

	ms->ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
	return 0;
}

void DispIroiro(CStatic *pic, int x0, int y0, int dx, int dy, int sx, int sy, int mode, int src)
{

	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC = pic->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);

	pDC->BitBlt(x0, y0, dx, dy, &MemDC, sx, sy, src);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	pic->ReleaseDC(pDC);//ReleaseDC(pDC)??はエラーとなる
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void CCapENT2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CRect rect;
		GetClientRect(&rect);
		SetCtrlPos();// rect.right, rect.bottom);
//		SetButtons(CapNYSmode);

		if (CapENTmode == CaptMode) {//capture
//			int num;
//			sscanf_s(ptxt[CAME], "%d", &num);
//			DispOneNum(&m_camnum, num, SRCCOPY);
//			DispIroiro(&m_cameratext, 4, 5, 20, 16, 402, 3, 5, SRCAND);
//			if (strstr(ptxt[INTE], "0"))DispIroiro(&m_deinter, 1, 1, 31, 29, 428, 36, 7, SRCCOPY);
//			else DispIroiro(&m_deinter, 1, 1, 31, 29, 428, 3, 6, SRCCOPY);
			Disp10Pics(PicsOffset);
			DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
			DispNum_sub(&m_setidwaku, IDnum);
		}
		else if (CapENTmode == PlayMode) {//||CapNYSmode==1){
			DispSlider(1);
	//		if (strstr(ptxt[INTE], "0"))DispIroiro(&m_deinter, 1, 1, 31, 29, 428, 36, 7, SRCCOPY);
	//		else DispIroiro(&m_deinter, 1, 1, 31, 29, 428, 3, 6, SRCCOPY);
			if (!m_PlayloopEnable) {
				DispOneFrame(playingfn, 0);
			}
			Disp10Pics(PicsOffset);
			DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
			DispNum_sub(&m_setidwaku, IDnum);
		}else if(CapENTmode==Disp4Mode){
			Disp4Pics(1+2+4+8);//4マイ表示
			Disp10Pics(PicsOffset);
			DispNum(&m_datacnt,dayCnt,idCnt,allCnt);
			DispNum_sub(&m_setidwaku,IDnum);
			
		}else if(CapENTmode==Disp1Mode){
			DispLPic(CurPicL);//最後に表示したものを表示
			DispNum(&m_datacnt,dayCnt,idCnt,allCnt);
			DispNum_sub(&m_setidwaku,IDnum);
		}
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CCapENT2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#define hisiRGB RGB(250,250,250)
#define sankakuRGB RGB(250,250,0)
#define haniRGB RGB(120,120,120)
#define wakuRGB RGB(180,180,180) //grayRGB
#define sumiRGB RGB(0,0,0)//縦じま

void Hisigata(CDC *pDC,int x,int y)
{
	CBrush BR, *oldB; // oldB は、使う必要はありません。(選択前の、古いブラシのポインタを保存します。)
	BR.CreateSolidBrush(hisiRGB);// RGB(0,255,255) ); // BR を水色のブラシとする
	oldB = pDC->SelectObject(&BR); // ブラシ BR を選択します。(以後の塗りつぶしには BR が使用されます。)
	POINT po[5];
	po[0].x=x-9;
	po[0].y=y+11;
	po[1].x=x;
	po[1].y=y+2;
	po[2].x=x+9;
	po[2].y=y+11;
	po[3].x=x;
	po[3].y=y+20;
	pDC->SetPolyFillMode(WINDING );
	pDC->Polygon(po,4);
	pDC->SelectObject(oldB); // ブラシを元に戻します。
}
void SankakuL(CDC *pDC,int x,int y)
{
	CBrush BR, *oldB; // oldB は、使う必要はありません。(選択前の、古いブラシのポインタを保存します。)
	BR.CreateSolidBrush(sankakuRGB);// RGB(0,255,255) ); // BR を水色のブラシとする
	oldB = pDC->SelectObject(&BR); // ブラシ BR を選択します。(以後の塗りつぶしには BR が使用されます。)
	POINT po[5];

	po[0].x=x;
	po[0].y=y;
	po[1].x=x+11;
	po[1].y=y+12-1;
	po[2].x=x;
	po[2].y=y+24-2;
	pDC->SetPolyFillMode(WINDING );
	pDC->Polygon(po,3);
	pDC->SelectObject(oldB); // ブラシを元に戻します。
}
void SankakuR(CDC *pDC,int x,int y)
{
	CBrush BR, *oldB; // oldB は、使う必要はありません。(選択前の、古いブラシのポインタを保存します。)
	BR.CreateSolidBrush(sankakuRGB);// RGB(0,255,255) ); // BR を水色のブラシとする
	oldB = pDC->SelectObject(&BR); // ブラシ BR を選択します。(以後の塗りつぶしには BR が使用されます。)
	POINT po[5];
	po[0].x=x-11;
	po[0].y=y+12-1;
	po[1].x=x;
	po[1].y=y;
	po[2].x=x;
	po[2].y=y+24-2;
	pDC->SetPolyFillMode(WINDING );
	pDC->Polygon(po,3);
	pDC->SelectObject(oldB); // ブラシを元に戻します。
}

void Waku(CDC *pDC,int x,int y,int x1,int y1)
{
	pDC->FillSolidRect(x,y,x1,1,RGB(0,0,0));
	pDC->FillSolidRect(x,y,1,y1,RGB(0,0,0));
	pDC->FillSolidRect(x+x1,y,1,y1,RGB(0,0,0));
	pDC->FillSolidRect(x,y+y1,x1+1,1,RGB(0,0,0));
}

void CCapENT2Dlg::DispSlider(int f)
{//全体を右に10ずらす
//	slideh=29;

	if(trimposa<0||//trimposb>slidew||
		trimposa>trimposb||currentframe<0||maxframenum<=0){
		return;
	}
	if(	trimposb>slidew)trimposb=slidew;
	CDC *pDC=m_moviept.GetDC();
	CDC	MemDC;
	CBitmap bmpMem;
	MemDC.CreateCompatibleDC(pDC);
	bmpMem.CreateCompatibleBitmap(pDC,slidew+100,slideh+100);
	CBitmap* pOldBmp=MemDC.SelectObject(&bmpMem);
	int wab=trimposb-trimposa;//,dy=27;
//	pDC->FillSolidRect(-10,0,slidew+20,slideh+10,grayRGB);
//	MemDC.FillSolidRect(0,0,slidew+20,slideh+10,grayRGB);
	MemDC.FillSolidRect(0,0,slidew+18,slideh+10,grayRGB);
	if(f==2){//初期設定表示
//		pDC->FillSolidRect(0,0,slidew+1,slideh,wakuRGB);//(234,232,216));//塗りつぶし
//		pDC->FillSolidRect(0,0,wab+1,slideh,haniRGB);
//		SankakuL(pDC,0,3);
//		SankakuR(pDC,slidew,3);
//		Hisigata(pDC,0,0);
		MemDC.FillSolidRect(10,0,slidew,slideh,wakuRGB);//(234,232,216));//塗りつぶし
		MemDC.FillSolidRect(10,0,wab,slideh,haniRGB);
		SankakuL(&MemDC,10,3);
		SankakuR(&MemDC,10+slidew-1,3);
		Hisigata(&MemDC,10,0);
	}else if(f==1){//0：slideを消すだけ
	//枠内塗りつぶし
//		pDC->FillSolidRect(0,0,slidew+1,slideh,wakuRGB);//(234,232,216));//塗りつぶし
		MemDC.FillSolidRect(10,0,slidew,slideh,wakuRGB);//(234,232,216));//塗りつぶし
	//範囲(a-b)
		MemDC.FillSolidRect(10+trimposa,0,wab,slideh,haniRGB);
		SankakuL(&MemDC,10+trimposa,3);
		SankakuR(&MemDC,10+trimposb-1,3);
	//菱形
		Hisigata(&MemDC,10+slidew*currentframe/maxframenum,3);//int(double(WI)*(pos/avilen))+tx0(),Y0+1);
	}
	//ちらつき防止：temporaryCDCに描いたsliderを実際のsliderにコピー
//	pDC->BitBlt(0,0,slidew+20,slideh+10,&MemDC,0,0,SRCCOPY);
	pDC->BitBlt(0,0,slidew+18,slideh+10,&MemDC,0,0,SRCCOPY);
//	ReleaseDC(pDC);
	m_moviept.ReleaseDC(pDC);//こちらがいいのだろうか？
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void PushfnPtxt(char *fn)
{
	char buf[100];
	char *p;
	if (strstr(fn, "00000000"))return;
	if (p = strstr(ptxt[HIST], fn)) {
		strcpy_s(p, 100, p + strlen(fn) + 1);
	}
	sprintf_s(buf, "%s,%s", fn, ptxt[HIST]);
	buf[8 * 10 + 9] = '\0';
	strcpy_s(ptxt[HIST], buf);
}
int backupx0;
void CCapENT2Dlg::SetCtrlPos()//int w, int h)
{
	CRect rect;
	GetClientRect(&rect);
	int w=Winw = rect.right;// .Width();// w;
	int h=Winh = rect.bottom;// Height();// h;
	int y=2;
	if(w<850)w=850;
	if(h<500)h=500;
	int butw=82,buth=80,dy=82;
//	if(strstr(ptxt[DAUT],"1")){//display size setting auto
	//ここは削除？autoにするとエラー？何を考えてたんだろう思い出せないので削除
		Gwinh=h-dy*2-14;
		if(Gwinh>Para1(CSIZ)){
			Gwinh=Para1(CSIZ)+(h-120-Para1(CSIZ))/5;
		}
		Gwinw=w-2*butw-120;
		if(Para0(CSIZ)*Gwinh>Para1(CSIZ)*Gwinw){
			Gwinh=Para1(CSIZ)*Gwinw/Para0(CSIZ);
		}else{
			Gwinw=Gwinh*Para0(CSIZ)/Para1(CSIZ);
		}
		sprintf_s(ptxt[DSIZ],"%d,%d",Gwinw,Gwinh);
//	}

	Gwinx=slidex=(w-Gwinw)/2;
	Gwiny=(h-Gwinh)/2-5;
	slidey=Gwiny+Gwinh+3;
	slidew=Gwinw;
	slideh=29;
	m_setid.MoveWindow(PicPos[20][0] = w - butw - 2, PicPos[20][1] = y + 2 * dy + 20 +20, PicPos[20][2] = butw, PicPos[20][3] = buth - 20, 1);//***** 3
	m_setidwaku.MoveWindow(PicPos[20][0] = w - butw - 2, PicPos[20][1] = y + 2 * dy+20, PicPos[20][2] = butw, PicPos[20][3] = buth, 1);//************3
	m_dayretr.MoveWindow(PicPos[21][0] = w - butw - 2, PicPos[21][1] = y + 3 * dy+20+20, PicPos[21][2] = butw, PicPos[21][3] = buth, 1);//********** 4
	m_stillcapbut.MoveWindow(PicPos[22][0]=Gwinx+Gwinw+8,PicPos[22][1]=Gwiny,PicPos[22][2]=55,PicPos[22][3]=76,1);
	m_cutmovie.MoveWindow(PicPos[23][0] = slidex+Gwinw+8, PicPos[23][1] = slidey-26, PicPos[23][2] = 55, PicPos[23][3] = 55,1);
	m_deintbut.MoveWindow(PicPos[24][0] = Gwinx + Gwinw + 8, PicPos[24][1] = Gwiny + 76 + 6, PicPos[24][2] = 55, PicPos[24][3] = 55, 1);
	m_deintonbut.MoveWindow(PicPos[25][0] = Gwinx + Gwinw + 8, PicPos[25][1] = Gwiny + 76 + 6 +57, PicPos[25][2] = 55, PicPos[25][3] = 55, 1);
	m_record.MoveWindow(PicPos[26][0] = w - butw - 2, PicPos[26][1] = y+dy, PicPos[26][2] = butw, PicPos[26][3] = buth, 1);//******** 1
	m_totalcnt.MoveWindow(w - butw - 2, y, butw, 20, 1);//******1
	m_exit.MoveWindow(w - butw - 2, y+20 , butw, buth-20, 1);//*****1
	m_datacnt.MoveWindow(w - butw - 2, y + 2*dy, butw, 20, 1);//******** 2
	m_daycnt.MoveWindow(w - butw - 2, y  + 3*dy+20, butw, 20, 1);//****** 2

	m_stopcap.MoveWindow(Gwinx + Gwinw/2 - butw-2 , Gwiny - buth - 2, butw, buth, 1);
	m_stopdisp.MoveWindow(Gwinx + Gwinw/2 + 2, Gwiny - buth - 2, butw, buth, 1);

	m_setrefer.MoveWindow(PicPos[17][0]=w-butw-2,PicPos[17][1]=y+4*dy +20 +20,	PicPos[17][2]=butw,PicPos[17][3]=buth,1);//***************** 5
	m_timetrim.MoveWindow(slidex,Gwiny-25,Gwinw,30,1);
	m_moviept.MoveWindow(slidex-10,slidey,slidew+12,29,1);
	int pic0x=2,pic0y=2,pich=(h-1)/10-1,picdy=pich+1,picw=pich*4/3;//picw=(Winh
	int picm0x=butw+3,picm0y=2,picmh=(h-3*picm0y)/2,picmw=(w-2*butw-6-2)/2;
	if(picw>butw){
		picm0x=picw+3;
		picmw=(w-2*picw-6-2)/2;
	}
//	m_camnum.MoveWindow(w - butw - 2, picm0y + 2 * picmh + 2 - buth, butw, buth, 1);
	m_picmax.MoveWindow(picw + 2, y, w -picw-butw - 2 * 2, h - 4);//大きな画像用
	if (CapENTmode == CaptMode) {
		m_menu.MoveWindow(w - butw - 2, picm0y + 2 * picmh + 2 - buth, butw, buth, 1);
	}
	else {
		m_menu.MoveWindow(w - butw - 2, picm0y + 2 * picmh + 2 - buth - 2 * dy, butw, buth, 1);
	}
	m_backupbut.MoveWindow(w - butw - 2, picm0y + 2 * picmh + 2 - buth - dy, butw, buth, 1);

	m_delpic.MoveWindow(    PicPos[16][0]=w-butw-2,PicPos[16][1]=picm0y+2*picmh+2-buth,PicPos[16][2]=butw,PicPos[16][3]=buth,1);
	m_delpicwaku.MoveWindow(PicPos[16][0]=w-butw-2,PicPos[16][1]=picm0y+2*picmh+2-buth,PicPos[16][2]=butw,PicPos[16][3]=buth,1);
	m_pic0.MoveWindow(PicPos[0][0]=pic0x,PicPos[0][1]=pic0y+0*picdy,PicPos[0][2]=picw,PicPos[0][3]=pich,1);
	m_pic1.MoveWindow(PicPos[1][0]=pic0x,PicPos[1][1]=pic0y+1*picdy,PicPos[1][2]=picw,PicPos[1][3]=pich,1);
	m_pic2.MoveWindow(PicPos[2][0]=pic0x,PicPos[2][1]=pic0y+2*picdy,PicPos[2][2]=picw,PicPos[2][3]=pich,1);
	m_pic3.MoveWindow(PicPos[3][0]=pic0x,PicPos[3][1]=pic0y+3*picdy,PicPos[3][2]=picw,PicPos[3][3]=pich,1);
	m_pic4.MoveWindow(PicPos[4][0]=pic0x,PicPos[4][1]=pic0y+4*picdy,PicPos[4][2]=picw,PicPos[4][3]=pich,1);
	m_pic5.MoveWindow(PicPos[5][0]=pic0x,PicPos[5][1]=pic0y+5*picdy,PicPos[5][2]=picw,PicPos[5][3]=pich,1);
	m_pic6.MoveWindow(PicPos[6][0]=pic0x,PicPos[6][1]=pic0y+6*picdy,PicPos[6][2]=picw,PicPos[6][3]=pich,1);
	m_pic7.MoveWindow(PicPos[7][0]=pic0x,PicPos[7][1]=pic0y+7*picdy,PicPos[7][2]=picw,PicPos[7][3]=pich,1);
	m_pic8.MoveWindow(PicPos[8][0]=pic0x,PicPos[8][1]=pic0y+8*picdy,PicPos[8][2]=picw,PicPos[8][3]=pich,1);
	m_pic9.MoveWindow(PicPos[9][0]=pic0x,PicPos[9][1]=pic0y+9*picdy,PicPos[9][2]=picw,PicPos[9][3]=pich,1);

	m_picm0.MoveWindow(PicPos[10][0]=picm0x,        PicPos[10][1]=picm0y,        PicPos[10][2]=picmw,PicPos[10][3]=picmh,1);
	m_picm1.MoveWindow(PicPos[11][0]=picm0x+picmw+2,PicPos[11][1]=picm0y,        PicPos[11][2]=picmw,PicPos[11][3]=picmh,1);
	m_picm2.MoveWindow(PicPos[12][0]=picm0x,        PicPos[12][1]=picm0y+picmh+2,PicPos[12][2]=picmw,PicPos[12][3]=picmh,1);
	m_picm3.MoveWindow(PicPos[13][0]=picm0x+picmw+2,PicPos[13][1]=picm0y+picmh+2,PicPos[13][2]=picmw,PicPos[13][3]=picmh,1);

	backupx0 = picm0x + picmw + 2 + picmw;
	m_picl.MoveWindow(PicPos[14][0]=Gwinx, PicPos[14][1] = Gwiny, PicPos[14][2] = Gwinw, PicPos[14][3] = Gwinh,1);
	
	m_moview.MoveWindow(Gwinx,Gwiny,Gwinw,Gwinh,1);
}

BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam)
{
  DWORD dwThreadId, dwProcessId;

  dwThreadId = GetWindowThreadProcessId(hwnd, &dwProcessId);
  if (dwProcessId == (DWORD)lParam) {
    PostMessage(hwnd, WM_CLOSE, 0, 0);
  }

  return TRUE;
}


void CCapENT2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(CapENTmode==CaptMode){
		if(IsFile(lastrecfn))f2gomi(lastrecfn);
	}
	Del21xx_Datafile();
	SaveCon();
	usbio232=-1;//usbiothread 終了	
//	SetUSBIOenter(0);
}
UINT CCapENT2Dlg::CaptureThread(LPVOID pParam)
{
	((CCapENT2Dlg*)pParam)->CaptureThread();
	return 0;
}
void CCapENT2Dlg::CaptureThread(void)
{//capturethreadではデインターレースは使用しない
	bool capdevice=true;
	int errorcnt=0;
	CDC* pDC=GetDC();
	char fn[301],buf[301];
	static int captime;
	SetTimer(1, 100, NULL);
	time_t now=time(NULL);
	struct tm tms;
	struct tm* tmp=&tms;
	localtime_s(tmp,&now);
	sprintf_s(fn,"%s\\gazou\\%i\\%08d%i%02i%02i%02i%02i%02i.wmv",CurDir,tmp->tm_year+1900,IDnum,tmp->tm_year+1900+100,tmp->tm_mon+1,tmp->tm_mday,tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
	strcpy_s(lastrecfn,fn);
	m_CaploopEnable = true;
	VideoCapture capture(Para0(CAME));//デバイスのオープン
	capture.set(CV_CAP_PROP_FRAME_WIDTH, Para0(CSIZ));//ここで設定するのが良さそう
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, Para1(CSIZ));//ここで設定するのが良さそう
	captime = 0;
	if(!capture.isOpened()){
		capdevice=false;
		capture.release();
	}else{
		capdevice=true;
	}
	Mat frame;
	int start=timeGetTime();
	int recframenum=0;
	capturetime=0;
	if (capdevice == false) {
		if (ptxt[CAME][0] == '0') {
			m_pCaptureThread = NULL;
			ReleaseDC(pDC);
			MessageBox("no camera!!");
			CapENTmode = Disp4Mode;
			Invalidate(false);
			return;
		}
		else {
			m_pCaptureThread = NULL;
			ReleaseDC(pDC);
			sprintf_s(buf, "Camera Number: %s doesn't exist\n\nCamera Number -> 0", ptxt[CAME]);
			MessageBox(buf);
			strcpy_s(ptxt[CAME], "10");//OnClickedCamnum()で５より大きければ０にセットされる
//			OnClickedCamnum();
			return;
		}
	}

	int tw=capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int th=capture.get(CV_CAP_PROP_FRAME_HEIGHT);

	if (Para0(CSIZ) != tw||Para1(CSIZ)!=th){//frame.size().width) {
		sprintf_s(ptxt[CSIZ], "%d,%d", tw, th);// frame.size().width, frame.size().height);
		SetCtrlPos();// rect.right, rect.bottom);
		InvalidateRect(false);
	}

	VideoWriter rec(fn,CV_FOURCC('W','M','V','2'),Para0(FPSN),Size(Para0(CSIZ),Para1(CSIZ)));
	static int winw, winh;
	Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
	HDC whdc = pDC->GetSafeHdc();
	////////////////
	pDC->FillSolidRect(Gwinx,Gwiny,Gwinw,Gwinh,RGB(255,255,255));
	while (m_CaploopEnable) {
		if(!capdevice){
			errorcnt++;
			sprintf_s(buf,"Camera(%d) open error %d!",Para0(CAME),errorcnt);
			pDC->TextOutA(Gwinx+30,Gwiny+30,buf);
			pDC->TextOutA(Gwinx+30,Gwiny+55,"Push Stop-button or CameraNumber at the bottom right.");
			Sleep(100);
			continue;//camera_numの変更を行うかストップbuttonで抜ける
		}
		capturetime=timeGetTime()-start;
		capture >> frame;
		int rows,cols,step;
		uchar *data;
		
		rows=frame.rows;
		cols=frame.cols;
		step=frame.step;
		data=frame.data;

		localtime_s(tmp,&now);
		now=time(NULL);
		localtime_s(tmp,&now);
		if(strstr(ptxt[WRID],"1")||strstr(ptxt[WRCA],"1")){
			char buf[64];
			if(strstr(ptxt[WRCA],"1")){
				sprintf_s(buf, sizeof(buf), "%i/%02i/%02i", tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday);
				rectangle(frame,Point(Para0(CSIZ),21),Point(Para0(CSIZ)-147,0), CV_RGB (255,255,255),-1,CV_AA,0 );
				putText(frame, buf, Point(Para0(CSIZ)-147, 18), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
				sprintf_s(buf, sizeof(buf), "%02i:%02i:%02i",tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
				rectangle(frame,Point(Para0(CSIZ),Para1(CSIZ)+7-3),Point(Para0(CSIZ)-100,Para1(CSIZ)-18-3), CV_RGB (255,255,255),-1,CV_AA,0 );
				putText(frame, buf, Point(Para0(CSIZ)-100, Para1(CSIZ)-3), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
			}
			if(strstr(ptxt[WRID],"1")){
				sprintf_s(buf, sizeof(buf), "ID:%08d", IDnum);
				rectangle(frame,Point(142,21),Point(0,0), CV_RGB (255,255,255),-1,CV_AA,0 );
				putText(frame, buf, Point(1, 18), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
			}
		}
		////////////////////////////////
		if (winw != Gwinw || winh != Gwinh) {//変化したら
			Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
		}

		if (m_CaploopEnable == false)break;
		rec << frame;	//	画像をファイルへ書き込む
		if (strstr(ptxt[INTE], "1")) {//デインターレースは表示のみ。書き込み文字部分はそのまま
			for (int y = 20; y < rows - 20; y += 2) {
		//	for (int y = 0; y < rows - 2; y += 2) {
					for (int x = 0; x < cols; x++) {
					// Blue
					data[(y + 1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0] + data[(y + 2) * step + x * 3 + 0]) / 2;
					// Green
					data[(y + 1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1] + data[(y + 2) * step + x * 3 + 1]) / 2;
					// Red
					data[(y + 1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2] + data[(y + 2) * step + x * 3 + 2]) / 2;
					//Reserved
					//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}
			for (int y = 0; y < 18; y += 2) {
				//	for (int y = 0; y < rows - 2; y += 2) {
				for (int x = 142; x < cols-147; x++) {
					// Blue
					data[(y + 1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0] + data[(y + 2) * step + x * 3 + 0]) / 2;
					// Green
					data[(y + 1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1] + data[(y + 2) * step + x * 3 + 1]) / 2;
					// Red
					data[(y + 1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2] + data[(y + 2) * step + x * 3 + 2]) / 2;
					//Reserved
					//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}
			for (int y = rows - 20; y < rows - 2; y += 2) {
				//	for (int y = 0; y < rows - 2; y += 2) {
				for (int x = 0; x < cols - 100; x++) {
					// Blue
					data[(y + 1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0] + data[(y + 2) * step + x * 3 + 0]) / 2;
					// Green
					data[(y + 1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1] + data[(y + 2) * step + x * 3 + 1]) / 2;
					// Red
					data[(y + 1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2] + data[(y + 2) * step + x * 3 + 2]) / 2;
					//Reserved
					//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}

		}
		BMat = frame;
		BITMAPINFO bitInfo;
		bitInfo.bmiHeader.biBitCount = 24;
		bitInfo.bmiHeader.biWidth = BMat.cols; //the bitmap is a bottom-up DIB and its origin is the lower-left corner.
		bitInfo.bmiHeader.biHeight = -BMat.rows; //If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
		bitInfo.bmiHeader.biPlanes = 1;
		bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo.bmiHeader.biCompression = BI_RGB;
		bitInfo.bmiHeader.biClrImportant = 0;
		bitInfo.bmiHeader.biClrUsed = 0;
		bitInfo.bmiHeader.biSizeImage = 0;
		bitInfo.bmiHeader.biXPelsPerMeter = 0;
		bitInfo.bmiHeader.biYPelsPerMeter = 0;
		//if (Para0(FLSP) == 0)
		pDC->SetStretchBltMode(HALFTONE);//一回設定するとそのままの様
		StretchDIBits(
			whdc,
			Gwinx, Gwiny,
			Gwinw, Gwinh,//matSize.width, matSize.height,
			0, 0,
			BMat.cols, BMat.rows,
			BMat.data,
			&bitInfo,
			DIB_RGB_COLORS,
			SRCCOPY
		);

		if (CaptureNowf) {
			if (capturetime - captime > 1000) {
				sprintf_s(buf, "%s\\gazou\\%i\\%08d%i%02i%02i%02i%02i%02i.jpg", CurDir, tmp->tm_year + 1900, IDnum, tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
				imwrite(buf, frame);
				PutOne2(buf);//to CurPics & alldata
				captime = timeGetTime() - start;
			}
			CaptureNowf=false;
		}
		recframenum++;
		if(recframenum>30*60*60){
			m_CaploopEnable=false;
			break;
		}
	}
	m_pCaptureThread=NULL;
	m_moview.ReleaseDC(pDC);
}

bool IsFile(char *fn)//folderでもtrueで戻る
{
	struct stat st;
	if (strstr(fn, ".jpg") || strstr(fn, ".wmv") || strstr(fn, ".avi") || strstr(fn, ".xlsx") || strstr(fn, ".docm")) {
		if (stat(fn, &st) != 0)return false;
		return true;
	}
	return false;
}
//bool isfile(char *fn){//IsFile()だと2GBのファイルはチェックできない。
//CFileFind find;

//	if (find.FindFile(fn)) {
//		return true;
	// ファイルが存在
//	}
//	return false;
//}

void CCapENT2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1){//100msecごと
		static int cnt=0;
		cnt++;

		if(CapENTmode==PlayMode){//play
			DispSlider(1);
			DispTimeTrim();
			if(OnPaintf){
				OnPaintf=false;
				Disp10Pics(PicsOffset);
			}
		}else if(CapENTmode==CaptMode){//capture
			DispTimeTrim();
			if(OnPaintf){
				OnPaintf=false;
				Disp10Pics(PicsOffset);
			}
			if(KillRecordCnt>0){//capture
				if(!m_pCaptureThread){
					KillRecordCnt--;//=false;
					if(KillRecordCnt==0){
						if(IsFile(lastrecfn))f2gomi(lastrecfn);
						m_pCaptureThread = AfxBeginThread(CaptureThread,this);
					}
				}
			}
		}else if(CapENTmode==Disp4Mode){
			if(OnPaintf){
				OnPaintf=false;
				Disp4Pics(1+2+4+8);
				Disp10Pics(PicsOffset);
			}
		}else if(CapENTmode==Disp1Mode){
			if(OnPaintf){
				OnPaintf=false;
				DispLPic(CurPicL);// DispPics(1+2+4+8);
				Disp10Pics(PicsOffset);
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CCapENT2Dlg::OnBnClickedStopcap()
{

//	SetUSBIOenter(0);
	usbio232=-1;//usbiothread 終了	

	SetButtons(CapENTmode=PlayMode);
	m_CaploopEnable=false;
	sliderf=0;
	trimposa=0;
	trimposb=slidew;
	currentframe=0;
	strcpy_s(playingfn,300,lastrecfn);
	Sleep(100);
	PutOne2(playingfn);
	DispOneFrame(playingfn,0);
	Sleep(100);	
	DispSlider(2);
	Sleep(500);

	moviepausef = false;
	m_pPlayThread = AfxBeginThread(PlayThread, this);

}
void SetEN(char *path,char *fullpath,int mode)//1:path 2:2017\path 0:.....\2017￥
{
	int i;
	char buf[301];
	if(strlen(fullpath)==0){
		strcpy_s(path,50,"");
		return;
	}
	for(i=strlen(fullpath);i>0;i--){
		if(fullpath[i]=='\\')break;
	}
	strcpy_s(path,50,&fullpath[i+1]);
	if(mode==1)return;//1234567820170603121212.jpg
	strcpy_s(path,50,&fullpath[i-4]);
	if(mode==2)return;//2017\1234....jpg
	strcpy_s(buf,fullpath);
	buf[strlen(buf)-strlen(path)+5]='\0';
	strcpy_s(path,300,buf);//c:\??????\gazou\2017￥
}


void CCapENT2Dlg::OnBnClickedCancel()
{
	m_CaploopEnable=false;
	m_PlayloopEnable=false;
	m_PrevloopEnable=false;
	Sleep(300);
	CDialogEx::OnCancel();
}


void CCapENT2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	InvalidateRect(false);
	// TODO: ここにメッセージ ハンドラー コードを追加します。
}
UINT CCapENT2Dlg::PlayThread(LPVOID pParam)
{
	((CCapENT2Dlg*)pParam)->PlayThread();
	return 0;
}

void DispPlaySankaku(CDC* pDC, int x0, int y0,int s)//三角を表示する位置(x0,y0)、大きさsize
{
	int i;
	for (i = 0; i<s; i++) {
		pDC->FillSolidRect( x0, y0 - s + i, 2 * i, 1, RGB(200, 200, 200));
	}
	for (i = 0; i<s; i++) {
		pDC->FillSolidRect( x0, y0      + i, 2 * (s - i), 1, RGB(200, 200, 200));
	}

}

void CCapENT2Dlg::PlayThread()
{
	CDC* pDC=m_moview.GetDC();
	bool atendpos = false;
	SetTimer(1, 100, NULL);
//	int capframenum;

	m_PlayloopEnable = true;
	VideoCapture capture(playingfn);

	Mat frame;
	int frame0;
	DWORD time0,time;
	time0=time=timeGetTime();
	maxframenum=capture.get(CV_CAP_PROP_FRAME_COUNT);
	frame0=0;
	///////////////
	static int winw, winh;
	Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
	HDC whdc = pDC->GetSafeHdc();
	////////////////
	while (m_PlayloopEnable) {
		static bool pausefchange=false;
		capture >> frame;

		if (frame.empty() || capture.get(CV_CAP_PROP_POS_AVI_RATIO) == 1 || atendpos) {
			if (atendpos) {
				SetFrame = currentframe = trimposa*maxframenum / slidew;
			}
			else {
				SetFrame = currentframe = 0;
			}
			atendpos = false;
			moviepausef = true;
			//	m_PlayloopEnable = false;
			//	break;
		}
		if(moviepausef){
			capture.set(CV_CAP_PROP_POS_FRAMES,SetFrame);
			frame0=SetFrame;
			pausefchange=true;
			Sleep(50);
		}else{
			if(pausefchange){
				time0=timeGetTime();
				pausefchange=false;
			}
		}

		currentframe=capture.get(CV_CAP_PROP_POS_FRAMES);
		if(m_PlayloopEnable==false)break;
		CBitmap m_bmp;
		int rows,cols,step;
		uchar *data;
		rows=frame.rows;
		cols=frame.cols;
		step=frame.step;
		data=frame.data;

//以前録画したジャギー映像を再生する時は以下を使うと良いかもしれない
/*		if(strstr(ptxt[INTE],"1")){//取りあえずこれ。
			for (int y = 0; y < rows-2; y+=2) {
				for (int x = 0; x < cols; x++) {
					// Blue
					data[(y+1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0]+data[(y+2) * step + x * 3 + 0])/2;
					// Green
					data[(y+1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1]+data[(y+2) * step + x * 3 + 1])/2;
					// Red
					data[(y+1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2]+data[(y+2) * step + x * 3 + 2])/2;
					//Reserved
//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}
		}
*/
		if (strstr(ptxt[INTE], "1")) {//デインターレースは表示のみ。書き込み文字部分はそのまま
			for (int y = 20; y < rows - 20; y += 2) {//この範囲は全体を処理（平均化）
				//	for (int y = 0; y < rows - 2; y += 2) {
				for (int x = 0; x < cols; x++) {
					// Blue
					data[(y + 1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0] + data[(y + 2) * step + x * 3 + 0]) / 2;
					// Green
					data[(y + 1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1] + data[(y + 2) * step + x * 3 + 1]) / 2;
					// Red
					data[(y + 1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2] + data[(y + 2) * step + x * 3 + 2]) / 2;
					//Reserved
					//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}
			for (int y = 0; y < 18; y += 2) {
				//	for (int y = 0; y < rows - 2; y += 2) {
				for (int x = 142; x < cols - 147; x++) {//IDと日付部分以外を処理
					// Blue
					data[(y + 1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0] + data[(y + 2) * step + x * 3 + 0]) / 2;
					// Green
					data[(y + 1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1] + data[(y + 2) * step + x * 3 + 1]) / 2;
					// Red
					data[(y + 1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2] + data[(y + 2) * step + x * 3 + 2]) / 2;
					//Reserved
					//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}
			for (int y = rows - 20; y < rows - 2; y += 2) {
				//	for (int y = 0; y < rows - 2; y += 2) {
				for (int x = 0; x < cols - 100; x++) {//時分秒以外を処理
					// Blue
					data[(y + 1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0] + data[(y + 2) * step + x * 3 + 0]) / 2;
					// Green
					data[(y + 1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1] + data[(y + 2) * step + x * 3 + 1]) / 2;
					// Red
					data[(y + 1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2] + data[(y + 2) * step + x * 3 + 2]) / 2;
					//Reserved
					//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}
		}
		DWORD wait;
		if(!moviepausef){
			wait=(currentframe-frame0)*333/10-(timeGetTime()-time0);
			if(wait>0&&wait<300)Sleep(wait);
		}

		if (currentframe<trimposb*maxframenum / slidew||moviepausef) {
			////////////////////////////////
			if (winw != Gwinw || winh != Gwinh) {//変化したら
				Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
			}
			BMat = frame;
			BITMAPINFO bitInfo;
			bitInfo.bmiHeader.biBitCount = 24;
			bitInfo.bmiHeader.biWidth = BMat.cols; //the bitmap is a bottom-up DIB and its origin is the lower-left corner.
			bitInfo.bmiHeader.biHeight = -BMat.rows; //If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
			bitInfo.bmiHeader.biPlanes = 1;
			bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bitInfo.bmiHeader.biCompression = BI_RGB;
			bitInfo.bmiHeader.biClrImportant = 0;
			bitInfo.bmiHeader.biClrUsed = 0;
			bitInfo.bmiHeader.biSizeImage = 0;
			bitInfo.bmiHeader.biXPelsPerMeter = 0;
			bitInfo.bmiHeader.biYPelsPerMeter = 0;
			pDC->SetStretchBltMode(HALFTONE);//一回設定するとそのままの様
			StretchDIBits(
				whdc,
				0, 0,
				Gwinw, Gwinh,//matSize.width, matSize.height,
				0, 0,
				BMat.cols, BMat.rows,
				BMat.data,
				&bitInfo,
				DIB_RGB_COLORS,
				SRCCOPY
			);
		}
		else {
			atendpos = true;
		}

		if(moviepausef){
			DispPlaySankaku(pDC, 30, Gwinh-50,20);
		}
	//	capframenum = 0;
		if(CaptureNowf){//&&capframenum!=currentframe){//直前をチェックしても、同じframeをキャプチャーしていないかをチェックしたことにはならない。あきらめることとする。
			char playcapfn[301];
			SetPlayCapfn(playcapfn,playingfn,currentframe);
			//2017\\1234567821xx?????と続いている場合は21xxを20xxに変更
			//SetPlayCapfn()で対処
			imwrite(playcapfn, frame);
			PutOne2(playcapfn);//to CurPics & alldata
			CaptureNowf=false;
		//	capframenum=currentframe;
		}
	}
	m_pPlayThread=NULL;
	m_moview.ReleaseDC(pDC);
	DispOneFrame(playingfn,0);
}

void CCapENT2Dlg::DispOneFrame(char* fn, int fnumber)
{
	CDC* pDC=m_moview.GetDC();
	BITMAP bm;
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);   // pDCとコンパチブルなデバイスコンテキストを作成

	VideoCapture capture(fn);

	Mat frame;
	maxframenum=capture.get(CV_CAP_PROP_FRAME_COUNT);
	if(fnumber>=maxframenum-1)fnumber=maxframenum-1;
	capture.set(CV_CAP_PROP_POS_FRAMES,fnumber);
	capture >> frame;
	CBitmap m_bmp;
	int rows,cols,step;
	uchar *data;
	rows=frame.rows;
	cols=frame.cols;
	step=frame.step;
	data=frame.data;
	char* ColorBuf = (char*)calloc(rows * rows * 4, sizeof(RGBQUAD));
		
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			// Blue
			ColorBuf[y * cols * 4 + x * 4 + 0] = data[y * step + x * 3 + 0];
			// Green
			ColorBuf[y * cols * 4 + x * 4 + 1] = data[y * step + x * 3 + 1];
			// Red
			ColorBuf[y * cols * 4 + x * 4 + 2] = data[y * step + x * 3 + 2];
			//Reserved
			ColorBuf[y * cols * 4 + x * 4 + 3] = 0;
		}
	}
  	m_bmp.CreateBitmap(frame.cols, frame.rows, 1, 32, ColorBuf);
	free(ColorBuf);
	m_bmp.GetObject(sizeof(BITMAP),&bm);
	dcMem.SelectObject(&m_bmp);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,Gwinw,Gwinh,&dcMem,0,0, bm.bmWidth, bm.bmHeight,SRCCOPY);
	DispPlaySankaku(pDC, 30, Gwinh - 50,20);
	m_moview.ReleaseDC(pDC);
	DeleteDC(dcMem);
}

void CCapENT2Dlg::PlayMovie(void)
{
	if(CapENTmode==PlayMode){
		if(m_pPlayThread){//!=NULL){
			if(!moviepausef){//SetFrame<0){
				if(currentframe>maxframenum-2)SetFrame=0;
				else SetFrame=currentframe;
				moviepausef=true;
			}else{
				moviepausef=false;//SetFrame=-1;
			}
		}else{
			if(strlen(playingfn)<3||!IsFile(playingfn))return;
			sliderf=0;
			currentframe=0;
			DispSlider(1);
			moviepausef=false;
			m_pPlayThread = AfxBeginThread(PlayThread,this);
		}
	}else if(CapENTmode==Disp4Mode){
		if(!checkavifn(listaviselected))return;
		SetButtons(CapENTmode=PlayMode);
		strcpy_s(playingfn,300,listaviselected);
		sliderf=0;
		trimposa=0;
		trimposb=slidew;
		currentframe=0;
		DispSlider(1);
		moviepausef=false;
		m_pPlayThread = AfxBeginThread(PlayThread,this);
	}
}

void Setfn2iddate(char *fn,char *iddate)
{
	int id,y,m,d,h,M,s;
	char buf[51];
	sscanf_s(fn,"%08d%04d%02d%02d%02d%02d%02d%s",&id,&y,&M,&d,&h,&m,&s,buf,50);
	sprintf_s(iddate,200,"%08d %04d-%02d-%02d %02d:%02d",id,y,M,d,h,m);
}

int checkslider(int x,int y)//0-slidew -2:video -1:それ以外の場所
{
	if(y>=slidey-20&&y<slidey+slideh+20){//{pos.y<=(Y0+HE+35)){
		if(x>=slidex-15&&x<=slidex+15+slidew){//(X0+WI+15)){
			if(x<slidex)return 0;
			else if(x>slidex+slidew)return slidew;
			else return x-slidex;
		}
	}else if(x>Gwinx&&x<Gwinx+Gwinw&&y>Gwiny&&y<Gwiny+Gwinh){
		return -2;
	}
	return -1;
}
bool checkavifn(char *fn)
{
	if(strlen(fn)<20)return false;
	if(strlen(fn)>300)return false;
	if(!(strstr(fn,".avi")||strstr(fn,".wmv")))return false;
	return true;
}


void drawmaru(CDC* pDC,DWORD co,int cx,int cy,int r)
{
	CPen pen(PS_SOLID,1,co);
	CBrush pen_br(co);
	CPen* oldpen=pDC->SelectObject(&pen);
	CBrush* oldbr=pDC->SelectObject(&pen_br);
	CRect rect;
	rect.top=cy-r;
	rect.left=cx-r;
	rect.bottom=cy+r;
	rect.right=cx+r;
	pDC->Ellipse(&rect);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbr);
	return;
}

void CCapENT2Dlg::DispTimeTrim(void)
{
	int i,ct,x,x0=172-15,y0=46,dx=18,dy=21;
	char buf[100];
	CDC MemDC;
	CDC *pDC=m_timetrim.GetDC();
	CBitmap *pOldBmp,m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
//	if(m_CaploopEnable&&CapENTmode==CaptMode){//capture
	if(CapENTmode==CaptMode){//capture
		ct=capturetime/1000;
		if(ct%2){
			drawmaru(pDC,RGB(255,0,0),Gwinw/2-13,7+5,7);
		}else{
			drawmaru(pDC,RGB(240,240,240),Gwinw/2-13,7+5,7);
			//pDC->FillSolidRect(Gwinw/2-10,0,20,20,grayRGB);//(255,0,0));
		}
		sprintf_s(buf,"%02d:%02d",ct/60,ct%60);
		for(i=0;i<strlen(buf);i++){
			if(buf[i]>='0'&&buf[i]<='9'){
				x=(buf[i]-'0')*dx+x0;
			}else if(buf[i]=='.'){
				x=10*dx+x0;
			}else if(buf[i]==':'){
				x=11*dx+x0;
			}else if(buf[i]=='-'){
				x=12*dx+x0;
			}else if(buf[i]=='/'){
				x=13*dx+x0;
			}else x=14*dx+x0;
			pDC->BitBlt(i*(dx),0,dx,dy,&MemDC,x,y0,SRCCOPY);
		}
	}else if(CapENTmode==PlayMode){//m_PlayloopEnable){
		pDC->FillSolidRect(100,0,50,20,grayRGB);
		sprintf_s(buf,"%02d:%02d/%02d:%02d",currentframe/Para0(FPSN)/60,(currentframe/Para0(FPSN))%60,maxframenum/Para0(FPSN)/60,(maxframenum/Para0(FPSN))%60);
//		drawmaru(pDC,grayRGB,Gwinw/2,7,4);//赤丸を消す
		for(i=0;i<strlen(buf);i++){
			if(buf[i]>='0'&&buf[i]<='9'){
				x=(buf[i]-'0')*dx+x0;
			}else if(buf[i]=='.'){
				x=10*dx+x0;
			}else if(buf[i]==':'){
				x=11*dx+x0;
			}else if(buf[i]=='-'){
				x=12*dx+x0;
			}else if(buf[i]=='/'){
				x=13*dx+x0;
			}else x=14*dx+x0;
			pDC->BitBlt(i*(dx),0,dx,dy,&MemDC,x,y0,SRCCOPY);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
		}
//		drawmaru(pDC,grayRGB,Gwinw/2,7,4);//赤丸を消す
/*		sprintf_s(buf,"%02d:%02d",maxframenum/Para0(FPSN)/60,(maxframenum/Para0(FPSN))%60);
		for(i=0;i<strlen(buf);i++){
			if(buf[i]>='0'&&buf[i]<='9'){
				x=(buf[i]-'0')*dx+x0;
			}else if(buf[i]=='.'){
				x=10*dx+x0;
			}else if(buf[i]==':'){
				x=11*dx+x0;
			}else if(buf[i]=='-'){
				x=12*dx+x0;
			}else if(buf[i]=='/'){
				x=13*dx+x0;
			}else x=14*dx+x0;
			pDC->BitBlt((i+6)*(dx),0,dx,dy,&MemDC,x,y0,SRCCOPY);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
		}*/
	}else{
		pDC->FillSolidRect(0,0,Gwinw,dy,grayRGB);
	}
	m_timetrim.ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void SetPlayCapfn(char *playcapfn,char *playingfn,int currentframe)
{//21xx年というwmvのこともあるのでyear部分は年号フォルダからモラル
//void SetEN(char *path,char *fullpath,int mode)//1:path 2:2017￥path 0:.....￥2017￥
	int i,id,y,mo,d,h,m,s,damy,ns;
	char b[301];
	CTimeSpan cts(0,0,0,1);//1second
	SetEN(b,playingfn,2);
	b[4]='\0';
	sscanf_s(b,"%d",&y);
	SetEN(b,playingfn,1);
	if(strlen(b)==26)sscanf_s(b,"%08d%04d%02d%02d%02d%02d%02d.wmv",&id,&damy,&mo,&d,&h,&m,&s);
	else sscanf_s(b, "%06d%04d%02d%02d%02d%02d%02d.wmv", &id, &damy, &mo, &d, &h, &m, &s);
	CTime ct(y,mo,d,h,m,s);
	ns=currentframe/Para0(FPSN);
	if(ns==0)ns=1;
	for(i=0;i<ns;i++)ct+=cts;//1secを加える
	SetEN(b,playingfn,0);
	while(1){
		sprintf_s(playcapfn,300,"%s%08d%04d%02d%02d%02d%02d%02d.jpg",b,id,
			y=ct.GetYear(),mo=ct.GetMonth(),d=ct.GetDay(),h=ct.GetHour(),m=ct.GetMinute(),s=ct.GetSecond());
		if(!IsFile(playcapfn))break;
		ct+=cts;
	}
}

void CCapENT2Dlg::SetTrimName(char *tfn,char *pfn,int n)
{//21xx年というwmvのこともあるのでyear部分は年号フォルダからモラル
	int i,id,y,mo,d,h,m,s,damy,ns;
	char b[301];
	//CTime ct;
	CTimeSpan cts(0,0,0,1);//1second
	SetEN(b,pfn,2);
	b[4]='\0';
	sscanf_s(b,"%d",&y);
	SetEN(b,pfn,1);
	sscanf_s(b,"%08d%04d%02d%02d%02d%02d%02d.wmv",&id,&damy,&mo,&d,&h,&m,&s);
	CTime ct(y,mo,d,h,m,s);
	ns=n*maxframenum/slidew/Para0(FPSN);//currentframe/Para0(FPSN);
	if(ns==0)ns=1;
	for(i=0;i<ns;i++)ct+=cts;//1secを加える
	SetEN(b,pfn,0);
	while(1){
		sprintf_s(tfn,300,"%s%08d%04d%02d%02d%02d%02d%02d.wmv",b,id,
			y=ct.GetYear(),mo=ct.GetMonth(),d=ct.GetDay(),h=ct.GetHour(),m=ct.GetMinute(),s=ct.GetSecond());
		if(!IsFile(tfn))break;
		ct+=cts;
	}
}

void CCapENT2Dlg::OnBnClickedCutmovie()
{
//	if(m_TrimloopEnable)return;
	if(!strstr(playingfn,".wmv"))return;//.wmv でなければ、今のところtrim不能
	if(!m_PlayloopEnable){
		if(!IsFile(playingfn))return;
		moviepausef=false;
		m_pPlayThread = AfxBeginThread(PlayThread,this);
	}
	if (trimposb == slidew&&trimposa == 0) {
		char b[301];
		strcpy_s(b, playingfn);
		if (b[strlen(b) - 17] == '1') {//21xxの場合は20xxにrenameするだけ
			m_PlayloopEnable = false;
			//CopyFile(playingfn, b, FALSE);
			Sleep(200);
			b[strlen(b) - 17] = '0';
			CopyFile(playingfn, b, FALSE);
			PutOne2(b);
		}
		else {//20xxの場合はそのまま戻る
			MessageBox("same length ?");//
		}
	}
	else {
		CTrimChan dlg;
		SetTrimName(trimingfn, playingfn, trimposa);
		strcpy_s(dlg.fn1, playingfn);
		strcpy_s(dlg.fn2, trimingfn);
		dlg.m_posa = trimposa;
		dlg.m_posb = trimposb;
		if (dlg.DoModal() == IDOK) {
			Sleep(300);
			PutOne2(trimingfn);
		}
		else {
			Sleep(300);
			if (IsFile(trimingfn))CFile::Remove(trimingfn);
		}
	}
}
/*
int CheckPicPos(int mode, int x, int y)//書き換える必要あり
//0-9 thumbnail
//10-13(picm mode:3) 
//14 picl
//chanid 15//削除
//delete 16
//refer 17
//setid 20
//deint 21
//stillcap 22
//cutmovie 23
//deint 24
//deinton 25
//record 26
{
	int i , j;
	if (mode == CaptMode)return -1;
	j = 16;//deleteならそれを返す
	if (x >= PicPos[j][0] && y >= PicPos[j][1] && x < PicPos[j][0] + PicPos[j][2] && y < PicPos[j][1] + PicPos[j][3]) {
		return j;
	}
	for(i=0;i<10;i++){//0-9ならそれを返す
		if (x >= PicPos[i][0] && y >= PicPos[i][1] && x < PicPos[i][0] + PicPos[i][2] && y < PicPos[i][1] + PicPos[i][3]) {
				return i;
		}
	}
	if (mode == PlayMode || mode == Disp1Mode) {//一枚表示なら
		j = 14;
		if (x >= PicPos[j][0] && y >= PicPos[j][1] && x < PicPos[j][0] + PicPos[j][2] && y < PicPos[j][1] + PicPos[j][3]) {
			return j;
		}
	}
	for(i = 10; i < 14; i++) {//4枚表示なら
		if (x >= PicPos[i][0] && y >= PicPos[i][1] && x < PicPos[i][0] + PicPos[i][2]  && y < PicPos[i][1] + PicPos[i][3] ) {
			return i;
		}
	}
	return -1;
}*/
int CheckPicPos(int mode, int x, int y)//書き換える必要あり
//0-9 thumbnail
//10-13(picm mode:3) 
//14 picl
//chanid 15//削除
//delete 16
//refer 17
//setid 20
//deint 21
//stillcap 22
//cutmovie 23
//deint 24
//deinton 25
//record 26
{
	int i, r = -1;
	if (mode == CaptMode)return -1;
	if (mode == PlayMode) {
		for (i = 21; i < 27; i++) {
			if (x >= PicPos[i][0] && y >= PicPos[i][1] && x < PicPos[i][0] + PicPos[i][2] && y < PicPos[i][1] + PicPos[i][3]) {
				return i;
			}
		}
	}
	for (i = 0; i < 21; i++) {
		if (i == 15)continue;
		if (i > 16 && i < 21)continue;

		if (x >= PicPos[i][0] && y >= PicPos[i][1] && x < PicPos[i][0] + PicPos[i][2] && y < PicPos[i][1] + PicPos[i][3]) {
			r = i;
			break;
		}
	}
	if (mode == PlayMode || mode == Disp1Mode || mode == CaptMode) {//これらのモードの時はPICLをチェック
		i = 14;
		if (x >= PicPos[i][0] && y >= PicPos[i][1] && x < PicPos[i][0] + PicPos[i][2] && y < PicPos[i][1] + PicPos[i][3]) {
			r = i;
		}
	}
	return r;
}
bool handonf = false;
BOOL CCapENT2Dlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		switch(pMsg->wParam) {
			case VK_RETURN:
				if(CapENTmode==CaptMode||CapENTmode==PlayMode){
					CaptureNowf=true;
					return true;
				}
				return false;
			case VK_SPACE:
				if(CapENTmode==PlayMode){
					PlayMovie();
				}
				else if (CapENTmode == CaptMode) {
					if (strstr(ptxt[INTE], "1")) {
						strcpy_s(ptxt[INTE], "0");
	//					DispIroiro(&m_deinter, 1, 1, 31, 29, 428, 36, 7, SRCCOPY);
					}
					else {
						strcpy_s(ptxt[INTE], "1");
		//				DispIroiro(&m_deinter, 1, 1, 31, 29, 428, 3, 6, SRCCOPY);
					}
				}
				return true;
			case VK_F1:
//				if (CapENTmode != CaptMode) {
				OnClickedRecord();
				//	OnBnClickedRecordbutton();// SetID();
					return true;
//				}
//				break;
			case VK_F2:
				if (CapENTmode == CaptMode) {
					OnBnClickedStopcap();
				}
				else if (CapENTmode == Disp4Mode||CapENTmode==Disp1Mode) {
//void SetEN(char *path,char *fullpath,int mode)//1:path 2:2017\path 0:.....\2017￥
					char buf[60];
					if (IsFile(lastrecfn)) {
						SetEN(buf, lastrecfn, 2);
						PlayDispPic(buf);
					}
				}
				return true;
			case VK_F3:
				if (CapENTmode == CaptMode) {
					m_CaploopEnable = false;

					sliderf = 0;
					trimposa = 0;
					trimposb = slidew;
					currentframe = 0;
					strcpy_s(playingfn, 300, lastrecfn);
					Sleep(100);
					PutOne2(playingfn);
					DispOneFrame(playingfn, 0);
					Sleep(100);

					Disp4Pics(1 + 2 + 4 + 8);
					CapENTmode = Disp4Mode;
				}
				else if (CapENTmode == PlayMode || CapENTmode == Disp1Mode) {
					m_PlayloopEnable = false;
					Disp4Pics(1 + 2 + 4 + 8);
					CapENTmode = Disp4Mode;
				}
				return true;
//			case VK_F4:
	//			if (CapENTmode == CaptMode) {
		//			if (Para0(FLSP) == 0)strcpy_s(ptxt[FLSP], "1");
			//		else strcpy_s(ptxt[FLSP], "0");
			//		return true;
			//	}
			//	break;
			case VK_LEFT:
				if (CapENTmode == PlayMode) {
					PlayMovie();
					SetFrame = currentframe - 1;
					if (SetFrame<0)SetFrame = 1;
					moviepausef = true;
				}
				return true;
			case VK_RIGHT:
				if (CapENTmode == PlayMode) {
					PlayMovie();
					SetFrame = currentframe +1;
					if (SetFrame>maxframenum)SetFrame = maxframenum - 5;
					moviepausef = true;
				}
				return true;
			case VK_DOWN:
				if (CapENTmode == PlayMode) {
					PlayMovie();
					SetFrame = currentframe - maxframenum / 10;
					if (SetFrame<0)SetFrame = 1;
					moviepausef = true;
				}
				return true;
			case VK_UP:
				if (CapENTmode == PlayMode) {
					PlayMovie();
					SetFrame = currentframe + maxframenum / 10;
					if (SetFrame>maxframenum)SetFrame = maxframenum - 5;
					moviepausef = true;
				}
				return true;
			case VK_ESCAPE:
				return true;
			case VK_BACK:
				return true;
			default:
				break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCapENT2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(handonf){
		if(CheckPicsflagfn(picsflag)){
			HCURSOR hCursor = LoadCursor( NULL, IDC_HAND );     // 砂時計カーソル
			SetCursor( hCursor );//IDC_ARROW
		}
	}
#ifdef _DEBUG
	CDC *pDC = GetDC();
	char buf[100];
	sprintf_s(buf, "%05d:%05d", point.x, point.y);
	pDC->TextOutA(10, 10, buf);
	ReleaseDC(pDC);
#endif
	if(CapENTmode==PlayMode){
	//	CPoint point;
	//	point.x = pMsg->pt.x;
	//	point.y = pMsg->pt.y;
		ScreenToClient(&point);
	//	picsflag = -1;
		int x=checkslider(point.x,point.y);
		if(sliderf==2){//三角マーク以外
			if(x>=0){
				if(x*maxframenum/slidew>=maxframenum)SetFrame=maxframenum-1;//かたまりそう？
				else SetFrame=x*maxframenum/slidew;
			}else{
				sliderf=0;
			}
		}else if(sliderf==1){//左三角マーク
			if(x>=0){
				if(x+sankakuzure<trimposb-20)trimposa=x+sankakuzure;
				else trimposa=trimposb-20;
				if(trimposa<0)trimposa=0;

				if (x*maxframenum / slidew >= maxframenum)SetFrame = maxframenum - 1;//かたまりそう？
				else SetFrame = x*maxframenum / slidew;

			}else{
				sliderf=0;
			}
		}else if(sliderf==3){//右三角マーク
			if(x>=0){
				if(x+sankakuzure>trimposa+20)trimposb=x+sankakuzure;
				else trimposb=trimposa+20;

				if (x*maxframenum / slidew >= maxframenum)SetFrame = maxframenum - 1;//かたまりそう？
				else SetFrame = x*maxframenum / slidew;



			}else{
				sliderf=0;
			}
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void f2gomi(char *gomi)//ここに来るときはファイルの存在をチェックしておくこと。void f2gomi(HWND hwnd,char *gomi)
{
	char	buf[513];
//	if (!isfile(gomi)) {
//		sprintf_s(buf, "%s can't be found.",gomi);
//		AfxMessageBox(buf);
//		return;
//	}
	SHFILEOPSTRUCT	fo;
	fo.hwnd = NULL;//hwnd;
	fo.wFunc = FO_DELETE;
	strcpy_s(buf,512,gomi);
	buf[strlen(buf)+1] = 0;
	fo.pFrom = buf;
	fo.pTo = 0;
	fo.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI;
	if (SHFileOperation(&fo)) {
		sprintf_s(buf, "%s can't be deleted.",gomi);
		AfxMessageBox(buf);
	}
}
void Del21xx_Datafile()
{
	CStdioFile fr;
	CFileFind find;
	char buf[100],fn[301];
	fr.Open(DATA_FN,CFile::modeRead|CFile::typeText);
	while(fr.ReadString(buf,99)){
		buf[strlen(buf)-1]='\0';
		if(buf[strlen(buf)-17]=='1'){
			sprintf_s(fn,"%s\\gazou\\%s",CurDir,buf);
			if(find.FindFile(fn))f2gomi(fn);//if (IsFile(fn))f2gomi(fn);//IsFile()だと2GBのファイルはチェックできない。
			else AfxMessageBox("? at del21xx_datafile");
		}
	}
	fr.Abort();
}
void Delfn_Datafile(char *fn1)//データファイルからfn1を削除
{
	CStdioFile fr,fw;
	char buf[100],fn[301],fndatafn[301],fntemp[301];
	sprintf_s(fndatafn, "%s\\%s", CurDir, DATA_FN);
	sprintf_s(fntemp, "%s\\%s", CurDir, "temp.txt");
	CopyFile(fndatafn, fntemp, FALSE);//上書き
	fr.Open(fntemp,CFile::modeRead|CFile::typeText);
	fw.Open(fndatafn,CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	strcpy_s(fn,&fn1[strlen(fn1)-31]);
	while(fr.ReadString(buf,99)){
		if(strstr(buf,fn)){
			continue;
		}
		fw.WriteString(buf);
	}
	fr.Abort();
	fw.Abort();
//	if(IsFile(fndatafn))CFile::Remove(fndatafn);
//	CFile::Rename(fntemp,fndatafn);
//	strcpy_s(fntemp, "");
}
void DelfnCurPics(char *fn1)
{
	int i,n;
	char fn[300];
	strcpy_s(fn,&fn1[strlen(fn1)-31]);
	for(i=0;strlen(CurPics[i])!=0;i++){
		if(strstr(fn,CurPics[i])){
			n=i;
			break;
		}
	}
	if(strlen(CurPics[i])==0){
		AfxMessageBox("DelfnCurPics error");
		return;
	}
	for(;strlen(CurPics[i])!=0;i++){
		strcpy_s(CurPics[i],CurPics[i+1]);
	}
	strcpy_s(CurPics[i],"");
	if(PicsOffset==n){
		PicsOffset--;
		if(PicsOffset<0)PicsOffset=0;
	}
}
bool picsflagnull(int fnn)//gazouを指していて、それがnullならtrue
{//画像を指していなければfalse
	if (fnn >= 0 && fnn < 10) {
		if (strlen(CurPics[picsflag + PicsOffset]) == 0)return true;
	}
	else if (fnn < 14 && fnn>9) {
		if (strlen(CurPics4[picsflag - 10]) == 0)return true;
	}
	else if (fnn == 14) {
		if (strlen(CurPicL) == 0)return true;
	}
	return false;
}
bool is2117file(int fnn)
{
	char fn[301];
	if (fnn >= 0 && fnn < 10) {
		sprintf_s(fn, "%s\\gazou\\%s", CurDir, CurPics[picsflag + PicsOffset]);
	}
	else if (fnn > 9 && fnn < 14) {
		sprintf_s(fn, "%s\\gazou\\%s", CurDir, CurPics4[picsflag - 10]);
	}
	else if (fnn == 14) {
		if (CapENTmode == Disp1Mode) {
			sprintf_s(fn, "%s\\gazou\\%s", CurDir, CurPicL);
		}
		else if (CapENTmode == PlayMode) {
			strcpy_s(fn, playingfn);
		}
	}
	if (fn[strlen(fn) - 17] == '1')return true;
	else return false;
}
void CCapENT2Dlg::DeletePic(int fnn)
{
	char fn[301],path[50];
	if(fnn>=0&&fnn<10){
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics[picsflag+PicsOffset]);
		if(strstr(fn,".wmv")){
			if(strstr(playingfn,fn)){//再生中のものなら
				m_PlayloopEnable=false;
				Sleep(200);
				if(CapENTmode==PlayMode)CapENTmode=Disp1Mode;
			}
		}
	}else if(fnn>9&&fnn<14){
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPics4[picsflag-10]);
	}else if(fnn==14){
		if(CapENTmode==Disp1Mode){
			sprintf_s(fn,"%s\\gazou\\%s",CurDir,CurPicL);
			strcpy_s(CurPicL,"");
		}else if(CapENTmode==PlayMode){
			strcpy_s(fn,playingfn);
			m_PlayloopEnable=false;
			Sleep(200);
			CapENTmode=Disp1Mode;
		}
	}else return;
	if (fn[strlen(fn) - 17] == '1') {
		MessageBox("一時ファイルです。\nプログラムを終了すると、自動的に削除されます。");// CurPics[i][strlen(CurPics[i] - 17)] == '1')
		return;
	}
	if(IsFile(fn))f2gomi(fn);
	Delfn_Datafile(fn);
	DelfnCurPics(fn);
	for(int i=0;i<4;i++){
		if(strstr(fn,CurPics4[i]))strcpy_s(CurPics4[i],"");
	}
	Disp10Pics(PicsOffset);
	if(CapENTmode==Disp4Mode)Disp4Pics(1+2+4+8);
	else if(CapENTmode==Disp1Mode)DispLPic("");
	SetEN(path, fn, 1);// 1:path 2 : 2017\path 0:.....\2017￥
	path[8] = 0;
	sprintf_s(fn,"%08d",IDnum);
	if (strstr(path, fn))idCnt--;
	allCnt--;
	DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
}


void CCapENT2Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnRButtonDown(nFlags, point);
}
void CCapENT2Dlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	int x;
	if((x=CheckPicPos(CapENTmode,point.x,point.y))!=-1){
		picsflag=x;
		if (CapENTmode == Disp1Mode||CapENTmode==PlayMode) {
			if (x > 9 && x < 14)goto onrend;
		}
		if (picsflagnull(picsflag))goto onrend;
		if (is2117file(x))goto onrend;
		if ((x >= 0 && x < 10) && CapENTmode > 0) {
			CMenu    *popupMenuP = NULL;
			CMenu    cMenu;
			int      err = 0;
			if (!err) if (!cMenu.LoadMenu(IDR_MENU7)) err = 1;
			if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
			if (!err) {
				if (!popupMenuP->TrackPopupMenu(
					TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
			}
			cMenu.DestroyMenu();
		}
		else if (CapENTmode == Disp1Mode || CapENTmode == Disp4Mode || CapENTmode == PlayMode) {

			CMenu    *popupMenuP = NULL;
			CMenu *popupMenuP1 = NULL;
			CMenu    cMenu;
			MENUITEMINFO mii = { sizeof(mii) };
			mii.fMask = MIIM_STRING;
			int      err = 0;
			if (!err) {
				if (CapENTmode == Disp4Mode) {
					if (!cMenu.LoadMenu(IDR_MENU1)) err = 1;
				}
				else {
					if (!cMenu.LoadMenu(IDR_MENU2)) err = 1;
				}
			}
			if (!err) if ((popupMenuP1 = cMenu.GetSubMenu(0)) == NULL) err = 1;
			if (!err){
	//			ClientToScreen(&point);

				popupMenuP = popupMenuP1->GetSubMenu(5);
				mii.dwTypeData = ptxt[REF0];
				popupMenuP->SetMenuItemInfoA(0, &mii, TRUE);
				mii.dwTypeData = ptxt[REF1];
				popupMenuP->SetMenuItemInfoA(1, &mii, TRUE);
				mii.dwTypeData = ptxt[REF2];
				popupMenuP->SetMenuItemInfoA(2, &mii, TRUE);
				mii.dwTypeData = ptxt[REF3];
				popupMenuP->SetMenuItemInfoA(3, &mii, TRUE);
				mii.dwTypeData = ptxt[REF4];
				popupMenuP->SetMenuItemInfoA(4, &mii, TRUE);
				mii.dwTypeData = ptxt[REF5];
				popupMenuP->SetMenuItemInfoA(5, &mii, TRUE);
				mii.dwTypeData = ptxt[REF6];
				popupMenuP->SetMenuItemInfoA(6, &mii, TRUE);
				mii.dwTypeData = ptxt[REF7];
				popupMenuP->SetMenuItemInfoA(7, &mii, TRUE);
				mii.dwTypeData = ptxt[REF8];
				popupMenuP->SetMenuItemInfoA(8, &mii, TRUE);
				mii.dwTypeData = ptxt[REF9];
				popupMenuP->SetMenuItemInfoA(9, &mii, TRUE);
//				mii.dwTypeData = "All files";
//				popupMenuP->SetMenuItemInfoA(10, &mii, TRUE);

				if (!popupMenuP1->TrackPopupMenu(
					TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
			}
			cMenu.DestroyMenu();
		}
	}
	onrend:
	sliderf=0;
	CDialogEx::OnRButtonUp(nFlags, point);
}
int compare_char(const void* left, const void* right) {
    char *left_char = (char *)left;
    char *right_char = (char *)right;

    return strcmp(  right_char,left_char );
}

void CCapENT2Dlg::DispOne10(int n, char* fn)
{
	CImage img;
	CBitmap *myBMP;
	CDC *pDC;
	CRect rect;
//	if(!strstr(fn,".wmv")&&!strstr(fn,".jpg")&&!strstr(fn,".avi"))return;
	m_pic0.GetClientRect(&rect);//represent
	if(n==0)pDC=m_pic0.GetDC();
	else if(n==1)pDC=m_pic1.GetDC();
	else if(n==2)pDC=m_pic2.GetDC();
	else if(n==3)pDC=m_pic3.GetDC();
	else if(n==4)pDC=m_pic4.GetDC();
	else if(n==5)pDC=m_pic5.GetDC();
	else if(n==6)pDC=m_pic6.GetDC();
	else if(n==7)pDC=m_pic7.GetDC();
	else if(n==8)pDC=m_pic8.GetDC();
	else pDC=m_pic9.GetDC();
	if(strstr(fn,".jpg")){
		if(img.Load(fn)==S_OK){
			CDC myDC;
			BITMAP bm;
			myBMP=CBitmap::FromHandle(img);
			myDC.CreateCompatibleDC(pDC);
			CBitmap *oldBMP=myDC.SelectObject(myBMP);
			myBMP->GetBitmap(&bm);
			pDC->SetStretchBltMode(HALFTONE);
			pDC->StretchBlt(1,1,rect.right-2,rect.bottom-2,&myDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
			myDC.SelectObject(oldBMP);
			DeleteDC(myDC);
		}else{
//			MessageBox(fn);
		}
	}else if(strstr(fn,".wmv")||strstr(fn,".avi")){
		pDC->FillSolidRect(1,1,rect.right-2,rect.bottom-2,RGB(230,230,230));
		for(int i=0;i<10;i++){//21xx年のときは赤
			if(fn[strlen(fn)-17]=='1')pDC->FillSolidRect(rect.right/2-10,rect.bottom/2-10+i,2*i,1,RGB(255,10,10));
			else pDC->FillSolidRect(rect.right/2-10,rect.bottom/2-10+i,2*i,1,RGB(100,100,100));
		}
		for(int i=0;i<10;i++){
			if(fn[strlen(fn)-17]=='1')pDC->FillSolidRect(rect.right/2-10,rect.bottom/2-0+i,2*(10-i),1,RGB(255,10,10));
			else pDC->FillSolidRect(rect.right/2-10,rect.bottom/2-0+i,2*(10-i),1,RGB(100,100,100));
		}
	}else{
		pDC->FillSolidRect(1,1,rect.right-2,rect.bottom-2,RGB(230,230,230));
	}
	if(n==0)m_pic0.ReleaseDC(pDC);
	else if(n==1)m_pic1.ReleaseDC(pDC);
	else if(n==2)m_pic2.ReleaseDC(pDC);
	else if(n==3)m_pic3.ReleaseDC(pDC);
	else if(n==4)m_pic4.ReleaseDC(pDC);
	else if(n==5)m_pic5.ReleaseDC(pDC);
	else if(n==6)m_pic6.ReleaseDC(pDC);
	else if(n==7)m_pic7.ReleaseDC(pDC);
	else if(n==8)m_pic8.ReleaseDC(pDC);
	else m_pic9.ReleaseDC(pDC);
}
void CCapENT2Dlg::SetNewIDPics()//n:offset
{//2017\0123456720171212232323.jpg
	//gazou\2017\6keta or 8keta
	//CapENTでは6桁、CapENT2では8桁で保存している。
	CStdioFile ff;
	int i = 0, j = 0;
	char buf[100], buf1[100];// , id6[20], id8[20];

	ff.Open(DATA_FN, CFile::modeRead | CFile::typeText);
	allCnt = 0;
	idCnt = 0;
	while (ff.ReadString(buf, 99)) {
		allCnt++;
		buf[strlen(buf) - 1] = '\0';//行末をトル
		strcpy_s(buf1, &buf[5]);//
			if (buf[5]=='9') {
				sprintf_s(CurPics[i++], "%s:%s", &buf[5], buf);//&buf[5]年号部分を省く
				idCnt++;
				//				strcpy_s(CurPics[i++],buf);
			}

		if (i >= 10000)break;
	}
	ff.Abort();
	qsort(CurPics, i, sizeof(CurPics[0]), compare_char);//
	for (; i < 10000; i++)strcpy_s(CurPics[i], "");

	for (i = 0; strlen(CurPics[i]) != 0 && i < 10000; i++) {
		strcpy_s(buf, &CurPics[i][27]);
		strcpy_s(CurPics[i], buf);
		//		for(j=0;CurPics[i][j+32-5]!=0&&j<35;j++)CurPics[i][j]=CurPics[i][j+32-5];
		//		for(;j<50;j++)CurPics[i][j]=0;
	}
	i = 0;
	j = 0;
	while (i < 10000) {
		//録画時に同じファイル名静止画がないかチェックする。
		//再生時にも同じファイル名静止画をチェックするが、
		//録画時に保存したファイル名はチェックしていない。
		//なので2枚同じファイル名が存在することはある
		//それをここでチェックしているつもり
		if (i > 0 && strstr(CurPics[i], CurPics[i - 1])) {
			i++;
			continue;
		}
		strcpy_s(CurPics[j++], CurPics[i++]);
	}
	for (; j < 10000; j++)strcpy_s(CurPics[j], "");

	PicsOffset = 0;
}

void CCapENT2Dlg::SetNewIDPics(int idn,int mode)//n:offset
{//2017\0123456720171212232323.jpg
	//gazou\2017\6keta or 8keta
	//CapENTでは6桁、CapENT2では8桁で保存している。
	CStdioFile ff;
	int i=0,j=0;
	char buf[100],buf1[100],id6[20],id8[20];

	sprintf_s(id6,"%06d",idn);
	sprintf_s(id8,"%08d",idn);
	ff.Open(DATA_FN,CFile::modeRead|CFile::typeText);
	allCnt=0;
	idCnt=0;
	while(ff.ReadString(buf,99)){
		allCnt++;
		buf[strlen(buf)-1]='\0';//行末をトル
		strcpy_s(buf1,&buf[5]);//
		if(strlen(buf)>30){//8桁の場合。CapENT2では8桁のファイルを作る。
			buf1[8]=0;
			if(strstr(buf1,id8)){
				sprintf_s(CurPics[i++],"%s:%s",&buf[5],buf);//&buf[5]年号部分を省く
				idCnt++;
//				strcpy_s(CurPics[i++],buf);
			}
		}else{//CapENTで作成した6桁のファイルも検索する。
			buf1[6]=0;
			if(strstr(buf1,id6)){
				sprintf_s(CurPics[i++],"00%s:%s",&buf[5],buf);
				idCnt++;
//				strcpy_s(CurPics[i++],buf);
			}
		}
		if(i>=10000)break;
	}
	ff.Abort();
	qsort(CurPics, i, sizeof(CurPics[0]), compare_char);//
	for(;i<10000;i++)strcpy_s(CurPics[i],"");

	for(i=0;strlen(CurPics[i])!=0&&i<10000;i++){
		strcpy_s(buf,&CurPics[i][27]);
		strcpy_s(CurPics[i],buf);
//		for(j=0;CurPics[i][j+32-5]!=0&&j<35;j++)CurPics[i][j]=CurPics[i][j+32-5];
//		for(;j<50;j++)CurPics[i][j]=0;
	}
	i=0;
	j=0;
	while(i<10000){
		//録画時に同じファイル名静止画がないかチェックする。
		//再生時にも同じファイル名静止画をチェックするが、
		//録画時に保存したファイル名はチェックしていない。
		//なので2枚同じファイル名が存在することはある
		//それをここでチェックしているつもり
		if(i>0 && strstr(CurPics[i],CurPics[i-1])){
			i++;
			continue;
		}
		strcpy_s(CurPics[j++],CurPics[i++]);
	}
	for(;j<10000;j++)strcpy_s(CurPics[j],"");
	if(mode==1){
		i=j=0;
		while(j<4){
			if(strlen(CurPics[i])!=0){//temp video では、年号20xx を21xxとしている。これは４pics、Lpicに取りあえず表示しない
				//if ((strstr(CurPics[i], ".wmv") || strstr(CurPics[i], ".avi") || strstr(CurPics[i], ".mp4")) && CurPics[i][strlen(CurPics[i] - 17)] == '1') {//2117  -> 2(1)17 この1をチェックのつもり
				if (strstr(CurPics[i], ".wmv") || strstr(CurPics[i], ".avi") || strstr(CurPics[i], ".mp4")) {//2117  -> 2(1)17 この1をチェックのつもり
						i++;
				}else{
					strcpy_s(CurPics4[j++],CurPics[i++]);
				}
			}else break;
		}
		for(;j<5;j++)strcpy_s(CurPics4[j],"");
		strcpy_s(CurPicL,CurPics[0]);
	}
	/*
#ifdef _DEBUG
//	if(mode==1){
		ff.Open("pic4.txt",CFile::modeCreate|CFile::modeWrite|CFile::typeText);
		for(i=0;strlen(CurPics4[i])!=0;i++){
			ff.WriteString(CurPics4[i]);
			ff.WriteString("\n");
		}
		ff.Abort();
//	}
	ff.Open("pic10.txt",CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	for(i=0;strlen(CurPics[i])!=0&&i<10;i++){
		ff.WriteString(CurPics[i]);
		ff.WriteString("\n");
	}
	ff.Abort();
#endif
	*/
	PicsOffset=0;
}
void Putfn2Datafile(char *fname)//fullpath
{//CapENT2data.txtにファイルを書き込む
	//2個重複して書き込んでしまう不具合は無視
	CStdioFile ff;
	char fn[MAX_PATH];
	ff.Open(DATA_FN,CFile::modeCreate|CFile::modeNoTruncate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
	ff.SeekToEnd();//追記の場合
	strcpy_s(fn,&fname[strlen(fname)-31]);//2017￥
	ff.WriteString(fn);
	ff.WriteString("\n");
	ff.Abort();
}

void CCapENT2Dlg::PutOne2(char *fname)//fullpath
{//現在のIDnumのfileを追加し、Pic10,Pic4,PicLを書き換える。
	CStdioFile ff;
//	char buf[200];
	static char fnbefore[301]="kuroda";
	char fn[50],fn1[MAX_PATH];
	if(strstr(fname,fnbefore)&&strstr(fnbefore,fname))return;
	strcpy_s(fn1,fname);//念のため
	ff.Open(DATA_FN,CFile::modeCreate|CFile::modeNoTruncate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
/*
	while(ff.ReadString(buf,99)){
		buf[strlen(buf)-1]='\0';
		if(buf[strlen(buf)-17]=='1'){
			sprintf_s(fn,"%s\\gazou\\%s",CurDir,buf);
		}
	}
	ff.Abort();
*/
	ff.SeekToEnd();//追記の場合
	strcpy_s(fn,&fn1[strlen(fn1)-31]);
	ff.WriteString(fn);//2017￥012345672017
	ff.WriteString("\n");
	ff.Abort();
	SetNewIDPics(IDnum,1);
	DispNum(&m_datacnt, -1, idCnt, allCnt);
	Sleep(100);
	OnPaintf=true;
	strcpy_s(fnbefore,fname);
}


void CCapENT2Dlg::Disp10Pics(int n)
{
	int i;
	char buf[301];
	for(i=0;i<10;i++){
		if((i+n)<10000){
			if(strlen(CurPics[i+n])!=0)sprintf_s(buf,"%s\\gazou\\%s",CurDir,CurPics[i+n]);
			else strcpy_s(buf,"");
		}else{
			strcpy_s(buf,"");
		}
		DispOne10(i,buf);
	}
}
void erase_norisiro(CDC *pDC, int x, int y, int w, int h, int ww, int wh) {
	if (w < ww - 2) {
		pDC->FillSolidRect(1, 1, (ww -  w) / 2, wh - 2, grayRGB);
		pDC->FillSolidRect(x+w, 1, (ww-2 - w) / 2-1, wh - 2, grayRGB);
	}
	else if (h < wh - 2) {
		pDC->FillSolidRect(1, 1, ww - 2, (wh - h) / 2, grayRGB);
//		pDC->FillSolidRect(1, 1, ww - 2, (wh - 2 - h) / 2, grayRGB);
		pDC->FillSolidRect(1, y+h, ww - 2, (wh - 2 - h) / 2-1, grayRGB);
	}
}
void CCapENT2Dlg::DispOne4(CStatic *dc, char* fns)
{
	CImage img;
	CBitmap *myBMP;
	CDC *pDC;
	CRect rect;
	char fn[301];
	dc->GetClientRect(&rect);//represent
	int wx=1,wy=1,ww=rect.right-2,wh=rect.bottom-2;
/*	if(ww*Para1(CSIZ)>wh*Para0(CSIZ)){
		ww=wh*Para0(CSIZ)/Para1(CSIZ)-2;
		wx=(rect.right-ww)/2+1;
	}else{
		wh=ww*Para1(CSIZ)/Para0(CSIZ)-2;
		wy=(rect.bottom-wh)/2+1;
	}
*/	pDC = dc->GetDC();
//	pDC->FillSolidRect(0, 0, rect.right, rect.bottom, grayRGB);
	sprintf_s(fn, "%s\\gazou\\%s", CurDir, fns);
	if (strstr(fns, ".wmv") || strstr(fns, ".avi") || strstr(fns, ".mp4")) {
		BITMAP bm;
		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);   // pDCとコンパチブルなデバイスコンテキストを作成
		VideoCapture capture(fn);
		Mat frame;
		maxframenum = capture.get(CV_CAP_PROP_FRAME_COUNT);
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);// fnumber);
		capture >> frame;
		CBitmap m_bmp;
		int rows, cols, step;
		uchar *data;
		rows = frame.rows;
		cols = frame.cols;
		step = frame.step;
		data = frame.data;
		char* ColorBuf = (char*)calloc(rows * rows * 4, sizeof(RGBQUAD));
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				// Blue
				ColorBuf[y * cols * 4 + x * 4 + 0] = data[y * step + x * 3 + 0];
				// Green
				ColorBuf[y * cols * 4 + x * 4 + 1] = data[y * step + x * 3 + 1];
				// Red
				ColorBuf[y * cols * 4 + x * 4 + 2] = data[y * step + x * 3 + 2];
				//Reserved
				ColorBuf[y * cols * 4 + x * 4 + 3] = 0;
			}
		}
		m_bmp.CreateBitmap(frame.cols, frame.rows, 1, 32, ColorBuf);
		free(ColorBuf);
		m_bmp.GetObject(sizeof(BITMAP), &bm);
		dcMem.SelectObject(&m_bmp);
		pDC->SetStretchBltMode(HALFTONE);

//		if (ww*Para1(CSIZ)>wh*Para0(CSIZ)) {
//			ww = wh*Para0(CSIZ) / Para1(CSIZ) - 2;
//			wx = (rect.right - ww) / 2 + 1;
//		}
//		else {
//			wh = ww*Para1(CSIZ) / Para0(CSIZ) - 2;
//			wy = (rect.bottom - wh) / 2 + 1;
//		}
		if (ww*bm.bmHeight>wh*bm.bmWidth) {
			ww = wh*bm.bmWidth / bm.bmHeight - 2;
			wx = (rect.right - ww) / 2 + 1;
		}
		else {
			wh = ww*bm.bmHeight / bm.bmWidth - 2;
			wy = (rect.bottom - wh) / 2 + 1;
		}

		pDC->StretchBlt(wx, wy, ww, wh, &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		erase_norisiro(pDC, wx, wy, ww, wh, rect.right, rect.bottom);
		//	pDC->FillSolidRect(10, 10, 20, 20, RGB(0, 0, 0));
		DispPlaySankaku(pDC, wx + ww / 2 - 10, wy + wh / 2 - 10, 20);

		dc->ReleaseDC(pDC);
		DeleteDC(dcMem);
	}
	else if(img.Load(fn)==S_OK){
		CDC myDC;
		BITMAP bm;
		myBMP=CBitmap::FromHandle(img);
		myDC.CreateCompatibleDC(pDC);
		CBitmap *oldBMP=myDC.SelectObject(myBMP);
		myBMP->GetBitmap(&bm);
		pDC->SetStretchBltMode(HALFTONE);

		if (ww*bm.bmHeight>wh*bm.bmWidth) {
			ww = wh*bm.bmWidth / bm.bmHeight - 2;
			wx = (rect.right - ww) / 2 + 1;
		}
		else {
			wh = ww*bm.bmHeight / bm.bmWidth - 2;
			wy = (rect.bottom - wh) / 2 + 1;
		}


		pDC->StretchBlt(wx,wy,ww,wh,&myDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		erase_norisiro(pDC, wx, wy, ww, wh, rect.right, rect.bottom);
		myDC.SelectObject(oldBMP);
		DeleteDC(myDC);//必要か？
		
	}else{
		pDC->FillSolidRect(1,1,rect.right-2,rect.bottom-2,RGB(230,230,230));
	}
	ReleaseDC(pDC);
}
void CCapENT2Dlg::Disp4Pics(int n)//1, 2, 4, 8
{
	SetButtons(CapENTmode=Disp4Mode);
	if(n%2)DispOne4(&m_picm0,CurPics4[0]);
	if((n/2)%2)DispOne4(&m_picm1,CurPics4[1]);
	if((n/4)%2)DispOne4(&m_picm2,CurPics4[2]);
	if(n>=8)DispOne4(&m_picm3,CurPics4[3]);
}

void CCapENT2Dlg::DispLPic(char* fns)
{
	CImage img;
	CBitmap *myBMP;
	CDC *pDC;
	CRect rect,rectm;
	char fn[301];
	SetButtons(CapENTmode=Disp1Mode);
	m_picl.GetClientRect(&rect);
	m_picmax.GetClientRect(&rectm);
	int wx = 1, wy = 1, ww = rect.right - 2, wh = rect.bottom - 2;
//	int wx = (rectm.right-rect.right)/2-2, wy = (rectm.bottom-rect.bottom)/2-2, ww = rect.right, wh = rect.bottom;
	if(strlen(fns)==0){
		strcpy_s(fn,"");
	}else{
		sprintf_s(fn,"%s\\gazou\\%s",CurDir,fns);
	}	
	pDC=m_picl.GetDC();

	if(strlen(fn)==0){
		pDC->FillSolidRect(1,1,rect.right-2,rect.bottom-2,RGB(230,230,230));
	}
	else if (strstr(fns, ".wmv") || strstr(fns, ".avi") || strstr(fns, ".mp4")) {
		BITMAP bm;
		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);   // pDCとコンパチブルなデバイスコンテキストを作成
		VideoCapture capture(fn);
		Mat frame;
		maxframenum = capture.get(CV_CAP_PROP_FRAME_COUNT);
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);// fnumber);
		capture >> frame;
		CBitmap m_bmp;
		int rows, cols, step;
		uchar *data;
		rows = frame.rows;
		cols = frame.cols;
		step = frame.step;
		data = frame.data;
		char* ColorBuf = (char*)calloc(rows * rows * 4, sizeof(RGBQUAD));
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				// Blue
				ColorBuf[y * cols * 4 + x * 4 + 0] = data[y * step + x * 3 + 0];
				// Green
				ColorBuf[y * cols * 4 + x * 4 + 1] = data[y * step + x * 3 + 1];
				// Red
				ColorBuf[y * cols * 4 + x * 4 + 2] = data[y * step + x * 3 + 2];
				//Reserved
				ColorBuf[y * cols * 4 + x * 4 + 3] = 0;
			}
		}
		m_bmp.CreateBitmap(frame.cols, frame.rows, 1, 32, ColorBuf);
		free(ColorBuf);
		m_bmp.GetObject(sizeof(BITMAP), &bm);
		dcMem.SelectObject(&m_bmp);
		pDC->SetStretchBltMode(HALFTONE);

		//		if (ww*Para1(CSIZ)>wh*Para0(CSIZ)) {
		//			ww = wh*Para0(CSIZ) / Para1(CSIZ) - 2;
		//			wx = (rect.right - ww) / 2 + 1;
		//		}
		//		else {
		//			wh = ww*Para1(CSIZ) / Para0(CSIZ) - 2;
		//			wy = (rect.bottom - wh) / 2 + 1;
		//		}
		if (ww*bm.bmHeight>wh*bm.bmWidth) {
			ww = wh*bm.bmWidth / bm.bmHeight - 2;
			wx = (rect.right - ww) / 2 + 1;
		}
		else {
			wh = ww*bm.bmHeight / bm.bmWidth - 2;
			wy = (rect.bottom - wh) / 2 + 1;
		}

		pDC->StretchBlt(wx, wy, ww, wh, &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		erase_norisiro(pDC, wx, wy, ww, wh, rect.right, rect.bottom);
		//	pDC->FillSolidRect(10, 10, 20, 20, RGB(0, 0, 0));
		DispPlaySankaku(pDC, wx + ww / 2 - 10, wy + wh / 2 - 10, 20);

//		dcMem->ReleaseDC(pDC);
		DeleteDC(dcMem);
	}
	
	
	
	else if(img.Load(fn)==S_OK){
		static bool ismax = true;// winrect = 0;
//		bool currentismax = true;
		CDC myDC;
		BITMAP bm;
		myBMP=CBitmap::FromHandle(img);
		myDC.CreateCompatibleDC(pDC);
		CBitmap *oldBMP=myDC.SelectObject(myBMP);
		myBMP->GetBitmap(&bm);
		if (bm.bmWidth > rect.right + 5 || bm.bmHeight > rect.bottom + 5) {
			ReleaseDC(pDC);
			pDC = m_picmax.GetDC();
			m_picmax.GetClientRect(&rect);//represent
			wx = 1, wy = 1, ww = rectm.right - 2, wh = rectm.bottom - 2;
			if (ww*bm.bmHeight > wh*bm.bmWidth) {
				ww = wh*bm.bmWidth / bm.bmHeight - 2;
				wx = (rectm.right - ww) / 2 + 1;
			}
			else {
				wh = ww*bm.bmHeight / bm.bmWidth - 2;
				wy = (rectm.bottom - wh) / 2 + 1;
			}
			ismax = true;
		}
		else {
			if (ww*bm.bmHeight>wh*bm.bmWidth) {
				ww = wh*bm.bmWidth / bm.bmHeight - 2;
				wx = (rect.right - ww) / 2 + 1;
			}
			else {
				wh = ww*bm.bmHeight / bm.bmWidth - 2;
				wy = (rect.bottom - wh) / 2 + 1;
			}
			if (ismax) {//直前がpicmaxだった時はpicmaxをerase
				CDC *dc = m_picmax.GetDC();
				dc->FillSolidRect(0, 0, rectm.right, rectm.bottom, grayRGB);
				m_picmax.ReleaseDC(dc);// ->Release(dc);
			}
			ismax = false;
		}
		pDC->SetStretchBltMode(HALFTONE);

//		pDC->StretchBlt(1,1,rect.right-2,rect.bottom-2,&myDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);

		pDC->StretchBlt(wx, wy, ww, wh, &myDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		erase_norisiro(pDC, wx, wy, ww, wh, rect.right, rect.bottom);
		myDC.SelectObject(oldBMP);
		DeleteDC(myDC);//必要か？
	}
	ReleaseDC(pDC);
}

void CCapENT2Dlg::OnStnClickedPicl()
{
	SetButtons(CapENTmode=Disp4Mode);
	Disp4Pics(1+2+4+8);
}

void CCapENT2Dlg::PlayDispPic(char* fn)
{
	if(strstr(fn,"wmv")||strstr(fn,".avi")){
		if(CapENTmode==PlayMode){
			m_PlayloopEnable=false;
			Sleep(200);
		}else{
			SetButtons(CapENTmode=PlayMode);
		}
		sprintf_s(playingfn,"%s\\gazou\\%s",CurDir,fn);
		sliderf=0;
		trimposa=0;
		trimposb=slidew;
		currentframe=0;
		DispSlider(1);
		moviepausef=false;
		m_pPlayThread = AfxBeginThread(PlayThread,this);
	}else{
		strcpy_s(CurPicL,fn);
		m_PlayloopEnable=false;
		DispLPic(fn);
	}
}

int isinthums(char *fn)
{
	int i;
	for (i = 0; strlen(CurPics[i]) != 0; i++) {
		if (strstr(CurPics[i], fn) && strlen(CurPics[i]) == strlen(fn))return i;
	}
	return -1;
}
bool isvideo(char *fn)
{
	if (strstr(fn, ".wmv"))return true;
	if (strstr(fn, ".avi"))return true;
	if (strstr(fn, ".m4"))return true;
	return false;
}

BOOL CCapENT2Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	ScreenToClient(&pt);

	int n,x=CheckPicPos(CapENTmode,pt.x,pt.y);// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
    if(x>=0&&x<10&&zDelta<0){//thumnail
			PicsOffset++;
			if(PicsOffset<0)PicsOffset=0;
			if(strlen(CurPics[PicsOffset])==0)PicsOffset--;
			Disp10Pics(PicsOffset);
    }else if(x>=0&&x<10){//thumnail
			PicsOffset--;
			if(PicsOffset<0)PicsOffset=0;
			if(strlen(CurPics[PicsOffset])==0)PicsOffset--;
			Disp10Pics(PicsOffset);
	}
	else if (x > 9 && x < 14 && CapENTmode==Disp4Mode && (n=isinthums(CurPics4[x-10]))>=0) {		//画像がthumnailのものだったら、thumnail全体を順に表示
		if (zDelta > 0) {
			if (n < 1)return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
			strcpy_s(CurPics4[x - 10], CurPics[n - 1]);
//			if (!isvideo(CurPics4[x - 10])) {
				Disp4Pics(pow(2, x - 10));//Disp4Picsは動画の時はgray表示	
//			}
/*			else {
				if (x - 10 == 0)DispOneFrameDC(CurPics4[x - 10], &m_picm0,0);
				else if (x - 10 == 1)DispOneFrameDC(CurPics4[x - 10], &m_picm1,0);
				else if (x - 10 == 2)DispOneFrameDC(CurPics4[x - 10], &m_picm2,0);
				else DispOneFrameDC(CurPics4[x - 10], &m_picm3,0);
			}
*/		}
		else {
			if (strlen(CurPics[n + 1]) == 0)return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
			strcpy_s(CurPics4[x - 10], CurPics[n + 1]);
//			if (!isvideo(CurPics4[x - 10])) {
				Disp4Pics(pow(2, x - 10));
//			}
/*			else {
				if (x - 10 == 0)DispOneFrameDC(CurPics4[x - 10], &m_picm0,0);
				else if (x - 10 == 1)DispOneFrameDC(CurPics4[x - 10], &m_picm1,0);
				else if (x - 10 == 2)DispOneFrameDC(CurPics4[x - 10], &m_picm2,0);
				else DispOneFrameDC(CurPics4[x - 10], &m_picm3,0);
			}
*/		}
	}
	else if (x == 14 && CapENTmode==Disp1Mode && (n = isinthums(CurPicL)) >= 0) {		//画像がthumnailのものだったら、thumnail全体を順に表示

		if (zDelta > 0) {
			if (n < 1)return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
			strcpy_s(CurPicL, CurPics[n - 1]);
//			if (!isvideo(CurPicL)){
				DispLPic(CurPicL);//DispLpicは動画の時はなにも表示しない
//			}
//			else {
//				DispOneFrameDC(CurPicL,&m_picl,0);
//			}
		}else{
			if (strlen(CurPics[n + 1]) == 0)return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
			strcpy_s(CurPicL, CurPics[n + 1]);
//			if (!isvideo(CurPicL)){
				DispLPic(CurPicL);
//			}
//			else {
//				DispOneFrameDC(CurPicL,&m_picl,0);
//			}
		}
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CCapENT2Dlg::DispDelWaku(void)
{
	CDC *pDC=m_delpic.GetDC();
	CRect rect;
	m_delpic.GetClientRect(rect);
	int x,y;
	x=rect.right;
	y=rect.bottom;
	pDC->FillSolidRect(0,0,x,1,RGB(0,0,0));
	pDC->FillSolidRect(x-1,0,1,y,RGB(0,0,0));
	pDC->FillSolidRect(0,0,1,y,RGB(0,0,0));
	pDC->FillSolidRect(0,y-1,x,1,RGB(0,0,0));
//	ReleaseDC(pDC);
	m_delpic.ReleaseDC(pDC);
}

/*void CCapENT2Dlg::SetID(void)
{
	if(CapENTmode==CaptMode)return;
	m_PlayloopEnable=false;
	Sleep(500);
	sliderf=0;
	trimposa=0;
	trimposb=slidew;
	currentframe=0;
	CGetNewID dlg;
	char path[30];
	dlg.m_record_setid_find = 1;
	dlg.m_IDnum = IDnum;
	if (dlg.DoModal() == IDOK) {
		if (dlg.m_record_setid_find==2){//IDnum<100000000) {//そのまま抜けたときは参照、ID一覧表示
			IDnum = dlg.m_IDnum;
			SetNewIDPics(IDnum, 1);
			SetButtons(CapENTmode = Disp4Mode);//4個表示
			OnPaintf = true;
			sprintf_s(path, "%08d", IDnum);
			PushfnPtxt(path);//履歴に登録
			DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
			DispNum_sub(&m_setidwaku, IDnum);
		}
		else {//Cancel searchのみ、4picsは変更しない
			IDnum = dlg.m_IDnum;
			SetNewIDPics(IDnum, 0);
//			m_PrevloopEnable = false;
//			SetButtons(CapENTmode = Disp4);//4個表示
			OnPaintf = true;
			sprintf_s(path, "%08d", IDnum);
			PushfnPtxt(path);//履歴に登録
			DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
			DispNum_sub(&m_setidwaku, IDnum);
		}
		InvalidateRect(false);
	}
}*/

bool CheckPicsflagfn(int pn)
{
	if(pn>=0&&pn<10){
		if(strlen(CurPics[pn+PicsOffset])==0)return false;
	}else if(pn>9&&pn<14){
		if(strlen(CurPics4[pn-10])==0)return false;
	}else if(pn==14){
		if(CapENTmode==Disp1Mode){
			if(strlen(CurPicL)==0)return false;
		}else if(CapENTmode==PlayMode){
			if(strlen(playingfn)==0)return false;
		}
	}
	return true;
}
void Picsflag2fn(char *fn,int pn)
{
//	char fn[301],fn1[301];
	if(pn>=0&&pn<10){
		sprintf_s(fn,300,"%s\\gazou\\%s",CurDir,CurPics[pn+PicsOffset]);
	}else if(pn>9&&pn<14){
		sprintf_s(fn,300,"%s\\gazou\\%s",CurDir,CurPics4[pn-10]);
	}else if(pn==14){
		if(CapENTmode==Disp1Mode){
			sprintf_s(fn,300,"%s\\gazou\\%s",CurDir,CurPicL);
		}else if(CapENTmode==PlayMode){
			strcpy_s(fn,300,playingfn);
		}
	}
}


void DrawDeinter(CStatic *pic,int mode,int src)
{
	int x,y,dx=25,dy=27;
	CDC MemDC,*pDC;
	CBitmap *pOldBmp,m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC=pic->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	if(mode==5){
		x=460;
		y=0;
		dx=100;
	}else if(mode==6){//deinter
		x=428;
		y=3;
	}else if(mode==7){//inter
		x=428;
		y=36;
	}
	pDC->BitBlt(1,1,dx,dy,&MemDC,x,y,src);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	pic->ReleaseDC(pDC);//ReleaseDC(pDC)??はエラーとなる
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


//void CCapENT2Dlg::OnClickedCamnum()
//{
//	int num;
//	sscanf_s(ptxt[CAME],"%d",&num);
//	num++;
//	if(num>5)num=0;
//	sprintf_s(ptxt[CAME],"%d",num);
//	DispOneNum(&m_camnum,num,SRCCOPY);
//	m_CaploopEnable=false;
//	sliderf=0;
//	trimposa=0;
//	trimposb=slidew;
//	currentframe=0;
//	KillRecordCnt=3;
//}

void CCapENT2Dlg::DispNum(CStatic *id,int n1,int n2,int n3)//DispNum(&m_datacnt, dayCnt, idCnt, allCnt);//line,int num,char *txt)
{//n1が-1なら塗り潰す
	int i,x,x0=0,y0=46,dx=10,dy=20,ys1=8;
	char buf[100];
	CDC MemDC;
//	CDC *pDC = id->GetDC();
	CDC *pDC = m_datacnt.GetDC();// id->GetDC();
	CDC *pDCdaycnt = m_daycnt.GetDC();
	CDC *pDCtotalcnt = m_totalcnt.GetDC();

	CBitmap *pOldBmp,m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
//	pDC->FillSolidRect(1, 1, 79,78 , RGB(255, 255, 255));// grayRGB);//
	if(n1>=0){//daycnt
		sprintf_s(buf,"%08d",n1);
		for(i=0;i<strlen(buf);i++){
			if(buf[i]>='0'&&buf[i]<='9'){
				x=(buf[i]-'0')*dx+x0;
			}else if(buf[i]=='.'){
				x=10*dx+x0;
			}else if(buf[i]==':'){
				x=11*dx+x0;
			}else{
				x=12*dx+x0;
			}
			pDCdaycnt->BitBlt(i*dx,0,dx,dy,&MemDC,x,y0,SRCCOPY);
		}
	}
	else {
		if(CapENTmode==Disp4Mode)
		pDCdaycnt->FillSolidRect(0, 0, 79, 20, RGB(255, 255, 255));
	}
	if (n2 >= 0) {//IDcnt
		sprintf_s(buf, "%08d", n2);
		for (i = 0; i < strlen(buf); i++) {
			if (buf[i] >= '0'&&buf[i] <= '9') {
				x = (buf[i] - '0')*dx + x0;
			}
			else if (buf[i] == '.') {
				x = 10 * dx + x0;
			}
			else if (buf[i] == ':') {
				x = 11 * dx + x0;
			}
			else {
				x = 12 * dx + x0;
			}
			pDC->BitBlt(i*dx,0, dx, dy, &MemDC, x, y0, SRCCOPY);
		}
	}
	if (n3 >= 0) {
		sprintf_s(buf, "%08d", n3);
		for (i = 0; i < strlen(buf); i++) {
			if (buf[i] >= '0'&&buf[i] <= '9') {
				x = (buf[i] - '0')*dx + x0;
			}
			else if (buf[i] == '.') {
				x = 10 * dx + x0;
			}
			else if (buf[i] == ':') {
				x = 11 * dx + x0;
			}
			else {
				x = 12 * dx + x0;
			}
//			pDC->BitBlt(i*dx, ys1 + 2 * 22, dx, dy, &MemDC, x, y0, SRCCOPY);
			pDCtotalcnt->BitBlt(i*dx,0, dx, dy, &MemDC, x, y0, SRCCOPY);
		}
	}
//	pDC->FillSolidRect(0, 0, 1, 78, RGB(0, 0, 0));//hidari hasi ga hamideru node sikatanakuこうした
	m_datacnt.ReleaseDC(pDC);
	m_daycnt.ReleaseDC(pDCdaycnt);
	m_totalcnt.ReleaseDC(pDCtotalcnt);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void CCapENT2Dlg::SetYmd2Pic10(char* ymd)
{
	CStdioFile ff;
	int i=0,j=0;
	char buf[100],buf1[100];
	ff.Open(DATA_FN,CFile::modeRead|CFile::typeText);
	allCnt=0;
	dayCnt=0;
	while(ff.ReadString(buf,99)){
		allCnt++;
		buf[strlen(buf)-1]=0;//\nを削除
		strcpy_s(buf1,&buf[strlen(buf)-18]);
		//2017￥1234567821xx1212100000.wmv
		//上の様に21xxのこともあるので
		buf1[1]='0';//20xxに戻しているつもり、
		buf1[8]='\0';
		if(strstr(buf1,ymd)){
			sprintf_s(CurPics[i++],"%s:%s",&buf[strlen(buf)-18],buf);//&buf[]:年号部分以降
			dayCnt++;
		}
		strcpy_s(CurPics[i],"");
		if(i>=10000)break;
	}
	ff.Abort();
	qsort(CurPics, i, sizeof(CurPics[0]), compare_char);
	for(;i<10000;i++)strcpy_s(CurPics[i],"");

	for(i=0;CurPics[i][0]!='\0'&&i<10000;i++){
		strcpy_s(buf,&CurPics[i][19]);
		strcpy_s(CurPics[i],buf);
	}
}
void CCapENT2Dlg::SetIDsub(int pics)
{
	char fn[301],fn1[301];//,tail[50],fn1[301];
	Picsflag2fn(fn,pics);
	if(IsFile(fn)){
		SetEN(fn1,fn,1);
		fn1[strlen(fn1)-18]='\0';
		sscanf_s(fn1,"%d",&IDnum);
		SetNewIDPics(IDnum,0);
		Disp10Pics(PicsOffset=0);
		DispNum(&m_datacnt,dayCnt,idCnt,allCnt);
		DispNum_sub(&m_setidwaku, IDnum);
	//	DispNum_sub(&m_setid, IDnum);
	}
}

void ChanframeID(char*fn,char *final,int id)
{
	char buf[50];
	Mat frame;
	frame=imread(fn);
	if(frame.empty()){
		AfxMessageBox("file?");
		return;
	}
	if(strstr(ptxt[WRID],"1")){
		sprintf_s(buf, sizeof(buf), "ID:%08d", id);
		rectangle(frame,Point(142,21),Point(0,0), CV_RGB (255,255,255),-1,CV_AA,0 );
		putText(frame, buf, Point(1, 18), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
	}
	imwrite(final, frame);
}

void ChanframesID(char *fn,char *final,int id)
{
	int fourcc;
	char buf[50];
	fourcc=CV_FOURCC('W','M','V','2');
//	CFile::Rename(fn,"temp.wmv");
	VideoWriter rec(final,fourcc,30,Size(Para0(CSIZ),Para1(CSIZ)));
	VideoCapture capture(fn);//デバイスのオープン
	Mat frame;
	for(;;){
		capture >> frame;
		if(frame.empty())break;
		if(strstr(ptxt[WRID],"1")){
			sprintf_s(buf, sizeof(buf), "ID:%08d", id);
			rectangle(frame,Point(142,21),Point(0,0), CV_RGB (255,255,255),-1,CV_AA,0 );
			putText(frame, buf, Point(1, 18), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
		}
		rec << frame;	//	画像をファイルへ書き込む
	}
}

void CCapENT2Dlg::OnPopupChangeid()
{
	int i, pics;// = picsflag;
	char fn[301],fn1[301],tail[301],final[301];
	pics = picsflag;
	if(pics>14||pics<10)return;//ここに来る前にチェックしてありそうだが
	if (picsflagnull(pics))return;////ここに来る前にチェックしてありそうだが
	CGetID dlg;
	Picsflag2fn(fn,pics);
	if(IsFile(fn)){
		SetEN(fn1,fn,1);//fn1には2017\の後ろが入る
		strcpy_s(tail,&fn1[strlen(fn1)-18]);//2017以降の文字列
		fn1[strlen(fn1)-18]='\0';
		sscanf_s(fn1,"%d",&i);
		dlg.oldIDnum=i;
		if (chanid == 0)dlg.m_IDnum = i;
		else dlg.m_IDnum = chanid;
		if(dlg.DoModal()==IDOK){
//			SetEN(fn1,fn,2);//fn1には2017\1234567820170603121212.jpg
//			SetEN(fn1,fn,1);//fn1には1234567820170603121212.jpg
			SetEN(fn1,fn,0);//fn1には???￥gazou￥2017￥までが入る
			sprintf_s(final,"%s%08d%s",fn1,dlg.m_IDnum,tail);
			chanid = dlg.m_IDnum;
			if(strstr(final,".jpg")){
				if(IsFile(final)){
					if(AfxMessageBox("overwrite OK?",MB_YESNO)==IDYES){
						ChanframeID(fn,final,dlg.m_IDnum);
						Putfn2Datafile(final);
						SetEN(fn1,final,2);
						if(CapENTmode==Disp4Mode){
							strcpy_s(CurPics4[pics-10],fn1);
							Disp4Pics(1+2+4+8);
						}else if(CapENTmode==Disp1Mode){
							strcpy_s(CurPicL,fn1);
							DispLPic(fn1);
							for(i=0;i<4;i++){
								if(strlen(CurPics4[i])!=0&&strstr(fn,CurPics4[i])){
									strcpy_s(CurPics4[i],fn1);
								}
							}
						}
					}
				}else{
					ChanframeID(fn,final,dlg.m_IDnum);
					Putfn2Datafile(final);
					SetEN(fn1,final,2);
					if(CapENTmode==Disp4Mode){
						strcpy_s(CurPics4[pics-10],fn1);
						Disp4Pics(1+2+4+8);
					}else if(CapENTmode==Disp1Mode){
						strcpy_s(CurPicL,fn1);
						DispLPic(fn1);
							for(i=0;i<4;i++){
								if(strlen(CurPics4[i])!=0&&strstr(fn,CurPics4[i])){
									strcpy_s(CurPics4[i],fn1);
								}
							}
					}
				}
			}else{//movie 変換したビデオ登録、元ビデオも削除し登録も削除しているが、pic10、pic4、picLはまだそのまま！！！！
				CTrimChan dlg;
				if (IsFile(final)) {
					if (AfxMessageBox("overwrite OK?", MB_YESNO) == IDYES) {
						if (IsFile(final))CFile::Remove(final);
					}
					else {
						return;
					}
				}
				strcpy_s(dlg.fn1, fn);
				strcpy_s(dlg.fn2, final);
				dlg.m_posa = 0;// trimposa;
				dlg.m_posb = 0;// trimposb;
				m_PlayloopEnable = false;
				dlg.m_newid = chanid;
				if (dlg.DoModal() == IDOK) {
					Sleep(300);
					Putfn2Datafile(final);
					if (IsFile(fn))CFile::Remove(fn);
					Delfn_Datafile(fn);
					strcpy_s(playingfn, final);
					//SetEN(fn1, final, 2);
					strcpy_s(fn1, &fn[strlen(fn) - 31]);
					for (int i = 0; i < 4; i++) {
						if (strstr(fn1, CurPics4[i]))strcpy_s(CurPics4[i], &final[strlen(final)-31]);
					}
					for (i = 0; strlen(CurPics[i]) != 0; i++) {
						if (strstr(fn1, CurPics[i])) {
							strcpy_s(CurPics[i], &final[strlen(final) - 31]);
							break;
						}
					}
//					if (strlen(CurPics[i]) == 0) {
//						AfxMessageBox("DelfnCurPics error");
//						return;
//					}
					trimposa = 0;
					trimposb = slidew;
					currentframe = 0;
					DispSlider(2);
					DispOneFrame(playingfn, 0);
				}
				else {
					Sleep(300);
					if (IsFile(final))CFile::Remove(final);
				}
			}
		}
	}
	else MessageBox("?");
}
/*UINT CCapENT2Dlg::ChanThread(LPVOID pParam)
{
	((CCapENT2Dlg*)pParam)->ChanThread();
	return 0;
}


void CCapENT2Dlg::ChanThread(void)
{
	int fourcc;
	char buf[50];
	SetTimer(1,100,NULL);
	fourcc=CV_FOURCC('W','M','V','2');
	VideoWriter rec(chanfn2,fourcc,30,Size(Para0(CSIZ),Para1(CSIZ)));
	VideoCapture capture(chanfn1);//デバイスのオープン
	Mat frame;
	chanframes=capture.get(CV_CAP_PROP_FRAME_COUNT);
	for(;;){
		capture >> frame;
		if(frame.empty())break;
		if(strstr(ptxt[WRID],"1")){
			sprintf_s(buf, sizeof(buf), "ID:%08d", chanid);
			rectangle(frame,Point(142,21),Point(0,0), CV_RGB (255,255,255),-1,CV_AA,0 );
			putText(frame, buf, Point(1, 18), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
		}
		rec << frame;	//	画像をファイルへ書き込む
		chancurrentframe=capture.get(CV_CAP_PROP_POS_FRAMES);
	}
	m_pChanThread=NULL;
//	Sleep(1000);
//	if(IsFile(fn))f2gomi("temp.wmv");//delete
//	Sleep(100);
//	CFile::Rename("temp.wmv",fn);
}*/


void CCapENT2Dlg::OnPopupSetid()
{
	if (picsflagnull(picsflag))return;
	SetIDsub(picsflag);//MessageBox("set id");// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CCapENT2Dlg::OnPopupDelete()
{
	if (picsflagnull(picsflag))return;
	DeletePic(picsflag);//MessageBox("delete");// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CCapENT2Dlg::OnPopupDatesearch()
{
	if (picsflagnull(picsflag))return;
	DayRetr(picsflag);//MessageBox("date search");// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CCapENT2Dlg::OnPopupCopy()
{
//			SetEN(fn1,fn,2);//fn1には2017\1234567820170603121212.jpg
//			SetEN(fn1,fn,1);//fn1には1234567820170603121212.jpg
//			SetEN(fn1,fn,0);//fn1には???\gazou\2017\までが入る

	char fn[301],path[301];
	if (picsflagnull(picsflag))return;
	Picsflag2fn(path,picsflag);
//	strcpy_s(path,playingfn);
	SetEN(fn,path,1);
	CString SetFPath;
	if(strstr(fn,".wmv")||strstr(fn,".WMV")){
		CFileDialog myDLG(FALSE,"wmv",fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.wmv)|*.wmv||",NULL);
		if( myDLG.DoModal() == IDOK){
			SetFPath = myDLG.GetPathName();
			CopyFile(path,SetFPath,FALSE);
		}
	}else if(strstr(fn,".avi")||strstr(fn,".AVI")){
		CFileDialog myDLG(FALSE,"avi",fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.avi)|*.avi||",NULL);
		if( myDLG.DoModal() == IDOK){
			SetFPath = myDLG.GetPathName();
			CopyFile(path,SetFPath,FALSE);
		}
	}else{
		CFileDialog myDLG(FALSE,"jpg",fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.jpg)|*.jpg||",NULL);
		if( myDLG.DoModal() == IDOK){
			SetFPath = myDLG.GetPathName();
			CopyFile(path,SetFPath,FALSE);
		}
	}
}


void CCapENT2Dlg::OnPopupSetblank()
{
	CPoint pt;
	GetCursorPos(&pt);
	int x=CheckPicPos(CapENTmode,pt.x,pt.y);
	if(picsflag>9&&picsflag<14){
		strcpy_s(CurPics4[picsflag-10],"");//pics4
		Disp4Pics(1+2+4+8);
	}
}


void CCapENT2Dlg::DispNum_sub(CStatic* waku, int id)
{
	int i,x,x0=0,y0=46,dx=10,dy=20;
	bool zerof=false;
	char buf[100];
	CDC MemDC,*pDC;
	CBitmap *pOldBmp,m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);

	pDC=waku->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	pDC->FillSolidRect(1,1,80,19,RGB(255,255,255));
	sprintf_s(buf,"%08d",id);//8桁未満は上のけたを０で埋める
	for(i=0;i<8;i++){//
		if(buf[i]>='0'&&buf[i]<='9'){
			if(buf[i]!='0'||i==7)zerof=true;//0以外が出てきたらフラグを立てる
			if(buf[i]=='0'&&!zerof){//０以外が出ていないときは空白
				x=13*dx+x0;
			}else{
				x=(buf[i]-'0')*dx+x0;
			}
		}else{
			x=13*dx+x0;
		}
		pDC->BitBlt(i*dx,0,dx,dy,&MemDC,x+1,y0+1,SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	}
	waku->ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

#include < locale.h >
void runexcel(char *exfn,char *pfn)
{
	//マルチバイト２ユニコード
	//変換前文字列
	//char* 	wStrC	= "マルチバイト文字列";
	//変換文字列格納バッファ
	WCHAR	excelfn[602],picfn[602];

	size_t wLen = 0;
	errno_t err = 0;

	//ロケール指定
	setlocale(LC_ALL,"japanese");
	//変換
	err = mbstowcs_s(&wLen, excelfn, 600,exfn, _TRUNCATE);
	err = mbstowcs_s(&wLen, picfn, 600,pfn, _TRUNCATE);


// Initialize COM for this thread...
	CoInitialize(NULL);

	// Get CLSID for our server...
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);

	if(FAILED(hr)) {

		::MessageBox(NULL, "CLSIDFromProgID() failed", "Error", 0x10010);
		return;
	}

	// Start server and get IDispatch...
	IDispatch *pXlApp;
	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&pXlApp);
	if(FAILED(hr)) {
		::MessageBox(NULL, "Excel not registered properly", "Error", 0x10010);
		return;
	}
	// Make it visible (i.e. app.visible = 1)
	{
		VARIANT x;
		x.vt = VT_I4;
		x.lVal = 1;
		AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlApp, L"Visible", 1, x);
	}
	// Get Workbooks collection
	IDispatch *pXlBooks;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"Workbooks", 0);
		pXlBooks = result.pdispVal;
	}
	IDispatch *pXlBook;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT fname;
		fname.vt = VT_BSTR;
//		fname.bstrVal=::SysAllocString(L"c:\\temp\\2pics.xlsx");
		fname.bstrVal=::SysAllocString(excelfn);
		AutoWrap(DISPATCH_METHOD, &result, pXlBooks, L"Open", 1, fname);
		pXlBook = result.pdispVal;
	}

	// Get ActiveSheet object
	IDispatch *pXlSheet;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"ActiveSheet", 0);
		pXlSheet = result.pdispVal;
	}
	
	IDispatch *pXlShapes;
	{
		VARIANT result;
		VariantInit(&result);

		AutoWrap(DISPATCH_PROPERTYGET, &result, pXlSheet, L"Shapes", 0);
		pXlShapes = result.pdispVal;
	}
	IDispatch *pXlShape;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT fname;
		fname.vt = VT_BSTR;
//		fname.bstrVal=::SysAllocString(L"C:\\temp\\face.jpg");
		fname.bstrVal=::SysAllocString(picfn);
		VARIANT xpropf;
		xpropf.vt=VT_BOOL;
		xpropf.boolVal=FALSE;
		VARIANT xpropt;
		xpropt.vt=VT_BOOL;
		xpropt.boolVal=TRUE;

		VARIANT xtop;
		xtop.vt=VT_R8;
		xtop.dblVal=10.0;
		VARIANT xleft;
		xleft.vt=VT_R8;
		xleft.dblVal=10.0;
			VARIANT xwidth;
			VARIANT xheight;
		if(strstr(pfn,"2pics.jpg")){
			xwidth.vt=VT_R8;
			xwidth.dblVal=236;
			xheight.vt=VT_R8;
			xheight.dblVal=358;
		}else{//4pics.jpg 2pics_upper.jpg
//			VARIANT xwidth;
			xwidth.vt=VT_R8;
			xwidth.dblVal=322.5;
//			VARIANT xheight;
			xheight.vt=VT_R8;
			xheight.dblVal=242.5;
		}

		//I need to put the arguments in reverse order
		AutoWrap(DISPATCH_METHOD, &result, pXlShapes, L"AddPicture", 7,xheight,xwidth,xleft,xtop,xpropt,xpropf,fname);
		pXlShape = result.pdispVal;
	}
}

void CCapENT2Dlg::OnPopupPrt2()
{
	char worddoc[350],exceldoc[350],picfn[301];
	MakeJpg4prt(0);
	sprintf_s(picfn,"%s\\2pics.jpg",CurDir);
	sprintf_s(worddoc,"%s\\2pics.docm",CurDir);
	sprintf_s(exceldoc,"%s\\2pics.xlsx",CurDir);
	if(IsFile(exceldoc)){
//		AfxGetMainWnd()->SetWindowPos(&wndNoTopMost ,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE| SWP_SHOWWINDOW);
//	いろいろ試したが、VisualStudio上ではExcellが最前面に来るが、単体で起動してExcelを立ち上げるとExcelは後ろに回る
		runexcel(exceldoc,picfn);
	}else if(IsFile(worddoc)){
		ShellExecute(NULL,"open",worddoc,NULL,NULL,SW_SHOWNORMAL);
	}else{
		AfxMessageBox("no documents!( excel, word)");
	}
}



void CCapENT2Dlg::OnPopupPrt2u()
{
	char worddoc[350],exceldoc[350],picfn[301];
	MakeJpg4prt(1);
	sprintf_s(picfn,"%s\\2pics_upper.jpg",CurDir);
	sprintf_s(worddoc,"%s\\2pics.docm",CurDir);
	sprintf_s(exceldoc,"%s\\2pics_upper.xlsx",CurDir);
	if(IsFile(exceldoc))runexcel(exceldoc,picfn);
	else if(IsFile(worddoc))ShellExecute(NULL,"open",worddoc,NULL,NULL,SW_SHOWNORMAL);
	else AfxMessageBox("no documents!( excel, word)");
}

void CCapENT2Dlg::OnPopupPrt4()
{
	char worddoc[350],exceldoc[350],picfn[301];
	MakeJpg4prt(2);	
	sprintf_s(picfn,"%s\\4pics.jpg",CurDir);
	sprintf_s(worddoc,"%s\\4pics.docm",CurDir);
	sprintf_s(exceldoc,"%s\\4pics.xlsx",CurDir);
	if(IsFile(exceldoc))runexcel(exceldoc,picfn);
	else if(IsFile(worddoc))ShellExecute(NULL,"open",worddoc,NULL,NULL,SW_SHOWNORMAL);
	else AfxMessageBox("no documents!( excel, word)");
}

void CCapENT2Dlg::OnBnClickedStopdisp()
{
	m_CaploopEnable = false;

	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	strcpy_s(playingfn, 300, lastrecfn);
	Sleep(100);
	PutOne2(playingfn);
	DispOneFrame(playingfn, 0);
	Sleep(100);

	Disp4Pics(1 + 2 + 4 + 8);
	CapENTmode = Disp4Mode;
}

/*
void CCapENT2Dlg::OnPopupRotate2()
{
	Mat vim, him;					// 画像格納用/
	char fn[301];
	if (picsflag>9 && picsflag<14) {
		sprintf_s(fn, "%s\\gazou\\%s", CurDir, CurPics4[picsflag - 10]);
	}
	else return;
	Mat im = imread(fn);		// 画像の取得 /
	flip(im, vim,-1);
	imwrite(fn, vim);// 上下反転 // -1:両軸反転 1:左右反転
	Disp4Pics(1 + 2 + 4 + 8);
}


void CCapENT2Dlg::OnPopupRotate3()
{
	Mat vim, him;					// 画像格納用/
	char fn[301];// , head[100];

	if (picsflag==14) {
		sprintf_s(fn, "%s\\gazou\\%s", CurDir, CurPicL);
	}
	else return;
	Mat im = imread(fn);		// 画像の取得 /
	flip(im, vim, -1);
	imwrite(fn, vim);// 上下反転 // -1:両軸反転 1:左右反転

	DispLPic(CurPicL);
}
*/

void CCapENT2Dlg::OnPopupSetbackup()
{
	char cdr[MAX_PATH], buf[MAX_PATH];
	LPMALLOC pma;
	BROWSEINFO bif;
	LPITEMIDLIST iil;
	sprintf_s(buf, "Backupフォルダ %s", ptxt[BKUP]);
	if (::SHGetMalloc(&pma) == NOERROR)//Shell の標準のアロケータを取得
	{
		GetCurrentDirectory(sizeof(cdr), cdr);
		memset(&bif, 0x00, sizeof(bif));
		bif.hwndOwner = m_hWnd;//GetSafeHwnd();
		bif.pidlRoot = NULL;
		bif.pszDisplayName = cdr;
		bif.lpszTitle = buf;//"Backupフォルダ"
		bif.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
		bif.lpfn = NULL;
		bif.lParam = 0;
		if ((iil = SHBrowseForFolder(&bif)))
		{
			if (::SHGetPathFromIDList(iil, ptxt[BKUP]))//SaveFolder))
			{//bufに選択されたパスが入っています。
				TRACE("buf=%s\n", ptxt[BKUP]);//SaveFolder);
			}
			//iilを解放します。
			pma->Free(iil);
			//			m_videofold = ptxt[FOL2]r;

			UpdateData(false);

		}
		pma->Release();
	}	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void Putfn2BkupFile(char *fname)//fullpath
{//CapENT2data.txtにファイルを書き込む
 //2個重複して書き込んでしまう不具合は無視
	CStdioFile ff;
	char fn[MAX_PATH];
	sprintf_s(fn, "%s\\bkupfiles.txt", ptxt[BKUP]);
	ff.Open(fn, CFile::modeCreate | CFile::modeNoTruncate |
		CFile::modeWrite | CFile::modeRead | CFile::typeText);
	ff.SeekToEnd();//追記の場合
//	strcpy_s(fn, &fname[strlen(fname) - 31]);//2017￥
	ff.WriteString(fname);
	ff.WriteString("\n");
	ff.Abort();
}

bool strstr_match(char *str1, char *str2)
{
	while (*str2) {
		if (*str1!= *str2)return false;
		str1++;
		str2++;
	}
	return true;
}
bool checkisfn(CStdioFile *ff, char *txt) {
	char buf[300];
	ff->SeekToBegin();
	while (ff->ReadString(buf, 99)) {
		if (strstr(buf, txt))return true;
	}
	return false;
}
int Ymd_make(CStdioFile *fn, char *DirName,char *ymd)
{
	WIN32_FIND_DATA fd;  // 列挙情報取得用
	char Pattern[500];
//	char SubFolder[500];
	char fdfn[500];
	char fpath[500];
	int cnt = 0;
	strcpy_s(Pattern, DirName); // 探索パスを作成 
	strcat_s(Pattern, "*.*");

	HANDLE hFind;   // 検索用のハンドル 

	hFind = FindFirstFile(Pattern, &fd); // 最初のファイルを検索 
	if (hFind == INVALID_HANDLE_VALUE)
		return cnt;  // ファイルは１個も存在しない(実際は . ..があるので実行されないはず) 
	do {
		//		int jpgwmv;
		strcpy_s(fdfn, fd.cFileName);
		if (strcmp(fdfn, ".") != 0 && strcmp(fdfn, "..") != 0) { // . ..は無視 
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // フォルダ属性か調べる 
																  //現在のフォルダに見つかったフォルダを追加
			//	sprintf_s(SubFolder, 300, "%s%s\\", DirName, fdfn);
			//	Ymd_make(fn, SubFolder);  // サブフォルダを検索する 
			}
			else {
				if (check_jpgwmv(fdfn)) {
					if (strstr_match(&fdfn[strlen(fdfn) - 18], ymd)) {
						sprintf_s(fpath, "%s\%s", DirName, fdfn);//\\だとそのまま\\になる？？？？ので\ひとつにした。エラーは出るがこれでよし？？？
						fn->WriteString(&fpath[strlen(DirName) - 5]);//年号フォルダも含める
						//fn->WriteString(fdfn);//ファイル名のみ
						fn->WriteString("\n");
						cnt++;
					}
				}
			}
		}
	} while (FindNextFile(hFind, &fd) != 0);  // ファイルが無くなるまで続ける 
	FindClose(hFind);  //ハンドルを閉じる 
	return cnt;
}

void CCapENT2Dlg::OnPopupBackup()
{
	OnClickedBackupbut();
}


void CCapENT2Dlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CCapENT2Dlg::OnClickedRecord()
{
	CGetNewID dlg;
	char path[30];
//	LoadConCsize();//CapENTconfig.txtのCSIZEを、プログラム起動中に書き換えたときのために、ここでも読み込む
	if (GetKeyState(VK_SHIFT) & 0x8000) {
		changeCSIZflag = true;
	}
	else {
		changeCSIZflag = false;
	}
	if (CapENTmode == CaptMode) {
		//		return;
		m_PlayloopEnable = false;
		m_CaploopEnable = false;
		usbio232 = -1;//念のため
		Sleep(100);//500->1000変更してみた。ここでフリーズすることがあるので-->かんけいなさそうなので100msにした
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		if (IsFile(lastrecfn))f2gomi(lastrecfn);
	}
	else {// if(CapENTmode==PlayMode){
		m_PlayloopEnable = false;
		m_CaploopEnable = false;//念のため
		usbio232 = -1;//念のため
		Sleep(100);//500->1000変更してみた。ここでフリーズすることがあるので-->かんけいなさそうなので100msにした
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
	}

	dlg.m_IDnum = IDnum;
	dlg.m_record_setid_find = 0;//record
	if (dlg.DoModal() == IDOK) {
		//1億足して抜けたときはレコード onpaintf=trueで表示される
		usbio232 = uio_find();
		int tm;
		AfxBeginThread(USB_RS232Thread, &tm);
		IDnum = dlg.m_IDnum % 100000000;
		SetNewIDPics(IDnum, 1);
		SetTimer(1, 100, NULL);
		SetButtons(CapENTmode = CaptMode);
		m_pCaptureThread = AfxBeginThread(CaptureThread, this);
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		OnPaintf = true;
		sprintf_s(path, "%08d", IDnum);
		PushfnPtxt(path);//履歴に登録
		DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
		DispNum_sub(&m_setidwaku, IDnum);
		//		DispNum_sub(&m_setid, IDnum);
	}
	else {
		if (dlg.m_IDnum != 0) {
			IDnum = dlg.m_IDnum;
			//そのまま抜けたときは参照、ID一覧表示
			IDnum = dlg.m_IDnum;
			SetNewIDPics(IDnum, 1);
			SetButtons(CapENTmode = Disp4Mode);//4個表示
			OnPaintf = true;
			sprintf_s(path, "%08d", IDnum);
			PushfnPtxt(path);//履歴に登録
			DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
			DispNum_sub(&m_setidwaku, IDnum);
			//			DispNum_sub(&m_setid, IDnum);
		}
	}
	InvalidateRect(false);
}


void CCapENT2Dlg::OnClickedStillcapbut()
{
	CaptureNowf = true;
}


void CCapENT2Dlg::OnClickedSetid()
{
	if (CapENTmode == CaptMode)return;
	m_PlayloopEnable = false;
	Sleep(500);
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	CGetNewID dlg;
	char path[30];
	dlg.m_record_setid_find = 1;
	dlg.m_IDnum = IDnum;
	if (dlg.DoModal() == IDOK) {
		if (dlg.m_record_setid_find == 2) {//IDnum<100000000) {//そのまま抜けたときは参照、ID一覧表示
			IDnum = dlg.m_IDnum;
			SetNewIDPics(IDnum, 1);
			SetButtons(CapENTmode = Disp4Mode);//4個表示
			OnPaintf = true;
			sprintf_s(path, "%08d", IDnum);
			PushfnPtxt(path);//履歴に登録
			DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
			DispNum_sub(&m_setidwaku, IDnum);
		}
		else {//Cancel searchのみ、4picsは変更しない
			IDnum = dlg.m_IDnum;
			SetNewIDPics(IDnum, 0);
			//			m_PrevloopEnable = false;
			//			SetButtons(CapENTmode = Disp4);//4個表示
			OnPaintf = true;
			sprintf_s(path, "%08d", IDnum);
			PushfnPtxt(path);//履歴に登録
			DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
			DispNum_sub(&m_setidwaku, IDnum);
		}
		InvalidateRect(false);
	}
}

void CCapENT2Dlg::DayRetr(int flag)
{
	CDayretr dlg;
	char y[30];

	char fn[301];
	if (CheckPicsflagfn(flag)) {
		int ymd;
		Picsflag2fn(fn, flag);
		strcpy_s(y, &fn[strlen(fn) - 18]);
		y[8] = '\0';
		y[1] = '0';//2117->2017
		if (GetKeyState(VK_SHIFT) & 0x8000) {//shiftを押して入ると年月日入力ダイアログを表示する
			sscanf_s(y, "%d", &ymd);
			dlg.ymd = ymd;
			if (dlg.DoModal() == IDOK) {
				sprintf_s(y, "%d", dlg.ymd);
				SetYmd2Pic10(y);//これで検索して10pics表示
				Disp10Pics(PicsOffset = 0);
			}
		}
		else {
			SetYmd2Pic10(y);
			Disp10Pics(PicsOffset = 0);
		}
		DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
	}
	else {
		MessageBox("nothing?");
	}
}

void CCapENT2Dlg::OnClickedDate()
{
	CDayretr dlg;

	char y[250];
	if (lastdayretr > 2000 && lastdayretr < 21171231)dlg.ymd = lastdayretr;
	else dlg.ymd = 0;
	if (dlg.DoModal() == IDOK) {
		sprintf_s(y, "%d", dlg.ymd);
		SetYmd2Pic10(y);//これで検索して10pics表示
		Disp10Pics(PicsOffset = 0);
		DispNum(&m_datacnt, dayCnt, idCnt, allCnt);
		lastdayretr = dlg.ymd;
	}
}
void CCapENT2Dlg::Set2refer(int ref) {
	char fn[301], fn1[301], path[301];
	int fnn = picsflag;
	
	if (picsflagnull(fnn))return;
	Picsflag2fn(fn, fnn);
	if (!IsFile(fn))return;
	SetEN(path, fn, 1);//pathに2017￥0123456720171212121212.jpg
	fn[strlen(fn) - strlen(path)] = '\0';
	if (strlen(path) == 26) {
		sprintf_s(fn1, "%s9%d000000%s", fn, ref, &path[8]);
	}
	else {//6桁の時。要らなさそうだが残しとこう。
		sprintf_s(fn1, "%s9%d000000%s", fn, ref, &path[6]);
	}
	Picsflag2fn(fn, fnn);
	CopyFile(fn, fn1, FALSE);//上書き
	Putfn2Datafile(fn1);
}
void CCapENT2Dlg::OnPop2S0() { Set2refer(0); }
void CCapENT2Dlg::OnPop2S1() { Set2refer(1); }
void CCapENT2Dlg::OnPop2S2() { Set2refer(2); }
void CCapENT2Dlg::OnPop2S3() { Set2refer(3); }
void CCapENT2Dlg::OnPop2S4() { Set2refer(4); }
void CCapENT2Dlg::OnPop2S5() { Set2refer(5); }
void CCapENT2Dlg::OnPop2S6() { Set2refer(6); }
void CCapENT2Dlg::OnPop2S7() { Set2refer(7); }
void CCapENT2Dlg::OnPop2S8() { Set2refer(8); }
void CCapENT2Dlg::OnPop2S9() { Set2refer(9); }

/*void CCapENT2Dlg::Ref123(int ref, int fnn)
{
	char fn[301], fn1[301], path[301];
	if (fnn > 16 && fnn < 21) {
		IDnum = 90000000 + 1000000 * ref;
		SetNewIDPics(IDnum, 0);//4picもセットしてしまうのでそこを修正すること
		Disp10Pics(PicsOffset = 0);
		return;
	}
	else if (fnn > 14) {
		return;
	}
	Picsflag2fn(fn, fnn);
	if (!IsFile(fn))return;
	SetEN(path, fn, 1);//pathに2017￥0123456720171212121212.jpg
	fn[strlen(fn) - strlen(path)] = '\0';
	if (strlen(path) == 26) {
		sprintf_s(fn1, "%s9%d000000%s", fn, ref, &path[8]);
	}
	else {
		sprintf_s(fn1, "%s9%d000000%s", fn, ref, &path[6]);
	}
	Picsflag2fn(fn, fnn);
	CopyFile(fn, fn1, FALSE);//上書き
	Putfn2Datafile(fn1);
	//	PutOne2(fn1);//to CurPics & alldata
}*/
void CCapENT2Dlg::DispRefer(int ref) {
	IDnum = 90000000 + 1000000 * ref;
	SetNewIDPics(IDnum, 0);//4picもセットしてしまうのでそこを修正すること
	Disp10Pics(PicsOffset = 0);
}
void CCapENT2Dlg::OnPopupS0() { DispRefer(0); }
void CCapENT2Dlg::OnPopupS1() { DispRefer(1); }
void CCapENT2Dlg::OnPopupS2() { DispRefer(2); }
void CCapENT2Dlg::OnPopupS3() { DispRefer(3); }
void CCapENT2Dlg::OnPopupS4() { DispRefer(4); }
void CCapENT2Dlg::OnPopupS5() { DispRefer(5); }
void CCapENT2Dlg::OnPopupS6() { DispRefer(6); }
void CCapENT2Dlg::OnPopupS7() { DispRefer(7); }
void CCapENT2Dlg::OnPopupS8() { DispRefer(8); }
void CCapENT2Dlg::OnPopupS9() { DispRefer(9); }
void CCapENT2Dlg::OnPopupAllfiles()
{
	SetNewIDPics();
	Disp10Pics(PicsOffset = 0);
}


void CCapENT2Dlg::OnPopupSetrefname()
{
	CSetrefnames dlg;
	dlg.m_ref0 = ptxt[REF0];
	dlg.m_ref1 = ptxt[REF1];
	dlg.m_ref2 = ptxt[REF2];
	dlg.m_ref3 = ptxt[REF3];
	dlg.m_ref4 = ptxt[REF4];
	dlg.m_ref5 = ptxt[REF5];
	dlg.m_ref6 = ptxt[REF6];
	dlg.m_ref7 = ptxt[REF7];
	dlg.m_ref8 = ptxt[REF8];
	dlg.m_ref9 = ptxt[REF9];
	if (dlg.DoModal() == IDOK) {
		strcpy_s(ptxt[REF0], dlg.m_ref0);
		strcpy_s(ptxt[REF1], dlg.m_ref1);
		strcpy_s(ptxt[REF2], dlg.m_ref2);
		strcpy_s(ptxt[REF3], dlg.m_ref3);
		strcpy_s(ptxt[REF4], dlg.m_ref4);
		strcpy_s(ptxt[REF5], dlg.m_ref5);
		strcpy_s(ptxt[REF6], dlg.m_ref6);
		strcpy_s(ptxt[REF7], dlg.m_ref7);
		strcpy_s(ptxt[REF8], dlg.m_ref8);
		strcpy_s(ptxt[REF9], dlg.m_ref9);
	}
}


void CCapENT2Dlg::OnClickedSetrefer()
{

	CMenu    *popupMenuP = NULL;
	CMenu    cMenu;
	int      err = 0;
	POINT point;
	MENUITEMINFO mii = { sizeof(mii) };
	mii.fMask = MIIM_STRING;
	//画面全体でのマウスカーソルの位置を取得
	GetCursorPos(&point);
	if (!err) if (!cMenu.LoadMenu(IDR_MENU4)) err = 1;
	if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
	if (!err) {
		//	ClientToScreen(&point);
		mii.dwTypeData = ptxt[REF0];
		popupMenuP->SetMenuItemInfoA(0, &mii, TRUE);
		mii.dwTypeData = ptxt[REF1];
		popupMenuP->SetMenuItemInfoA(1, &mii, TRUE);
		mii.dwTypeData = ptxt[REF2];
		popupMenuP->SetMenuItemInfoA(2, &mii, TRUE);
		mii.dwTypeData = ptxt[REF3];
		popupMenuP->SetMenuItemInfoA(3, &mii, TRUE);
		mii.dwTypeData = ptxt[REF4];
		popupMenuP->SetMenuItemInfoA(4, &mii, TRUE);
		mii.dwTypeData = ptxt[REF5];
		popupMenuP->SetMenuItemInfoA(5, &mii, TRUE);
		mii.dwTypeData = ptxt[REF6];
		popupMenuP->SetMenuItemInfoA(6, &mii, TRUE);
		mii.dwTypeData = ptxt[REF7];
		popupMenuP->SetMenuItemInfoA(7, &mii, TRUE);
		mii.dwTypeData = ptxt[REF8];
		popupMenuP->SetMenuItemInfoA(8, &mii, TRUE);
		mii.dwTypeData = ptxt[REF9];
		popupMenuP->SetMenuItemInfoA(9, &mii, TRUE);
		if (!popupMenuP->TrackPopupMenu(
			TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
	}
	cMenu.DestroyMenu();// TODO: ここにコントロール通知ハンドラー コードを追加します。
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
/*
void DispBkUp(CDC *pDC, int f1, int t1, int x0,int y0,int mode)//11or12:直前の値を表示
{
	char buf[200];
	x0 = x0 + backupx0-155;
	y0 = y0 + Winh - 160;
	if (mode == 0) {//clear
		pDC->FillSolidRect(x0,y0, 202 + 100 + 30, 52, RGB(255,255,255));
	}
	else if(mode%10==1){//backup
		pDC->FillSolidRect(x0-5, y0-2, 155, 82, RGB(255,255,255));
		pDC->TextOutA(x0, y0, "< Backup >");
		pDC->TextOutA(x0, y0+20, "from local to remote");
		sprintf_s(buf, ": %05d", t1);
		pDC->TextOutA(x0, y0 + 40, "local( all)");
		pDC->TextOutA(x0+55+30, y0 + 40, buf);
		sprintf_s(buf, ": %05d", f1);
		pDC->TextOutA(x0, y0 + 60, "to remote");
		pDC->TextOutA(x0+55+30, y0 + 60, buf);
	}
	else if (mode%10 == 2) {
		pDC->FillSolidRect(x0 - 5, y0 - 2 -90, 155, 82, RGB(255, 255, 255));
		pDC->TextOutA(x0, y0 - 90, "< Restore >");
		pDC->TextOutA(x0, y0+20 - 90, "from remote to local");
		sprintf_s(buf, ": %05d ", f1);
		pDC->TextOutA(x0, y0 + 60 - 90, "to local");
		pDC->TextOutA(x0+55+30, y0 + 60 - 90, buf);
		sprintf_s(buf, ": %05d ", t1);
		pDC->TextOutA(x0, y0 + 40 - 90, "remote( all)");
		pDC->TextOutA(x0+55+30, y0 + 40 - 90, buf);
	}
}
*/
void CCapENT2Dlg::OnClickedBackupbut()
{
	CStdioFile ff, fbk;
	CDayretr dlg;
	CTransDLG dlg1;

	int total=0, fit=0;// i = 0, j = 0;
	char ymd[30], ymd4[30],buf1[301];// , buf2[301], fn[MAX_PATH];
	if (strlen(ptxt[BKUP]) < 5) {
		MessageBox("BackupFolderが未設定です");
		return;
	}
	if (dlg.DoModal() == IDOK) {
		sprintf_s(ymd, "%d", dlg.ymd);
		if (strlen(ymd) < 4) {
			MessageBox("年単位のバックアップが限度です");
			return;
		}
		strcpy_s(ymd4, ymd);
		ymd4[4] = '\0';
		sprintf_s(buf1, "%s\\%s", ptxt[BKUP], ymd4);//BackUpFolder の年号フォルダ
		_mkdir(buf1);//backUpFolderに年号フォルダがないこともあるので作成。
		strcpy_s(dlg1.title , "<BackUp> from local to remote");
		strcpy_s(dlg1.ymd, ymd);
		if (dlg1.DoModal() == IDOK) {
		}
	}
}


void CCapENT2Dlg::OnClickedMenu()
{
	CMenu    *popupMenuP = NULL;
	CMenu    cMenu;
	int      err = 0;
	POINT point;
	//画面全体でのマウスカーソルの位置を取得
	GetCursorPos(&point);
	if (CapENTmode == PlayMode||CapENTmode==Disp1Mode||CapENTmode==Disp4Mode) {
		if (!err) if (!cMenu.LoadMenu(IDR_MENU5)) err = 1;
		if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
		if (!err) {
		//	ClientToScreen(&point);

			if (strstr(ptxt[INTE], "1")) {
				popupMenuP->CheckMenuItem(ID_POPUP_DEINTERON, MF_CHECKED);
			}
			else {
				popupMenuP->CheckMenuItem(ID_POPUP_DEINTEROFF, MF_CHECKED);
			}

			if (!popupMenuP->TrackPopupMenu(
				TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
		}
	}else if(CapENTmode==CaptMode){
		if (!err) if (!cMenu.LoadMenu(IDR_MENU6)) err = 1;
		if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
		if (!err) {

			if (strstr(ptxt[INTE], "1")) {
				popupMenuP->CheckMenuItem(ID_POPUP_DEINTERON, MF_CHECKED);
			}
			else {
				popupMenuP->CheckMenuItem(ID_POPUP_DEINTEROFF, MF_CHECKED);
			}
			//popupMenuP->DeleteMenu(4, MF_BYCOMMAND);
			for (int i = 7; i > cameran+2; i--) {
				popupMenuP->RemoveMenu(i, MF_BYPOSITION);
			}
			if (Para0(CAME) == 0)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA1, MF_CHECKED);
			if (Para0(CAME) == 1)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA2, MF_CHECKED);
			if (Para0(CAME) == 2)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA3, MF_CHECKED);
			if (Para0(CAME) == 3)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA4, MF_CHECKED);
			if (Para0(CAME) == 4)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA5, MF_CHECKED);

			
			//	ClientToScreen(&point);
			if (!popupMenuP->TrackPopupMenu(
				TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
		}
	}
	cMenu.DestroyMenu();// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCapENT2Dlg::OnPopupRestore()
{
	CStdioFile fall,flocal,fremote;
	CDayretr dlg;
	CTransDLG dlg1;
//	bool fitF;
//	int fit = 0, total = 0;// i = 0, j = 0;
	char ymd[30];// , ymd4[30], buf[301], buf1[301], buf2[301];// , fn[MAX_PATH];
	if (strlen(ptxt[BKUP]) < 5) {
		MessageBox("BackupFolderが未設定です");
		return;
	}

	if (dlg.DoModal() == IDOK) {
		sprintf_s(ymd, "%d", dlg.ymd);
		if (strlen(ymd) < 4) {
			MessageBox("年単位のリストアが限度です");
			return;
		}
	}
	else {
		return;
	}
	strcpy_s(dlg1.title, "<Restore> from remote to local");
	strcpy_s(dlg1.ymd, ymd);
	if (dlg1.DoModal() == IDOK) {

	}
	/*
	strcpy_s(ymd4, ymd);
	ymd4[4] = '\0';
	sprintf_s(buf1, "%s\\%s\\", ptxt[BKUP], ymd4);
	sprintf_s(fn, "%s\\ymd_remote.txt", CurDir);//ymd_remote.txtを作る//\\になってしまっている
	if (!fremote.Open(fn, CFile::modeCreate | CFile::modeWrite | CFile::modeRead | CFile::typeText)) {
		MessageBox("ymd_remote.txtがオープンできません");
		return;
	}
	total = Ymd_make(&fremote, buf1, ymd);//ymd_remote.txtにymdに合致するファイルを書き込む,buf1は年号フォルダ
	fremote.Abort();

	sprintf_s(fn, "%s\\%s", CurDir, DATA_FN);
	fall.Open(fn, CFile::modeRead | CFile::typeText);
	sprintf_s(fn, "%s\\ymd_local.txt", CurDir);
	if (!flocal.Open(fn, CFile::modeCreate | CFile::modeWrite | CFile::modeRead | CFile::typeText)) {
		MessageBox("ymd_local.txtがオープンできません");
		return;
	}
	while (fall.ReadString(buf, 99)) {
		buf[strlen(buf) - 1] = '\0';//\nを削除
		if (strstr_match(&buf[strlen(buf) - 18], ymd)) {
			flocal.WriteString(buf);
			flocal.WriteString("\n");
		}
	}
	fall.Abort();
	flocal.Abort();
	//ymd.txtに合致ファイル:local
	//bkupfiles.txtに合致ファイル:remote
	sprintf_s(fn, "%s\\%s", CurDir, DATA_FN);
	fall.Open(fn, CFile::modeWrite | CFile::modeRead | CFile::typeText);
	fall.SeekToEnd();
	sprintf_s(fn, "%s\\ymd_local.txt", CurDir);
	flocal.Open(fn, CFile::modeRead | CFile::typeText);
	sprintf_s(fn, "%s\\ymd_remote.txt", CurDir);
	fremote.Open(fn, CFile::modeRead | CFile::typeText);
	fit = 0;
	CDC *pDC = GetDC();
	while (fremote.ReadString(buf, 99)) {
		buf[strlen(buf) - 1] = '\0';
		fitF = false;
		while (flocal.ReadString(buf1, 99)) {
			buf1[strlen(buf1) - 1] = '\0';
			if (strstr(buf1, buf)) {
				fitF = true;
				break;
			}
		}
		if (!fitF) {
			fall.WriteString(buf);//2019\\になってしまっている
			fall.WriteString("\n");
			fit++;
			sprintf_s(buf1, "%s\\gazou\\%s", CurDir, buf);
			sprintf_s(buf2, "%s\\%s", ptxt[BKUP], buf);//&buf[]:年号部分以降
			CopyFile(buf2, buf1, FALSE);
			DispBkUp(pDC, fit, total, 0,0, 2);
		}
		flocal.SeekToBegin();
	}
	DispBkUp(pDC, fit, total, 0,0, 2);
	ReleaseDC(pDC);
	fall.Abort();
	fremote.Abort();
	flocal.Abort();
//	RestoreDispFlag = true;
*/
}
/*void CDVCapENTView::OnHelphtml()
{CFileFind find;

	if (find.FindFile(fn)) {
		return true;
	// ファイルが存在
	}
	return false;
}*/


void CCapENT2Dlg::OnPopupHelp()
{
	CFileFind find;
	char fn[301];
	sprintf_s(fn, "%s\\Capent2_Help\\capent.html", CurDir);

	if (find.FindFile(fn)) {
		::ShellExecute(NULL, "open", fn, NULL, NULL, SW_SHOWNORMAL);
	}
	else {
		MessageBox("no help-file.");
	}
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CCapENT2Dlg::OnBnClickedExitbut()
{
	SendMessage(WM_CLOSE);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}



void CCapENT2Dlg::OnClickedDeintbut()
{
	strcpy_s(ptxt[INTE], "0");
	bmp_deint.LoadBitmapA(IDB_DEINTBUT_CHECK);
	bmp_deinton.LoadBitmapA(IDB_DEINTONBUT);
	m_deintbut.SetBitmap(bmp_deint);
	m_deintonbut.SetBitmap(bmp_deinton);
}


void CCapENT2Dlg::OnClickedDeintonbut()
{
	strcpy_s(ptxt[INTE], "1");
	bmp_deint.LoadBitmapA(IDB_DEINTBUT);
	bmp_deinton.LoadBitmapA(IDB_DEINTON_CHECK);
	m_deintbut.SetBitmap(bmp_deint);
	m_deintonbut.SetBitmap(bmp_deinton);
}


void CCapENT2Dlg::OnPopupDeinteron()
{
	//strcpy_s(ptxt[INTE], "1");
	OnClickedDeintonbut();
}


void CCapENT2Dlg::OnPopupDeinteroff()
{
//	strcpy_s(ptxt[INTE], "0");
	OnClickedDeintbut();
}


void CCapENT2Dlg::OnPopupCamera1()
{
	sprintf_s(ptxt[CAME], "%d", 0);
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapENT2Dlg::OnPopupCamera2()
{
	sprintf_s(ptxt[CAME], "%d", 1);
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
	// TODO: ここにコマンド ハンドラー コードを追加します。
}


void CCapENT2Dlg::OnPopupCamera3()
{
	sprintf_s(ptxt[CAME], "%d", 2);
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapENT2Dlg::OnPopupCamera4()
{
	sprintf_s(ptxt[CAME], "%d", 3);
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapENT2Dlg::OnPopupCamera5()
{
	sprintf_s(ptxt[CAME], "%d", 4);
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapENT2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int x = CheckPicPos(CapENTmode, point.x, point.y);
	picsflag = x; //picsflag = x;何をクリックしたか。upするまで保持。0-14 
	int sx = checkslider(point.x, point.y);
	if (CapENTmode == PlayMode) {//if (sx >= 0)//再生スライドバーをクリック

		if (sx >= 0) {//再生スライドバーをクリック
			picsflag = -2;//sliderの時は-2。
			if (!m_pPlayThread) {
				m_pPlayThread = AfxBeginThread(PlayThread, this);
				sliderf = 0;
			}
			if (sx > trimposa - 14 && sx < trimposa + 14) {
				sankakuzure = trimposa - sx;
				sliderf = 1;//左黄色三角マークの時
			}
			else if (sx > trimposb - 14 && sx < trimposb + 14) {
				sankakuzure = trimposb - sx;
				sliderf = 3;//左黄色三角マークの時
			}
			else {
				sliderf = 2;//他の部分の再生スライドバーの時
			}
			SetFrame = sx * maxframenum / slidew;
			moviepausef = true;
		}
		else {
			if ((x<10||x==14)&&CheckPicsflagfn(x)) {
				handonf = true;
				HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);     //handカーソル
				SetCursor(hCursor);//DC_ARROW
			}

		}	
	}
	else if (CapENTmode == Disp4Mode) {
		if (x<14&&CheckPicsflagfn(x)) {
			handonf = true;
			HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);     // handカーソル
			SetCursor(hCursor);//DC_ARROW	
		}
	}
	else if (CapENTmode == Disp1Mode) {
		if ((x < 10 || x == 14) && CheckPicsflagfn(x)) {
			handonf = true;
			HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);     // handカーソル
			SetCursor(hCursor);//DC_ARROW	
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCapENT2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	int x = checkslider(point.x, point.y);
	handonf = false;
	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);// 矢印カーソル
	SetCursor(hCursor);//DC_ARROW
	if (x == -1 && x == picsflag)goto kokoend;
	else if (CapENTmode == PlayMode) {//play movie
		if (picsflag > 20 && picsflag < 24)goto kokoend;
		if (picsflag == -1)goto kokoend;
		if (sliderf == 2 || sliderf == 3 || sliderf == 1) {//play point を押したとき　1,3:左右黄色三角を押したときはmousemoveで対応しているが?
			x = checkslider(point.x, point.y);
			if (x >= 0) {
				SetFrame = x * maxframenum / slidew;
			}
			sliderf = 0;

		}
		else {
			if (picsflagnull(picsflag))goto kokoend;
			x = CheckPicPos(CapENTmode, point.x, point.y);
			if (x == picsflag && x > 9 && x < 14) {//-1 && picsflag == -1) {//空白部分をクリックすると4枚表示
				m_PlayloopEnable = false;
				Disp4Pics(1 + 2 + 4 + 8);
				CapENTmode = Disp4Mode;
			}
			else if (x == 14 && picsflag == 14) {//video
				PlayMovie();
			}
			else if (x == 16) {//delete
				DeletePic(picsflag);
			}
			else if (x > -1 && x < 10 && x == picsflag) {//0-9 disp 10pic　大きく表示もしくは再生
				PlayDispPic(CurPics[x + PicsOffset]);//strcpy_s(CurPicL,CurPics4[x]);

			}
			else if ((x > -1 && x < 10) && picsflag < 10 && (x != picsflag)) {//pic10 で動いたとき
				PicsOffset -= 5 * (x - picsflag);
				if (PicsOffset < 0)PicsOffset = 0;
				while (strlen(CurPics[PicsOffset]) == 0) {
					PicsOffset -= 5;
					if (PicsOffset < 0) {
						PicsOffset = 0;
						break;
					}
				}
				Disp10Pics(PicsOffset);

			}
			else if (picsflag >= 0 && picsflag < 10) {//10picsを空白地帯にドラッグ
				int x1 = CheckPicPos(Disp4Mode, point.x, point.y);//4枚表示でのx
				if (x1 > 9 && x1 < 14) {
					//						if (strstr(CurPics[picsflag + PicsOffset], ".jpg")) {
					strcpy_s(CurPics4[x1 - 10], CurPics[picsflag + PicsOffset]);
					Disp4Pics(1 + 2 + 4 + 8);
					m_PlayloopEnable = false;
					CapENTmode = Disp4Mode;
				}
			}
		}
	}
	else if (CapENTmode == Disp4Mode) {//四枚表示
		if (picsflagnull(picsflag))goto kokoend;

		x = CheckPicPos(CapENTmode, point.x, point.y);
		if (x == 16) {//delete
			DeletePic(picsflag);
		}
		else if (x == picsflag) {
			if (x > -1 && x < 10) {//0-9 disp 10pic　大きく表示もしくは再生
				PlayDispPic(CurPics[x + PicsOffset]);
			}
			else if (x > 9 && x < 14) {//10-14 大きく表示
				strcpy_s(CurPicL, CurPics4[x - 10]);
				if (strstr(CurPicL, ".jpg")) {
					DispLPic(CurPics4[x - 10]);
					CapENTmode = Disp1Mode;
				}
				else {
					PlayDispPic(CurPicL);
				}
			}
		}
		else if (x > 9 && x < 14) {
			if (picsflag > -1 && picsflag < 10) {//picsのどれかを4picsのどれかに表示
				strcpy_s(CurPics4[x - 10], CurPics[picsflag + PicsOffset]);
				Disp4Pics(1 + 2 + 4 + 8);
			}
			else if (picsflag > 9 && picsflag < 15) {//4picsを入れ替える
				strcpy_s(CurPics4[4], CurPics4[x - 10]);
				strcpy_s(CurPics4[x - 10], CurPics4[picsflag - 10]);
				strcpy_s(CurPics4[picsflag - 10], CurPics4[4]);
				Disp4Pics(1 + 2 + 4 + 8);
			}

		}
		else if ((x > -1 && x < 10) && (x != picsflag)) {
			PicsOffset -= 5 * (x - picsflag);
			if (PicsOffset < 0)PicsOffset = 0;
			while (strlen(CurPics[PicsOffset]) == 0) {
				PicsOffset -= 5;
				if (PicsOffset < 0) {
					PicsOffset = 0;
					break;
				}
			}
			Disp10Pics(PicsOffset);
		}

	}
	else if (CapENTmode == Disp1Mode) {//一枚表示
		x = CheckPicPos(CapENTmode, point.x, point.y);
		if (x == 16) {//delete
			if (picsflagnull(picsflag))goto kokoend;
			DeletePic(picsflag);
		}
		else if ((x == picsflag) && (x > -1 && x < 10)) {//0-9 disp 10pic　大きく表示もしくは再生
			PlayDispPic(CurPics[x + PicsOffset]);//strcpy_s(CurPicL,CurPics4[x]);
		}
		else if ((x == picsflag) && (x > 9 && x < 15)) {//4pics 表示
			Disp4Pics(1 + 2 + 4 + 8);
		}
		else if (x == 14) {
			if (picsflag > -1 && picsflag < 10) {//0-9 disp 10pic　大きく表示もしくは再生
				PlayDispPic(CurPics[picsflag + PicsOffset]);//strcpy_s(CurPicL,CurPics4[x]);

			}
		}
		else if ((x > -1 && x < 10) && (x != picsflag)) {
			PicsOffset -= 5 * (x - picsflag);
			if (PicsOffset < 0)PicsOffset = 0;
			while (strlen(CurPics[PicsOffset]) == 0) {
				PicsOffset -= 5;
				if (PicsOffset < 0) {
					PicsOffset = 0;
					break;
				}
			}
			Disp10Pics(PicsOffset);

		}
		else if (picsflag >= 0 && picsflag < 10) {//10picsを空白地帯にドラッグ
			int x1 = CheckPicPos(Disp4Mode, point.x, point.y);//4枚表示でのx
			if (x1 > 9 && x1 < 14) {
				//					if (strstr(CurPics[picsflag + PicsOffset], ".jpg")) {
				strcpy_s(CurPics4[x1 - 10], CurPics[picsflag + PicsOffset]);
				Disp4Pics(1 + 2 + 4 + 8);
				CapENTmode = Disp4Mode;
			}
		}
	}
	kokoend:
	CDialogEx::OnLButtonUp(nFlags, point);
}
