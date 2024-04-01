// ConstantConv.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantConv.h"


// CConstantConv 대화 상자

IMPLEMENT_DYNAMIC(CConstantConv, CDialog)

CConstantConv::CConstantConv(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_CONV, pParent)
{
	m_radio_index = 0;
}

CConstantConv::~CConstantConv()
{
}

void CConstantConv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_index);

}


BEGIN_MESSAGE_MAP(CConstantConv, CDialog)
END_MESSAGE_MAP()


// CConstantConv 메시지 처리기
