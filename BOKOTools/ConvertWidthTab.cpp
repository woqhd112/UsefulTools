// ConvertWidthTab.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "ConvertWidthTab.h"
#include "GeneralUtil.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ConvertWidthTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertWidthTab, CDialogEx)

ConvertWidthTab::ConvertWidthTab(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_WIDTH, pParent)
{
	this->currentTheme = currentTheme;
	bComboShow = false;
}

ConvertWidthTab::~ConvertWidthTab()
{
}

void ConvertWidthTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ICON_WIDTH, m_btn_icon);
	DDX_Control(pDX, IDC_BUTTON_COMBO2, m_btn_combo);
	DDX_Control(pDX, IDC_COMBO_LEFT2, m_combo_left);
	DDX_Control(pDX, IDC_BUTTON_CONTAINER2, m_btn_test1);
	DDX_Control(pDX, IDC_EDIT_LEFT_VALUE2, m_edit_left_value);
	DDX_Control(pDX, IDC_STATIC_SQUAREDM, m_stt_squared_m);
	DDX_Control(pDX, IDC_STATIC_ARE, m_stt_are);
	DDX_Control(pDX, IDC_STATIC_HECTARE, m_stt_hectare);
	DDX_Control(pDX, IDC_STATIC_SQUAREDKM, m_stt_squared_km);
	DDX_Control(pDX, IDC_STATIC_SQUAREDFT, m_stt_squared_ft);
	DDX_Control(pDX, IDC_STATIC_SQUAREDYD, m_stt_squared_yd);
	DDX_Control(pDX, IDC_STATIC_ACRE, m_stt_acre);
	DDX_Control(pDX, IDC_STATIC_SQUARERULER, m_stt_square_ruler);
	DDX_Control(pDX, IDC_STATIC_SQUARE, m_stt_square);
	DDX_Control(pDX, IDC_STATIC_DANBO, m_stt_danbo);
	DDX_Control(pDX, IDC_STATIC_JUNGBO, m_stt_jungbo);
	DDX_Control(pDX, IDC_STATIC_DIVIDE2, m_stt_divide);
	DDX_Control(pDX, IDC_STATIC_WIDTH_ALL_VIEW, m_stt_width_all_view);
}


BEGIN_MESSAGE_MAP(ConvertWidthTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMBO2, &ConvertWidthTab::OnBnClickedButtonCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO_LEFT2, &ConvertWidthTab::OnCbnSelchangeComboLeft2)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT2, &ConvertWidthTab::OnCbnSelchangeComboRight2)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_LEFT_VALUE2, &ConvertWidthTab::OnEnChangeEditLeftValue2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ConvertWidthTab 메시지 처리기


