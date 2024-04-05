
// Color Image 영상처리Doc.cpp: CColorImage영상처리Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Color Image 영상처리.h"
#endif

#include "Color Image 영상처리Doc.h"
#include "ConstantF.h"
#include "Constant2.h"
#include "ConstantEmphChannel.h"
#include "ConstantDig.h"
#include "ConstantPara.h"
#include "ConstantMorph.h"
#include "CConstantScale2.h"
#include "ConstantScale.h"
#include "ConstantMirror.h"
#include "ConstantConv.h"
#include "ConstantEdge.h"
#include "ConstantLog.h"
#include "ConstantDog.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImage영상처리Doc

IMPLEMENT_DYNCREATE(CColorImage영상처리Doc, CDocument)

BEGIN_MESSAGE_MAP(CColorImage영상처리Doc, CDocument)
END_MESSAGE_MAP()


// CColorImage영상처리Doc 생성/소멸

CColorImage영상처리Doc::CColorImage영상처리Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImage영상처리Doc::~CColorImage영상처리Doc()
{
}

BOOL CColorImage영상처리Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CColorImage영상처리Doc serialization

void CColorImage영상처리Doc::Serialize(CArchive& ar)
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
void CColorImage영상처리Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CColorImage영상처리Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImage영상처리Doc::SetSearchContent(const CString& value)
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

// CColorImage영상처리Doc 진단

#ifdef _DEBUG
void CColorImage영상처리Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImage영상처리Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImage영상처리Doc 명령


unsigned char** CColorImage영상처리Doc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;
	retMemory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];

	return retMemory;
}


BOOL CColorImage영상처리Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 메모리 해제, 관련 값 초기화
	if (m_inImageR != NULL) {
		OnFree2D(m_inImageR, m_inH);
		OnFree2D(m_inImageG, m_inH);
		OnFree2D(m_inImageB, m_inH);
		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}

	CImage image;
	image.Load(lpszPathName);
	// (중요!) 입력 영상 폭과 높이 결정
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	// 메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage 객체에서 메모리로 읽기
	COLORREF px;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			px = image.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);

		}
	}

	return TRUE;
}

template <typename T>
void CColorImage영상처리Doc::OnFree2D(T** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


void CColorImage영상처리Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);

	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);

	CDocument::OnCloseDocument();
}


void CColorImage영상처리Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}


void CColorImage영상처리Doc::OnFreeOutimage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}
}


void CColorImage영상처리Doc::OnGaryImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// G = (R + G + B) / 3
			avg = (m_inImageR[i][k]+ m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageG[i][k] = (unsigned char)avg; 
			m_outImageB[i][k] = (unsigned char)avg; 
			m_outImageR[i][k] = (unsigned char)avg;
		}
	}
}


BOOL CColorImage영상처리Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;
	CImage image;
	image.Create(m_outW, m_outH, 32);

	unsigned char R, G, B;
	COLORREF px;
	for (int i = 0; i < m_outW; i++) {
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);

	return TRUE;
}


void CColorImage영상처리Doc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = 255 - m_inImageR[i][k];
			m_outImageG[i][k] = 255 - m_inImageG[i][k];
			m_outImageB[i][k] = 255 - m_inImageB[i][k];
		}
	}
}


void CColorImage영상처리Doc::OnPostImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	int levels = 8;
	for (int i = 0; i < m_inH; i++) { // 경계값 -> 양자화로 변경
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = (m_inImageR[i][j] / (256 / levels)) * (256 / levels);
			m_outImageG[i][j] = (m_inImageG[i][j] / (256 / levels)) * (256 / levels);
			m_outImageB[i][j] = (m_inImageB[i][j] / (256 / levels)) * (256 / levels);
		}
	}
}


void CColorImage영상처리Doc::OnGammaImage()
{
	CConstantF dlg;
	if (dlg.DoModal() != IDOK)
		return
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double gam = (double)dlg.m_constant_f;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = pow(((double)m_inImageR[i][j] / 255.0), gam) * 255.0;
			m_outImageG[i][j] = pow(((double)m_inImageG[i][j] / 255.0), gam) * 255.0;
			m_outImageB[i][j] = pow(((double)m_inImageB[i][j] / 255.0), gam) * 255.0;
		}
	}
}


void CColorImage영상처리Doc::OnEmphImage()
{
	CConstant2 dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int targetR = (int)dlg.m_constant1; 
	int targetG = (int)dlg.m_constant2; 
	int targetB = (int)dlg.m_constant3;
	// 기준 색상으로부터 강조할 범위
	int tolerance = (int)dlg.m_constant4;
	// 기준 색상
	m_selectedColor = RGB(targetR, targetG, targetB);
	// 범위 강조 함수 시에만 기준 색상 출력
	m_emphImageExecuted = true;

	int grayscale, distance = 0;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 입력 영상 픽셀 색상과 기준 색상의 거리 계산
			distance = sqrt(pow(m_inImageR[i][j] - targetR, 2) + pow(m_inImageG[i][j] - targetG, 2) + pow(m_inImageB[i][j] - targetB, 2));
			// 거리가 기준 색상으로부터 범위 내에 있다면 색상 출력
			if (distance <= tolerance) {
				m_outImageR[i][j] = m_inImageR[i][j];
				m_outImageG[i][j] = m_inImageG[i][j];
				m_outImageB[i][j] = m_inImageB[i][j];
			}
			else { // 범위 밖에 있다면 흑백으로 출력
				grayscale = (m_inImageR[i][j] + m_inImageG[i][j] + m_inImageB[i][j]) / 3; 
				m_outImageR[i][j] = grayscale;
				m_outImageG[i][j] = grayscale;
				m_outImageB[i][j] = grayscale;
			}
		}
	}
	
}


void CColorImage영상처리Doc::OnStaurChange()
{
	CConstantMorph dlg;
	if (dlg.DoModal() != IDOK)
		return;
	double val = (double)dlg.m_constant_morph;
	// TODO: 여기에 구현 코드 추가.	
	// // 기존 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// H(색상) : 0 ~ 360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB -> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][j];
			G = m_inImageG[i][j];
			B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];

			// 채도(S) 감소(흐리게)
			S = S - val;
			if (S < 0)
				S = 0;

			// HSI -> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0];
			G = rgb[1];
			B = rgb[2];
			m_outImageR[i][j] = R;
			m_outImageG[i][j] = G;
			m_outImageB[i][j] = B;
		}
	}

}


double* CColorImage영상처리Doc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


unsigned char* CColorImage영상처리Doc::HSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}


void CColorImage영상처리Doc::OnAddImage()  // HSI 사용해서 구현하기 실패
{
	CConstantDig dlg;
	if (dlg.DoModal() != IDOK)
		return
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImageR[i][j] + val <= 255) 
				m_outImageR[i][j] = m_inImageR[i][j] + val;
			else
				m_outImageR[i][j] = 255;
			if (m_inImageG[i][j] + val <= 255) 
				m_outImageG[i][j] = m_inImageG[i][j] + val;
			else
				m_outImageG[i][j] = 255;
			if (m_inImageB[i][j] + val <= 255)
				m_outImageB[i][j] = m_inImageB[i][j] + val;
			else
				m_outImageB[i][j] = 255;
		}
	}


}


void CColorImage영상처리Doc::OnSubImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDig dlg;
	if (dlg.DoModal() != IDOK)
		return
		// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// I(명도) : 0 ~ 255

			// RGB -> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][j];
			G = m_inImageG[i][j];
			B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];

			if (I - val >= 0.0) // I(명도) 감소
				I = I - val;
			else
				I = 0.0;

			// HSI -> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0];
			G = rgb[1];
			B = rgb[2];
			m_outImageR[i][j] = R;
			m_outImageG[i][j] = G;
			m_outImageB[i][j] = B;
		}
	}
}


