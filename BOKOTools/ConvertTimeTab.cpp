﻿// ConvertTimeTab.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "ConvertTimeTab.h"
#include "GeneralUtil.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ConvertTimeTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertTimeTab, CDialogEx)

ConvertTimeTab::ConvertTimeTab(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_TIME, pParent)
{
	this->currentTheme = currentTheme;
}

ConvertTimeTab::~ConvertTimeTab()
{
}

void ConvertTimeTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ICON_TIME, m_btn_icon);
	DDX_Control(pDX, IDC_EDIT_DATE, m_edit_date);
	DDX_Control(pDX, IDC_EDIT_HOUR, m_edit_hour);
	DDX_Control(pDX, IDC_EDIT_MINUTE, m_edit_minute);
	DDX_Control(pDX, IDC_EDIT_SECOND, m_edit_second);
	DDX_Control(pDX, IDC_BUTTON_DATE_TEST, m_btn_test1);
	DDX_Control(pDX, IDC_BUTTON_HOUR_TEST, m_btn_test2);
	DDX_Control(pDX, IDC_BUTTON_MINUTE_TEST, m_btn_test3);
	DDX_Control(pDX, IDC_BUTTON_SECOND_TEST, m_btn_test4);
	DDX_Control(pDX, IDC_BUTTON_RESET_TIME, m_btn_reset);
	DDX_Control(pDX, IDC_STATIC_DHMS_TIME, m_stt_dhms);
	DDX_Control(pDX, IDC_STATIC_HMS_TIME, m_stt_hms);
	DDX_Control(pDX, IDC_STATIC_MS_TIME, m_stt_ms);
	DDX_Control(pDX, IDC_STATIC_S_TIME, m_stt_s);
	DDX_Control(pDX, IDC_STATIC_DIVIDE5, m_stt_divide);
	DDX_Control(pDX, IDC_STATIC_TIME_ALL_VIEW, m_stt_time_all_view);
}


BEGIN_MESSAGE_MAP(ConvertTimeTab, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_DATE, &ConvertTimeTab::OnEnChangeEditDate)
	ON_EN_CHANGE(IDC_EDIT_HOUR, &ConvertTimeTab::OnEnChangeEditHour)
	ON_EN_CHANGE(IDC_EDIT_MINUTE, &ConvertTimeTab::OnEnChangeEditMinute)
	ON_EN_CHANGE(IDC_EDIT_SECOND, &ConvertTimeTab::OnEnChangeEditSecond)
	ON_BN_CLICKED(IDC_BUTTON_RESET_TIME, &ConvertTimeTab::OnBnClickedButtonResetTime)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ConvertTimeTab 메시지 처리기


