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
}


BEGIN_MESSAGE_MAP(SortIcon, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// SortIcon 메시지 처리기


BOOL SortIcon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundImage(currentTheme->GetMainBkIconID());

	CRect SystemRect;
	CPoint pos;
	GetClientRect(SystemRect);
	pos.x = LONG(GetSystemMetrics(SM_CXSCREEN) / 2.0f - SystemRect.Width() / 2.0f);
	pos.y = LONG(GetSystemMetrics(SM_CYSCREEN) / 2.0f - SystemRect.Height() / 2.0f);

	// 윈도우의 다이얼로그 사이즈는 양옆 위아래로 9씩의 마진값과 상단 타이틀의 38의 마진값을 가진다.
	// 그래서 사이즈 조정시 넓이 + 18, 높이 + 47을 입력해야한다.
	//this->MoveWindow(pos.x, pos.y, nVector_X, nVector_Y);
	this->MoveWindow(pos.x, pos.y, MARGIN_X(730), MARGIN_Y(550));

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
	if (allButtonList)
	{
		allButtonList->bBottomDragChange = false;
		allButtonList->bRightDragChange = false;
	}
}