void ConvertWidthTab::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL ConvertWidthTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());

	int nBrightness = GetBrightness(GetRValue(currentTheme->GetFunctionSubColor()), GetGValue(currentTheme->GetFunctionSubColor()), GetBValue(currentTheme->GetFunctionSubColor()));

	if (nBrightness > 120)
	{
		m_btn_icon.LoadStdImage(IDB_PNG_CONVERT_WIDTH_CLICK, _T("PNG"));
		m_btn_icon.LoadHovImage(IDB_PNG_CONVERT_WIDTH_HOVER, _T("PNG"));
		m_btn_icon.LoadAltImage(IDB_PNG_CONVERT_WIDTH_NOMAL, _T("PNG"));
	}
	else
	{
		m_btn_icon.LoadStdImage(IDB_PNG_CONVERT_WIDTH_NOMAL, _T("PNG"));
		m_btn_icon.LoadHovImage(IDB_PNG_CONVERT_WIDTH_HOVER, _T("PNG"));
		m_btn_icon.LoadAltImage(IDB_PNG_CONVERT_WIDTH_CLICK, _T("PNG"));
	}
	m_stt_width_all_view.MoveWindow(0, 0, 529, 314);
	m_stt_divide.MoveWindow(0, 0, 529, 62);
	m_btn_icon.MoveWindow(5, 5, 24, 24);
	m_btn_test1.MoveWindow(38 + 20, 18, 168 + 20, 26);
	m_btn_combo.MoveWindow(38 + 20 + 168 + 16 + 20, 18, 185 + 20, 26);
	m_edit_left_value.MoveWindow(38 + 20 + 10, 22, 168 + 20 - 50, 18);
	m_combo_left.MoveWindow(38 + 20 + 168 + 16 + 20, 18, 185 + 20, 90);

	int nStaticStart_x = 10;
	int nStaticStart_y = 75;
	int nStaticWidth = 165;
	int nStaticHeight = 30;
	int nStaticMargin_x = 10;
	int nStaticMargin_y = 30;

	m_stt_squared_m.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 0, 165, 30);
	m_stt_are.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 0, 165, 30);
	m_stt_hectare.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 2, 75 + (nStaticHeight + nStaticMargin_y) * 0, 165, 30);

	m_stt_squared_km.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 1, 165, 30);
	m_stt_squared_ft.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 1, 165, 30);
	m_stt_squared_yd.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 2, 75 + (nStaticHeight + nStaticMargin_y) * 1, 165, 30);

	m_stt_acre.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 2, 165, 30);
	m_stt_square_ruler.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 2, 165, 30);
	m_stt_square.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 2, 75 + (nStaticHeight + nStaticMargin_y) * 2, 165, 30);

	m_stt_danbo.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 0, 75 + (nStaticHeight + nStaticMargin_y) * 3, 165, 30);
	m_stt_jungbo.MoveWindow(nStaticStart_x + (nStaticWidth + nStaticMargin_x) * 1, 75 + (nStaticHeight + nStaticMargin_y) * 3, 165, 30);

	CRect borderRect, thisRect;
	m_btn_test1.GetWindowRect(borderRect);
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
	m_btn_test1.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 22);
	m_btn_test1.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test1.m_bUseMouseBkGroundColorEvent = false;
	m_btn_combo.SetTextColor(currentTheme->GetFunctionTextColor());
	m_btn_test1.SetTextColor(currentTheme->GetFunctionTextColor());

	m_edit_left_value.Initialize(18, _T("고딕"));

	m_stt_squared_m.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_are.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_hectare.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_squared_km.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_squared_ft.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_squared_yd.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_acre.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_square_ruler.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_square.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_danbo.Initialize(22, currentTheme->GetThemeFontName());
	m_stt_jungbo.Initialize(22, currentTheme->GetThemeFontName());

	comboFont.CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		currentTheme->GetThemeFontName());
	m_combo_left.SetFont(&comboFont);

	m_combo_left.InsertString(0, _T("제곱미터 (m²)"));
	m_combo_left.InsertString(1, _T("아르 (a)"));
	m_combo_left.InsertString(2, _T("헥타르 (ha)"));
	m_combo_left.InsertString(3, _T("제곱킬로미터 (km²)"));
	m_combo_left.InsertString(4, _T("제곱피트 (ft²)"));
	m_combo_left.InsertString(5, _T("제곱야드 (yd²)"));
	m_combo_left.InsertString(6, _T("에이커 (ac)"));
	m_combo_left.InsertString(7, _T("평방자"));
	m_combo_left.InsertString(8, _T("평"));
	m_combo_left.InsertString(9, _T("단보"));
	m_combo_left.InsertString(10, _T("정보"));


	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_combo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test1.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_left_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_squared_m.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_are.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_hectare.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_squared_km.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_squared_ft.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_squared_yd.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_acre.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_square_ruler.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_square.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_danbo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_jungbo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test1.BringWindowToTop();
	m_stt_squared_m.BringWindowToTop();
	m_stt_are.BringWindowToTop();
	m_stt_hectare.BringWindowToTop();
	m_stt_squared_km.BringWindowToTop();
	m_stt_squared_ft.BringWindowToTop();
	m_stt_squared_yd.BringWindowToTop();
	m_stt_acre.BringWindowToTop();
	m_stt_square_ruler.BringWindowToTop();
	m_stt_square.BringWindowToTop();
	m_stt_danbo.BringWindowToTop();
	m_stt_jungbo.BringWindowToTop();
	m_edit_left_value.BringWindowToTop();
	m_combo_left.BringWindowToTop();
	m_btn_combo.BringWindowToTop();

	m_combo_left.SetCurSel(0);

	SetComboButtonText(_T("▼"));
	SetTestButtonText();

	m_edit_left_value.SetWindowTextW(_T("1"));
	ConvertWidth();

	m_combo_left.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ConvertWidthTab::ConvertWidth()
{
	CString strSymbol;
	double dFirstResult = ConvertLeftToSquaredKMeter();
	SetStaticValue(dFirstResult);
}

