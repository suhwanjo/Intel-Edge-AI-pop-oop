
// Gray scale 영상처리 MFCDoc.cpp: CGrayscale영상처리MFCDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Gray scale 영상처리 MFC.h"
#endif

#include "Gray scale 영상처리 MFCDoc.h"
#include <cmath>
#include <propkey.h>
#include "ConstantDig.h"
#include "ConstantDigF.h"
#include "Constant2.h"
#include "ConstantMorph.h"
#include "ConstantMove.h"
#include "ConstantRotat.h"
#include "ConstantScale.h"
#include "ConstantMirror.h"
#include "ConstantConv.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayscale영상처리MFCDoc

IMPLEMENT_DYNCREATE(CGrayscale영상처리MFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CGrayscale영상처리MFCDoc, CDocument)
END_MESSAGE_MAP()


// CGrayscale영상처리MFCDoc 생성/소멸

CGrayscale영상처리MFCDoc::CGrayscale영상처리MFCDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayscale영상처리MFCDoc::~CGrayscale영상처리MFCDoc()
{
}

BOOL CGrayscale영상처리MFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayscale영상처리MFCDoc serialization

void CGrayscale영상처리MFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGrayscale영상처리MFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayscale영상처리MFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayscale영상처리MFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayscale영상처리MFCDoc 진단

#ifdef _DEBUG
void CGrayscale영상처리MFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayscale영상처리MFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayscale영상처리MFCDoc 명령


unsigned char** CGrayscale영상처리MFCDoc::OnMalloc2D(int h, int w, int initVal)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;
	retMemory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];

	return retMemory;
}


void CGrayscale영상처리MFCDoc::Onfree2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


BOOL CGrayscale영상처리MFCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 
	// 선택된 파일 열기
	CFile File; // 제공하는 파일 클래스
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// (중요!) 이미지의 폭과 높이를 결정
	ULONGLONG fLength = File.GetLength();
	// 메모리 해제, 관련 값 초기화
	Onfree2D(m_inImage, m_inH);
	m_inImage = NULL; // 포인터는 해제 후 NULL 넣어줌
	m_inH = m_inW = 0;
	m_inH = m_inW = (int)sqrt((double)fLength);
	// 메모리 할당
	m_inImage = OnMalloc2D(m_inH, m_inW, 0);
	// 파일에서 메모리로 읽기
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);

	File.Close();

	return TRUE;
}


void CGrayscale영상처리MFCDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Onfree2D(m_inImage, m_inH);
	m_inImage = NULL; // 포인터는 해제 후 NULL 넣어줌
	m_inH = m_inW = 0;
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	CDocument::OnCloseDocument();
}


void CGrayscale영상처리MFCDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			m_outImage[i][k] = m_inImage[i][k];
}


void CGrayscale영상처리MFCDoc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			m_outImage[i][k] = 255 - m_inImage[i][k];
}


void CGrayscale영상처리MFCDoc::OnPostImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_outImage[i][j] >= 0 && m_inImage[i][j] <= 31)
				m_outImage[i][j] = 31;
			else if (m_inImage[i][j] > 31 && m_inImage[i][j] <= 63)
				m_outImage[i][j] = 63;
			else if (m_inImage[i][j] > 63 && m_inImage[i][j] <= 95)
				m_outImage[i][j] = 95;
			else if (m_inImage[i][j] > 95 && m_inImage[i][j] <= 127)
				m_outImage[i][j] = 127;
			else if (m_inImage[i][j] > 127 && m_inImage[i][j] <= 159)
				m_outImage[i][j] = 159;
			else if (m_inImage[i][j] > 159 && m_inImage[i][j] <= 191)
				m_outImage[i][j] = 191;
			else if (m_inImage[i][j] > 191 && m_inImage[i][j] <= 223)
				m_outImage[i][j] = 223;
			else if (m_inImage[i][j] > 223 && m_inImage[i][j] <= 255)
				m_outImage[i][j] = 255;
		}
	}
}


