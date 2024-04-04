// ConstantLog.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantLog.h"


// CConstantLog 대화 상자

IMPLEMENT_DYNAMIC(CConstantLog, CDialog)

CConstantLog::CConstantLog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDM_CONSTANT_LOG, pParent)
{
	m_radio_log = 0;
}

CConstantLog::~CConstantLog()
{
}

void CConstantLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, (int&)m_radio_log);

}


BEGIN_MESSAGE_MAP(CConstantLog, CDialog)
END_MESSAGE_MAP()


// CConstantLog 메시지 처리기
