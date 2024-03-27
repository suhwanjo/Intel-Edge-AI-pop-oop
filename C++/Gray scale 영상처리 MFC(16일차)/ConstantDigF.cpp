// ConstantDigF.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantDigF.h"


// CConstantDigF 대화 상자

IMPLEMENT_DYNAMIC(CConstantDigF, CDialog)

CConstantDigF::CConstantDigF(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_F, pParent)
	, m_constant_f(0)
{

}

CConstantDigF::~CConstantDigF()
{
}

void CConstantDigF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_F, m_constant_f);
	DDV_MinMaxDouble(pDX, m_constant_f, 0.5, 5.0);
}


BEGIN_MESSAGE_MAP(CConstantDigF, CDialog)
END_MESSAGE_MAP()


// CConstantDigF 메시지 처리기
