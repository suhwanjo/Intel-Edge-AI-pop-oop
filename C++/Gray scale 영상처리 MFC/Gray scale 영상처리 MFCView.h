
// Gray scale 영상처리 MFCView.h: CGrayscale영상처리MFCView 클래스의 인터페이스
//

#pragma once


class CGrayscale영상처리MFCView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGrayscale영상처리MFCView() noexcept;
	DECLARE_DYNCREATE(CGrayscale영상처리MFCView)

// 특성입니다.
public:
	CGrayscale영상처리MFCDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGrayscale영상처리MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnReverseImage();
	afx_msg void OnPostImage();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistoEqual();
	afx_msg void OnAddImage();
};

#ifndef _DEBUG  // Gray scale 영상처리 MFCView.cpp의 디버그 버전
inline CGrayscale영상처리MFCDoc* CGrayscale영상처리MFCView::GetDocument() const
   { return reinterpret_cast<CGrayscale영상처리MFCDoc*>(m_pDocument); }
#endif

