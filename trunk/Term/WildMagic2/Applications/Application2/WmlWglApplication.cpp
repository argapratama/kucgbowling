// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#ifdef WML_USE_WGL

#include <windows.h>
#include <mmsystem.h>
#include "WmlApplication.h"

#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"WildMagic2.lib")
#pragma comment(lib,"WmlRenderer.lib")
#include "WmlWglRenderer.h"
#include "WmlOpenGLCamera.h"
using namespace Wml;

const int Application::KEY_ESCAPE = VK_ESCAPE;
const int Application::KEY_LEFT_ARROW = VK_LEFT;
const int Application::KEY_RIGHT_ARROW = VK_RIGHT;
const int Application::KEY_UP_ARROW = VK_UP;
const int Application::KEY_DOWN_ARROW = VK_DOWN;
const int Application::KEY_HOME = VK_HOME;
const int Application::KEY_END = VK_END;
const int Application::KEY_PAGE_UP = VK_PRIOR;
const int Application::KEY_PAGE_DOWN = VK_NEXT;
const int Application::KEY_INSERT = VK_INSERT;
const int Application::KEY_DELETE = VK_DELETE;
const int Application::KEY_F1 = VK_F1;
const int Application::KEY_F2 = VK_F2;
const int Application::KEY_F3 = VK_F3;
const int Application::KEY_F4 = VK_F4;
const int Application::KEY_F5 = VK_F5;
const int Application::KEY_F6 = VK_F6;
const int Application::KEY_F7 = VK_F7;
const int Application::KEY_F8 = VK_F8;
const int Application::KEY_F9 = VK_F9;
const int Application::KEY_F10 = VK_F10;
const int Application::KEY_F11 = VK_F11;
const int Application::KEY_F12 = VK_F12;

const int Application::KEY_SHIFT = MK_SHIFT;
const int Application::KEY_CONTROL = MK_CONTROL;
const int Application::KEY_ALT = 0;      // not currently handled
const int Application::KEY_COMMAND = 0;  // not currently handled

const int Application::MOUSE_LEFT_BUTTON = 0;
const int Application::MOUSE_MIDDLE_BUTTON = 1;
const int Application::MOUSE_RIGHT_BUTTON = 2;
const int Application::MOUSE_UP = 0;
const int Application::MOUSE_DOWN = 1;

const int Application::MOD_LBUTTON = MK_LBUTTON;
const int Application::MOD_MBUTTON = MK_MBUTTON;
const int Application::MOD_RBUTTON = MK_RBUTTON;

