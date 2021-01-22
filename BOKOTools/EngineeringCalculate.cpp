// EngineeringCalculate.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "EngineeringCalculate.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// EngineeringCalculate 대화 상자

IMPLEMENT_DYNAMIC(EngineeringCalculate, CDialogEx)

EngineeringCalculate::EngineeringCalculate(int nManualImageID, bool bUsingManual, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ENGINEERING, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme;
	this->bUsingManual = bUsingManual;
	usingManual = new UsingManualDialog(true, IDD_DIALOG_ENGINEERING, nManualImageID, currentTheme);
	timeline = new ResultTimeline(currentTheme);
	calculate = new Calculate;
	bTimeline = false;
}

EngineeringCalculate::~EngineeringCalculate()
{
	if (calculate)
	{
		delete calculate;
		calculate = (Calculate*)nullptr;
	}

	if (timeline)
	{
		timeline->DestroyWindow();
		delete timeline;
		timeline = nullptr;
	}

	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
	}
}

void EngineeringCalculate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CALCULATE_VIEW, m_edit_calculate_view);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_btn_clear);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btn_back);
	DDX_Control(pDX, IDC_BUTTON_DIVIDE, m_btn_divide);
	DDX_Control(pDX, IDC_BUTTON_MULTI, m_btn_multi);
	DDX_Control(pDX, IDC_BUTTON_SUM, m_btn_sum);
	DDX_Control(pDX, IDC_BUTTON_MIN, m_btn_min);
	DDX_Control(pDX, IDC_BUTTON_RESULT, m_btn_result);
	DDX_Control(pDX, IDC_BUTTON_DOT, m_btn_dot);
	DDX_Control(pDX, IDC_BUTTON_0, m_btn_0);
	DDX_Control(pDX, IDC_BUTTON_1, m_btn_1);
	DDX_Control(pDX, IDC_BUTTON_2, m_btn_2);
	DDX_Control(pDX, IDC_BUTTON_3, m_btn_3);
	DDX_Control(pDX, IDC_BUTTON_4, m_btn_4);
	DDX_Control(pDX, IDC_BUTTON_5, m_btn_5);
	DDX_Control(pDX, IDC_BUTTON_6, m_btn_6);
	DDX_Control(pDX, IDC_BUTTON_7, m_btn_7);
	DDX_Control(pDX, IDC_BUTTON_8, m_btn_8);
	DDX_Control(pDX, IDC_BUTTON_9, m_btn_9);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_edit_result);
	DDX_Control(pDX, IDC_BUTTON_OPENBRACKET, m_btn_openbracket);
	DDX_Control(pDX, IDC_BUTTON_CLOSEBRACKET, m_btn_closebracket);
	DDX_Control(pDX, IDC_BUTTON_EXPONENTIATION, m_btn_exponentiation);
	DDX_Control(pDX, IDC_BUTTON_REMAINER, m_btn_remainer);
	DDX_Control(pDX, IDC_BUTTON_ROOT, m_btn_root);
	DDX_Control(pDX, IDC_BUTTON_FACTORIAL, m_btn_factorial);
	DDX_Control(pDX, IDC__STATIC_CALCULATE_VIEW, m_stt_calculate_view);
	DDX_Control(pDX, IDC_BUTTON_REPORT, m_btn_report);
	DDX_Control(pDX, IDC_BUTTON_TRASH, m_btn_trash);
	DDX_Control(pDX, IDC_STATIC_BUTTON_CALCULATE_VIEW, m_stt_btn_calculate_view);
}