void CColorImage영상처리Doc::OnBinaryImage()
{
	CConstantDig dlg;
	if (dlg.DoModal() != IDOK)
		return
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double val = (double)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// I(명도) : 0 ~ 255

			// RGB -> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][j];
			G = m_inImageG[i][j];
			B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];

			if (I > val) {  // 입력 받은 값을 기준으로 I(명도) 이진화
				I = 255.0;
				H = 0.0;
				S = 0.0;
			}
			else
				I = 0.0;

			// HSI -> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0];
			G = rgb[1];
			B = rgb[2];
			m_outImageR[i][j] = R;
			m_outImageG[i][j] = G;
			m_outImageB[i][j] = B;
		}
	}
}


void CColorImage영상처리Doc::OnBinaryMid()
{
		// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int intensities[256] = { 0 };
	int total_pixels = m_inH * m_inW;
	int median = 0;

	// I 값의 히스토그램 계산
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			unsigned char R = m_inImageR[i][j];
			unsigned char G = m_inImageG[i][j];
			unsigned char B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			int I = (int)(hsi[2]);
			intensities[I]++;
		}
	}
	// 중간값 계산
	int count = 0;
	for (int i = 0; i < 256; i++) {
		count += intensities[i];
		if (count >= total_pixels / 2) {
			median = i;
			break;
		}
	}
	CString message;
	message.Format(_T("이미지의 중앙값은 %d 입니다."), median);  // 중앙값 출력
	MessageBox(AfxGetMainWnd()->GetSafeHwnd(), message, _T("알림"), MB_OK);
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			unsigned char R = m_inImageR[i][j];
			unsigned char G = m_inImageG[i][j];
			unsigned char B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			double H = hsi[0];
			double S = hsi[1];
			double I = hsi[2];

			if (I >= median) {
				I = 255.0;
				H = 0.0;
				S = 0.0;
			}
			else {
				I = 0.0;
				H = 0.0;
				S = 0.0;
			}

			unsigned char* rgb = HSI2RGB(H, S, I);
			m_outImageR[i][j] = rgb[0];
			m_outImageG[i][j] = rgb[1];
			m_outImageB[i][j] = rgb[2];
		}
	}
}


void CColorImage영상처리Doc::OnBinaryAvg()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double sum = 0.0;
	// I값의 합 계산
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			unsigned char R = m_inImageR[i][j];
			unsigned char G = m_inImageG[i][j];
			unsigned char B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			double I = hsi[2];
			sum += I;
		}
	}
	// I값의 평균 계산
	double mean = sum / (m_inH * m_inW);

	CString message;
	message.Format(_T("이미지의 평균값은 %d 입니다."), (int)mean);
	MessageBox(AfxGetMainWnd()->GetSafeHwnd(), message, _T("알림"), MB_OK);
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			unsigned char R = m_inImageR[i][j];
			unsigned char G = m_inImageG[i][j];
			unsigned char B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			double H = hsi[0];
			double S = hsi[1];
			double I = hsi[2];

			if (I >= mean) {
				I = 255.0;
				H = 0.0;
				S = 0.0;
			}
			else {
				I = 0.0;
				H = 0.0;
				S = 0.0;
			}

			unsigned char* rgb = HSI2RGB(H, S, I);
			m_outImageR[i][j] = rgb[0];
			m_outImageG[i][j] = rgb[1];
			m_outImageB[i][j] = rgb[2];
		}
	}
}


void CColorImage영상처리Doc::OnParaImage()
{
	CConstantPara btn;
	if (btn.DoModal() != IDOK)
		return	
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	if (btn.m_radio_para == 0) { // 첫 번째 라디오 버튼이 클릭될 경우, CAP
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i][j] = 255.0 * pow(((double)m_inImageR[i][j] / 127.0 - 1.0), 2.0); 
				m_outImageG[i][j] = 255.0 * pow(((double)m_inImageG[i][j] / 127.0 - 1.0), 2.0); 
				m_outImageB[i][j] = 255.0 * pow(((double)m_inImageB[i][j] / 127.0 - 1.0), 2.0); 
			}
		}
	}
	else if (btn.m_radio_para == 1) {  // CUP
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i][j] = 255.0 - 255.0 * pow(((double)m_inImageR[i][j] / 127.0 - 1.0), 2.0); 
				m_outImageG[i][j] = 255.0 - 255.0 * pow(((double)m_inImageG[i][j] / 127.0 - 1.0), 2.0); 
				m_outImageB[i][j] = 255.0 - 255.0 * pow(((double)m_inImageB[i][j] / 127.0 - 1.0), 2.0); 
			}
		}
	}

}


void CColorImage영상처리Doc::OnHistoStretch()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int highR = m_inImageR[0][0];
	int lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0];
	int lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0];
	int lowB = m_inImageB[0][0];
	// 각 채널의 최대 최소값 구하기
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImageR[i][j] < lowR)
				lowR = m_inImageR[i][j];
			if (m_inImageR[i][j] > highR)
				highR = m_inImageR[i][j];

			if (m_inImageG[i][j] < lowG)
				lowG = m_inImageG[i][j];
			if (m_inImageG[i][j] > highG)
				highG = m_inImageG[i][j];

			if (m_inImageB[i][j] < lowB)
				lowB = m_inImageB[i][j];
			if (m_inImageB[i][j] > highB)
				highB = m_inImageB[i][j];
		}
	}
	// 스트레칭
	for (int i = 0; i < m_inH; i++) {  // End-In 탐색
		for (int j = 0; j < m_inW; j++) {
			int newValR, newValG, newValB;

			if (m_inImageR[i][j] < lowR)
				newValR = 0;
			else if (m_inImageR[i][j] > highR)
				newValR = 255;
			else
				newValR = (int)((m_inImageR[i][j] - lowR) / (double)(highR - lowR) * 255.0);

			if (m_inImageG[i][j] < lowG)
				newValG = 0;
			else if (m_inImageG[i][j] > highG)
				newValG = 255;
			else
				newValG = (int)((m_inImageG[i][j] - lowG) / (double)(highG - lowG) * 255.0);

			if (m_inImageB[i][j] < lowB)
				newValB = 0;
			else if (m_inImageB[i][j] > highB)
				newValB = 255;
			else
				newValB = (int)((m_inImageB[i][j] - lowB) / (double)(highB - lowB) * 255.0);

			m_outImageR[i][j] = newValR;
			m_outImageG[i][j] = newValG;
			m_outImageB[i][j] = newValB;
		}
	}
}


void CColorImage영상처리Doc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 1단계 : 빈도수 세기(=히스토그램) histoR[256], histoG[256], histoB[256]
	int histoR[256] = { 0, };
	int histoG[256] = { 0, };
	int histoB[256] = { 0, };
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			histoR[m_inImageR[i][j]]++;
			histoG[m_inImageG[i][j]]++;
			histoB[m_inImageB[i][j]]++;
		}
	}
	// 2단계 : 누적히스토그램 생성
	int sumHistoR[256] = { 0, };
	int sumHistoG[256] = { 0, };
	int sumHistoB[256] = { 0, };
	sumHistoR[0] = histoR[0];
	sumHistoG[0] = histoG[0];
	sumHistoB[0] = histoB[0];
	for (int i = 1; i < 256; i++) {
		sumHistoR[i] = sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] = sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] = sumHistoB[i - 1] + histoB[i];
	}
	// 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
	double normalHistoR[256] = { 0.0 };
	double normalHistoG[256] = { 0.0 };
	double normalHistoB[256] = { 0.0 };
	for (int i = 0; i < 256; i++) {
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = (unsigned char)normalHistoR[m_inImageR[i][j]];
			m_outImageG[i][j] = (unsigned char)normalHistoG[m_inImageG[i][j]];
			m_outImageB[i][j] = (unsigned char)normalHistoB[m_inImageB[i][j]];
		}
	}
}


