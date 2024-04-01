#pragma once
#include "afxdialogex.h"


// CConstantMirror 대화 상자

class CConstantMirror : public CDialog
{
	DECLARE_DYNAMIC(CConstantMirror)

public:
	CConstantMirror(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantMirror();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_MIRROR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_radio_mirror;
	afx_msg void OnBnClickedMirror();
};
