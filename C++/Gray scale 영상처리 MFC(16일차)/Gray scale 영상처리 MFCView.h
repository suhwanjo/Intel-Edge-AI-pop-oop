
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
	afx_msg void OnSubImage();
	afx_msg void OnBinaryImage();
	afx_msg void OnBinaryMid();
	afx_msg void OnBinaryAvg();
	afx_msg void OnParaCap();
	afx_msg void OnParaCup();
	afx_msg void OnGammaImage();
	afx_msg void OnEmphImage();
	afx_msg void OnMorphImage();
	afx_msg void OnScaleImage();
	afx_msg void OnRotatImage();
	afx_msg void OnMoveImage();
	afx_msg void OnScaleExpand();
	afx_msg void OnScaleReduct();
	afx_msg void OnMirrorImage();
	afx_msg void OnEmbossImage();
	afx_msg void OnBlurrImage();
	afx_msg void OnSmothImage();
	afx_msg void OnSharpImage();
	afx_msg void OnPrewittHo();
	afx_msg void OnPrewittVer();
	afx_msg void OnSobelHo();
	afx_msg void OnSobelVer();
	afx_msg void OnLaplace();
	afx_msg void OnLog();
	afx_msg void OnDog();
};

#ifndef _DEBUG  // Gray scale 영상처리 MFCView.cpp의 디버그 버전
inline CGrayscale영상처리MFCDoc* CGrayscale영상처리MFCView::GetDocument() const
   { return reinterpret_cast<CGrayscale영상처리MFCDoc*>(m_pDocument); }
#endif