void CColorImage영상처리Doc::OnMorphImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantMorph dlg;
	if (dlg.DoModal() != IDOK)
		return;
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double val = (double)dlg.m_constant_morph;
	CString filePath;
	CFileDialog dlgFile(TRUE);
	if (dlgFile.DoModal() == IDOK) {
		filePath = dlgFile.GetPathName();

		CImage image2;
		HRESULT hr = image2.Load(filePath);  // 두 번째 이미지 열기
		if (FAILED(hr)) {
			AfxMessageBox(_T("오류: 파일 열기 실패."));
			return;
		}

		int secondImageH = image2.GetHeight();
		int secondImageW = image2.GetWidth();
		if (secondImageH != m_outH || secondImageW != m_outW) {
			AfxMessageBox(_T("오류: 두 이미지의 가로와 세로 크기는 같아야 합니다."));
			return;
		}
		// 모핑 연산
		for (int y = 0; y < m_outH; y++) {
			for (int x = 0; x < m_outW; x++) {
				COLORREF pixel1 = RGB(m_inImageR[y][x], m_inImageG[y][x], m_inImageB[y][x]);
				COLORREF pixel2 = image2.GetPixel(x, y);

				int morphedR = (int)(GetRValue(pixel1) * val + GetRValue(pixel2) * (1 - val));
				int morphedG = (int)(GetGValue(pixel1) * val + GetGValue(pixel2) * (1 - val));
				int morphedB = (int)(GetBValue(pixel1) * val + GetBValue(pixel2) * (1 - val));

				m_outImageR[y][x] = (unsigned char)morphedR;
				m_outImageG[y][x] = (unsigned char)morphedG;
				m_outImageB[y][x] = (unsigned char)morphedB;
			}
		}
	}
	else {
		return;
	}
}


void CColorImage영상처리Doc::OnScaleUp()
{
	CConstantScale dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int scale = (int)dlg.m_constant_scale;
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH * scale;
	m_outW = m_inW * scale;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int y1, x1, y2, x2;
	float y_orig, x_orig, y_diff, x_diff;
	int val1R, val2R, val3R, val4R;
	int val1G, val2G, val3G, val4G;
	int val1B, val2B, val3B, val4B;

	for (int y = 0; y < m_outH; y++) {
		for (int x = 0; x < m_outW; x++) {
			y_orig = y / scale; // 출력 이미지의 좌표를 원본 이미지의 비율로 변환
			x_orig = x / scale; 

			y1 = (int)floor(y_orig); // 실수 좌표에서 가장 가까운 작은 정수 좌표
			x1 = (int)floor(x_orig); 
			y2 = (int)ceil(y_orig); // 실수 좌표에서 가장 가까운 큰 정수 좌표
			x2 = (int)ceil(x_orig); 

			y_diff = y_orig - y1; // 실수 y 좌표와 정수 y 좌표의 차이
			x_diff = x_orig - x1; 

			// 원본 이미지에서 가까운 4개의 픽셀 값을 가져옴
			val1R = m_inImageR[y1][x1]; val1G = m_inImageG[y1][x1]; val1B = m_inImageB[y1][x1];
			val2R = m_inImageR[y1][x2]; val2G = m_inImageG[y1][x2]; val2B = m_inImageB[y1][x2];
			val3R = m_inImageR[y2][x1]; val3G = m_inImageG[y2][x1]; val3B = m_inImageB[y2][x1];
			val4R = m_inImageR[y2][x2]; val4G = m_inImageG[y2][x2]; val4B = m_inImageB[y2][x2];

			// 양선형 보간 공식 적용
			m_outImageR[y][x] = (int)(val1R * (1 - x_diff) * (1 - y_diff) +
				val2R * x_diff * (1 - y_diff) +
				val3R * (1 - x_diff) * y_diff +
				val4R * x_diff * y_diff);

			m_outImageG[y][x] = (int)(val1G * (1 - x_diff) * (1 - y_diff) +
				val2G * x_diff * (1 - y_diff) +
				val3G * (1 - x_diff) * y_diff +
				val4G * x_diff * y_diff);

			m_outImageB[y][x] = (int)(val1B * (1 - x_diff) * (1 - y_diff) +
				val2B * x_diff * (1 - y_diff) +
				val3B * (1 - x_diff) * y_diff +
				val4B * x_diff * y_diff);
		}
	}
}


void CColorImage영상처리Doc::OnScaleDown()
{
	CConstantScale dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int scale = (int)dlg.m_constant_scale;
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH / scale;
	m_outW = m_inW / scale;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// 히스토그램 생성
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			int histR[256] = { 0 };
			int histG[256] = { 0 };
			int histB[256] = { 0 };

			for (int k = i * scale; k < (i + 1) * scale; k++) {
				for (int q = j * scale; q < (j + 1) * scale; q++) {
					histR[m_inImageR[k][q]]++;
					histG[m_inImageG[k][q]]++;
					histB[m_inImageB[k][q]]++;
				}
			}
			// 중간값 찾기
			int medianR = 0, medianG = 0, medianB = 0;
			int countR = 0, countG = 0, countB = 0;
			for (int a = 0; a < 256; a++) {
				countR += histR[a];
				countG += histG[a];
				countB += histB[a];

				if (countR >= (scale * scale) / 2 && medianR == 0) {
					medianR = a;
				}
				if (countG >= (scale * scale) / 2 && medianG == 0) {
					medianG = a;
				}
				if (countB >= (scale * scale) / 2 && medianB == 0) {
					medianB = a;
				}
			}
			m_outImageR[i][j] = medianR;
			m_outImageG[i][j] = medianG;
			m_outImageB[i][j] = medianB;
		}
	}

}


void CColorImage영상처리Doc::OnRotateImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantScale dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	int degree = (int)dlg.m_constant_scale;
	double tmp_angle = fmod((double)degree, 90.0) * 3.141592 / 180.0;
	double tmp_angle90 = (90.0 - fmod((double)degree, 90.0)) * 3.141592 / 180.0;
	m_outH = (int)(m_inH * cos(tmp_angle90) + m_inW * cos(tmp_angle)); // 회전하는 각도에 따라 출력 영상 크기 결정
	m_outW = (int)(m_inW * cos(tmp_angle) + m_inH * cos(tmp_angle90));

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double angle = degree * 3.141592 / 180.0;
	int dx = (m_outW - m_inW) / 2;
	int dy = (m_outH - m_inH) / 2;
	unsigned char** tmp_imageR = OnMalloc2D(m_outH, m_outW);
	unsigned char** tmp_imageG = OnMalloc2D(m_outH, m_outW);
	unsigned char** tmp_imageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {  // 커진 출력 영상의 중앙으로 이동
		for (int j = 0; j < m_inW; j++) {
			tmp_imageR[i + dy][j + dx] = m_inImageR[i][j];  // 거꾸로 되어 있었음 -> dx가 열(column)
			tmp_imageG[i + dy][j + dx] = m_inImageG[i][j];
			tmp_imageB[i + dy][j + dx] = m_inImageB[i][j];
		}
	}
	int cx = m_outW / 2;
	int cy = m_outH / 2;
	// 백워딩으로 회전
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			int xd = i;
			int yd = j;
			int xs = (int)(cos(angle) * (xd - cx) + sin(angle) * (yd - cy)) + cx;
			int ys = (int)(-sin(angle) * (xd - cx) + cos(angle) * (yd - cy)) + cy;
			if (0 <= xs && xs < m_outH && 0 <= ys && ys < m_outW) {
				m_outImageR[xd][yd] = tmp_imageR[xs][ys];
				m_outImageG[xd][yd] = tmp_imageG[xs][ys];
				m_outImageB[xd][yd] = tmp_imageB[xs][ys];
			}
		}
	}
	OnFree2D(tmp_imageR, m_outH);
	OnFree2D(tmp_imageG, m_outH);
	OnFree2D(tmp_imageB, m_outH);
}


void CColorImage영상처리Doc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantScale dlg;
	if (dlg.DoModal() != IDOK)
		return;
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int move = (int)dlg.m_constant_scale;
	if (move >= 0) { // 우측 하단으로 이동
		for (int i = move; i < m_outH; i++) {
			for (int j = move; j < m_outW; j++) {  // 클리핑 필요 없음
				m_outImageR[i][j] = m_inImageR[i - move][j - move];
				m_outImageG[i][j] = m_inImageG[i - move][j - move];
				m_outImageB[i][j] = m_inImageB[i - move][j - move];
			}
		}
	}
	else { // 좌측 상단으로 이동
		for (int i = 0; i < m_outH + move; i++) {
			for (int j = 0; j < m_outW + move; j++) {
				m_outImageR[i][j] = m_inImageR[i - move][j - move];
				m_outImageG[i][j] = m_inImageG[i - move][j - move];
				m_outImageB[i][j] = m_inImageB[i - move][j - move];
			}
		}
	}

}


