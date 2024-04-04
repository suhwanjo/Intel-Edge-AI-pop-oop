#pragma once
#include "afxdialogex.h"


// CConstantLog 대화 상자

class CConstantLog : public CDialog
{
	DECLARE_DYNAMIC(CConstantLog)

public:
	CConstantLog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantLog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDM_CONSTANT_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_radio_log;
};
