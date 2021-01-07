// SortIcon.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "SortIcon.h"
#include "afxdialogex.h"


// SortIcon 대화 상자

IMPLEMENT_DYNAMIC(SortIcon, CDialogEx)

SortIcon::SortIcon(std::vector<std::vector<int>> ctlVector, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SORT_ICON, pParent)
{
	this->ctlVector = ctlVector;
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	nButtonID = 40000;
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
}

void SortIcon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SORT_VIEW, m_stt_sort_view);
	DDX_Control(pDX, IDC_STATIC_ALL_VIEW, m_stt_all_view);
	DDX_Control(pDX, IDC_BUTTON_SORT_SCROLL_LINE, m_btn_sort_scroll_line);
	DDX_Control(pDX, IDC_BUTTON_SORT_SAVE, m_btn_sort_save);
}


BEGIN_MESSAGE_MAP(SortIcon, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_SORT_SCROLL_LINE, &SortIcon::OnBnClickedButtonSortScrollLine)
	ON_BN_CLICKED(IDC_BUTTON_SORT_SAVE, &SortIcon::OnBnClickedButtonSortSave)
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

	m_btn_sort_scroll_line.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_sort_scroll_line.SetTextColor(currentTheme->GetTextColor());
	m_btn_sort_save.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_sort_save.SetTextColor(currentTheme->GetTextColor());

	m_btn_sort_scroll_line.MoveWindow(nStartPos_x, nStartPos_y + 504 - 10 + 5, 474 - 10 + 30, 25);
	m_btn_sort_save.MoveWindow(nStartPos_x + 474 - 10 + 30 + 5, nStartPos_y + 504 - 10 + 5, 730 - (nStartPos_x + 474 - 10 + 30 + 5) - 10, 25);

	parentDlg = (CBOKOToolsDlg*)pParent;

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
	CRect rect;
	m_stt_sort_view.GetWindowRect(rect);
	if(PtInRect(rect, pMsg->pt))
	{
		//TRACE(L"? : %d\n", pMsg->message);
		if (pMsg->message == 647)
		{
			
		}
	}

	m_stt_all_view.GetWindowRect(rect);
	if (PtInRect(rect, pMsg->pt))
	{
	}
	if (pMsg->message == 647)
	{
		/*CGdipButton* hoverButton = allButtonList->hoverButton;
		if (hoverButton != nullptr)
		{
			dragDlg = new DragDialog(currentTheme, hoverButton);
			dragDlg->Create(IDD_DIALOG_DRAG);
			dragDlg->ShowWindow(SW_SHOW);
			dragDlg->MoveWindow(pMsg->pt.x, pMsg->pt.y, 128, 128);
		}*/
	}
	//TRACE(L"? : %d\n", pMsg->message);
	if (pMsg->message == WM_MOUSEMOVE)
	{

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
	parentDlg->SaveButtonCtlPos(ctlVector);
}