void CColorImage영상처리Doc::OnMirrorImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantMirror btn;
	if (btn.DoModal() != IDOK)
		return;
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	if (btn.m_radio_mirror == 0) { // 상-하 뒤집기
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				m_outImageR[m_outH - 1 - i][j] = m_inImageR[i][j];
				m_outImageG[m_outH - 1 - i][j] = m_inImageG[i][j];
				m_outImageB[m_outH - 1 - i][j] = m_inImageB[i][j];
			}
		}
	}
	else { // 좌-우 뒤집기
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				m_outImageR[i][m_outW - 1 - j] = m_inImageR[i][j];
				m_outImageG[i][m_outW - 1 - j] = m_inImageG[i][j];
				m_outImageB[i][m_outW - 1 - j] = m_inImageB[i][j];
			}
		}
	}
}


double** CColorImage영상처리Doc::OnmallocDouble2D(int h, int w) // 함수 오버로딩 가능하지만, 반환 값만 달라 헷갈릴 수 있음
{
	double** retMemory;
	retMemory = new double* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];

	return retMemory;
}


void CColorImage영상처리Doc::OnfreeDouble2D(double** memory, int h)
{
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


double** CColorImage영상처리Doc::OnConvolution(unsigned char** inputImage, int h, int w, double** mask, int maskSize)
{
	// TODO: 여기에 구현 코드 추가.
	int paddedH = h + (maskSize - 1);
	int paddedW = w + (maskSize - 1);
	double** paddedImage = OnmallocDouble2D(paddedH, paddedW);
	for (int i = 0; i < paddedH; i++) {
		for (int j = 0; j < paddedW; j++) {
			paddedImage[i][j] = 127.0;
		}
	}
	double** outputImage = OnmallocDouble2D(m_inH, m_inW);
	// 입력 이미지를 패딩된 이미지에 복사
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			paddedImage[i + (int)(maskSize / 2)][j + (int)(maskSize / 2)] = inputImage[i][j];
		}
	}
	// 컨볼루션 연산
	double sum;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			sum = 0.0;
			for (int k = 0; k < maskSize; k++) {
				for (int q = 0; q < maskSize; q++) {
					sum += paddedImage[i + k][j + q] * mask[k][q];
				}
			}
			outputImage[i][j] = sum;
		}
	}
	OnFree2D(paddedImage, paddedH);
	return outputImage;
}


void CColorImage영상처리Doc::OnEmbossImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;

	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// 마스크 크기 설정
	int size;
	if (btn.m_radio_index == 0)
		size = 3;
	else if (btn.m_radio_index == 1)
		size = 5;
	else if (btn.m_radio_index == 2)
		size = 7;
	else if (btn.m_radio_index == 3)
		size = 9;

	double** mask = OnmallocDouble2D(size, size);
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
	double** tmpOutImageR = OnConvolution(m_inImageR, m_inH, m_inW, mask, size);
	double** tmpOutImageG = OnConvolution(m_inImageG, m_inH, m_inW, mask, size);
	double** tmpOutImageB = OnConvolution(m_inImageB, m_inH, m_inW, mask, size);

	// 마스크 값의 합에 따라 후처리 (엠보싱만)
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			tmpOutImageR[i][j] += 127.0;
			tmpOutImageG[i][j] += 127.0;
			tmpOutImageB[i][j] += 127.0;
		}
	}
	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R 채널 클리핑
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (tmpOutImageR[i][j] > 255.0)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G 채널 클리핑
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (tmpOutImageG[i][j] > 255.0)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B 채널 클리핑
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (tmpOutImageB[i][j] > 255.0)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}
	OnFree2D(mask, size);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnBlurrImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;
	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int size;
	if (btn.m_radio_index == 0)
		size = 3;
	else if (btn.m_radio_index == 1)
		size = 5;
	else if (btn.m_radio_index == 2)
		size = 7;
	else if (btn.m_radio_index == 3)
		size = 9;
	double** mask = OnmallocDouble2D(size, size);
	// 평균 마스크 생성
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mask[i][j] = 1 / (double)(size * size);
		}
	}
	double** tmpOutImageR = OnConvolution(m_inImageR, m_inH, m_inW, mask, size);
	double** tmpOutImageG = OnConvolution(m_inImageG, m_inH, m_inW, mask, size);
	double** tmpOutImageB = OnConvolution(m_inImageB, m_inH, m_inW, mask, size);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R 채널 클리핑
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (tmpOutImageR[i][j] > 255.0)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];
			// G 채널 클리핑
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (tmpOutImageG[i][j] > 255.0)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];
			// B 채널 클리핑
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (tmpOutImageB[i][j] > 255.0)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}
	OnFree2D(mask, size);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnSmoothImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;
	CConstantF dlg;
	if (dlg.DoModal() != IDOK)
		return;
	double sigma = (double)dlg.m_constant_f;

	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int size;
	if (btn.m_radio_index == 0)
		size = 3;
	else if (btn.m_radio_index == 1)
		size = 5;
	else if (btn.m_radio_index == 2)
		size = 7;
	else if (btn.m_radio_index == 3)
		size = 9;
	double** mask = OnmallocDouble2D(size, size);
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
	double** tmpOutImageR = OnConvolution(m_inImageR, m_inH, m_inW, mask, size);
	double** tmpOutImageG = OnConvolution(m_inImageG, m_inH, m_inW, mask, size);
	double** tmpOutImageB = OnConvolution(m_inImageB, m_inH, m_inW, mask, size);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R 채널 클리핑
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (tmpOutImageR[i][j] > 255.0)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];
			// G 채널 클리핑
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (tmpOutImageG[i][j] > 255.0)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];
			// B 채널 클리핑
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (tmpOutImageB[i][j] > 255.0)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}
	OnFree2D(mask, size);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnSharpImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;
	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int size;
	if (btn.m_radio_index == 0)
		size = 3;
	else if (btn.m_radio_index == 1)
		size = 5;
	else if (btn.m_radio_index == 2)
		size = 7;
	else if (btn.m_radio_index == 3)
		size = 9;
	double** mask = OnmallocDouble2D(size, size);
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
	double** tmpOutImageR = OnConvolution(m_inImageR, m_inH, m_inW, mask, size);
	double** tmpOutImageG = OnConvolution(m_inImageG, m_inH, m_inW, mask, size);
	double** tmpOutImageB = OnConvolution(m_inImageB, m_inH, m_inW, mask, size);

	// 임시 출력 영상 -> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R 채널 클리핑
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (tmpOutImageR[i][j] > 255.0)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];
			// G 채널 클리핑
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (tmpOutImageG[i][j] > 255.0)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];
			// B 채널 클리핑
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (tmpOutImageB[i][j] > 255.0)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}
	OnFree2D(mask, size);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnPrewittImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantEdge btn;
	if (btn.DoModal() != IDOK)
		return;
	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 3;

	double** mask = OnmallocDouble2D(size, size);
	double** tmpOutImage = OnmallocDouble2D(m_outH, m_outW);
	unsigned char** grayImage = OnToGrayScale(m_inImageR, m_inImageG, m_inImageB, m_inH, m_inW);

	if (btn.m_radio_edge == 0) { 
		// 수직 마스크
		mask[0][0] = -1.; mask[0][1] = 0.; mask[0][2] = 1.;
		mask[1][0] = -1.; mask[1][1] = 0.; mask[1][2] = 1.;
		mask[2][0] = -1.; mask[2][1] = 0.; mask[2][2] = 1.;

		tmpOutImage = OnConvolution(grayImage, m_inH, m_inW, mask, size);

		// 임시 출력 영상 -> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0) 
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
				else if (tmpOutImage[i][j] > 255.0) 
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}
	}
	else if(btn.m_radio_edge == 1) { 
		// 수평 마스크
		mask[0][0] = -1.; mask[0][1] = -1.; mask[0][2] = -1.;
		mask[1][0] = 0.; mask[1][1] = 0.; mask[1][2] = 0.;
		mask[2][0] = 1.; mask[2][1] = 1.; mask[2][2] = 1.;

		tmpOutImage = OnConvolution(grayImage, m_inH, m_inW, mask, size);

		// 임시 출력 영상 -> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
				else if (tmpOutImage[i][j] > 255.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}
	}
	else {
		CConstantDig dlg;
		if (dlg.DoModal() != IDOK)
			return;
		double** mask1 = OnmallocDouble2D(size, size);
		mask1[0][0] = -1.; mask1[0][1] = 0.; mask1[0][2] = 1.;
		mask1[1][0] = -1.; mask1[1][1] = 0.; mask1[1][2] = 1.;
		mask1[2][0] = -1.; mask1[2][1] = 0.; mask1[2][2] = 1.;

		double** mask2 = OnmallocDouble2D(size, size);
		mask2[0][0] = -1.; mask2[0][1] = -1.; mask2[0][2] = -1.;
		mask2[1][0] = 0.; mask2[1][1] = 0.; mask2[1][2] = 0.;
		mask2[2][0] = 1.; mask2[2][1] = 1.; mask2[2][2] = 1.;

		// 수직 에지와 수평 에지를 구한 후 더함
		double** tmpOutImage_vert = OnConvolution(grayImage, m_inH, m_inW, mask1, size);
		double** tmpOutImage_hori = OnConvolution(grayImage, m_inH, m_inW, mask2, size);
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				//tmpOutImage[i][j] = abs(tmpOutImage_vert[i][j]) + abs(tmpOutImage_hori[i][j]); // 그레디언트 강도 계산
				tmpOutImage[i][j] = sqrt(pow(tmpOutImage_vert[i][j], 2) + pow(tmpOutImage_hori[i][j], 2)); // 그레디언트 강도 계산
			}
		}
		// 임계값 적용 및 이진화
		int threshold = (int)dlg.m_constant; // 임계값은 필요에 따라 조정 가능
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] >= double(threshold))
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
			}
		}
		OnFree2D(mask1, size);
		OnFree2D(mask2, size);
		OnFree2D(tmpOutImage_vert, m_outH);
		OnFree2D(tmpOutImage_hori, m_outH);
	}
	OnFree2D(mask, size);
	OnFree2D(tmpOutImage, m_outH);
	OnFree2D(grayImage, m_inH);
}


