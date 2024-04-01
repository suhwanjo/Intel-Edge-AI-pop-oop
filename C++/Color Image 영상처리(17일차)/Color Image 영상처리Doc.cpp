
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


void CColorImage영상처리Doc::OnFree2D(unsigned char** memory, int h)
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
			avg = (m_inImageR[i][k]+ m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageG[i][k] = m_outImageB[i][k] = m_outImageR[i][k] = (unsigned char)avg;
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
			m_outImageB[i][j] = pow(((double)m_inImageB[i][j] / 255.0), gam) * 255.0; // pow의 반환 타입은 double
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
	m_emphImageExecuted = true;

	int grayscale, distance = 0;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			distance = sqrt(pow(m_inImageR[i][j] - targetR, 2) + pow(m_inImageG[i][j] - targetG, 2) + pow(m_inImageB[i][j] - targetB, 2));

			if (distance <= tolerance) {
				m_outImageR[i][j] = m_inImageR[i][j];
				m_outImageG[i][j] = m_inImageG[i][j];
				m_outImageB[i][j] = m_inImageB[i][j];
			}
			else {
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

			// 채도(S) 흐리게
			S = S - 0.2;
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

			if (I - val >= 0.0) // val이 음수면
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

			if (I > val) {
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
			int I = static_cast<int>(hsi[2]);
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
	message.Format(_T("이미지의 중앙값은 %d 입니다."), median);
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

	if (btn.m_radio_para == 0) {
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i][j] = 255.0 * pow(((double)m_inImageR[i][j] / 127.0 - 1.0), 2.0); // CAP 파라볼라 : 밝은 곳이 입체적으로 보임
				m_outImageG[i][j] = 255.0 * pow(((double)m_inImageG[i][j] / 127.0 - 1.0), 2.0); // CAP 파라볼라 : 밝은 곳이 입체적으로 보임
				m_outImageB[i][j] = 255.0 * pow(((double)m_inImageB[i][j] / 127.0 - 1.0), 2.0); // CAP 파라볼라 : 밝은 곳이 입체적으로 보임
			}
		}
	}
	else if (btn.m_radio_para == 1) {
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i][j] = 255.0 - 255.0 * pow(((double)m_inImageR[i][j] / 127.0 - 1.0), 2.0); // CUP 파라볼라 : 어두운 곳이 입체적으로 보임
				m_outImageG[i][j] = 255.0 - 255.0 * pow(((double)m_inImageG[i][j] / 127.0 - 1.0), 2.0); // CUP 파라볼라 : 어두운 곳이 입체적으로 보임
				m_outImageB[i][j] = 255.0 - 255.0 * pow(((double)m_inImageB[i][j] / 127.0 - 1.0), 2.0); // CUP 파라볼라 : 어두운 곳이 입체적으로 보임
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
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			int oldValR = m_inImageR[i][j];
			int newValR = (int)((oldValR - lowR) / (double)(highR - lowR) * 255.0);
			m_outImageR[i][j] = newValR;

			int oldValG = m_inImageG[i][j];
			int newValG = (int)((oldValG - lowG) / (double)(highG - lowG) * 255.0);
			m_outImageG[i][j] = newValG;

			int oldValB = m_inImageB[i][j];
			int newValB = (int)((oldValB - lowB) / (double)(highB - lowB) * 255.0);
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
		HRESULT hr = image2.Load(filePath);
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
			y_orig = y / scale;
			x_orig = x / scale;

			y1 = (int)floor(y_orig);
			x1 = (int)floor(x_orig);
			y2 = (int)ceil(y_orig);
			x2 = (int)ceil(x_orig);

			y_diff = y_orig - y1;
			x_diff = x_orig - x1;

			val1R = m_inImageR[y1][x1];
			val2R = m_inImageR[y1][x2];
			val3R = m_inImageR[y2][x1];
			val4R = m_inImageR[y2][x2];

			val1G = m_inImageG[y1][x1];
			val2G = m_inImageG[y1][x2];
			val3G = m_inImageG[y2][x1];
			val4G = m_inImageG[y2][x2];

			val1B = m_inImageB[y1][x1];
			val2B = m_inImageB[y1][x2];
			val3B = m_inImageB[y2][x1];
			val4B = m_inImageB[y2][x2];

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
}


void CColorImage영상처리Doc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
}


void CColorImage영상처리Doc::OnMirrorImage()
{
	// TODO: 여기에 구현 코드 추가.
}
