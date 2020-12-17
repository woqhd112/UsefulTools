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
	bFirstRestClock = true;
	bFirstWorkClock = true;
	bWorkEnd = false;
	bRestEnd = false;
	os = OPERATE_STATE_NONE;
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
	DDX_Control(pDX, IDC_RADIO_INFINITE, m_radio_infinite);
	DDX_Control(pDX, IDC_RADIO_CUSTOM, m_radio_custom);
	DDX_Control(pDX, IDC_EDIT_CUSTOM_COUNT, m_edit_custom_count);
	DDX_Control(pDX, IDC_EDIT_STATE, m_edit_state);
	DDX_Control(pDX, IDC_BUTTON_COLOR_NONE, m_btn_color_none);
	DDX_Control(pDX, IDC_BUTTON_COLOR_WORKING, m_btn_color_working);
	DDX_Control(pDX, IDC_BUTTON_COLOR_RESTING, m_btn_color_resting);
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
	ON_BN_CLICKED(IDC_RADIO_INFINITE, &Timer::OnBnClickedRadioInfinite)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, &Timer::OnBnClickedRadioCustom)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_COLOR_NONE, &Timer::OnBnClickedButtonColorNone)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_WORKING, &Timer::OnBnClickedButtonColorWorking)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_RESTING, &Timer::OnBnClickedButtonColorResting)
END_MESSAGE_MAP()


// Timer 메시지 처리기