void ConvertTimeTab::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL ConvertTimeTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());
	
	int nBrightness = GetBrightness(GetRValue(currentTheme->GetFunctionSubColor()), GetGValue(currentTheme->GetFunctionSubColor()), GetBValue(currentTheme->GetFunctionSubColor()));

	if (nBrightness > 120)
	{
		m_btn_icon.LoadStdImage(IDB_PNG_CONVERT_TIME_CLICK, _T("PNG"));
		m_btn_icon.LoadHovImage(IDB_PNG_CONVERT_TIME_HOVER, _T("PNG"));
		m_btn_icon.LoadAltImage(IDB_PNG_CONVERT_TIME_NOMAL, _T("PNG"));
	}
	else
	{
		m_btn_icon.LoadStdImage(IDB_PNG_CONVERT_TIME_NOMAL, _T("PNG"));
		m_btn_icon.LoadHovImage(IDB_PNG_CONVERT_TIME_HOVER, _T("PNG"));
		m_btn_icon.LoadAltImage(IDB_PNG_CONVERT_TIME_CLICK, _T("PNG"));
	}
	m_stt_time_all_view.MoveWindow(0, 0, 529, 314);
	m_stt_divide.MoveWindow(0, 0, 529, 62 + 26);
	m_btn_icon.MoveWindow(5, 5, 24, 24);

	int nButtonStart_x = 48;
	int nButtonStart_y = 18;
	int nButtonWidth = 110;
	int nButtonHeight = 26;
	int nButtonMargin = 5;
	int nEditMargin_xLeft = 5;
	int nEditMargin_y = 2;
	int nEditMargin_xRight = 30;

	m_btn_test1.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 0, nButtonStart_y, nButtonWidth, nButtonHeight);
	m_btn_test2.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 1, nButtonStart_y, nButtonWidth, nButtonHeight);
	m_btn_test3.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 2, nButtonStart_y, nButtonWidth, nButtonHeight);
	m_btn_test4.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 3, nButtonStart_y, nButtonWidth, nButtonHeight);

	m_edit_date.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 0 + nEditMargin_xLeft, nButtonStart_y + nEditMargin_y, nButtonWidth - nEditMargin_xLeft * 2 - nEditMargin_xRight, nButtonHeight - nEditMargin_y * 2);
	m_edit_hour.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 1 + nEditMargin_xLeft, nButtonStart_y + nEditMargin_y, nButtonWidth - nEditMargin_xLeft * 2 - nEditMargin_xRight, nButtonHeight - nEditMargin_y * 2);
	m_edit_minute.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 2 + nEditMargin_xLeft, nButtonStart_y + nEditMargin_y, nButtonWidth - nEditMargin_xLeft * 2 - nEditMargin_xRight, nButtonHeight - nEditMargin_y * 2);
	m_edit_second.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 3 + nEditMargin_xLeft, nButtonStart_y + nEditMargin_y, nButtonWidth - nEditMargin_xLeft * 2 - nEditMargin_xRight, nButtonHeight - nEditMargin_y * 2);

	m_btn_reset.MoveWindow(nButtonStart_x + (nButtonWidth + nButtonMargin) * 3, nButtonStart_y + nButtonHeight + 10, nButtonWidth, nButtonHeight);
	
	int nStaticStart_x = 10;
	int nStaticStart_y = 75 + 26 + 30;
	int nStaticWidth = 260;
	int nStaticHeight = 30;
	int nStaticMargin_x = 10;
	int nStaticMargin_y = 50;

	m_stt_dhms.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, nStaticStart_y + (nStaticHeight + nStaticMargin_y) * 0, nStaticWidth, nStaticHeight);
	m_stt_hms.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, nStaticStart_y + (nStaticHeight + nStaticMargin_y) * 0, nStaticWidth, nStaticHeight);
	m_stt_ms.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, nStaticStart_y + (nStaticHeight + nStaticMargin_y) * 1, nStaticWidth, nStaticHeight);
	m_stt_s.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, nStaticStart_y + (nStaticHeight + nStaticMargin_y) * 1, nStaticWidth, nStaticHeight);

	m_btn_reset.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_reset.SetTextColor(currentTheme->GetTextColor());
	m_btn_test1.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_test1.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test1.m_bUseMouseBkGroundColorEvent = false;
	m_btn_test2.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_test2.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test2.m_bUseMouseBkGroundColorEvent = false;
	m_btn_test3.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_test3.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test3.m_bUseMouseBkGroundColorEvent = false;
	m_btn_test4.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_test4.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test4.m_bUseMouseBkGroundColorEvent = false;
	m_btn_test1.SetTextColor(currentTheme->GetFunctionTextColor());
	m_btn_test2.SetTextColor(currentTheme->GetFunctionTextColor());
	m_btn_test3.SetTextColor(currentTheme->GetFunctionTextColor());
	m_btn_test4.SetTextColor(currentTheme->GetFunctionTextColor());

	m_edit_date.Initialize(18, _T("고딕"));
	m_edit_hour.Initialize(18, _T("고딕"));
	m_edit_minute.Initialize(18, _T("고딕"));
	m_edit_second.Initialize(18, _T("고딕"));

	m_stt_dhms.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_hms.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_ms.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_s.Initialize(22, currentTheme->GetThemeFontName());

	m_btn_test1.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_test2.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_test3.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_test4.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_date.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_hour.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_minute.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_second.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test1.BringWindowToTop();
	m_btn_test2.BringWindowToTop();
	m_btn_test3.BringWindowToTop();
	m_btn_test4.BringWindowToTop();
	m_edit_date.BringWindowToTop();
	m_edit_hour.BringWindowToTop();
	m_edit_minute.BringWindowToTop();
	m_edit_second.BringWindowToTop();

	m_edit_date.LimitText(7);
	m_edit_hour.LimitText(7);
	m_edit_minute.LimitText(7);
	m_edit_second.LimitText(7);

	m_btn_test1.SetWindowTextW(_T("일"));
	m_btn_test2.SetWindowTextW(_T("시간"));
	m_btn_test3.SetWindowTextW(_T("분"));
	m_btn_test4.SetWindowTextW(_T("초"));

	ConvertTime();

	CRect borderRect, thisRect;
	this->GetWindowRect(thisRect);
	m_btn_test1.GetWindowRect(borderRect);
	int nLeft = int(borderRect.left - thisRect.left - 2);
	int nTop = int(borderRect.top - thisRect.top - 2);
	drawBorderRect1 = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };

	m_btn_test2.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 2);
	nTop = int(borderRect.top - thisRect.top - 2);
	drawBorderRect2 = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };

	m_btn_test3.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 2);
	nTop = int(borderRect.top - thisRect.top - 2);
	drawBorderRect3 = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };

	m_btn_test4.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 2);
	nTop = int(borderRect.top - thisRect.top - 2);
	drawBorderRect4 = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ConvertTimeTab::ConvertTime()
{
	CString strDate, strHour, strMinute, strSecond;

	m_edit_date.GetWindowTextW(strDate);
	m_edit_hour.GetWindowTextW(strHour);
	m_edit_minute.GetWindowTextW(strMinute);
	m_edit_second.GetWindowTextW(strSecond);

	if (strDate.IsEmpty()) strDate = _T("0");
	if (strHour.IsEmpty()) strHour = _T("0");
	if (strMinute.IsEmpty()) strMinute = _T("0");
	if (strSecond.IsEmpty()) strSecond = _T("0");

	SetDHMS(strDate, strHour, strMinute, strSecond);
	SetHMS(strDate, strHour, strMinute, strSecond);
	SetMS(strDate, strHour, strMinute, strSecond);
	SetS(strDate, strHour, strMinute, strSecond);
}

