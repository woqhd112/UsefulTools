// Timer.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "BaseCalculatorDlg.h"
#include "Timer.h"
#include "afxdialogex.h"


// Timer 대화 상자

IMPLEMENT_DYNAMIC(Timer, CDialogEx)

Timer::Timer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TIMER, pParent)
{
	this->pParent = pParent;
	bStart = true;
	bWorkEnd = false;
	bRestEnd = false;
}

Timer::~Timer()
{
	if (bThread)
	{
		bThread = false;
		TerminateThread(m_thread, 0);
		m_thread = nullptr;
		Sleep(50);
	}
}

void Timer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WORK_HOUR1, m_edit_work_hour_1);
	DDX_Control(pDX, IDC_EDIT_WORK_HOUR2, m_edit_work_hour_2);
	DDX_Control(pDX, IDC_EDIT_WORK_MINUTE1, m_edit_work_minute_1);
	DDX_Control(pDX, IDC_EDIT_WORK_MINUTE2, m_edit_work_minute_2);
	DDX_Control(pDX, IDC_EDIT_WORK_SECOND1, m_edit_work_second_1);
	DDX_Control(pDX, IDC_EDIT_WORK_SECOND2, m_edit_work_second_2);
	DDX_Control(pDX, IDC_EDIT_REST_HOUR1, m_edit_rest_hour_1);
	DDX_Control(pDX, IDC_EDIT_REST_HOUR2, m_edit_rest_hour_2);
	DDX_Control(pDX, IDC_EDIT_REST_MINUTE1, m_edit_rest_minute_1);
	DDX_Control(pDX, IDC_EDIT_REST_MINUTE2, m_edit_rest_minute_2);
	DDX_Control(pDX, IDC_EDIT_REST_SECOND1, m_edit_rest_second_1);
	DDX_Control(pDX, IDC_EDIT_REST_SECOND2, m_edit_rest_second_2);
	DDX_Control(pDX, IDC_BUTTON_STARTANDSTOP2, m_btn_startandstop);
	DDX_Control(pDX, IDC_BUTTON_RESET2, m_btn_reset);
	DDX_Control(pDX, IDC_BUTTON_WORK_HOUR_UP, m_btn_work_hour_up);
	DDX_Control(pDX, IDC_BUTTON_WORK_HOUR_DOWN, m_btn_work_hour_down);
	DDX_Control(pDX, IDC_BUTTON_WORK_MINUTE_UP, m_btn_work_minute_up);
	DDX_Control(pDX, IDC_BUTTON_WORK_MINUTE_DOWN, m_btn_work_minute_down);
	DDX_Control(pDX, IDC_BUTTON_WORK_SECOND_UP, m_btn_work_second_up);
	DDX_Control(pDX, IDC_BUTTON_WORK_SECOND_DOWN, m_btn_work_second_down);
	DDX_Control(pDX, IDC_BUTTON_REST_HOUR_UP, m_btn_rest_hour_up);
	DDX_Control(pDX, IDC_BUTTON_REST_HOUR_DOWN, m_btn_rest_hour_down);
	DDX_Control(pDX, IDC_BUTTON_REST_MINUTE_UP, m_btn_rest_minute_up);
	DDX_Control(pDX, IDC_BUTTON_REST_MINUTE_DOWN, m_btn_rest_minute_down);
	DDX_Control(pDX, IDC_BUTTON_REST_SECOND_UP, m_btn_rest_second_up);
	DDX_Control(pDX, IDC_BUTTON_REST_SECOND_DOWN, m_btn_rest_second_down);
}


