#pragma once
#include "afxdialogex.h"


// CConstantDigF 대화 상자

class CConstantDigF : public CDialog
{
	DECLARE_DYNAMIC(CConstantDigF)

public:
	CConstantDigF(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDigF();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_F };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constant_f;
};
