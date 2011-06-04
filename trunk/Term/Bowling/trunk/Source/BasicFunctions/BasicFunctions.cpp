
// BasicFunctions.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "BasicFunctions.h"
#include "BasicFunctionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBasicFunctionsApp

BEGIN_MESSAGE_MAP(CBasicFunctionsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBasicFunctionsApp 생성

CBasicFunctionsApp::CBasicFunctionsApp()
    : mainDialog_(nullptr)
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

CBasicFunctionsApp::~CBasicFunctionsApp()
{
    if(mainDialog_ != nullptr)
    {
        delete mainDialog_;
    }
}

// 유일한 CBasicFunctionsApp 개체입니다.

CBasicFunctionsApp theApp;


// CBasicFunctionsApp 초기화

BOOL CBasicFunctionsApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

    mainDialog_ = new CBasicFunctionsDlg();
	m_pMainWnd = mainDialog_;

    mainDialog_->Create(IDD_BASICFUNCTIONS_DIALOG);
    mainDialog_->ShowWindow(SW_SHOW);

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return TRUE;
}



BOOL CBasicFunctionsApp::OnIdle(LONG lCount)
{
    mainDialog_->UpdateAndDraw();

    //return CWinApp::OnIdle(lCount);
    return TRUE;
}
