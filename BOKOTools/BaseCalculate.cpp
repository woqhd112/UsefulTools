// BaseCalculate.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "BaseCalculate.h"
#include "afxdialogex.h"
#include "BOKOToolsDlg.h"
#include <stack>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// BaseCalculate 대화 상자

IMPLEMENT_DYNAMIC(BaseCalculate, CDialogEx)

BaseCalculate::BaseCalculate(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BASE, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
}

BaseCalculate::~BaseCalculate()
{
}

void BaseCalculate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RESULT, m_select);
	DDX_Control(pDX, IDC_COMBO_SELECT, m_result);
	DDX_Control(pDX, IDC_STATIC_INPUT_SELECT, m_stt_input_select);
	DDX_Control(pDX, IDC_STATIC_OUTPUT_RESULT, m_stt_output_result);
	DDX_Control(pDX, IDC_INPUT_10_FROM2, m_edit_input_ten_from_base);
	DDX_Control(pDX, IDC_OUTPUT_2_FROM2, m_edit_output_select_from_base);
	DDX_Control(pDX, IDC_BUTTON_RESULT_TWO_FROM2, m_btn_result_select_from_base);
	//DDX_Control(pDX, IDC_STATIC_GROUP_BASE, m_stt_group_base);
	DDX_Control(pDX, IDC_STATIC_BASE_VIEW, m_stt_base_view);
	DDX_Control(pDX, IDC_STATIC_BASE, m_stt_base);
	DDX_Control(pDX, IDC_STATIC_SELECT_INPUT, m_stt_select_input);
	DDX_Control(pDX, IDC_STATIC_SELECT_OUTPUT, m_stt_result_select);
}


BEGIN_MESSAGE_MAP(BaseCalculate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RESULT_TWO_FROM2, &BaseCalculate::OnBnClickedButtonResultTwoFrom2)
	ON_CBN_SELCHANGE(IDC_COMBO_RESULT, &BaseCalculate::OnCbnSelchangeComboResult)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

 
// BaseCalculate 메시지 처리기


BOOL BaseCalculate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	this->SetWindowPos(NULL, 0, 0, 400, 300, SWP_NOMOVE);

	m_btn_result_select_from_base.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("가비아 솔미체"), 25);
	m_btn_result_select_from_base.SetTextColor(currentTheme->GetTextColor());
	m_edit_input_ten_from_base.Initialize(25, _T("가비아 솔미체"));
	m_edit_output_select_from_base.Initialize(25, _T("가비아 솔미체"));
	m_stt_base.Initialize(30, _T("가비아 솔미체"));
	m_stt_input_select.Initialize(20, _T("가비아 솔미체"));
	m_stt_output_result.Initialize(20, _T("가비아 솔미체"));
	m_stt_select_input.Initialize(20, _T("가비아 솔미체"));
	m_stt_result_select.Initialize(20, _T("가비아 솔미체"));

	SetComboBox();

	drawBorderRect = { 20, 55, 360, 245 };
	m_stt_base.MoveWindow(20, 20, 200, 30);
	m_stt_select_input.MoveWindow(30, 90, 70, 20);
	m_select.MoveWindow(100, 85, 80, 30);
	m_stt_result_select.MoveWindow(190, 90, 70, 20);
	m_result.MoveWindow(260, 85, 80, 30);
	m_stt_input_select.MoveWindow(30, 130, 70, 20);
	m_edit_input_ten_from_base.MoveWindow(100, 125, 240, 30);
	m_stt_output_result.MoveWindow(30, 170, 70, 20);
	m_edit_output_select_from_base.MoveWindow(100, 165, 240, 30);
	m_btn_result_select_from_base.MoveWindow(200, 205, 140, 30);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void BaseCalculate::SetComboBox()
{
	comboFont.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		_T("가비아 솔미체"));
	m_select.SetFont(&comboFont);
	m_select.AddString(_T("2진법"));
	m_select.AddString(_T("3진법"));
	m_select.AddString(_T("4진법"));
	m_select.AddString(_T("5진법"));
	m_select.AddString(_T("6진법"));
	m_select.AddString(_T("7진법"));
	m_select.AddString(_T("8진법"));
	m_select.AddString(_T("9진법"));
	m_select.AddString(_T("10진법"));
	m_select.AddString(_T("11진법"));
	m_select.AddString(_T("12진법"));
	m_select.AddString(_T("13진법"));
	m_select.AddString(_T("14진법"));
	m_select.AddString(_T("15진법"));
	m_select.AddString(_T("16진법"));
	m_select.SetCurSel(8);
	SelectComboBox();
	m_result.SetFont(&comboFont);
	m_result.AddString(_T("2진법"));
	m_result.AddString(_T("3진법"));
	m_result.AddString(_T("4진법"));
	m_result.AddString(_T("5진법"));
	m_result.AddString(_T("6진법"));
	m_result.AddString(_T("7진법"));
	m_result.AddString(_T("8진법"));
	m_result.AddString(_T("9진법"));
	m_result.AddString(_T("10진법"));
	m_result.AddString(_T("11진법"));
	m_result.AddString(_T("12진법"));
	m_result.AddString(_T("13진법"));
	m_result.AddString(_T("14진법"));
	m_result.AddString(_T("15진법"));
	m_result.AddString(_T("16진법"));
	m_result.SetCurSel(0);
	SelectComboBox();
}


