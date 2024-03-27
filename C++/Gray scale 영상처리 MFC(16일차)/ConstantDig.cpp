// ConstantDig.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantDig.h"


// CConstantDig 대화 상자

IMPLEMENT_DYNAMIC(CConstantDig, CDialog)

CConstantDig::CConstantDig(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT, pParent)
	, m_constant(0)
{

}

CConstantDig::~CConstantDig()
{
}

void CConstantDig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxInt(pDX, m_constant, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstantDig, CDialog)
END_MESSAGE_MAP()


// CConstantDig 메시지 처리기
