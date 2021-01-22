// ManualList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "ManualList.h"
#include "afxdialogex.h"


// ManualList 대화 상자

IMPLEMENT_DYNAMIC(ManualList, CDialogEx)

ManualList::ManualList(std::vector<int> usingManualIDVector, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MANUAL_LIST, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	this->usingManualIDVector = usingManualIDVector;
}

ManualList::~ManualList()
{
}

void ManualList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BASE_CALCULATOR_MANUAL, m_btn_base_calculator_manual);
	DDX_Control(pDX, IDC_BUTTON_ENGINEERING_CALCULATOR_MANUAL, m_btn_engineering_calculator_manual);
	DDX_Control(pDX, IDC_BUTTON_STOPWATCH_MANUAL, m_btn_stopwatch_manual);
	DDX_Control(pDX, IDC_BUTTON_UNIT_CONVERTER_MANUAL, m_btn_unit_converter_manual);
	DDX_Control(pDX, IDC_DATE_CALCULATOR_MANUAL, m_btn_date_calculator_manual);
	DDX_Control(pDX, IDC_BUTTON_WORK_TIMER_MANUAL, m_btn_work_timer_manual);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_MANUAL, m_btn_notepad_manual);
	DDX_Control(pDX, IDC_BUTTON_BASE_TIMER_MANUAL, m_btn_base_timer_manual);
	DDX_Control(pDX, IDC_BUTTON_WORLD_CLOCK_MANUAL, m_btn_world_clock_manual);
	DDX_Control(pDX, IDC_BUTTON_SORT_ICON_MANUAL, m_btn_sort_icon_manual);
	DDX_Control(pDX, IDC_BUTTON_THEME_SETTING_MANUAL, m_btn_theme_setting_manual);
	DDX_Control(pDX, IDC_BUTTON_MAIN_FRAME_MANUAL, m_btn_main_frame_manual);
}


BEGIN_MESSAGE_MAP(ManualList, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_BASE_CALCULATOR_MANUAL, &ManualList::OnBnClickedButtonBaseCalculatorManual)
	ON_BN_CLICKED(IDC_BUTTON_ENGINEERING_CALCULATOR_MANUAL, &ManualList::OnBnClickedButtonEngineeringCalculatorManual)
	ON_BN_CLICKED(IDC_BUTTON_STOPWATCH_MANUAL, &ManualList::OnBnClickedButtonStopwatchManual)
	ON_BN_CLICKED(IDC_BUTTON_UNIT_CONVERTER_MANUAL, &ManualList::OnBnClickedButtonUnitConverterManual)
	ON_BN_CLICKED(IDC_DATE_CALCULATOR_MANUAL, &ManualList::OnBnClickedDateCalculatorManual)
	ON_BN_CLICKED(IDC_BUTTON_WORK_TIMER_MANUAL, &ManualList::OnBnClickedButtonWorkTimerManual)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_MANUAL, &ManualList::OnBnClickedButtonNotepadManual)
	ON_BN_CLICKED(IDC_BUTTON_BASE_TIMER_MANUAL, &ManualList::OnBnClickedButtonBaseTimerManual)
	ON_BN_CLICKED(IDC_BUTTON_WORLD_CLOCK_MANUAL, &ManualList::OnBnClickedButtonWorldClockManual)
	ON_BN_CLICKED(IDC_BUTTON_SORT_ICON_MANUAL, &ManualList::OnBnClickedButtonSortIconManual)
	ON_BN_CLICKED(IDC_BUTTON_THEME_SETTING_MANUAL, &ManualList::OnBnClickedButtonThemeSettingManual)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_FRAME_MANUAL, &ManualList::OnBnClickedButtonMainFrameManual)
END_MESSAGE_MAP()


// ManualList 메시지 처리기


BOOL ManualList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	this->SetWindowPos(NULL, 0, 0, 300, 350, SWP_NOMOVE);

	SetItemCtlInit(m_btn_main_frame_manual.GetDlgCtrlID(), 0);
	SetItemCtlInit(m_btn_theme_setting_manual.GetDlgCtrlID(), 1);
	SetItemCtlInit(m_btn_sort_icon_manual.GetDlgCtrlID(), 2);
	SetItemCtlInit(m_btn_base_calculator_manual.GetDlgCtrlID(), 3);
	SetItemCtlInit(m_btn_engineering_calculator_manual.GetDlgCtrlID(), 4);
	SetItemCtlInit(m_btn_stopwatch_manual.GetDlgCtrlID(), 5);
	SetItemCtlInit(m_btn_unit_converter_manual.GetDlgCtrlID(), 6);
	SetItemCtlInit(m_btn_date_calculator_manual.GetDlgCtrlID(), 7);
	SetItemCtlInit(m_btn_work_timer_manual.GetDlgCtrlID(), 8);
	SetItemCtlInit(m_btn_notepad_manual.GetDlgCtrlID(), 9);
	SetItemCtlInit(m_btn_base_timer_manual.GetDlgCtrlID(), 10);
	SetItemCtlInit(m_btn_world_clock_manual.GetDlgCtrlID(), 11);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ManualList::SetItemCtlInit(int nCtlID, int nIdx)
{
	CalculateButton* ctlButton = (CalculateButton*)GetDlgItem(nCtlID);
	ctlButton->Initialize(currentTheme->GetFunctionBkColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	ctlButton->m_bUseMouseBkGroundColorEvent = false;
	ctlButton->m_bUseMouseTextItalicEvent = true;
	ctlButton->m_bUseMouseTextBoldEvent = true;
	ctlButton->SetTextColor(currentTheme->GetTextColor());

	ctlButton->MoveWindow(nStartButtonPos_x + ((nButtonWidth + nButtonMargin_x) * (nIdx % 2)), nStartButtonPos_y + ((nButtonHeight + nButtonMargin_y) * (nIdx / 2)), nButtonWidth, nButtonHeight);
}

void ManualList::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void ManualList::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


BOOL ManualList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH ManualList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void ManualList::OnBnClickedButtonBaseCalculatorManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_BASE, usingManualIDVector.at(0), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonEngineeringCalculatorManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_ENGINEERING, usingManualIDVector.at(1), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonStopwatchManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_STOPWATCH, usingManualIDVector.at(2), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonUnitConverterManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_CONVERTER, usingManualIDVector.at(3), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedDateCalculatorManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_DATE, usingManualIDVector.at(4), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonWorkTimerManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_TIMER, usingManualIDVector.at(5), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonNotepadManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_NOTEPAD, usingManualIDVector.at(6), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonBaseTimerManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_BASE_TIMER, usingManualIDVector.at(7), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonWorldClockManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_WORLD_CLOCK, usingManualIDVector.at(8), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonSortIconManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_SORT_ICON, usingManualIDVector.at(9), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonThemeSettingManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_DIALOG_SETTING_THEME, usingManualIDVector.at(10), currentTheme);
	usingManual.DoModal();
}


void ManualList::OnBnClickedButtonMainFrameManual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UsingManualDialog usingManual(false, IDD_BASECALCULATOR_DIALOG, usingManualIDVector.at(11), currentTheme);
	usingManual.DoModal();
}
