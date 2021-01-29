// SortIcon.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "SortIcon.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// SortIcon 대화 상자

IMPLEMENT_DYNAMIC(SortIcon, CDialogEx)

SortIcon::SortIcon(int nManualImageID, bool bUsingManual, CtlVector ctlVector, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SORT_ICON, pParent)
{
	this->ctlVector = ctlVector;
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	this->bUsingManual = bUsingManual;
	nButtonID = 40000;

	usingManual = new UsingManualDialog(true, IDD_DIALOG_SORT_ICON, nManualImageID, currentTheme);
}

SortIcon::~SortIcon()
{
	if (sortButtonList)
	{
		delete sortButtonList;
		sortButtonList = nullptr;
	}

	if (allButtonList)
	{
		delete allButtonList;
		allButtonList = nullptr;
	}

	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
	}
}

void SortIcon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SORT_VIEW, m_stt_sort_view);
	DDX_Control(pDX, IDC_STATIC_ALL_VIEW, m_stt_all_view);
	DDX_Control(pDX, IDC_BUTTON_SORT_SCROLL_LINE, m_btn_sort_scroll_line);
	DDX_Control(pDX, IDC_BUTTON_SORT_SAVE, m_btn_sort_save);
	DDX_Control(pDX, IDC_BUTTON_SORT_RESET, m_btn_sort_reset);
}


BEGIN_MESSAGE_MAP(SortIcon, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_SORT_SCROLL_LINE, &SortIcon::OnBnClickedButtonSortScrollLine)
	ON_BN_CLICKED(IDC_BUTTON_SORT_SAVE, &SortIcon::OnBnClickedButtonSortSave)
	ON_BN_CLICKED(IDC_BUTTON_SORT_RESET, &SortIcon::OnBnClickedButtonSortReset)
END_MESSAGE_MAP()


// SortIcon 메시지 처리기


BOOL SortIcon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundImage(currentTheme->GetMainBkIconID());

	this->SetWindowPos(NULL, 0, 0, MARGIN_X(730), MARGIN_Y(550), SWP_NOMOVE);

	CRect thisRect;
	this->GetWindowRect(thisRect);

	originCtlVector = ctlVector;

	int nBorderWidth = int((thisRect.Width() - 18) / 2);
	int nStartPos_x = 10;
	int nStartPos_y = 10;

	m_stt_sort_view.MoveWindow(nStartPos_x, nStartPos_y, 474 - 10 + 30, 504 - 10);
	m_stt_all_view.MoveWindow(nStartPos_x + 474 - 10 + 30 + 5, nStartPos_y, 730 - (nStartPos_x + 474 - 10 + 30 + 5) - 10, 504 - 10);

	sortButtonList = new SortButtonList(ctlVector, currentTheme, this);
	sortButtonList->Create(IDD_DIALOG_SORT, &m_stt_sort_view);
	sortButtonList->MoveWindow(0, 0, 474 - 10 + 30, 504 - 10);
	sortButtonList->ShowWindow(SW_SHOW);

	allButtonList = new AllButtonList(ctlVector, currentTheme, this);
	allButtonList->Create(IDD_DIALOG_ALL, &m_stt_all_view);
	allButtonList->MoveWindow(0, 0, 730 - (nStartPos_x + 474 - 10 + 30 + 5) - 10, 504 - 10);
	allButtonList->ShowWindow(SW_SHOW);

	GetWindowRect(dragRect);

	m_btn_sort_scroll_line.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_sort_scroll_line.SetTextColor(currentTheme->GetTextColor());
	m_btn_sort_save.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_sort_save.SetTextColor(currentTheme->GetTextColor());
	m_btn_sort_reset.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_sort_reset.SetTextColor(currentTheme->GetTextColor());

	m_btn_sort_scroll_line.MoveWindow(nStartPos_x, nStartPos_y + 504 - 10 + 5, 474 - 10 + 30, 25);

	int nSortButtonStartPos_x = nStartPos_x + 474 - 10 + 30 + 5;
	int nSortButtonStartPos_y = nStartPos_y + 504 - 10 + 5;
	int nSortButtonWidth = (730 - nSortButtonStartPos_x - 10) / 2 - 5;
	int nSortButtonHeight = 25;
	m_btn_sort_save.MoveWindow(nSortButtonStartPos_x, nSortButtonStartPos_y, nSortButtonWidth, nSortButtonHeight);
	m_btn_sort_reset.MoveWindow(nSortButtonStartPos_x + nSortButtonWidth + 10, nSortButtonStartPos_y, nSortButtonWidth, nSortButtonHeight);

	parentDlg = (CBOKOToolsDlg*)pParent;

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL, GetDesktopWindow());
		usingManual->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void SortIcon::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL SortIcon::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH SortIcon::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void SortIcon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


