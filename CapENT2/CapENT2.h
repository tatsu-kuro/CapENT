// CapENT2.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#define Vertxt "CapENT(64Bit) Version2.9 - 2019/11/1"


// CCapENT2App:
// このクラスの実装については、CapENT2.cpp を参照してください。
//

class CCapENT2App : public CWinApp
{
public:
	CCapENT2App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CCapENT2App theApp;