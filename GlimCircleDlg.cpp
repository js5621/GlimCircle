
// GlimCircleDlg.cpp: 구현 파일
//
#include<cmath>
#include<math.h>
#include <iostream>
using namespace std;
#define _USE_MATH_DEFINES

#include "pch.h"
#include "framework.h"
#include "GlimCircle.h"
#include "GlimCircleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <thread>


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
	DDX_Control(pDX, IDC_Edit_PointSize, m_CEditPointSize);
	DDX_Control(pDX, IDC_EDIT_CircleThickness, m_CEditCircleThickness);
}

BEGIN_MESSAGE_MAP(CGlimCircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_Init, &CGlimCircleDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BUTTON_PointSize, &CGlimCircleDlg::OnBnClickedButtonPointsize)
	ON_BN_CLICKED(IDC_Button_CircleThickness, &CGlimCircleDlg::OnBnClickedButtonCirclethickness)
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
		SetDrawArea();
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CGlimCircleDlg::SetDrawArea()
{
	int nWidth = 500;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
	UpdateDisplay();
}

void CGlimCircleDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);

}


void CGlimCircleDlg::DrawPoint(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();


	for (int j = y; j < y + nRadius * 2; j++) {

		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInPoint(i, j, nCenterX, nCenterY, nRadius))
			{
				if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
				{
					int realPitch = abs(nPitch);
					int index = y* realPitch + x;

					if (nPitch > 0)
					{
						fm[index] = nGray;
					}
					else
					{
						fm[(nHeight - 1 - y) * realPitch + x] = nGray;
					}

				}
				fm[j * nPitch + i] = nGray;
			}		
		}
	}
}

bool CGlimCircleDlg::isInPoint(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

void CGlimCircleDlg::OnLButtonDown(UINT nFlags, CPoint point)// 다이얼로그 빈공간 찍을때 점 생성
{
	if (m_sizeThickness == 0 || m_pointRadius == 0)
	{
		return;
	}

	int nGray = 0;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = m_pointRadius;
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	m_bLButtonDown = true;

	m_clicklimit++;

	if (m_clicklimit <= 3)
	{
		m_pointCollection[m_clicklimit-1] = point;
		DrawPoint(fm, point.x, point.y, nRadius, nGray);

		if (m_clicklimit == 3)
		{
			CalculateCircleCenter();
		}
	}

	else
	{
		std::thread thread0(&CGlimCircleDlg::threadDrawCircle, this, point, 0);
		thread0.detach();  // 비동기 실행 (detach 또는 join 중 택1)
		std::thread thread1(&CGlimCircleDlg::threadDrawCircle, this, point, 1);
		thread1.detach();
		std::thread thread2(&CGlimCircleDlg::threadDrawCircle, this, point, 2);
		thread2.detach();
	}

	UpdateDisplay();
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CGlimCircleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLButtonDown = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}

std::chrono::steady_clock::time_point m_lastMouseMoveTime;


void CGlimCircleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLButtonDown)
	{
		if (m_clicklimit <= 3) // 원이 형성되기전에 점 드래그 방지 
		{
			return;
		}
		// 마우스를 왼쪽 버튼으로 누르고 있을 때만 실행되는 코드
		using namespace std::chrono;

		auto now = steady_clock::now();
		if (duration_cast<milliseconds>(now - m_lastMouseMoveTime).count() > 500)
		{
			m_lastMouseMoveTime = now;

			std::thread thread0(&CGlimCircleDlg::threadDrawCircle, this, point, 0);
			thread0.detach();
		}
		if (isInPoint(point.x, point.y, m_pointCollection[0].x, m_pointCollection[0].y,
			m_pointRadius))
		{
			//m_pointCollection[0].x = point.x;
			//m_pointCollection[0].x = point.y;
		}

		else if (isInPoint(point.x, point.y, m_pointCollection[1].x, m_pointCollection[1].y,
			m_pointRadius))
		{

		}
		
		else if (isInPoint(point.x, point.y, m_pointCollection[2].x, m_pointCollection[2].y,
			m_pointRadius))
		{

		}
		
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
void CGlimCircleDlg::threadDrawCircle(CPoint point,int index)
{
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 1; j++)
		{
			TRACE("원그리는중");
			//	int nGray = 0;
			//	int nWidth = m_image.GetWidth();
			//	int nHeight = m_image.GetHeight();
			//	int nPitch = m_image.GetPitch();
			//	int nRadius = m_pointRadius;
			//	unsigned char* fm = (unsigned char*)m_image.GetBits();
			//	DrawPoint(fm, m_pointCollection[].x+point.x, point.y, nRadius, 0xff);
			//	for (int k = 0; k < 3; k++)
			//	{
			//		
			//	}
			//	DrawCircle(fm, m_CircleCenterPoint, m_circleRadius, 0xff);


			//	for (int l = 0; l < 3; l++)
			//	{
			//		DrawPoint(fm, m_pointCollection[l].x, m_pointCollection[l].y, nRadius, 0);
			//	}

			//	CalculateCircleCenter();
			//	DrawCircle(fm, m_CircleCenterPoint, m_circleRadius, nGray);
			//	UpdateDisplay();
			///*}	*/		
		}
	}
}

