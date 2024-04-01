// ConstantScale.cpp: 구현 파일
//

#include "pch.h"
#include "Color Image 영상처리.h"
#include "afxdialogex.h"
#include "ConstantScale.h"


// CConstantScale 대화 상자

IMPLEMENT_DYNAMIC(CConstantScale, CDialogEx)

CConstantScale::CConstantScale(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONSTANT_SCALE, pParent)
	, m_constant_scale(0)
{

}

CConstantScale::~CConstantScale()
{
}

void CConstantScale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_constant_scale);
}


BEGIN_MESSAGE_MAP(CConstantScale, CDialogEx)
END_MESSAGE_MAP()


// CConstantScale 메시지 처리기
