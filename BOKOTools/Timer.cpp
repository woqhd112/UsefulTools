// Timer.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "BOKOToolsDlg.h"
#include "Timer.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#pragma comment(lib, "UxTheme.lib")

// Timer 대화 상자

IMPLEMENT_DYNAMIC(Timer, CDialogEx)

Timer::Timer(bool bUsingManual, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TIMER, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	this->bUsingManual = bUsingManual;
	std::vector<int> manualList = { IDB_PNG_BASE_CLICK_THEME_BASIC, IDB_PNG_BASE_CLICK_THEME_CLOUD, IDB_PNG_BASE_CLICK_THEME_DETECTIVE, IDB_PNG_BASE_CLICK_THEME_INK };
	usingManual = new UsingManualDialog(IDD_DIALOG_TIMER, manualList, currentTheme);
	nDivideMargin = 0;
	bDivideClick = false;
	//nBkBrightness = 0;
	efp = FOCUS_WORK_HOUR_1;
}

Timer::~Timer()
{
	PlaySound(NULL, AfxGetInstanceHandle(), NULL);
	if (tr.bThread)
	{
		tr.bThread = false;
		DWORD nExitCode = NULL;
		DWORD nExitSoundCode = NULL;
		if (tr.bSoundThread)
		{
			tr.bSoundThread = false;
			GetExitCodeThread(tr.m_soundThread->m_hThread, &nExitSoundCode);
			if (TerminateThread(tr.m_soundThread->m_hThread, nExitSoundCode) != 0)
			{
				delete tr.m_soundThread;
				tr.m_soundThread = nullptr;
			}
		}

		GetExitCodeThread(tr.m_thread->m_hThread, &nExitCode);
		if (TerminateThread(tr.m_thread->m_hThread, nExitCode) != 0)
		{
			delete tr.m_thread;
			tr.m_thread = nullptr;
		}
	}

	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
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
	DDX_Control(pDX, IDC_BUTTON_STARTANDSTOP2, m_btn_startandpause);
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
	DDX_Control(pDX, IDC_BUTTON_TIME_SAVE, m_btn_time_save);
	DDX_Control(pDX, IDC_BUTTON_TIME_LOAD, m_btn_time_load);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btn_stop);
	DDX_Control(pDX, IDC_BUTTON_SETTING_DIVIDE, m_btn_setting_divide);
	DDX_Control(pDX, IDC_STATIC_REPEAT_SETTING, m_stt_repeat_setting);
	DDX_Control(pDX, IDC_STATIC_WORK_TIME, m_stt_work_time);
	DDX_Control(pDX, IDC_STATIC_REST_TIME, m_stt_rest_time);
	DDX_Control(pDX, IDC_STATIC_TIME_SETTING, m_stt_time_setting);
	DDX_Control(pDX, IDC_STATIC_STATE, m_stt_state);
	DDX_Control(pDX, IDC_STATIC_TIME_LOAD, m_stt_time_load);
	DDX_Control(pDX, IDC_STATIC_TIME_SAVE, m_stt_time_save);
	DDX_Control(pDX, IDC_STATIC_WORK_HOUR, m_stt_work_hour);
	DDX_Control(pDX, IDC_STATIC_WORK_MINUTE, m_stt_work_minute);
	DDX_Control(pDX, IDC_STATIC_WORK_SECOND, m_stt_work_second);
	DDX_Control(pDX, IDC_STATIC_REST_HOUR, m_stt_rest_hour);
	DDX_Control(pDX, IDC_STATIC_REST_MINUTE, m_stt_rest_minute);
	DDX_Control(pDX, IDC_STATIC_REST_SECOND, m_stt_rest_second);
	DDX_Control(pDX, IDC_STATIC_REPEAT_SETTING_VIEW, m_stt_repeat_setting_view);
	DDX_Control(pDX, IDC_STATIC_WORK_TIME_VIEW, m_stt_work_time_view);
	DDX_Control(pDX, IDC_STATIC_REST_TIME_VIEW, m_stt_rest_time_view);
	DDX_Control(pDX, IDC_STATIC_TIME_SETTING_VIEW, m_stt_time_setting_view);
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
	ON_BN_CLICKED(IDC_BUTTON_TIME_LOAD, &Timer::OnBnClickedButtonTimeLoad)
	ON_BN_CLICKED(IDC_BUTTON_TIME_SAVE, &Timer::OnBnClickedButtonTimeSave)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &Timer::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SETTING_DIVIDE, &Timer::OnBnClickedButtonSettingDivide)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Timer 메시지 처리기