void CColorImage영상처리Doc::OnSobelImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantEdge btn;
	if (btn.DoModal() != IDOK)
		return;
	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 3;

	double** mask = OnmallocDouble2D(size, size);
	double** tmpOutImage = OnmallocDouble2D(m_outH, m_outW);
	unsigned char** grayImage = OnToGrayScale(m_inImageR, m_inImageG, m_inImageB, m_inH, m_inW);

	if (btn.m_radio_edge == 0) {
		// 수직 마스크
		mask[0][0] = -1.; mask[0][1] = 0.; mask[0][2] = 1.;
		mask[1][0] = -2.; mask[1][1] = 0.; mask[1][2] = 2.;
		mask[2][0] = -1.; mask[2][1] = 0.; mask[2][2] = 1.;

		tmpOutImage = OnConvolution(grayImage, m_inH, m_inW, mask, size);

		// 임시 출력 영상 -> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
				else if (tmpOutImage[i][j] > 255.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}
	}
	else if (btn.m_radio_edge == 1) { 
		// 수평 마스크
		mask[0][0] = -1.; mask[0][1] = -2.; mask[0][2] = -1.;
		mask[1][0] = 0.; mask[1][1] = 0.; mask[1][2] = 0.;
		mask[2][0] = 1.; mask[2][1] = 2.; mask[2][2] = 1.;

		tmpOutImage = OnConvolution(grayImage, m_inH, m_inW, mask, size);

		// 임시 출력 영상 -> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
				else if (tmpOutImage[i][j] > 255.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}
	}
	else {
		CConstantDig dlg;
		if (dlg.DoModal() != IDOK)
			return;
		double** mask1 = OnmallocDouble2D(size, size);
		mask1[0][0] = -1.; mask1[0][1] = 0.; mask1[0][2] = 1.;
		mask1[1][0] = -1.; mask1[1][1] = 0.; mask1[1][2] = 1.;
		mask1[2][0] = -1.; mask1[2][1] = 0.; mask1[2][2] = 1.;

		double** mask2 = OnmallocDouble2D(size, size);
		mask2[0][0] = -1.; mask2[0][1] = -1.; mask2[0][2] = -1.;
		mask2[1][0] = 0.; mask2[1][1] = 0.; mask2[1][2] = 0.;
		mask2[2][0] = 1.; mask2[2][1] = 1.; mask2[2][2] = 1.;

		// 수직 에지와 수평 에지를 구한 후 더함
		double** tmpOutImage_vert = OnConvolution(grayImage, m_inH, m_inW, mask1, size);
		double** tmpOutImage_hori = OnConvolution(grayImage, m_inH, m_inW, mask2, size);

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				tmpOutImage[i][j] = sqrt(pow(tmpOutImage_vert[i][j], 2) + pow(tmpOutImage_hori[i][j], 2)); // 그레디언트 강도 계산
			}
		}
		// 임계값 적용 및 이진화
		int threshold = (int)dlg.m_constant; // 임계값은 필요에 따라 조정 가능
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] >= double(threshold))
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
			}
		}
		OnFree2D(mask1, size);
		OnFree2D(mask2, size);
		OnFree2D(tmpOutImage_vert, m_outH);
		OnFree2D(tmpOutImage_hori, m_outH);
	}
	OnFree2D(mask, size);
	OnFree2D(tmpOutImage, m_outH);
	OnFree2D(grayImage, m_inH);
}

// 라플라시안 마스크 적용 후 제로 크로싱을 통한 성능 향상 -> 라플라시안(2차 미분 연산)은 결과가 양수와 음수로 나옴. 0에 가까우면 에지가 아님.
void CColorImage영상처리Doc::OnLaplaceImage() 
{
	CConstantDig dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int t = (int)dlg.m_constant;
	// TODO: 여기에 구현 코드 추가.
	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 3;
	double** mask = OnmallocDouble2D(size, size);
	unsigned char** grayImage = OnToGrayScale(m_inImageR, m_inImageG, m_inImageB, m_inH, m_inW);  // 나은 에지 추출을 위해 흑백으로 변환

	// 라플라시안 마스크 초기화
	mask[0][0] = 0.; mask[0][1] = 1.; mask[0][2] = 0.;
	mask[1][0] = 1.; mask[1][1] = -4.; mask[1][2] = 1.;
	mask[2][0] = 0.; mask[2][1] = 1.; mask[2][2] = 0.;

	double** tmpOutImage = OnConvolution(grayImage, m_inH, m_inW, mask, size);

	// 제로 크로싱을 위한 테두리 1칸 0으로 패딩
	double** tmpOutImagePad = OnmallocDouble2D(m_inH + 2, m_inW + 2);
	// 테두리 1칸을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int j = 0; j < m_inW + 2; j++) {
			tmpOutImagePad[i][j] = 127.0;
		}
	}
	// 중심 영역에 tmpOutImage 값 복사
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			tmpOutImagePad[i + 1][j + 1] = tmpOutImage[i][j];
		}
	}
	// zero-crossing
	double isEgde;
	for (int j = 1; j < m_inH - 1; j++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int sum = 0;
			// 좌측 45도 방향에서 부호가 바뀌는지 확인
			if (tmpOutImage[j - 1][k - 1] * tmpOutImage[j + 1][k + 1] < 0) { // 바뀐다면 그 차이가 임계값보다 큰지 확인
				isEgde = abs(tmpOutImage[j - 1][k - 1]) + abs(tmpOutImage[j + 1][k + 1]);
				if (isEgde >= (double)t) 
					sum += 1;
			}
			// 우측 45도 방향에서 부호가 바뀌는지 확인
			if (tmpOutImage[j + 1][k - 1] * tmpOutImage[j - 1][k + 1] < 0) {
				isEgde = abs(tmpOutImage[j - 1][k - 1]) + abs(tmpOutImage[j - 1][k + 1]);
				if (isEgde >= (double)t)
					sum += 1;
			}
			// 세로 방향에서 부호가 바뀌는지 확인
			if (tmpOutImage[j][k - 1] * tmpOutImage[j][k + 1] < 0) {
				isEgde = abs(tmpOutImage[j][k - 1]) + abs(tmpOutImage[j][k + 1]);
				if (isEgde >= (double)t)
					sum += 1;
			}
			// 가로 방향에서 부호가 바뀌는지 확인
			if (tmpOutImage[j - 1][k] * tmpOutImage[j + 1][k] < 0) {
				isEgde = abs(tmpOutImage[j - 1][k]) + abs(tmpOutImage[j + 1][k]);
				if (isEgde >= (double)t)
					sum += 1;
			}
			// 부호가 바뀌는 쌍과 그 차이가 임계값보다 큰 경우가 2쌍 이상이면 에지 처리
			if (sum >= 2)
				tmpOutImagePad[j][k] = 255.0;
			else
				tmpOutImagePad[j][k] = 0.0;
		}
	}
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)tmpOutImagePad[i][j];
		}
	}
	OnFree2D(mask, size);
	OnFree2D(tmpOutImage, m_inH);
	OnFree2D(grayImage, m_inH);
	OnFree2D(tmpOutImagePad, m_inH + 2);
}