BEGIN_MESSAGE_MAP(Timer, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_WORK_HOUR_UP, &Timer::OnBnClickedButtonWorkHourUp)
	ON_BN_CLICKED(IDC_BUTTON_WORK_HOUR_DOWN, &Timer::OnBnClickedButtonWorkHourDown)
	ON_BN_CLICKED(IDC_BUTTON_WORK_MINUTE_UP, &Timer::OnBnClickedButtonWorkMinuteUp)
	ON_BN_CLICKED(IDC_BUTTON_WORK_MINUTE_DOWN, &Timer::OnBnClickedButtonWorkMinuteDown)
	ON_BN_CLICKED(IDC_BUTTON_WORK_SECOND_UP, &Timer::OnBnClickedButtonWorkSecondUp)
	ON_BN_CLICKED(IDC_BUTTON_WORK_SECOND_DOWN, &Timer::OnBnClickedButtonWorkSecondDown)
	ON_BN_CLICKED(IDC_BUTTON_REST_HOUR_UP, &Timer::OnBnClickedButtonRestHourUp)
	ON_BN_CLICKED(IDC_BUTTON_REST_HOUR_DOWN, &Timer::OnBnClickedButtonRestHourDown)
	ON_BN_CLICKED(IDC_BUTTON_REST_MINUTE_UP, &Timer::OnBnClickedButtonRestMinuteUp)
	ON_BN_CLICKED(IDC_BUTTON_REST_MINUTE_DOWN, &Timer::OnBnClickedButtonRestMinuteDown)
	ON_BN_CLICKED(IDC_BUTTON_REST_SECOND_UP, &Timer::OnBnClickedButtonRestSecondUp)
	ON_BN_CLICKED(IDC_BUTTON_REST_SECOND_DOWN, &Timer::OnBnClickedButtonRestSecondDown)
	ON_BN_CLICKED(IDC_BUTTON_STARTANDSTOP2, &Timer::OnBnClickedButtonStartandstop2)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, &Timer::OnBnClickedButtonReset2)
END_MESSAGE_MAP()


// Timer 메시지 처리기


BOOL Timer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(RGB(255, 255, 255));
	m_backBrush.CreateSolidBrush(RGB(50, 50, 50));

	m_btn_startandstop.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_reset.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_hour_up.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_hour_down.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_minute_up.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_minute_down.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_second_up.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_second_down.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_hour_up.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_hour_down.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_minute_up.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_minute_down.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_second_up.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_second_down.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);

	m_edit_work_hour_1.Initialize(25, _T("고딕"));
	m_edit_work_hour_2.Initialize(25, _T("고딕"));
	m_edit_work_minute_1.Initialize(25, _T("고딕"));
	m_edit_work_minute_2.Initialize(25, _T("고딕"));
	m_edit_work_second_1.Initialize(25, _T("고딕"));
	m_edit_work_second_2.Initialize(25, _T("고딕"));
	m_edit_rest_hour_1.Initialize(25, _T("고딕"));
	m_edit_rest_hour_2.Initialize(25, _T("고딕"));
	m_edit_rest_minute_1.Initialize(25, _T("고딕"));
	m_edit_rest_minute_2.Initialize(25, _T("고딕"));
	m_edit_rest_second_1.Initialize(25, _T("고딕"));
	m_edit_rest_second_2.Initialize(25, _T("고딕"));

	m_edit_work_hour_1.SetLimitText(1);
	m_edit_work_hour_2.SetLimitText(1);
	m_edit_work_minute_1.SetLimitText(1);
	m_edit_work_minute_2.SetLimitText(1);
	m_edit_work_second_1.SetLimitText(1);
	m_edit_work_second_2.SetLimitText(1);
	m_edit_rest_hour_1.SetLimitText(1);
	m_edit_rest_hour_2.SetLimitText(1);
	m_edit_rest_minute_1.SetLimitText(1);
	m_edit_rest_minute_2.SetLimitText(1);
	m_edit_rest_second_1.SetLimitText(1);
	m_edit_rest_second_2.SetLimitText(1);

	EmptyTextCondition();

	m_btn_startandstop.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Timer::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void Timer::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	Timer::PostNcDestroy();
}


