// ConstantMirror.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantMirror.h"


// CConstantMirror 대화 상자

IMPLEMENT_DYNAMIC(CConstantMirror, CDialog)

CConstantMirror::CConstantMirror(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_MIRROR, pParent)
{
	m_radio_index = 0;
}

CConstantMirror::~CConstantMirror()
{
}

void CConstantMirror::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_EDIT_CONSTANT_HOR, m_constant_hor);
	DDX_Control(pDX, IDC_EDIT_CONSTANT_VER, m_constant_ver);*/
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_index);
}


BEGIN_MESSAGE_MAP(CConstantMirror, CDialog)
END_MESSAGE_MAP()


// CConstantMirror 메시지 처리기
