
// GojasTools.h: PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#pragma warning (disable : 4819)
#include "resource.h"		// 주 기호입니다.

#define MARGIN_X(Width)	{Width + 18}
#define MARGIN_Y(Height) {Height + 38}

// CBOKOToolsApp:
// 이 클래스의 구현에 대해서는 BOKOTools.cpp을(를) 참조하세요.
//

class CBOKOToolsApp : public CWinApp
{
public:
	CBOKOToolsApp();
	~CBOKOToolsApp();
	ULONG_PTR m_gdiplusToken;

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CBOKOToolsApp theApp;
