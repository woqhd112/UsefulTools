﻿// ConvertLengthTab.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "ConvertLengthTab.h"
#include "GeneralUtil.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ConvertLengthTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertLengthTab, CDialogEx)

ConvertLengthTab::ConvertLengthTab(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_LENGTH, pParent)
{
	this->currentTheme = currentTheme;
	bComboShow = false;
}

ConvertLengthTab::~ConvertLengthTab()
{
}

void ConvertLengthTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ICON_LENGTH, m_btn_icon);
	DDX_Control(pDX, IDC_BUTTON_COMBO, m_btn_combo);
	DDX_Control(pDX, IDC_COMBO_LEFT, m_combo_left);
	DDX_Control(pDX, IDC_EDIT_LEFT_VALUE, m_edit_left_value);
	DDX_Control(pDX, IDC_BUTTON_CONTAINER, m_btn_test);
	DDX_Control(pDX, IDC_STATIC_MM, m_stt_mm);
	DDX_Control(pDX, IDC_STATIC_CM, m_stt_cm);
	DDX_Control(pDX, IDC_STATIC_M, m_stt_m);
	DDX_Control(pDX, IDC_STATIC_KM, m_stt_km);
	DDX_Control(pDX, IDC_STATIC_IN, m_stt_in);
	DDX_Control(pDX, IDC_STATIC_FT, m_stt_ft);
	DDX_Control(pDX, IDC_STATIC_YD, m_stt_yd);
	DDX_Control(pDX, IDC_STATIC_MILES, m_stt_miles);
	DDX_Control(pDX, IDC_STATIC_JA, m_stt_ja);
	DDX_Control(pDX, IDC_STATIC_GAN, m_stt_gan);
	DDX_Control(pDX, IDC_STATIC_JUNG, m_stt_jung);
	DDX_Control(pDX, IDC_STATIC_LEE, m_stt_lee);
	DDX_Control(pDX, IDC_STATIC_HAELEE, m_stt_haelee);
	DDX_Control(pDX, IDC_STATIC_DIVIDE, m_stt_divide);
	DDX_Control(pDX, IDC_STATIC_LENGTH_ALL_VIEW, m_stt_length_all_view);
}


BEGIN_MESSAGE_MAP(ConvertLengthTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMBO, &ConvertLengthTab::OnBnClickedButtonCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_LEFT, &ConvertLengthTab::OnCbnSelchangeComboLeft)
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_LEFT_VALUE, &ConvertLengthTab::OnEnChangeEditLeftValue)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ConvertLengthTab 메시지 처리기


