// ConstantDog.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantDog.h"


// CConstantDog 대화 상자

IMPLEMENT_DYNAMIC(CConstantDog, CDialog)

CConstantDog::CConstantDog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG5, pParent)
{
	m_radio_dog = 0;
}

CConstantDog::~CConstantDog()
{
}

void CConstantDog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_dog);

}


BEGIN_MESSAGE_MAP(CConstantDog, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CConstantDog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CConstantDog::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CConstantDog 메시지 처리기


void CConstantDog::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CConstantDog::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
