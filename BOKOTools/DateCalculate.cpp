// TimeCalculate.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "DateCalculate.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// DateCalculate 대화 상자

IMPLEMENT_DYNAMIC(DateCalculate, CDialogEx)

DateCalculate::DateCalculate(bool bUsingManual, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TIME, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	this->bUsingManual = bUsingManual;
	std::vector<int> manualList = { IDB_PNG_BASE_CLICK_THEME_BASIC, IDB_PNG_BASE_CLICK_THEME_CLOUD, IDB_PNG_BASE_CLICK_THEME_DETECTIVE, IDB_PNG_BASE_CLICK_THEME_INK };
	usingManual = new UsingManualDialog(IDD_DIALOG_DATE, manualList, currentTheme);
	bBaseEditMax = false;
	bLimitEditMax = false;
}

DateCalculate::~DateCalculate()
{
	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
	}
}

void DateCalculate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_cal_calendar);
	DDX_Control(pDX, IDC_EDIT_BASEDATE, m_edit_baseedit);
	DDX_Control(pDX, IDC_EDIT_AFTER_DATE, m_edit_afterdate);
	DDX_Control(pDX, IDC_EDIT_AFTERDATE_RESULT, m_edit_afterdate_result);
	DDX_Control(pDX, IDC_EDIT_LIMITDATE_RESULT, m_edit_limitdate_result);
	DDX_Control(pDX, IDC_EDIT_LIMIT_DATE, m_edit_limitdate);
	DDX_Control(pDX, IDC_BUTTON_AFTERDATE, m_btn_afterdate);
	DDX_Control(pDX, IDC_BUTTON_LIMITDATE, m_btn_limitdate);
	DDX_Control(pDX, IDC_BUTTON_FOCUS, m_btn_focus);
	DDX_Control(pDX, IDC_BUTTON_ALLRESET, m_btn_reset);
	DDX_Control(pDX, IDC_STATIC_LIMITDATE_VIEW, m_stt_limitdate_view);
	DDX_Control(pDX, IDC_STATIC_LIMITDATE_DIVIDE_VIEW, m_stt_limitdate_divide_view);
	DDX_Control(pDX, IDC_STATIC_LIMITDATE, m_stt_limitdate);
	DDX_Control(pDX, IDC_STATIC_BASE_DATE, m_stt_base_date);
	DDX_Control(pDX, IDC_STATIC_FIRST_OFFICIAL, m_stt_first_official);
	DDX_Control(pDX, IDC_STATIC_LAST_OFFICIAL, m_stt_last_official);
}


BEGIN_MESSAGE_MAP(DateCalculate, CDialogEx)
	ON_WM_CLOSE()
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR, &DateCalculate::OnMcnSelchangeMonthcalendar)
	ON_EN_CHANGE(IDC_EDIT_BASEDATE, &DateCalculate::OnEnChangeEditBasedate)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_LIMIT_DATE, &DateCalculate::OnEnChangeEditLimitDate)
	ON_BN_CLICKED(IDC_BUTTON_AFTERDATE, &DateCalculate::OnBnClickedButtonAfterdate)
	ON_BN_CLICKED(IDC_BUTTON_LIMITDATE, &DateCalculate::OnBnClickedButtonLimitdate)
	ON_BN_CLICKED(IDC_BUTTON_ALLRESET, &DateCalculate::OnBnClickedButtonAllreset)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DateCalculate 메시지 처리기