void CColorImage영상처리Doc::OnLogImage()
{
	CConstantLog btn;
	if (btn.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
		// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 5;
	unsigned char** grayImage = OnToGrayScale(m_inImageR, m_inImageG, m_inImageB, m_inH, m_inW);

	if (btn.m_radio_log == 0) {  // LOG 마스크 사용
		// 마스크 초기화
		double** mask = OnmallocDouble2D(size, size);
		mask[0][0] = 0.; mask[0][1] = 0.; mask[0][2] = -1.; mask[0][3] = 0.; mask[0][4] = 0.;
		mask[1][0] = 0.; mask[1][1] = -1.; mask[1][2] = -2.; mask[1][3] = -1.; mask[1][4] = 0.;
		mask[2][0] = -1.; mask[2][1] = -2.; mask[2][2] = 16.; mask[2][3] = -2.; mask[2][4] = -1.;
		mask[3][0] = 0.; mask[3][1] = -1.; mask[3][2] = -2.; mask[3][3] = -1.; mask[3][4] = 0.;
		mask[4][0] = 0.; mask[4][1] = 0.; mask[4][2] = -1.; mask[4][3] = 0.; mask[4][4] = 0.;

		double** tmpOutImage = OnConvolution(grayImage, m_inH, m_inW, mask, size);

		// 임시 출력 영상 -> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
				else if (tmpOutImage[i][j] > 255.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}
		OnFree2D(tmpOutImage, m_inH);
		OnFree2D(mask, size);
	}
	else {  // 가우시안 -> 라플라시안 -> 제로 크로싱 (라플라시안에 가우시안을 씌우면 연산량 감소)
		const int size3 = 3;

		// 3x3 라플라시안 마스크 생성 
		double** maskLaplace = OnmallocDouble2D(size3, size3);
		maskLaplace[0][0] = 0.; maskLaplace[0][1] = 1.; maskLaplace[0][2] = 0.;
		maskLaplace[1][0] = 1.; maskLaplace[1][1] = -4.; maskLaplace[1][2] = 1.;
		maskLaplace[2][0] = 0.; maskLaplace[2][1] = 1.; maskLaplace[2][2] = 0.;

		// 3x3 가우시안 마스크 생성
		double** maskGauss = OnmallocDouble2D(size3, size3);
		double gaussian;
		double sigma;
		int center = size3 / 2;
		CConstantF dlg;
		if (dlg.DoModal() != IDOK)
			return;
		sigma = (double)dlg.m_constant_f;  // 시그마 작은 값 넣어야 함
		for (int i = 0; i < size3; i++) {
			for (int j = 0; j < size3; j++) {
				double x = sqrt((pow((i - center), 2) + pow((j - center), 2)));
				gaussian = exp(-(x * x) / (2.0 * sigma * sigma)) / (sigma * sqrt(2.0 * 3.141592));
				maskGauss[i][j] = gaussian;
			}
		}
		// 입력 영상에 가우시안 스무딩 적용
		double** inputGauss = OnConvolution(grayImage, m_inH, m_inW, maskGauss, size3);
		unsigned char** tmp = OnMalloc2D(m_inH, m_inW);
		for (int i = 0; i < m_inH; i++) {  // Onconvolution 함수 오버로딩 하면 되겠지만.. 그냥 형변환해서 사용
			for (int j = 0; j < m_inW; j++) {
				tmp[i][j] = (unsigned char)inputGauss[i][j];
			}
		}
		// 스무딩 된 입력 영상에 라플라시안 적용
		double** outputImage = OnConvolution(tmp, m_inH, m_inW, maskLaplace, size3);

		// 제로 크로싱을 위한 테두리 1칸 0으로 패딩
		int paddedH = m_inH + 2;
		int paddedW = m_inW + 2;
		double** paddedImage = OnmallocDouble2D(paddedH, paddedW);
		// 테두리 1칸을 0으로 초기화
		for (int i = 0; i < paddedH; i++) {
			for (int j = 0; j < paddedW; j++) {
				paddedImage[i][j] = 0.0;
			}
		}
		// 중심 영역에 outputImage 값 복사
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				paddedImage[i + 1][j + 1] = outputImage[i][j];
			}
		}
		// zero-crossing
		CConstantDig dlg2;
		if (dlg2.DoModal() != IDOK)
			return;
		int t = (int)dlg2.m_constant;
		double isEgde;
		for (int j = 1; j < m_inH - 1; j++) {
			for (int k = 1; k < m_inW - 1; k++) {
				int sum = 0;
				// 좌측 45도 방향에서 부호가 바뀌는지 확인
				if (outputImage[j - 1][k - 1] * outputImage[j + 1][k + 1] < 0) { // 바뀐다면 그 차이가 임계값보다 큰지 확인
					isEgde = abs(outputImage[j - 1][k - 1]) + abs(outputImage[j + 1][k + 1]);
					if (isEgde >= (double)t)
						sum += 1;
				}
				// 우측 45도 방향에서 부호가 바뀌는지 확인
				if (outputImage[j + 1][k - 1] * outputImage[j - 1][k + 1] < 0) {
					isEgde = abs(outputImage[j - 1][k - 1]) + abs(outputImage[j - 1][k + 1]);
					if (isEgde >= (double)t)
						sum += 1;
				}
				// 세로 방향에서 부호가 바뀌는지 확인
				if (outputImage[j][k - 1] * outputImage[j][k + 1] < 0) {
					isEgde = abs(outputImage[j][k - 1]) + abs(outputImage[j][k + 1]);
					if (isEgde >= (double)t)
						sum += 1;
				}
				// 가로 방향에서 부호가 바뀌는지 확인
				if (outputImage[j - 1][k] * outputImage[j + 1][k] < 0) {
					isEgde = abs(outputImage[j - 1][k]) + abs(outputImage[j + 1][k]);
					if (isEgde >= (double)t)
						sum += 1;
				}
				// 부호가 바뀌는 쌍과 그 차이가 임계값보다 큰 경우가 2쌍 이상이면 에지 처리
				if (sum >= 2)
					paddedImage[j][k] = 255.0;
				else
					paddedImage[j][k] = 0.0;
			}
		}
		// 영상 출력 이미지에 값을 복사
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)paddedImage[i][j];
			}
		}
		// 메모리 해제
		OnFree2D(paddedImage, paddedH);
		OnFree2D(outputImage, m_inH);
		OnFree2D(maskGauss, size3);
		OnFree2D(inputGauss, m_inH);
		OnFree2D(maskLaplace, size3);
	}
	OnFree2D(grayImage, m_inH);
}


