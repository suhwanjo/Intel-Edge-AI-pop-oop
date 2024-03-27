// ConstantScale.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantScale.h"


// CConstantScale 대화 상자

IMPLEMENT_DYNAMIC(CConstantScale, CDialog)

CConstantScale::CConstantScale(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_SCALE, pParent)
	, m_constant_scale(0)
{

}

CConstantScale::~CConstantScale()
{
}

void CConstantScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_SCALE, m_constant_scale);
	DDV_MinMaxInt(pDX, m_constant_scale, 1, 10);
}


BEGIN_MESSAGE_MAP(CConstantScale, CDialog)
END_MESSAGE_MAP()


// CConstantScale 메시지 처리기
