
// GlimCircleDlg.h: 헤더 파일
//

#pragma once

//원과 관련된 매크로 지정
#define CIRCLE_POINT_COUNT 3
#define CIRCLE_FIRST_POINT 0
#define CIRCLE_SECOND_POINT 1
#define CIRCLE_THRIRD_POINT 2

//색과 관련된 값지정
#define COLOR_WHITE 0xff
#define COLOR_BLACK 0

// CGlimCircleDlg 대화 상자
class CGlimCircleDlg : public CDialogEx
{

private:
	CImage m_image;
	CPoint m_pointCollection[3];
	CPoint m_CircleCenterPoint;
	COLORREF m_defaultCircleColor; // 점 및 라인 그리는 색상
	COLORREF m_defaultInitColor;// 점 초기화 색상
	int m_clicklimit;
	int m_circleRadius;
	int m_pointRadius;
	int m_sizeThickness;
	bool m_bLButtonDown;
	bool m_isCircleMove[CIRCLE_POINT_COUNT];
	// 생성입니다.
public:
	CGlimCircleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMCIRCLE_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
private:
	void CalculateCircleCenter();
	void DrawPoint(unsigned char* fm, int x, int y, int nRadius, int nGray);
	void DrawCircle(unsigned char* fm, CPoint centerPoint, int radius, int nGray);
	void DrawBitmapBySetSize(unsigned char* fm, int x, int y, int size, int nGray);
	void threadDrawCircleForRandom();
	void threadDrawCircle(CPoint touchPoint, CPoint* circlePoint);
	void EraseCircle();
	void EraseWhite(unsigned char* fm, int nGray);
	void SetDrawArea();
	void ShowPointText(int index, CPoint point);
	void UpdateDisplay();
	bool isInPoint(int i, int j, int nCenterX, int nCenterY, int nRadius);
	bool IsCollinear(CPoint p1, CPoint p2, CPoint p3);


protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTst();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnBnClickedButtonPointsize();
	afx_msg void OnBnClickedButtonCirclethickness();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CEdit m_CEditPointSize;
	CEdit m_CEditCircleThickness;
	afx_msg void OnBnClickedButtonCircleRandomMove();
};