BEGIN_MESSAGE_MAP(EngineeringCalculate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &EngineeringCalculate::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &EngineeringCalculate::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &EngineeringCalculate::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_MULTI, &EngineeringCalculate::OnBnClickedButtonMulti)
	ON_BN_CLICKED(IDC_BUTTON_SUM, &EngineeringCalculate::OnBnClickedButtonSum)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &EngineeringCalculate::OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &EngineeringCalculate::OnBnClickedButtonResult)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &EngineeringCalculate::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_0, &EngineeringCalculate::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &EngineeringCalculate::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &EngineeringCalculate::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &EngineeringCalculate::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &EngineeringCalculate::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &EngineeringCalculate::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &EngineeringCalculate::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &EngineeringCalculate::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &EngineeringCalculate::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &EngineeringCalculate::OnBnClickedButton9)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_OPENBRACKET, &EngineeringCalculate::OnBnClickedButtonOpenbracket)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEBRACKET, &EngineeringCalculate::OnBnClickedButtonClosebracket)
	ON_BN_CLICKED(IDC_BUTTON_EXPONENTIATION, &EngineeringCalculate::OnBnClickedButtonExponentiation)
	ON_BN_CLICKED(IDC_BUTTON_REMAINER, &EngineeringCalculate::OnBnClickedButtonRemainer)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ROOT, &EngineeringCalculate::OnBnClickedButtonRoot)
	ON_BN_CLICKED(IDC_BUTTON_FACTORIAL, &EngineeringCalculate::OnBnClickedButtonFactorial)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, &EngineeringCalculate::OnBnClickedButtonReport)
	ON_BN_CLICKED(IDC_BUTTON_TRASH, &EngineeringCalculate::OnBnClickedButtonTrash)
	ON_WM_MOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// EngineeringCalculate 메시지 처리기