void CColorImage영상처리Doc::OnDogImage()
{
	CConstantDog btn;
	if (btn.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
		// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	unsigned char** grayImage = OnToGrayScale(m_inImageR, m_inImageG, m_inImageB, m_inH, m_inW);

	if (btn.m_radio_dog == 0) {  // DOG 마스크 사용
		// 마스크 초기화
		const int size = 7;
		double** mask = OnmallocDouble2D(size, size);
		// 마스크 초기화
		mask[0][0] = 0; mask[0][1] = 0; mask[0][2] = -1; mask[0][3] = -1; mask[0][4] = -1; mask[0][5] = 0; mask[0][6] = 0;
		mask[1][0] = 0; mask[1][1] = -2; mask[1][2] = -3; mask[1][3] = -3; mask[1][4] = -3; mask[1][5] = -2; mask[1][6] = 0;
		mask[2][0] = -1; mask[2][1] = -3; mask[2][2] = 5; mask[2][3] = 5; mask[2][4] = 5; mask[2][5] = -3; mask[2][6] = -1;
		mask[3][0] = -1; mask[3][1] = -3; mask[3][2] = 5; mask[3][3] = 16; mask[3][4] = 5; mask[3][5] = -3; mask[3][6] = -1;
		mask[4][0] = -1; mask[4][1] = -3; mask[4][2] = 5; mask[4][3] = 5; mask[4][4] = 5; mask[4][5] = -3; mask[4][6] = -1;
		mask[5][0] = 0; mask[5][1] = -2; mask[5][2] = -3; mask[5][3] = -3; mask[5][4] = -3; mask[5][5] = -2; mask[5][6] = 0;
		mask[6][0] = 0; mask[6][1] = 0; mask[6][2] = -1; mask[6][3] = -1; mask[6][4] = -1; mask[6][5] = 0; mask[6][6] = 0;

		double** tmpOutImage = OnConvolution(grayImage, m_inH, m_inW, mask, size);

		// 임시 출력 영상 -> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
				else if (tmpOutImage[i][j] > 255.0)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}
		OnFree2D(tmpOutImage, m_inH);
		OnFree2D(mask, size);
	}
	else {
		const int size3 = 3;
		// 시그마가 다른 3x3 가우시안 마스크 2개 생성(1보다 작은게 좋음)
		double** maskGauss1 = OnmallocDouble2D(size3, size3);
		double** maskGauss2 = OnmallocDouble2D(size3, size3);
		double sigma1 = 0.3;
		double sigma2 = 0.5;
		int center = size3 / 2;

		for (int i = 0; i < size3; i++) {
			for (int j = 0; j < size3; j++) {
				double x = sqrt((pow((i - center), 2) + pow((j - center), 2)));
				double gaussian = exp(-(x * x) / (2.0 * sigma1 * sigma1)) / (sigma1 * sqrt(2.0 * 3.141592));
				maskGauss1[i][j] = gaussian;
			}
		}
		for (int i = 0; i < size3; i++) {
			for (int j = 0; j < size3; j++) {
				double x = sqrt((pow((i - center), 2) + pow((j - center), 2)));
				double gaussian = exp(-(x * x) / (2.0 * sigma2 * sigma2)) / (sigma2 * sqrt(2.0 * 3.141592));
				maskGauss2[i][j] = gaussian;
			}
		}
		double** tmpOutImage1 = OnConvolution(grayImage, m_inH, m_inW, maskGauss1, size3);
		double** tmpOutImage2 = OnConvolution(grayImage, m_inH, m_inW, maskGauss2, size3);
		double** outputImage = OnmallocDouble2D(m_inH, m_inW);
		CConstantDig dlg2;

		if (dlg2.DoModal() != IDOK)
			return;
		int t = (int)dlg2.m_constant;
		// 두 컨볼루션 결과 빼기
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++){
				outputImage[i][j] = tmpOutImage1[i][j] - tmpOutImage2[i][j];
			}
		}
		// 이진화
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (outputImage[i][j] < t)  // 작은 값 넣어야 함
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 0;
				else
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
			}
		}
		OnFree2D(outputImage, m_inH);
		OnFree2D(tmpOutImage2, m_inH);
		OnFree2D(tmpOutImage1, m_inH);
		OnFree2D(maskGauss2, size3);
		OnFree2D(maskGauss1, size3);
	}
	OnFree2D(grayImage, m_inH);
}


