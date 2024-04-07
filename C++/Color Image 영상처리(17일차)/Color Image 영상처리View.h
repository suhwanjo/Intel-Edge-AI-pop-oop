
// Color Image 영상처리View.h: CColorImage영상처리View 클래스의 인터페이스
//

#pragma once


class CColorImage영상처리View : public CView
{
protected: // serialization에서만 만들어집니다.
	CColorImage영상처리View() noexcept;
	DECLARE_DYNCREATE(CColorImage영상처리View)

// 특성입니다.
public:
	CColorImage영상처리Doc* GetDocument() const;

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
	virtual ~CColorImage영상처리View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGaryImage();
	afx_msg void OnReverseImage();
	afx_msg void OnPostImage();
	afx_msg void OnGammaImage();
	afx_msg void OnEmphImage();
	afx_msg void OnStaurChange();
	afx_msg void OnAddImage();
	afx_msg void OnSubImage();
	afx_msg void OnBinaryImage();
	afx_msg void OnBinaryMid();
	afx_msg void OnBinaryAvg();
	afx_msg void OnParaImage();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistoEqual();
	afx_msg void OnMorphImage();
	afx_msg void OnScaleUp();
	afx_msg void OnScaleDown();
	afx_msg void OnRotateImage();
	afx_msg void OnMoveImage();
	afx_msg void OnMirrorImage();
	afx_msg void OnEmbossImage();
	afx_msg void OnBlurrImage();
	afx_msg void OnSmoothImage();
	afx_msg void OnSharpImage();
	afx_msg void OnPrewittImage();
	afx_msg void OnSobelImage();
	afx_msg void OnLaplaceImage();
	afx_msg void OnLogImage();
	afx_msg void OnDogImage();
	afx_msg void OnEmbossHsi();
	afx_msg void OnPrewittHsi();
	afx_msg void OnSobelHsi();
	afx_msg void OnLaplaceHsi();
	afx_msg void OnLogHsi();
	afx_msg void OnDogHsi();
	afx_msg void OnCannyImage();
};

#ifndef _DEBUG  // Color Image 영상처리View.cpp의 디버그 버전
inline CColorImage영상처리Doc* CColorImage영상처리View::GetDocument() const
   { return reinterpret_cast<CColorImage영상처리Doc*>(m_pDocument); }
#endif

