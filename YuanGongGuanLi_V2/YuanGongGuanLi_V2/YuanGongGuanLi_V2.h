
// YuanGongGuanLi_V2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYuanGongGuanLi_V2App: 
// �йش����ʵ�֣������ YuanGongGuanLi_V2.cpp
//

class CYuanGongGuanLi_V2App : public CWinApp
{
public:
	CYuanGongGuanLi_V2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYuanGongGuanLi_V2App theApp;