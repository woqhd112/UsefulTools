// BaseTimer.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "BaseTimer.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"


// BaseTimer 대화 상자

IMPLEMENT_DYNAMIC(BaseTimer, CDialogEx)

BaseTimer::BaseTimer(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BASE_TIMER, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	bStart = true;
	bThread = false;
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
		GetExitCodeThread(m_soundThread->m_hThread, &nExitSoundCode);
		if (TerminateThread(m_soundThread->m_hThread, nExitSoundCode) != 0)
		{
			delete m_soundThread;
			m_soundThread = nullptr;
		}

		GetExitCodeThread(m_thread->m_hThread, &nExitCode);
		if (TerminateThread(m_thread->m_hThread, nExitCode) != 0)
		{
			delete m_thread;
			m_thread = nullptr;
		}
	}
}

void BaseTimer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_STARTANDSTOP, m_btn_startandstop);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_RESET, m_btn_reset);
	DDX_Control(pDX, IDC_STATIC_BASE_TIMER_MS, m_stt_ms);
	DDX_Control(pDX, IDC_STATIC_BASE_TIMER_VIEW, m_stt_basetimer_view);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_M_UP, m_btn_m_up);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_M_DOWN, m_btn_m_down);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_S_UP, m_btn_s_up);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_S_DOWM, m_btn_s_down);
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
END_MESSAGE_MAP()


// BaseTimer 메시지 처리기


BOOL BaseTimer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	m_btn_startandstop.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_reset.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_m_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_m_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_s_up.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_s_down.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_startandstop.SetTextColor(currentTheme->GetTextColor());
	m_btn_reset.SetTextColor(currentTheme->GetTextColor());
	m_btn_m_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_m_down.SetTextColor(currentTheme->GetTextColor());
	m_btn_s_up.SetTextColor(currentTheme->GetTextColor());
	m_btn_s_down.SetTextColor(currentTheme->GetTextColor());

	m_stt_ms.Initialize(50, _T("DS-Digital"));

	m_stt_basetimer_view.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_ms.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_ms.BringWindowToTop();

	return TRUE;  // return TRUE unless you set the focus to a control
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
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE_TIMER_MS)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
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
	basetimer->StartSound(_T("SoundTrack\\BaseTimer\\Alarm.wav"));

	return 0;
}

void BaseTimer::StartSound(CString strSoundPath)
{
	PlaySound(strSoundPath, AfxGetInstanceHandle(), SND_ASYNC);
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
}

void BaseTimer::StartBaseTimer()
{
	while (bThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();

		CString strMS, strM, strS;
		m_stt_ms.GetWindowTextW(strMS);
		AfxExtractSubString(strM, strMS, 0, ':');
		AfxExtractSubString(strS, strMS, 1, ':');
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
			m_soundThread = AfxBeginThread(thrLoadSound, this);
			m_stt_ms.SetWindowTextW(_T("00:00"));
			ResetDefaultValue();
			break;
		}

		strMS.Format(_T("%02d:%02d"), m, s);
		m_stt_ms.SetWindowTextW(strMS);

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep((1000 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(1000 - (duration * 1000)));
	}
}

bool BaseTimer::DeleteMainThread()
{
	if (bThread)
	{
		bThread = false;
		DWORD nExitCode = NULL;

		GetExitCodeThread(m_thread->m_hThread, &nExitCode);
		if (TerminateThread(m_thread->m_hThread, nExitCode) != 0)
		{
			delete m_thread;
			m_thread = nullptr;
			return true;
		}
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
	m_stt_ms.SetWindowTextW(_T("00:00"));
}

void BaseTimer::MinuteUp()
{
	CString strMS, strM, strS;
	m_stt_ms.GetWindowTextW(strMS);
	AfxExtractSubString(strM, strMS, 0, ':');
	AfxExtractSubString(strS, strMS, 1, ':');
	int nMinute = _ttoi(strM);

	if (nMinute >= 99) return;

	nMinute++;
	CString strFormat;
	strFormat.Format(_T("%02d:%s"), nMinute, strS);
	m_stt_ms.SetWindowTextW(strFormat);
}

void BaseTimer::MinuteDown()
{
	CString strMS, strM, strS;
	m_stt_ms.GetWindowTextW(strMS);
	AfxExtractSubString(strM, strMS, 0, ':');
	AfxExtractSubString(strS, strMS, 1, ':');
	int nMinute = _ttoi(strM);

	if (nMinute <= 0) return;

	nMinute--;
	CString strFormat;
	strFormat.Format(_T("%02d:%s"), nMinute, strS);
	m_stt_ms.SetWindowTextW(strFormat);
}

void BaseTimer::SecondUp()
{
	CString strMS, strM, strS;
	m_stt_ms.GetWindowTextW(strMS);
	AfxExtractSubString(strM, strMS, 0, ':');
	AfxExtractSubString(strS, strMS, 1, ':');
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
	strFormat.Format(_T("%02d:%02d"), nMinute, nSecond);
	m_stt_ms.SetWindowTextW(strFormat);
}

void BaseTimer::SecondDown()
{
	CString strMS, strM, strS;
	m_stt_ms.GetWindowTextW(strMS);
	AfxExtractSubString(strM, strMS, 0, ':');
	AfxExtractSubString(strS, strMS, 1, ':');
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
	strFormat.Format(_T("%02d:%02d"), nMinute, nSecond);
	m_stt_ms.SetWindowTextW(strFormat);
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