void CGrayscale영상처리MFCDoc::OnHistoStretch()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	int high = m_inImage[0][0]; // 최대, 최소 구할 때 처음 값으로 설정
	int low = m_inImage[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] < low)
				low = m_inImage[i][j];
			if (m_inImage[i][j] > high)
				high = m_inImage[i][j];
		}
	}
	// End-In 탐색 : 최대 최소값 사이를 좁혀 스트레칭 효과를 극대화
	// high -= 50;
	// low += 50;  
	//
	int oldVal, newVal;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			oldVal = m_inImage[i][j];
			newVal = (int)((oldVal - low) / (double)(high - low) * 255.0);
			m_outImage[i][j] = newVal;
		}
	}

}


void CGrayscale영상처리MFCDoc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	// 1단계 : 빈도수 세기(=히스토그램) histo[256]
	int histo[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++)
			histo[m_inImage[i][j]]++;
	// 2단계 : 누적히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	// 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImage[i][j] = (unsigned char)normalHisto[m_inImage[i][j]];
		}
	}
}


void CGrayscale영상처리MFCDoc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] + val <= 255) // val이 음수면
				m_outImage[i][j] = m_inImage[i][j] + val;
			else
				m_outImage[i][j] = 255;
		}
	}
}


void CGrayscale영상처리MFCDoc::OnSubImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] - val >= 0) // val이 음수면
				m_outImage[i][j] = m_inImage[i][j] - val;
			else
				m_outImage[i][j] = 0;
		}
	}
}


void CGrayscale영상처리MFCDoc::OnBinaryImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	int val = (int)dlg.m_constant;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] > val)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = 0;
		}
	}

}


BOOL CGrayscale영상처리MFCDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		for (int i = 0; i < m_outH; i++)
			File.Write(m_outImage[i], m_outW);
		File.Close();
	}

	return true;
}


void CGrayscale영상처리MFCDoc::OnBinaryAvg()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 진짜 영상처리 알고리즘
	int hap = 0;
	int result;
	// 평균 구하기
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			hap += m_inImage[i][j];
		}
	}
	result = hap / (m_inH * m_inW);
	CString message;
	message.Format(_T("이미지의 평균값은 %d 입니다."), result);
	MessageBox(AfxGetMainWnd()->GetSafeHwnd(), message, _T("알림"), MB_OK);
	// 이진화
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] > result)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = 0;
		}
	}
}


void CGrayscale영상처리MFCDoc::OnBinaryMid()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	// 진짜 영상처리 알고리즘
	int count = 0;
	int median = 0;
	int arr[256] = { 0 };
	// 중앙값 구하기
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			arr[m_inImage[i][j]] += 1;
		}
	}
	for (int i = 0; i < 256; i++) {
		count += arr[i];
		if (count >= (m_inH * m_inW / 2)) {
			median = i;
			break;
		}
	}
	CString message;
	message.Format(_T("이미지의 중앙값은 %d 입니다."), median);
	MessageBox(AfxGetMainWnd()->GetSafeHwnd(), message, _T("알림"), MB_OK);
	// 이진화
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] > median)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = 0;
		}
	}
	
}


void CGrayscale영상처리MFCDoc::OnParaCup()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImage[i][j] = 255.0 - 255.0 * pow(((double)m_inImage[i][j] / 127.0 - 1.0), 2.0); // CUP 파라볼라 : 어두운 곳이 입체적으로 보임
		}
	}
}


void CGrayscale영상처리MFCDoc::OnParaCap()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImage[i][j] = 255.0 * pow(((double)m_inImage[i][j] / 127.0 - 1.0), 2.0); // CAP 파라볼라 : 밝은 곳이 입체적으로 보임
		}
	}
}


void CGrayscale영상처리MFCDoc::OnGammaImage()
{
	CConstantDigF dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double gam = (double)dlg.m_constant_f;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImage[i][j] = pow(((double)m_inImage[i][j] / 255.0), gam) * 255.0; // pow의 반환 타입은 double
		}
	}
}


