﻿// ConvertWidthTab.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "ConvertWidthTab.h"
#include "afxdialogex.h"


// ConvertWidthTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertWidthTab, CDialogEx)

ConvertWidthTab::ConvertWidthTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_WIDTH, pParent)
{
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
	DDX_Control(pDX, IDC_COMBO_RIGHT2, m_combo_right);
	DDX_Control(pDX, IDC_BUTTON_TEST2, m_btn_test);
	DDX_Control(pDX, IDC_EDIT_LEFT_VALUE2, m_edit_left_value);
	DDX_Control(pDX, IDC_EDIT_RIGHT_VALUE2, m_edit_right_value);
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
}


BEGIN_MESSAGE_MAP(ConvertWidthTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMBO2, &ConvertWidthTab::OnBnClickedButtonCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO_LEFT2, &ConvertWidthTab::OnCbnSelchangeComboLeft2)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT2, &ConvertWidthTab::OnCbnSelchangeComboRight2)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_LEFT_VALUE2, &ConvertWidthTab::OnEnChangeEditLeftValue2)
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
	m_backBrush.CreateSolidBrush(RGB(250, 250, 250));

	this->SetBackgroundColor(RGB(250, 250, 250));

	m_btn_icon.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_icon.InsertImage(IDB_PNG_WIDTH_NOMAL);
	m_btn_combo.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_combo.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_combo.SetWindowTextW(_T("테스트"));
	m_btn_combo.m_bUseMouseEvent = false;
	m_btn_test.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_test.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test.m_bUseMouseEvent = false;

	m_edit_left_value.Initialize(13, _T("휴먼매직체"));
	m_edit_right_value.Initialize(15, _T("휴먼매직체"));

	m_stt_squared_m.Initialize(14, _T("휴먼매직체"));
	m_stt_are.Initialize(14, _T("휴먼매직체"));
	m_stt_hectare.Initialize(14, _T("휴먼매직체"));
	m_stt_squared_km.Initialize(14, _T("휴먼매직체"));
	m_stt_squared_ft.Initialize(14, _T("휴먼매직체"));
	m_stt_squared_yd.Initialize(14, _T("휴먼매직체"));
	m_stt_acre.Initialize(14, _T("휴먼매직체"));
	m_stt_square_ruler.Initialize(14, _T("휴먼매직체"));
	m_stt_square.Initialize(14, _T("휴먼매직체"));
	m_stt_danbo.Initialize(14, _T("휴먼매직체"));
	m_stt_jungbo.Initialize(14, _T("휴먼매직체"));

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

	m_combo_right.InsertString(0, _T("제곱미터 (m²)"));
	m_combo_right.InsertString(1, _T("아르 (a)"));
	m_combo_right.InsertString(2, _T("헥타르 (ha)"));
	m_combo_right.InsertString(3, _T("제곱킬로미터 (km²)"));
	m_combo_right.InsertString(4, _T("제곱피트 (ft²)"));
	m_combo_right.InsertString(5, _T("제곱야드 (yd²)"));
	m_combo_right.InsertString(6, _T("에이커 (ac)"));
	m_combo_right.InsertString(7, _T("평방자"));
	m_combo_right.InsertString(8, _T("평"));
	m_combo_right.InsertString(9, _T("단보"));
	m_combo_right.InsertString(10, _T("정보"));

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_combo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_left_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_right_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

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
	m_edit_right_value.BringWindowToTop();
	m_combo_left.BringWindowToTop();
	m_combo_right.BringWindowToTop();
	m_btn_combo.BringWindowToTop();

	m_combo_left.SetCurSel(1);
	m_combo_right.SetCurSel(0);

	SetComboButtonText(_T("▼"));
	SetTestButtonText();

	m_edit_left_value.SetWindowTextW(_T("1"));
	ConvertLength();

	m_combo_left.ShowWindow(SW_HIDE);
	m_combo_right.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ConvertWidthTab::ConvertLength()
{
	CString strSymbol;
	double dFirstResult = ConvertLeftToSquaredKMeter();
	double dLastResult = ConvertSquaredKMeterToRight(dFirstResult, strSymbol);

	CString strResult;
	strResult.Format(_T("%g %s"), dLastResult, strSymbol);
	m_edit_right_value.SetWindowTextW(strResult);
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
		dResult = 0;
	}
	else if (nSel == 1) // a -> km²
	{
		double dare = _ttof(strText);
		dResult = 0;
	}

	return dResult;
}