BOOL EngineeringCalculate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_backBrush.CreateSolidBrush(currentTheme->GetFunctionSubColor());

	this->SetWindowPos(NULL, 0, 0, 300, 450, SWP_NOMOVE);
	this->GetWindowRect(thisRect);

	timeline->Create(IDD_DIALOG_TIMELINE, this);
	timeline->MoveWindow(300, 45, 220, 305);
	drawTimelineBorderRect = {298, 43, 300 + 222, 45 + 307};
	m_btn_report.MoveWindow(250, 10, 24, 24);
	m_btn_trash.MoveWindow(495, 360, 24, 24);
	timeline->ShowWindow(SW_HIDE);
	m_btn_trash.ShowWindow(SW_HIDE);

	m_stt_calculate_view.MoveWindow(8, 45, 276, 135);
	drawBorderRect = { 7, 43, 278, 137 };
	m_edit_calculate_view.MoveWindow(9, 50, 265, 30);
	m_edit_result.MoveWindow(9, 100, 265, 30);
	m_stt_btn_calculate_view.MoveWindow(8, 148, 276, 395);
	drawButtonBorderRect = { 7, 146, 278, 393 };

	SetButtonPos();
	
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());

	COLORREF buttonColor = RGB(MaxRGBColor(GetRValue(currentTheme->GetButtonColor()), 20), MaxRGBColor(GetGValue(currentTheme->GetButtonColor()), 20), MaxRGBColor(GetBValue(currentTheme->GetButtonColor()), 20));
	m_btn_0.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_1.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_2.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_3.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_4.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_5.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_6.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_7.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_8.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_9.Initialize(buttonColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("고딕"), 23, FW_BOLD);
	m_btn_back.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_clear.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_divide.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_multi.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_sum.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_min.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_result.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_dot.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_openbracket.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_closebracket.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_exponentiation.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_remainer.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_root.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);
	m_btn_factorial.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 17, FW_NORMAL);

	m_btn_0.SetTextColor(currentTheme->GetTextColor());
	m_btn_1.SetTextColor(currentTheme->GetTextColor());
	m_btn_2.SetTextColor(currentTheme->GetTextColor());
	m_btn_3.SetTextColor(currentTheme->GetTextColor());
	m_btn_4.SetTextColor(currentTheme->GetTextColor());
	m_btn_5.SetTextColor(currentTheme->GetTextColor());
	m_btn_6.SetTextColor(currentTheme->GetTextColor());
	m_btn_7.SetTextColor(currentTheme->GetTextColor());
	m_btn_8.SetTextColor(currentTheme->GetTextColor());
	m_btn_9.SetTextColor(currentTheme->GetTextColor());
	m_btn_back.SetTextColor(currentTheme->GetTextColor());
	m_btn_clear.SetTextColor(currentTheme->GetTextColor());
	m_btn_divide.SetTextColor(currentTheme->GetTextColor());
	m_btn_multi.SetTextColor(currentTheme->GetTextColor());
	m_btn_sum.SetTextColor(currentTheme->GetTextColor());
	m_btn_min.SetTextColor(currentTheme->GetTextColor());
	m_btn_result.SetTextColor(currentTheme->GetTextColor());
	m_btn_dot.SetTextColor(currentTheme->GetTextColor());
	m_btn_openbracket.SetTextColor(currentTheme->GetTextColor());
	m_btn_closebracket.SetTextColor(currentTheme->GetTextColor());
	m_btn_exponentiation.SetTextColor(currentTheme->GetTextColor());
	m_btn_remainer.SetTextColor(currentTheme->GetTextColor());
	m_btn_root.SetTextColor(currentTheme->GetTextColor());
	m_btn_factorial.SetTextColor(currentTheme->GetTextColor());

	m_edit_result.Initialize(30, _T("고딕"));
	m_edit_calculate_view.Initialize(23, _T("고딕"));

	m_btn_report.LoadStdImage(IDB_PNG_TIMELINE_NOMAL, _T("PNG"));
	m_btn_report.LoadHovImage(IDB_PNG_TIMELINE_HOVER, _T("PNG"));
	m_btn_report.LoadAltImage(IDB_PNG_TIMELINE_CLICK, _T("PNG"));

	m_btn_trash.LoadStdImage(IDB_PNG_TRASH_NOMAL, _T("PNG"));
	m_btn_trash.LoadHovImage(IDB_PNG_TRASH_HOVER, _T("PNG"));
	m_btn_trash.LoadAltImage(IDB_PNG_TRASH_CLICK, _T("PNG"));

	m_edit_calculate_view.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_result.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_calculate_view.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	
	m_edit_calculate_view.BringWindowToTop();
	m_edit_result.BringWindowToTop();

	ClickEnd(_T("0"));
	m_edit_result.SetWindowTextW(_T("0"));

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL, GetDesktopWindow());
		usingManual->ShowWindow(SW_SHOW);
	}
	
	return FALSE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void EngineeringCalculate::SetButtonPos()
{
	int nButtonStartPos_x = 15;
	int nButtonStartPos_y = 154;
	int nButtonWidth = 60;
	int nButtonHeight = 34;
	int nButtonMargin = 5;

	m_btn_remainer.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 0, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 0, nButtonWidth, nButtonHeight);
	m_btn_root.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 1, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 0, nButtonWidth, nButtonHeight);
	m_btn_exponentiation.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 2, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 0, nButtonWidth, nButtonHeight);
	m_btn_factorial.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 3, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 0, nButtonWidth, nButtonHeight);

	m_btn_clear.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 0, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 1, nButtonWidth, nButtonHeight);
	m_btn_back.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 1, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 1, nButtonWidth, nButtonHeight);
	m_btn_openbracket.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 2, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 1, nButtonWidth, nButtonHeight);
	m_btn_closebracket.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 3, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 1, nButtonWidth, nButtonHeight);

	m_btn_7.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 0, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 2, nButtonWidth, nButtonHeight);
	m_btn_8.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 1, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 2, nButtonWidth, nButtonHeight);
	m_btn_9.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 2, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 2, nButtonWidth, nButtonHeight);
	m_btn_divide.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 3, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 2, nButtonWidth, nButtonHeight);

	m_btn_4.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 0, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 3, nButtonWidth, nButtonHeight);
	m_btn_5.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 1, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 3, nButtonWidth, nButtonHeight);
	m_btn_6.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 2, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 3, nButtonWidth, nButtonHeight);
	m_btn_multi.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 3, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 3, nButtonWidth, nButtonHeight);

	m_btn_1.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 0, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 4, nButtonWidth, nButtonHeight);
	m_btn_2.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 1, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 4, nButtonWidth, nButtonHeight);
	m_btn_3.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 2, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 4, nButtonWidth, nButtonHeight);
	m_btn_sum.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 3, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 4, nButtonWidth, nButtonHeight);

	m_btn_dot.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 0, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 5, nButtonWidth, nButtonHeight);
	m_btn_0.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 1, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 5, nButtonWidth, nButtonHeight);
	m_btn_result.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 2, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 5, nButtonWidth, nButtonHeight);
	m_btn_min.MoveWindow(nButtonStartPos_x + (nButtonWidth + nButtonMargin) * 3, nButtonStartPos_y + (nButtonHeight + nButtonMargin) * 5, nButtonWidth, nButtonHeight);

}

// 클리어버튼 1. 에딧 클리어, 2. 계산 초기화
void EngineeringCalculate::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ClickEnd(_T("0"));
	m_edit_result.SetWindowTextW(_T("0"));
}