void ConvertTimeTab::SetS(CString strDate, CString strHour, CString strMinute, CString strSecond)
{
	int nDate = _ttoi(strDate);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);

	nHour += (nDate * 24);
	nMinute += (nHour * 60);
	nSecond += (nMinute * 60);

	CString strFormat;

	strFormat.Format(_T("%d  초"), nSecond);
	m_stt_s.SetWindowTextW(strFormat);
}

void ConvertTimeTab::SetMS(CString strDate, CString strHour, CString strMinute, CString strSecond)
{
	int nDate = _ttoi(strDate);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);

	nHour += (nDate * 24);
	nMinute += (nHour * 60);

	while (true)
	{
		if (nSecond >= 60)
		{
			nSecond -= 60;
			nMinute++;
		}

		if (nSecond < 60) break;
	}

	CString strFormat;

	strFormat.Format(_T("%d  분 %d  초"), nMinute, nSecond);
	m_stt_ms.SetWindowTextW(strFormat);
}

void ConvertTimeTab::SetHMS(CString strDate, CString strHour, CString strMinute, CString strSecond)
{
	int nDate = _ttoi(strDate);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);

	nHour += (nDate * 24);

	while (true)
	{
		if (nMinute >= 60)
		{
			nMinute -= 60;
			nHour++;
		}

		if (nSecond >= 60)
		{
			nSecond -= 60;
			nMinute++;
		}

		if (nMinute < 60 && nSecond < 60) break;
	}

	CString strFormat;

	strFormat.Format(_T("%d  시간 %d  분 %d  초"), nHour, nMinute, nSecond);
	m_stt_hms.SetWindowTextW(strFormat);
}

void ConvertTimeTab::SetDHMS(CString strDate, CString strHour, CString strMinute, CString strSecond)
{
	int nDate = _ttoi(strDate);
	int nHour = _ttoi(strHour);
	int nMinute = _ttoi(strMinute);
	int nSecond = _ttoi(strSecond);

	while (true)
	{
		if (nHour >= 24)
		{
			nHour -= 24;
			nDate++;
		}

		if (nMinute >= 60)
		{
			nMinute -= 60;
			nHour++;
		}

		if (nSecond >= 60)
		{
			nSecond -= 60;
			nMinute++;
		}

		if (nHour < 24 && nMinute < 60 && nSecond < 60) break;
	}

	CString strFormat;

	strFormat.Format(_T("%d  일 %d  시간 %d  분 %d  초"), nDate, nHour, nMinute, nSecond);
	m_stt_dhms.SetWindowTextW(strFormat);
}