void ConvertLengthTab::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL ConvertLengthTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());

	int nBrightness = GetBrightness(GetRValue(currentTheme->GetFunctionSubColor()), GetGValue(currentTheme->GetFunctionSubColor()), GetBValue(currentTheme->GetFunctionSubColor()));

	if (nBrightness > 120)
	{
		m_btn_icon.LoadStdImage(IDB_PNG_CONVERT_LENGTH_CLICK, _T("PNG"));
		m_btn_icon.LoadHovImage(IDB_PNG_CONVERT_LENGTH_HOVER, _T("PNG"));
		m_btn_icon.LoadAltImage(IDB_PNG_CONVERT_LENGTH_NOMAL, _T("PNG"));
	}
	else
	{
		m_btn_icon.LoadStdImage(IDB_PNG_CONVERT_LENGTH_NOMAL, _T("PNG"));
		m_btn_icon.LoadHovImage(IDB_PNG_CONVERT_LENGTH_HOVER, _T("PNG"));
		m_btn_icon.LoadAltImage(IDB_PNG_CONVERT_LENGTH_CLICK, _T("PNG"));
	}
	m_stt_length_all_view.MoveWindow(0, 0, 529, 314);
	m_stt_divide.MoveWindow(0, 0, 529, 62);
	m_btn_icon.MoveWindow(5, 5, 24, 24);
	m_btn_test.MoveWindow(38 + 20, 18, 168 + 20, 26);
	m_btn_combo.MoveWindow(38 + 20 + 168 + 16 + 20, 18, 185 + 20, 26);
	m_edit_left_value.MoveWindow(38 + 20 + 10, 22, 168 + 20 - 50, 18);
	m_combo_left.MoveWindow(38 + 20 + 168 + 16 + 20, 18, 185 + 20, 90);

	int nStaticStart_x = 10;
	int nStaticStart_y = 75;
	int nStaticWidth = 165;
	int nStaticHeight = 30;
	int nStaticMargin_x = 10;
	int nStaticMargin_y = 20;

	m_stt_mm.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 0, 165, 30);
	m_stt_cm.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 0, 165, 30);
	m_stt_m.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 2, 75 + (nStaticHeight + nStaticMargin_y) * 0, 165, 30);

	m_stt_km.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 1, 165, 30);
	m_stt_in.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 1, 165, 30);
	m_stt_ft.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 2, 75 + (nStaticHeight + nStaticMargin_y) * 1, 165, 30);
	
	m_stt_yd.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 2, 165, 30);
	m_stt_miles.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 2, 165, 30);
	m_stt_ja.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 2, 75 + (nStaticHeight + nStaticMargin_y) * 2, 165, 30);

	m_stt_gan.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 3, 165, 30);
	m_stt_jung.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 3, 165, 30);
	m_stt_lee.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 2, 75 + (nStaticHeight + nStaticMargin_y) * 3, 165, 30);

	m_stt_haelee.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 4, 165, 30);

	CRect borderRect, thisRect;
	m_btn_test.GetWindowRect(borderRect);
	this->GetWindowRect(thisRect);
	int nLeft = int(borderRect.left - thisRect.left - 2);
	int nTop = int(borderRect.top - thisRect.top - 2);
	drawBorderRect = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };

	m_btn_combo.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 2);
	nTop = int(borderRect.top - thisRect.top - 2);
	drawComboBorderRect = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };


	m_btn_combo.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 22);
	m_btn_combo.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_combo.m_bUseMouseBkGroundColorEvent = false;
	m_btn_test.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 22);
	m_btn_test.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test.m_bUseMouseBkGroundColorEvent = false;
	m_btn_combo.SetTextColor(currentTheme->GetFunctionTextColor());
	m_btn_test.SetTextColor(currentTheme->GetFunctionTextColor());

	m_edit_left_value.Initialize(18, _T("고딕"));
	
	m_stt_mm.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_cm.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_m.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_km.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_in.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_ft.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_yd.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_miles.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_ja.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_gan.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_jung.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_lee.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_haelee.Initialize(22, currentTheme->GetThemeFontName());


	comboFont.CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		currentTheme->GetThemeFontName());
	m_combo_left.SetFont(&comboFont);

	m_combo_left.InsertString(0, _T("밀리미터 (mm)"));
	m_combo_left.InsertString(1, _T("센티미터 (cm)"));
	m_combo_left.InsertString(2, _T("미터 (m)"));
	m_combo_left.InsertString(3, _T("킬로미터 (km)"));
	m_combo_left.InsertString(4, _T("인치 (in)"));
	m_combo_left.InsertString(5, _T("피트 (ft)"));
	m_combo_left.InsertString(6, _T("야드 (yd)"));
	m_combo_left.InsertString(7, _T("마일 (mile)"));
	m_combo_left.InsertString(8, _T("자 (尺)"));
	m_combo_left.InsertString(9, _T("간 (間)"));
	m_combo_left.InsertString(10, _T("정 (町)"));
	m_combo_left.InsertString(11, _T("리 (里)"));
	m_combo_left.InsertString(12, _T("해리 (海里)"));


	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_combo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_left_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_mm.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_cm.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_m.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_km.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_in.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_ft.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_yd.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_miles.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_ja.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_gan.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_jung.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_lee.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_haelee.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test.BringWindowToTop();
	m_stt_mm.BringWindowToTop();
	m_stt_cm.BringWindowToTop();
	m_stt_m.BringWindowToTop();
	m_stt_km.BringWindowToTop();
	m_stt_in.BringWindowToTop();
	m_stt_ft.BringWindowToTop();
	m_stt_yd.BringWindowToTop();
	m_stt_miles.BringWindowToTop();
	m_stt_ja.BringWindowToTop();
	m_stt_gan.BringWindowToTop();
	m_stt_jung.BringWindowToTop();
	m_stt_lee.BringWindowToTop();
	m_stt_haelee.BringWindowToTop();
	m_edit_left_value.BringWindowToTop();
	m_combo_left.BringWindowToTop();
	m_btn_combo.BringWindowToTop();

	m_combo_left.SetCurSel(0);
	
	SetComboButtonText(_T("▼"));
	SetTestButtonText();

	m_edit_left_value.SetWindowTextW(_T("1"));
	ConvertLength();

	m_combo_left.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ConvertLengthTab::OnBnClickedButtonCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bComboShow)
	{
		m_combo_left.ShowWindow(SW_SHOW);
		bComboShow = true;
		SetComboButtonText(_T("▲"));
	}
	else
	{
		m_combo_left.ShowWindow(SW_HIDE);
		bComboShow = false;
		SetComboButtonText(_T("▼"));
	}
}



