// CapENT2.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��
#define Vertxt "CapENT(64Bit) Version2.9 - 2019/11/1"


// CCapENT2App:
// ���̃N���X�̎����ɂ��ẮACapENT2.cpp ���Q�Ƃ��Ă��������B
//

class CCapENT2App : public CWinApp
{
public:
	CCapENT2App();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CCapENT2App theApp;