#pragma once
#include "afxdialogex.h"


// CSlider 대화 상자

class CSlider : public CDialog
{
	DECLARE_DYNAMIC(CSlider)

public:
	CSlider(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSlider();
	int spin_value;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
};
