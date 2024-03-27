
// Gray scale 영상처리 MFC.h: Gray scale 영상처리 MFC 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CGrayscale영상처리MFCApp:
// 이 클래스의 구현에 대해서는 Gray scale 영상처리 MFC.cpp을(를) 참조하세요.
//

class CGrayscale영상처리MFCApp : public CWinApp
{
public:
	CGrayscale영상처리MFCApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGrayscale영상처리MFCApp theApp;
