// Constant2.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "Constant2.h"


// CConstant2 대화 상자

IMPLEMENT_DYNAMIC(CConstant2, CDialog)

CConstant2::CConstant2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_constant1(0)
	, m_constant2(0)
	, m_constant3(0)
	, m_constant4(0)
{

}

CConstant2::~CConstant2()
{
}

void CConstant2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_constant1);
	DDX_Text(pDX, IDC_EDIT2, m_constant2);
	DDX_Text(pDX, IDC_EDIT3, m_constant3);
	DDX_Text(pDX, IDC_EDIT4, m_constant4);
}


BEGIN_MESSAGE_MAP(CConstant2, CDialog)
END_MESSAGE_MAP()


// CConstant2 메시지 처리기
