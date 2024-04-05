#pragma once
#include "afxdialogex.h"


// CConstantDog 대화 상자

class CConstantDog : public CDialog
{
	DECLARE_DYNAMIC(CConstantDog)

public:
	CConstantDog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_radio_dog;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
