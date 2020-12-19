// ConvertWeightTab.cpp: 구현 파일
//

#include "pch.h"
#include "GojasTools.h"
#include "ConvertWeightTab.h"
#include "afxdialogex.h"


// ConvertWeightTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertWeightTab, CDialogEx)

ConvertWeightTab::ConvertWeightTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_WEIGHT, pParent)
{
	bComboShow = false;
}

ConvertWeightTab::~ConvertWeightTab()
{
}

void ConvertWeightTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ICON_WEIGHT, m_btn_icon);
	DDX_Control(pDX, IDC_BUTTON_COMBO3, m_btn_combo);
	DDX_Control(pDX, IDC_EDIT_LEFT_VALUE3, m_edit_left_value);
	DDX_Control(pDX, IDC_EDIT_RIGHT_VALUE3, m_edit_right_value);
	DDX_Control(pDX, IDC_BUTTON_CONTAINER3, m_btn_test1);
	DDX_Control(pDX, IDC_COMBO_LEFT3, m_combo_left);
	DDX_Control(pDX, IDC_COMBO_RIGHT3, m_combo_right);
	DDX_Control(pDX, IDC_STATIC_MG, m_stt_mg);
	DDX_Control(pDX, IDC_STATIC_G, m_stt_g);
	DDX_Control(pDX, IDC_STATIC_KG, m_stt_kg);
	DDX_Control(pDX, IDC_STATIC_T, m_stt_t);
	DDX_Control(pDX, IDC_STATIC_KT, m_stt_kt);
	DDX_Control(pDX, IDC_STATIC_GR, m_stt_gr);
	DDX_Control(pDX, IDC_STATIC_OZ, m_stt_oz);
	DDX_Control(pDX, IDC_STATIC_LB, m_stt_lb);
	DDX_Control(pDX, IDC_STATIC_DON, m_stt_don);
	DDX_Control(pDX, IDC_STATIC_NYANG, m_stt_nyang);
	DDX_Control(pDX, IDC_STATIC_GEUN, m_stt_geun);
	DDX_Control(pDX, IDC_STATIC_GUAN, m_stt_guan);
	DDX_Control(pDX, IDC_BUTTON_REVERSE2, m_btn_reverse);
	DDX_Control(pDX, IDC_STATIC_DIVIDE3, m_stt_divide);
}


BEGIN_MESSAGE_MAP(ConvertWeightTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMBO3, &ConvertWeightTab::OnBnClickedButtonCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO_LEFT3, &ConvertWeightTab::OnCbnSelchangeComboLeft3)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT3, &ConvertWeightTab::OnCbnSelchangeComboRight3)
	ON_EN_CHANGE(IDC_EDIT_LEFT_VALUE3, &ConvertWeightTab::OnEnChangeEditLeftValue3)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_REVERSE2, &ConvertWeightTab::OnBnClickedButtonReverse2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ConvertWeightTab 메시지 처리기