// 한칸 뒤로 1. 에딧 한칸 삭제
void EngineeringCalculate::OnBnClickedButtonBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (calculate->GetResult())
	{
		return;
	}

	CString strText = _T("");
	m_edit_calculate_view.GetWindowTextW(strText);
	if (strText != _T("0"))
	{
		strText.Delete(strText.GetLength() - 1, 1);
		if (strText.IsEmpty())
		{
			strText = _T("0");
		}
	}

	ClickEnd(strText);
}

void EngineeringCalculate::InputToOperator(CString inputOperator)
{
	CString strText = _T("");
	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Type typeBystr = calculate->GetInstanceTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	Formula::Bracket bType = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	Formula::Operator oType = calculate->GetInstanceOperTypeStr(inputOperator);
	if (typeBystr == Formula::Type::TYPE_OPERATOR ||
		typeBystr == Formula::Type::TYPE_DOT)
	{
		strText.Delete(strText.GetLength() - 1, 1);
	}
	else if (bType == Formula::Bracket::BRACKET_TYPE_OPEN) 
	{
		if (oType == Formula::Operator::OPERATOR_TYPE_MULTIPLE || 
			oType == Formula::Operator::OPERATOR_TYPE_DIVIDE ||
			oType == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION || 
			oType == Formula::Operator::OPERATOR_TYPE_REMAINDER)
		{
			return;
		}
	}

	if (calculate->GetResult())
	{
		m_edit_result.GetWindowTextW(strText);
		m_edit_calculate_view.SetWindowTextW(strText);
		calculate->SetResult(false);
	}

	strText.AppendFormat(_T("%s"), inputOperator);
	ClickEnd(strText);
}

// 나누기 계산
void EngineeringCalculate::OnBnClickedButtonDivide()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InputToOperator(_T("÷"));
}

// 곱하기 계산
void EngineeringCalculate::OnBnClickedButtonMulti()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InputToOperator(_T("×"));
}

// 더하기 계산 
void EngineeringCalculate::OnBnClickedButtonSum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InputToOperator(_T("＋"));
}

// 빼기 계산 
void EngineeringCalculate::OnBnClickedButtonMin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InputToOperator(_T("－"));
}

// 지수 계산
void EngineeringCalculate::OnBnClickedButtonExponentiation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InputToOperator(_T("^"));
}


// 나머지 계산
void EngineeringCalculate::OnBnClickedButtonRemainer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InputToOperator(_T("%"));
}

// 루트 계산
void EngineeringCalculate::OnBnClickedButtonRoot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");
	m_edit_calculate_view.GetWindowTextW(strText);

	if (calculate->GetResult())
	{
		m_edit_result.GetWindowTextW(strText);
		m_edit_calculate_view.SetWindowTextW(strText);
		calculate->SetResult(false);
	}

	Formula::Type typeBystr = calculate->GetInstanceTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	Formula::Bracket bType = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (typeBystr == Formula::Type::TYPE_DOT)
	{
		return;
	}
	else if (typeBystr == Formula::Type::TYPE_NUMBER)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}
	else if (bType == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{	
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%s"), _T("√"));
	}
	else
	{
		strText.Format(_T("%s"), _T("√"));
	}

	ClickEnd(strText);
}

// 팩토리얼 계산
void EngineeringCalculate::OnBnClickedButtonFactorial()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");
	m_edit_calculate_view.GetWindowTextW(strText);

	if (calculate->GetResult())
	{
		m_edit_result.GetWindowTextW(strText);
		m_edit_calculate_view.SetWindowTextW(strText);
		calculate->SetResult(false);
	}

	Formula::Type typeBystr = calculate->GetInstanceTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	Formula::Bracket bType = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	Formula::Operator oType = calculate->GetInstanceOperTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (typeBystr == Formula::Type::TYPE_DOT)
	{
		return;
	}
	else if (bType == Formula::Bracket::BRACKET_TYPE_OPEN)
	{
		return;
	}
	else if (oType == Formula::Operator::OPERATOR_TYPE_DIVIDE ||
			 oType == Formula::Operator::OPERATOR_TYPE_MULTIPLE ||
			 oType == Formula::Operator::OPERATOR_TYPE_PLUS ||
			 oType == Formula::Operator::OPERATOR_TYPE_MINUS ||
			 oType == Formula::Operator::OPERATOR_TYPE_REMAINDER ||
			 oType == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION)
	{
		strText.Delete(strText.GetLength() - 1, 1);
	}

	strText.AppendFormat(_T("%s"), _T("!"));
	ClickEnd(strText);
}

