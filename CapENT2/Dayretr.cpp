// Dayretr.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "CapENT2.h"
#include "Dayretr.h"
#include "afxdialogex.h"
#include "CapENT2moromoro.h"


// CDayretr �_�C�A���O

IMPLEMENT_DYNAMIC(CDayretr, CDialogEx)

CDayretr::CDayretr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDayretr::IDD, pParent)
{

}

CDayretr::~CDayretr()
{
}

void CDayretr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALLCLEARNUM, m_ac);
	DDX_Control(pDX, IDC_BUTTON0, m_num0);
	DDX_Control(pDX, IDC_BUTTON1, m_num1);
	DDX_Control(pDX, IDC_BUTTON2, m_num2);
	DDX_Control(pDX, IDC_BUTTON3, m_num3);
	DDX_Control(pDX, IDC_BUTTON4, m_num4);
	DDX_Control(pDX, IDC_BUTTON5, m_num5);
	DDX_Control(pDX, IDC_BUTTON6, m_num6);
	DDX_Control(pDX, IDC_BUTTON7, m_num7);
	DDX_Control(pDX, IDC_BUTTON8, m_num8);
	DDX_Control(pDX, IDC_BUTTON9, m_num9);
	//  DDX_Control(pDX, IDC_BUTTONX, m_numx);
	DDX_Control(pDX, IDC_CLEARNUM, m_c);
	DDX_Control(pDX, IDC_DAY_YMD, m_ymd);
	DDX_Control(pDX, IDC_DAY1, m_day1);
	DDX_Control(pDX, IDC_DAY10, m_day10);
	DDX_Control(pDX, IDC_DAY2, m_day2);
	DDX_Control(pDX, IDC_DAY3, m_day3);
	DDX_Control(pDX, IDC_DAY4, m_day4);
	DDX_Control(pDX, IDC_DAY5, m_day5);
	DDX_Control(pDX, IDC_DAY6, m_day6);
	DDX_Control(pDX, IDC_DAY7, m_day7);
	DDX_Control(pDX, IDC_DAY8, m_day8);
	DDX_Control(pDX, IDC_DAY9, m_day9);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
}


BEGIN_MESSAGE_MAP(CDayretr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CDayretr::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CDayretr::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDayretr::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CDayretr::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDayretr::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDayretr::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CDayretr::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDayretr::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDayretr::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON0, &CDayretr::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_CLEARNUM, &CDayretr::OnBnClickedClearnum)
	ON_BN_CLICKED(IDC_ALLCLEARNUM, &CDayretr::OnBnClickedAllclearnum)
//	ON_BN_CLICKED(IDC_BUTTONX, &CDayretr::OnBnClickedButtonx)
	ON_STN_CLICKED(IDC_DAY1, &CDayretr::OnStnClickedDay1)
	ON_STN_CLICKED(IDC_DAY2, &CDayretr::OnStnClickedDay2)
	ON_STN_CLICKED(IDC_DAY3, &CDayretr::OnStnClickedDay3)
	ON_STN_CLICKED(IDC_DAY4, &CDayretr::OnStnClickedDay4)
	ON_STN_CLICKED(IDC_DAY5, &CDayretr::OnStnClickedDay5)
	ON_STN_CLICKED(IDC_DAY6, &CDayretr::OnStnClickedDay6)
	ON_STN_CLICKED(IDC_DAY7, &CDayretr::OnStnClickedDay7)
	ON_STN_CLICKED(IDC_DAY8, &CDayretr::OnStnClickedDay8)
	ON_STN_CLICKED(IDC_DAY9, &CDayretr::OnStnClickedDay9)
	ON_STN_CLICKED(IDC_DAY10, &CDayretr::OnStnClickedDay10)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDayretr ���b�Z�[�W �n���h���[

void CDayretr::OnBnClickedButton7()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+7);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton8()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+8);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton9()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+9);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton4()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+4);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton5()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+5);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton6()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+6);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton1()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+1);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton2()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+2);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton3()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+3);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedButton0()
{
	if(ymd==0)return;
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10);
}