void ConvertLengthTab::OnCbnSelchangeComboLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetComboButtonText(_T("▲"));
	SetTestButtonText();
	ConvertLength();
}


void ConvertLengthTab::ConvertLength()
{
	CString strSymbol;
	double dFirstResult = ConvertLeftToMeter();
	SetStaticValue(dFirstResult);
}

double ConvertLengthTab::ConvertLeftToMeter()
{
	CString strText;
	m_edit_left_value.GetWindowTextW(strText);
	double dResult = 0;
	int nSel = m_combo_left.GetCurSel();

	if (nSel == 0)	// mm -> m
	{
		double dmMeter = _ttof(strText);
		dResult = (dmMeter * 0.1) / 100;
	}
	else if (nSel == 1) // cm -> m
	{
		double dcMeter = _ttof(strText);
		dResult = (dcMeter * 1) / 100;
	}
	else if (nSel == 2) // m -> m
	{
		double dMeter = _ttof(strText);
		dResult = (dMeter * 100) / 100;
	}
	else if (nSel == 3) // km -> m
	{
		double dkMeter = _ttof(strText);
		dResult = (dkMeter * 100000) / 100;
	}
	else if (nSel == 4) // inch -> m
	{
		double dinch = _ttof(strText);
		dResult = (dinch * 2.54) / 100;
	}
	else if (nSel == 5) // feet -> m
	{
		double dfeet = _ttof(strText);
		dResult = (dfeet * 30.48) / 100;
	}
	else if (nSel == 6) // yard -> m
	{
		double dyard = _ttof(strText);
		dResult = (dyard * 90.44) / 100;
	}
	else if (nSel == 7) // mile -> m
	{
		double dmiles= _ttof(strText);
		dResult = (dmiles * 160934.4) / 100;
	}
	else if (nSel == 8) // ja -> m
	{
		double dja = _ttof(strText);
		dResult = (dja * 30.3) / 100;
	}
	else if (nSel == 9) // gan -> m
	{
		double dgan = _ttof(strText);
		dResult = (dgan * 181.8182) / 100;
	}
	else if (nSel == 10) // jung -> m
	{
		double djung = _ttof(strText);
		dResult = (djung * 10909.0909) / 100;
	}
	else if (nSel == 11) // lee -> m
	{
		double dlee = _ttof(strText);
		dResult = (dlee * 39272.7273) / 100;
	}
	else // haelee -> m
	{
		double dhaelee = _ttof(strText);
		dResult = (dhaelee * 185200) / 100;
	}

	return dResult;
}

void ConvertLengthTab::SetStaticValue(double dFirstValue)
{
	CString strFormat;

	strFormat.Format(_T("%g mm"), dFirstValue * 100 * 10);
	m_stt_mm.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g cm"), dFirstValue * 100);
	m_stt_cm.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g m"), dFirstValue);
	m_stt_m.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g km"), dFirstValue / 1000);
	m_stt_km.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g in"), dFirstValue * 39.370079);
	m_stt_in.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g ft"), dFirstValue * 3.28084);
	m_stt_ft.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g yd"), dFirstValue  * 1.093613);
	m_stt_yd.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g mile"), (dFirstValue * 0.621371) / 1000);
	m_stt_miles.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 尺"), dFirstValue * 3.3);
	m_stt_ja.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 間"), dFirstValue * 0.55);
	m_stt_gan.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 町"), (dFirstValue * 9.166667) / 1000);
	m_stt_jung.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 里"), (dFirstValue * 2.546296) / 1000);
	m_stt_lee.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 海里"), (dFirstValue * 0.539957) / 1000);
	m_stt_haelee.SetWindowTextW(strFormat);
}

void ConvertLengthTab::SetComboButtonText(CString strSymbol)
{
	CString strFormatText, strLeftText;
	int nLeftIdx = m_combo_left.GetCurSel();

	m_combo_left.GetLBText(nLeftIdx, strLeftText);

	strFormatText.Format(_T("%s       %s"), strLeftText, strSymbol);
	m_btn_combo.SetWindowTextW(strFormatText);
}

