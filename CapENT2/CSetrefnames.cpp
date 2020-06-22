// CSetrefnames.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapENT2.h"
#include "CSetrefnames.h"
#include "afxdialogex.h"


// CSetrefnames ダイアログ

IMPLEMENT_DYNAMIC(CSetrefnames, CDialogEx)

CSetrefnames::CSetrefnames(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETREFNAMES, pParent)
	, m_ref0(_T(""))
	, m_ref1(_T(""))
	, m_ref2(_T(""))
	, m_ref3(_T(""))
	, m_ref4(_T(""))
	, m_ref5(_T(""))
	, m_ref6(_T(""))
	, m_ref7(_T(""))
	, m_ref8(_T(""))
//	, m_rerf9(_T(""))
	, m_ref9(_T(""))
{

}

CSetrefnames::~CSetrefnames()
{
}

void CSetrefnames::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_REF0, m_ref0);
	DDX_Text(pDX, IDC_REF1, m_ref1);
	DDX_Text(pDX, IDC_REF2, m_ref2);
	DDX_Text(pDX, IDC_REF3, m_ref3);
	DDX_Text(pDX, IDC_REF4, m_ref4);
	DDX_Text(pDX, IDC_REF5, m_ref5);
	//  DDX_Control(pDX, IDC_REF6, m_ref6);
	//  DDX_Control(pDX, IDC_REF7, m_ref7);
	//  DDX_Control(pDX, IDC_REF8, m_ref8);
	//  DDX_Control(pDX, IDC_REF9, m_ref9);
	DDX_Text(pDX, IDC_REF6, m_ref6);
	DDX_Text(pDX, IDC_REF7, m_ref7);
	DDX_Text(pDX, IDC_REF8, m_ref8);
	//  DDX_Text(pDX, IDC_REF9, m_rerf9);
	DDX_Text(pDX, IDC_REF9, m_ref9);
}


BEGIN_MESSAGE_MAP(CSetrefnames, CDialogEx)
END_MESSAGE_MAP()


// CSetrefnames メッセージ ハンドラー