void CColorImage영상처리Doc::OnEmbossHsi()
{
	CConstantConv btn;
	if (btn.DoModal() != IDOK)
		return;

	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int size;
	if (btn.m_radio_index == 0)
		size = 3;
	else if (btn.m_radio_index == 1)
		size = 5;
	else if (btn.m_radio_index == 2)
		size = 7;
	else if (btn.m_radio_index == 3)
		size = 9;

	double** mask = OnmallocDouble2D(size, size);
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

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageG = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageB = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpInImageH = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageS = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageI = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpOutImageR = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageG = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageB = OnmallocDouble2D(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + (size - 1); i++)
		for (int k = 0; k < m_inW + (size - 1); k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + (size / 2)][k + (size / 2)] = m_inImageR[i][k];
			tmpInImageG[i + (size / 2)][k + (size / 2)] = m_inImageG[i][k];
			tmpInImageB[i + (size / 2)][k + (size / 2)] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < size; m++)
				for (int n = 0; n < size; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + (size - 1));
	OnFree2D(tmpInImageG, m_inH + (size - 1));
	OnFree2D(tmpInImageB, m_inH + (size - 1));
	OnFree2D(tmpInImageH, m_inH + (size - 1));
	OnFree2D(tmpInImageS, m_inH + (size - 1));
	OnFree2D(tmpInImageI, m_inH + (size - 1));
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnPrewittHsi()
{
	CConstantEdge btn;
	if (btn.DoModal() != IDOK)
		return;
	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 3;
	double** mask = OnmallocDouble2D(size, size);
	if (btn.m_radio_edge == 0) {
		mask[0][0] = -1.; mask[0][1] = 0.; mask[0][2] = 1.;
		mask[1][0] = -1.; mask[1][1] = 0.; mask[1][2] = 1.;
		mask[2][0] = -1.; mask[2][1] = 0.; mask[2][2] = 1.;
	}
	else {
		mask[0][0] = -1.; mask[0][1] = -1.; mask[0][2] = -1.;
		mask[1][0] = 0.; mask[1][1] = 0.; mask[1][2] = 0.;
		mask[2][0] = 1.; mask[2][1] = 1.; mask[2][2] = 1.;
	}

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageG = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageB = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpInImageH = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageS = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageI = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpOutImageR = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageG = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageB = OnmallocDouble2D(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + (size - 1); i++)
		for (int k = 0; k < m_inW + (size - 1); k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + (size / 2)][k + (size / 2)] = m_inImageR[i][k];
			tmpInImageG[i + (size / 2)][k + (size / 2)] = m_inImageG[i][k];
			tmpInImageB[i + (size / 2)][k + (size / 2)] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < size; m++)
				for (int n = 0; n < size; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127.0;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + (size - 1));
	OnFree2D(tmpInImageG, m_inH + (size - 1));
	OnFree2D(tmpInImageB, m_inH + (size - 1));
	OnFree2D(tmpInImageH, m_inH + (size - 1));
	OnFree2D(tmpInImageS, m_inH + (size - 1));
	OnFree2D(tmpInImageI, m_inH + (size - 1));
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnSobelHsi()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantEdge btn;
	if (btn.DoModal() != IDOK)
		return;
	// 메모리 해제
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 3;
	double** mask = OnmallocDouble2D(size, size);
	if (btn.m_radio_edge == 0) {
		mask[0][0] = -1.; mask[0][1] = 0.; mask[0][2] = 1.;
		mask[1][0] = -2.; mask[1][1] = 0.; mask[1][2] = 2.;
		mask[2][0] = -1.; mask[2][1] = 0.; mask[2][2] = 1.;
	}
	else {
		mask[0][0] = -1.; mask[0][1] = -2.; mask[0][2] = -1.;
		mask[1][0] = 0.; mask[1][1] = 0.; mask[1][2] = 0.;
		mask[2][0] = 1.; mask[2][1] = 2.; mask[2][2] = 1.;
	}

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageG = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageB = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpInImageH = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageS = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageI = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpOutImageR = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageG = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageB = OnmallocDouble2D(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + (size - 1); i++)
		for (int k = 0; k < m_inW + (size - 1); k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + (size / 2)][k + (size / 2)] = m_inImageR[i][k];
			tmpInImageG[i + (size / 2)][k + (size / 2)] = m_inImageG[i][k];
			tmpInImageB[i + (size / 2)][k + (size / 2)] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < size; m++)
				for (int n = 0; n < size; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127.0;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + (size - 1));
	OnFree2D(tmpInImageG, m_inH + (size - 1));
	OnFree2D(tmpInImageB, m_inH + (size - 1));
	OnFree2D(tmpInImageH, m_inH + (size - 1));
	OnFree2D(tmpInImageS, m_inH + (size - 1));
	OnFree2D(tmpInImageI, m_inH + (size - 1));
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnLaplaceHsi()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 3;
	double** mask = OnmallocDouble2D(size, size);

	// 마스크 초기화
	mask[0][0] = 0.; mask[0][1] = 1.; mask[0][2] = 0.;
	mask[1][0] = 1.; mask[1][1] = -4.; mask[1][2] = 1.;
	mask[2][0] = 0.; mask[2][1] = 1.; mask[2][2] = 0.;

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageG = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageB = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpInImageH = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageS = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageI = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpOutImageR = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageG = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageB = OnmallocDouble2D(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + (size - 1); i++)
		for (int k = 0; k < m_inW + (size - 1); k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + (size / 2)][k + (size / 2)] = m_inImageR[i][k];
			tmpInImageG[i + (size / 2)][k + (size / 2)] = m_inImageG[i][k];
			tmpInImageB[i + (size / 2)][k + (size / 2)] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < size; m++)
				for (int n = 0; n < size; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127.0;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + (size - 1));
	OnFree2D(tmpInImageG, m_inH + (size - 1));
	OnFree2D(tmpInImageB, m_inH + (size - 1));
	OnFree2D(tmpInImageH, m_inH + (size - 1));
	OnFree2D(tmpInImageS, m_inH + (size - 1));
	OnFree2D(tmpInImageI, m_inH + (size - 1));
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnLogHsi()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 5;
	double** mask = OnmallocDouble2D(size, size);

	// 마스크 초기화
	mask[0][0] = 0.; mask[0][1] = 0.; mask[0][2] = -1.; mask[0][3] = 0.; mask[0][4] = 0.;
	mask[1][0] = 0.; mask[1][1] = -1.; mask[1][2] = -2.; mask[1][3] = -1.; mask[1][4] = 0.;
	mask[2][0] = -1.; mask[2][1] = -2.; mask[2][2] = 16.; mask[2][3] = -2.; mask[2][4] = -1.;
	mask[3][0] = 0.; mask[3][1] = -1.; mask[3][2] = -2.; mask[3][3] = -1.; mask[3][4] = 0.;
	mask[4][0] = 0.; mask[4][1] = 0.; mask[4][2] = -1.; mask[4][3] = 0.; mask[4][4] = 0.;

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageG = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageB = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpInImageH = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageS = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageI = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpOutImageR = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageG = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageB = OnmallocDouble2D(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + (size - 1); i++)
		for (int k = 0; k < m_inW + (size - 1); k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + (size / 2)][k + (size / 2)] = m_inImageR[i][k];
			tmpInImageG[i + (size / 2)][k + (size / 2)] = m_inImageG[i][k];
			tmpInImageB[i + (size / 2)][k + (size / 2)] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < size; m++)
				for (int n = 0; n < size; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127.0;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + (size - 1));
	OnFree2D(tmpInImageG, m_inH + (size - 1));
	OnFree2D(tmpInImageB, m_inH + (size - 1));
	OnFree2D(tmpInImageH, m_inH + (size - 1));
	OnFree2D(tmpInImageS, m_inH + (size - 1));
	OnFree2D(tmpInImageI, m_inH + (size - 1));
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CColorImage영상처리Doc::OnDogHsi()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutimage();
	// (중요!) 이미지의 폭과 높이를 결정
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	const int size = 7;
	double** mask = OnmallocDouble2D(size, size);

	// 마스크 초기화
	mask[0][0] = 0; mask[0][1] = 0; mask[0][2] = -1; mask[0][3] = -1; mask[0][4] = -1; mask[0][5] = 0; mask[0][6] = 0;
	mask[1][0] = 0; mask[1][1] = -2; mask[1][2] = -3; mask[1][3] = -3; mask[1][4] = -3; mask[1][5] = -2; mask[1][6] = 0;
	mask[2][0] = -1; mask[2][1] = -3; mask[2][2] = 5; mask[2][3] = 5; mask[2][4] = 5; mask[2][5] = -3; mask[2][6] = -1;
	mask[3][0] = -1; mask[3][1] = -3; mask[3][2] = 5; mask[3][3] = 16; mask[3][4] = 5; mask[3][5] = -3; mask[3][6] = -1;
	mask[4][0] = -1; mask[4][1] = -3; mask[4][2] = 5; mask[4][3] = 5; mask[4][4] = 5; mask[4][5] = -3; mask[4][6] = -1;
	mask[5][0] = 0; mask[5][1] = -2; mask[5][2] = -3; mask[5][3] = -3; mask[5][4] = -3; mask[5][5] = -2; mask[5][6] = 0;
	mask[6][0] = 0; mask[6][1] = 0; mask[6][2] = -1; mask[6][3] = -1; mask[6][4] = -1; mask[6][5] = 0; mask[6][6] = 0;

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageG = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageB = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpInImageH = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageS = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));
	tmpInImageI = OnmallocDouble2D(m_inH + (size - 1), m_inW + (size - 1));

	tmpOutImageR = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageG = OnmallocDouble2D(m_outH, m_outW);
	tmpOutImageB = OnmallocDouble2D(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + (size - 1); i++)
		for (int k = 0; k < m_inW + (size - 1); k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + (size / 2)][k + (size / 2)] = m_inImageR[i][k];
			tmpInImageG[i + (size / 2)][k + (size / 2)] = m_inImageG[i][k];
			tmpInImageB[i + (size / 2)][k + (size / 2)] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < size; m++)
				for (int n = 0; n < size; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127.0;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + (size - 1));
	OnFree2D(tmpInImageG, m_inH + (size - 1));
	OnFree2D(tmpInImageB, m_inH + (size - 1));
	OnFree2D(tmpInImageH, m_inH + (size - 1));
	OnFree2D(tmpInImageS, m_inH + (size - 1));
	OnFree2D(tmpInImageI, m_inH + (size - 1));
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


double** CColorImage영상처리Doc::OnToGrayscale(unsigned char** inImageR, unsigned char** inImageG, unsigned char** inImageB, int h, int w)
{  // 반환 타입 잘못 지정
	double** outImage = OnmallocDouble2D(h, w);
	for (int i = 0; i < h; i++) { 
		for (int j = 0; j < w; j++) { 
			outImage[i][j] = (m_inImageR[i][j] + m_inImageG[i][j] + m_inImageB[i][j]) / 3;
		} 
	} 
	return outImage;
}


unsigned char** CColorImage영상처리Doc::OnToGrayScale(unsigned char** inImageR, unsigned char** inImageG, unsigned char** inImageB, int h, int w)
{  // 에지 검출을 더욱 편리하게 하기 위한 흑백 전환 함수
	unsigned char** outImage = OnMalloc2D(h, w);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			outImage[i][j] = (unsigned char)((m_inImageR[i][j] + m_inImageG[i][j] + m_inImageB[i][j]) / 3);
		}
	}
	return outImage;
}
