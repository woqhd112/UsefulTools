// AllButtonList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "AllButtonList.h"
#include "SortIcon.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// AllButtonList 대화 상자

IMPLEMENT_DYNAMIC(AllButtonList, CDialogEx)

AllButtonList::AllButtonList(std::vector<std::vector<int>> ctlVector, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ALL, pParent)
{
	this->ctlVector = ctlVector;
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	nButtonStackCount = 0;
	nButtonID = 45000;

	bLineEnd = false;

	bButtonHover = true;
	bHoverBase = true;
	bHoverEngineering = true;
	bStopWatch = true;
	bConverter = true;
	bDateCal = true;
	bWorkTimer = true;
	bNotePad = true;
	bBaseTimer = true;
	bWorldClock = true;
	bComingSoon1 = true;
	bComingSoon2 = true;
	bComingSoon3 = true;
	bUseDragDlg = false;

	bDragActivation = false;
	bTopOverDetect = false;
	bLeftOverDetect = false;
	bBottomOverDetect = false;
	bRightOverDetect = false;

	bSortButtonHoverEvent = false;

	bScrollButtonDetect = false;
	//bScrollThread = false;
	//nScrollButtonDetectCount = 0;
}

AllButtonList::~AllButtonList()
{
	DeleteAllButton();
}

void AllButtonList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AllButtonList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// AllButtonList 메시지 처리기


BOOL AllButtonList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());

	sorticon = (SortIcon*)pParent;

	LoadAllButton();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void AllButtonList::DeleteAllButton()
{
	for (int i = 0; i < (int)allButtonVector.size(); i++)
	{
		CGdipButton* button = allButtonVector.at(i);
		delete button;
		button = nullptr;
	}
	allButtonVector.clear();
	nButtonStackCount = 0;
}

ThemeData::FunctionIcon AllButtonList::GetFunctionIconByButtonID(int nButtonID)
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

CString AllButtonList::GetButtonNameByButtonID(int nButtonID)
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

void AllButtonList::CreateExitButton(int nButtonCtlID)
{
	int nStartPos_x = 40;
	int nStartPos_y = 20;
	int nPictureSize = 128;
	int nPictureToPictureMargin_y = 30;

	bool bFindCtlID = false;

	for (int i = 0; i < (int)ctlVector.size(); i++)
	{
		if (ctlVector.at(i).at(0) == nButtonCtlID)
		{
			bFindCtlID = true;
			break;
		}
	}
	if (!bFindCtlID)
	{
		CGdipButton* button = new CGdipButton;
		button->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nButtonID + nButtonCtlID);
		button->ShowWindow(SW_SHOW);

		button->strButtonName = GetButtonNameByButtonID(nButtonCtlID);
		button->LoadStdImage(GetFunctionIconByButtonID(nButtonCtlID).nNormalID, _T("PNG"));
		button->LoadHovImage(GetFunctionIconByButtonID(nButtonCtlID).nHoverID, _T("PNG"));
		button->LoadAltImage(GetFunctionIconByButtonID(nButtonCtlID).nClickID, _T("PNG"));
		button->MoveWindow(nStartPos_x, nStartPos_y + (nPictureSize + nPictureToPictureMargin_y) * nButtonStackCount, nPictureSize, nPictureSize);
		//button->MoveWindow(nStartPos_x, nStartPos_y + (nPictureSize - (nPictureSize / 2 / 2)) * nButtonStackCount, nPictureSize, nPictureSize);

		allButtonVector.push_back(button);
		nButtonStackCount++;

		//CtlToTop();
	}
	else
	{
		bFindCtlID = false;
	}
}

void AllButtonList::CtlToTop()
{
	for (int i = 0; i < (int)allButtonVector.size(); i++)
	{
		for (int j = i; j < allButtonVector.size(); j++)
		{
			allButtonVector.at(i)->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
			allButtonVector.at(j)->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

			allButtonVector.at(i)->BringWindowToTop();
			allButtonVector.at(j)->BringWindowToTop();
		}
	}
}

