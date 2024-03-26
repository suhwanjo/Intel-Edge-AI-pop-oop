
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

#include <propkey.h>

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
