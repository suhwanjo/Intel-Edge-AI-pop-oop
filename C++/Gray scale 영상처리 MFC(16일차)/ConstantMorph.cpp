// ConstantMorph.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantMorph.h"


// CConstantMorph 대화 상자

IMPLEMENT_DYNAMIC(CConstantMorph, CDialog)

CConstantMorph::CConstantMorph(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MORPH, pParent)
	, m_constant_morph(0)
{

}

CConstantMorph::~CConstantMorph()
{
}

void CConstantMorph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MORPH, m_constant_morph);
	DDV_MinMaxDouble(pDX, m_constant_morph, 0.0, 1.0);
}


BEGIN_MESSAGE_MAP(CConstantMorph, CDialog)
END_MESSAGE_MAP()


// CConstantMorph 메시지 처리기
