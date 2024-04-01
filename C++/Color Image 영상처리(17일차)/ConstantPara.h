#pragma once
#include "afxdialogex.h"


// CConstantPara 대화 상자

class CConstantPara : public CDialog
{
	DECLARE_DYNAMIC(CConstantPara)

public:
	CConstantPara(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantPara();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_PARA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_radio_para;
};
