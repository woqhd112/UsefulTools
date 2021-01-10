// ConvertBitTab.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "ConvertBitTab.h"
#include "afxdialogex.h"


// ConvertBitTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertBitTab, CDialogEx)

ConvertBitTab::ConvertBitTab(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_BIT, pParent)
{
	this->currentTheme = currentTheme;
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
	DDX_Control(pDX, IDC_EDIT_LEFT_VALUE4, m_edit_left_value);
	DDX_Control(pDX, IDC_STATIC_BIT, m_stt_bit);
	DDX_Control(pDX, IDC_STATIC_BYTE, m_stt_byte);
	DDX_Control(pDX, IDC_STATIC_KBYTE, m_stt_kbyte);
	DDX_Control(pDX, IDC_STATIC_MBYTE, m_stt_mbyte);
	DDX_Control(pDX, IDC_STATIC_GBYTE, m_stt_gbyte);
	DDX_Control(pDX, IDC_STATIC_TBYTE, m_stt_tbyte);
	DDX_Control(pDX, IDC_STATIC_PBTYE, m_stt_pbyte);
	DDX_Control(pDX, IDC_STATIC_EBYTE, m_stt_ebyte);
	DDX_Control(pDX, IDC_BUTTON_CONTAINER4, m_btn_container);
	DDX_Control(pDX, IDC_STATIC_DIVIDE4, m_stt_divide);
}


