#pragma once
#include "afxdialogex.h"


// CConstantMove 대화 상자

class CConstantMove : public CDialog
{
	DECLARE_DYNAMIC(CConstantMove)

public:
	CConstantMove(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantMove();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_MOVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constant_move;
};
