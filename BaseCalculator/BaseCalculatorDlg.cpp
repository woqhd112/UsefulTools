
// BaseCalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BaseCalculator.h"
#include "BaseCalculatorDlg.h"
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



CBaseCalculatorDlg::CBaseCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASECALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CBaseCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BASE, m_btn_base);
	DDX_Control(pDX, IDC_BUTTON_CALCULATOR, m_btn_engineering);
	DDX_Control(pDX, IDC_STATIC_ENGINEERING, m_stt_engineering);
	DDX_Control(pDX, IDC_STATIC_BASE, m_stt_base);
	DDX_Control(pDX, IDC_BUTTON_CONVERTER, m_btn_converter);
	DDX_Control(pDX, IDC_STATIC_CONVERTER, m_stt_converter);
	DDX_Control(pDX, IDC_STATIC_DATE, m_stt_date);
	DDX_Control(pDX, IDC_BUTTON_DATE, m_btn_date);
	DDX_Control(pDX, IDC_STATIC_STOPWATCH, m_stt_stopwatch);
	DDX_Control(pDX, IDC_BUTTON_STOPWATCH, m_btn_stopwatch);
	DDX_Control(pDX, IDC_BUTTON_TIMER1, m_btn_timer);
	DDX_Control(pDX, IDC_STATIC_TIMER1, m_stt_timer);
}

BEGIN_MESSAGE_MAP(CBaseCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASE, &CBaseCalculatorDlg::OnBnClickedButtonBase)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATOR, &CBaseCalculatorDlg::OnBnClickedButtonCalculator)
	ON_BN_CLICKED(IDC_BUTTON_CONVERTER, &CBaseCalculatorDlg::OnBnClickedButtonConverter)
	ON_BN_CLICKED(IDC_BUTTON_TIME, &CBaseCalculatorDlg::OnBnClickedButtonTime)
	ON_BN_CLICKED(IDC_BUTTON_STOPWATCH, &CBaseCalculatorDlg::OnBnClickedButtonStopWatch)
	ON_BN_CLICKED(IDC_BUTTON_TIMER1, &CBaseCalculatorDlg::OnBnClickedButtonTimer1)
END_MESSAGE_MAP()


// CBaseCalculatorDlg 메시지 처리기

BOOL CBaseCalculatorDlg::OnInitDialog()
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


	this->SetBackgroundColor(RGB(255, 255, 255));
	m_btn_base.Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_FLAT);
	m_btn_base.InsertImage(IDB_PNG_BASE_NOMAL);
	m_btn_engineering.Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_FLAT);
	m_btn_engineering.InsertImage(IDB_PNG_ENGINEERING_NOMAL);
	m_btn_converter.Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_FLAT);
	m_btn_converter.InsertImage(IDB_PNG_CONVERTER_NOMAL);
	m_btn_date.Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_FLAT);
	m_btn_date.InsertImage(IDB_PNG_TIME_NOMAL);
	m_btn_stopwatch.Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_FLAT);
	m_btn_stopwatch.InsertImage(IDB_PNG_STOPWATCH_NOMAL);
	m_btn_timer.Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_FLAT);
	m_btn_timer.InsertImage(IDB_PNG_TIMER1_NOMAL);
	m_stt_engineering.Initialize(15, _T("고딕"));
	m_stt_base.Initialize(15, _T("고딕"));
	m_stt_converter.Initialize(15, _T("고딕"));
	m_stt_date.Initialize(15, _T("고딕"));
	m_stt_stopwatch.Initialize(15, _T("고딕"));
	m_stt_timer.Initialize(15, _T("고딕"));

	
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBaseCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBaseCalculatorDlg::OnPaint()
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
HCURSOR CBaseCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 진법계산 버튼 클릭
void CBaseCalculatorDlg::OnBnClickedButtonBase()
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

// 공학계산 버튼 클릭
void CBaseCalculatorDlg::OnBnClickedButtonCalculator()
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

// 단위변환 버튼 클릭
void CBaseCalculatorDlg::OnBnClickedButtonConverter()
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

// 시간계산 버튼 클릭
void CBaseCalculatorDlg::OnBnClickedButtonTime()
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

// 스탑워치 버튼 클릭
void CBaseCalculatorDlg::OnBnClickedButtonStopWatch()
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

// 타이머 버튼 클릭
void CBaseCalculatorDlg::OnBnClickedButtonTimer1()
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
void CBaseCalculatorDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}

BOOL CBaseCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_base)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_engineering)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_converter)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_date)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_stopwatch)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_timer)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