void SortIcon::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect changeRect;
	GetWindowRect(&changeRect);
	dragRect.SetRect(changeRect.left, changeRect.top, dragRect.right + (changeRect.left - dragRect.left), dragRect.bottom + (changeRect.top - dragRect.top));
}


void SortIcon::OnBnClickedButtonSortScrollLine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (sortButtonList->scroll.GetLineCount() > sortButtonList->scroll.GetCurrentLinePos())
	{
		// 스크롤 한단 내리기
		sortButtonList->SendMessageW(WM_VSCROLL, SB_PAGEDOWN, 0);
	}
	else
	{
		// 스크롤 하나 추가하고 한단 내리기
		sortButtonList->scroll.IncreaseScroll();
		sortButtonList->SendMessageW(WM_VSCROLL, SB_PAGEDOWN, 0);
	}
	
}


void SortIcon::OnBnClickedButtonSortSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	sortButtonList->ctlVector.clear();
	allButtonList->ctlVector.clear();
	ctlVector.clear();
	sortButtonList->ctlVector = sortButtonList->saveCtlVector;
	allButtonList->ctlVector = sortButtonList->saveCtlVector;
	ctlVector = sortButtonList->saveCtlVector;
	originCtlVector = sortButtonList->saveCtlVector;
	parentDlg->SaveButtonCtlPos(ctlVector);
}

bool SortIcon::SameVectorCondition(CtlVector thisVector, CtlVector targetVector)
{
	if (thisVector.size() != targetVector.size()) return false;

	bool bReturn = false;
	unsigned short sSameIncreaseCount = 0;
	for (int i = 0; i < (int)thisVector.size(); i++)
	{
		ControlList thisCtlList = thisVector.at(i);
		for (int j = 0; j < (int)targetVector.size(); j++)
		{
			ControlList targetCtlList = targetVector.at(j);
			if (thisCtlList == targetCtlList)
			{
				sSameIncreaseCount++;
				break;
			}
		}
	}
	// 아 id값은 전부 같아도 위치가 달라서 증가안하는거였음ㅋㅋ 맞는부분임
	if (sSameIncreaseCount == (int)thisVector.size() && sSameIncreaseCount == targetVector.size()) bReturn = true;

	return bReturn;
}

void SortIcon::OnBnClickedButtonSortReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SameVectorCondition(sortButtonList->saveCtlVector, originCtlVector))
	{
		return;
	}

	sortButtonList->ctlVector.clear();
	sortButtonList->saveCtlVector.clear();
	allButtonList->ctlVector.clear();
	ctlVector.clear();
	sortButtonList->ctlVector = originCtlVector;
	sortButtonList->saveCtlVector = originCtlVector;
	allButtonList->ctlVector = originCtlVector;
	ctlVector = originCtlVector;

	sortButtonList->LoadSortButton(ctlVector);
	sortButtonList->ButtonBringToTop();
	allButtonList->LoadAllButton();
}

