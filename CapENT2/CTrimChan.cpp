// CTrimChan.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapENT2.h"
#include "CTrimChan.h"
#include "afxdialogex.h"
#include <opencv2\opencv.hpp>
#include "CapENT2moromoro.h"
using namespace cv;
UINT CTrimThread(LPVOID pParam);
UINT ChanIDThread(LPVOID dammy);
bool loopEnable;
int framenum;
int maxframenum;
char trimfn2[301];
char trimfn1[301];
int posa;
int posb;
int newid;

// CTrimChan ダイアログ

IMPLEMENT_DYNAMIC(CTrimChan, CDialogEx)

CTrimChan::CTrimChan(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRIMCHAN, pParent)
	, m_frames(_T(""))
{

	m_posa = 0;
	m_posb = 0;
	m_newid = 0;
}

CTrimChan::~CTrimChan()
{
}

void CTrimChan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FRAMES, m_frames);
}


BEGIN_MESSAGE_MAP(CTrimChan, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTrimChan メッセージ ハンドラー

UINT CTrimThread(LPVOID dammy)
{
	int fourcc;
	fourcc = CV_FOURCC('W', 'M', 'V', '2');
	//	strcpy_s(trimsrcfn,playingfn);
	VideoWriter rec(trimfn2, fourcc, Para0(FPSN), Size(Para0(CSIZ), Para1(CSIZ)));
	VideoCapture capture(trimfn1);//デバイスのオープン
	Mat frame;
	loopEnable = true;
	framenum = 0;
	//	trimingposa = posa;
	//	trimingposb = posb;
	maxframenum = capture.get(CV_CAP_PROP_FRAME_COUNT);
	capture.set(CV_CAP_PROP_POS_FRAMES, posa*maxframenum / slidew);

	Sleep(100);//いるか？
	for (int i = 0; loopEnable && (i < (posb - posa)*maxframenum / slidew); i++) {
		framenum++;
		capture >> frame;
		rec << frame;	//	画像をファイルへ書き込む
	}
	//	m_pTrimThread = NULL;
		//	Sleep(110);
	loopEnable = false;
	return 0;
}

UINT ChanIDThread(LPVOID dammy)//char *fn,char *final,int id)
{
	int fourcc;
	char buf[50];
	fourcc = CV_FOURCC('W', 'M', 'V', '2');
	VideoWriter rec(trimfn2, fourcc, 30, Size(Para0(CSIZ), Para1(CSIZ)));//trim ではないが、そのままとしている
	VideoCapture capture(trimfn1);//デバイスのオープン
//	changingIDf = true;
	loopEnable = true;
	framenum = 0;
	maxframenum = capture.get(CV_CAP_PROP_FRAME_COUNT);
	Mat frame;
	for (;;) {
		if (!loopEnable)break;
		capture >> frame;
		if (frame.empty())break;
		framenum++;
		if (strstr(ptxt[WRID], "1")) {
			sprintf_s(buf, sizeof(buf), "ID:%08d", newid);
			rectangle(frame, Point(142, 21), Point(0, 0), CV_RGB(255, 255, 255), -1, CV_AA, 0);
			putText(frame, buf, Point(1, 18), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
		}
		rec << frame;	//	画像をファイルへ書き込む
	}
	//	changingIDf = false;
		//	Sleep(200);
		//	f2gomi(chanfn1);
	loopEnable = false;
	return 0;
}

void CTrimChan::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (nIDEvent == 1) {//100msecごと
		char buf[100];
		if (posb != posa) {
			//		float ff = float(framenum) / float(Para0(FPSN));
				//	float f0 = float((posb - posa)*maxframenum / float(Gwinw)) / (float)Para0(FPSN);
					//小数点以下が余ることがあるので-1している
					//sprintf_s(buf, "remains : %05.1f/%05.1f", (f0 - ff - 1.0 > 0 ? f0 - ff - 1.0 : 0), f0);//swm[mode][2]?SW_SHOW:SW_HIDE
			sprintf_s(buf, "frames : %04d/%04d", framenum, (posb - posa)*maxframenum / Gwinw);
			m_frames = buf;
		}
		else {
			//			float ratio = float(framenum) / float(maxframenum);
			sprintf_s(buf, "frames : %04d/%04d", framenum, maxframenum);
			m_frames = buf;
		}
		UpdateData(false);
		if(!loopEnable)	CDialogEx::OnOK();
	}
	CDialogEx::OnTimer(nIDEvent);
}




BOOL CTrimChan::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	strcpy_s(trimfn1, fn1);
	strcpy_s(trimfn2, fn2);
	posa = m_posa;
	posb = m_posb;
	newid = m_newid;
	SetTimer(1, 100, NULL);
	int tm;
	if (posa != posb) {
		AfxBeginThread(CTrimThread, &tm);
	}
	else {
		AfxBeginThread(ChanIDThread, &tm);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CTrimChan::OnOK()
{
	if (loopEnable)return;
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	loopEnable = false;
	CDialogEx::OnOK();
}



void CTrimChan::OnCancel()
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	loopEnable = false;
	CDialogEx::OnCancel();
}