double ConvertWidthTab::ConvertLeftToSquaredKMeter()
{
	CString strText;
	m_edit_left_value.GetWindowTextW(strText);
	double dResult = 0;
	int nSel = m_combo_left.GetCurSel();
	// 처리
	if (nSel == 0)	// m² -> km²
	{
		double dsqMeter = _ttof(strText);
		dResult = dsqMeter / 1000000;
	}
	else if (nSel == 1) // a -> km²
	{
		double dare = _ttof(strText);
		dResult = dare / 10000;
	}
	else if (nSel == 2) // ha -> km²
	{
		double dhectare = _ttof(strText);
		dResult = dhectare / 100;
	}
	else if (nSel == 3) // km² -> km²
	{
		double dsqkMeter = _ttof(strText);
		dResult = dsqkMeter;
	}
	else if (nSel == 4) // ft² -> km²
	{
		double dsqFeet = _ttof(strText);
		dResult = dsqFeet / 10763910.4;
	}
	else if (nSel == 5) // yd² -> km²
	{
		double dsqYard = _ttof(strText);
		dResult = dsqYard / 1195990.05;
	}
	else if (nSel == 6) // ac -> km²
	{
		double dacre = _ttof(strText);
		dResult = (dacre * 4046.85642) / 1000000;
	}
	else if (nSel == 7) // 평방자 -> km²
	{
		double dsqRuler = _ttof(strText);
		dResult = (dsqRuler / 10.89) / 1000000;
	}
	else if (nSel == 8) // 평 -> km²
	{
		double dsquare = _ttof(strText);
		dResult = dsquare / 302500;
	}
	else if (nSel == 9) // 단보 -> km²
	{
		double ddanbo = _ttof(strText);
		dResult = (ddanbo * 991.735537) / 1000000;
	}
	else if (nSel == 10) // 정보 -> km²
	{
		double djungbo = _ttof(strText);
		dResult = (djungbo * 9917.35537) / 1000000;
	}

	return dResult;
}

void ConvertWidthTab::SetStaticValue(double dFirstValue)
{
	CString strFormat;
	// 처리
	strFormat.Format(_T("%g m²"), dFirstValue * 1000000);
	m_stt_squared_m.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g a"), dFirstValue * 10000);
	m_stt_are.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g ha"), dFirstValue * 100);
	m_stt_hectare.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g km²"), dFirstValue);
	m_stt_squared_km.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g ft²"), dFirstValue * 10763910.4);
	m_stt_squared_ft.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g yd²"), dFirstValue * 1195990.05);
	m_stt_squared_yd.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g ac"), dFirstValue * 247.105381);
	m_stt_acre.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 평방자"), dFirstValue * 10890000);
	m_stt_square_ruler.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 평"), dFirstValue * 302500);
	m_stt_square.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 단보"), dFirstValue * 1008.33333);
	m_stt_danbo.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 정보"), dFirstValue * 100.833333);
	m_stt_jungbo.SetWindowTextW(strFormat);
}

void ConvertWidthTab::SetComboButtonText(CString strSymbol)
{
	CString strFormatText, strLeftText;
	int nLeftIdx = m_combo_left.GetCurSel();

	m_combo_left.GetLBText(nLeftIdx, strLeftText);

	strFormatText.Format(_T("%s        %s"), strLeftText, strSymbol);
	m_btn_combo.SetWindowTextW(strFormatText);
}

