// ConstantEmphChannel.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantEmphChannel.h"


// CConstantEmphChannel 대화 상자

IMPLEMENT_DYNAMIC(CConstantEmphChannel, CDialog)

CConstantEmphChannel::CConstantEmphChannel(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EMPH_CHNNEL, pParent)
{
	m_radio_emph_R = 0;
}

CConstantEmphChannel::~CConstantEmphChannel()
{
}

void CConstantEmphChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_emph_R);

}


BEGIN_MESSAGE_MAP(CConstantEmphChannel, CDialog)
END_MESSAGE_MAP()


// CConstantEmphChannel 메시지 처리기