void CGrayscale영상처리MFCDoc::OnEmphImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant2 dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	int startVal = (int)dlg.m_constant1;
	int endVal = (int)dlg.m_constant2;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if ((m_inImage[i][j] > startVal && m_inImage[i][j] < endVal) || (m_inImage[i][j] < startVal && m_inImage[i][j] > endVal))
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = m_inImage[i][j];
		}
	}
}


void CGrayscale영상처리MFCDoc::OnMorphImage()
{
	CConstantMorph dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// Memory allocation for the output image
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	// Fetching the blending factor from the slider and scaling it to the range of 0 to 1
	double val = (double)dlg.m_constant_morph;

	// Open dialog to select second image
	CString filePath;
	CFileDialog dlgFile(TRUE);
	if (dlgFile.DoModal() == IDOK) {
		filePath = dlgFile.GetPathName();

		// Open selected file for the second image
		CFile file;
		if (!file.Open(filePath, CFile::modeRead | CFile::typeBinary)) {
			AfxMessageBox(_T("Failed to open file."));
			return;
		}

		// Determine the width and height of the second image
		ULONGLONG fLength = file.GetLength();
		int secondImageH = (int)sqrt((double)fLength);
		int secondImageW = secondImageH;

		// Allocate memory for the second image
		unsigned char** image2 = OnMalloc2D(secondImageH, secondImageW, 0);

		// Read from file into memory
		for (int i = 0; i < secondImageH; i++)
			file.Read(image2[i], secondImageW);

		file.Close();

		// Perform morphing operation pixel by pixel
		for (int y = 0; y < m_outH; y++) {
			for (int x = 0; x < m_outW; x++) {
				// Get pixel values from the first and second input images
				int pixel1 = m_inImage[y][x];
				int pixel2 = image2[y][x];

				// Calculate the morphed pixel value
				int morphedPixel = (int)(pixel1 * val + pixel2 * (1 - val));

				// Set the morphed pixel value in m_outImage
				m_outImage[y][x] = morphedPixel;
			}
		}

		// Free memory for the second image
		Onfree2D(image2, secondImageH);
	}
	else {
		// User canceled the dialog, return without processing
		return;
	}
}


void CGrayscale영상처리MFCDoc::OnMoveImage()
{
	CConstantMove dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// Memory allocation for the output image
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	int move = (int)dlg.m_constant_move;
	if (move >= 0) { // 우측 하단으로 이동
		for (int i = 0; i < m_outH - move; i++) {
			for (int j = 0; j < m_outW - move; j++) {
				if ((0 <= i && i < m_outH) && (0 <= j && j < m_outW))
					m_outImage[i + move][j + move] = m_inImage[i][j];
			}
		}
	}
	else // 좌측 상단으로 이동
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if ((0 - move <= i && i < m_outH) && (0 - move <= j && j < m_outW))
					m_outImage[i + move][j + move] = m_inImage[i][j];
			}
		}
}


void CGrayscale영상처리MFCDoc::OnRotatImage()
{
	CConstantRotat dlg;
	if (dlg.DoModal() != IDOK)
		return;

	Onfree2D(m_outImage, m_outH);
	int degree = (int)dlg.m_constant_rotat;
	double tmp_angle = fmod((double)degree, 90.0) * 3.141592 / 180.0;
	double tmp_angle90 = (90.0 - fmod((double)degree, 90.0)) * 3.141592 / 180.0;
	m_outImage = NULL;
	m_outH = m_outW = 0;
	m_outH = (int)(m_inH * cos(tmp_angle90) + m_inW * cos(tmp_angle));
	m_outW = (int)(m_inW * cos(tmp_angle) + m_inH * cos(tmp_angle90));
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);


	double angle = degree * 3.141592 / 180.0;
	int dx = (m_outW - m_inW) / 2;
	int dy = (m_outH - m_inH) / 2;
	unsigned char** tmp_image = OnMalloc2D(m_outH, m_outW, 0);
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			tmp_image[i + dx][j + dy] = m_inImage[i][j];
		}
	}
	int cx = m_outW / 2;
	int cy = m_outH / 2;

	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			int xd = i;
			int yd = j;
			int xs = (int)(cos(angle) * (xd - cx) + sin(angle) * (yd - cy)) + cx;
			int ys = (int)(-sin(angle) * (xd - cx) + cos(angle) * (yd - cy)) + cy;
			if (0 <= xs && xs < m_outH && 0 <= ys && ys < m_outW) {
				m_outImage[xd][yd] = tmp_image[xs][ys];
			}
		}
	}
	for (int i = 0; i < m_outH; i++) {
		free(tmp_image[i]);
	}
	free(tmp_image);

}


