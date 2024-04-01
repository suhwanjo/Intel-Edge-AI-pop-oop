// ConstantPara.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantPara.h"


// CConstantPara 대화 상자

IMPLEMENT_DYNAMIC(CConstantPara, CDialog)

CConstantPara::CConstantPara(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_PARA, pParent)
{
	m_radio_para = 0;
}

CConstantPara::~CConstantPara()
{
}

void CConstantPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_CAP, (int&)m_radio_para);

}


BEGIN_MESSAGE_MAP(CConstantPara, CDialog)
END_MESSAGE_MAP()


// CConstantPara 메시지 처리기