void ConvertWeightTab::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL ConvertWeightTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_backBrush.CreateSolidBrush(RGB(250, 250, 250));

	this->SetBackgroundColor(RGB(250, 250, 250));
	
	m_btn_icon.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_icon.InsertImage(IDB_PNG_WEIGHT_NOMAL);
	m_btn_reverse.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_SEMIFLAT);
	m_btn_reverse.InsertImage(IDB_PNG_REVERSE_NOMAL);
	m_btn_combo.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_combo.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_combo.SetWindowTextW(_T("테스트"));
	m_btn_combo.m_bUseMouseEvent = false;
	m_btn_test1.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_test1.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test1.m_bUseMouseEvent = false;

	m_edit_left_value.Initialize(18, _T("휴먼매직체"));
	m_edit_right_value.Initialize(20, _T("휴먼매직체"));

	m_stt_mg.Initialize(15, _T("휴먼매직체"));
	m_stt_g.Initialize(15, _T("휴먼매직체"));
	m_stt_kg.Initialize(15, _T("휴먼매직체"));
	m_stt_t.Initialize(15, _T("휴먼매직체"));
	m_stt_kt.Initialize(15, _T("휴먼매직체"));
	m_stt_gr.Initialize(15, _T("휴먼매직체"));
	m_stt_oz.Initialize(15, _T("휴먼매직체"));
	m_stt_lb.Initialize(15, _T("휴먼매직체"));
	m_stt_don.Initialize(15, _T("휴먼매직체"));
	m_stt_nyang.Initialize(15, _T("휴먼매직체"));
	m_stt_geun.Initialize(15, _T("휴먼매직체"));
	m_stt_guan.Initialize(15, _T("휴먼매직체"));

	m_combo_left.InsertString(0, _T("밀리그램 (mg)"));
	m_combo_left.InsertString(1, _T("그램 (g)"));
	m_combo_left.InsertString(2, _T("킬로그램 (kg)"));
	m_combo_left.InsertString(3, _T("톤 (t)"));
	m_combo_left.InsertString(4, _T("킬로톤 (kt)"));
	m_combo_left.InsertString(5, _T("그레인 (gr)"));
	m_combo_left.InsertString(6, _T("온스 (oz)"));
	m_combo_left.InsertString(7, _T("파운드 (lb)"));
	m_combo_left.InsertString(8, _T("돈"));
	m_combo_left.InsertString(9, _T("냥"));
	m_combo_left.InsertString(10, _T("근"));
	m_combo_left.InsertString(11, _T("관"));

	m_combo_right.InsertString(0, _T("밀리그램 (mg)"));
	m_combo_right.InsertString(1, _T("그램 (g)"));
	m_combo_right.InsertString(2, _T("킬로그램 (kg)"));
	m_combo_right.InsertString(3, _T("톤 (t)"));
	m_combo_right.InsertString(4, _T("킬로톤 (kt)"));
	m_combo_right.InsertString(5, _T("그레인 (gr)"));
	m_combo_right.InsertString(6, _T("온스 (oz)"));
	m_combo_right.InsertString(7, _T("파운드 (lb)"));
	m_combo_right.InsertString(8, _T("돈"));
	m_combo_right.InsertString(9, _T("냥"));
	m_combo_right.InsertString(10, _T("근"));
	m_combo_right.InsertString(11, _T("관"));

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_combo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test1.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_left_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_right_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_mg.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_g.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_kg.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_t.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_kt.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_gr.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_oz.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_lb.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_don.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_nyang.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_geun.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_guan.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test1.BringWindowToTop();
	m_stt_mg.BringWindowToTop();
	m_stt_g.BringWindowToTop();
	m_stt_kg.BringWindowToTop();
	m_stt_t.BringWindowToTop();
	m_stt_kt.BringWindowToTop();
	m_stt_gr.BringWindowToTop();
	m_stt_oz.BringWindowToTop();
	m_stt_lb.BringWindowToTop();
	m_stt_don.BringWindowToTop();
	m_stt_nyang.BringWindowToTop();
	m_stt_geun.BringWindowToTop();
	m_stt_guan.BringWindowToTop();
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
	ConvertWeight();

	m_combo_left.ShowWindow(SW_HIDE);
	m_combo_right.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ConvertWeightTab::ConvertWeight()
{
	CString strSymbol;
	double dFirstResult = ConvertLeftToKGram();
	double dLastResult = ConvertKGramToRight(dFirstResult, strSymbol);

	CString strResult;
	strResult.Format(_T("%g %s"), dLastResult, strSymbol);
	m_edit_right_value.SetWindowTextW(strResult);
}

double ConvertWeightTab::ConvertLeftToKGram()
{
	CString strText;
	m_edit_left_value.GetWindowTextW(strText);
	double dResult = 0;
	int nSel = m_combo_left.GetCurSel();
	// 처리
	if (nSel == 0)	// mg -> kg
	{
		double dmGram = _ttof(strText);
		dResult = dmGram / 1000000;
	}
	else if (nSel == 1) // g -> kg
	{
		double dGram = _ttof(strText);
		dResult = dGram / 1000;
	}
	else if (nSel == 2) // kg -> kg
	{
		double dkGram = _ttof(strText);
		dResult = dkGram;
	}
	else if (nSel == 3) // t -> kg
	{
		double dTon = _ttof(strText);
		dResult = dTon * 1000;
	}
	else if (nSel == 4) // kt -> kg
	{
		double dkTon = _ttof(strText);
		dResult = dkTon * 1000000;
	}
	else if (nSel == 5) // gr -> kg
	{
		double dGrain = _ttof(strText);
		dResult = (dGrain * 64.79891) / 1000000;
	}
	else if (nSel == 6) // oz -> kg
	{
		double dOnz = _ttof(strText);
		dResult = (dOnz * 28349.5231) / 1000000;
	}
	else if (nSel == 7) // lb -> kg
	{
		double dPound = _ttof(strText);
		dResult = (dPound * 453.59237) / 1000;
	}
	else if (nSel == 8) // 돈 -> kg
	{
		double dDon = _ttof(strText);
		dResult = (dDon * 3.75) / 1000;
	}
	else if (nSel == 9) // 냥 -> kg
	{
		double dNyang = _ttof(strText);
		dResult = (dNyang * 37.5) / 1000;
	}
	else if (nSel == 10) // 근 -> kg
	{
		double dGeun = _ttof(strText);
		dResult = (dGeun * 600) / 1000;
	}
	else if (nSel == 11) // 관 -> kg
	{
		double dGuan = _ttof(strText);
		dResult = dGuan * 3.75;
	}

	return dResult;
}