void Timer::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBaseCalculatorDlg* parent = (CBaseCalculatorDlg*)pParent;
	parent->bTimer = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL Timer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_startandstop)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_reset)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_work_hour_up)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_work_hour_down)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_work_minute_up)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_work_minute_down)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_work_second_up)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_work_second_down)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_rest_hour_up)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_rest_hour_down)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_rest_minute_up)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_rest_minute_down)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_rest_second_up)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_rest_second_down)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_edit_work_hour_1)
		{
			m_edit_work_hour_1.SetWindowTextW(_T(""));
			m_edit_work_hour_1.HideCaret();
			EmptyTextCondition(m_edit_work_hour_1.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_work_hour_2)
		{
			m_edit_work_hour_2.SetWindowTextW(_T(""));
			m_edit_work_hour_2.HideCaret();
			EmptyTextCondition(m_edit_work_hour_2.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_work_minute_1)
		{
			m_edit_work_minute_1.SetWindowTextW(_T(""));
			m_edit_work_minute_1.HideCaret();
			EmptyTextCondition(m_edit_work_minute_1.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_work_minute_2)
		{
			m_edit_work_minute_2.SetWindowTextW(_T(""));
			m_edit_work_minute_2.HideCaret();
			EmptyTextCondition(m_edit_work_minute_2.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_work_second_1)
		{
			m_edit_work_second_1.SetWindowTextW(_T(""));
			m_edit_work_second_1.HideCaret();
			EmptyTextCondition(m_edit_work_second_1.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_work_second_2)
		{
			m_edit_work_second_2.SetWindowTextW(_T(""));
			m_edit_work_second_2.HideCaret();
			EmptyTextCondition(m_edit_work_second_2.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_rest_hour_1)
		{
			m_edit_rest_hour_1.SetWindowTextW(_T(""));
			m_edit_rest_hour_1.HideCaret();
			EmptyTextCondition(m_edit_rest_hour_1.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_rest_hour_2)
		{
			m_edit_rest_hour_2.SetWindowTextW(_T(""));
			m_edit_rest_hour_2.HideCaret();
			EmptyTextCondition(m_edit_rest_hour_2.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_rest_minute_1)
		{
			m_edit_rest_minute_1.SetWindowTextW(_T(""));
			m_edit_rest_minute_1.HideCaret();
			EmptyTextCondition(m_edit_rest_minute_1.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_rest_minute_2)
		{
			m_edit_rest_minute_2.SetWindowTextW(_T(""));
			m_edit_rest_minute_2.HideCaret();
			EmptyTextCondition(m_edit_rest_minute_2.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_rest_second_1)
		{
			m_edit_rest_second_1.SetWindowTextW(_T(""));
			m_edit_rest_second_1.HideCaret();
			EmptyTextCondition(m_edit_rest_second_1.GetDlgCtrlID());
		}
		else if (pMsg->hwnd == m_edit_rest_second_2)
		{
			m_edit_rest_second_2.SetWindowTextW(_T(""));
			m_edit_rest_second_2.HideCaret();
			EmptyTextCondition(m_edit_rest_second_2.GetDlgCtrlID());
		}
	}
	else if (WM_KEYDOWN == pMsg->message)
	{
		if (pMsg->wParam == VK_NUMPAD0) pMsg->wParam = L'0';
		else if (pMsg->wParam == VK_NUMPAD1) pMsg->wParam = L'1';
		else if (pMsg->wParam == VK_NUMPAD2) pMsg->wParam = L'2';
		else if (pMsg->wParam == VK_NUMPAD3) pMsg->wParam = L'3';
		else if (pMsg->wParam == VK_NUMPAD4) pMsg->wParam = L'4';
		else if (pMsg->wParam == VK_NUMPAD5) pMsg->wParam = L'5';
		else if (pMsg->wParam == VK_NUMPAD6) pMsg->wParam = L'6';
		else if (pMsg->wParam == VK_NUMPAD7) pMsg->wParam = L'7';
		else if (pMsg->wParam == VK_NUMPAD8) pMsg->wParam = L'8';
		else if (pMsg->wParam == VK_NUMPAD9) pMsg->wParam = L'9';

		if (pMsg->hwnd == m_edit_work_minute_1)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_minute_2)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == L'6') {}
			else if (pMsg->wParam == L'7') {}
			else if (pMsg->wParam == L'8') {}
			else if (pMsg->wParam == L'9') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_second_1)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_second_2)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == L'6') {}
			else if (pMsg->wParam == L'7') {}
			else if (pMsg->wParam == L'8') {}
			else if (pMsg->wParam == L'9') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_minute_1)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_minute_2)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == L'6') {}
			else if (pMsg->wParam == L'7') {}
			else if (pMsg->wParam == L'8') {}
			else if (pMsg->wParam == L'9') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_second_1)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_second_2)
		{
			if (pMsg->wParam == L'0') {}
			else if (pMsg->wParam == L'1') {}
			else if (pMsg->wParam == L'2') {}
			else if (pMsg->wParam == L'3') {}
			else if (pMsg->wParam == L'4') {}
			else if (pMsg->wParam == L'5') {}
			else if (pMsg->wParam == L'6') {}
			else if (pMsg->wParam == L'7') {}
			else if (pMsg->wParam == L'8') {}
			else if (pMsg->wParam == L'9') {}
			else if (pMsg->wParam == VK_LEFT) {}
			else if (pMsg->wParam == VK_UP) {}
			else if (pMsg->wParam == VK_RIGHT) {}
			else if (pMsg->wParam == VK_DOWN) {}
			else if (pMsg->wParam == VK_BACK) {}
			else
			{
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void Timer::EmptyTextCondition(int nExceptionEditCtlID /* = 0*/)
{
	CString strEmptyCheck;

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_work_hour_1))
	{
		m_edit_work_hour_1.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_work_hour_1.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_work_hour_2))
	{
		m_edit_work_hour_2.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_work_hour_2.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_work_minute_1))
	{
		m_edit_work_minute_1.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_work_minute_1.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_work_minute_2))
	{
		m_edit_work_minute_2.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_work_minute_2.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_work_second_1))
	{
		m_edit_work_second_1.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_work_second_1.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_work_second_2))
	{
		m_edit_work_second_2.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_work_second_2.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_rest_hour_1))
	{
		m_edit_rest_hour_1.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_rest_hour_1.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_rest_hour_2))
	{
		m_edit_rest_hour_2.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_rest_hour_2.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_rest_minute_1))
	{
		m_edit_rest_minute_1.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_rest_minute_1.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_rest_minute_2))
	{
		m_edit_rest_minute_2.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_rest_minute_2.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_rest_second_1))
	{
		m_edit_rest_second_1.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_rest_second_1.SetWindowTextW(_T("0"));
		}
	}

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_rest_second_2))
	{
		m_edit_rest_second_2.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_rest_second_2.SetWindowTextW(_T("0"));
		}
	}
}


void Timer::OnBnClickedButtonWorkHourUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_work_hour_1.GetWindowTextW(strFirstText);
	m_edit_work_hour_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText >= 9 && nFirstText >= 9)
	{
		return;
	}
	else if (nLastText >= 9 && nFirstText < 9)
	{
		nFirstText++;
		nLastText = 0;
	}
	else
	{
		nLastText++;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_work_hour_1.SetWindowTextW(strFirstText);
	m_edit_work_hour_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonWorkHourDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_work_hour_1.GetWindowTextW(strFirstText);
	m_edit_work_hour_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText <= 0 && nFirstText <= 0)
	{
		return;
	}
	else if (nLastText <= 0 && nFirstText > 0)
	{
		nFirstText--;
		nLastText = 9;
	}
	else
	{
		nLastText--;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_work_hour_1.SetWindowTextW(strFirstText);
	m_edit_work_hour_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonWorkMinuteUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_work_minute_1.GetWindowTextW(strFirstText);
	m_edit_work_minute_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText >= 9 && nFirstText >= 5)
	{
		return;
	}
	else if (nLastText >= 9 && nFirstText < 5)
	{
		nFirstText++;
		nLastText = 0;
	}
	else
	{
		nLastText++;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_work_minute_1.SetWindowTextW(strFirstText);
	m_edit_work_minute_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonWorkMinuteDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_work_minute_1.GetWindowTextW(strFirstText);
	m_edit_work_minute_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText <= 0 && nFirstText <= 0)
	{
		return;
	}
	else if (nLastText <= 0 && nFirstText > 0)
	{
		nFirstText--;
		nLastText = 9;
	}
	else
	{
		nLastText--;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_work_minute_1.SetWindowTextW(strFirstText);
	m_edit_work_minute_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonWorkSecondUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_work_second_1.GetWindowTextW(strFirstText);
	m_edit_work_second_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText >= 9 && nFirstText >= 5)
	{
		return;
	}
	else if (nLastText >= 9 && nFirstText < 5)
	{
		nFirstText++;
		nLastText = 0;
	}
	else
	{
		nLastText++;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_work_second_1.SetWindowTextW(strFirstText);
	m_edit_work_second_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonWorkSecondDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_work_second_1.GetWindowTextW(strFirstText);
	m_edit_work_second_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText <= 0 && nFirstText <= 0)
	{
		return;
	}
	else if (nLastText <= 0 && nFirstText > 0)
	{
		nFirstText--;
		nLastText = 9;
	}
	else
	{
		nLastText--;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_work_second_1.SetWindowTextW(strFirstText);
	m_edit_work_second_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonRestHourUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_rest_hour_1.GetWindowTextW(strFirstText);
	m_edit_rest_hour_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText >= 9 && nFirstText >= 9)
	{
		return;
	}
	else if (nLastText >= 9 && nFirstText < 9)
	{
		nFirstText++;
		nLastText = 0;
	}
	else
	{
		nLastText++;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_rest_hour_1.SetWindowTextW(strFirstText);
	m_edit_rest_hour_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonRestHourDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_rest_hour_1.GetWindowTextW(strFirstText);
	m_edit_rest_hour_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText <= 0 && nFirstText <= 0)
	{
		return;
	}
	else if (nLastText <= 0 && nFirstText > 0)
	{
		nFirstText--;
		nLastText = 9;
	}
	else
	{
		nLastText--;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_rest_hour_1.SetWindowTextW(strFirstText);
	m_edit_rest_hour_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonRestMinuteUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_rest_minute_1.GetWindowTextW(strFirstText);
	m_edit_rest_minute_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText >= 9 && nFirstText >= 5)
	{
		return;
	}
	else if (nLastText >= 9 && nFirstText < 5)
	{
		nFirstText++;
		nLastText = 0;
	}
	else
	{
		nLastText++;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_rest_minute_1.SetWindowTextW(strFirstText);
	m_edit_rest_minute_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonRestMinuteDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_rest_minute_1.GetWindowTextW(strFirstText);
	m_edit_rest_minute_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText <= 0 && nFirstText <= 0)
	{
		return;
	}
	else if (nLastText <= 0 && nFirstText > 0)
	{
		nFirstText--;
		nLastText = 9;
	}
	else
	{
		nLastText--;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_rest_minute_1.SetWindowTextW(strFirstText);
	m_edit_rest_minute_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonRestSecondUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_rest_second_1.GetWindowTextW(strFirstText);
	m_edit_rest_second_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText >= 9 && nFirstText >= 5)
	{
		return;
	}
	else if (nLastText >= 9 && nFirstText < 5)
	{
		nFirstText++;
		nLastText = 0;
	}
	else
	{
		nLastText++;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_rest_second_1.SetWindowTextW(strFirstText);
	m_edit_rest_second_2.SetWindowTextW(strLastText);
}


void Timer::OnBnClickedButtonRestSecondDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EmptyTextCondition();

	CString strFirstText, strLastText;
	m_edit_rest_second_1.GetWindowTextW(strFirstText);
	m_edit_rest_second_2.GetWindowTextW(strLastText);

	int nFirstText = _ttoi(strFirstText);
	int nLastText = _ttoi(strLastText);

	if (nLastText <= 0 && nFirstText <= 0)
	{
		return;
	}
	else if (nLastText <= 0 && nFirstText > 0)
	{
		nFirstText--;
		nLastText = 9;
	}
	else
	{
		nLastText--;
	}

	strFirstText.Format(_T("%d"), nFirstText);
	strLastText.Format(_T("%d"), nLastText);

	m_edit_rest_second_1.SetWindowTextW(strFirstText);
	m_edit_rest_second_2.SetWindowTextW(strLastText);
}

void Timer::SetEnabledCtrl(BOOL bEnabled)
{
	m_btn_reset.EnableWindow(bEnabled);
	m_btn_work_hour_up.EnableWindow(bEnabled);
	m_btn_work_hour_down.EnableWindow(bEnabled);
	m_btn_work_minute_up.EnableWindow(bEnabled);
	m_btn_work_minute_down.EnableWindow(bEnabled);
	m_btn_work_second_up.EnableWindow(bEnabled);
	m_btn_work_second_down.EnableWindow(bEnabled);
	m_btn_rest_hour_up.EnableWindow(bEnabled);
	m_btn_rest_hour_down.EnableWindow(bEnabled);
	m_btn_rest_minute_up.EnableWindow(bEnabled);
	m_btn_rest_minute_down.EnableWindow(bEnabled);
	m_btn_rest_second_up.EnableWindow(bEnabled);
	m_btn_rest_second_down.EnableWindow(bEnabled);

	m_edit_work_hour_1.EnableWindow(bEnabled);
	m_edit_work_hour_2.EnableWindow(bEnabled);
	m_edit_work_minute_1.EnableWindow(bEnabled);
	m_edit_work_minute_2.EnableWindow(bEnabled);
	m_edit_work_second_1.EnableWindow(bEnabled);
	m_edit_work_second_2.EnableWindow(bEnabled);
	m_edit_rest_hour_1.EnableWindow(bEnabled);
	m_edit_rest_hour_2.EnableWindow(bEnabled);
	m_edit_rest_minute_1.EnableWindow(bEnabled);
	m_edit_rest_minute_2.EnableWindow(bEnabled);
	m_edit_rest_second_1.EnableWindow(bEnabled);
	m_edit_rest_second_2.EnableWindow(bEnabled);
}