void ConvertLengthTab::SetTestButtonText()
{
	if (m_combo_left.GetCurSel() == 0)
	{
		m_btn_test.SetWindowTextW(_T("mm"));
	}
	else if (m_combo_left.GetCurSel() == 1)
	{
		m_btn_test.SetWindowTextW(_T("cm"));
	}
	else if (m_combo_left.GetCurSel() == 2)
	{
		m_btn_test.SetWindowTextW(_T("m"));
	}
	else if (m_combo_left.GetCurSel() == 3)
	{
		m_btn_test.SetWindowTextW(_T("km"));
	}
	else if (m_combo_left.GetCurSel() == 4)
	{
		m_btn_test.SetWindowTextW(_T("in"));
	}
	else if (m_combo_left.GetCurSel() == 5)
	{
		m_btn_test.SetWindowTextW(_T("ft"));
	}
	else if (m_combo_left.GetCurSel() == 6)
	{
		m_btn_test.SetWindowTextW(_T("yd"));
	}
	else if (m_combo_left.GetCurSel() == 7)
	{
		m_btn_test.SetWindowTextW(_T("mile"));
	}
	else if (m_combo_left.GetCurSel() == 8)
	{
		m_btn_test.SetWindowTextW(_T("尺"));
	}
	else if (m_combo_left.GetCurSel() == 9)
	{
		m_btn_test.SetWindowTextW(_T("間"));
	}
	else if (m_combo_left.GetCurSel() == 10)
	{
		m_btn_test.SetWindowTextW(_T("町"));
	}
	else if (m_combo_left.GetCurSel() == 11)
	{
		m_btn_test.SetWindowTextW(_T("里"));
	}
	else if (m_combo_left.GetCurSel() == 12)
	{
		m_btn_test.SetWindowTextW(_T("海里"));
	}
}



BOOL ConvertLengthTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	if (m_edit_left_value.m_bFocusOn)
	{
		CRect rect;
		m_edit_left_value.GetClientRect(rect);
		CDC* pDC = m_edit_left_value.GetWindowDC();
		pDC->Draw3dRect(rect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	}
	
	if (pMsg->message == WM_LBUTTONUP)
	{
		m_edit_left_value.Invalidate();
		if (pMsg->hwnd != m_edit_left_value)
		{
			m_edit_left_value.m_bFocusOn = false;
			m_edit_left_value.HideCaret();
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

		if (pMsg->hwnd == m_edit_left_value.GetSafeHwnd())
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


HBRUSH ConvertLengthTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_LEFT_VALUE)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MM)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_CM)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_M)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_KM)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_IN)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_FT)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_YD)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_MILES)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_JA)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_GAN)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_JUNG)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_LEE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_HAELEE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void ConvertLengthTab::OnEnChangeEditLeftValue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	ConvertLength();

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ConvertLengthTab::CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth /* = 1*/)
{
	if (nDepth > 4)
		return;

	CRect controlRect, controlToMarginRect1, controlToMarginRect2;

	if (nDepth == 1)
	{
		m_stt_mm.GetWindowRect(&controlToMarginRect1);
		m_stt_km.GetWindowRect(&controlToMarginRect2);
		m_stt_mm.GetClientRect(&controlRect);
	}
	else if (nDepth == 2)
	{
		m_stt_km.GetWindowRect(&controlToMarginRect1);
		m_stt_yd.GetWindowRect(&controlToMarginRect2);
		m_stt_km.GetClientRect(&controlRect);
	}
	else if (nDepth == 3)
	{
		m_stt_yd.GetWindowRect(&controlToMarginRect1);
		m_stt_gan.GetWindowRect(&controlToMarginRect2);
		m_stt_yd.GetClientRect(&controlRect);
	}
	else
	{
		m_stt_gan.GetWindowRect(&controlToMarginRect1);
		m_stt_haelee.GetWindowRect(&controlToMarginRect2);
		m_stt_gan.GetClientRect(&controlRect);
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

void ConvertLengthTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	
	CRect divideRect;
	m_stt_divide.GetClientRect(&divideRect);

	CRect divideToMargin1, divideToMargin2;
	m_stt_divide.GetWindowRect(&divideToMargin1);
	m_stt_mm.GetWindowRect(&divideToMargin2);
	int nDivideMargin = divideToMargin2.top - divideToMargin1.bottom;

	CalcDrawLine(&dc, divideRect.top + divideRect.Height(), nDivideMargin);

	dc.Draw3dRect(drawBorderRect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	dc.Draw3dRect(drawComboBorderRect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
}