BOOL Timer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowTheme(m_radio_infinite, _T(""), _T(""));
	SetWindowTheme(m_radio_custom, _T(""), _T(""));

	tr.none_color = currentTheme->GetFunctionBkColor();
	tr.work_color = RGB(150, 150, 150);
	tr.rest_color = currentTheme->GetFunctionSubColor();

	radioFont.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		currentTheme->GetThemeFontName());

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_returnBrush.CreateSolidBrush(RGB(255, 255, 255));

	this->SetWindowPos(NULL, 0, 0, 410, 550, SWP_NOMOVE);
	m_stt_repeat_setting.MoveWindow(30, 10 + 5, 300, 20);
	m_stt_repeat_setting_view.MoveWindow(30, 40, 335, 85);
	m_stt_state.MoveWindow(70, 55, 50, 20);
	m_edit_state.MoveWindow(130, 50, 190, 25);
	m_radio_infinite.MoveWindow(70, 85, 100, 30);
	m_radio_custom.MoveWindow(180, 85, 100, 30);
	m_edit_custom_count.MoveWindow(270, 85, 50, 25);

	m_stt_work_time.MoveWindow(30, 125 + 5, 300, 20);
	m_stt_work_time_view.MoveWindow(30, 155, 335, 65);
	m_edit_work_hour_1.MoveWindow(50, 164, 25, 43);
	m_edit_work_hour_2.MoveWindow(75, 164, 25, 43);
	m_btn_work_hour_up.MoveWindow(100, 165, 18, 21);
	m_btn_work_hour_down.MoveWindow(100, 186, 18, 21);
	m_stt_work_hour.MoveWindow(120, 187, 30, 20);
	m_edit_work_minute_1.MoveWindow(155, 164, 25, 43);
	m_edit_work_minute_2.MoveWindow(180, 164, 25, 43);
	m_btn_work_minute_up.MoveWindow(205, 165, 18, 21);
	m_btn_work_minute_down.MoveWindow(205, 186, 18, 21);
	m_stt_work_minute.MoveWindow(225, 187, 30, 20);
	m_edit_work_second_1.MoveWindow(260, 164, 25, 43);
	m_edit_work_second_2.MoveWindow(285, 164, 25, 43);
	m_btn_work_second_up.MoveWindow(310, 165, 18, 21);
	m_btn_work_second_down.MoveWindow(310, 186, 18, 21);
	m_stt_work_second.MoveWindow(330, 187, 30, 20);

	m_stt_rest_time.MoveWindow(30, 220 + 5, 300, 20);
	m_stt_rest_time_view.MoveWindow(30, 250, 335, 65);
	m_edit_rest_hour_1.MoveWindow(50, 259, 25, 43);
	m_edit_rest_hour_2.MoveWindow(75, 259, 25, 43);
	m_btn_rest_hour_up.MoveWindow(100, 260, 18, 21);
	m_btn_rest_hour_down.MoveWindow(100, 281, 18, 21);
	m_stt_rest_hour.MoveWindow(120, 282, 30, 20);
	m_edit_rest_minute_1.MoveWindow(155, 259, 25, 43);
	m_edit_rest_minute_2.MoveWindow(180, 259, 25, 43);
	m_btn_rest_minute_up.MoveWindow(205, 260, 18, 21);
	m_btn_rest_minute_down.MoveWindow(205, 281, 18, 21);
	m_stt_rest_minute.MoveWindow(225, 282, 30, 20);
	m_edit_rest_second_1.MoveWindow(260, 259, 25, 43);
	m_edit_rest_second_2.MoveWindow(285, 259, 25, 43);
	m_btn_rest_second_up.MoveWindow(310, 260, 18, 21);
	m_btn_rest_second_down.MoveWindow(310, 281, 18, 21);
	m_stt_rest_second.MoveWindow(330, 282, 30, 20);

	m_btn_startandpause.MoveWindow(30, 330, 105, 25);
	m_btn_stop.MoveWindow(145, 330, 105, 25);
	m_btn_reset.MoveWindow(260, 330, 105, 25);
	m_btn_setting_divide.MoveWindow(0, 370, 392, 15);

	m_stt_time_setting.MoveWindow(30, 390 + 5, 300, 20);
	m_stt_time_setting_view.MoveWindow(30, 420, 335, 65);
	m_stt_time_load.MoveWindow(50, 445, 100, 30);
	m_btn_time_load.MoveWindow(150, 445, 24, 24);
	m_stt_time_save.MoveWindow(200, 445, 100, 30);
	m_btn_time_save.MoveWindow(300, 445, 24, 24);

	m_btn_startandpause.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_stop.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_reset.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_work_hour_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_hour_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_minute_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_minute_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_second_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_work_second_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_hour_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_hour_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_minute_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_minute_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_second_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_rest_second_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_setting_divide.Initialize(currentTheme->GetFunctionBkColor(), CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_radio_infinite.SetFont(&radioFont);
	m_radio_custom.SetFont(&radioFont);

	nBkBrightness = GetBrightness(GetRValue(tr.none_color), GetGValue(tr.none_color), GetBValue(tr.none_color));
	
	if (nBkBrightness > 120)
	{
		m_btn_time_save.LoadStdImage(IDB_PNG_SAVE_NOMAL, _T("PNG"));
		m_btn_time_load.LoadStdImage(IDB_PNG_LOAD_NOMAL, _T("PNG"));
		m_btn_time_save.LoadAltImage(IDB_PNG_SAVE_CLICK, _T("PNG"));
		m_btn_time_load.LoadAltImage(IDB_PNG_LOAD_CLICK, _T("PNG"));
	}
	else
	{
		m_btn_time_save.LoadStdImage(IDB_PNG_SAVE_CLICK, _T("PNG"));
		m_btn_time_load.LoadStdImage(IDB_PNG_LOAD_CLICK, _T("PNG"));
		m_btn_time_save.LoadAltImage(IDB_PNG_SAVE_NOMAL, _T("PNG"));
		m_btn_time_load.LoadAltImage(IDB_PNG_LOAD_NOMAL, _T("PNG"));
	}
	m_btn_time_save.LoadHovImage(IDB_PNG_SAVE_HOVER, _T("PNG"));
	m_btn_time_load.LoadHovImage(IDB_PNG_LOAD_HOVER, _T("PNG"));

	m_btn_startandpause.SetTextColor(currentTheme->GetTextColor());
	m_btn_stop.SetTextColor(currentTheme->GetTextColor());
	m_btn_reset.SetTextColor(currentTheme->GetTextColor());
	m_btn_work_hour_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_work_hour_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_work_minute_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_work_minute_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_work_second_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_work_second_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_rest_hour_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_rest_hour_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_rest_minute_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_rest_minute_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_rest_second_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_rest_second_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_setting_divide.SetTextColor(currentTheme->GetTextColor());

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
	m_edit_custom_count.Initialize(20, _T("고딕"));
	m_edit_state.Initialize(25, currentTheme->GetThemeFontName());

	m_stt_repeat_setting.Initialize(20, currentTheme->GetThemeFontName());
	m_stt_time_setting.Initialize(20, currentTheme->GetThemeFontName());
	m_stt_work_time.Initialize(20, currentTheme->GetThemeFontName());
	m_stt_rest_time.Initialize(20, currentTheme->GetThemeFontName());
	m_stt_state.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_work_hour.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_work_minute.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_work_second.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_rest_hour.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_rest_minute.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_rest_second.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_time_load.Initialize(18, currentTheme->GetThemeFontName());
	m_stt_time_save.Initialize(18, currentTheme->GetThemeFontName());

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
	m_edit_custom_count.LimitText(2);


	EmptyTextCondition();
	m_edit_state.SetWindowTextW(_T("None"));
	m_radio_custom.SetCheck(TRUE);
	m_btn_stop.EnableWindow(FALSE);

	m_btn_startandpause.SetFocus();

	SetDivideMargin();
	OnBnClickedButtonSettingDivide();

	int nRv = GetRValue(tr.none_color);
	int nGv = GetGValue(tr.none_color);
	int nBv = GetBValue(tr.none_color);
	m_btn_setting_divide.m_defaultColor = tr.none_color;
	m_btn_setting_divide.m_hoverColor = RGB(MinRGBColor(nRv, 20), MinRGBColor(nGv, 20), MinRGBColor(nBv, 20));
	m_btn_setting_divide.m_downColor = RGB(MinRGBColor(nRv, 70), MinRGBColor(nGv, 70), MinRGBColor(nBv, 70));

	CRect borderRect, thisRect;
	this->GetWindowRect(thisRect);
	m_stt_repeat_setting_view.GetWindowRect(borderRect);
	int nLeft = int(borderRect.left - thisRect.left - 10);
	int nTop = int(borderRect.top - thisRect.top - 35);
	drawBorderRect1 = { nLeft, nTop, nLeft + borderRect.Width(), nTop + borderRect.Height() };

	m_stt_work_time_view.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 10);
	nTop = int(borderRect.top - thisRect.top - 35);
	drawBorderRect2 = { nLeft, nTop, nLeft + borderRect.Width(), nTop + borderRect.Height() };

	m_stt_rest_time_view.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 10);
	nTop = int(borderRect.top - thisRect.top - 35);
	drawBorderRect3 = { nLeft, nTop, nLeft + borderRect.Width(), nTop + borderRect.Height() };

	m_stt_time_setting_view.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 10);
	nTop = int(borderRect.top - thisRect.top - 35);
	drawBorderRect4 = { nLeft, nTop, nLeft + borderRect.Width(), nTop + borderRect.Height() };

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL);
		usingManual->ShowWindow(SW_SHOW);
	}


	return FALSE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void Timer::SetDivideMargin()
{
	CRect divideRect, thisRect;
	m_btn_setting_divide.GetWindowRect(divideRect);
	this->GetWindowRect(thisRect);
	//nDivideMargin = thisRect.bottom - 385 - 47;
	nDivideMargin = thisRect.bottom - divideRect.bottom - 9;
}