void ConvertWeightTab::SetStaticValue(double dFirstValue)
{
	CString strFormat;
	// 처리
	strFormat.Format(_T("%g mg"), dFirstValue * 1000000);
	m_stt_mg.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g g"), dFirstValue * 1000);
	m_stt_g.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g kg"), dFirstValue);
	m_stt_kg.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g t"), dFirstValue / 1000);
	m_stt_t.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g kt"), dFirstValue / 1000000);
	m_stt_kt.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g gr"), dFirstValue * 15432.3584);
	m_stt_gr.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g oz"), dFirstValue * 35.2739619);
	m_stt_oz.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g lb"), dFirstValue * 2.20462262);
	m_stt_lb.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 돈"), dFirstValue * 266.666667);
	m_stt_don.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 냥"), dFirstValue * 26.6666667);
	m_stt_nyang.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 근"), dFirstValue * 1.66666667);
	m_stt_geun.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g 관"), dFirstValue * 0.266666667);
	m_stt_guan.SetWindowTextW(strFormat);
}

double ConvertWeightTab::ConvertKGramToRight(double dFirstResult, CString& strSymbol)
{
	double dResult = 0;
	int nSel = m_combo_right.GetCurSel();
	// 처리
	if (nSel == 0)	// kg -> mg
	{
		dResult = dFirstResult * 1000000;
		strSymbol = _T("mg");
	}
	else if (nSel == 1) // kg -> g
	{
		dResult = dFirstResult * 1000;
		strSymbol = _T("g");
	}
	else if (nSel == 2) // kg -> kg
	{
		dResult = dFirstResult;
		strSymbol = _T("kg");
	}
	else if (nSel == 3) // kg -> t
	{
		dResult = dFirstResult / 1000;
		strSymbol = _T("t");
	}
	else if (nSel == 4) // kg -> kt
	{
		dResult = dFirstResult / 1000000;
		strSymbol = _T("kt");
	}
	else if (nSel == 5) // kg -> gr
	{
		dResult = dFirstResult * 15432.3584;
		strSymbol = _T("gr");
	}
	else if (nSel == 6) // kg -> oz
	{
		dResult = dFirstResult * 35.2739619;
		strSymbol = _T("oz");
	}
	else if (nSel == 7) // kg -> lb
	{
		dResult = dFirstResult * 2.20462262;
		strSymbol = _T("lb");
	}
	else if (nSel == 8) // kg -> 돈
	{
		dResult = dFirstResult * 266.666667;
		strSymbol = _T("돈");
	}
	else if (nSel == 9) // kg -> 냥
	{
		dResult = dFirstResult * 26.6666667;
		strSymbol = _T("냥");
	}
	else if (nSel == 10) // kg -> 근
	{
		dResult = dFirstResult * 1.66666667;
		strSymbol = _T("근");
	}
	else if (nSel == 11) // kg -> 관
	{
		dResult = dFirstResult * 0.266666667;
		strSymbol = _T("관");
	}

	SetStaticValue(dFirstResult);

	return dResult;
}

void ConvertWeightTab::SetComboButtonText(CString strSymbol)
{
	CString strFormatText, strLeftText, strRightText;
	int nLeftIdx = m_combo_left.GetCurSel();
	int nRightIdx = m_combo_right.GetCurSel();

	m_combo_left.GetLBText(nLeftIdx, strLeftText);
	m_combo_right.GetLBText(nRightIdx, strRightText);

	strFormatText.Format(_T("%s   ⇒   %s         %s"), strLeftText, strRightText, strSymbol);
	m_btn_combo.SetWindowTextW(strFormatText);
}