BEGIN_MESSAGE_MAP(ConvertBitTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COMBO4, &ConvertBitTab::OnBnClickedButtonCombo4)
	ON_EN_CHANGE(IDC_EDIT_LEFT_VALUE4, &ConvertBitTab::OnEnChangeEditLeftValue4)
	ON_CBN_SELCHANGE(IDC_COMBO_LEFT4, &ConvertBitTab::OnCbnSelchangeComboLeft4)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT4, &ConvertBitTab::OnCbnSelchangeComboRight4)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
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

	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());

	m_btn_icon.LoadStdImage(IDB_PNG_CONVERT_BIT_NOMAL, _T("PNG"));
	m_btn_icon.LoadHovImage(IDB_PNG_CONVERT_BIT_HOVER, _T("PNG"));
	m_btn_icon.LoadAltImage(IDB_PNG_CONVERT_BIT_CLICK, _T("PNG"));
	m_btn_icon.MoveWindow(5, 5, 24, 24);


	m_btn_combo.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("휴먼매직체"), 14);
	m_btn_combo.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_combo.m_bUseMouseBkGroundColorEvent = false;
	m_btn_container.Initialize(currentTheme->GetFunctionSubColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("굴림"), 14);
	m_btn_container.SetAlignment(CMFCButton::AlignStyle::ALIGN_RIGHT);
	m_btn_container.m_bUseMouseBkGroundColorEvent = false;
	m_btn_combo.SetTextColor(currentTheme->GetFunctionTextColor());
	m_btn_container.SetTextColor(currentTheme->GetFunctionTextColor());

	m_edit_left_value.Initialize(18, _T("휴먼매직체"));

	m_stt_bit.Initialize(15, _T("휴먼매직체"));
	m_stt_byte.Initialize(15, _T("휴먼매직체"));
	m_stt_kbyte.Initialize(15, _T("휴먼매직체"));
	m_stt_mbyte.Initialize(15, _T("휴먼매직체"));
	m_stt_gbyte.Initialize(15, _T("휴먼매직체"));
	m_stt_tbyte.Initialize(15, _T("휴먼매직체"));
	m_stt_pbyte.Initialize(15, _T("휴먼매직체"));
	m_stt_ebyte.Initialize(15, _T("휴먼매직체"));

	m_combo_left.InsertString(0, _T("비트 (bit)"));
	m_combo_left.InsertString(1, _T("바이트 (B)"));
	m_combo_left.InsertString(2, _T("킬로바이트 (KB)"));
	m_combo_left.InsertString(3, _T("메가바이트 (MB)"));
	m_combo_left.InsertString(4, _T("기가바이트 (GB)"));
	m_combo_left.InsertString(5, _T("테라바이트 (TB)"));
	m_combo_left.InsertString(6, _T("페타바이트 (PB)"));
	m_combo_left.InsertString(7, _T("엑사바이트 (EB)"));

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_combo.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_container.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_left_value.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_combo_left.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_bit.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_byte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_kbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_mbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_gbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_tbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_pbyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_ebyte.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_btn_container.BringWindowToTop();
	m_stt_bit.BringWindowToTop();
	m_stt_byte.BringWindowToTop();
	m_stt_kbyte.BringWindowToTop();
	m_stt_mbyte.BringWindowToTop();
	m_stt_gbyte.BringWindowToTop();
	m_stt_tbyte.BringWindowToTop();
	m_stt_pbyte.BringWindowToTop();
	m_stt_ebyte.BringWindowToTop();
	m_edit_left_value.BringWindowToTop();
	m_combo_left.BringWindowToTop();
	m_btn_combo.BringWindowToTop();
	m_combo_left.SetCurSel(1);

	SetComboButtonText(_T("▼"));
	SetTestButtonText();

	m_edit_left_value.SetWindowTextW(_T("1"));
	ConvertBit();

	m_combo_left.ShowWindow(SW_HIDE);

	CRect borderRect, thisRect;
	m_btn_container.GetWindowRect(borderRect);
	this->GetWindowRect(thisRect);
	int nLeft = int(borderRect.left - thisRect.left - 2);
	int nTop = int(borderRect.top - thisRect.top - 2);
	drawBorderRect = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };

	m_btn_combo.GetWindowRect(borderRect);
	nLeft = int(borderRect.left - thisRect.left - 2);
	nTop = int(borderRect.top - thisRect.top - 2);
	drawComboBorderRect = { nLeft, nTop, nLeft + borderRect.Width() + 2, nTop + borderRect.Height() + 2 };

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ConvertBitTab::ConvertBit()
{
	CString strSymbol;
	double dFirstResult = ConvertLeftToMByte();
	SetStaticValue(dFirstResult);
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
		double dBit = _ttof(strText);
		dResult = dBit / 8 / 1024 / 1024;
	}
	else if (nSel == 1) // b -> mb
	{
		double dByte = _ttof(strText);
		dResult = dByte / 1024 / 1024;
	}
	else if (nSel == 2) // kb -> mb
	{
		double dkByte = _ttof(strText);
		dResult = dkByte / 1024;
	}
	else if (nSel == 3) // mb -> mb
	{
		double dmByte = _ttof(strText);
		dResult = dmByte;
	}
	else if (nSel == 4) // gb -> mb
	{
		double dgByte = _ttof(strText);
		dResult = dgByte * 1024;
	}
	else if (nSel == 5) // tb -> mb
	{
		double dtByte = _ttof(strText);
		dResult = dtByte * 1024 * 1024;
	}
	else if (nSel == 6) // pb -> mb
	{
		double dpByte = _ttof(strText);
		dResult = dpByte * 1024 * 1024 * 1024;
	}
	else if (nSel == 7) // eb -> mb
	{
		double deByte = _ttof(strText);
		dResult = deByte * 1024 * 1024 * 1024 * 1024;
	}

	return dResult;
}

void ConvertBitTab::SetStaticValue(double dFirstValue)
{
	CString strFormat;
	// 처리
	strFormat.Format(_T("%g bit"), dFirstValue * 1024 * 1024 * 8);
	m_stt_bit.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g B"), dFirstValue * 1024 * 1024);
	m_stt_byte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g KB"), dFirstValue * 1024);
	m_stt_kbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g MB"), dFirstValue);
	m_stt_mbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g GB"), dFirstValue / 1024);
	m_stt_gbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g TB"), dFirstValue / 1024 / 1024);
	m_stt_tbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g PB"), dFirstValue / 1024 / 1024 / 1024);
	m_stt_pbyte.SetWindowTextW(strFormat);

	strFormat.Format(_T("%g EB"), dFirstValue / 1024 / 1024 / 1024 / 1024);
	m_stt_ebyte.SetWindowTextW(strFormat);
}