BOOL Timer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	LoadSettingColor(&none_color, &work_color, &rest_color);
	/*none_color = BACKGROUND_COLOR_YELLOW;
	work_color = BACKGROUND_COLOR_GREEN;
	rest_color = BACKGROUND_COLOR_RED;*/

	this->SetBackgroundColor(none_color);
	m_returnBrush.CreateSolidBrush(RGB(255, 255, 255));

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

	m_btn_color_none.Initialize(none_color, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_color_working.Initialize(work_color, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_color_resting.Initialize(rest_color, CMFCButton::FlatStyle::BUTTONSTYLE_3D);

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
	m_edit_custom_count.Initialize(15, _T("고딕"));
	m_edit_state.Initialize(25, _T("고딕"));

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
	
	//m_edit_state.EnableWindow(FALSE);
	m_edit_state.SetWindowTextW(_T("None"));

	m_radio_custom.SetCheck(TRUE);
	m_edit_custom_count.SetWindowTextW(_T("1"));

	m_btn_startandstop.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void Timer::LoadSettingColor(COLORREF* none_color, COLORREF* work_color, COLORREF* rest_color)
{
	// 파일, xml파일 불러오기 함수
	bool bSavedXml = false;
	CMarkup markUp;
	if (markUp.Load(_T("Config\\Timer\\ColorSetting.conf")))
	{
		markUp.FindElem(_T("Timer"));
		markUp.IntoElem();
		while (markUp.FindElem(_T("Color")))
		{
			CString strColorState = markUp.GetAttrib(_T("name"));
			CString strColorRed = markUp.GetAttrib(_T("redv"));
			CString strColorGreen = markUp.GetAttrib(_T("greenv"));
			CString strColorBlue = markUp.GetAttrib(_T("bluev"));

			if (strColorState == _T("none"))
			{
				*none_color = RGB(_ttoi(strColorRed), _ttoi(strColorGreen), _ttoi(strColorBlue));
			}
			else if (strColorState == _T("working"))
			{
				*work_color = RGB(_ttoi(strColorRed), _ttoi(strColorGreen), _ttoi(strColorBlue));
			}
			else if (strColorState == _T("resting"))
			{
				*rest_color = RGB(_ttoi(strColorRed), _ttoi(strColorGreen), _ttoi(strColorBlue));
			}
			bSavedXml = true;
		}
	}
	else
	{
		// 이부분 리팩토링 그리고 사용자지정색 디폴트 추가
		BOOL bRval = FALSE;
		CString szRoot = _T("");

		TCHAR chFilePath[256] = { 0, };
		GetModuleFileName(NULL, chFilePath, 256);
		szRoot = (LPCTSTR)chFilePath;
		int nLen = szRoot.ReverseFind('\\');

		if (nLen > 0)
		{
			szRoot = szRoot.Left(nLen);
		}

		CFileFind rootFind;
		if (!rootFind.FindFile(szRoot + _T("\\BaseCalculator"))) {
			szRoot += _T("\\Config");
		}
		else
		{
			szRoot += _T("\\BaseCalculator\\Config");
		}
		rootFind.Close();

		CFileFind configFind;
		if (!configFind.FindFile(szRoot))
		{
			CreateDirectory(szRoot, NULL);

			CFileFind timerFind;
			szRoot += _T("\\Timer");
			if (!timerFind.FindFile(szRoot))
			{
				CreateDirectory(szRoot, NULL);
				CFileFind xmlFind;
				szRoot += _T("\\ColorSetting.conf");
				if (!timerFind.FindFile(szRoot))
				{
					markUp.AddElem(_T("Timer"));
					markUp.IntoElem();
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("none"));
					markUp.AddAttrib(_T("redv"), _T("241"));
					markUp.AddAttrib(_T("greenv"), _T("209"));
					markUp.AddAttrib(_T("bluev"), _T("85"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("working"));
					markUp.AddAttrib(_T("redv"), _T("101"));
					markUp.AddAttrib(_T("greenv"), _T("179"));
					markUp.AddAttrib(_T("bluev"), _T("97"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("resting"));
					markUp.AddAttrib(_T("redv"), _T("215"));
					markUp.AddAttrib(_T("greenv"), _T("70"));
					markUp.AddAttrib(_T("bluev"), _T("57"));
					*none_color = BACKGROUND_COLOR_YELLOW;
					*work_color = BACKGROUND_COLOR_GREEN;
					*rest_color = BACKGROUND_COLOR_RED;
					bSavedXml = true;
				}
				xmlFind.Close();
			}
			else
			{
				CFileFind xmlFind;
				szRoot += _T("\\ColorSetting.conf");
				if (!timerFind.FindFile(szRoot))
				{
					markUp.AddElem(_T("Timer"));
					markUp.IntoElem();
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("none"));
					markUp.AddAttrib(_T("redv"), _T("241"));
					markUp.AddAttrib(_T("greenv"), _T("209"));
					markUp.AddAttrib(_T("bluev"), _T("85"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("working"));
					markUp.AddAttrib(_T("redv"), _T("101"));
					markUp.AddAttrib(_T("greenv"), _T("179"));
					markUp.AddAttrib(_T("bluev"), _T("97"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("resting"));
					markUp.AddAttrib(_T("redv"), _T("215"));
					markUp.AddAttrib(_T("greenv"), _T("70"));
					markUp.AddAttrib(_T("bluev"), _T("57"));
					*none_color = BACKGROUND_COLOR_YELLOW;
					*work_color = BACKGROUND_COLOR_GREEN;
					*rest_color = BACKGROUND_COLOR_RED;
					bSavedXml = true;
				}
				xmlFind.Close();
			}
			timerFind.Close();
		}
		else
		{
			CFileFind timerFind;
			szRoot += _T("\\Timer");
			if (!timerFind.FindFile(szRoot))
			{
				CreateDirectory(szRoot, NULL);
				CFileFind xmlFind;
				szRoot += _T("\\ColorSetting.conf");
				if (!timerFind.FindFile(szRoot))
				{
					markUp.AddElem(_T("Timer"));
					markUp.IntoElem();
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("none"));
					markUp.AddAttrib(_T("redv"), _T("241"));
					markUp.AddAttrib(_T("greenv"), _T("209"));
					markUp.AddAttrib(_T("bluev"), _T("85"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("working"));
					markUp.AddAttrib(_T("redv"), _T("101"));
					markUp.AddAttrib(_T("greenv"), _T("179"));
					markUp.AddAttrib(_T("bluev"), _T("97"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("resting"));
					markUp.AddAttrib(_T("redv"), _T("215"));
					markUp.AddAttrib(_T("greenv"), _T("70"));
					markUp.AddAttrib(_T("bluev"), _T("57"));
					*none_color = BACKGROUND_COLOR_YELLOW;
					*work_color = BACKGROUND_COLOR_GREEN;
					*rest_color = BACKGROUND_COLOR_RED;
					bSavedXml = true;
				}
				xmlFind.Close();
			}
			else
			{
				CFileFind xmlFind;
				szRoot += _T("\\ColorSetting.conf");
				if (!timerFind.FindFile(szRoot))
				{
					markUp.AddElem(_T("Timer"));
					markUp.IntoElem();
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("none"));
					markUp.AddAttrib(_T("redv"), _T("241"));
					markUp.AddAttrib(_T("greenv"), _T("209"));
					markUp.AddAttrib(_T("bluev"), _T("85"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("working"));
					markUp.AddAttrib(_T("redv"), _T("101"));
					markUp.AddAttrib(_T("greenv"), _T("179"));
					markUp.AddAttrib(_T("bluev"), _T("97"));
					markUp.AddElem(_T("Color"));
					markUp.AddAttrib(_T("name"), _T("resting"));
					markUp.AddAttrib(_T("redv"), _T("215"));
					markUp.AddAttrib(_T("greenv"), _T("70"));
					markUp.AddAttrib(_T("bluev"), _T("57"));
					*none_color = BACKGROUND_COLOR_YELLOW;
					*work_color = BACKGROUND_COLOR_GREEN;
					*rest_color = BACKGROUND_COLOR_RED;
					bSavedXml = true;
				}
				xmlFind.Close();
			}
		}
		configFind.Close();
	}
	if (bSavedXml)
	{
		SaveXml(&markUp);
	}
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
		else if (pMsg->hwnd == m_edit_state)
		{
			m_edit_state.HideCaret();
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
	m_radio_infinite.EnableWindow(bEnabled);
	m_radio_custom.EnableWindow(bEnabled);

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
	if(m_radio_custom.GetCheck())
		m_edit_custom_count.EnableWindow(bEnabled);
}

bool Timer::WorkTimeToUnderTenSecondCondition()
{
	bool bReturn = true;

	CString strHour, strMinute, strSecond, strHour1, strHour2, strMinute1, strMinute2, strSecond1, strSecond2;
	m_edit_work_hour_1.GetWindowTextW(strHour1);
	m_edit_work_hour_2.GetWindowTextW(strHour2);
	m_edit_work_minute_1.GetWindowTextW(strMinute1);
	m_edit_work_minute_2.GetWindowTextW(strMinute2);
	m_edit_work_second_1.GetWindowTextW(strSecond1);
	m_edit_work_second_2.GetWindowTextW(strSecond2);

	strHour.Format(_T("%s%s"), strHour1, strHour2);
	strMinute.Format(_T("%s%s"), strMinute1, strMinute2);
	strSecond.Format(_T("%s%s"), strSecond1, strSecond2);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);
	if (nHour == 0 && nMinute == 0 && nSecond < 10)
	{
		bReturn = false;
	}

	return bReturn;
}

bool Timer::RestTimeToUnderTenSecondCondition()
{
	bool bReturn = true;

	CString strHour, strMinute, strSecond, strHour1, strHour2, strMinute1, strMinute2, strSecond1, strSecond2;
	m_edit_rest_hour_1.GetWindowTextW(strHour1);
	m_edit_rest_hour_2.GetWindowTextW(strHour2);
	m_edit_rest_minute_1.GetWindowTextW(strMinute1);
	m_edit_rest_minute_2.GetWindowTextW(strMinute2);
	m_edit_rest_second_1.GetWindowTextW(strSecond1);
	m_edit_rest_second_2.GetWindowTextW(strSecond2);

	strHour.Format(_T("%s%s"), strHour1, strHour2);
	strMinute.Format(_T("%s%s"), strMinute1, strMinute2);
	strSecond.Format(_T("%s%s"), strSecond1, strSecond2);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);
	if (nHour == 0 && nMinute == 0 && nSecond < 10)
	{
		bReturn = false;
	}

	return bReturn;
}

void Timer::OnBnClickedButtonStartandstop2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (bStart)
	{
		// 텍스트 검사해서 워킹, 레스트가 10초미만일경우 리턴
		// func
		if (!WorkTimeToUnderTenSecondCondition())
		{
			MessageBox(_T("Work Time의 최소시간은 10초 입니다."));
			return;
		}

		if (!RestTimeToUnderTenSecondCondition())
		{
			MessageBox(_T("Rest Time의 최소시간은 10초 입니다."));
			return;
		}

		bStart = false;
		bThread = true;
		m_btn_startandstop.SetWindowTextW(_T("정지"));
		SetEnabledCtrl(FALSE);
		m_thread = AfxBeginThread(thrTimer, this);
	}
	else
	{
		bFirstRestClock = true;
		bFirstWorkClock = true;
		bStart = true;
		bThread = false;
		m_btn_startandstop.SetWindowTextW(_T("시작"));
		SetEnabledCtrl(TRUE);
		SetOperateStateToColor(OPERATE_STATE_NONE);
	}
}

UINT Timer::thrTimer(LPVOID method)
{
	Timer* timer = (Timer*)method;
	timer->StartTimer();

	return 0;
}

void Timer::SetGlobalEditText()
{
	CString strHour1, strHour2, strMinute1, strMinute2, strSecond1, strSecond2;
	m_edit_work_hour_1.GetWindowTextW(strHour1);
	m_edit_work_hour_2.GetWindowTextW(strHour2);
	m_edit_work_minute_1.GetWindowTextW(strMinute1);
	m_edit_work_minute_2.GetWindowTextW(strMinute2);
	m_edit_work_second_1.GetWindowTextW(strSecond1);
	m_edit_work_second_2.GetWindowTextW(strSecond2);

	g_str_work_hour.Format(_T("%s%s"), strHour1, strHour2);
	g_str_work_minute.Format(_T("%s%s"), strMinute1, strMinute2);
	g_str_work_second.Format(_T("%s%s"), strSecond1, strSecond2);

	m_edit_rest_hour_1.GetWindowTextW(strHour1);
	m_edit_rest_hour_2.GetWindowTextW(strHour2);
	m_edit_rest_minute_1.GetWindowTextW(strMinute1);
	m_edit_rest_minute_2.GetWindowTextW(strMinute2);
	m_edit_rest_second_1.GetWindowTextW(strSecond1);
	m_edit_rest_second_2.GetWindowTextW(strSecond2);

	g_str_rest_hour.Format(_T("%s%s"), strHour1, strHour2);
	g_str_rest_minute.Format(_T("%s%s"), strMinute1, strMinute2);
	g_str_rest_second.Format(_T("%s%s"), strSecond1, strSecond2);
}

bool Timer::CheckRepeatCount()
{
	bFirstRestClock = true;
	bFirstWorkClock = true;
	CString strRepeatCount;
	m_edit_custom_count.GetWindowTextW(strRepeatCount);
	int nCount = _ttoi(strRepeatCount);
	if (nCount == 0)
	{
		bStart = true;
		bThread = false;
		m_btn_startandstop.SetWindowTextW(_T("시작"));
		SetEnabledCtrl(TRUE);
		SetOperateStateToColor(OPERATE_STATE_NONE);
		return true;
	}
	nCount--;
	strRepeatCount.Format(_T("%d"), nCount);
	m_edit_custom_count.SetWindowTextW(strRepeatCount);

	return false;
}

void Timer::StartTimer()
{
	EmptyTextCondition();
	SetGlobalEditText();
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
			CalculateRestTime();
		}

		if (bRestEnd)
		{
			bWorkEnd = false;
			bRestEnd = false;

			if (m_radio_custom.GetCheck())
			{
				if (CheckRepeatCount())
				{
					// 마무리 멘트 알람 함수
					// func
					break;
				}
			}
			else
			{
				bFirstRestClock = true;
				bFirstWorkClock = true;
			}
		}

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep(1000 - duration + duration);
	}
}

void Timer::CalculateWorkTime()
{
	if (bFirstWorkClock)
	{
		// 일 시작 알람 함수
		// func
		bFirstWorkClock = false;
		SetOperateStateToColor(OPERATE_STATE_WORKING);

		m_edit_rest_hour_1.SetWindowTextW((CString)g_str_rest_hour.GetAt(0));
		m_edit_rest_hour_2.SetWindowTextW((CString)g_str_rest_hour.GetAt(1));
		m_edit_rest_minute_1.SetWindowTextW((CString)g_str_rest_minute.GetAt(0));
		m_edit_rest_minute_2.SetWindowTextW((CString)g_str_rest_minute.GetAt(1));
		m_edit_rest_second_1.SetWindowTextW((CString)g_str_rest_second.GetAt(0));
		m_edit_rest_second_2.SetWindowTextW((CString)g_str_rest_second.GetAt(1));
	}
	CString strHour, strMinute, strSecond, strHour1, strHour2, strMinute1, strMinute2, strSecond1, strSecond2;
	m_edit_work_hour_1.GetWindowTextW(strHour1);
	m_edit_work_hour_2.GetWindowTextW(strHour2);
	m_edit_work_minute_1.GetWindowTextW(strMinute1);
	m_edit_work_minute_2.GetWindowTextW(strMinute2);
	m_edit_work_second_1.GetWindowTextW(strSecond1);
	m_edit_work_second_2.GetWindowTextW(strSecond2);

	strHour.Format(_T("%s%s"), strHour1, strHour2);
	strMinute.Format(_T("%s%s"), strMinute1, strMinute2);
	strSecond.Format(_T("%s%s"), strSecond1, strSecond2);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);

	if (nHour > 0 && nMinute == 0 && nSecond == 0)
	{
		nHour--;
		nMinute = 59;
		nSecond = 59;
	}
	else if (nMinute > 0 && nSecond == 0)
	{
		nMinute--;
		nSecond = 59;
	}
	else if (nSecond > 0)
	{
		nSecond--;
	}

	if (nHour == 0 && nMinute == 0 && nSecond == 0)
	{
		bWorkEnd = true;
		// 종료 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 1)
	{
		// 종료 1초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 2)
	{
		// 종료 2초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 3)
	{
		// 종료 3초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 4)
	{
		// 종료 4초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 5)
	{
		// 종료 5초전 알람 함수
		// func
	}
	strHour.Format(_T("%02d"), nHour);
	strMinute.Format(_T("%02d"), nMinute);
	strSecond.Format(_T("%02d"), nSecond);
	m_edit_work_hour_1.SetWindowTextW((CString)strHour.GetAt(0));
	m_edit_work_hour_2.SetWindowTextW((CString)strHour.GetAt(1));
	m_edit_work_minute_1.SetWindowTextW((CString)strMinute.GetAt(0));
	m_edit_work_minute_2.SetWindowTextW((CString)strMinute.GetAt(1));
	m_edit_work_second_1.SetWindowTextW((CString)strSecond.GetAt(0));
	m_edit_work_second_2.SetWindowTextW((CString)strSecond.GetAt(1));
}

void Timer::CalculateRestTime()
{
	if (bFirstRestClock)
	{
		
		// 휴식 시작 알람 함수
		// func
		bFirstRestClock = false;
		SetOperateStateToColor(OPERATE_STATE_RESTING);

		CString strCount;
		m_edit_custom_count.GetWindowTextW(strCount);
		if (_ttoi(strCount) > 0)
		{
			m_edit_work_hour_1.SetWindowTextW((CString)g_str_work_hour.GetAt(0));
			m_edit_work_hour_2.SetWindowTextW((CString)g_str_work_hour.GetAt(1));
			m_edit_work_minute_1.SetWindowTextW((CString)g_str_work_minute.GetAt(0));
			m_edit_work_minute_2.SetWindowTextW((CString)g_str_work_minute.GetAt(1));
			m_edit_work_second_1.SetWindowTextW((CString)g_str_work_second.GetAt(0));
			m_edit_work_second_2.SetWindowTextW((CString)g_str_work_second.GetAt(1));
		}
	}
	CString strHour, strMinute, strSecond, strHour1, strHour2, strMinute1, strMinute2, strSecond1, strSecond2;
	m_edit_rest_hour_1.GetWindowTextW(strHour1);
	m_edit_rest_hour_2.GetWindowTextW(strHour2);
	m_edit_rest_minute_1.GetWindowTextW(strMinute1);
	m_edit_rest_minute_2.GetWindowTextW(strMinute2);
	m_edit_rest_second_1.GetWindowTextW(strSecond1);
	m_edit_rest_second_2.GetWindowTextW(strSecond2);

	strHour.Format(_T("%s%s"), strHour1, strHour2);
	strMinute.Format(_T("%s%s"), strMinute1, strMinute2);
	strSecond.Format(_T("%s%s"), strSecond1, strSecond2);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);

	if (nHour > 0 && nMinute == 0 && nSecond == 0)
	{
		nHour--;
		nMinute = 59;
		nSecond = 59;
	}
	else if (nMinute > 0 && nSecond == 0)
	{
		nMinute--;
		nSecond = 59;
	}
	else if (nSecond > 0)
	{
		nSecond--;
	}

	if (nHour == 0 && nMinute == 0 && nSecond == 0)
	{
		bRestEnd = true;
		// 종료 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 1)
	{
		// 종료 1초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 2)
	{
		// 종료 2초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 3)
	{
		// 종료 3초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 4)
	{
		// 종료 4초전 알람 함수
		// func
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 5)
	{
		// 종료 5초전 알람 함수
		// func
	}
	strHour.Format(_T("%02d"), nHour);
	strMinute.Format(_T("%02d"), nMinute);
	strSecond.Format(_T("%02d"), nSecond);
	m_edit_rest_hour_1.SetWindowTextW((CString)strHour.GetAt(0));
	m_edit_rest_hour_2.SetWindowTextW((CString)strHour.GetAt(1));
	m_edit_rest_minute_1.SetWindowTextW((CString)strMinute.GetAt(0));
	m_edit_rest_minute_2.SetWindowTextW((CString)strMinute.GetAt(1));
	m_edit_rest_second_1.SetWindowTextW((CString)strSecond.GetAt(0));
	m_edit_rest_second_2.SetWindowTextW((CString)strSecond.GetAt(1));
}

void Timer::SetOperateStateToColor(OperateState os)
{
	this->os = os;
	if (os == OPERATE_STATE_NONE)
	{
		OnCtlColor(m_edit_state.GetWindowDC(), &m_edit_state, CTLCOLOR_STATIC);
		m_edit_state.SetWindowTextW(_T("None"));
		this->SetBackgroundColor(none_color);
	}
	else if (os == OPERATE_STATE_RESTING)
	{
		OnCtlColor(m_edit_state.GetWindowDC(), &m_edit_state, CTLCOLOR_STATIC);
		m_edit_state.SetWindowTextW(_T("Resting"));
		this->SetBackgroundColor(rest_color);
	}
	else if (os == OPERATE_STATE_WORKING)
	{
		OnCtlColor(m_edit_state.GetWindowDC(), &m_edit_state, CTLCOLOR_STATIC);
		m_edit_state.SetWindowTextW(_T("Working"));
		this->SetBackgroundColor(work_color);
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


void Timer::OnBnClickedRadioInfinite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_custom_count.EnableWindow(FALSE);
}


void Timer::OnBnClickedRadioCustom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_custom_count.EnableWindow(TRUE);
}


HBRUSH Timer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_STATE)
		{
			if (os == OPERATE_STATE_NONE)
			{
				pDC->SetTextColor(none_color);
				pDC->SetBkColor(RGB(255, 255, 255));
				hbr = (HBRUSH)m_returnBrush;
			}
			else if (os == OPERATE_STATE_RESTING)
			{
				pDC->SetTextColor(rest_color);
				pDC->SetBkColor(RGB(255, 255, 255));
				hbr = (HBRUSH)m_returnBrush;
			}
			else if (os == OPERATE_STATE_WORKING)
			{
				pDC->SetTextColor(work_color);
				pDC->SetBkColor(RGB(255, 255, 255));
				hbr = (HBRUSH)m_returnBrush;
			}
		}
	}
	else
	{
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void Timer::OnBnClickedButtonColorNone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog none_color_dlg(none_color, CC_FULLOPEN, this);
	COLORREF user_color_list[16] = { BACKGROUND_COLOR_YELLOW , BACKGROUND_COLOR_GREEN , BACKGROUND_COLOR_RED , };
	for (int i = 3; i < 16; i++)
	{
		user_color_list[i] = RGB(255, 255, 255);
	}
	none_color_dlg.m_cc.lpCustColors = user_color_list;

	if (none_color_dlg.DoModal())
	{
		none_color = none_color_dlg.GetColor();
		m_btn_color_none.SetFaceColor(none_color);
		this->SetBackgroundColor(none_color);

		CMarkup markUp;
		if (markUp.Load(_T("Config\\Timer\\ColorSetting.conf")))
		{
			markUp.FindElem(_T("Timer"));
			markUp.IntoElem();
			while (markUp.FindElem(_T("Color")))
			{
				CString strColorState = markUp.GetAttrib(_T("name"));
				
				if (strColorState == _T("none"))
				{
					markUp.SetAttrib(_T("redv"), GetRValue(none_color));
					markUp.SetAttrib(_T("greenv"), GetGValue(none_color));
					markUp.SetAttrib(_T("bluev"), GetBValue(none_color));
				}
			}
		}
		SaveXml(&markUp);
	}
}


void Timer::OnBnClickedButtonColorWorking()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog work_color_dlg(work_color, CC_FULLOPEN, this);
	COLORREF user_color_list[16] = { BACKGROUND_COLOR_YELLOW , BACKGROUND_COLOR_GREEN , BACKGROUND_COLOR_RED , };
	for (int i = 3; i < 16; i++)
	{
		user_color_list[i] = RGB(255, 255, 255);
	}
	work_color_dlg.m_cc.lpCustColors = user_color_list;

	if (work_color_dlg.DoModal())
	{
		work_color = work_color_dlg.GetColor();
		m_btn_color_working.SetFaceColor(work_color);

		CMarkup markUp;
		if (markUp.Load(_T("Config\\Timer\\ColorSetting.conf")))
		{
			markUp.FindElem(_T("Timer"));
			markUp.IntoElem();
			while (markUp.FindElem(_T("Color")))
			{
				CString strColorState = markUp.GetAttrib(_T("name"));

				if (strColorState == _T("working"))
				{
					markUp.SetAttrib(_T("redv"), GetRValue(work_color));
					markUp.SetAttrib(_T("greenv"), GetGValue(work_color));
					markUp.SetAttrib(_T("bluev"), GetBValue(work_color));
				}
			}
		}
		SaveXml(&markUp);
	}
}


void Timer::OnBnClickedButtonColorResting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog rest_color_dlg(rest_color, CC_FULLOPEN, this);
	COLORREF user_color_list[16] = { BACKGROUND_COLOR_YELLOW , BACKGROUND_COLOR_GREEN , BACKGROUND_COLOR_RED , };
	for (int i = 3; i < 16; i++)
	{
		user_color_list[i] = RGB(255, 255, 255);
	}
	rest_color_dlg.m_cc.lpCustColors = user_color_list;

	if (rest_color_dlg.DoModal())
	{
		rest_color = rest_color_dlg.GetColor();
		m_btn_color_resting.SetFaceColor(rest_color);

		CMarkup markUp;
		if (markUp.Load(_T("Config\\Timer\\ColorSetting.conf")))
		{
			markUp.FindElem(_T("Timer"));
			markUp.IntoElem();
			while (markUp.FindElem(_T("Color")))
			{
				CString strColorState = markUp.GetAttrib(_T("name"));

				if (strColorState == _T("resting"))
				{
					markUp.SetAttrib(_T("redv"), GetRValue(rest_color));
					markUp.SetAttrib(_T("greenv"), GetGValue(rest_color));
					markUp.SetAttrib(_T("bluev"), GetBValue(rest_color));
				}
			}
		}
		SaveXml(&markUp);
	}
}

void Timer::SaveXml(CMarkup* markup)
{
	CString strXML = markup->GetDoc();

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	JWXml::CXml saveXML;
	saveXML.LoadXml((LPCTSTR)strXML);
	saveXML.SaveWithFormatted(_T("Config\\Timer\\ColorSetting.conf"));
	saveXML.Close();
	CoUninitialize();
}
