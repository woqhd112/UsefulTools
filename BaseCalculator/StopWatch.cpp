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
}

StopWatch::~StopWatch()
{
	if (bThread)
	{
		bThread = false;
		TerminateThread(m_thread, 0);
		m_thread = nullptr;
		Sleep(50);
	}
}

void StopWatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIMER_VIEW, m_stt_stopwatch_view);
	DDX_Control(pDX, IDC_STATIC_HMS, m_stt_hms);
	DDX_Control(pDX, IDC_STATIC_MILS, m_stt_mils);
	DDX_Control(pDX, IDC_BUTTON_STARTANDSTOP, m_btn_startandstop);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_btn_reset);
}


BEGIN_MESSAGE_MAP(StopWatch, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_STARTANDSTOP, &StopWatch::OnBnClickedButtonStartandstop)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &StopWatch::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// Timer 메시지 처리기

BOOL StopWatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(RGB(255, 255, 255));
	m_backBrush.CreateSolidBrush(RGB(50, 50, 50));

	m_btn_startandstop.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_reset.Initialize(RGB(230, 230, 230), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_stt_hms.Initialize(40, _T("DS-Digital"));
	m_stt_mils.Initialize(20, _T("DS-Digital"));

	m_stt_stopwatch_view.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_hms.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_mils.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_hms.BringWindowToTop();
	m_stt_mils.BringWindowToTop();

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
		m_thread = AfxBeginThread(thrStopWatch, this);
	}
	else
	{
		bStart = true;
		bThread = false;
		m_btn_startandstop.SetWindowTextW(_T("시작"));
		m_btn_reset.EnableWindow(TRUE);
	}
}


void StopWatch::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_stt_hms.SetWindowTextW(_T("00:00"));
	m_stt_mils.SetWindowTextW(_T("00"));
}

UINT StopWatch::thrStopWatch(LPVOID method)
{
	StopWatch* stopwatch = (StopWatch*)method;
	stopwatch->StartStopWatch();

	return 0;
}

void StopWatch::StartStopWatch()
{
	m_btn_reset.EnableWindow(FALSE);
	CString strM;
	CString strS;

	while (bThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();

		m_stt_mils.GetWindowTextW(strMils);
		m_stt_hms.GetWindowTextW(strHMS);
		AfxExtractSubString(strM, strHMS, 0, ':');
		AfxExtractSubString(strS, strHMS, 1, ':');
		int mils = _ttoi(strMils);
		int m = _ttoi(strM);
		int s = _ttoi(strS);

		mils++;

		if (m >= 59 && s >= 59 && mils >= 100)
		{
			m_stt_hms.SetWindowTextW(_T("59:59"));
			m_stt_mils.SetWindowTextW(_T("99"));
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

		strMils.Format(_T("%02d"), mils);
		strHMS.Format(_T("%02d:%02d"), m, s);
		m_stt_hms.SetWindowTextW(strHMS);
		m_stt_mils.SetWindowTextW(strMils);

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep(DWORD(10 - duration));
	}
}
