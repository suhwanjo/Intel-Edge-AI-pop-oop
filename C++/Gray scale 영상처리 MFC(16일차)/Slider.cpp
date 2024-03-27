// Slider.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "Slider.h"


// CSlider 대화 상자

IMPLEMENT_DYNAMIC(CSlider, CDialog)

CSlider::CSlider(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CSlider::~CSlider()
{
}

void CSlider::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSlider, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CSlider::OnDeltaposSpin1)
END_MESSAGE_MAP()


// CSlider 메시지 처리기


BOOL CSlider::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	spin_value = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSlider::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMUpDown->iDelta < 0) {
		spin_value++;
	}
	else {
		spin_value--;
	}
	SetDlgItemInt(IDC_EDIT_SPIN, spin_value);
	
	
	*pResult = 0;
}
