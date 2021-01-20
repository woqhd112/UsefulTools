// BaseTimer.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "BaseTimer.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// BaseTimer 대화 상자

IMPLEMENT_DYNAMIC(BaseTimer, CDialogEx)

BaseTimer::BaseTimer(bool bUsingManual, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BASE_TIMER, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	this->bUsingManual = bUsingManual;
	std::vector<int> manualList = { IDB_PNG_BASE_CLICK_THEME_BASIC, IDB_PNG_BASE_CLICK_THEME_CLOUD, IDB_PNG_BASE_CLICK_THEME_DETECTIVE, IDB_PNG_BASE_CLICK_THEME_INK };
	usingManual = new UsingManualDialog(manualList, currentTheme, this);
	bStart = true;
	bThread = false;
	bSoundThread = false;
	bMaintainThread = false;
	nMaintainCount = 0;
	bs = SIGNAL_NONE;
}

BaseTimer::~BaseTimer()
{
	PlaySound(NULL, AfxGetInstanceHandle(), NULL);
	if (bThread)
	{
		bThread = false;
		DWORD nExitCode = NULL;
		DWORD nExitSoundCode = NULL;
		if (bSoundThread)
		{
			bSoundThread = false;
			GetExitCodeThread(m_soundThread->m_hThread, &nExitSoundCode);
			if (TerminateThread(m_soundThread->m_hThread, nExitSoundCode) != 0)
			{
				delete m_soundThread;
				m_soundThread = nullptr;
			}
		}

		GetExitCodeThread(m_thread->m_hThread, &nExitCode);
		if (TerminateThread(m_thread->m_hThread, nExitCode) != 0)
		{
			delete m_thread;
			m_thread = nullptr;
		}
	}

	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
	}
}

void BaseTimer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_STARTANDSTOP, m_btn_startandstop);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_RESET, m_btn_reset);
	DDX_Control(pDX, IDC_STATIC_BASE_TIMER_VIEW, m_stt_basetimer_view);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_M_UP, m_btn_m_up);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_M_DOWN, m_btn_m_down);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_S_UP, m_btn_s_up);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_S_DOWM, m_btn_s_down);
	DDX_Control(pDX, IDC_EDIT_BASETIMER_M, m_edit_basetimer_m);
	DDX_Control(pDX, IDC_EDIT_BASETIMER_S, m_edit_basetimer_s);
	DDX_Control(pDX, IDC_STATIC_BASETIMER_COLON, m_stt_basetimer_colon);
}


BEGIN_MESSAGE_MAP(BaseTimer, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_STARTANDSTOP, &BaseTimer::OnBnClickedButtonBaseTimerStartandstop)
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_RESET, &BaseTimer::OnBnClickedButtonBaseTimerReset)
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_M_UP, &BaseTimer::OnBnClickedButtonBaseTimerMUp)
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_M_DOWN, &BaseTimer::OnBnClickedButtonBaseTimerMDown)
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_S_UP, &BaseTimer::OnBnClickedButtonBaseTimerSUp)
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_S_DOWM, &BaseTimer::OnBnClickedButtonBaseTimerSDowm)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// BaseTimer 메시지 처리기