// 10진수를 선택진수로 변환 버튼
void BaseCalculate::OnBnClickedButtonResultTwoFrom2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");
	m_edit_input_ten_from_base.GetWindowTextW(strText);
	if (!strText.IsEmpty())
	{
		int nSelect = m_select.GetCurSel();
		int nResult = m_result.GetCurSel();
		InputTenToSet(nResult + 2, OutputSetToTen(nSelect + 2));
	}
}


void BaseCalculate::InputTenToSet(int nMacro, CString strOutput)
{
	CString strText = _T("");
	CString strFormat = _T("");
	int nBase = 0;
	int nRemainder = 0;
	int nShare = 0;
	int nSize = 0;
	char cTemp = 0;
	char cRemainder = '\0';
	char cShare = '\0';
	std::stack<char> totalBase;

	strText = strOutput;
	nBase = _ttoi(strText);

	while (true)
	{
		nRemainder = nBase % nMacro;
		nShare = nBase / nMacro;

		if (nShare > (nMacro - 1))
		{
			nBase = nShare;
			cRemainder = ConvertIntToChar(nRemainder);
			totalBase.push(cRemainder);
		}
		else
		{
			cRemainder = ConvertIntToChar(nRemainder);
			cShare = ConvertIntToChar(nShare);
			totalBase.push(cRemainder);
			totalBase.push(cShare);
			break;
		}
	}

	nSize = (int)totalBase.size();
	for (int i = 0; i < nSize; i++)
	{
		cTemp = totalBase.top();
		strFormat.AppendFormat(_T("%c"), cTemp);
		totalBase.pop();
	}
	m_edit_output_select_from_base.SetWindowTextW(strFormat);
}

CString BaseCalculate::OutputSetToTen(int nMacro)
{
	CString strText = _T("");
	CString strTest = _T("");
	CString strFormat = _T("");
	int nBase = 0;
	int nLength = 0;
	int nSum = 0;
	int nConvertInt = 0;

	m_edit_input_ten_from_base.GetWindowTextW(strText);
	nBase = _ttoi(strText);

	nLength = strText.GetLength();

	for (int i = 0; i < nLength; i++)
	{
		strTest = (CString)strText.GetAt(i);
		nConvertInt = ConvertCharToInt(strTest.MakeLower());
		nConvertInt = static_cast<int>(nConvertInt * pow(nMacro, nLength - (i + 1)));
		nSum += nConvertInt;
	}
	strFormat.Format(_T("%d"), nSum);
	return strFormat;
}


char BaseCalculate::ConvertIntToChar(int nInt)
{
	if (nInt == 0) return '0';
	else if (nInt == 1) return '1';
	else if (nInt == 2) return '2';
	else if (nInt == 3) return '3';
	else if (nInt == 4) return '4';
	else if (nInt == 5) return '5';
	else if (nInt == 6) return '6';
	else if (nInt == 7) return '7';
	else if (nInt == 8) return '8';
	else if (nInt == 9) return '9';
	else if (nInt == 10) return 'a';
	else if (nInt == 11) return 'b';
	else if (nInt == 12) return 'c';
	else if (nInt == 13) return 'd';
	else if (nInt == 14) return 'e';
	else if (nInt == 15) return 'f';

	return '\0';
}

int BaseCalculate::ConvertCharToInt(CString strStr)
{
	if (strStr == _T("0")) return 0;
	else if (strStr == _T("1")) return 1;
	else if (strStr == _T("2")) return 2;
	else if (strStr == _T("3")) return 3;
	else if (strStr == _T("4")) return 4;
	else if (strStr == _T("5")) return 5;
	else if (strStr == _T("6")) return 6;
	else if (strStr == _T("7")) return 7;
	else if (strStr == _T("8")) return 8;
	else if (strStr == _T("9")) return 9;
	else if (strStr == _T("a")) return 10;
	else if (strStr == _T("b")) return 11;
	else if (strStr == _T("c")) return 12;
	else if (strStr == _T("d")) return 13;
	else if (strStr == _T("e")) return 14;
	else if (strStr == _T("f")) return 15;

	return 0;
}


void BaseCalculate::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}

void BaseCalculate::OnCbnSelchangeComboResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_input_ten_from_base.SetWindowTextW(_T(""));
	m_edit_output_select_from_base.SetWindowTextW(_T(""));
	SelectComboBox();
}

void BaseCalculate::SelectComboBox()
{
	CString strText1 = _T("");
	CString strText2 = _T("");
	int nSelect = m_select.GetCurSel();
	int nResult = m_result.GetCurSel();
	strText1.Format(_T("%d진수"), nSelect + 2);
	strText2.Format(_T("%d진수"), nResult + 2);
	m_stt_input_select.SetWindowTextW(strText1);
	m_stt_output_result.SetWindowTextW(strText2);
}

