// ConstantRotat.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantRotat.h"


// CConstantRotat 대화 상자

IMPLEMENT_DYNAMIC(CConstantRotat, CDialog)

CConstantRotat::CConstantRotat(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_ROTAT, pParent)
	, m_constant_rotat(0)
{

}

CConstantRotat::~CConstantRotat()
{
}

void CConstantRotat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_constant_rotat);
}


BEGIN_MESSAGE_MAP(CConstantRotat, CDialog)
END_MESSAGE_MAP()


// CConstantRotat 메시지 처리기
