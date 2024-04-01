// ConstantF.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantF.h"


// CConstantF 대화 상자

IMPLEMENT_DYNAMIC(CConstantF, CDialog)

CConstantF::CConstantF(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_F, pParent)
	, m_constant_f(0)
{

}

CConstantF::~CConstantF()
{
}

void CConstantF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_F, m_constant_f);
}


BEGIN_MESSAGE_MAP(CConstantF, CDialog)
END_MESSAGE_MAP()


// CConstantF 메시지 처리기