void ConvertBitTab::SetComboButtonText(CString strSymbol)
{
	CString strFormatText, strLeftText;
	int nLeftIdx = m_combo_left.GetCurSel();

	m_combo_left.GetLBText(nLeftIdx, strLeftText);

	strFormatText.Format(_T("%s        %s"), strLeftText, strSymbol);
	m_btn_combo.SetWindowTextW(strFormatText);
}

void ConvertBitTab::SetTestButtonText()
{
	if (m_combo_left.GetCurSel() == 0)
	{
		m_btn_container.SetWindowTextW(_T("bit"));
	}
	else if (m_combo_left.GetCurSel() == 1)
	{
		m_btn_container.SetWindowTextW(_T("B"));
	}
	else if (m_combo_left.GetCurSel() == 2)
	{
		m_btn_container.SetWindowTextW(_T("KB"));
	}
	else if (m_combo_left.GetCurSel() == 3)
	{
		m_btn_container.SetWindowTextW(_T("MB"));
	}
	else if (m_combo_left.GetCurSel() == 4)
	{
		m_btn_container.SetWindowTextW(_T("GB"));
	}
	else if (m_combo_left.GetCurSel() == 5)
	{
		m_btn_container.SetWindowTextW(_T("TB"));
	}
	else if (m_combo_left.GetCurSel() == 6)
	{
		m_btn_container.SetWindowTextW(_T("PB"));
	}
	else if (m_combo_left.GetCurSel() == 7)
	{
		m_btn_container.SetWindowTextW(_T("EB"));
	}
}

void ConvertBitTab::OnBnClickedButtonCombo4()
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


void ConvertBitTab::OnEnChangeEditLeftValue4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ConvertBit();
}


void ConvertBitTab::OnCbnSelchangeComboLeft4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetComboButtonText(_T("▲"));
	SetTestButtonText();
	ConvertBit();
}


void ConvertBitTab::OnCbnSelchangeComboRight4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_combo_left.ShowWindow(SW_HIDE);
	bComboShow = false;

	SetComboButtonText(_T("▼"));
	ConvertBit();
}


BOOL ConvertBitTab::PreTranslateMessage(MSG* pMsg)
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
			pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			pDC->SetTextColor(currentTheme->GetFunctionTextColor());
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
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void ConvertBitTab::CalcDrawLine(CPaintDC* dc, int nStartValue_y, int nStartMargin, int nDepth /* = 1*/)
{
	if (nDepth > 3)
		return;

	CRect controlRect, controlToMarginRect1, controlToMarginRect2;

	if (nDepth == 1)
	{
		m_stt_bit.GetWindowRect(&controlToMarginRect1);
		m_stt_mbyte.GetWindowRect(&controlToMarginRect2);
		m_stt_bit.GetClientRect(&controlRect);
	}
	else
	{
		m_stt_mbyte.GetWindowRect(&controlToMarginRect1);
		m_stt_pbyte.GetWindowRect(&controlToMarginRect2);
		m_stt_mbyte.GetClientRect(&controlRect);
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

void ConvertBitTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	
	CRect divideRect;
	m_stt_divide.GetClientRect(&divideRect);

	CRect divideToMargin1, divideToMargin2;
	m_stt_divide.GetWindowRect(&divideToMargin1);
	m_stt_bit.GetWindowRect(&divideToMargin2);
	int nDivideMargin = divideToMargin2.top - divideToMargin1.bottom;

	CalcDrawLine(&dc, divideRect.top + divideRect.Height(), nDivideMargin);

	dc.Draw3dRect(drawBorderRect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
	dc.Draw3dRect(drawComboBorderRect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());
}
