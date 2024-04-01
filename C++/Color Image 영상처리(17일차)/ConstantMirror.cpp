// ConstantMirror.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantMirror.h"


// CConstantMirror 대화 상자

IMPLEMENT_DYNAMIC(CConstantMirror, CDialog)

CConstantMirror::CConstantMirror(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_MIRROR, pParent)
{
	m_radio_mirror = 0;
}

CConstantMirror::~CConstantMirror()
{
}

void CConstantMirror::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_mirror);
}


BEGIN_MESSAGE_MAP(CConstantMirror, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CConstantMirror::OnBnClickedMirror)
END_MESSAGE_MAP()


// CConstantMirror 메시지 처리기


void CConstantMirror::OnBnClickedMirror()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
