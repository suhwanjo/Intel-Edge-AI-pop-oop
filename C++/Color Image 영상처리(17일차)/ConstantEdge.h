#pragma once
#include "afxdialogex.h"


// CConstantEdge 대화 상자

class CConstantEdge : public CDialog
{
	DECLARE_DYNAMIC(CConstantEdge)

public:
	CConstantEdge(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantEdge();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_EDGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_radio_edge;
};