// 오픈 괄호
void EngineeringCalculate::OnBnClickedButtonOpenbracket()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");
	m_edit_calculate_view.GetWindowTextW(strText);

	if (calculate->GetResult())
	{
		m_edit_result.GetWindowTextW(strText);
		m_edit_calculate_view.SetWindowTextW(strText);
		calculate->SetResult(false);
	}

	Formula::Type typeBystr = calculate->GetInstanceTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	Formula::Operator oType = calculate->GetInstanceOperTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (typeBystr == Formula::Type::TYPE_DOT)
	{
		return;
	}
	else if (typeBystr == Formula::Type::TYPE_NUMBER ||
			 oType == Formula::Operator::OPERATOR_TYPE_FACTORIAL)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}
	else if (typeBystr == Formula::Type::TYPE_BRACKET)
	{
		Formula::Bracket bType = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
		if (bType == Formula::Bracket::BRACKET_TYPE_CLOSE)
		{
			if (strText != _T("0"))
			{
				strText.AppendFormat(_T("%s"), _T("×"));
			}
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%s"), _T("("));
	}
	else
	{
		strText.Format(_T("%s"), _T("("));
	}

	ClickEnd(strText);
}

// 닫기 괄호
void EngineeringCalculate::OnBnClickedButtonClosebracket()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");
	m_edit_calculate_view.GetWindowTextW(strText);

	if (calculate->GetResult())
	{
		m_edit_result.GetWindowTextW(strText);
		m_edit_calculate_view.SetWindowTextW(strText);
		calculate->SetResult(false);
		return;
	}

	Formula::Type typeBystr = calculate->GetInstanceTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (typeBystr == Formula::Type::TYPE_OPERATOR ||
		typeBystr == Formula::Type::TYPE_DOT)
	{
		return;
	}
	else if (typeBystr == Formula::Type::TYPE_BRACKET)
	{
		Formula::Bracket bType = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
		if (bType == Formula::Bracket::BRACKET_TYPE_OPEN) return;
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%s"), _T(")"));
	}
	else
	{
		return;
	}

	ClickEnd(strText);
}

// = 계산
void EngineeringCalculate::OnBnClickedButtonResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");
	CString strResult = _T("");
	m_edit_calculate_view.GetWindowTextW(strText);

	// 식 정상인지 조건검사
	if (calculate->FormulaCondition(strText))
	{
		strResult = calculate->ResultOperate(strText);
	}
	else
	{
		strResult = _T("수식을 확인하세요.");
	}

	ClickEnd(strText);
	m_edit_result.SetWindowTextW(strResult);

	CString str1, str2;
	m_edit_calculate_view.GetWindowTextW(str1);
	m_edit_result.GetWindowTextW(str2);
	timeline->AppendTimeline(str1, str2);
}

void EngineeringCalculate::ClickEnd(CString strEnd)
{
	m_edit_calculate_view.SetWindowTextW(strEnd);
	m_edit_calculate_view.SetFocus();
	m_edit_calculate_view.SetSel(-1);
}

// 닷 
void EngineeringCalculate::OnBnClickedButtonDot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	m_edit_calculate_view.GetWindowTextW(strText);
	if (calculate->IsDot(strText))
	{
		strText.AppendFormat(_T("%s"), _T("."));
	}

	ClickEnd(strText);
}

// 0버튼 클릭
void EngineeringCalculate::OnBnClickedButton0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 0);
	}
	else
	{
		strText.Format(_T("%d"), 0);
	}

	ClickEnd(strText);
}

// 1버튼 클릭
void EngineeringCalculate::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 1);
	}
	else
	{
		strText.Format(_T("%d"), 1);
	}
	ClickEnd(strText);
}

// 2버튼 클릭
void EngineeringCalculate::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 2);
	}
	else
	{
		strText.Format(_T("%d"), 2);
	}
	ClickEnd(strText);
}

// 3버튼 클릭
void EngineeringCalculate::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 3);
	}
	else
	{
		strText.Format(_T("%d"), 3);
	}
	ClickEnd(strText);
}

// 4버튼 클릭
void EngineeringCalculate::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 4);
	}
	else
	{
		strText.Format(_T("%d"), 4);
	}
	ClickEnd(strText);
}

// 5버튼 클릭
void EngineeringCalculate::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 5);
	}
	else
	{
		strText.Format(_T("%d"), 5);
	}
	ClickEnd(strText);
}

