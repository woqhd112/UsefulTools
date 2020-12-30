// SortButtonList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "SortButtonList.h"
#include "afxdialogex.h"


// SortButtonList 대화 상자

IMPLEMENT_DYNAMIC(SortButtonList, CDialogEx)

SortButtonList::SortButtonList(std::vector<std::vector<int>> ctlVector, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SORT, pParent)
{
	this->ctlVector = ctlVector;
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	nButtonID = 40000;
}

SortButtonList::~SortButtonList()
{
	for (int i = 0; i < (int)sortButtonVector.size(); i++)
	{
		CGdipButton* button = sortButtonVector.at(i);
		delete button;
		button = nullptr;
	}
}

void SortButtonList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SortButtonList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// SortButtonList 메시지 처리기


BOOL SortButtonList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	LoadSortButton();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CRect SortButtonList::SetButtonPosition(int nItemCount)
{
	int nStartPos_x = 35;
	int nStartPos_y = 20;
	int nPictureSize = 128;

	int nPictureToPictureMargin_y = 30;
	int nPictureToPictureMargin_x = 20;
	CRect ButtonPos;

	nStartPos_y += ((nPictureSize + nPictureToPictureMargin_y) * (nItemCount / 3));

	nStartPos_x += ((nPictureSize + nPictureToPictureMargin_x) * (nItemCount % 3));

	ButtonPos = { nStartPos_x, nStartPos_y, nStartPos_x + nPictureSize, nStartPos_y + nPictureSize };
	return ButtonPos;
}

void SortButtonList::LoadSortButton()
{
	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 504 - 40 + 9;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	CGdipButton* button;

	for (int i = 0; i < (int)ctlVector.size(); i++)
	{
		bool bEnd = true;
		button = new CGdipButton;
		button->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nButtonID++);
		button->ShowWindow(SW_SHOW);

		CRect ButtonPos = SetButtonPosition(i);
		if ((i + 1) % 9 == 0)
		{
			bEnd = false;
			scroll.LineEnd();
		}
		if (bEnd)
		{
			if (i == (int)ctlVector.size() - 1)  scroll.LineEnd();
		}

		if (ctlVector.at(i).at(0) == IDC_BUTTON_BASE_GDI)
		{
			button->LoadStdImage(currentTheme->GetBaseIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetBaseIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetBaseIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_CALCULATOR_GDI)
		{
			button->LoadStdImage(currentTheme->GetEngineeringIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetEngineeringIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetEngineeringIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_STOPWATCH_GDI)
		{
			button->LoadStdImage(currentTheme->GetStopWatchIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetStopWatchIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetStopWatchIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_CONVERTER_GDI)
		{
			button->LoadStdImage(currentTheme->GetConverterIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetConverterIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetConverterIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_DATE_GDI)
		{
			button->LoadStdImage(currentTheme->GetDateCalIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetDateCalIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetDateCalIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_TIMER_GDI)
		{
			button->LoadStdImage(currentTheme->GetWorkTimerIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetWorkTimerIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetWorkTimerIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_NOTEPAD_GDI)
		{
			button->LoadStdImage(currentTheme->GetNotePadIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetNotePadIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetNotePadIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_BASE_TIMER_GDI)
		{
			button->LoadStdImage(currentTheme->GetBaseTimerIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetBaseTimerIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetBaseTimerIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_WORLD_CLOCK_GDI)
		{
			button->LoadStdImage(currentTheme->GetWorldClockIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetWorldClockIcon().nHoverID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetWorldClockIcon().nClickID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_COMINGSOON_GDI1)
		{
			button->LoadStdImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_COMINGSOON_GDI2)
		{
			button->LoadStdImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
		}
		else if (ctlVector.at(i).at(0) == IDC_BUTTON_COMINGSOON_GDI3)
		{
			button->LoadStdImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
			button->LoadHovImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
			button->LoadAltImage(currentTheme->GetCommingSoonIcon().nNormalID, _T("PNG"));
		}

		sortButtonVector.push_back(button);
		button->MoveWindow(ButtonPos);
	}
	scroll.ExecuteScrollPos(currentTheme);
}

HBRUSH SortButtonList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG) // 다이얼로그일 경우
	{
		CBrush B;
		B.CreateStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT); // 투명 설정 
		
		return B;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void SortButtonList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	pParent->Invalidate();
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL SortButtonList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (scroll.GetLineCount() > 1)
	{
		UINT nFlag = scroll.OperateWheel(zDelta);
		if (nFlag == SB_PAGEUP && scroll.GetCurrentLinePos() == 1) {}
		else if (nFlag == SB_PAGEDOWN && scroll.GetCurrentLinePos() == scroll.GetLineCount()) {}
		else { OnVScroll(nFlag, 0, GetScrollBarCtrl(SB_VERT)); }
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
