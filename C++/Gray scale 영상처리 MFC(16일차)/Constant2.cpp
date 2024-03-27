// Constant2.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "Constant2.h"


// CConstant2 대화 상자

IMPLEMENT_DYNAMIC(CConstant2, CDialog)

CConstant2::CConstant2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDM_CONSTANT2, pParent)
	, m_constant1(0)
	, m_constant2(0)
{

}

CConstant2::~CConstant2()
{
}

void CConstant2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT2_1, m_constant1);
	DDV_MinMaxInt(pDX, m_constant1, 0, 255);
	DDX_Text(pDX, IDC_EDIT_CONSTANT2_2, m_constant2);
	DDV_MinMaxInt(pDX, m_constant2, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstant2, CDialog)
END_MESSAGE_MAP()


// CConstant2 메시지 처리기