void Timer::OnBnClickedButtonStartandstop2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (bStart)
	{
		bStart = false;
		bThread = true;
		m_btn_startandstop.SetWindowTextW(_T("정지"));
		SetEnabledCtrl(FALSE);
		m_thread = AfxBeginThread(thrTimer, this);
	}
	else
	{
		bStart = true;
		bThread = false;
		m_btn_startandstop.SetWindowTextW(_T("시작"));
		SetEnabledCtrl(TRUE);
	}
}

UINT Timer::thrTimer(LPVOID method)
{
	Timer* timer = (Timer*)method;
	timer->StartTimer();

	return 0;
}


void Timer::StartTimer()
{
	while (bThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();

		if (!bWorkEnd)
		{
			CalculateWorkTime();
		}
		else
		{
			// 휴식시간 계산함수 추가
		}

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep(1000 - duration + duration);
	}
}

void Timer::CalculateWorkTime()
{
	CString strHour1, strHour2, strMinute1, strMinute2, strSecond1, strSecond2;
	m_edit_work_hour_1.GetWindowTextW(strHour1);
	m_edit_work_hour_2.GetWindowTextW(strHour2);
	m_edit_work_minute_1.GetWindowTextW(strMinute1);
	m_edit_work_minute_2.GetWindowTextW(strMinute2);
	m_edit_work_second_1.GetWindowTextW(strSecond1);
	m_edit_work_second_2.GetWindowTextW(strSecond2);

	int nHour1 = _ttoi(strHour1);
	int nHour2 = _ttoi(strHour2);
	int nMinute1 = _ttoi(strMinute1);
	int nMinute2 = _ttoi(strMinute2);
	int nSecond1 = _ttoi(strSecond1);
	int nSecond2 = _ttoi(strSecond2);

	if (nHour1 == 0 && nHour2 == 0 && nMinute1 == 0 && nMinute2 == 0 && nSecond1 == 0 && nSecond2 == 0)
	{
		bWorkEnd = true;
		// 알람소리 스레드
	}
}

void Timer::OnBnClickedButtonReset2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_work_hour_1.SetWindowTextW(_T("0"));
	m_edit_work_hour_2.SetWindowTextW(_T("0"));
	m_edit_work_minute_1.SetWindowTextW(_T("0"));
	m_edit_work_minute_2.SetWindowTextW(_T("0"));
	m_edit_work_second_1.SetWindowTextW(_T("0"));
	m_edit_work_second_2.SetWindowTextW(_T("0"));
	m_edit_rest_hour_1.SetWindowTextW(_T("0"));
	m_edit_rest_hour_2.SetWindowTextW(_T("0"));
	m_edit_rest_minute_1.SetWindowTextW(_T("0"));
	m_edit_rest_minute_2.SetWindowTextW(_T("0"));
	m_edit_rest_second_1.SetWindowTextW(_T("0"));
	m_edit_rest_second_2.SetWindowTextW(_T("0"));
}