void AllButtonList::LoadAllButton()
{
	DeleteAllButton();
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_DEFAULT;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 504 - 40 + 9;
	//csi.nOnePageSize = 20 + 128;
	csi.nScrollPos = 0;
	csi.nWheelValue = 30;
	csi.bLikeButtonEvent = false;
	scroll.Initialize(csi);


	int nStartPos_x = 40;
	int nStartPos_y = 20;
	int nPictureSize = 128;
	int nPictureToPictureMargin_y = 30;

	CreateExitButton(IDC_BUTTON_BASE_GDI);
	CreateExitButton(IDC_BUTTON_CALCULATOR_GDI);
	CreateExitButton(IDC_BUTTON_STOPWATCH_GDI);
	CreateExitButton(IDC_BUTTON_CONVERTER_GDI);
	CreateExitButton(IDC_BUTTON_DATE_GDI);
	CreateExitButton(IDC_BUTTON_TIMER_GDI);
	CreateExitButton(IDC_BUTTON_NOTEPAD_GDI);
	CreateExitButton(IDC_BUTTON_BASE_TIMER_GDI);
	CreateExitButton(IDC_BUTTON_WORLD_CLOCK_GDI);
	CreateExitButton(IDC_BUTTON_COMINGSOON_GDI1);
	CreateExitButton(IDC_BUTTON_COMINGSOON_GDI2);
	CreateExitButton(IDC_BUTTON_COMINGSOON_GDI3);
	for (int i = 0; i < ((int)allButtonVector.size() - 1) / 3 + 1; i++)
	{
		scroll.LineEnd();
	}
	scroll.ExecuteScrollPos(currentTheme);
}