//void CGrayscale영상처리MFCDoc::OnScaleImage()
//{
//	// TODO: 여기에 구현 코드 추가.
//}


void CGrayscale영상처리MFCDoc::OnScaleReduct()
{
	CConstantScale dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int scale = (int)dlg.m_constant_scale;

	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = (int)(m_inH / scale);
	m_outW = (int)(m_inW / scale);
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	int count, median = 0;
	for (int i = 0; i < m_outH; i++) { // 중간값으로 축소
		for (int j = 0; j < m_outW; j++) {
			int histo[256] = { 0, };
			for (int k = i * scale; k < ((i + 1) * scale); k++) {
				for (int q = j * scale; q < ((j + 1) * scale); q++) {
					// 히스토그램 계산
					histo[m_inImage[k][q]] += 1;
				}
			}
			count = 0;
			for (int a = 0; a < 256; a++) {
				count += histo[a];
				// 중간 값 계산
				if (count >= (scale * scale) / 2) {
					median = a;
					break;
				}
			}
			m_outImage[i][j] = median;
		}
	}
}


void CGrayscale영상처리MFCDoc::OnScaleExpand()
{
	CConstantScale dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
		// 메모리 해제
	int scale = (int)dlg.m_constant_scale;
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = (int)m_inH * scale;
	m_outW = (int)m_inW * scale;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	int y1, x1, y2, x2;
	float y_orig, x_orig, y_diff, x_diff;
	int val1, val2, val3, val4;
	for (int y = 0; y < m_outH; y++) {
		for (int x = 0; x < m_outW; x++) {
			y_orig = y / scale;
			x_orig = x / scale;

			y1 = (int)floor(y_orig);
			x1 = (int)floor(x_orig);
			y2 = (int)ceil(y_orig);
			x2 = (int)ceil(x_orig);

			y_diff = y_orig - y1;
			x_diff = x_orig - x1;

			val1 = m_inImage[y1][x1];
			val2 = m_inImage[y1][x2];
			val3 = m_inImage[y2][x1];
			val4 = m_inImage[y2][x2];

			m_outImage[y][x] = (int)(val1 * (1 - x_diff) * (1 - y_diff) +
				val2 * x_diff * (1 - y_diff) +
				val3 * (1 - x_diff) * y_diff +
				val4 * x_diff * y_diff);
		}
	}
}


void CGrayscale영상처리MFCDoc::OnMirrorImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantMirror btn;
	if (btn.DoModal() != IDOK)
		return;

	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	
	if (btn.m_radio_index == 0) {
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				// 상-하
				m_outImage[-(i - m_outH + 1)][j] = m_inImage[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				// 좌-우
				m_outImage[i][-(j - m_outW + 1)] = m_inImage[i][j];
			}
		}
	}
}


