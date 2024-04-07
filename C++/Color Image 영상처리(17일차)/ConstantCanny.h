#pragma once
#include "afxdialogex.h"


// CConstantCanny 대화 상자

class CConstantCanny : public CDialog
{
	DECLARE_DYNAMIC(CConstantCanny)

public:
	CConstantCanny(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantCanny();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_CANNY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constant_low;
	int m_constant_high;
};