void Timer::CreateConfigFile(CString& strFullPath)
{
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	strFullPath = (LPCTSTR)chFilePath;
	int nLen = strFullPath.ReverseFind('\\');

	if (nLen > 0)
	{
		strFullPath = strFullPath.Left(nLen);
	}

	CFileFind rootFind;
	if (rootFind.FindFile(strFullPath + _T("\\BOKOTools"))) {
		strFullPath += _T("\\BOKOTools");
	}
	rootFind.Close();

	CreateDefaultDirectory(strFullPath, _T("\\Config"));
	CreateDefaultDirectory(strFullPath, _T("\\WorkTimer"));
}

void Timer::CreateDefaultDirectory(CString& strFullPath, CString strAppendPath)
{
	CFileFind findPath;
	strFullPath += strAppendPath;
	if (!findPath.FindFile(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}
	findPath.Close();
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
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bTimer = false;
	delete this;
	CDialogEx::PostNcDestroy();
}

BOOL Timer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_edit_work_hour_1)
		{
			m_edit_work_hour_1.SetWindowTextW(_T(""));
			m_edit_work_hour_1.HideCaret();
			EmptyTextCondition(m_edit_work_hour_1.GetDlgCtrlID());
			efp = FOCUS_WORK_HOUR_1;
		}
		else if (pMsg->hwnd == m_edit_work_hour_2)
		{
			m_edit_work_hour_2.SetWindowTextW(_T(""));
			m_edit_work_hour_2.HideCaret();
			EmptyTextCondition(m_edit_work_hour_2.GetDlgCtrlID());
			efp = FOCUS_WORK_HOUR_2;
		}
		else if (pMsg->hwnd == m_edit_work_minute_1)
		{
			m_edit_work_minute_1.SetWindowTextW(_T(""));
			m_edit_work_minute_1.HideCaret();
			EmptyTextCondition(m_edit_work_minute_1.GetDlgCtrlID());
			efp = FOCUS_WORK_MINUTE_1;
		}
		else if (pMsg->hwnd == m_edit_work_minute_2)
		{
			m_edit_work_minute_2.SetWindowTextW(_T(""));
			m_edit_work_minute_2.HideCaret();
			EmptyTextCondition(m_edit_work_minute_2.GetDlgCtrlID());
			efp = FOCUS_WORK_MINUTE_2;
		}
		else if (pMsg->hwnd == m_edit_work_second_1)
		{
			m_edit_work_second_1.SetWindowTextW(_T(""));
			m_edit_work_second_1.HideCaret();
			EmptyTextCondition(m_edit_work_second_1.GetDlgCtrlID());
			efp = FOCUS_WORK_SECOND_1;
		}
		else if (pMsg->hwnd == m_edit_work_second_2)
		{
			m_edit_work_second_2.SetWindowTextW(_T(""));
			m_edit_work_second_2.HideCaret();
			EmptyTextCondition(m_edit_work_second_2.GetDlgCtrlID());
			efp = FOCUS_WORK_SECOND_2;
		}
		else if (pMsg->hwnd == m_edit_rest_hour_1)
		{
			m_edit_rest_hour_1.SetWindowTextW(_T(""));
			m_edit_rest_hour_1.HideCaret();
			EmptyTextCondition(m_edit_rest_hour_1.GetDlgCtrlID());
			efp = FOCUS_REST_HOUR_1;
		}
		else if (pMsg->hwnd == m_edit_rest_hour_2)
		{
			m_edit_rest_hour_2.SetWindowTextW(_T(""));
			m_edit_rest_hour_2.HideCaret();
			EmptyTextCondition(m_edit_rest_hour_2.GetDlgCtrlID());
			efp = FOCUS_REST_HOUR_2;
		}
		else if (pMsg->hwnd == m_edit_rest_minute_1)
		{
			m_edit_rest_minute_1.SetWindowTextW(_T(""));
			m_edit_rest_minute_1.HideCaret();
			EmptyTextCondition(m_edit_rest_minute_1.GetDlgCtrlID());
			efp = FOCUS_REST_MINUTE_1;
		}
		else if (pMsg->hwnd == m_edit_rest_minute_2)
		{
			m_edit_rest_minute_2.SetWindowTextW(_T(""));
			m_edit_rest_minute_2.HideCaret();
			EmptyTextCondition(m_edit_rest_minute_2.GetDlgCtrlID());
			efp = FOCUS_REST_MINUTE_2;
		}
		else if (pMsg->hwnd == m_edit_rest_second_1)
		{
			m_edit_rest_second_1.SetWindowTextW(_T(""));
			m_edit_rest_second_1.HideCaret();
			EmptyTextCondition(m_edit_rest_second_1.GetDlgCtrlID());
			efp = FOCUS_REST_SECOND_1;
		}
		else if (pMsg->hwnd == m_edit_rest_second_2)
		{
			m_edit_rest_second_2.SetWindowTextW(_T(""));
			m_edit_rest_second_2.HideCaret();
			EmptyTextCondition(m_edit_rest_second_2.GetDlgCtrlID());
			efp = FOCUS_REST_SECOND_2;
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

		if (pMsg->hwnd == m_edit_work_hour_1)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_hour_2)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_minute_1)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_minute_2)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_second_1)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_work_second_2)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_hour_1)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_hour_2)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_minute_1)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_minute_2)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_second_1)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_rest_second_2)
		{
			if (pMsg->wParam == L'0') { strCurrentFocusText = _T("0"); }
			else if (pMsg->wParam == L'1') { strCurrentFocusText = _T("1"); }
			else if (pMsg->wParam == L'2') { strCurrentFocusText = _T("2"); }
			else if (pMsg->wParam == L'3') { strCurrentFocusText = _T("3"); }
			else if (pMsg->wParam == L'4') { strCurrentFocusText = _T("4"); }
			else if (pMsg->wParam == L'5') { strCurrentFocusText = _T("5"); }
			else if (pMsg->wParam == L'6') { strCurrentFocusText = _T("6"); }
			else if (pMsg->wParam == L'7') { strCurrentFocusText = _T("7"); }
			else if (pMsg->wParam == L'8') { strCurrentFocusText = _T("8"); }
			else if (pMsg->wParam == L'9') { strCurrentFocusText = _T("9"); }
			else
			{
				return TRUE;
			}
		}
		else
		{
			if (pMsg->wParam == VK_ESCAPE)
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

	if (nExceptionEditCtlID != ::GetDlgCtrlID(m_edit_custom_count))
	{
		m_edit_custom_count.GetWindowTextW(strEmptyCheck);
		if (strEmptyCheck.IsEmpty())
		{
			m_edit_custom_count.SetWindowTextW(_T("1"));
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
	m_btn_stop.EnableWindow(!bEnabled);

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

bool Timer::TimeToUnderTenSecondCondition(bool isWork)
{
	bool bReturn = true;

	CString strHour, strMinute, strSecond, strHour1, strHour2, strMinute1, strMinute2, strSecond1, strSecond2;
	if (isWork)
	{
		m_edit_work_hour_1.GetWindowTextW(strHour1);
		m_edit_work_hour_2.GetWindowTextW(strHour2);
		m_edit_work_minute_1.GetWindowTextW(strMinute1);
		m_edit_work_minute_2.GetWindowTextW(strMinute2);
		m_edit_work_second_1.GetWindowTextW(strSecond1);
		m_edit_work_second_2.GetWindowTextW(strSecond2);
	}
	else
	{
		m_edit_rest_hour_1.GetWindowTextW(strHour1);
		m_edit_rest_hour_2.GetWindowTextW(strHour2);
		m_edit_rest_minute_1.GetWindowTextW(strMinute1);
		m_edit_rest_minute_2.GetWindowTextW(strMinute2);
		m_edit_rest_second_1.GetWindowTextW(strSecond1);
		m_edit_rest_second_2.GetWindowTextW(strSecond2);
	}

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
	if (tr.bStart)
	{
		if (!tr.bPause)
		{
			if (!TimeToUnderTenSecondCondition(true))
			{
				MessageBox(_T("Work Time의 최소시간은 10초 입니다."));
				return;
			}

			if (!TimeToUnderTenSecondCondition(false))
			{
				MessageBox(_T("Rest Time의 최소시간은 10초 입니다."));
				return;
			}
		}
		tr.ps = PROGRESS_STATE_NONE;
		tr.bStart = false;
		tr.bThread = true;
		m_btn_startandpause.SetWindowTextW(_T("일시 정지"));
		SetEnabledCtrl(FALSE);
		tr.m_thread = AfxBeginThread(thrTimer, this);
	}
	else
	{
		SetOperateStateToColor(OPERATE_STATE_PAUSE);
		tr.bStart = true;
		tr.bPause = true;
		tr.bThread = false;
		m_btn_startandpause.SetWindowTextW(_T("시작"));
	}
}

bool Timer::TimerThreadDelete()
{
	if (tr.bThread)
	{
		tr.bThread = false;
		DWORD nExitCode = NULL;

		GetExitCodeThread(tr.m_thread->m_hThread, &nExitCode);
		if (TerminateThread(tr.m_thread->m_hThread, nExitCode) != 0)
		{
			delete tr.m_thread;
			tr.m_thread = nullptr;
			return true;
		}
	}
	return false;
}

void Timer::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (TimerThreadDelete())
	{
		PlaySound(NULL, AfxGetInstanceHandle(), NULL);
		ResetTimerReference();
	}
}

void Timer::ResetTimerReference()
{
	tr.ps = PROGRESS_STATE_NONE;
	tr.bFirstRestClock = true;
	tr.bFirstWorkClock = false;
	tr.bConstFirstWorkClock = true;
	tr.bLastWorkClock = false;
	tr.bStart = true;
	tr.bPause = false;
	tr.bThread = false;
	tr.bWorkEnd = false;
	tr.bRestEnd = false;
	m_btn_startandpause.SetWindowTextW(_T("시작"));
	SetEnabledCtrl(TRUE);
	SetOperateStateToColor(OPERATE_STATE_NONE);
	SetDefaultGlobalEditText();
}

UINT Timer::thrTimer(LPVOID method)
{
	Timer* timer = (Timer*)method;
	timer->StartTimer();

	return 0;
}

UINT Timer::thrLoadSound(LPVOID method)
{
	Timer* timer = (Timer*)method;

	int nSoundResourceID = 0;

	switch (timer->tr.ps)
	{
	case Timer::ProgressState::PROGRESS_STATE_WORKING_START:
		nSoundResourceID = IDR_WAVE_START_WORK;
		break;
	case Timer::ProgressState::PROGRESS_STATE_WORKING_END:
		nSoundResourceID = IDR_WAVE_END_WORK;
		break;
	case Timer::ProgressState::PROGRESS_STATE_RESTING_START:
		nSoundResourceID = IDR_WAVE_START_REST;
		break;
	case Timer::ProgressState::PROGRESS_STATE_SOON_WORKING_START:
		nSoundResourceID = IDR_WAVE_SOON_START_WORK;
		break;
	case Timer::ProgressState::PROGRESS_STATE_SOON_RESTING_START:
		nSoundResourceID = IDR_WAVE_SOON_START_REST;
		break;
	case Timer::ProgressState::PROGRESS_STATE_COUNT_0:
		nSoundResourceID = 0;
		break;
	case Timer::ProgressState::PROGRESS_STATE_COUNT_1:
		nSoundResourceID = 0;
		break;
	case Timer::ProgressState::PROGRESS_STATE_COUNT_2:
		nSoundResourceID = 0;
		break;
	case Timer::ProgressState::PROGRESS_STATE_COUNT_3:
		nSoundResourceID = 0;
		break;
	case Timer::ProgressState::PROGRESS_STATE_COUNT_4:
		nSoundResourceID = 0;
		break;
	case Timer::ProgressState::PROGRESS_STATE_COUNT_5:
		nSoundResourceID = 0;
		break;
	case Timer::ProgressState::PROGRESS_STATE_WORKING_END_ALL:
		nSoundResourceID = IDR_WAVE_END_WORK_ALL;
		break;
	default : 
		break;
	}

	if (nSoundResourceID == 0)
	{
		timer->StartBeepSound(timer->tr.ps);
	}
	else
	{
		timer->StartSound(nSoundResourceID);
	}
	timer->tr.bSoundThread = false;

	return 0;
}

void Timer::StartBeepSound(ProgressState ps)
{
	if (ps == PROGRESS_STATE_COUNT_0)
	{
		Beep(1000, 1000);
	}
	else
	{
		Beep(500, 400);
	}
}

void Timer::StartSound(int nSoundResourceID)
{
	PlaySound(MAKEINTRESOURCE(nSoundResourceID), AfxGetInstanceHandle(), SND_ASYNC | SND_RESOURCE);
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

	m_edit_custom_count.GetWindowTextW(g_str_repeat_count);
}

void Timer::SetDefaultGlobalEditText()
{
	m_edit_work_hour_1.SetWindowTextW((CString)g_str_work_hour.GetAt(0));
	m_edit_work_hour_2.SetWindowTextW((CString)g_str_work_hour.GetAt(1));
	m_edit_work_minute_1.SetWindowTextW((CString)g_str_work_minute.GetAt(0));
	m_edit_work_minute_2.SetWindowTextW((CString)g_str_work_minute.GetAt(1));
	m_edit_work_second_1.SetWindowTextW((CString)g_str_work_second.GetAt(0));
	m_edit_work_second_2.SetWindowTextW((CString)g_str_work_second.GetAt(1));

	m_edit_rest_hour_1.SetWindowTextW((CString)g_str_rest_hour.GetAt(0));
	m_edit_rest_hour_2.SetWindowTextW((CString)g_str_rest_hour.GetAt(1));
	m_edit_rest_minute_1.SetWindowTextW((CString)g_str_rest_minute.GetAt(0));
	m_edit_rest_minute_2.SetWindowTextW((CString)g_str_rest_minute.GetAt(1));
	m_edit_rest_second_1.SetWindowTextW((CString)g_str_rest_second.GetAt(0));
	m_edit_rest_second_2.SetWindowTextW((CString)g_str_rest_second.GetAt(1));

	m_edit_custom_count.SetWindowTextW(g_str_repeat_count);
}

bool Timer::CheckRepeatCount(bool bCalc)
{
	CString strRepeatCount;
	m_edit_custom_count.GetWindowTextW(strRepeatCount);
	int nCount = _ttoi(strRepeatCount);
	if (bCalc) nCount--;
	if (nCount <= 0)
	{
		if (!bCalc) MessageBox(_T("반복횟수가 0입니다."));
		ResetTimerReference();
		return true;
	}
	else if (nCount == 1)
	{
		if (bCalc) tr.bLastWorkClock = true;
	}
	if (bCalc)
	{
		strRepeatCount.Format(_T("%d"), nCount);
		m_edit_custom_count.SetWindowTextW(strRepeatCount);
	}

	return false;
}

void Timer::StartTimer()
{
	EmptyTextCondition();
	if (!tr.bPause)
	{
		SetGlobalEditText();
		tr.ps = PROGRESS_STATE_COUNT_0;
		StartBeepSound(tr.ps);
	}
	while (tr.bThread)
	{
		if (CheckRepeatCount(false)) break;
		clock_t start, finish;
		double duration;

		start = clock();

		if (!tr.bWorkEnd)
		{
			CalculateWorkTime();
		}
		else
		{
			CalculateRestTime();
		}

		if (tr.bRestEnd)
		{
			tr.bWorkEnd = false;
			tr.bRestEnd = false;
			tr.bFirstRestClock = true;
			tr.bFirstWorkClock = true;

			if (m_radio_custom.GetCheck())
			{
				if (CheckRepeatCount(true))
				{
					// 마무리 멘트 알람 함수
					// func
					Sleep(1000);
					tr.ps = PROGRESS_STATE_WORKING_END_ALL;
					tr.bSoundThread = true;
					tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
					
					break;
				}
			}
		}

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep((1000 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(1000 - (duration * 1000)));
	}
}

void Timer::CalculateWorkTime()
{
	if (tr.bConstFirstWorkClock)
	{
		tr.ps = PROGRESS_STATE_SOON_WORKING_START;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
		tr.bConstFirstWorkClock = false;
	}
	if (tr.os != OPERATE_STATE_WORKING)
	{
		SetOperateStateToColor(OPERATE_STATE_WORKING);
	}
	if (tr.bFirstWorkClock)
	{
		// 일 시작 알람 함수
		// func
		tr.ps = PROGRESS_STATE_WORKING_START;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
		tr.bFirstWorkClock = false;

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
		tr.bWorkEnd = true;
		// 종료 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_0;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
		
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 1)
	{
		// 종료 1초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_1;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 2)
	{
		// 종료 2초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_2;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 3)
	{
		// 종료 3초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_3;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 4)
	{
		// 종료 4초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_4;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 5)
	{
		// 종료 5초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_5;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 7)
	{
		// 종료 7초전 알람 함수
		// func
		if (tr.bLastWorkClock)
		{
			tr.ps = PROGRESS_STATE_WORKING_END;
			tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
		}
		else
		{
			tr.ps = PROGRESS_STATE_SOON_RESTING_START;
			tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
		}
	}
	strHour.Format(_T("%02d"), nHour);
	strMinute.Format(_T("%02d"), nMinute);
	strSecond.Format(_T("%02d"), nSecond);
	if (tr.bThread)
	{
		m_edit_work_hour_1.SetWindowTextW((CString)strHour.GetAt(0));
		m_edit_work_hour_2.SetWindowTextW((CString)strHour.GetAt(1));
		m_edit_work_minute_1.SetWindowTextW((CString)strMinute.GetAt(0));
		m_edit_work_minute_2.SetWindowTextW((CString)strMinute.GetAt(1));
		m_edit_work_second_1.SetWindowTextW((CString)strSecond.GetAt(0));
		m_edit_work_second_2.SetWindowTextW((CString)strSecond.GetAt(1));
	}
}

void Timer::CalculateRestTime()
{
	if (tr.bLastWorkClock)
	{
		tr.bRestEnd = true;
		tr.bLastWorkClock = false;
		return;
	}
	if (tr.os != OPERATE_STATE_RESTING)
	{
		SetOperateStateToColor(OPERATE_STATE_RESTING);
	}
	if (tr.bFirstRestClock)
	{
		// 휴식 시작 알람 함수
		// func
		tr.ps = PROGRESS_STATE_RESTING_START;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
		tr.bFirstRestClock = false;

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
		tr.bRestEnd = true;
		// 종료 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_0;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 1)
	{
		// 종료 1초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_1;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 2)
	{
		// 종료 2초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_2;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 3)
	{
		// 종료 3초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_3;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 4)
	{
		// 종료 4초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_4;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 5)
	{
		// 종료 5초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_COUNT_5;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	else if (nHour == 0 && nMinute == 0 && nSecond == 7)
	{
		// 종료 7초전 알람 함수
		// func
		tr.ps = PROGRESS_STATE_SOON_WORKING_START;
		tr.m_soundThread = AfxBeginThread(thrLoadSound, this);
	}
	strHour.Format(_T("%02d"), nHour);
	strMinute.Format(_T("%02d"), nMinute);
	strSecond.Format(_T("%02d"), nSecond);
	if (tr.bThread)
	{
		m_edit_rest_hour_1.SetWindowTextW((CString)strHour.GetAt(0));
		m_edit_rest_hour_2.SetWindowTextW((CString)strHour.GetAt(1));
		m_edit_rest_minute_1.SetWindowTextW((CString)strMinute.GetAt(0));
		m_edit_rest_minute_2.SetWindowTextW((CString)strMinute.GetAt(1));
		m_edit_rest_second_1.SetWindowTextW((CString)strSecond.GetAt(0));
		m_edit_rest_second_2.SetWindowTextW((CString)strSecond.GetAt(1));
	}
}

void Timer::SetOperateStateToColor(OperateState os)
{
	this->tr.os = os;
	if (os == OPERATE_STATE_NONE)
	{
		SetOperateColor(tr.none_color, _T("None"));
	}
	else if (os == OPERATE_STATE_RESTING)
	{
		SetOperateColor(tr.rest_color, _T("Resting"));
	}
	else if (os == OPERATE_STATE_WORKING)
	{
		SetOperateColor(tr.work_color, _T("Working"));
	}
	else if (os == OPERATE_STATE_PAUSE)
	{
		OnCtlColor(m_edit_state.GetWindowDC(), &m_edit_state, CTLCOLOR_STATIC);
		m_edit_state.SetWindowTextW(_T("Pause"));
	}
}

void Timer::SetOperateColor(COLORREF color, CString strOperateState)
{
	int nRv = GetRValue(color);
	int nGv = GetGValue(color);
	int nBv = GetBValue(color);
	nBkBrightness = GetBrightness(nRv, nGv, nBv);
	OnCtlColor(m_edit_state.GetWindowDC(), &m_edit_state, CTLCOLOR_STATIC);
	m_edit_state.SetWindowTextW(strOperateState);
	m_btn_time_save.DisConnect();
	m_btn_time_load.DisConnect();
	this->SetBackgroundColor(color);
	m_btn_setting_divide.SetFaceColor(color);
	m_btn_setting_divide.m_defaultColor = color;
	m_btn_setting_divide.m_hoverColor = RGB(MinRGBColor(nRv, 20), MinRGBColor(nGv, 20), MinRGBColor(nBv, 20));
	m_btn_setting_divide.m_downColor = RGB(MinRGBColor(nRv, 70), MinRGBColor(nGv, 70), MinRGBColor(nBv, 70));
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
	m_edit_custom_count.SetWindowTextW(_T("1"));
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
			if (tr.os == OPERATE_STATE_NONE)
			{
				pDC->SetTextColor(tr.none_color);
				pDC->SetBkColor(RGB(255, 255, 255));
				hbr = (HBRUSH)m_returnBrush;
			}
			else if (tr.os == OPERATE_STATE_RESTING)
			{
				pDC->SetTextColor(tr.rest_color);
				pDC->SetBkColor(RGB(255, 255, 255));
				hbr = (HBRUSH)m_returnBrush;
			}
			else if (tr.os == OPERATE_STATE_WORKING)
			{
				pDC->SetTextColor(tr.work_color);
				pDC->SetBkColor(RGB(255, 255, 255));
				hbr = (HBRUSH)m_returnBrush;
			}
			else if (tr.os == OPERATE_STATE_PAUSE)
			{
				pDC->SetTextColor(RGB(200, 200, 200));
				hbr = (HBRUSH)m_returnBrush;
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_STATE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME_LOAD)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME_SAVE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_WORK_HOUR)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_WORK_MINUTE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_WORK_SECOND)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_REST_SECOND)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_REST_HOUR)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_REST_MINUTE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_REPEAT_SETTING)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_WORK_TIME)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_REST_TIME)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME_SETTING)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_REST_MINUTE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_RADIO_INFINITE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
			return (HBRUSH)GetStockObject(NULL_BRUSH);
		}
		else if (pWnd->GetDlgCtrlID() == IDC_RADIO_CUSTOM)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
			return (HBRUSH)GetStockObject(NULL_BRUSH);
		}
	}
	else
	{
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void Timer::SaveXml(CMarkup* markup, CString strSaveFullPath)
{
	CString strXML = markup->GetDoc();

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	JWXml::CXml saveXML;
	saveXML.LoadXml((LPCTSTR)strXML);
	saveXML.SaveWithFormatted(strSaveFullPath);
	saveXML.Close();
	CoUninitialize();
}


void Timer::OnBnClickedButtonTimeLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (tr.bThread)
	{
		MessageBox(_T("타이머 작동중엔 기능이 제한됩니다."));
		return;
	}
	CString szRoot = _T("");
	CreateConfigFile(szRoot);

	CString szFilter = _T("Config File(*.conf)|*.conf||");
	CFileDialog dlg(TRUE, L"*.conf", szRoot + _T("\\"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (IDOK == dlg.DoModal())
	{
		CString strFullPath = dlg.GetPathName();
		CMarkup markUp;
		if (markUp.Load(strFullPath))
		{
			markUp.FindElem(_T("Timer"));
			markUp.IntoElem();
			while (markUp.FindElem(_T("Time")))
			{
				CString strTimeState = markUp.GetAttrib(_T("name"));

				if (strTimeState == _T("work"))
				{
					CString strHour = markUp.GetAttrib(_T("hour"));
					CString strMinute = markUp.GetAttrib(_T("minute"));
					CString strSecond = markUp.GetAttrib(_T("second"));
					m_edit_work_hour_1.SetWindowTextW((CString)strHour.GetAt(0));
					m_edit_work_hour_2.SetWindowTextW((CString)strHour.GetAt(1));
					m_edit_work_minute_1.SetWindowTextW((CString)strMinute.GetAt(0));
					m_edit_work_minute_2.SetWindowTextW((CString)strMinute.GetAt(1));
					m_edit_work_second_1.SetWindowTextW((CString)strSecond.GetAt(0));
					m_edit_work_second_2.SetWindowTextW((CString)strSecond.GetAt(1));
				}
				else if (strTimeState == _T("rest"))
				{
					CString strHour = markUp.GetAttrib(_T("hour"));
					CString strMinute = markUp.GetAttrib(_T("minute"));
					CString strSecond = markUp.GetAttrib(_T("second"));
					m_edit_rest_hour_1.SetWindowTextW((CString)strHour.GetAt(0));
					m_edit_rest_hour_2.SetWindowTextW((CString)strHour.GetAt(1));
					m_edit_rest_minute_1.SetWindowTextW((CString)strMinute.GetAt(0));
					m_edit_rest_minute_2.SetWindowTextW((CString)strMinute.GetAt(1));
					m_edit_rest_second_1.SetWindowTextW((CString)strSecond.GetAt(0));
					m_edit_rest_second_2.SetWindowTextW((CString)strSecond.GetAt(1));
				}
				else
				{
					CString strRepeatValue = markUp.GetAttrib(_T("value"));
					CString strRepeatType = markUp.GetAttrib(_T("type"));
					if (strRepeatType == _T("infinite"))
					{
						m_radio_infinite.SetCheck(TRUE);
						m_radio_custom.SetCheck(FALSE);
						m_edit_custom_count.EnableWindow(FALSE);
					}
					else
					{
						m_radio_custom.SetCheck(TRUE);
						m_radio_infinite.SetCheck(FALSE);
						m_edit_custom_count.EnableWindow(TRUE);
					}
					m_edit_custom_count.SetWindowTextW(strRepeatValue);
				}
			}
		}
	}
}


void Timer::OnBnClickedButtonTimeSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (tr.bThread)
	{
		MessageBox(_T("타이머 작동중엔 기능이 제한됩니다."));
		return;
	}
	CString szRoot = _T("");
	CreateConfigFile(szRoot);

	CString szFilter = _T("Config File(*.conf)|*.conf||");
	CFileDialog dlg(FALSE, L"*.conf", szRoot + _T("\\"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (IDOK == dlg.DoModal())
	{
		EmptyTextCondition();
		CMarkup markUp;
		CString strFullPath = dlg.GetPathName();

		CString strWorkHour1, strWorkHour2, strWorkMinute1, strWorkMinute2, strWorkSecond1, strWorkSecond2;
		CString strRestHour1, strRestHour2, strRestMinute1, strRestMinute2, strRestSecond1, strRestSecond2;
		CString strRepeatCount, strRepeatType;

		m_edit_work_hour_1.GetWindowTextW(strWorkHour1);
		m_edit_work_hour_2.GetWindowTextW(strWorkHour2);
		m_edit_work_minute_1.GetWindowTextW(strWorkMinute1);
		m_edit_work_minute_2.GetWindowTextW(strWorkMinute2);
		m_edit_work_second_1.GetWindowTextW(strWorkSecond1);
		m_edit_work_second_2.GetWindowTextW(strWorkSecond2);

		m_edit_rest_hour_1.GetWindowTextW(strRestHour1);
		m_edit_rest_hour_2.GetWindowTextW(strRestHour2);
		m_edit_rest_minute_1.GetWindowTextW(strRestMinute1);
		m_edit_rest_minute_2.GetWindowTextW(strRestMinute2);
		m_edit_rest_second_1.GetWindowTextW(strRestSecond1);
		m_edit_rest_second_2.GetWindowTextW(strRestSecond2);

		m_edit_custom_count.GetWindowTextW(strRepeatCount);

		markUp.AddElem(_T("Timer"));
		markUp.IntoElem();
		markUp.AddElem(_T("Time"));
		markUp.AddAttrib(_T("name"), _T("work"));
		markUp.AddAttrib(_T("hour"), strWorkHour1 + strWorkHour2);
		markUp.AddAttrib(_T("minute"), strWorkMinute1 + strWorkMinute2);
		markUp.AddAttrib(_T("second"), strWorkSecond1 + strWorkSecond2);
		markUp.AddElem(_T("Time"));
		markUp.AddAttrib(_T("name"), _T("rest"));
		markUp.AddAttrib(_T("hour"), strRestHour1 + strRestHour2);
		markUp.AddAttrib(_T("minute"), strRestMinute1 + strRestMinute2);
		markUp.AddAttrib(_T("second"), strRestSecond1 + strRestSecond2);
		markUp.AddElem(_T("Time"));
		markUp.AddAttrib(_T("name"), _T("repeat"));
		markUp.AddAttrib(_T("type"), m_radio_infinite.GetCheck() ? _T("infinite") : _T("custom"));
		markUp.AddAttrib(_T("value"), strRepeatCount);
		SaveXml(&markUp, strFullPath);
	}
}

void Timer::OnBnClickedButtonSettingDivide()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRect divideRect, thisRect;
	m_btn_setting_divide.GetWindowRect(divideRect);
	this->GetWindowRect(thisRect);

	if (!bDivideClick)
	{
		m_btn_setting_divide.SetWindowTextW(_T("▼▼"));
		this->MoveWindow(thisRect.left, thisRect.top, thisRect.Width(), thisRect.Height() - nDivideMargin);
		bDivideClick = true;
	}
	else
	{
		m_btn_setting_divide.SetWindowTextW(_T("▲▲"));
		this->MoveWindow(thisRect.left, thisRect.top, thisRect.Width(), thisRect.Height() + nDivideMargin);
		bDivideClick = false;
	}
}

void Timer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(drawBorderRect1, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
	dc.Draw3dRect(drawBorderRect2, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
	dc.Draw3dRect(drawBorderRect3, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
	dc.Draw3dRect(drawBorderRect4, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
}