void CGrayscale영상처리MFCDoc::OnEmbossImage()
{
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;

	// 메모리 해제 및 할당
	Onfree2D(m_outImage, m_outH);
	m_outImage = OnMalloc2D(m_inH, m_inW, 0);

	int size;
	if (btn.m_conv_index3 == 0)
		size = 3;
	else if (btn.m_conv_index3 == 1)
		size = 5;
	else if (btn.m_conv_index3 == 2)
		size = 7;
	else if (btn.m_conv_index3 == 3)
		size = 9;

	double** mask = OnmallocDouble2D(size, size, 0);
	// 엠보싱 마스크 생성
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == 0 && j == 0)
				mask[i][j] = -1.0;
			else if (i == size - 1 && j == size - 1)
				mask[i][j] = 1.0;
			else
				mask[i][j] = 0.0;
		}
	}

	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, size);

	// 마스크 값의 합에 따라 후처리 (엠보싱만)
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			tmpOutImage[i][j] += 127.0;
		}
	}

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, size);
	OnfreeDouble2D(tmpOutImage, m_outH);
}

void CGrayscale영상처리MFCDoc::OnBlurrImage()
{
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;

	// 메모리 해제 및 할당
	Onfree2D(m_outImage, m_outH);
	m_outImage = OnMalloc2D(m_inH, m_inW, 0);

	int size;
	if (btn.m_conv_index3 == 0)
		size = 3;
	else if (btn.m_conv_index3 == 1)
		size = 5;
	else if (btn.m_conv_index3 == 2)
		size = 7;
	else if (btn.m_conv_index3 == 3)
		size = 9;

	double** mask = OnmallocDouble2D(size, size, 0);
	// 평균 마스크 생성
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mask[i][j] = 1 / (double)(size * size);
		}
	}

	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, size);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, size);
	OnfreeDouble2D(tmpOutImage, m_outH);
}

void CGrayscale영상처리MFCDoc::OnSmothImage()
{
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;
	CConstantDigF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	double sigma = (double)dlg.m_constant_f;

	// 메모리 해제 및 할당
	Onfree2D(m_outImage, m_outH);
	m_outImage = OnMalloc2D(m_inH, m_inW, 0);

	int size;
	if (btn.m_conv_index3 == 0)
		size = 3;
	else if (btn.m_conv_index3 == 1)
		size = 5;
	else if (btn.m_conv_index3 == 2)
		size = 7;
	else if (btn.m_conv_index3 == 3)
		size = 9;

	double** mask = OnmallocDouble2D(size, size, 0);
	double gaussian;
	int center = size / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// 가우시안 마스크 생성
			double x = sqrt((pow((i - center), 2) + pow((j - center), 2)));
			gaussian = exp(-(x * x) / (2.0 * sigma * sigma)) / (sigma * sqrt(2.0 * 3.141592));
			mask[i][j] = gaussian;
		}
	}

	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, size);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, size);
	OnfreeDouble2D(tmpOutImage, m_outH);
}

void CGrayscale영상처리MFCDoc::OnSharpImage()
{
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;

	// 메모리 해제 및 할당
	Onfree2D(m_outImage, m_outH);
	m_outImage = OnMalloc2D(m_inH, m_inW, 0);

	int size;
	if (btn.m_conv_index3 == 0)
		size = 3;
	else if (btn.m_conv_index3 == 1)
		size = 5;
	else if (btn.m_conv_index3 == 2)
		size = 7;
	else if (btn.m_conv_index3 == 3)
		size = 9;

	double** mask = OnmallocDouble2D(size, size, 0);
	int center = size / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// 샤프닝 마스크 생성
			if (i == center && j == center)
				mask[i][j] = (double)size * size;
			else
				mask[i][j] = -1.0;
		}
	}

	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, size);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, size);
	OnfreeDouble2D(tmpOutImage, m_outH);
}


double** CGrayscale영상처리MFCDoc::OnmallocDouble2D(int h, int w, int initVal)
{
	double** retMemory;
	retMemory = new double* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];

	return retMemory;
}


void CGrayscale영상처리MFCDoc::OnfreeDouble2D(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}

