
// Color Image 영상처리View.cpp: CColorImage영상처리View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Color Image 영상처리.h"
#endif

#include "Color Image 영상처리Doc.h"
#include "Color Image 영상처리View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorImage영상처리View

IMPLEMENT_DYNCREATE(CColorImage영상처리View, CView)

BEGIN_MESSAGE_MAP(CColorImage영상처리View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CColorImage영상처리View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_EQUAL_IMAGE, &CColorImage영상처리View::OnEqualImage)
	ON_COMMAND(IDM_GARY_IMAGE, &CColorImage영상처리View::OnGaryImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CColorImage영상처리View::OnReverseImage)
	ON_COMMAND(IDM_POST_IMAGE, &CColorImage영상처리View::OnPostImage)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CColorImage영상처리View::OnGammaImage)
	ON_COMMAND(IDM_EMPH_IMAGE, &CColorImage영상처리View::OnEmphImage)
	ON_COMMAND(IDM_STAUR_CHANGE, &CColorImage영상처리View::OnStaurChange)
	ON_COMMAND(IDM_ADD_IMAGE, &CColorImage영상처리View::OnAddImage)
	ON_COMMAND(IDM_SUB_IMAGE, &CColorImage영상처리View::OnSubImage)
	ON_COMMAND(IDM_BINARY_IMAGE, &CColorImage영상처리View::OnBinaryImage)
	ON_COMMAND(IDM_BINARY_MID, &CColorImage영상처리View::OnBinaryMid)
	ON_COMMAND(IDM_BINARY_AVG, &CColorImage영상처리View::OnBinaryAvg)
	ON_COMMAND(IDM_PARA_IMAGE, &CColorImage영상처리View::OnParaImage)
	ON_COMMAND(IDM_HISTO_STRETCH, &CColorImage영상처리View::OnHistoStretch)
	ON_COMMAND(IDM_HISTO_EQUAL, &CColorImage영상처리View::OnHistoEqual)
	ON_COMMAND(IDM_MORPH_IMAGE, &CColorImage영상처리View::OnMorphImage)
	ON_COMMAND(IDM_SCALE_UP, &CColorImage영상처리View::OnScaleUp)
	ON_COMMAND(IDM_SCALE_DOWN, &CColorImage영상처리View::OnScaleDown)
	ON_COMMAND(IDM_ROTATE_IMAGE, &CColorImage영상처리View::OnRotateImage)
	ON_COMMAND(IDM_MOVE_IMAGE, &CColorImage영상처리View::OnMoveImage)
	ON_COMMAND(IDM_MIRROR_IMAGE, &CColorImage영상처리View::OnMirrorImage)
	ON_COMMAND(IDM_EMBOSS_IMAGE, &CColorImage영상처리View::OnEmbossImage)
	ON_COMMAND(IDM_BLURR_IMAGE, &CColorImage영상처리View::OnBlurrImage)
	ON_COMMAND(IDM_SMOOTH_IMAGE, &CColorImage영상처리View::OnSmoothImage)
	ON_COMMAND(IDM_SHARP_IMAGE, &CColorImage영상처리View::OnSharpImage)
	ON_COMMAND(IDM_PREWITT_IMAGE, &CColorImage영상처리View::OnPrewittImage)
	ON_COMMAND(IDM_SOBEL_IMAGE, &CColorImage영상처리View::OnSobelImage)
	ON_COMMAND(IDM_LAPLACE_IMAGE, &CColorImage영상처리View::OnLaplaceImage)
	ON_COMMAND(IDM_LOG_IMAGE, &CColorImage영상처리View::OnLogImage)
	ON_COMMAND(IDM_DOG_IMAGE, &CColorImage영상처리View::OnDogImage)
END_MESSAGE_MAP()

// CColorImage영상처리View 생성/소멸

CColorImage영상처리View::CColorImage영상처리View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CColorImage영상처리View::~CColorImage영상처리View()
{
}

BOOL CColorImage영상처리View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CColorImage영상처리View 그리기

void CColorImage영상처리View::OnDraw(CDC* pDC)
{
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int R, G, B;
	// 입력
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			R = pDoc->m_inImageR[i][k];
			G = pDoc->m_inImageG[i][k];
			B = pDoc->m_inImageB[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
		}
	}
	// 출력
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			R = pDoc->m_outImageR[i][k];
			G = pDoc->m_outImageG[i][k];
			B = pDoc->m_outImageB[i][k];
			pDC->SetPixel(k + 10 + pDoc->m_inW, i + 5, RGB(R, G, B));
		}
	}

	if (pDoc->m_emphImageExecuted)
	{
		pDC->FillSolidRect((pDoc->m_inW * 2) + 30, 5, 100, 100, pDoc->m_selectedColor);
	}
}


// CColorImage영상처리View 인쇄


void CColorImage영상처리View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CColorImage영상처리View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CColorImage영상처리View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CColorImage영상처리View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CColorImage영상처리View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CColorImage영상처리View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CColorImage영상처리View 진단

#ifdef _DEBUG
void CColorImage영상처리View::AssertValid() const
{
	CView::AssertValid();
}

void CColorImage영상처리View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorImage영상처리Doc* CColorImage영상처리View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorImage영상처리Doc)));
	return (CColorImage영상처리Doc*)m_pDocument;
}
#endif //_DEBUG


// CColorImage영상처리View 메시지 처리기


void CColorImage영상처리View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnGaryImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaryImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnReverseImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnPostImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPostImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnEmphImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmphImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnStaurChange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStaurChange();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnSubImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSubImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnBinaryImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinaryImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnBinaryMid()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinaryMid();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnBinaryAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinaryAvg();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnParaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParaImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnMorphImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMorphImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnScaleUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnScaleUp();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnScaleDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnScaleDown();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnRotateImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotateImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMoveImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnMirrorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnEmbossImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnBlurrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurrImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnSmoothImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSmoothImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnSharpImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnPrewittImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPrewittImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnSobelImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSobelImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnLaplaceImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplaceImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnLogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLogImage();
	Invalidate(TRUE);
}


void CColorImage영상처리View::OnDogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImage영상처리Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDogImage();
	Invalidate(TRUE);
}