void ConvertWidthTab::SetTestButtonText()
{
	if (m_combo_left.GetCurSel() == 0)
	{
		m_btn_test1.SetWindowTextW(_T("m²"));
	}
	else if (m_combo_left.GetCurSel() == 1)
	{
		m_btn_test1.SetWindowTextW(_T("a"));
	}
	else if (m_combo_left.GetCurSel() == 2)
	{
		m_btn_test1.SetWindowTextW(_T("ha"));
	}
	else if (m_combo_left.GetCurSel() == 3)
	{
		m_btn_test1.SetWindowTextW(_T("km²"));
	}
	else if (m_combo_left.GetCurSel() == 4)
	{
		m_btn_test1.SetWindowTextW(_T("ft²"));
	}
	else if (m_combo_left.GetCurSel() == 5)
	{
		m_btn_test1.SetWindowTextW(_T("yd²"));
	}
	else if (m_combo_left.GetCurSel() == 6)
	{
		m_btn_test1.SetWindowTextW(_T("ac"));
	}
	else if (m_combo_left.GetCurSel() == 7)
	{
		m_btn_test1.SetWindowTextW(_T("평방자"));
	}
	else if (m_combo_left.GetCurSel() == 8)
	{
		m_btn_test1.SetWindowTextW(_T("평"));
	}
	else if (m_combo_left.GetCurSel() == 9)
	{
		m_btn_test1.SetWindowTextW(_T("단보"));
	}
	else if (m_combo_left.GetCurSel() == 10)
	{
		m_btn_test1.SetWindowTextW(_T("정보"));
	}
}


void ConvertWidthTab::OnBnClickedButtonCombo2()
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


void ConvertWidthTab::OnCbnSelchangeComboLeft2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetComboButtonText(_T("▲"));
	SetTestButtonText();
	ConvertWidth();
}


void ConvertWidthTab::OnCbnSelchangeComboRight2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_combo_left.ShowWindow(SW_HIDE);
	bComboShow = false;

	SetComboButtonText(_T("▼"));
	ConvertWidth();
}


BOOL ConvertWidthTab::PreTranslateMessage(MSG* pMsg)
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


HBRUSH ConvertWidthTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_LEFT_VALUE2)
		{
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_SQUAREDM)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ARE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_HECTARE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SQUAREDKM)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SQUAREDFT)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SQUAREDYD)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ACRE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SQUARERULER)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SQUARE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_DANBO)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_JUNGBO)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void ConvertWidthTab::OnEnChangeEditLeftValue2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ConvertWidth();
}

void ConvertWidthTab::CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth /* = 1*/)
{
	if (nDepth > 3)
		return;

	CRect controlRect, controlToMarginRect1, controlToMarginRect2;

	if (nDepth == 1)
	{
		m_stt_squared_m.GetWindowRect(&controlToMarginRect1);
		m_stt_squared_km.GetWindowRect(&controlToMarginRect2);
		m_stt_squared_m.GetClientRect(&controlRect);
	}
	else if (nDepth == 2)
	{
		m_stt_squared_km.GetWindowRect(&controlToMarginRect1);
		m_stt_acre.GetWindowRect(&controlToMarginRect2);
		m_stt_squared_km.GetClientRect(&controlRect);
	}
	else
	{
		m_stt_acre.GetWindowRect(&controlToMarginRect1);
		m_stt_danbo.GetWindowRect(&controlToMarginRect2);
		m_stt_acre.GetClientRect(&controlRect);
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

void ConvertWidthTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect divideRect;
	m_stt_divide.GetClientRect(&divideRect);

	CRect divideToMargin1, divideToMargin2;
	m_stt_divide.GetWindowRect(&divideToMargin1);
	m_stt_squared_m.GetWindowRect(&divideToMargin2);
	int nDivideMargin = divideToMargin2.top - divideToMargin1.bottom;

	CalcDrawLine(&dc, divideRect.top + divideRect.Height(), nDivideMargin);

	dc.Draw3dRect(drawBorderRect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	dc.Draw3dRect(drawComboBorderRect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
}
