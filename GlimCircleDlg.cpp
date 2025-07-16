
// GlimCircleDlg.cpp: 구현 파일
//
#include<cmath>
#include<math.h>

#include "pch.h"
#include "framework.h"
#include "GlimCircle.h"
#include "GlimCircleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CGlimCircleDlg 대화 상자



CGlimCircleDlg::CGlimCircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMCIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGlimCircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TST, &CGlimCircleDlg::OnBnClickedBtnTst)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CGlimCircleDlg 메시지 처리기

BOOL CGlimCircleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimCircleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimCircleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGlimCircleDlg::OnBnClickedBtnTst()
{
	/*int nWidth= 20;
	int nHeight = 20;
	int nBpp = 8;

	m_image.Create(nWidth, nHeight, nBpp);
	int nRadius = min(nWidth / 2, nHeight / 2);
	
	CPoint ncPoint = CPoint(300, 300);
	CDC* dc = GetDC();

	DrawCircle(dc, m_image, ncPoint, nRadius);
	*/
}

void CGlimCircleDlg::DrawPoint(CDC* pDC, CImage& img, CPoint origin, int radius)
{
	int width = img.GetWidth();
	int height = img.GetHeight();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int dx = x - width / 2;
			int dy = y - height / 2;
			if (dx * dx + dy * dy <= (radius * radius))
			{
				COLORREF color = m_image.GetPixel(x, y);
				pDC->SetPixelV(x + origin.x, y + origin.y, color);
			}

		}

	}
}

void CGlimCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)// 다이얼로그 빈공간 찍을때 점 생성
{
	int nWidth = 20;
	int nHeight = 20;
	int nBpp = 32;
	int nRadius = min(nWidth / 2, nHeight / 2);

	if (m_image.IsNull() == FALSE) // 점을 다시 찍을때 익셉션 발생하지 않도록 방지 
		m_image.Destroy();

	m_image.Create(nWidth, nHeight, nBpp);

	m_clicklimit++;

	CDC* dc = GetDC();

	if (m_clicklimit <= 3)
	{
		
		m_pointCollection[m_clicklimit-1] = point;
		DrawPoint(dc, m_image, point, nRadius);

		if (m_clicklimit == 3)
		{
			CalculateCircleCenter();
		}
	}

	ReleaseDC(dc);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CGlimCircleDlg::CalculateCircleCenter()
{
	CPoint point1 = m_pointCollection[0];
	CPoint point2 = m_pointCollection[1];
	CPoint point3 = m_pointCollection[2];
	
	double x1 = point1.x, y1 = point1.y;
	double x2 = point2.x, y2 = point2.y;
	double x3 = point3.x, y3 = point3.y;

	double d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));// 원의 중심(외심) 계산

	/*if (abs(d) < 1e-10)
	{
		AfxMessageBox(_T("원을 계산할 수 없습니다.", "오류"));

		return;
	}*/

	double ux = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
	double uy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / d;
	
	m_CircleCenterPoint = CPoint(int(round(ux)), int(round(uy)));	

	int nWidth = 20;
	int nHeight = 20;
	int nBpp = 32;
	int nRadius = min(nWidth / 2, nHeight / 2);

	if (m_image.IsNull() == FALSE) // 점을 다시 찍을때 익셉션 발생하지 않도록 방지 
		m_image.Destroy();

	m_image.Create(nWidth, nHeight, nBpp);

	CDC* dc = GetDC();

	DrawPoint(dc, m_image, m_CircleCenterPoint, nRadius);

}
