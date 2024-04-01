// ConstantDig.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantDig.h"


// CConstantDig 대화 상자

IMPLEMENT_DYNAMIC(CConstantDig, CDialog)

CConstantDig::CConstantDig(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_DIG, pParent)
	, m_constant(0)
{

}

CConstantDig::~CConstantDig()
{
}

void CConstantDig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_constant);
}


BEGIN_MESSAGE_MAP(CConstantDig, CDialog)
END_MESSAGE_MAP()


// CConstantDig 메시지 처리기
