
// Gray scale 영상처리 MFCView.cpp: CGrayscale영상처리MFCView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Gray scale 영상처리 MFC.h"
#endif

#include "Gray scale 영상처리 MFCDoc.h"
#include "Gray scale 영상처리 MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayscale영상처리MFCView

IMPLEMENT_DYNCREATE(CGrayscale영상처리MFCView, CView)

BEGIN_MESSAGE_MAP(CGrayscale영상처리MFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGrayscale영상처리MFCView::OnEqualImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CGrayscale영상처리MFCView::OnReverseImage)
	ON_COMMAND(IDM_POST_IMAGE, &CGrayscale영상처리MFCView::OnPostImage)
	ON_COMMAND(IDM_HISTO_STRETCH, &CGrayscale영상처리MFCView::OnHistoStretch)
	ON_COMMAND(IDM_HISTO_EQUAL, &CGrayscale영상처리MFCView::OnHistoEqual)
	ON_COMMAND(IDM_ADD_IMAGE, &CGrayscale영상처리MFCView::OnAddImage)
END_MESSAGE_MAP()

// CGrayscale영상처리MFCView 생성/소멸

CGrayscale영상처리MFCView::CGrayscale영상처리MFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayscale영상처리MFCView::~CGrayscale영상처리MFCView()
{
}

BOOL CGrayscale영상처리MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayscale영상처리MFCView 그리기

void CGrayscale영상처리MFCView::OnDraw(CDC* pDC)  // 자동 호출(화면을 갱신(무효화)할 때마다)
{
	CGrayscale영상처리MFCDoc* pDoc = GetDocument(); // doc 클래스에 접근
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	// 입력과 출력을 따로 보여줌
	unsigned char R, G, B;
	// 입력
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			R = G = B = pDoc->m_inImage[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
		}
	}
	// 출력
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			R = G = B = pDoc->m_outImage[i][k];
			pDC->SetPixel(k + 10 + pDoc->m_inW, i + 5, RGB(R, G, B));
		}
	}


}


// CGrayscale영상처리MFCView 인쇄

BOOL CGrayscale영상처리MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayscale영상처리MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayscale영상처리MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayscale영상처리MFCView 진단

#ifdef _DEBUG
void CGrayscale영상처리MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CGrayscale영상처리MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayscale영상처리MFCDoc* CGrayscale영상처리MFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayscale영상처리MFCDoc)));
	return (CGrayscale영상처리MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CGrayscale영상처리MFCView 메시지 처리기


void CGrayscale영상처리MFCView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayscale영상처리MFCDoc* pDoc = GetDocument(); // doc 클래스에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);  // OnDraw() 호출 효과
}


void CGrayscale영상처리MFCView::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayscale영상처리MFCDoc* pDoc = GetDocument(); // doc 클래스에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnReverseImage();
	Invalidate(TRUE);  // OnDraw() 호출 효과
}


void CGrayscale영상처리MFCView::OnPostImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayscale영상처리MFCDoc* pDoc = GetDocument(); // doc 클래스에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnPostImage();
	Invalidate(TRUE);  // OnDraw() 호출 효과
}


void CGrayscale영상처리MFCView::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayscale영상처리MFCDoc* pDoc = GetDocument(); // doc 클래스에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);  // OnDraw() 호출 효과
}


void CGrayscale영상처리MFCView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayscale영상처리MFCDoc* pDoc = GetDocument(); // doc 클래스에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);  // OnDraw() 호출 효과
}


void CGrayscale영상처리MFCView::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