HBRUSH AllButtonList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG) // 다이얼로그일 경우
	{
		//CBrush B;
		//B.CreateStockObject(NULL_BRUSH);
		//pDC->SetBkMode(TRANSPARENT); // 투명 설정 
		//return B;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void AllButtonList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	//pParent->Invalidate();
	for (int i = 0; i < (int)allButtonVector.size(); i++)
	{
		allButtonVector.at(i)->DisConnect();
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL AllButtonList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

void AllButtonList::HoverSignal(bool bSignal, bool* bSignalItem)
{
	if (bSignalItem == &bHoverBase) bHoverBase = !bSignal;
	else bHoverBase = bSignal;
	if (bSignalItem == &bHoverEngineering) bHoverEngineering = !bSignal;
	else bHoverEngineering = bSignal;
	if (bSignalItem == &bStopWatch) bStopWatch = !bSignal;
	else bStopWatch = bSignal;
	if (bSignalItem == &bConverter) bConverter = !bSignal;
	else  bConverter = bSignal;
	if (bSignalItem == &bDateCal) bDateCal = !bSignal;
	else bDateCal = bSignal;
	if (bSignalItem == &bWorkTimer) bWorkTimer = !bSignal;
	else bWorkTimer = bSignal;
	if (bSignalItem == &bNotePad) bNotePad = !bSignal;
	else bNotePad = bSignal;
	if (bSignalItem == &bBaseTimer) bBaseTimer = !bSignal;
	else bBaseTimer = bSignal;
	if (bSignalItem == &bWorldClock) bWorldClock = !bSignal;
	else bWorldClock = bSignal;
	if (bSignalItem == &bComingSoon1) bComingSoon1 = !bSignal;
	else bComingSoon1 = bSignal;
	if (bSignalItem == &bComingSoon2) bComingSoon2 = !bSignal;
	else bComingSoon2 = bSignal;
	if (bSignalItem == &bComingSoon3) bComingSoon3 = !bSignal;
	else bComingSoon3 = bSignal;

}

BOOL AllButtonList::DragActivation(POINT mousePoint)
{
	if (bUseDragDlg)
	{
		if (mousePoint.y <= sorticon->dragRect.top)
		{
			bTopOverDetect = true;
			bLeftOverDetect = false;
			bBottomOverDetect = false;
			bRightOverDetect = false;
		}
		else if (mousePoint.y > sorticon->dragRect.bottom)
		{
			bTopOverDetect = false;
			bLeftOverDetect = false;
			bBottomOverDetect = true;
			bRightOverDetect = false;
		}
		else if (mousePoint.x <= sorticon->dragRect.left)
		{
			bTopOverDetect = false;
			bLeftOverDetect = true;
			bBottomOverDetect = false;
			bRightOverDetect = false;
		}
		else if (mousePoint.x > sorticon->dragRect.right)
		{
			bTopOverDetect = false;
			bLeftOverDetect = false;
			bBottomOverDetect = false;
			bRightOverDetect = true;
		}
		else
		{
			bTopOverDetect = false;
			bLeftOverDetect = false;
			bBottomOverDetect = false;
			bRightOverDetect = false;
		}

		if (PtInRect(sorticon->dragRect, mousePoint))
		{
			dragDlg->MoveWindow(mousePoint.x - 32, mousePoint.y - 32, 64, 64);
			dragDlg->newButton->DisConnect();
			return TRUE;
		}
	}
	return FALSE;
}

void AllButtonList::CreateDragButton(CGdipButton* currentClickButton)
{
	SetCapture();
	bDragActivation = true;
	CGdipButton* hoverButton = currentClickButton;
	dragDlg = new DragDialog(hoverButton, pParent->GetParent());

	dragDlg->Create(IDD_DIALOG_DRAG);
	dragDlg->ShowWindow(SW_SHOW);
	bUseDragDlg = true;
}

BOOL AllButtonList::DragEventUp(HWND upHWND, CPoint upPoint)
{
	if (bUseDragDlg)
	{
		ReleaseCapture();
		bDragActivation = false;
		//sorticon->Invalidate();

		// sortbuttonlist의 좌표값 구하기
		POINT convertPoint = upPoint;
		sorticon->ScreenToClient(&convertPoint);
		convertPoint.x = convertPoint.x - 10;
		convertPoint.y = convertPoint.y - 10;
		int nLocToPos = sorticon->sortButtonList->ButtonLocationToPos(convertPoint);
		CRect rect = sorticon->sortButtonList->SetButtonPosition(nLocToPos);


		if (PtInRect(rect, convertPoint))
		{
			if (sorticon->sortButtonList->InsertNewButton(nLocToPos, dragDlg->newButton->nStdImageID, dragDlg->newButton->nHovImageID, dragDlg->newButton->nAltImageID, dragDlg->newButton->strButtonName))
			{
				for (int i = 0; i < (int)allButtonVector.size(); i++)
				{
					CGdipButton* button = allButtonVector.at(i);
					if (allButtonVector.at(i) == downButton)
					{
						nButtonStackCount = 0;
						int nButtonCtlID = 0;
						int nStaticCtlID = 0;

						if (downButton->GetDlgCtrlID() == IDC_BUTTON_BASE_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_BASE_GDI;
							nStaticCtlID = IDC_STATIC_BASE;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_CALCULATOR_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_CALCULATOR_GDI;
							nStaticCtlID = IDC_STATIC_ENGINEERING;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_STOPWATCH_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_STOPWATCH_GDI;
							nStaticCtlID = IDC_STATIC_STOPWATCH;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_CONVERTER_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_CONVERTER_GDI;
							nStaticCtlID = IDC_STATIC_CONVERTER;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_DATE_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_DATE_GDI;
							nStaticCtlID = IDC_STATIC_DATE;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_TIMER_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_TIMER_GDI;
							nStaticCtlID = IDC_STATIC_TIMER1;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_NOTEPAD_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_NOTEPAD_GDI;
							nStaticCtlID = IDC_STATIC_NOTEPAD;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_BASE_TIMER_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_BASE_TIMER_GDI;
							nStaticCtlID = IDC_STATIC_BASE_TIMER;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_WORLD_CLOCK_GDI + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_WORLD_CLOCK_GDI;
							nStaticCtlID = IDC_STATIC_WORLD_CLOCK;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_COMINGSOON_GDI1 + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_COMINGSOON_GDI1;
							nStaticCtlID = 0;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_COMINGSOON_GDI2 + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_COMINGSOON_GDI2;
							nStaticCtlID = 0;
						}
						else if (downButton->GetDlgCtrlID() == IDC_BUTTON_COMINGSOON_GDI3 + nButtonID)
						{
							nButtonCtlID = IDC_BUTTON_COMINGSOON_GDI3;
							nStaticCtlID = 0;
						}

						std::vector<int> ctlItem = { nButtonCtlID, nStaticCtlID, (nLocToPos + 1) + (9 * (sorticon->sortButtonList->scroll.GetCurrentLinePos() - 1)) };
						ctlVector.push_back(ctlItem);

						LoadAllButton();

						break;
					}
				}
			}
			else
			{
				for (int i = 0; i < allButtonVector.size(); i++)
				{
					allButtonVector.at(i)->ShowWindow(SW_SHOW);
				}
			}
		}
		else
		{
			for (int i = 0; i < allButtonVector.size(); i++)
			{
				allButtonVector.at(i)->ShowWindow(SW_SHOW);
			}
		}

		dragDlg->ShowWindow(SW_HIDE);
		delete dragDlg;
		dragDlg = nullptr;
		bUseDragDlg = false;
		sorticon->sortButtonList->EnableEmptyLine(SW_HIDE);

		return TRUE;
	}
	return FALSE;
}

BOOL AllButtonList::DragEventDown(HWND downHWND, CPoint downPoint)
{
	for (int i = 0; i < allButtonVector.size(); i++)
	{
		if (downHWND == allButtonVector.at(i)->m_hWnd)
		{
			if (allButtonVector.at(i)->strButtonName == _T("Base"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("Engineering"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("StopWatch"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("Converter"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("DateCal"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("WorkTimer"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("NotePad"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("BaseTimer"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("WorldClock"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon1"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon2"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
			else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon3"))
			{
				downButton = allButtonVector.at(i);
				CreateDragButton(allButtonVector.at(i));
				dragDlg->MoveWindow(downPoint.x + 2, downPoint.y + 2, 128, 128);
				allButtonVector.at(i)->ShowWindow(SW_HIDE);
				sorticon->sortButtonList->EnableEmptyLine(SW_SHOW);
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL AllButtonList::DragEventMove(HWND moveHWND, CPoint movePoint)
{
	if (bDragActivation)
	{
		if (DragActivation(movePoint))
		{
			// sortbuttonlist의 빈 테두리좌표영역 구하기
			POINT convertPoint = movePoint;
			sorticon->ScreenToClient(&convertPoint);
			convertPoint.x = convertPoint.x - 10;
			convertPoint.y = convertPoint.y - 10;
			int nLocToPos = sorticon->sortButtonList->ButtonLocationToPos(convertPoint);
			CRect rect = sorticon->sortButtonList->SetButtonPosition(nLocToPos);

			// sortbuttonlist의 스크롤내기리 버튼 좌표값 구하기
			POINT scrollButtonPoint = movePoint;
			sorticon->ScreenToClient(&scrollButtonPoint);
			CRect scrollButtonRect;
			sorticon->m_btn_sort_scroll_line.GetWindowRect(scrollButtonRect);
			sorticon->ScreenToClient(scrollButtonRect);

			bool bScrollEvent = false;
			if (PtInRect(scrollButtonRect, scrollButtonPoint))
			{
				if (!bScrollButtonDetect)
				{
					bScrollButtonDetect = true;
					sorticon->m_btn_sort_scroll_line.SetFaceColor(sorticon->m_btn_sort_scroll_line.m_hoverColor);
					bScrollEvent = true;
				}
			}
			else
			{
				if (bScrollButtonDetect)
				{
					bScrollButtonDetect = false;
					sorticon->m_btn_sort_scroll_line.SetFaceColor(sorticon->m_btn_sort_scroll_line.m_defaultColor);
					bScrollEvent = false;
				}
			}

			if (!bScrollEvent)
			{
				if (PtInRect(rect, convertPoint))
				{
					if (nLocToPos != -1)
					{
						bSortButtonHoverEvent = true;
						sorticon->sortButtonList->iconMoveButtonVector.at(nLocToPos)->UseHoverEvent();
					}
				}
				else
				{
					if (bSortButtonHoverEvent)
					{
						bSortButtonHoverEvent = false;
						for (int i = 0; i < (int)sorticon->sortButtonList->iconMoveButtonVector.size(); i++)
						{
							sorticon->sortButtonList->iconMoveButtonVector.at(i)->UserLeaveEvent();
						}
					}
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL AllButtonList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (DragEventUp(pMsg->hwnd, pMsg->pt)) return TRUE;
	}
	else if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (DragEventDown(pMsg->hwnd, pMsg->pt)) return TRUE;
	}
	else if (pMsg->message == WM_MOUSEMOVE)
	{
		if (DragEventMove(pMsg->hwnd, pMsg->pt)) return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}

//UINT AllButtonList::thrScrollDetect(LPVOID method)
//{
//	AllButtonList* thisDlg = (AllButtonList*)method;
//	thisDlg->StartScrollThread();
//	
//	return 0;
//}
//
//void AllButtonList::StartScrollThread()
//{
//	while (bScrollThread)
//	{
//		Sleep(1500);
//		nScrollButtonDetectCount++;
//
//		if (nScrollButtonDetectCount > 0)
//		{
//			sorticon->OnBnClickedButtonSortScrollLine();
//			TRACE(L"scroll count : %d\n", sorticon->sortButtonList->scroll.GetLineCount());
//		}
//	}
//}

void AllButtonList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//::ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}


void AllButtonList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//::SetCapture(this->GetSafeHwnd());
	CDialogEx::OnLButtonDown(nFlags, point);
}


void AllButtonList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnMouseMove(nFlags, point);
}


