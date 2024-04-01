#pragma once
#include "afxdialogex.h"


// CConstantConv 대화 상자

class CConstantConv : public CDialog
{
	DECLARE_DYNAMIC(CConstantConv)

public:
	CConstantConv(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantConv();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_CONV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_radio_index;
};
