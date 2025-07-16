
// GlimCircleDlg.h: 헤더 파일
//

#pragma once


// CGlimCircleDlg 대화 상자
class CGlimCircleDlg : public CDialogEx
{

private:
	CImage m_image;
	CPoint m_pointCollection[3];
	CPoint m_CircleCenterPoint;
	int m_clicklimit;
	
	
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
	void DrawPoint(CDC* pDC, CImage& img, CPoint center, int radius);
};
