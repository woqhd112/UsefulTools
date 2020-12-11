// ConvertLengthTab.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "ConvertLengthTab.h"
#include "afxdialogex.h"


// ConvertLengthTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertLengthTab, CDialogEx)

ConvertLengthTab::ConvertLengthTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_LENGTH, pParent)
{
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
	DDX_Control(pDX, IDC_COMBO_RIGHT, m_combo_right);
	DDX_Control(pDX, IDC_EDIT_LEFT_VALUE, m_edit_left_value);
	DDX_Control(pDX, IDC_EDIT_RIGHT_VALUE, m_edit_right_value);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_btn_test);
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
}


BEGIN_MESSAGE_MAP(ConvertLengthTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMBO, &ConvertLengthTab::OnBnClickedButtonCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_LEFT, &ConvertLengthTab::OnCbnSelchangeComboLeft)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT, &ConvertLengthTab::OnCbnSelchangeComboRight)
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_LEFT_VALUE, &ConvertLengthTab::OnEnChangeEditLeftValue)
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

	m_backBrush.CreateSolidBrush(RGB(250, 250, 250));

	this->SetBackgroundColor(RGB(250, 250, 250));

	m_btn_icon.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_icon.InsertImage(IDB_PNG_LENGTH_NOMAL);
	m_btn_combo.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_combo.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_combo.SetWindowTextW(_T("테스트"));
	m_btn_combo.m_bUseMouseEvent = false;
	m_btn_test.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_test.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test.m_bUseMouseEvent = false;

	m_stt_mm.Initialize(18, _T("휴먼매직체"));
	m_stt_cm.Initialize(18, _T("휴먼매직체"));
	m_stt_m.Initialize(18, _T("휴먼매직체"));
	m_stt_km.Initialize(18, _T("휴먼매직체"));
	m_stt_in.Initialize(18, _T("휴먼매직체"));
	m_stt_ft.Initialize(18, _T("휴먼매직체"));
	m_stt_yd.Initialize(18, _T("휴먼매직체"));
	m_stt_miles.Initialize(18, _T("휴먼매직체"));
	m_stt_ja.Initialize(18, _T("휴먼매직체"));
	m_stt_gan.Initialize(18, _T("휴먼매직체"));
	m_stt_jung.Initialize(18, _T("휴먼매직체"));
	m_stt_lee.Initialize(18, _T("휴먼매직체"));
	m_stt_haelee.Initialize(18, _T("휴먼매직체"));

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

	m_combo_right.InsertString(0, _T("밀리미터 (mm)"));
	m_combo_right.InsertString(1, _T("센티미터 (cm)"));
	m_combo_right.InsertString(2, _T("미터 (m)"));
	m_combo_right.InsertString(3, _T("킬로미터 (km)"));
	m_combo_right.InsertString(4, _T("인치 (in)"));
	m_combo_right.InsertString(5, _T("피트 (ft)"));
	m_combo_right.InsertString(6, _T("야드 (yd)"));
	m_combo_right.InsertString(7, _T("마일 (mile)"));
	m_combo_right.InsertString(8, _T("자 (尺)"));
	m_combo_right.InsertString(9, _T("간 (間)"));
	m_combo_right.InsertString(10, _T("정 (町)"));
	m_combo_right.InsertString(11, _T("리 (里)"));
	m_combo_right.InsertString(12, _T("해리 (海里)"));

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_combo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_left_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_edit_left_value.BringWindowToTop();
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


void ConvertLengthTab::OnBnClickedButtonCombo()
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



void ConvertLengthTab::OnCbnSelchangeComboLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetComboButtonText(_T("▲"));
	SetTestButtonText();
}


void ConvertLengthTab::OnCbnSelchangeComboRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_combo_left.ShowWindow(SW_HIDE);
	m_combo_right.ShowWindow(SW_HIDE);
	bComboShow = false;

	SetComboButtonText(_T("▼"));
	ConvertLength();
}

void ConvertLengthTab::ConvertLength()
{
	double dFirstResult = ConvertLeftToMeter();
	double dLastResult = ConvertMeterToRight(dFirstResult);

	CString strResult;
	strResult.Format(_T("%g"), dLastResult);
	m_edit_right_value.SetWindowTextW(strResult);
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

double ConvertLengthTab::ConvertMeterToRight(double dFirstResult)
{
	double dResult = 0;
	int nSel = m_combo_right.GetCurSel();

	if (nSel == 0) // m -> mm
	{
		dResult = dFirstResult * 100 * 10;
	}
	else if (nSel == 1) // m -> cm
	{
		dResult = dFirstResult * 100;
	}
	else if (nSel == 2) // m -> m
	{
		dResult = dFirstResult;
	}
	else if (nSel == 3) // m -> km
	{
		dResult = dFirstResult / 1000;
	}
	else if (nSel == 4) // m -> inch
	{
		dResult = dFirstResult * 39.370079;
	}
	else if (nSel == 5) // m -> feet
	{
		dResult = dFirstResult * 3.28084;
	}
	else if (nSel == 6) // m -> yard
	{
		dResult = dFirstResult * 1.093613;
	}
	else if (nSel == 7) // m -> mile
	{
		dResult = (dFirstResult * 0.621371) / 1000;
	}
	else if (nSel == 8) // m -> ja
	{
		dResult = dFirstResult * 3.3;
	}
	else if (nSel == 9) // m -> gan
	{
		dResult = dFirstResult * 0.55;
	}
	else if (nSel == 10) // m -> jung
	{
		dResult = (dFirstResult * 9.166667) / 1000;
	}
	else if (nSel == 11) // m -> lee
	{
		dResult = (dFirstResult * 2.546296) / 1000;
	}
	else // m -> haelee
	{
		dResult = (dFirstResult * 0.539957) / 1000;
	}

	return dResult;
}

void ConvertLengthTab::SetComboButtonText(CString strSymbol)
{
	CString strFormatText, strLeftText, strRightText;
	int nLeftIdx = m_combo_left.GetCurSel();
	int nRightIdx = m_combo_right.GetCurSel();

	m_combo_left.GetLBText(nLeftIdx, strLeftText);
	m_combo_right.GetLBText(nRightIdx, strRightText);

	strFormatText.Format(_T("%s   ⇒   %s         %s"), strLeftText, strRightText, strSymbol);
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
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_edit_left_value)
		{
			CRect rect;
			m_edit_left_value.GetClientRect(rect);
			CDC* pDC = m_edit_left_value.GetWindowDC();
			pDC->Draw3dRect(rect, RGB(0, 0, 0), RGB(0, 0, 0));
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


HBRUSH ConvertLengthTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_LEFT_VALUE)
		{
			pDC->SetBkColor(RGB(250, 250, 250));
			hbr = (HBRUSH)m_backBrush;
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

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
