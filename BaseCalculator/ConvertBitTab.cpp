// ConvertBitTab.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "ConvertBitTab.h"
#include "afxdialogex.h"


// ConvertBitTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertBitTab, CDialogEx)

ConvertBitTab::ConvertBitTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_BIT, pParent)
{
	bComboShow = false;
}

ConvertBitTab::~ConvertBitTab()
{
}

void ConvertBitTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ICON_BIT, m_btn_icon);
	DDX_Control(pDX, IDC_BUTTON_COMBO4, m_btn_combo);
	DDX_Control(pDX, IDC_COMBO_LEFT4, m_combo_left);
	DDX_Control(pDX, IDC_COMBO_RIGHT4, m_combo_right);
	DDX_Control(pDX, IDC_BUTTON_TEST4, m_btn_test);
	DDX_Control(pDX, IDC_EDIT_LEFT_VALUE4, m_edit_left_value);
	DDX_Control(pDX, IDC_EDIT_RIGHT_VALUE4, m_edit_right_value);
	DDX_Control(pDX, IDC_STATIC_BIT, m_stt_bit);
	DDX_Control(pDX, IDC_STATIC_BYTE, m_stt_byte);
	DDX_Control(pDX, IDC_STATIC_KBYTE, m_stt_kbyte);
	DDX_Control(pDX, IDC_STATIC_MBYTE, m_stt_mbyte);
	DDX_Control(pDX, IDC_STATIC_GBYTE, m_stt_gbyte);
	DDX_Control(pDX, IDC_STATIC_TBYTE, m_stt_tbyte);
	DDX_Control(pDX, IDC_STATIC_PBTYE, m_stt_pbyte);
	DDX_Control(pDX, IDC_STATIC_EBYTE, m_stt_ebyte);
}


BEGIN_MESSAGE_MAP(ConvertBitTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMBO4, &ConvertBitTab::OnBnClickedButtonCombo4)
	ON_EN_CHANGE(IDC_EDIT_LEFT_VALUE4, &ConvertBitTab::OnEnChangeEditLeftValue4)
	ON_CBN_SELCHANGE(IDC_COMBO_LEFT4, &ConvertBitTab::OnCbnSelchangeComboLeft4)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT4, &ConvertBitTab::OnCbnSelchangeComboRight4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ConvertBitTab 메시지 처리기