BOOL BaseTimer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	this->SetWindowPos(NULL, 0, 0, 320, 210, SWP_NOMOVE);

	m_stt_basetimer_view.MoveWindow(50, 20, 200, 90);
	drawBorderRect = { 49, 19, 202 + 49, 92 + 19 };

	m_edit_basetimer_m.MoveWindow(55, 25, 80, 80);
	m_stt_basetimer_colon.MoveWindow(140, 25, 20, 80);
	m_edit_basetimer_s.MoveWindow(165, 25, 80, 80);

	m_btn_m_up.MoveWindow(10, 30, 30, 30);
	m_btn_m_down.MoveWindow(10, 70, 30, 30);
	m_btn_s_up.MoveWindow(260, 30, 30, 30);
	m_btn_s_down.MoveWindow(260, 70, 30, 30);

	m_btn_startandstop.MoveWindow(50 ,120, 95, 30);
	m_btn_reset.MoveWindow(155, 120, 95, 30);

	m_btn_startandstop.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	m_btn_reset.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	m_btn_m_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_m_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_s_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_s_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_startandstop.SetTextColor(currentTheme->GetTextColor());
	m_btn_reset.SetTextColor(currentTheme->GetTextColor());
	m_btn_m_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_m_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_s_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_s_down.SetTextColor(currentTheme->GetTextColor());

	m_edit_basetimer_m.Initialize(55, _T("DS-Digital"));
	m_edit_basetimer_s.Initialize(55, _T("DS-Digital"));

	m_stt_basetimer_colon.Initialize(55, _T("DS-Digital"));

	m_stt_basetimer_view.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_basetimer_colon.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_basetimer_m.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_basetimer_s.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_basetimer_colon.BringWindowToTop();
	m_edit_basetimer_m.BringWindowToTop();
	m_edit_basetimer_s.BringWindowToTop();


	m_edit_basetimer_m.SetWindowTextW(_T("00"));
	m_edit_basetimer_s.SetWindowTextW(_T("00"));
	m_btn_startandstop.SetFocus();

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL, this);
		usingManual->ShowWindow(SW_SHOW);
	}

	return FALSE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void BaseTimer::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void BaseTimer::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	BaseTimer::PostNcDestroy();
}