void CDayretr::OnBnClickedClearnum()
{
	DispNum(ymd=ymd/10);	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnBnClickedAllclearnum()
{
	DispNum(ymd=0);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


//void CDayretr::OnBnClickedButtonx()
//{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
//}


void CDayretr::OnStnClickedDay1()
{
	DispNum(ymd=y1);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay2()
{
	DispNum(ymd=y2);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay3()
{
	DispNum(ymd=y3);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay4()
{
	DispNum(ymd=y4);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay5()
{
	DispNum(ymd=y5);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay6()
{
	DispNum(ymd=y6);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay7()
{
	DispNum(ymd=y7);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay8()
{
	DispNum(ymd=y8);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay9()
{
	DispNum(ymd=y9);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


void CDayretr::OnStnClickedDay10()
{
	DispNum(ymd=y10);// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


BOOL CDayretr::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//	ymd=0;
	int y=12;
	int nx=20;
	int ny=y+80;
	int dx=72,dy=72,nw=71,nh=71;
	int histw=103,histh=35;
	m_ymd.MoveWindow(nx,ny-71,nw*3+histw+3,70,1);
	m_num7.MoveWindow(nx     ,ny,nw,nh,1);
	m_num8.MoveWindow(nx+  dx,ny,nw,nh,1);
	m_num9.MoveWindow(nx+2*dx,ny,nw,nh,1);
	m_num4.MoveWindow(nx     ,ny+dy,nw,nh,1);
	m_num5.MoveWindow(nx+  dx,ny+dy,nw,nh,1);
	m_num6.MoveWindow(nx+2*dx,ny+dy,nw,nh,1);
	m_num1.MoveWindow(nx     ,ny+2*dy,nw,nh,1);
	m_num2.MoveWindow(nx+  dx,ny+2*dy,nw,nh,1);
	m_num3.MoveWindow(nx+2*dx,ny+2*dy,nw,nh,1);
	m_num0.MoveWindow(nx     ,ny+3*dy,nw,nh,1);
	m_c.MoveWindow(nx+  dx,ny+3*dy,nw,nh,1);
	m_ac.MoveWindow(nx+2*dx,ny+3*dy,nw,nh,1);

//	m_cancel.MoveWindow(nx,ny+4*dy,nw,nh,1);
//	m_startcap.MoveWindow(nx+dx,ny+4*dy,nw,nh,1);
//	m_ok.MoveWindow(nx+2*dx,ny+4*dy,nw,nh,1);
//	m_numx.ShowWindow(SW_HIDE);
//	m_cancel.MoveWindow(nx,ny+4*dy,nw,nh,1);
//	m_cancel.MoveWindow(nx,ny+4*dy,nw,nh,1);
//	m_ok.MoveWindow(nx+dx,ny+4*dy,2*nw,nh,1);

	m_ok.MoveWindow(nx+3*dx/2+1,ny+4*dy,3*nw/2,nh,1);
	m_cancel.MoveWindow(nx,ny+4*dy,3*nw/2,nh,1);


	m_day1.MoveWindow(nx+3*dx,ny,histw,histh);
	m_day2.MoveWindow(nx+3*dx,ny+(histh+1)*1,histw,histh);
	m_day3.MoveWindow(nx+3*dx,ny+(histh+1)*2,histw,histh);
	m_day4.MoveWindow(nx+3*dx,ny+(histh+1)*3,histw,histh);
	m_day5.MoveWindow(nx+3*dx,ny+(histh+1)*4,histw,histh);
	m_day6.MoveWindow(nx+3*dx,ny+(histh+1)*5,histw,histh);
	m_day7.MoveWindow(nx+3*dx,ny+(histh+1)*6,histw,histh);
	m_day8.MoveWindow(nx+3*dx,ny+(histh+1)*7,histw,histh);
	m_day9.MoveWindow(nx+3*dx,ny+(histh+1)*8,histw,histh);
	m_day10.MoveWindow(nx+3*dx,ny+(histh+1)*9,histw,histh);
//	m_cancel.MoveWindow(nx,ny+4*dy,dx+nw/2-1,nh,1);
//	m_ok.MoveWindow(nx+dx+nw/2+1,ny+4*dy,dx+nw/2-1,nh,1);

//	m_currentid.MoveWindow(nx+2*dx,ny+4*dy,nw,20,1);
//	bmp_button_start.LoadBitmapA(IDB_STARTBUTTON);
//	m_startcap.SetBitmap(bmp_button_start);//ok ���X�^�[�g
//	bmp_button_alllist.LoadBitmapA(IDB_BUTTON_ALLLIST);
//	m_cancel.SetBitmap(bmp_button_alllist);
//	bmp_button_curplay.LoadBitmapA(IDB_BUTTON_CURPLAY);
//	m_start.SetBitmap(bmp_button_curplay);
	// TODO:  �����ɏ�������ǉ����Ă�������
	MoveWindow(Winw/2-(nw*3+2+20*2+10*2)/2,Winh/2-(ny+4*dy+20+nw+20*2)/2, nw*3+2+20*2+10*2+histw, ny+5*dy+20+20*2, 1);// dlgrect.right - dlgrect.left, dlgrect.bottom - dlgrect.top, 1);// 0, 0, 100, 200, 1);
//	MoveWindow(0,0, nw*3+2+20*2+10*2+histw, ny+5*dy+20+20*2, 1);// dlgrect.right - dlgrect.left, dlgrect.bottom - dlgrect.top, 1);// 0, 0, 100, 200, 1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}


void CDayretr::DispNum(int ymd)
{
	int i,idn,x,x0=0,y0=0,dx=33,dy=45;
	bool zerof=false;
	char buf[100];
	CDC MemDC,*pDC;
	CBitmap *pOldBmp,m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC=m_ymd.GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);

	pDC->FillSolidRect(0,0,315,66,RGB(255,255,255));
	idn=ymd;
//	sprintf_s(buf,"%08d",idn);//8�������͏�̂������O�Ŗ��߂�
	sprintf_s(buf,"%d",idn);
	strcat_s(buf,"        ");
	buf[8]='\0';
	for(i=0;i<8;i++){//
		if(buf[i]>='0'&&buf[i]<='9'){
		
				x=(buf[i]-'0')*dx+x0;
		
		}else{
			x = 355;// 10 * dx + x0;
		}
		pDC->BitBlt(i*(dx+2)+20,10,dx,dy,&MemDC,x,y0,SRCAND);
	}
	m_ymd.ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


void CDayretr::DispNum_sub(CStatic* id, int idn)
{
	int i,x,x0=0,y0=46,dx=10,dy=20;
	bool zerof=false;
	char buf[100];
	CDC MemDC,*pDC;
	CBitmap *pOldBmp,m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);

	pDC=id->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bmp);
	pDC->FillSolidRect(0,0,98,33,RGB(255,255,255));
	sprintf_s(buf,"%08d",idn);//8�������͏�̂������O�Ŗ��߂�
	for(i=0;i<8;i++){//
		if(buf[i]>='0'&&buf[i]<='9'){
			if(buf[i]!='0'||i==7)zerof=true;//0�ȊO���o�Ă�����t���O�𗧂Ă�
			if(buf[i]=='0'&&!zerof){//�O�ȊO���o�Ă��Ȃ��Ƃ��͋�
				x=13*dx+x0;
			}else{
				x=(buf[i]-'0')*dx+x0;
			}
		}else{
			x=13*dx+x0;
		}
		pDC->BitBlt(2+i*(dx+2),8,dx,dy,&MemDC,x,y0,SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	}
	id->ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void CDayretr::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CTime    cTime;
	CTimeSpan    cTimeSpan1(1, 0, 0, 0);//1��
	cTime = CTime::GetCurrentTime();    // ���ݎ���
	if(ymd==0)DispNum(ymd=cTime.GetYear()*10000+cTime.GetMonth()*100+cTime.GetDay());
	else DispNum(ymd);
//	cTime-=cTimeSpan1;
	DispNum_sub(&m_day1, yh[1] = y1 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day2, yh[2] = y2 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day3, yh[3] = y3 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day4, yh[4] = y4 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day5, yh[5] = y5 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day6, yh[6] = y6 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day7, yh[7] = y7 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day8, yh[8] = y8 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day9, yh[9] = y9 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day10, yh[10] = y10 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
}


BOOL CDayretr::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		switch(pMsg->wParam) {
		case VK_RETURN:
//			OnBnClickedStartcap();
			OnOK();
			return true;// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
		case '0':
		case  VK_NUMPAD0:
			OnBnClickedButton0();
			return true;
		case 'J':
		case '1':
		case  VK_NUMPAD1:
			OnBnClickedButton1();
			return true;
		case 'K':
		case '2':
		case  VK_NUMPAD2:
			OnBnClickedButton2();
			return true;
		case 'L':
		case '3':
		case  VK_NUMPAD3:
			OnBnClickedButton3();
			return true;
		case 'U':
		case '4':
		case  VK_NUMPAD4:
			OnBnClickedButton4();
			return true;
		case 'I':
		case '5':
		case  VK_NUMPAD5:
			OnBnClickedButton5();
			return true;
		case 'O':
		case '6':
		case  VK_NUMPAD6:
			OnBnClickedButton6();
			return true;
		case '7':
		case  VK_NUMPAD7:
			OnBnClickedButton7();
			return true;
		case '8':
		case  VK_NUMPAD8:
			OnBnClickedButton8();
			return true;
		case '9': 
		case  VK_NUMPAD9:
			OnBnClickedButton9();
			return true;
		case VK_BACK:
		case VK_CLEAR:
			OnBnClickedClearnum();
			return true;
		case VK_DELETE:
			OnBnClickedAllclearnum();
			return true;
		case VK_DOWN:
			yhist++;
			if (yhist > 10)yhist = 10;
			if (yhist != 0)DispNum(ymd = yh[yhist]);// 3); //DispNum(m_IDnum = GetNthID(ptxt[HIST], m_hist));
			return true;
		case VK_UP:
			yhist--;
			if (yhist < 0)yhist = 0;
			if (yhist != 0)DispNum(ymd = yh[yhist]);//DispNum(m_IDnum = GetNthID(ptxt[HIST], m_hist));
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
