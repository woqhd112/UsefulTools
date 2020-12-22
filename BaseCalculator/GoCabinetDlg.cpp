
// BaseCalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GoCabinet.h"
#include "GoCabinetDlg.h"
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
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBaseCalculatorDlg 대화 상자



CGoCabinetDlg::CGoCabinetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASECALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CGoCabinetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ENGINEERING, m_stt_engineering);
	DDX_Control(pDX, IDC_STATIC_BASE, m_stt_base);
	DDX_Control(pDX, IDC_STATIC_CONVERTER, m_stt_converter);
	DDX_Control(pDX, IDC_STATIC_DATE, m_stt_date);
	DDX_Control(pDX, IDC_STATIC_STOPWATCH, m_stt_stopwatch);
	DDX_Control(pDX, IDC_STATIC_TIMER1, m_stt_timer);
	DDX_Control(pDX, IDC_BUTTON_BASE_GDI, m_btn_base_gdi);
	DDX_Control(pDX, IDC_BUTTON_CALCULATOR_GDI, m_btn_calculator_gdi);
	DDX_Control(pDX, IDC_BUTTON_STOPWATCH_GDI, m_btn_stopwatch_gdi);
	DDX_Control(pDX, IDC_BUTTON_CONVERTER_GDI, m_btn_converter_gdi);
	DDX_Control(pDX, IDC_BUTTON_DATE_GDI, m_btn_date_gdi);
	DDX_Control(pDX, IDC_BUTTON_TIMER_GDI, m_btn_timer_gdi);
}

BEGIN_MESSAGE_MAP(CGoCabinetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASE_GDI, &CGoCabinetDlg::OnBnClickedButtonBaseGdi)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATOR_GDI, &CGoCabinetDlg::OnBnClickedButtonCalculatorGdi)
	ON_BN_CLICKED(IDC_BUTTON_STOPWATCH_GDI, &CGoCabinetDlg::OnBnClickedButtonStopwatchGdi)
	ON_BN_CLICKED(IDC_BUTTON_CONVERTER_GDI, &CGoCabinetDlg::OnBnClickedButtonConverterGdi)
	ON_BN_CLICKED(IDC_BUTTON_DATE_GDI, &CGoCabinetDlg::OnBnClickedButtonDateGdi)
	ON_BN_CLICKED(IDC_BUTTON_TIMER_GDI, &CGoCabinetDlg::OnBnClickedButtonTimerGdi)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CBaseCalculatorDlg 메시지 처리기