BOOL DateCalculate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());

	this->SetWindowPos(NULL, 0, 0, 320, 690, SWP_NOMOVE);
	//m_cal_calendar.SizeMinReq();
	m_cal_calendar.MoveWindow(30, 20, 240, 160);
	CRect calRect;
	m_cal_calendar.GetWindowRect(calRect);
	m_stt_base_date.MoveWindow(30, 30 + calRect.Height() + 20, 100, 30);
	m_edit_baseedit.MoveWindow(30, 30 + calRect.Height() + 20 + 30, 150, 30);
	m_btn_reset.MoveWindow(30 + 150 + 10, 30 + calRect.Height() + 20 + 30, 80, 30);

	m_stt_limitdate.MoveWindow(30, 150 + calRect.Height(), 150, 30);
	m_stt_limitdate_view.MoveWindow(25, 150 + calRect.Height() + 30 + 10, 255, 280);
	m_stt_limitdate_divide_view.MoveWindow(25, 150 + calRect.Height() + 30 + 10 + 140, 255, 140);

	int nDateFormatStartPos_x = 45;
	int nFirstDateFormatStartPos_y = 215 + calRect.Height();
	int nLastDateFormatStartPos_y = 355 + calRect.Height();
	int nEditWidth = 120;
	int nFirstStaticWidth = 70;
	int nLastStaticWidth = 100;
	int nButtonWidth = 50;
	int nCtrlHeight = 30;
	int nCtrlMargin = 20;


	m_edit_afterdate.MoveWindow(nDateFormatStartPos_x, nFirstDateFormatStartPos_y, nEditWidth, nCtrlHeight);
	m_stt_first_official.MoveWindow(nDateFormatStartPos_x + nEditWidth + nCtrlMargin, nFirstDateFormatStartPos_y, nFirstStaticWidth, nCtrlHeight);
	m_btn_afterdate.MoveWindow(nDateFormatStartPos_x, nFirstDateFormatStartPos_y + nCtrlHeight + nCtrlMargin, nButtonWidth, nCtrlHeight);
	m_edit_afterdate_result.MoveWindow(nDateFormatStartPos_x + nButtonWidth + nCtrlMargin, nFirstDateFormatStartPos_y + nCtrlHeight + nCtrlMargin, nEditWidth, nCtrlHeight);

	m_edit_limitdate.MoveWindow(nDateFormatStartPos_x, nLastDateFormatStartPos_y, nEditWidth, nCtrlHeight);
	m_stt_last_official.MoveWindow(nDateFormatStartPos_x + nEditWidth + nCtrlMargin - 10, nLastDateFormatStartPos_y, nLastStaticWidth, nCtrlHeight);
	m_btn_limitdate.MoveWindow(nDateFormatStartPos_x, nLastDateFormatStartPos_y + nCtrlHeight + nCtrlMargin, nButtonWidth, nCtrlHeight);
	m_edit_limitdate_result.MoveWindow(nDateFormatStartPos_x + nButtonWidth + nCtrlMargin, nLastDateFormatStartPos_y + nCtrlHeight + nCtrlMargin, nEditWidth, nCtrlHeight);

	CRect borderRect, thisRect;
	this->GetWindowRect(thisRect);
	m_stt_limitdate_view.GetWindowRect(borderRect);
	int nLeft = int(borderRect.left - thisRect.left - 10);
	int nTop = int(borderRect.top - thisRect.top - 35);
	drawBorderRect1 = { nLeft, nTop, nLeft + borderRect.Width(), nTop + borderRect.Height() };

	m_stt_limitdate_divide_view.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 10);
	nTop = int(borderRect.top - thisRect.top - 35);
	drawBorderRect2 = { nLeft, nTop, nLeft + borderRect.Width(), nTop + borderRect.Height() };

	m_btn_afterdate.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_limitdate.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_reset.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_afterdate.SetTextColor(currentTheme->GetTextColor());
	m_btn_limitdate.SetTextColor(currentTheme->GetTextColor());
	m_btn_reset.SetTextColor(currentTheme->GetTextColor());

	m_edit_baseedit.Initialize(20, _T("고딕"));
	m_edit_afterdate.Initialize(20, _T("고딕"));
	m_edit_afterdate_result.Initialize(20, _T("고딕"));
	m_edit_limitdate_result.Initialize(12, _T("고딕"));
	m_edit_limitdate.Initialize(12, _T("고딕"));

	m_stt_limitdate.Initialize(25, currentTheme->GetThemeFontName());
	m_stt_base_date.Initialize(25, currentTheme->GetThemeFontName());
	m_stt_first_official.Initialize(20, currentTheme->GetThemeFontName());
	m_stt_last_official.Initialize(20, currentTheme->GetThemeFontName());

	m_edit_baseedit.SetLimitText(10);
	m_edit_limitdate.SetLimitText(10);

	SetCalendar();

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL);
		usingManual->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DateCalculate::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL DateCalculate::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_edit_afterdate_result)
		{
			m_edit_afterdate_result.HideCaret();
		}
		else if (pMsg->hwnd == m_edit_limitdate_result)
		{
			m_edit_limitdate_result.HideCaret();
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

		if (pMsg->hwnd == m_edit_baseedit.GetSafeHwnd())
		{
			if (pMsg->wParam == L'1' ||
				pMsg->wParam == L'2' ||
				pMsg->wParam == L'3' ||
				pMsg->wParam == L'4' ||
				pMsg->wParam == L'5' ||
				pMsg->wParam == L'6' ||
				pMsg->wParam == L'7' || 
				pMsg->wParam == L'8' ||
				pMsg->wParam == L'9' ||
				pMsg->wParam == L'0' ||
				pMsg->wParam == VK_DECIMAL ||
				pMsg->wParam == VK_LEFT ||
				pMsg->wParam == VK_UP ||
				pMsg->wParam == VK_RIGHT ||
				pMsg->wParam == VK_DOWN ||
				pMsg->wParam == VK_BACK ||
				pMsg->wParam == VK_OEM_PERIOD)
			{
				CString strText;
				m_edit_baseedit.GetWindowTextW(strText);
				int nLength = strText.GetLength();

				if (bBaseEditMax)
				{
					bool bIsFirstDot = false;
					bool bIsLastDot = false;
					bool bIsSubDot = false;

					for (int i = 0; i < 4; i++)
					{
						if (IsDot((CString)strText.GetAt(i)))
						{
							bIsSubDot = true;
						}
					}

					for (int i = 5; i < 7; i++)
					{
						if (IsDot((CString)strText.GetAt(i)))
						{
							bIsSubDot = true;
						}
					}

					for (int i = 8; i < nLength; i++)
					{
						if (IsDot((CString)strText.GetAt(i)))
						{
							bIsSubDot = true;
						}
					}

					if (IsDot((CString)strText.GetAt(4)))
					{
						bIsFirstDot = true;
					}

					if (IsDot((CString)strText.GetAt(7)))
					{
						bIsLastDot = true;
					}

					if (bIsSubDot)
					{
						m_edit_baseedit.m_bExampleText = true;
						m_edit_baseedit.SetWindowTextW(_T("ex) 1900.01.01"));
						m_btn_focus.SetFocus();
						return TRUE;
					}

					if (bIsFirstDot && bIsLastDot)
					{
						
					}
					else
					{
						m_edit_baseedit.m_bExampleText = true;
						m_edit_baseedit.SetWindowTextW(_T("ex) 1900.01.01"));
						m_btn_focus.SetFocus();
						return TRUE;
					}
				}
			}
			else
			{
				return TRUE;
			}
		}
		else if (pMsg->hwnd == m_edit_limitdate.GetSafeHwnd())
		{
			if (pMsg->wParam == L'1' ||
				pMsg->wParam == L'2' ||
				pMsg->wParam == L'3' ||
				pMsg->wParam == L'4' ||
				pMsg->wParam == L'5' ||
				pMsg->wParam == L'6' ||
				pMsg->wParam == L'7' ||
				pMsg->wParam == L'8' ||
				pMsg->wParam == L'9' ||
				pMsg->wParam == L'0' ||
				pMsg->wParam == VK_DECIMAL ||
				pMsg->wParam == VK_LEFT ||
				pMsg->wParam == VK_UP ||
				pMsg->wParam == VK_RIGHT ||
				pMsg->wParam == VK_DOWN ||
				pMsg->wParam == VK_BACK ||
				pMsg->wParam == VK_OEM_PERIOD)
			{
				CString strText;
				m_edit_limitdate.GetWindowTextW(strText);
				int nLength = strText.GetLength();
			

				if (bLimitEditMax)
				{
					bool bIsFirstDot = false;
					bool bIsLastDot = false;
					bool bIsSubDot = false;

					if (IsDot((CString)strText.GetAt(4)))
					{
						bIsFirstDot = true;
					}

					if (IsDot((CString)strText.GetAt(7)))
					{
						bIsLastDot = true;
					}

					for (int i = 0; i < 4; i++)
					{
						if (IsDot((CString)strText.GetAt(i)))
						{
							bIsSubDot = true;
						}
					}

					for (int i = 5; i < 7; i++)
					{
						if (IsDot((CString)strText.GetAt(i)))
						{
							bIsSubDot = true;
						}
					}

					for (int i = 8; i < nLength; i++)
					{
						if (IsDot((CString)strText.GetAt(i)))
						{
							bIsSubDot = true;
						}
					}

					if (bIsSubDot)
					{
						m_edit_limitdate.m_bExampleText = true;
						m_edit_limitdate.SetWindowTextW(_T("ex) 1900.01.01"));
						m_btn_focus.SetFocus();
						return TRUE;
					}

					if (bIsFirstDot && bIsLastDot) 
					{
						
					}
					else
					{
						m_edit_limitdate.m_bExampleText = true;
						m_edit_limitdate.SetWindowTextW(_T("ex) 1900.01.01"));
						m_btn_focus.SetFocus();
						return TRUE;
					}
				}
			}
			else
			{
				return TRUE;
			}
		}
		else
		{
			if (pMsg->message == WM_KEYDOWN)
			{
				if (pMsg->wParam == VK_ESCAPE)
				{
					return TRUE;
				}
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

bool DateCalculate::IsDot(CString strText)
{
	if (strText == _T(".")) return true;
	else return false;
}

void DateCalculate::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bDate = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


void DateCalculate::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	DateCalculate::PostNcDestroy();
}

void DateCalculate::SetCalendar()
{
	CTime currentTime;
	CString strFormatTime;
	m_cal_calendar.GetCurSel(currentTime);
	strFormatTime.Format(_T("%04d.%02d.%02d"), currentTime.GetYear(), currentTime.GetMonth(), currentTime.GetDay());
	m_edit_baseedit.SetWindowTextW(strFormatTime);
}

void DateCalculate::OnMcnSelchangeMonthcalendar(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_baseedit.m_bExampleText = false;
	m_edit_limitdate.m_bExampleText = false;
	SetCalendar();

	*pResult = 0;
}


void DateCalculate::OnEnChangeEditBasedate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strText;
	m_edit_baseedit.GetWindowTextW(strText);
	int nLength = strText.GetLength();

	if (nLength >= 9)
	{
		bBaseEditMax = true;
	}
	else
	{
		bBaseEditMax = false;
	}
}

void DateCalculate::OnEnChangeEditLimitDate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strText;
	m_edit_limitdate.GetWindowTextW(strText);
	int nLength = strText.GetLength();

	if (nLength >= 9)
	{
		bLimitEditMax = true;
	}
	else
	{
		bLimitEditMax = false;
	}
}

