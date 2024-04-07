// ConstantCanny.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantCanny.h"


// CConstantCanny 대화 상자

IMPLEMENT_DYNAMIC(CConstantCanny, CDialog)

CConstantCanny::CConstantCanny(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_CANNY, pParent)
	, m_constant_low(0)
	, m_constant_high(0)
{

}

CConstantCanny::~CConstantCanny()
{
}

void CConstantCanny::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_constant_low);
	DDX_Text(pDX, IDC_EDIT2, m_constant_high);
}


BEGIN_MESSAGE_MAP(CConstantCanny, CDialog)
END_MESSAGE_MAP()


// CConstantCanny 메시지 처리기
