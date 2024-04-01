#pragma once
#include "afxdialogex.h"


// CConstantEmphChannel 대화 상자

class CConstantEmphChannel : public CDialog
{
	DECLARE_DYNAMIC(CConstantEmphChannel)

public:
	CConstantEmphChannel(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantEmphChannel();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMPH_CHNNEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_radio_emph_R, m_radio_emph_G, m_radio_emph_B;
};
