#pragma once
#include "afxdialogex.h"


// CConstantScale 대화 상자

class CConstantScale : public CDialog
{
	DECLARE_DYNAMIC(CConstantScale)

public:
	CConstantScale(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantScale();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_SCALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constant_scale;
};