void ConvertBitTab::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL ConvertBitTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_backBrush.CreateSolidBrush(RGB(250, 250, 250));

	this->SetBackgroundColor(RGB(250, 250, 250));

	m_btn_icon.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_icon.InsertImage(IDB_PNG_BIT_NOMAL);
	m_btn_combo.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_combo.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_combo.SetWindowTextW(_T("테스트"));
	m_btn_combo.m_bUseMouseEvent = false;
	m_btn_test.Initialize(RGB(250, 250, 250), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"));
	m_btn_test.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_test.m_bUseMouseEvent = false;

	m_edit_left_value.Initialize(13, _T("휴먼매직체"));
	m_edit_right_value.Initialize(15, _T("휴먼매직체"));

	m_stt_bit.Initialize(14, _T("휴먼매직체"));
	m_stt_byte.Initialize(14, _T("휴먼매직체"));
	m_stt_kbyte.Initialize(14, _T("휴먼매직체"));
	m_stt_mbyte.Initialize(14, _T("휴먼매직체"));
	m_stt_gbyte.Initialize(14, _T("휴먼매직체"));
	m_stt_tbyte.Initialize(14, _T("휴먼매직체"));
	m_stt_pbyte.Initialize(14, _T("휴먼매직체"));
	m_stt_ebyte.Initialize(14, _T("휴먼매직체"));

	m_combo_left.InsertString(0, _T("비트 (bit)"));
	m_combo_left.InsertString(1, _T("바이트 (B)"));
	m_combo_left.InsertString(2, _T("킬로바이트 (KB)"));
	m_combo_left.InsertString(3, _T("메가바이트 (MB)"));
	m_combo_left.InsertString(4, _T("기가바이트 (GB)"));
	m_combo_left.InsertString(5, _T("테라바이트 (TB)"));
	m_combo_left.InsertString(6, _T("페타바이트 (PB)"));
	m_combo_left.InsertString(7, _T("엑사바이트 (EB)"));

	m_combo_right.InsertString(0, _T("비트 (bit)"));
	m_combo_right.InsertString(1, _T("바이트 (B)"));
	m_combo_right.InsertString(2, _T("킬로바이트 (KB)"));
	m_combo_right.InsertString(3, _T("메가바이트 (MB)"));
	m_combo_right.InsertString(4, _T("기가바이트 (GB)"));
	m_combo_right.InsertString(5, _T("테라바이트 (TB)"));
	m_combo_right.InsertString(6, _T("페타바이트 (PB)"));
	m_combo_right.InsertString(7, _T("엑사바이트 (EB)"));

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_combo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_test.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_left_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_right_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_combo_right.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_bit.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_byte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_kbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_mbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_gbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_tbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_pbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_ebyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_bit.BringWindowToTop();
	m_stt_byte.BringWindowToTop();
	m_stt_kbyte.BringWindowToTop();
	m_stt_mbyte.BringWindowToTop();
	m_stt_gbyte.BringWindowToTop();
	m_stt_tbyte.BringWindowToTop();
	m_stt_pbyte.BringWindowToTop();
	m_stt_ebyte.BringWindowToTop();
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

void ConvertBitTab::ConvertLength()
{
	CString strSymbol;
	double dFirstResult = ConvertLeftToMByte();
	double dLastResult = ConvertMByteToRight(dFirstResult, strSymbol);

	CString strResult;
	strResult.Format(_T("%g %s"), dLastResult, strSymbol);
	m_edit_right_value.SetWindowTextW(strResult);
}

double ConvertBitTab::ConvertLeftToMByte()
{
	CString strText;
	m_edit_left_value.GetWindowTextW(strText);
	double dResult = 0;
	int nSel = m_combo_left.GetCurSel();
	// 처리
	if (nSel == 0)	// bit -> mb
	{
		double dmGram = _ttof(strText);
		dResult = 0;
	}
	else if (nSel == 1) // b -> mb
	{
		double dGram = _ttof(strText);
		dResult = 0;
	}
	else if (nSel == 2) // kb -> mb
	{
		double dkGram = _ttof(strText);
		dResult = 0;
	}
	else if (nSel == 3) // mb -> mb
	{
		double dTon = _ttof(strText);
		dResult = 0;
	}
	else if (nSel == 4) // gb -> mb
	{
		double dkTon = _ttof(strText);
		dResult = 0;
	}
	else if (nSel == 5) // tb -> mb
	{
		double dGrain = _ttof(strText);
		dResult = 0;
	}
	else if (nSel == 6) // pb -> mb
	{
		double dOnz = _ttof(strText);
		dResult = 0;
	}
	else if (nSel == 7) // eb -> mb
	{
		double dPound = _ttof(strText);
		dResult = 0;
	}

	return dResult;
}

void ConvertBitTab::SetStaticValue(double dFirstValue)
{
	CString strFormat;
	// 처리
	strFormat.Format(_T("%g bit"), 0);
	m_stt_bit.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g B"), 0);
	m_stt_byte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g KB"), 0);
	m_stt_kbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g MB"), 0);
	m_stt_mbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g GB"), 0);
	m_stt_gbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g TB"), 0);
	m_stt_tbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g PB"), 0);
	m_stt_pbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g EB"), 0);
	m_stt_ebyte.SetWindowTextW(strFormat);
}

double ConvertBitTab::ConvertMByteToRight(double dFirstResult, CString& strSymbol)
{
	double dResult = 0;
	int nSel = m_combo_right.GetCurSel();
	// 처리
	if (nSel == 0)	// mb -> bit
	{
		dResult = 0;
		strSymbol = _T("bit");
	}
	else if (nSel == 1) // mb -> b
	{
		dResult = 0;
		strSymbol = _T("B");
	}
	else if (nSel == 2) // mb -> kb
	{
		dResult = 0;
		strSymbol = _T("KB");
	}
	else if (nSel == 3) // mb -> mb
	{
		dResult = 0;
		strSymbol = _T("MB");
	}
	else if (nSel == 4) // mb -> gb
	{
		dResult = 0;
		strSymbol = _T("GB");
	}
	else if (nSel == 5) // mb -> tb
	{
		dResult = 0;
		strSymbol = _T("TB");
	}
	else if (nSel == 6) // mb -> pb
	{
		dResult = 0;
		strSymbol = _T("PB");
	}
	else if (nSel == 7) // mb -> eb
	{
		dResult = 0;
		strSymbol = _T("EB");
	}

	SetStaticValue(dFirstResult);

	return dResult;
}

void ConvertBitTab::SetComboButtonText(CString strSymbol)
{
	CString strFormatText, strLeftText, strRightText;
	int nLeftIdx = m_combo_left.GetCurSel();
	int nRightIdx = m_combo_right.GetCurSel();

	m_combo_left.GetLBText(nLeftIdx, strLeftText);
	m_combo_right.GetLBText(nRightIdx, strRightText);

	strFormatText.Format(_T("%s   ⇒   %s         %s"), strLeftText, strRightText, strSymbol);
	m_btn_combo.SetWindowTextW(strFormatText);
}

void ConvertBitTab::SetTestButtonText()
{
	if (m_combo_left.GetCurSel() == 0)
	{
		m_btn_test.SetWindowTextW(_T("bit"));
	}
	else if (m_combo_left.GetCurSel() == 1)
	{
		m_btn_test.SetWindowTextW(_T("B"));
	}
	else if (m_combo_left.GetCurSel() == 2)
	{
		m_btn_test.SetWindowTextW(_T("KB"));
	}
	else if (m_combo_left.GetCurSel() == 3)
	{
		m_btn_test.SetWindowTextW(_T("MB"));
	}
	else if (m_combo_left.GetCurSel() == 4)
	{
		m_btn_test.SetWindowTextW(_T("GB"));
	}
	else if (m_combo_left.GetCurSel() == 5)
	{
		m_btn_test.SetWindowTextW(_T("TB"));
	}
	else if (m_combo_left.GetCurSel() == 6)
	{
		m_btn_test.SetWindowTextW(_T("PB"));
	}
	else if (m_combo_left.GetCurSel() == 7)
	{
		m_btn_test.SetWindowTextW(_T("EB"));
	}
}

void ConvertBitTab::OnBnClickedButtonCombo4()
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


void ConvertBitTab::OnEnChangeEditLeftValue4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ConvertLength();
}


void ConvertBitTab::OnCbnSelchangeComboLeft4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetComboButtonText(_T("▲"));
	SetTestButtonText();
	ConvertLength();
}


void ConvertBitTab::OnCbnSelchangeComboRight4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_combo_left.ShowWindow(SW_HIDE);
	m_combo_right.ShowWindow(SW_HIDE);
	bComboShow = false;

	SetComboButtonText(_T("▼"));
	ConvertLength();
}


BOOL ConvertBitTab::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_edit_left_value.m_bFocusOn)
	{
		CRect rect;
		m_edit_left_value.GetClientRect(rect);
		CDC* pDC = m_edit_left_value.GetWindowDC();
		pDC->Draw3dRect(rect, RGB(0, 0, 0), RGB(0, 0, 0));
	}

	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_combo)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
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


HBRUSH ConvertBitTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_LEFT_VALUE4)
		{
			pDC->SetBkColor(RGB(250, 250, 250));
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_BIT)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_BYTE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_KBYTE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_MBYTE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_GBYTE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TBYTE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_PBTYE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_EBYTE)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_RIGHT_VALUE4)
		{
			pDC->SetTextColor(RGB(236, 130, 60));
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