ThemeData::FunctionIcon SortIcon::GetFunctionIconByButtonID(int nButtonID)
{
	if (nButtonID == IDC_BUTTON_BASE_GDI) return currentTheme->GetBaseIcon();
	else if (nButtonID == IDC_BUTTON_CALCULATOR_GDI) return currentTheme->GetEngineeringIcon();
	else if (nButtonID == IDC_BUTTON_STOPWATCH_GDI) return currentTheme->GetStopWatchIcon();
	else if (nButtonID == IDC_BUTTON_CONVERTER_GDI) return currentTheme->GetConverterIcon();
	else if (nButtonID == IDC_BUTTON_DATE_GDI) return currentTheme->GetDateCalIcon();
	else if (nButtonID == IDC_BUTTON_TIMER_GDI) return currentTheme->GetWorkTimerIcon();
	else if (nButtonID == IDC_BUTTON_NOTEPAD_GDI) return currentTheme->GetNotePadIcon();
	else if (nButtonID == IDC_BUTTON_BASE_TIMER_GDI) return currentTheme->GetBaseTimerIcon();
	else if (nButtonID == IDC_BUTTON_WORLD_CLOCK_GDI) return currentTheme->GetWorldClockIcon();
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI1) return currentTheme->GetCommingSoonIcon();
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI2) return currentTheme->GetCommingSoonIcon();
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI3) return currentTheme->GetCommingSoonIcon();

	return currentTheme->GetBaseIcon();
}

CString SortIcon::GetButtonNameByButtonID(int nButtonID)
{
	if (nButtonID == IDC_BUTTON_BASE_GDI) return _T("Base");
	else if (nButtonID == IDC_BUTTON_CALCULATOR_GDI)  return _T("Engineering");
	else if (nButtonID == IDC_BUTTON_STOPWATCH_GDI) return _T("StopWatch");
	else if (nButtonID == IDC_BUTTON_CONVERTER_GDI) return _T("Converter");
	else if (nButtonID == IDC_BUTTON_DATE_GDI) return _T("DateCal");
	else if (nButtonID == IDC_BUTTON_TIMER_GDI) return _T("WorkTimer");
	else if (nButtonID == IDC_BUTTON_NOTEPAD_GDI) return _T("NotePad");
	else if (nButtonID == IDC_BUTTON_BASE_TIMER_GDI) return _T("BaseTimer");
	else if (nButtonID == IDC_BUTTON_WORLD_CLOCK_GDI) return _T("WorldClock");
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI1) return _T("ComingSoon1");
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI2) return _T("ComingSoon2");
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI3) return _T("ComingSoon3");

	return _T("");
}

int SortIcon::GetStaticIDByButtonID(int nButtonID)
{
	int nStaticID = 0;
	if (nButtonID == IDC_BUTTON_BASE_GDI) nStaticID = IDC_STATIC_BASE;
	else if (nButtonID == IDC_BUTTON_CALCULATOR_GDI)  nStaticID = IDC_STATIC_ENGINEERING;
	else if (nButtonID == IDC_BUTTON_STOPWATCH_GDI) nStaticID = IDC_STATIC_STOPWATCH;
	else if (nButtonID == IDC_BUTTON_CONVERTER_GDI) nStaticID = IDC_STATIC_CONVERTER;
	else if (nButtonID == IDC_BUTTON_DATE_GDI) nStaticID = IDC_STATIC_DATE;
	else if (nButtonID == IDC_BUTTON_TIMER_GDI) nStaticID = IDC_STATIC_TIMER1;
	else if (nButtonID == IDC_BUTTON_NOTEPAD_GDI) nStaticID = IDC_STATIC_NOTEPAD;
	else if (nButtonID == IDC_BUTTON_BASE_TIMER_GDI) nStaticID = IDC_STATIC_BASE_TIMER;
	else if (nButtonID == IDC_BUTTON_WORLD_CLOCK_GDI) nStaticID = IDC_STATIC_WORLD_CLOCK;
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI1) nStaticID = 0;
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI2) nStaticID = 0;
	else if (nButtonID == IDC_BUTTON_COMINGSOON_GDI3) nStaticID = 0;

	return nStaticID;
}