#include "carInDlg.h"
#include "carOutDlg.h"
// park_Manage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cpark_ManageApp:
// �йش����ʵ�֣������ park_Manage.cpp
//

class Cpark_ManageApp : public CWinApp
{
public:
	Cpark_ManageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cpark_ManageApp theApp;