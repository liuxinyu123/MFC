
// YuanGongGuanLi_V1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYuanGongGuanLi_V1App: 
// �йش����ʵ�֣������ YuanGongGuanLi_V1.cpp
//

class CYuanGongGuanLi_V1App : public CWinApp
{
public:
	CYuanGongGuanLi_V1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYuanGongGuanLi_V1App theApp;