BOOL CGoCabinetDlg::OnInitDialog()
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
	bBase = false;
	bEngineering = false;
	bConverter = false;
	bDate = false;
	bStopWatch = false;
	bTimer = false;

	m_returnBrush.CreateSolidBrush(RGB(35, 35, 35));
	
	m_stt_engineering.Initialize(15, _T("고딕"));
	m_stt_base.Initialize(15, _T("고딕"));
	m_stt_converter.Initialize(15, _T("고딕"));
	m_stt_date.Initialize(15, _T("고딕"));
	m_stt_stopwatch.Initialize(15, _T("고딕"));
	m_stt_timer.Initialize(15, _T("고딕"));

	m_btn_base_gdi.LoadStdImage(IDB_PNG_BASE_NOMAL, _T("PNG"));
	m_btn_base_gdi.LoadHovImage(IDB_PNG_BASE_HOVER, _T("PNG"));
	m_btn_base_gdi.LoadAltImage(IDB_PNG_BASE_CLICK, _T("PNG"));

	m_btn_calculator_gdi.LoadStdImage(IDB_PNG_ENGINEERING_NOMAL, _T("PNG"));
	m_btn_calculator_gdi.LoadHovImage(IDB_PNG_ENGINEERING_HOVER, _T("PNG"));
	m_btn_calculator_gdi.LoadAltImage(IDB_PNG_ENGINEERING_CLICK, _T("PNG"));

	m_btn_stopwatch_gdi.LoadStdImage(IDB_PNG_STOPWATCH_NOMAL, _T("PNG"));
	m_btn_stopwatch_gdi.LoadHovImage(IDB_PNG_STOPWATCH_HOVER, _T("PNG"));
	m_btn_stopwatch_gdi.LoadAltImage(IDB_PNG_STOPWATCH_CLICK, _T("PNG"));

	
	m_btn_converter_gdi.LoadStdImage(IDB_PNG_CONVERTER_NOMAL, _T("PNG"));
	m_btn_converter_gdi.LoadHovImage(IDB_PNG_CONVERTER_HOVER, _T("PNG"));
	m_btn_converter_gdi.LoadAltImage(IDB_PNG_CONVERTER_CLICK, _T("PNG"));

	m_btn_date_gdi.LoadStdImage(IDB_PNG_DATECAL_NOMAL, _T("PNG"));
	m_btn_date_gdi.LoadHovImage(IDB_PNG_DATECAL_HOVER, _T("PNG"));
	m_btn_date_gdi.LoadAltImage(IDB_PNG_DATECAL_CLICK, _T("PNG"));

	m_btn_timer_gdi.LoadStdImage(IDB_PNG_TIMER_NOMAL, _T("PNG"));
	m_btn_timer_gdi.LoadHovImage(IDB_PNG_TIMER_HOVER, _T("PNG"));
	m_btn_timer_gdi.LoadAltImage(IDB_PNG_TIMER_CLICK, _T("PNG"));

	this->SetBackgroundColor(RGB(55, 55, 55));

	m_btn_base_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_base.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_calculator_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_engineering.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_stopwatch_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_stopwatch.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_converter_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_converter.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_date_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_date.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_timer_gdi.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_timer.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_base_gdi.BringWindowToTop();
	m_btn_calculator_gdi.BringWindowToTop();
	m_btn_stopwatch_gdi.BringWindowToTop();
	m_btn_converter_gdi.BringWindowToTop();
	m_btn_date_gdi.BringWindowToTop();
	m_btn_timer_gdi.BringWindowToTop();
	m_stt_base.BringWindowToTop();
	m_stt_engineering.BringWindowToTop();
	m_stt_stopwatch.BringWindowToTop();
	m_stt_converter.BringWindowToTop();
	m_stt_date.BringWindowToTop();
	m_stt_timer.BringWindowToTop();

	SetCtlPos();
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGoCabinetDlg::SetCtlPos()
{
	CRect rect;
	m_stt_base.GetWindowRect(rect);

	const int PICTURE_WIDTH = 128;
	const int PICTURE_HEIGHT = 128;
	const int LEFT_MARGIN = 30;
	const int TOP_MARGIN = 30;
	const int PICTURE_TO_PICTURE_MARGIN_WIDTH = 20;
	const int PICTURE_TO_PICTURE_MARGIN_HEIGHT = 30;

	m_btn_base_gdi.MoveWindow(LEFT_MARGIN, TOP_MARGIN, PICTURE_WIDTH, PICTURE_HEIGHT);
	m_btn_calculator_gdi.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN, PICTURE_WIDTH, PICTURE_HEIGHT);
	m_btn_stopwatch_gdi.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN, PICTURE_WIDTH, PICTURE_HEIGHT);
	m_btn_converter_gdi.MoveWindow(LEFT_MARGIN, TOP_MARGIN + PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT, PICTURE_WIDTH, PICTURE_HEIGHT);
	m_btn_date_gdi.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN + PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT, PICTURE_WIDTH, PICTURE_HEIGHT);
	m_btn_timer_gdi.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN + PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT, PICTURE_WIDTH, PICTURE_HEIGHT);

	m_stt_base.MoveWindow(LEFT_MARGIN, TOP_MARGIN + PICTURE_HEIGHT, PICTURE_WIDTH, rect.Height());
	m_stt_engineering.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN + PICTURE_HEIGHT, PICTURE_WIDTH, rect.Height());
	m_stt_stopwatch.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN + PICTURE_HEIGHT, PICTURE_WIDTH, rect.Height());
	m_stt_converter.MoveWindow(LEFT_MARGIN, TOP_MARGIN + PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT + PICTURE_HEIGHT, PICTURE_WIDTH, rect.Height());
	m_stt_date.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN + PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT + PICTURE_HEIGHT, PICTURE_WIDTH, rect.Height());
	m_stt_timer.MoveWindow(LEFT_MARGIN + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH + PICTURE_WIDTH + PICTURE_TO_PICTURE_MARGIN_WIDTH, TOP_MARGIN + PICTURE_HEIGHT + PICTURE_TO_PICTURE_MARGIN_HEIGHT + PICTURE_HEIGHT, PICTURE_WIDTH, rect.Height());
}

void CGoCabinetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGoCabinetDlg::OnPaint()
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
HCURSOR CGoCabinetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGoCabinetDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}

BOOL CGoCabinetDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	

	return CDialogEx::PreTranslateMessage(pMsg);
}



void CGoCabinetDlg::OnBnClickedButtonBaseGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bBase)
	{
		base = new BaseCalculate(this);
		base->Create(IDD_DIALOG_BASE, GetDesktopWindow());
		base->ShowWindow(SW_SHOW);
		bBase = true;
	}
}


void CGoCabinetDlg::OnBnClickedButtonCalculatorGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bEngineering)
	{
		engineering = new EngineeringCalculate(this);
		engineering->Create(IDD_DIALOG_ENGINEERING, GetDesktopWindow());
		engineering->ShowWindow(SW_SHOW);
		bEngineering = true;
	}
}


void CGoCabinetDlg::OnBnClickedButtonStopwatchGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bStopWatch)
	{
		stopwatch = new StopWatch(this);
		stopwatch->Create(IDD_DIALOG_STOPWATCH, GetDesktopWindow());
		stopwatch->ShowWindow(SW_SHOW);
		bStopWatch = true;
	}

}


void CGoCabinetDlg::OnBnClickedButtonConverterGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bConverter)
	{
		converter = new UnitConverter(this);
		converter->Create(IDD_DIALOG_CONVERTER, GetDesktopWindow());
		converter->ShowWindow(SW_SHOW);
		bConverter = true;
	}
}


void CGoCabinetDlg::OnBnClickedButtonDateGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bDate)
	{
		date = new DateCalculate(this);
		date->Create(IDD_DIALOG_DATE, GetDesktopWindow());
		date->ShowWindow(SW_SHOW);
		bDate = true;
	}
}


void CGoCabinetDlg::OnBnClickedButtonTimerGdi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bTimer)
	{
		timer = new Timer(this);
		timer->Create(IDD_DIALOG_TIMER, GetDesktopWindow());
		timer->ShowWindow(SW_SHOW);
		bTimer = true;
	}
}


HBRUSH CGoCabinetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			//pDC->SetBkColor(RGB(35, 35, 35));
			//hbr = (HBRUSH)m_returnBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ENGINEERING)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			//pDC->SetBkColor(RGB(35, 35, 35));
			//hbr = (HBRUSH)m_returnBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_STOPWATCH)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			//pDC->SetBkColor(RGB(35, 35, 35));
			//hbr = (HBRUSH)m_returnBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_CONVERTER)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			//pDC->SetBkColor(RGB(35, 35, 35));
			//hbr = (HBRUSH)m_returnBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_DATE)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			//pDC->SetBkColor(RGB(35, 35, 35));
			//hbr = (HBRUSH)m_returnBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIMER1)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			//pDC->SetBkColor(RGB(35, 35, 35));
			//hbr = (HBRUSH)m_returnBrush;
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