// 6버튼 클릭
void EngineeringCalculate::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 6);
	}
	else
	{
		strText.Format(_T("%d"), 6);
	}
	ClickEnd(strText);
}

// 7버튼 클릭
void EngineeringCalculate::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 7);
	}
	else
	{
		strText.Format(_T("%d"), 7);
	}
	ClickEnd(strText);
}

// 8버튼 클릭
void EngineeringCalculate::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 8);
	}
	else
	{
		strText.Format(_T("%d"), 8);
	}
	ClickEnd(strText);
}

// 9버튼 클릭
void EngineeringCalculate::OnBnClickedButton9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strText = _T("");

	if (calculate->GetResult())
	{
		m_edit_result.SetWindowTextW(_T("0"));
		m_edit_calculate_view.SetWindowTextW(_T("0"));
		calculate->SetResult(false);
	}

	m_edit_calculate_view.GetWindowTextW(strText);

	Formula::Bracket bTypeBystr = calculate->GetInstanceBraTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (bTypeBystr == Formula::Bracket::BRACKET_TYPE_CLOSE)
	{
		if (strText != _T("0"))
		{
			strText.AppendFormat(_T("%s"), _T("×"));
		}
	}

	if (strText != _T("0"))
	{
		strText.AppendFormat(_T("%d"), 9);
	}
	else
	{
		strText.Format(_T("%d"), 9);
	}
	ClickEnd(strText);
}


BOOL EngineeringCalculate::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == m_edit_calculate_view)
		{
			m_edit_calculate_view.HideCaret();
		}
		else if (pMsg->hwnd == m_edit_result)
		{
			m_edit_result.HideCaret();
		}
	}
	else if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == m_btn_report)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
			SetCursor(hCursor);
		}
		else if (pMsg->hwnd == m_btn_trash)
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
		else if (pMsg->wParam == VK_DIVIDE) pMsg->wParam = L'/';
		else if (pMsg->wParam == VK_MULTIPLY) pMsg->wParam = L'*';
		else if (pMsg->wParam == VK_ADD) pMsg->wParam = L'+';
		else if (pMsg->wParam == VK_SUBTRACT) pMsg->wParam = L'-';
		else if (pMsg->wParam == VK_DECIMAL) pMsg->wParam = L'.';
		else if (pMsg->wParam == VK_OEM_MINUS) pMsg->wParam = L'-';

		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (pMsg->wParam == L'0')
			{
				OnBnClickedButtonClosebracket();
				return TRUE;
			}
			else if (pMsg->wParam == L'1')
			{
				OnBnClickedButtonFactorial();
				return TRUE;
			}
			else if (pMsg->wParam == L'2')
			{
				OnBnClickedButtonRoot();
				return TRUE;
			}
			else if (pMsg->wParam == L'5')
			{
				OnBnClickedButtonRemainer();
				return TRUE;
			}
			else if (pMsg->wParam == L'6')
			{
				OnBnClickedButtonExponentiation();
				return TRUE;
			}
			else if (pMsg->wParam == L'8')
			{
				OnBnClickedButtonMulti();
				return TRUE;
			}
			else if (pMsg->wParam == L'9')
			{
				OnBnClickedButtonOpenbracket();
				return TRUE;
			}
			else if (pMsg->wParam == VK_OEM_PLUS)
			{
				OnBnClickedButtonSum();
				return TRUE;
			}
		}
		else
		{
			if (pMsg->wParam == VK_OEM_PLUS)
			{
				OnBnClickedButtonResult();
				return TRUE;
			}
			else if (pMsg->wParam == VK_OEM_2)
			{
				OnBnClickedButtonDivide();
				return TRUE;
			}
			else if (pMsg->wParam == VK_OEM_PERIOD)
			{
				OnBnClickedButtonDot();
				return TRUE;
			}
			else if (pMsg->wParam == L'0')
			{
				OnBnClickedButton0();
				return TRUE;
			}
			else if (pMsg->wParam == L'1')
			{
				OnBnClickedButton1();
				return TRUE;
			}
			else if (pMsg->wParam == L'2')
			{
				OnBnClickedButton2();
				return TRUE;
			}
			else if (pMsg->wParam == L'3')
			{
				OnBnClickedButton3();
				return TRUE;
			}
			else if (pMsg->wParam == L'4')
			{
				OnBnClickedButton4();
				return TRUE;
			}
			else if (pMsg->wParam == L'5')
			{
				OnBnClickedButton5();
				return TRUE;
			}
			else if (pMsg->wParam == L'6')
			{
				OnBnClickedButton6();
				return TRUE;
			}
			else if (pMsg->wParam == L'7')
			{
				OnBnClickedButton7();
				return TRUE;
			}
			else if (pMsg->wParam == L'8')
			{
				OnBnClickedButton8();
				return TRUE;
			}
			else if (pMsg->wParam == L'9')
			{
				OnBnClickedButton9();
				return TRUE;
			}
		}

		if (pMsg->wParam == L'/')
		{
			OnBnClickedButtonDivide();
			return TRUE;
		}
		else if (pMsg->wParam == L'*')
		{
			OnBnClickedButtonMulti();
			return TRUE;
		}
		else if (pMsg->wParam == L'+')
		{
			OnBnClickedButtonSum();
			return TRUE;
		}
		else if (pMsg->wParam == L'-')
		{
			OnBnClickedButtonMin();
			return TRUE;
		}
		else if (pMsg->wParam == L'.')
		{
			OnBnClickedButtonDot();
			return TRUE;
		}
		else if (pMsg->wParam == VK_BACK)
		{
			OnBnClickedButtonBack();
			return TRUE;
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			OnBnClickedButtonClear();
			return TRUE;
		}
		else if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedButtonResult();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void EngineeringCalculate::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	EngineeringCalculate::PostNcDestroy();
}


