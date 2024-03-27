// ConstantMove.cpp: 구현 파일
//

#include "pch.h"
#include "Gray scale 영상처리 MFC.h"
#include "afxdialogex.h"
#include "ConstantMove.h"


// CConstantMove 대화 상자

IMPLEMENT_DYNAMIC(CConstantMove, CDialog)

CConstantMove::CConstantMove(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_MOVE, pParent)
	, m_constant_move(0)
{

}

CConstantMove::~CConstantMove()
{
}

void CConstantMove::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_MOVE, m_constant_move);
	DDV_MinMaxInt(pDX, m_constant_move, -255, 255);
}


BEGIN_MESSAGE_MAP(CConstantMove, CDialog)
END_MESSAGE_MAP()


// CConstantMove 메시지 처리기