BOOL ConvertTimeTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_edit_date.m_bFocusOn)
	{
		CRect rect;
		m_edit_date.GetClientRect(rect);
		CDC* pDC = m_edit_date.GetWindowDC();
		pDC->Draw3dRect(rect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	}
	else if (m_edit_hour.m_bFocusOn)
	{
		CRect rect;
		m_edit_hour.GetClientRect(rect);
		CDC* pDC = m_edit_hour.GetWindowDC();
		pDC->Draw3dRect(rect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	}
	else if (m_edit_minute.m_bFocusOn)
	{
		CRect rect;
		m_edit_minute.GetClientRect(rect);
		CDC* pDC = m_edit_minute.GetWindowDC();
		pDC->Draw3dRect(rect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	}
	else if (m_edit_second.m_bFocusOn)
	{
		CRect rect;
		m_edit_second.GetClientRect(rect);
		CDC* pDC = m_edit_second.GetWindowDC();
		pDC->Draw3dRect(rect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	}

	if (pMsg->message == WM_LBUTTONUP)
	{
		m_edit_date.Invalidate();
		m_edit_hour.Invalidate();
		m_edit_minute.Invalidate();
		m_edit_second.Invalidate();
		if (pMsg->hwnd == m_edit_date)
		{
			m_edit_hour.m_bFocusOn = false;
			m_edit_minute.m_bFocusOn = false;
			m_edit_second.m_bFocusOn = false;
		}
		else if (pMsg->hwnd == m_edit_hour)
		{
			m_edit_date.m_bFocusOn = false;
			m_edit_minute.m_bFocusOn = false;
			m_edit_second.m_bFocusOn = false;
		}
		else if (pMsg->hwnd == m_edit_minute)
		{
			m_edit_date.m_bFocusOn = false;
			m_edit_hour.m_bFocusOn = false;
			m_edit_second.m_bFocusOn = false;
		}
		else if (pMsg->hwnd == m_edit_second)
		{
			m_edit_date.m_bFocusOn = false;
			m_edit_hour.m_bFocusOn = false;
			m_edit_minute.m_bFocusOn = false;
		}
		else
		{
			m_edit_date.m_bFocusOn = false;
			m_edit_hour.m_bFocusOn = false;
			m_edit_minute.m_bFocusOn = false;
			m_edit_second.m_bFocusOn = false;
			m_edit_date.HideCaret();
			m_edit_hour.HideCaret();
			m_edit_minute.HideCaret();
			m_edit_second.HideCaret();
		}
	}
	else if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_icon)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
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

		if (pMsg->hwnd == m_edit_date.GetSafeHwnd() || 
			pMsg->hwnd == m_edit_hour.GetSafeHwnd() ||
			pMsg->hwnd == m_edit_minute.GetSafeHwnd() ||
			pMsg->hwnd == m_edit_second.GetSafeHwnd())
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
				pMsg->wParam == VK_LEFT ||
				pMsg->wParam == VK_UP ||
				pMsg->wParam == VK_RIGHT ||
				pMsg->wParam == VK_DOWN ||
				pMsg->wParam == VK_BACK)
			{
			}
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


HBRUSH ConvertTimeTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_DATE)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_HOUR)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_MINUTE)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_SECOND)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_DHMS_TIME)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_HMS_TIME)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_MS_TIME)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_S_TIME)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void ConvertTimeTab::OnEnChangeEditDate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ConvertTime();
}


void ConvertTimeTab::OnEnChangeEditHour()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ConvertTime();
}


void ConvertTimeTab::OnEnChangeEditMinute()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ConvertTime();
}


void ConvertTimeTab::OnEnChangeEditSecond()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ConvertTime();
}


void ConvertTimeTab::OnBnClickedButtonResetTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_date.SetWindowTextW(_T(""));
	m_edit_hour.SetWindowTextW(_T(""));
	m_edit_minute.SetWindowTextW(_T(""));
	m_edit_second.SetWindowTextW(_T(""));
	ConvertTime();
}

void ConvertTimeTab::CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth /* = 1*/)
{
	if (nDepth > 1)
		return;

	CRect controlRect, controlToMarginRect1, controlToMarginRect2;

	if (nDepth == 1)
	{
		m_stt_dhms.GetWindowRect(&controlToMarginRect1);
		m_stt_s.GetWindowRect(&controlToMarginRect2);
		m_stt_dhms.GetClientRect(&controlRect);
	}

	int nMargin = controlToMarginRect2.top - controlToMarginRect1.bottom;

	int nStart_x = controlRect.left + 15;
	int nStart_y = nStartValue_y + nStartMargin + controlRect.Height() + (nMargin / 2);
	int nEnd_x = (controlRect.left + controlRect.Width()) * 3;

	LOGBRUSH lb;

	lb.lbStyle = BS_SOLID;
	lb.lbColor = currentTheme->GetFunctionRectBorderColor();

	CPen arNewPen;
	CPen* pOldPen = NULL;
	arNewPen.CreatePen(PS_SOLID | PS_ENDCAP_SQUARE, 1, &lb);

	pOldPen = dc->SelectObject(&arNewPen);
	dc->MoveTo(nStart_x /*펜을 시작할 x축 좌표*/, nStart_y /*펜을 시작할 y축 좌표*/);
	dc->LineTo(nEnd_x /*펜을 끝낼 x축 좌표*/, nStart_y /*펜을 끝낼 y축 좌표*/);
	dc->SelectObject(pOldPen);
	arNewPen.DeleteObject();
	nDepth++;

	CalcDrawLine(dc, nStart_y, nMargin / 2, nDepth);
}

void ConvertTimeTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect divideRect;
	m_stt_divide.GetClientRect(&divideRect);

	CRect divideToMargin1, divideToMargin2;
	m_stt_divide.GetWindowRect(&divideToMargin1);
	m_stt_dhms.GetWindowRect(&divideToMargin2);
	int nDivideMargin = divideToMargin2.top - divideToMargin1.bottom;

	CalcDrawLine(&dc, divideRect.top + divideRect.Height(), nDivideMargin);

	dc.Draw3dRect(drawBorderRect1, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	dc.Draw3dRect(drawBorderRect2, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	dc.Draw3dRect(drawBorderRect3, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	dc.Draw3dRect(drawBorderRect4, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
}