void ConvertWidthTab::SetStaticValue(double dFirstValue)
{
	CString strFormat;
	// 처리
}

double ConvertWidthTab::ConvertSquaredKMeterToRight(double dFirstResult, CString& strSymbol)
{
	double dResult = 0;
	int nSel = m_combo_right.GetCurSel();
	// 처리

	SetStaticValue(dFirstResult);

	return dResult;
}

void ConvertWidthTab::SetComboButtonText(CString strSymbol)
{
	CString strFormatText, strLeftText, strRightText;
	int nLeftIdx = m_combo_left.GetCurSel();
	int nRightIdx = m_combo_right.GetCurSel();

	m_combo_left.GetLBText(nLeftIdx, strLeftText);
	m_combo_right.GetLBText(nRightIdx, strRightText);

	strFormatText.Format(_T("%s   ⇒   %s         %s"), strLeftText, strRightText, strSymbol);
	m_btn_combo.SetWindowTextW(strFormatText);
}

void ConvertWidthTab::SetTestButtonText()
{
	if (m_combo_left.GetCurSel() == 0)
	{
		m_btn_test.SetWindowTextW(_T("m²"));
	}
	else if (m_combo_left.GetCurSel() == 1)
	{
		m_btn_test.SetWindowTextW(_T("a"));
	}
	else if (m_combo_left.GetCurSel() == 2)
	{
		m_btn_test.SetWindowTextW(_T("ha"));
	}
	else if (m_combo_left.GetCurSel() == 3)
	{
		m_btn_test.SetWindowTextW(_T("km²"));
	}
	else if (m_combo_left.GetCurSel() == 4)
	{
		m_btn_test.SetWindowTextW(_T("ft²"));
	}
	else if (m_combo_left.GetCurSel() == 5)
	{
		m_btn_test.SetWindowTextW(_T("yd²"));
	}
	else if (m_combo_left.GetCurSel() == 6)
	{
		m_btn_test.SetWindowTextW(_T("ac"));
	}
	else if (m_combo_left.GetCurSel() == 7)
	{
		m_btn_test.SetWindowTextW(_T("평방자"));
	}
	else if (m_combo_left.GetCurSel() == 8)
	{
		m_btn_test.SetWindowTextW(_T("평"));
	}
	else if (m_combo_left.GetCurSel() == 9)
	{
		m_btn_test.SetWindowTextW(_T("단보"));
	}
	else if (m_combo_left.GetCurSel() == 10)
	{
		m_btn_test.SetWindowTextW(_T("정보"));
	}
}


void ConvertWidthTab::OnBnClickedButtonCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bComboShow)
	{
		m_combo_left.ShowWindow(SW_SHOW);
		m_combo_right.ShowWindow(SW_SHOW);
		bComboShow = true;
		SetComboButtonText(_T("▲"));
	}
	else
	{
		m_combo_left.ShowWindow(SW_HIDE);
		m_combo_right.ShowWindow(SW_HIDE);
		bComboShow = false;
		SetComboButtonText(_T("▼"));
	}
}


void ConvertWidthTab::OnCbnSelchangeComboLeft2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetComboButtonText(_T("▲"));
	SetTestButtonText();
	ConvertLength();
}


void ConvertWidthTab::OnCbnSelchangeComboRight2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_combo_left.ShowWindow(SW_HIDE);
	m_combo_right.ShowWindow(SW_HIDE);
	bComboShow = false;

	SetComboButtonText(_T("▼"));
	ConvertLength();
}


BOOL ConvertWidthTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (m_edit_left_value.m_bFocusOn)
	{
		CRect rect;
		m_edit_left_value.GetClientRect(rect);
		CDC* pDC = m_edit_left_value.GetWindowDC();
		pDC->Draw3dRect(rect, RGB(0, 0, 0), RGB(0, 0, 0));
	}

	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd != m_edit_left_value)
		{
			m_edit_left_value.m_bFocusOn = false;
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
			pDC->SetBkColor(RGB(250, 250, 250));
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
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_RIGHT_VALUE)
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

	ConvertLength();
}
