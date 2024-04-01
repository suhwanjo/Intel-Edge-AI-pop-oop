// ConstantEdge.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantEdge.h"


// CConstantEdge 대화 상자

IMPLEMENT_DYNAMIC(CConstantEdge, CDialog)

CConstantEdge::CConstantEdge(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_EDGE, pParent)
{
	m_radio_edge = 0;
}

CConstantEdge::~CConstantEdge()
{
}

void CConstantEdge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_edge);

}


BEGIN_MESSAGE_MAP(CConstantEdge, CDialog)
END_MESSAGE_MAP()


// CConstantEdge 메시지 처리기
