
// NotePad_V1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNotePad_V1App: 
// �йش����ʵ�֣������ NotePad_V1.cpp
//

class CNotePad_V1App : public CWinApp
{
public:
	CNotePad_V1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNotePad_V1App theApp;