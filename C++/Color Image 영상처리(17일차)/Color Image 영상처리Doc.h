
// Color Image 영상처리Doc.h: CColorImage영상처리Doc 클래스의 인터페이스
//


#pragma once


class CColorImage영상처리Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImage영상처리Doc() noexcept;
	DECLARE_DYNCREATE(CColorImage영상처리Doc)

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
	virtual ~CColorImage영상처리Doc();
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
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;
	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	unsigned char** OnMalloc2D(int h, int w);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void OnFree2D(unsigned char** memory, int h);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnFreeOutimage();
	void OnGaryImage();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnReverseImage();
	void OnPostImage();
	void OnGammaImage();
	void OnEmphImage();
	void OnStaurChange();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	COLORREF m_selectedColor;
	bool m_emphImageExecuted = false;
	void OnAddImage();
	void OnSubImage();
	void OnBinaryImage();
	void OnBinaryMid();
	void OnBinaryAvg();
	void OnParaImage();
	void OnHistoStretch();
	void OnHistoEqual();
	void OnMorphImage();
	void OnScaleUp();
	void OnScaleDown();
	void OnRotateImage();
	void OnMoveImage();
	void OnMirrorImage();
	double** OnmallocDouble2D(int h, int w);
	void OnfreeDouble2D(double** memory, int h);
	double** OnConvolution(unsigned char** inputImage, int h, int w, double** mask, int maskSize);
	void OnEmbossImage();
	void OnBlurrImage();
	void OnSmoothImage();
	void OnSharpImage();
	void OnPrewittImage();
	void OnSobelImage();
	void OnLaplaceImage();
	void OnLogImage();
	void OnDogImage();
};