// 잘못 만듦
//double** CGrayscale영상처리MFCDoc::ConvOperation(double** inputImage, int h, int w, double** mask, int maskSize)
//{
	//// TODO: 여기에 구현 코드 추가.
	//int paddedH = h + (maskSize - 1);
	//int paddedW = w + (maskSize - 1);
	//double** paddedImage = OnmallocDouble2D(paddedH, paddedW, 0);
	//double** outputImage = OnmallocDouble2D(h, w, 0);

	//// 입력 이미지를 패딩된 이미지에 복사
	//for (int i = 0; i < h; i++) {
	//	for (int j = 0; j < w; j++) {
	//		paddedImage[i + 1][j + 1] = inputImage[i][j];
	//	}
	//}

	//// 컨볼루션 연산
	//double sum;
	//for (int i = 0; i < h; i++) {
	//	for (int j = 0; j < w; j++) {
	//		sum = 0;
	//		for (int k = 0; k < maskSize; k++) {
	//			for (int q = 0; q < maskSize; q++) {
	//				sum += paddedImage[i + k][j + q] * mask[k][q];
	//			}
	//		}
	//		outputImage[i][j] = sum;
	//	}
	//}

	//OnfreeDouble2D(paddedImage, paddedH);
	//return outputImage;
//}


double** CGrayscale영상처리MFCDoc::OnConvolution(unsigned char** inputImage, int h, int w, double** mask, int maskSize)
{
	// TODO: 여기에 구현 코드 추가.
	int paddedH = h + (maskSize - 1);
	int paddedW = w + (maskSize - 1);
	double** paddedImage = OnmallocDouble2D(paddedH, paddedW, 0);
	double** outputImage = OnmallocDouble2D(m_outH, m_outW, 0);

	// 입력 이미지를 패딩된 이미지에 복사
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			paddedImage[i + (maskSize - 1)][j + (maskSize - 1)] = inputImage[i][j];
		}
	}

	// 컨볼루션 연산
	double sum;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			sum = 0;
			for (int k = 0; k < maskSize; k++) {
				for (int q = 0; q < maskSize; q++) {
					sum += paddedImage[i + k][j + q] * mask[k][q];
				}
			}
			outputImage[i][j] = sum;
		}
	}

	OnfreeDouble2D(paddedImage, paddedH);
	return outputImage;
}


void CGrayscale영상처리MFCDoc::OnPrewittVer()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	double** mask = OnmallocDouble2D(3, 3, 0);

	// 마스크 초기화
	mask[0][0] = -1.; mask[0][1] = 0.; mask[0][2] = 1.;
	mask[1][0] = -1.; mask[1][1] = 0.; mask[1][2] = 1.;
	mask[2][0] = -1.; mask[2][1] = 0.; mask[2][2] = 1.;
	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, 3);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, 3);
	OnfreeDouble2D(tmpOutImage, m_outH);
}


void CGrayscale영상처리MFCDoc::OnPrewittHo()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	double** mask = OnmallocDouble2D(3, 3, 0);

	// 마스크 초기화
	mask[0][0] = -1.; mask[0][1] = -1.; mask[0][2] = -1.;
	mask[1][0] = 0.; mask[1][1] = 0.; mask[1][2] = 0.;
	mask[2][0] = 1.; mask[2][1] = 1.; mask[2][2] = 1.;
	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, 3);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, 3);
	OnfreeDouble2D(tmpOutImage, m_outH);
}


void CGrayscale영상처리MFCDoc::OnSobelVer()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	double** mask = OnmallocDouble2D(3, 3, 0);

	// 마스크 초기화
	mask[0][0] = -1.; mask[0][1] = 0.; mask[0][2] = 1.;
	mask[1][0] = -2.; mask[1][1] = 0.; mask[1][2] = 2.;
	mask[2][0] = -1.; mask[2][1] = 0.; mask[2][2] = 1.;
	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, 3);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, 3);
	OnfreeDouble2D(tmpOutImage, m_outH);
}