void EngineeringCalculate::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bEngineering = false;
	delete this;
	CDialogEx::PostNcDestroy();
}

void EngineeringCalculate::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}

HBRUSH EngineeringCalculate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_CALCULATE_VIEW)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(RGB(150, 150, 150));
				pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			}
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_RESULT)
		{
			if (currentTheme)
			{
				pDC->SetTextColor(currentTheme->GetFunctionTextColor());
				pDC->SetBkColor(currentTheme->GetFunctionSubColor());
			}
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC__STATIC_CALCULATE_VIEW)
		{
			CRect rect;
			GetClientRect(&rect);

			CDC* pDC = m_stt_calculate_view.GetWindowDC();
			CBrush *pOld = pDC->SelectObject(&m_backBrush);
			pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
			pDC->SelectObject(pOld);
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else
	{
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}


	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void EngineeringCalculate::OnBnClickedButtonReport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!bTimeline)
	{
		this->MoveWindow(thisRect.left, thisRect.top, 300 + 260, thisRect.Height());
		timeline->ShowWindow(SW_SHOW);
		m_btn_trash.ShowWindow(SW_SHOW);
		bTimeline = true;
	}
	else
	{
		this->MoveWindow(thisRect.left, thisRect.top, thisRect.Width(), thisRect.Height());
		timeline->ShowWindow(SW_HIDE);
		m_btn_trash.ShowWindow(SW_HIDE);
		bTimeline = false;
	}
	m_edit_calculate_view.SetFocus();
	m_edit_calculate_view.SetSel(-1);
}

void EngineeringCalculate::OnBnClickedButtonTrash()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	timeline->DeleteTimeline();
	m_edit_calculate_view.SetFocus();
	m_edit_calculate_view.SetSel(-1);
}


void EngineeringCalculate::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CRect changeRect;
	GetWindowRect(&changeRect);
	thisRect.SetRect(changeRect.left, changeRect.top, thisRect.right + (changeRect.left - thisRect.left), thisRect.bottom + (changeRect.top - thisRect.top));
}


void EngineeringCalculate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(drawBorderRect, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
	dc.Draw3dRect(drawButtonBorderRect, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());
	dc.Draw3dRect(drawTimelineBorderRect, currentTheme->GetRectBorderColor(), currentTheme->GetRectBorderColor());

	CBrush *pOld = dc.SelectObject(&m_backBrush);
	dc.PatBlt(drawBorderRect.left + 1, drawBorderRect.top + 1, drawBorderRect.Width() - 2, drawBorderRect.Height() - 2, PATCOPY);
	dc.PatBlt(drawButtonBorderRect.left + 1, drawButtonBorderRect.top + 1, drawButtonBorderRect.Width() - 2, drawButtonBorderRect.Height() - 2, PATCOPY);
	dc.SelectObject(pOld);

}