HBRUSH DateCalculate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_BASEDATE)
		{
			if (m_edit_baseedit.m_bExampleText)
			{
				pDC->SetTextColor(RGB(180, 180, 180));
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_LIMIT_DATE)
		{
			if (m_edit_limitdate.m_bExampleText)
			{
				pDC->SetTextColor(RGB(180, 180, 180));
			}
		}
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_LIMITDATE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE_DATE)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_FIRST_OFFICIAL)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_LAST_OFFICIAL)
		{
			pDC->SetTextColor(currentTheme->GetTextColor());
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void DateCalculate::OnBnClickedButtonAfterdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText;
	m_edit_baseedit.GetWindowTextW(strText);
	int nLength = strText.GetLength();

	if (nLength >= 10)
	{
		if (!m_edit_baseedit.m_bExampleText)
		{
			int nMonth = 0;
			CString strMonth;
			strMonth.Format(_T("%s%s"), (CString)strText.GetAt(5), (CString)strText.GetAt(6));
			nMonth = _ttoi(strMonth);
			
			if (nMonth > 12)
			{
				MessageBox(_T("기준일 형식이 정확하지 않습니다."));
				m_edit_baseedit.SetFocus();
				return;
			}

			int nDate = 0;
			CString strDate;
			strDate.Format(_T("%s%s"), (CString)strText.GetAt(8), (CString)strText.GetAt(9));
			nDate = _ttoi(strDate);

			if (nDate > 31)
			{
				MessageBox(_T("기준일 형식이 정확하지 않습니다."));
				m_edit_baseedit.SetFocus();
				return;
			}

			int nYear = 0;
			CString strYear;
			strYear.Format(_T("%s%s%s%s"), (CString)strText.GetAt(0), (CString)strText.GetAt(1), (CString)strText.GetAt(2), (CString)strText.GetAt(3));
			nYear = _ttoi(strYear);
			
			CTime baseTime(nYear, nMonth, nDate, 0, 0, 0);
			strText.Format(_T("%04d.%02d.%02d"), baseTime.GetYear(), baseTime.GetMonth(), baseTime.GetDay());
			m_edit_baseedit.SetWindowTextW(strText);

			CString strAfterDate, strAfterDateResult;
			m_edit_afterdate.GetWindowTextW(strAfterDate);

			baseTime += CTimeSpan(_ttoi(strAfterDate), 0, 0, 0);

			strAfterDateResult.Format(_T("%04d.%02d.%02d"), baseTime.GetYear(), baseTime.GetMonth(), baseTime.GetDay());
			m_edit_afterdate_result.SetWindowTextW(strAfterDateResult);
		}
	}
	else
	{
		MessageBox(_T("기준일 형식이 정확하지 않습니다."));
		m_edit_baseedit.SetFocus();
	}
}


void DateCalculate::OnBnClickedButtonLimitdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTime baseTime, targetTime;
	bool bBaseSuccess = false;
	bool bTargetSuccess = false;

	CString strText;
	m_edit_baseedit.GetWindowTextW(strText);
	int nLength = strText.GetLength();

	if (nLength >= 10)
	{
		if (!m_edit_baseedit.m_bExampleText)
		{
			int nMonth = 0;
			CString strMonth;
			strMonth.Format(_T("%s%s"), (CString)strText.GetAt(5), (CString)strText.GetAt(6));
			nMonth = _ttoi(strMonth);

			if (nMonth > 12)
			{
				MessageBox(_T("기준일 형식이 정확하지 않습니다."));
				m_edit_baseedit.SetFocus();
				return;
			}

			int nDate = 0;
			CString strDate;
			strDate.Format(_T("%s%s"), (CString)strText.GetAt(8), (CString)strText.GetAt(9));
			nDate = _ttoi(strDate);

			if (nDate > 31)
			{
				MessageBox(_T("기준일 형식이 정확하지 않습니다."));
				m_edit_baseedit.SetFocus();
				return;
			}

			int nYear = 0;
			CString strYear;
			strYear.Format(_T("%s%s%s%s"), (CString)strText.GetAt(0), (CString)strText.GetAt(1), (CString)strText.GetAt(2), (CString)strText.GetAt(3));
			nYear = _ttoi(strYear);

			baseTime = { nYear, nMonth, nDate, 0, 0, 0 };
			strText.Format(_T("%04d.%02d.%02d"), baseTime.GetYear(), baseTime.GetMonth(), baseTime.GetDay());
			m_edit_baseedit.SetWindowTextW(strText);
			bBaseSuccess = true;
		}
	}
	else
	{
		MessageBox(_T("기준일 형식이 정확하지 않습니다."));
		m_edit_baseedit.SetFocus();
		return;
	}


	m_edit_limitdate.GetWindowTextW(strText);
	nLength = strText.GetLength();

	if (nLength >= 10)
	{
		if (!m_edit_limitdate.m_bExampleText)
		{
			int nMonth = 0;
			CString strMonth;
			strMonth.Format(_T("%s%s"), (CString)strText.GetAt(5), (CString)strText.GetAt(6));
			nMonth = _ttoi(strMonth);

			if (nMonth > 12)
			{
				MessageBox(_T("해당일 형식이 정확하지 않습니다."));
				m_edit_limitdate.SetFocus();
				return;
			}

			int nDate = 0;
			CString strDate;
			strDate.Format(_T("%s%s"), (CString)strText.GetAt(8), (CString)strText.GetAt(9));
			nDate = _ttoi(strDate);

			if (nDate > 31)
			{
				MessageBox(_T("해당일 형식이 정확하지 않습니다."));
				m_edit_limitdate.SetFocus();
				return;
			}

			int nYear = 0;
			CString strYear;
			strYear.Format(_T("%s%s%s%s"), (CString)strText.GetAt(0), (CString)strText.GetAt(1), (CString)strText.GetAt(2), (CString)strText.GetAt(3));
			nYear = _ttoi(strYear);

			targetTime = { nYear, nMonth, nDate, 0, 0, 0 };
			strText.Format(_T("%04d.%02d.%02d"), targetTime.GetYear(), targetTime.GetMonth(), targetTime.GetDay());
			m_edit_limitdate.SetWindowTextW(strText);
			bTargetSuccess = true;
		}
	}
	else
	{
		MessageBox(_T("해당일 형식이 정확하지 않습니다."));
		m_edit_limitdate.SetFocus();
		return;
	}

	if (bBaseSuccess && bTargetSuccess)
	{
		CString strResult;
		CTimeSpan resultTime = targetTime - baseTime;
		strResult.Format(_T("%lld"), resultTime.GetDays());
		m_edit_limitdate_result.SetWindowTextW(strResult);
	}
}


void DateCalculate::OnBnClickedButtonAllreset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_baseedit.SetWindowTextW(_T(""));
	m_edit_baseedit.m_bExampleText = false;
	m_edit_afterdate.SetWindowTextW(_T(""));
	m_edit_limitdate.SetWindowTextW(_T(""));
	m_edit_limitdate.m_bExampleText = false;
	m_edit_afterdate_result.SetWindowTextW(_T(""));
	m_edit_limitdate_result.SetWindowTextW(_T(""));
	bLimitEditMax = false;

	m_cal_calendar.SetCurSel(CTime::GetCurrentTime());
	SetCalendar();
}


void DateCalculate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(drawBorderRect1, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
	dc.Draw3dRect(drawBorderRect2, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
}