void CGrayscale영상처리MFCDoc::OnSobelHo()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	double** mask = OnmallocDouble2D(3, 3, 0);

	// 마스크 초기화
	mask[0][0] = -1.; mask[0][1] = -2.; mask[0][2] = -1.;
	mask[1][0] = 0.; mask[1][1] = 0.; mask[1][2] = 0.;
	mask[2][0] = 1.; mask[2][1] = 2.; mask[2][2] = 1.;
	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, 3);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, 3);
	OnfreeDouble2D(tmpOutImage, m_outH);
}


void CGrayscale영상처리MFCDoc::OnLaplace()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	double** mask = OnmallocDouble2D(3, 3, 0);

	// 마스크 초기화
	mask[0][0] = 0.; mask[0][1] = 1.; mask[0][2] = 0.;
	mask[1][0] = 1.; mask[1][1] = -4.; mask[1][2] = 1.;
	mask[2][0] = 0.; mask[2][1] = 1.; mask[2][2] = 0.;
	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, 3);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, 3);
	OnfreeDouble2D(tmpOutImage, m_outH);
}


void CGrayscale영상처리MFCDoc::OnLog()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	double** mask = OnmallocDouble2D(5, 5, 0);

	// 마스크 초기화
	mask[0][0] = 0; mask[0][1] = 0; mask[0][2] = -1; mask[0][3] = 0; mask[0][4] = 0;
	mask[1][0] = 0; mask[1][1] = -1; mask[1][2] = -2; mask[1][3] = -1; mask[1][4] = 0;
	mask[2][0] = -1; mask[2][1] = -2; mask[2][2] = 16; mask[2][3] = -2; mask[2][4] = -1;
	mask[3][0] = 0; mask[3][1] = -1; mask[3][2] = -2; mask[3][3] = -1; mask[3][4] = 0;
	mask[4][0] = 0; mask[4][1] = 0; mask[4][2] = -1; mask[4][3] = 0; mask[4][4] = 0;
	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, 5);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, 5);
	OnfreeDouble2D(tmpOutImage, m_outH);
}


void CGrayscale영상처리MFCDoc::OnDog()
{
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	Onfree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	double** mask = OnmallocDouble2D(7, 7, 0);

	// 마스크 초기화
	mask[0][0] = 0; mask[0][1] = 0; mask[0][2] = -1; mask[0][3] = -1; mask[0][4] = -1; mask[0][5] = 0; mask[0][6] = 0;
	mask[1][0] = 0; mask[1][1] = -2; mask[1][2] = -3; mask[1][3] = -3; mask[1][4] = -3; mask[1][5] = -2; mask[1][6] = 0;
	mask[2][0] = -1; mask[2][1] = -3; mask[2][2] = 5; mask[2][3] = 5; mask[2][4] = 5; mask[2][5] = -3; mask[2][6] = -1;
	mask[3][0] = -1; mask[3][1] = -3; mask[3][2] = 5; mask[3][3] = 16; mask[3][4] = 5; mask[3][5] = -3; mask[3][6] = -1;
	mask[4][0] = -1; mask[4][1] = -3; mask[4][2] = 5; mask[4][3] = 5; mask[4][4] = 5; mask[4][5] = -3; mask[4][6] = -1;
	mask[5][0] = 0; mask[5][1] = -2; mask[5][2] = -3; mask[5][3] = -3; mask[5][4] = -3; mask[5][5] = -2; mask[5][6] = 0;
	mask[6][0] = 0; mask[6][1] = 0; mask[6][2] = -1; mask[6][3] = -1; mask[6][4] = -1; mask[6][5] = 0; mask[6][6] = 0;
	double** tmpOutImage = OnConvolution(m_inImage, m_inH, m_inW, mask, 7);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			if (tmpOutImage[i][j] < 0.0)
				m_outImage[i][j] = 0;
			else if (tmpOutImage[i][j] > 255.0)
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
		}
	}

	OnfreeDouble2D(mask, 7);
	OnfreeDouble2D(tmpOutImage, m_outH);
}