//----------------------------------------------------------------------------
void Application::RequestTermination ()
{
    PostMessage((HWND)IntToPtr(ms_iWindowID),WM_DESTROY,0,0);
}
//----------------------------------------------------------------------------
float Application::GetTimeInSeconds ()
{
    float fTime = 0.001f*timeGetTime();
    return fTime;
}
//----------------------------------------------------------------------------
static char* ProcessCommand (char* acArgument)
{
    int iLength = (int)strlen(acArgument);

    // strip off quotes if command line was built from double-clicking a file
    char* acProcessed = new char[iLength+1];
    if ( acArgument[0] == '\"' )
    {
        strcpy(acProcessed,acArgument+1);  // remove leading quote
        if ( acArgument[iLength-1] == '\"' )
            acProcessed[iLength-2] = '\0';  // remove trailing quote
    }
    else
    {
        strcpy(acProcessed,acArgument);
    }

    return acProcessed;
}
//----------------------------------------------------------------------------
float Application::StringWidth (const char* acText)
{
    assert( acText && strlen(acText) > 0 );

    HWND hWnd = (HWND)IntToPtr(ms_iWindowID);
    HDC hDC = GetDC(hWnd);
    SIZE kSize;
    GetTextExtentPoint32(hDC,acText,(int)strlen(acText),&kSize);
    ReleaseDC(hWnd,hDC);

    return (float)kSize.cx;
}
//----------------------------------------------------------------------------
float Application::CharWidth (const char cCharacter)
{
    HWND hWnd = (HWND)IntToPtr(ms_iWindowID);
    HDC hDC = GetDC(hWnd);
    SIZE kSize;
    GetTextExtentPoint32(hDC,&cCharacter,1,&kSize);
    ReleaseDC(hWnd,hDC);

    return (float)kSize.cx;
}
//----------------------------------------------------------------------------
float Application::FontHeight ()
{
    HWND hWnd = (HWND)IntToPtr(ms_iWindowID);
    HDC hDC = GetDC(hWnd);
    TEXTMETRIC kMetric;
    GetTextMetrics(hDC,&kMetric);
    ReleaseDC(hWnd,hDC);

    return (float)kMetric.tmHeight;
}
//----------------------------------------------------------------------------
LRESULT CALLBACK WinProc (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    // GLUT does not support callbacks for key-down and key-up events.  As
    // such, it is not possible to get smooth camera motion with the
    // turret-based system while using GLUT.  However, Windows does have
    // key-down and key-up messages.  The following hack is used to allow
    // a Windows-based application to get the smooth motion.
    //    
    // The key-pressed callbacks require the mouse coordinates to be passed
    // as a pair of integers.  For Windows, the low-order byte of the x value
    // will contain the mouse x location.  The high-order byte will contain
    // either a 0 (WM_CHAR), 1 (WM_KEYDOWN), or 2 (WM_KEYUP).  The y value
    // contains the mouse location without encoding.

    Application* pkTheApp = Application::GetApplication();
    if ( !pkTheApp )
        return DefWindowProc(hWnd,uiMsg,wParam,lParam);

    switch ( uiMsg ) 
    {
        case WM_PAINT:
        {
            PAINTSTRUCT kPS;
            HDC hDC = BeginPaint(hWnd,&kPS);
            pkTheApp->OnDisplay();
            EndPaint(hWnd,&kPS);
            return 0;
        }
        case WM_MOVE:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            pkTheApp->OnMove(iXPos,iYPos);
            return 0;
        }
        case WM_SIZE:
        {
            int iWidth = int(LOWORD(lParam));
            int iHeight = int(HIWORD(lParam));
            pkTheApp->OnReshape(iWidth,iHeight);
            return 0;
        }
        case WM_CHAR:
        {
            unsigned char ucKey = (unsigned char)(char)wParam;

            // get cursor position client coordinates
            POINT kPoint;
            GetCursorPos(&kPoint);
            ScreenToClient(hWnd,&kPoint);
            int iXPos = (int)kPoint.x;
            int iYPos = (int)kPoint.y;

            pkTheApp->OnKeyDown(ucKey,iXPos,iYPos);
            return 0;
        }
        case WM_KEYDOWN:
        {
            int iVirtKey = int(wParam);

            // get cursor position client coordinates
            POINT kPoint;
            GetCursorPos(&kPoint);
            ScreenToClient(hWnd,&kPoint);
            int iXPos = (int)kPoint.x;
            int iYPos = (int)kPoint.y;

            if ( (VK_F1 <= iVirtKey && iVirtKey <= VK_F12)
            ||   (VK_PRIOR <= iVirtKey && iVirtKey <= VK_DOWN)
            ||   (iVirtKey == VK_INSERT) )
            {
                pkTheApp->OnSpecialKeyDown(iVirtKey,iXPos,iYPos);
            }
            return 0;
        }
        case WM_KEYUP:
        {
            int iVirtKey = int(wParam);

            // get cursor position client coordinates
            POINT kPoint;
            GetCursorPos(&kPoint);
            ScreenToClient(hWnd,&kPoint);
            int iXPos = (int)kPoint.x;
            int iYPos = (int)kPoint.y;

            if ( (VK_F1 <= iVirtKey && iVirtKey <= VK_F12)
            ||   (VK_PRIOR <= iVirtKey && iVirtKey <= VK_DOWN)
            ||   (iVirtKey == VK_INSERT) )
            {
                pkTheApp->OnSpecialKeyUp(iVirtKey,iXPos,iYPos);
            }
            else
            {
                pkTheApp->OnKeyUp((unsigned char)iVirtKey,iXPos,iYPos);
            }
            return 0;
        }
        case WM_LBUTTONDOWN:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            pkTheApp->OnMouseClick(Application::MOUSE_LEFT_BUTTON,
                Application::MOUSE_DOWN,iXPos,iYPos,PtrToUint(wParam));
            return 0;
        }
        case WM_LBUTTONUP:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            pkTheApp->OnMouseClick(Application::MOUSE_LEFT_BUTTON,
                Application::MOUSE_UP,iXPos,iYPos,PtrToUint(wParam));
            return 0;
        }
        case WM_MBUTTONDOWN:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            pkTheApp->OnMouseClick(Application::MOUSE_MIDDLE_BUTTON,
                Application::MOUSE_DOWN,iXPos,iYPos,PtrToUint(wParam));
            return 0;
        }
        case WM_MBUTTONUP:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            pkTheApp->OnMouseClick(Application::MOUSE_MIDDLE_BUTTON,
                Application::MOUSE_UP,iXPos,iYPos,PtrToUint(wParam));
            return 0;
        }
        case WM_RBUTTONDOWN:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            pkTheApp->OnMouseClick(Application::MOUSE_RIGHT_BUTTON,
                Application::MOUSE_DOWN,iXPos,iYPos,PtrToUint(wParam));
            return 0;
        }
        case WM_RBUTTONUP:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            pkTheApp->OnMouseClick(Application::MOUSE_RIGHT_BUTTON,
                Application::MOUSE_UP,iXPos,iYPos,PtrToUint(wParam));
            return 0;
        }
        case WM_MOUSEMOVE:
        {
            int iXPos = int(LOWORD(lParam));
            int iYPos = int(HIWORD(lParam));
            if ( (wParam & MK_LBUTTON)
            ||   (wParam & MK_MBUTTON)
            ||   (wParam & MK_RBUTTON) )
            {
                pkTheApp->OnMotion(iXPos,iYPos,PtrToUint(wParam));
            }
            else
            {
                pkTheApp->OnPassiveMotion(iXPos,iYPos);
            }
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hWnd,uiMsg,wParam,lParam);
}
//----------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE, LPSTR acArgument, int)
{
    Application* pkTheApp = Application::GetApplication();
    assert( pkTheApp );
    if ( !pkTheApp )
        return -1;

    if ( acArgument && strlen(acArgument) > 0 )
    {
        char* acProcessed = ProcessCommand(acArgument);
        pkTheApp->SetCommand(new Command(acProcessed));
        delete[] acProcessed;
    }

    if ( !pkTheApp->OnPrecreate() )
        return -2;

    // register the window class
    static char s_acWindowClass[] = "Wild Magic Application";
    WNDCLASS wc;
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WinProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = s_acWindowClass;
    wc.lpszMenuName  = NULL;
    RegisterClass(&wc);

    // require the window to have the specified client area
    RECT kRect = { 0, 0, pkTheApp->GetWidth()-1, pkTheApp->GetHeight()-1 };
    AdjustWindowRect(&kRect,WS_OVERLAPPEDWINDOW,false);

    // create the application window
    HWND hWnd = CreateWindow(
        s_acWindowClass,
        pkTheApp->GetWindowTitle(),
        WS_OVERLAPPEDWINDOW,
        pkTheApp->GetXPosition(),
        pkTheApp->GetYPosition(),
        kRect.right - kRect.left + 1,
        kRect.bottom - kRect.top + 1,
        0,
        0,
        hInstance,
        NULL);

    pkTheApp->SetWindowID(PtrToInt(hWnd));

    pkTheApp->SetRenderer(new WglRenderer(hWnd,pkTheApp->GetWidth(),
        pkTheApp->GetHeight()));

    pkTheApp->SetCamera(new OpenGLCamera((float)pkTheApp->GetWidth(),
        (float)pkTheApp->GetHeight()));

    if ( !pkTheApp->OnInitialize() )
        return -3;

    // display the window
    ShowWindow(hWnd,SW_SHOW);
    UpdateWindow(hWnd);

    // allow the application to initialize before starting the message pump
    MSG kMsg;
    while ( TRUE )
    {
        if ( PeekMessage(&kMsg,0,0,0,PM_REMOVE) )
        {
            if ( kMsg.message == WM_QUIT )
                break;

            HACCEL hAccel = 0;
            if ( !TranslateAccelerator(hWnd,hAccel,&kMsg) )
            {
                TranslateMessage(&kMsg);
                DispatchMessage(&kMsg);
            }
        }
        else
        {
            pkTheApp->OnIdle();
        }
    }

    pkTheApp->OnTerminate();

    return 0;
}
//----------------------------------------------------------------------------

#endif