void BaseTimer::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bBaseTimer = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL BaseTimer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == m_btn_m_up.m_hWnd)
		{
			bMaintainThread = true;
			bs = SIGNAL_MINUTE_UP;
			m_maintainThread = AfxBeginThread(thrClickMaintain, this);
		}
		else if (pMsg->hwnd == m_btn_m_down.m_hWnd)
		{
			bMaintainThread = true;
			bs = SIGNAL_MINUTE_DOWN;
			m_maintainThread = AfxBeginThread(thrClickMaintain, this);
		}
		else if (pMsg->hwnd == m_btn_s_up.m_hWnd)
		{
			bMaintainThread = true;
			bs = SIGNAL_SECOND_UP;
			m_maintainThread = AfxBeginThread(thrClickMaintain, this);
		}
		else if (pMsg->hwnd == m_btn_s_down.m_hWnd)
		{
			bMaintainThread = true;
			bs = SIGNAL_SECOND_DOWN;
			m_maintainThread = AfxBeginThread(thrClickMaintain, this);
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_btn_m_up.m_hWnd)
		{
			bMaintainThread = false;
			bs = SIGNAL_NONE;
		}
		else if (pMsg->hwnd == m_btn_m_down.m_hWnd)
		{
			bMaintainThread = false;
			bs = SIGNAL_NONE;
		}
		else if (pMsg->hwnd == m_btn_s_up.m_hWnd)
		{
			bMaintainThread = false;
			bs = SIGNAL_NONE;
		}
		else if (pMsg->hwnd == m_btn_s_down.m_hWnd)
		{
			bMaintainThread = false;
			bs = SIGNAL_NONE;
		}
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (pMsg->hwnd == m_edit_basetimer_m.m_hWnd)
			{
				m_edit_basetimer_m.HideCaret();
			}
			else if (pMsg->hwnd == m_edit_basetimer_s.m_hWnd)
			{
				m_edit_basetimer_s.HideCaret();
			}
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH BaseTimer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE_TIMER_VIEW)
		{
			CRect rect;
			GetClientRect(&rect);

			CDC* pDC = m_stt_basetimer_view.GetWindowDC();
			CBrush *pOld = pDC->SelectObject(&m_backBrush);
			pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
			pDC->SelectObject(pOld);
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASETIMER_COLON)
		{
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_BASETIMER_M)
		{
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_BASETIMER_S)
		{
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_BASETIMER_M)
		{
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_BASETIMER_S)
		{
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else
	{
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void BaseTimer::OnBnClickedButtonBaseTimerStartandstop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (bStart)
	{
		bStart = false;
		bThread = true;
		m_btn_startandstop.SetWindowTextW(_T("정지"));
		m_btn_reset.EnableWindow(FALSE);
		m_btn_m_up.EnableWindow(FALSE);
		m_btn_m_down.EnableWindow(FALSE);
		m_btn_s_up.EnableWindow(FALSE);
		m_btn_s_down.EnableWindow(FALSE);
		m_edit_basetimer_m.EnableWindow(FALSE);
		m_edit_basetimer_s.EnableWindow(FALSE);
		m_thread = AfxBeginThread(thrBaseTimer, this);
	}
	else
	{
		ResetDefaultValue();
		DeleteMainThread();
	}
}

UINT BaseTimer::thrBaseTimer(LPVOID method)
{
	BaseTimer* basetimer = (BaseTimer*)method;
	basetimer->StartBaseTimer();

	return 0;
}

UINT BaseTimer::thrLoadSound(LPVOID method)
{
	BaseTimer* basetimer = (BaseTimer*)method;
	basetimer->StartSound(IDR_WAVE_ALARM);

	return 0;
}

void BaseTimer::StartSound(int nSoundResourceID)
{
	PlaySound(MAKEINTRESOURCE(nSoundResourceID), AfxGetInstanceHandle(), SND_ASYNC | SND_RESOURCE);
	bSoundThread = false;
}

void BaseTimer::ResetDefaultValue()
{
	bStart = true;
	bThread = false;
	m_btn_startandstop.SetWindowTextW(_T("시작"));
	m_btn_reset.EnableWindow(TRUE);
	m_btn_m_up.EnableWindow(TRUE);
	m_btn_m_down.EnableWindow(TRUE);
	m_btn_s_up.EnableWindow(TRUE);
	m_btn_s_down.EnableWindow(TRUE);
	m_edit_basetimer_m.EnableWindow(TRUE);
	m_edit_basetimer_s.EnableWindow(TRUE);
}

void BaseTimer::StartBaseTimer()
{
	while (bThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();

		CString strM, strS;
		m_edit_basetimer_m.GetWindowTextW(strM);
		m_edit_basetimer_s.GetWindowTextW(strS);
		int m = _ttoi(strM);
		int s = _ttoi(strS);

		if (m <= 0 && s <= 0)
		{
			ResetDefaultValue();
			break;
		}
		else if (m > 0 && s <= 0)
		{
			m--;
			s = 59;
		}
		else if (s > 0)
		{
			s--;
		}

		if (m <= 0 && s <= 0)
		{
			// 종료 소리 실행 함수
			// func
			bSoundThread = true;
			m_edit_basetimer_m.SetWindowTextW(_T("00"));
			m_edit_basetimer_s.SetWindowTextW(_T("00"));
			for (int i = 0; i < 20; i++)
			{
				m_soundThread = AfxBeginThread(thrLoadSound, this);
				Sleep(6000);
			}
			ResetDefaultValue();
			break;
		}

		strM.Format(_T("%02d"), m);
		strS.Format(_T("%02d"), s);
		m_edit_basetimer_m.SetWindowTextW(strM);
		m_edit_basetimer_s.SetWindowTextW(strS);

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep((1000 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(1000 - (duration * 1000)));
	}
}

bool BaseTimer::DeleteMainThread()
{
	PlaySound(NULL, AfxGetInstanceHandle(), NULL);
	DWORD nExitCode = NULL;

	GetExitCodeThread(m_thread->m_hThread, &nExitCode);
	if (TerminateThread(m_thread->m_hThread, nExitCode) != 0)
	{
		delete m_thread;
		m_thread = nullptr;
		return true;
	}
	return false;
}

UINT BaseTimer::thrClickMaintain(LPVOID method)
{
	BaseTimer* basetimer = (BaseTimer*)method;
	basetimer->StartMaintainCount();

	return 0;
}

void BaseTimer::StartMaintainCount()
{
	int nCountPerSecond = 0;
	int nMaintainTime = 500;
	while (bMaintainThread)
	{
		switch (bs)
		{
		case SIGNAL_MINUTE_UP:
			MinuteUp();
			break;
		case SIGNAL_MINUTE_DOWN:
			MinuteDown();
			break;
		case SIGNAL_SECOND_UP:
			SecondUp();
			break;
		case SIGNAL_SECOND_DOWN:
			SecondDown();
			break;
		default:
			break;
		}

		Sleep(nMaintainTime);

		nMaintainCount++;
		nCountPerSecond++;
		if (nCountPerSecond == 6)
		{
			nMaintainTime = 250;
		}
		else if (nCountPerSecond == 18)
		{
			nMaintainTime = 125;
		}
	}
}

void BaseTimer::OnBnClickedButtonBaseTimerReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_basetimer_m.SetWindowTextW(_T("00"));
	m_edit_basetimer_s.SetWindowTextW(_T("00"));
}

void BaseTimer::MinuteUp()
{
	CString strM, strS;
	m_edit_basetimer_m.GetWindowTextW(strM);
	m_edit_basetimer_s.GetWindowTextW(strS);
	int nMinute = _ttoi(strM);

	if (nMinute >= 99) return;

	nMinute++;
	CString strFormat;
	strFormat.Format(_T("%02d"), nMinute);
	m_edit_basetimer_m.SetWindowTextW(strFormat);
	m_edit_basetimer_s.SetWindowTextW(strS);
}

void BaseTimer::MinuteDown()
{
	CString strM, strS;
	m_edit_basetimer_m.GetWindowTextW(strM);
	m_edit_basetimer_s.GetWindowTextW(strS);
	int nMinute = _ttoi(strM);

	if (nMinute <= 0) return;

	nMinute--;
	CString strFormat;
	strFormat.Format(_T("%02d"), nMinute);
	m_edit_basetimer_m.SetWindowTextW(strFormat);
	m_edit_basetimer_s.SetWindowTextW(strS);
}

void BaseTimer::SecondUp()
{
	CString strM, strS;
	m_edit_basetimer_m.GetWindowTextW(strM);
	m_edit_basetimer_s.GetWindowTextW(strS);
	int nMinute = _ttoi(strM);
	int nSecond = _ttoi(strS);

	if (nMinute >= 99 && nSecond >= 59)
	{
		return;
	}
	else if (nMinute < 99 && nSecond >= 59)
	{
		nMinute++;
		nSecond = 0;
	}
	else if (nSecond < 59)
	{
		nSecond++;
	}

	CString strFormat;
	strFormat.Format(_T("%02d"), nMinute);
	m_edit_basetimer_m.SetWindowTextW(strFormat);
	strFormat.Format(_T("%02d"), nSecond);
	m_edit_basetimer_s.SetWindowTextW(strFormat);
}

void BaseTimer::SecondDown()
{
	CString strM, strS;
	m_edit_basetimer_m.GetWindowTextW(strM);
	m_edit_basetimer_s.GetWindowTextW(strS);
	int nMinute = _ttoi(strM);
	int nSecond = _ttoi(strS);

	if (nMinute <= 0 && nSecond <= 0)
	{
		return;
	}
	else if (nMinute > 0 && nSecond <= 0)
	{
		nMinute--;
		nSecond = 59;
	}
	else if (nSecond > 0)
	{
		nSecond--;
	}

	CString strFormat;
	strFormat.Format(_T("%02d"), nMinute);
	m_edit_basetimer_m.SetWindowTextW(strFormat);
	strFormat.Format(_T("%02d"), nSecond);
	m_edit_basetimer_s.SetWindowTextW(strFormat);
}

void BaseTimer::OnBnClickedButtonBaseTimerMUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	nMaintainCount = 0;
}


void BaseTimer::OnBnClickedButtonBaseTimerMDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	nMaintainCount = 0;
}


void BaseTimer::OnBnClickedButtonBaseTimerSUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	nMaintainCount = 0;
}


void BaseTimer::OnBnClickedButtonBaseTimerSDowm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	nMaintainCount = 0;
}

void BaseTimer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(drawBorderRect, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());

	CBrush *pOld = dc.SelectObject(&m_backBrush);
	dc.PatBlt(drawBorderRect.left + 1, drawBorderRect.top + 1, drawBorderRect.Width() - 2, drawBorderRect.Height() - 2, PATCOPY);
	dc.SelectObject(pOld);
}
