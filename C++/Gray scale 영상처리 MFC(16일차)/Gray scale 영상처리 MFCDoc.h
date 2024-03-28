
// Gray scale 영상처리 MFCDoc.h: CGrayscale영상처리MFCDoc 클래스의 인터페이스
//


#pragma once


class CGrayscale영상처리MFCDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGrayscale영상처리MFCDoc() noexcept;
	DECLARE_DYNCREATE(CGrayscale영상처리MFCDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGrayscale영상처리MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImage = NULL;
	// 출력 영상 2차원 배열
	unsigned char** m_outImage = NULL;
	// int보다 커질 수도 있음
	int m_inH;
	int m_outH;
	int m_inW;
	int m_outW;
	unsigned char** OnMalloc2D(int h, int w, int initVal);
	void Onfree2D(unsigned char** memory, int h);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnReverseImage();
	void OnPostImage();
	void OnHistoStretch();
	void OnHistoEqual();
	void OnAddImage();
	void OnSubImage();
	void OnBinaryImage();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnBinaryAvg();
	void OnBinaryMid();
	void OnParaCup();
	void OnParaCap();
	void OnGammaImage();
	void OnEmphImage();
	void OnMorphImage();
	void OnMoveImage();
	void OnRotatImage();
	void OnScaleImage();
	void OnScaleReduct();
	void OnScaleExpand();
	void OnMirrorImage();
	void OnEmbossImage();
	void OnBlurrImage();
	void OnSmothImage();
	void OnSharpImage();
	double** OnmallocDouble2D(int h, int w, int initVal);
	void OnfreeDouble2D(double** memory, int h);
	//double** ConvOperation(double** inputImage, int h, int w, double** mask, int maskSize);
	double** OnConvolution(unsigned char** inputImage, int h, int w, double** mask, int maskSize);
	void OnPrewittVer();
	void OnPrewittHo();
	void OnSobelVer();
	void OnSobelHo();
	void OnLaplace();
	void OnLog();
	void OnDog();
};