void CGlimCircleDlg::CalculateCircleCenter()
{
	CPoint point1 = m_pointCollection[0];
	CPoint point2 = m_pointCollection[1];
	CPoint point3 = m_pointCollection[2];
	
	//외적을 통해 원을 그릴수 있는 거리인지 판단 
	if (IsCollinear(point1, point2, point3))
	{
		return;
	}

	double x1 = point1.x, y1 = point1.y;
	double x2 = point2.x, y2 = point2.y;
	double x3 = point3.x, y3 = point3.y;

	double d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));// 원의 중심(외심) 계산

	/*if (fabs(d) < 1e-10)
	{
		return;
	}*/

	double ux = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
	double uy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / d;
	
	m_circleRadius = (int)sqrt((ux - x1) * (ux - x1) + (uy - y1) * (uy - y1));

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nGray = 80;
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	m_CircleCenterPoint = CPoint(int(round(ux))+3, int(round(uy)+3));

	DrawCircle(fm,m_CircleCenterPoint, m_circleRadius,nGray);
}

void CGlimCircleDlg::DrawCircle(unsigned char* fm,CPoint centerPoint,int radius,int nGray)
{
	int nPitch = m_image.GetPitch();

	for (int degree = 0; degree < 360; ++degree)
	{
		double rad = degree * 3.14/ 180.0; // 각도를 라디안으로 변환
		int x = static_cast<int>(centerPoint.x + radius * cos(rad));
		int y = static_cast<int>(centerPoint.y + radius * sin(rad));

		DrawBitmapBySetSize(fm, x,y, m_sizeThickness, nGray);
	}
}

void CGlimCircleDlg::DrawBitmapBySetSize(unsigned char* fm, int x, int y, int size,int nGray)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	for (int dx = 0; dx < size; ++dx)
	{
		
		for (int dy = 0; dy < size; ++dy)
		{
			int realPitch = abs(nPitch);
			int dstX = x + dx;
			int dstY = y + dy;

			if (dstX >= 0 && dstX < nWidth && dstY >= 0 && dstY < nHeight)
			{
				int index = dstY * realPitch + dstX;

				if (nPitch > 0)
				{
					fm[index] = nGray;
				}
				else
				{
					fm[(nHeight - 1 - dstY) * realPitch + dstX] = nGray;
				}
					
			}
		}
	}
}

void CGlimCircleDlg::OnBnClickedBtnInit()
{
	EraseCircle();
}

void CGlimCircleDlg::EraseCircle()
{
	int nGray = 255;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = m_pointRadius;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	
	for (int i = 0; i < 3; i++)
	{
		DrawPoint(fm, m_pointCollection[i].x, m_pointCollection[i].y, nRadius, nGray);
	}
	
	DrawCircle(fm, m_CircleCenterPoint, m_circleRadius, nGray);

	//다시 그릴 수 있게 초기화 
	m_clicklimit = 0;

	for (int i = 0; i < 3; i++)
	{
		m_pointCollection[i] = CPoint(0, 0);
	}

	m_CircleCenterPoint = CPoint(0, 0);

	m_sizeThickness = 0;
	m_pointRadius = 0;
	GetDlgItem(IDC_BUTTON_PointSize)->EnableWindow(true);
	GetDlgItem(IDC_Button_CircleThickness)->EnableWindow(true);

	UpdateDisplay();
}

void CGlimCircleDlg::OnBnClickedButtonPointsize()// 버튼 크기 조절 
{
	CString pointSizeStr;
	GetDlgItemText(IDC_Edit_PointSize, pointSizeStr);
	
	if (pointSizeStr != _T(""))
	{
		m_pointRadius = _ttoi(pointSizeStr);
		SetDlgItemText(IDC_Edit_PointSize, _T(""));
		GetDlgItem(IDC_BUTTON_PointSize)->EnableWindow(false);
	}
	
}

void CGlimCircleDlg::OnBnClickedButtonCirclethickness()// 점 크기 조절 
{
	CString thickSizeStr;
	GetDlgItemText(IDC_EDIT_CircleThickness, thickSizeStr);

	if (thickSizeStr != _T(""))
	{
		m_sizeThickness = _ttoi(thickSizeStr);
		SetDlgItemText(IDC_EDIT_CircleThickness, _T(""));
		GetDlgItem(IDC_Button_CircleThickness)->EnableWindow(false);
	}
}

bool CGlimCircleDlg::IsCollinear(CPoint p1, CPoint p2, CPoint p3)
{
	// 세 점이 한 직선 위에 있는지 확인 (외적 이용)
	int cross = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	return abs(cross) < 5; // 허용오차 5픽셀
}
