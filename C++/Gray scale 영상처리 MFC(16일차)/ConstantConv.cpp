// ConstantConv.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantConv.h"


// CConstantConv 대화 상자

IMPLEMENT_DYNAMIC(CConstantConv, CDialog)

CConstantConv::CConstantConv(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_CONV, pParent)
{
	m_conv_index3 = 0;

}

CConstantConv::~CConstantConv()
{
}

void CConstantConv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_CONV_RADIO1, (int&)m_conv_index3);
	//DDX_Radio(pDX, IDC_CONV_RADIO2, (int&)m_conv_index3);
	//DDX_Radio(pDX, IDC_CONV_RADIO3, (int&)m_conv_index3);
	//DDX_Radio(pDX, IDC_CONV_RADIO4, (int&)m_conv_index3);
}


BEGIN_MESSAGE_MAP(CConstantConv, CDialog)
END_MESSAGE_MAP()


// CConstantConv 메시지 처리기
