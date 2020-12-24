// Timer.cpp: 구현 파일
//

#include "pch.h"
#include "GoCabinet.h"
#include "StopWatch.h"
#include "GoCabinetDlg.h"
#include "afxdialogex.h"


// Timer 대화 상자

IMPLEMENT_DYNAMIC(StopWatch, CDialogEx)

StopWatch::StopWatch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STOPWATCH, pParent)
{
	this->pParent = pParent;
	bStart = true;
	bLaptime = false;
	bThread = false;
}

StopWatch::~StopWatch()
{
	if (bThread)
	{
		bThread = false;
		DWORD nExitCode = NULL;
		GetExitCodeThread(m_thread->m_hThread, &nExitCode);
		if (TerminateThread(m_thread, nExitCode) != 0)
		{
			delete m_thread;
			m_thread = nullptr;
		}
	}

	if (laptime)
	{
		laptime.DestroyWindow();
	}
}

void StopWatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIMER_VIEW, m_stt_stopwatch_view);
	DDX_Control(pDX, IDC_STATIC_HMS, m_stt_hms);
	DDX_Control(pDX, IDC_BUTTON_STARTANDSTOP, m_btn_startandstop);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_btn_reset);
	DDX_Control(pDX, IDC_BUTTON_LAPTIME, m_btn_laptime);
	DDX_Control(pDX, IDC_BUTTON_LAPTIME_RESET, m_btn_laptime_reset);
}


BEGIN_MESSAGE_MAP(StopWatch, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_STARTANDSTOP, &StopWatch::OnBnClickedButtonStartandstop)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &StopWatch::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_LAPTIME, &StopWatch::OnBnClickedButtonLaptime)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_LAPTIME_RESET, &StopWatch::OnBnClickedButtonLaptimeReset)
END_MESSAGE_MAP()


// Timer 메시지 처리기

BOOL StopWatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(RGB(255, 255, 255));
	m_backBrush.CreateSolidBrush(RGB(50, 50, 50));

	GetWindowRect(&thisRect);

	laptime.Create(IDD_DIALOG_LAPTIME, this);
	laptime.GetWindowRect(&childRect);
	laptime.MoveWindow(15, thisRect.Height() - 30, int(thisRect.Width() * 0.9) - 15, int(childRect.Height() * 0.9));
	laptime.GetWindowRect(&childRect);
	m_btn_laptime_reset.GetClientRect(&laptimeResetRect);
	m_btn_laptime_reset.MoveWindow(thisRect.Width() / 2 - (laptimeResetRect.Width() / 2), thisRect.Height() - 30 + childRect.Height() + 5, laptimeResetRect.Width(), laptimeResetRect.Height());
	m_btn_laptime_reset.ShowWindow(SW_HIDE);
	laptime.ShowWindow(SW_HIDE);

	m_btn_startandstop.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_reset.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_laptime.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_laptime_reset.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);

	m_stt_hms.Initialize(45, _T("DS-Digital"));

	m_stt_stopwatch_view.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_hms.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_hms.BringWindowToTop();

	m_btn_laptime.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void StopWatch::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL StopWatch::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}



void StopWatch::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CGoCabinetDlg* parent = (CGoCabinetDlg*)pParent;
	parent->bStopWatch = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


void StopWatch::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	StopWatch::PostNcDestroy();
}


HBRUSH StopWatch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIMER_VIEW)
		{
			CRect rect;
			GetClientRect(&rect);

			CDC* pDC = m_stt_stopwatch_view.GetWindowDC();
			CBrush *pOld = pDC->SelectObject(&m_backBrush);
			pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
			pDC->SelectObject(pOld);
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_HMS)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(50, 50, 50));
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_MILS)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(50, 50, 50));
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


void StopWatch::OnBnClickedButtonStartandstop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (bStart)
	{
		bStart = false;
		bThread = true;
		m_btn_startandstop.SetWindowTextW(_T("정지"));
		m_btn_reset.EnableWindow(FALSE);
		m_btn_laptime.EnableWindow(TRUE);
		m_thread = AfxBeginThread(thrStopWatch, this);
	}
	else
	{
		bStart = true;
		bThread = false;
		m_btn_startandstop.SetWindowTextW(_T("시작"));
		m_btn_reset.EnableWindow(TRUE);
		m_btn_laptime.EnableWindow(FALSE);
		if (bThread)
		{
			bThread = false;
			DWORD nExitCode = NULL;

			GetExitCodeThread(m_thread->m_hThread, &nExitCode);
			if (TerminateThread(m_thread->m_hThread, nExitCode) != 0)
			{
				delete m_thread;
				m_thread = nullptr;
			}
		}
	}
}


void StopWatch::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_stt_hms.SetWindowTextW(_T("00:00:00"));
}

UINT StopWatch::thrStopWatch(LPVOID method)
{
	StopWatch* stopwatch = (StopWatch*)method;
	stopwatch->StartStopWatch();

	return 0;
}

void StopWatch::StartStopWatch()
{

	while (bThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();

		m_stt_hms.GetWindowTextW(strHMS);
		AfxExtractSubString(strM, strHMS, 0, ':');
		AfxExtractSubString(strS, strHMS, 1, ':');
		AfxExtractSubString(strMils, strHMS, 2, ':');
		int mils = _ttoi(strMils);
		int m = _ttoi(strM);
		int s = _ttoi(strS);

		mils++;

		if (m >= 59 && s >= 59 && mils >= 100)
		{
			m_stt_hms.SetWindowTextW(_T("59:59:99"));
			bStart = true;
			bThread = false;
			m_btn_startandstop.SetWindowTextW(_T("시작"));
			m_btn_reset.EnableWindow(TRUE);
			break;
		}

		if (mils >= 100)
		{
			mils = 0;
			s++;

			if (s >= 60)
			{
				s = 0;
				m++;
			}
		}

		strHMS.Format(_T("%02d:%02d:%02d"), m, s, mils);
		m_stt_hms.SetWindowTextW(strHMS);

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep((10 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(10 - (duration * 1000)));
	}
}


void StopWatch::OnBnClickedButtonLaptime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bLaptime)
	{
		this->MoveWindow(thisRect.left, thisRect.top, thisRect.Width(), thisRect.Height() + childRect.Height() + 60);
		laptime.ShowWindow(SW_SHOW);
		m_btn_laptime_reset.ShowWindow(SW_SHOW);
		bLaptime = true;
	}
	laptime.AppendLapTime(strM, strS, strMils);
}


void StopWatch::OnBnClickedButtonLaptimeReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (bLaptime)
	{
		this->MoveWindow(thisRect.left, thisRect.top, thisRect.Width(), thisRect.Height());
		laptime.ShowWindow(SW_HIDE);
		m_btn_laptime_reset.ShowWindow(SW_HIDE);
		bLaptime = false;
	}
	laptime.DeleteLapTime();
}

void StopWatch::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect changeRect;
	GetWindowRect(&changeRect);
	thisRect.SetRect(changeRect.left, changeRect.top, thisRect.right + (changeRect.left - thisRect.left), thisRect.bottom + (changeRect.top - thisRect.top));
}