BOOL BaseCalculate::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_result_select_from_base)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649));
			SetCursor(hCursor);
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_edit_output_select_from_base)
		{
			m_edit_output_select_from_base.HideCaret();
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
		else if (pMsg->wParam == VK_RETURN)
		{
			CString strText = _T("");
			m_edit_input_ten_from_base.GetWindowTextW(strText);
			if (!strText.IsEmpty())
			{
				OnBnClickedButtonResultTwoFrom2();
			}
			else
			{
				return TRUE;
			}
		}

		if (m_edit_input_ten_from_base.GetSafeHwnd())
		{
			if (GetFocus()->m_hWnd == m_edit_input_ten_from_base.m_hWnd)
			{
				if (m_select.GetCurSel() == 0)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 1)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 2)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 3)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 4)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 5)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 6)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 7)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 8)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else if (pMsg->wParam == L'9') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 9)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else if (pMsg->wParam == L'9') {}
					else if (pMsg->wParam == L'a' || pMsg->wParam == L'A') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 10)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else if (pMsg->wParam == L'9') {}
					else if (pMsg->wParam == L'a' || pMsg->wParam == L'A') {}
					else if (pMsg->wParam == L'b' || pMsg->wParam == L'B') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 11)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else if (pMsg->wParam == L'9') {}
					else if (pMsg->wParam == L'a' || pMsg->wParam == L'A') {}
					else if (pMsg->wParam == L'b' || pMsg->wParam == L'B') {}
					else if (pMsg->wParam == L'c' || pMsg->wParam == L'C') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 12)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else if (pMsg->wParam == L'9') {}
					else if (pMsg->wParam == L'a' || pMsg->wParam == L'A') {}
					else if (pMsg->wParam == L'b' || pMsg->wParam == L'B') {}
					else if (pMsg->wParam == L'c' || pMsg->wParam == L'C') {}
					else if (pMsg->wParam == L'd' || pMsg->wParam == L'D') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 13)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else if (pMsg->wParam == L'9') {}
					else if (pMsg->wParam == L'a' || pMsg->wParam == L'A') {}
					else if (pMsg->wParam == L'b' || pMsg->wParam == L'B') {}
					else if (pMsg->wParam == L'c' || pMsg->wParam == L'C') {}
					else if (pMsg->wParam == L'd' || pMsg->wParam == L'D') {}
					else if (pMsg->wParam == L'e' || pMsg->wParam == L'E') {}
					else { return TRUE; }
				}
				else if (m_select.GetCurSel() == 14)
				{
					if (pMsg->wParam == VK_BACK) {}
					else if (pMsg->wParam == VK_RETURN) {}
					else if (pMsg->wParam == VK_LEFT) {}
					else if (pMsg->wParam == VK_RIGHT) {}
					else if (pMsg->wParam == VK_UP) {}
					else if (pMsg->wParam == VK_DOWN) {}
					else if (pMsg->wParam == L'0') {}
					else if (pMsg->wParam == L'1') {}
					else if (pMsg->wParam == L'2') {}
					else if (pMsg->wParam == L'3') {}
					else if (pMsg->wParam == L'4') {}
					else if (pMsg->wParam == L'5') {}
					else if (pMsg->wParam == L'6') {}
					else if (pMsg->wParam == L'7') {}
					else if (pMsg->wParam == L'8') {}
					else if (pMsg->wParam == L'9') {}
					else if (pMsg->wParam == L'a' || pMsg->wParam == L'A') {}
					else if (pMsg->wParam == L'b' || pMsg->wParam == L'B') {}
					else if (pMsg->wParam == L'c' || pMsg->wParam == L'C') {}
					else if (pMsg->wParam == L'd' || pMsg->wParam == L'D') {}
					else if (pMsg->wParam == L'e' || pMsg->wParam == L'E') {}
					else if (pMsg->wParam == L'f' || pMsg->wParam == L'F') {}
					else { return TRUE; }
				}
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void BaseCalculate::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	BaseCalculate::PostNcDestroy();
}


void BaseCalculate::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bBase = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


HBRUSH BaseCalculate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SELECT_INPUT)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SELECT_OUTPUT)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_INPUT_SELECT)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_OUTPUT_RESULT)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetTextColor());
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_OUTPUT_RESULT)
		{
			if (currentTheme)
			{
				pDC->SetBkColor(RGB(255, 255, 255));
			}
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_BASE_VIEW)
		{
			/*CRect rect;
			m_stt_base_view.GetClientRect(rect);
			
			m_stt_base_view.GetWindowDC()->Draw3dRect(rect, currentTheme->GetFunctionRectBorderColor(), currentTheme->GetFunctionRectBorderColor());*/
			//hbr = (HBRUSH)borderBrush;
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void BaseCalculate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(drawBorderRect, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
}
