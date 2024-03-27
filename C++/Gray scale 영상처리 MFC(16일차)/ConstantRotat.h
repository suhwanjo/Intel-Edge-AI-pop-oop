#pragma once
#include "afxdialogex.h"


// CConstantRotat 대화 상자

class CConstantRotat : public CDialog
{
	DECLARE_DYNAMIC(CConstantRotat)

public:
	CConstantRotat(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantRotat();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_ROTAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constant_rotat;
};