void ConvertWeightTab::SetTestButtonText()
{
	if (m_combo_left.GetCurSel() == 0)
	{
		m_btn_test1.SetWindowTextW(_T("mg"));
	}
	else if (m_combo_left.GetCurSel() == 1)
	{
		m_btn_test1.SetWindowTextW(_T("g"));
	}
	else if (m_combo_left.GetCurSel() == 2)
	{
		m_btn_test1.SetWindowTextW(_T("kg"));
	}
	else if (m_combo_left.GetCurSel() == 3)
	{
		m_btn_test1.SetWindowTextW(_T("t"));
	}
	else if (m_combo_left.GetCurSel() == 4)
	{
		m_btn_test1.SetWindowTextW(_T("kt"));
	}
	else if (m_combo_left.GetCurSel() == 5)
	{
		m_btn_test1.SetWindowTextW(_T("gr"));
	}
	else if (m_combo_left.GetCurSel() == 6)
	{
		m_btn_test1.SetWindowTextW(_T("oz"));
	}
	else if (m_combo_left.GetCurSel() == 7)
	{
		m_btn_test1.SetWindowTextW(_T("lb"));
	}
	else if (m_combo_left.GetCurSel() == 8)
	{
		m_btn_test1.SetWindowTextW(_T("돈"));
	}
	else if (m_combo_left.GetCurSel() == 9)
	{
		m_btn_test1.SetWindowTextW(_T("냥"));
	}
	else if (m_combo_left.GetCurSel() == 10)
	{
		m_btn_test1.SetWindowTextW(_T("근"));
	}
	else if (m_combo_left.GetCurSel() == 11)
	{
		m_btn_test1.SetWindowTextW(_T("관"));
	}
}

void ConvertWeightTab::OnBnClickedButtonCombo3()
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


void ConvertWeightTab::OnCbnSelchangeComboLeft3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetComboButtonText(_T("▲"));
	SetTestButtonText();
	ConvertWeight();
}


void ConvertWeightTab::OnCbnSelchangeComboRight3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_combo_left.ShowWindow(SW_HIDE);
	m_combo_right.ShowWindow(SW_HIDE);
	bComboShow = false;

	SetComboButtonText(_T("▼"));
	ConvertWeight();
}


void ConvertWeightTab::OnEnChangeEditLeftValue3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ConvertWeight();
}


BOOL ConvertWeightTab::PreTranslateMessage(MSG* pMsg)
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
		m_edit_left_value.Invalidate();
		if (pMsg->hwnd != m_edit_left_value)
		{
			m_edit_left_value.m_bFocusOn = false;
			m_edit_left_value.HideCaret();
		}
		if (pMsg->hwnd == m_edit_right_value)
		{
			m_edit_right_value.HideCaret();
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


HBRUSH ConvertWeightTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_LEFT_VALUE3)
		{
			pDC->SetBkColor(RGB(250, 250, 250));
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MG)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_G)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_KG)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_T)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_KT)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_GR)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_OZ)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_LB)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_DON)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_NYANG)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_GEUN)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_GUAN)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_RIGHT_VALUE3)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void ConvertWeightTab::OnBnClickedButtonReverse2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nLeftSel = m_combo_left.GetCurSel();
	int nRightSel = m_combo_right.GetCurSel();

	m_combo_left.SetCurSel(nRightSel);
	m_combo_right.SetCurSel(nLeftSel);
	SetComboButtonText(_T("▼"));
	SetTestButtonText();
	ConvertWeight();
}

void ConvertWeightTab::CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth /* = 1*/)
{
	if (nDepth > 3)
		return;

	CRect controlRect, controlToMarginRect1, controlToMarginRect2;

	if (nDepth == 1)
	{
		m_stt_mg.GetWindowRect(&controlToMarginRect1);
		m_stt_t.GetWindowRect(&controlToMarginRect2);
		m_stt_mg.GetClientRect(&controlRect);
	}
	else if (nDepth == 2)
	{
		m_stt_t.GetWindowRect(&controlToMarginRect1);
		m_stt_oz.GetWindowRect(&controlToMarginRect2);
		m_stt_t.GetClientRect(&controlRect);
	}
	else
	{
		m_stt_oz.GetWindowRect(&controlToMarginRect1);
		m_stt_nyang.GetWindowRect(&controlToMarginRect2);
		m_stt_oz.GetClientRect(&controlRect);
	}

	int nMargin = controlToMarginRect2.top - controlToMarginRect1.bottom;

	int nStart_x = controlRect.left + 15;
	int nStart_y = nStartValue_y + nStartMargin + controlRect.Height() + (nMargin / 2);
	int nEnd_x = (controlRect.left + controlRect.Width()) * 3;

	LOGBRUSH lb;

	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(200, 200, 200);

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

void ConvertWeightTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect divideRect;
	m_stt_divide.GetClientRect(&divideRect);

	CRect divideToMargin1, divideToMargin2;
	m_stt_divide.GetWindowRect(&divideToMargin1);
	m_stt_mg.GetWindowRect(&divideToMargin2);
	int nDivideMargin = divideToMargin2.top - divideToMargin1.bottom;

	CalcDrawLine(&dc, divideRect.top + divideRect.Height(), nDivideMargin);
}
