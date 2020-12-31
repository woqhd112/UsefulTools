// AllButtonList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "AllButtonList.h"
#include "SortIcon.h"
#include "afxdialogex.h"


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

	bDragActivation = false;
	bBottomDragChange = false;
	bRightDragChange = false;
}

AllButtonList::~AllButtonList()
{
	for (int i = 0; i < (int)allButtonVector.size(); i++)
	{
		CGdipButton* button = allButtonVector.at(i);
		delete button;
		button = nullptr;
	}
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

void AllButtonList::StackCountCondition()
{
	if (nButtonStackCount > 0)
	{
		if (nButtonStackCount % 3 == 0) scroll.LineEnd();
	}
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
		button->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nButtonID++);
		button->ShowWindow(SW_SHOW);

		button->strButtonName = GetButtonNameByButtonID(nButtonCtlID);
		button->LoadStdImage(GetFunctionIconByButtonID(nButtonCtlID).nNormalID, _T("PNG"));
		button->LoadHovImage(GetFunctionIconByButtonID(nButtonCtlID).nHoverID, _T("PNG"));
		button->LoadAltImage(GetFunctionIconByButtonID(nButtonCtlID).nClickID, _T("PNG"));
		//button->MoveWindow(nStartPos_x, nStartPos_y + (nPictureSize + nPictureToPictureMargin_y) * nButtonStackCount, nPictureSize, nPictureSize);
		button->MoveWindow(nStartPos_x, nStartPos_y + (nPictureSize - (nPictureSize / 2 / 2)) * nButtonStackCount, nPictureSize, nPictureSize);

		allButtonVector.push_back(button);
		nButtonStackCount++;

		CtlToTop();
	}
	else
	{
		bFindCtlID = false;
	}
	StackCountCondition();
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
	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_DEFAULT;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 504 - 40 + 9;
	csi.nScrollPos = 0;
	csi.nWheelValue = 30;
	scroll.Initialize(csi);


	int nStartPos_x = 40;
	int nStartPos_y = 20;
	int nPictureSize = 128;
	int nPictureToPictureMargin_y = 30;
	int nButtonID = 45000;

	bool bFindCtlID = false;

	// 첫번쨰 버튼
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
	if (dragDlg)
	{
		if (mousePoint.y + 128 - 2 > sorticon->dragRect.bottom && mousePoint.x + 128 - 2 <= sorticon->dragRect.right)
		{
			mousePoint.y = mousePoint.y - 128;
			if (!bBottomDragChange)
			{
				bBottomDragChange = true;
				sorticon->dragRect.top = sorticon->dragRect.top - 128;
				sorticon->dragRect.bottom = sorticon->dragRect.bottom - 128;
			}
		}
		else if (mousePoint.y + 128 - 2 <= sorticon->dragRect.bottom && mousePoint.x + 128 - 2 > sorticon->dragRect.right)
		{
			mousePoint.x = mousePoint.x - 128;
			if (!bRightDragChange)
			{
				bRightDragChange = true;
				sorticon->dragRect.left = sorticon->dragRect.left - 128;
				sorticon->dragRect.right = sorticon->dragRect.right - 128;
			}
		}
		else if (mousePoint.y + 128 - 2 > sorticon->dragRect.bottom && mousePoint.x + 128 - 2 > sorticon->dragRect.right)
		{
			mousePoint.x = mousePoint.x - 128;
			mousePoint.y = mousePoint.y - 128;
			if (!bBottomDragChange && !bRightDragChange)
			{
				bBottomDragChange = true;
				bRightDragChange = true;
				sorticon->dragRect.top = sorticon->dragRect.top - 128;
				sorticon->dragRect.bottom = sorticon->dragRect.bottom - 128;
				sorticon->dragRect.left = sorticon->dragRect.left - 128;
				sorticon->dragRect.right = sorticon->dragRect.right - 128;
			}
		}
		else
		{
			if (bBottomDragChange)
			{
				bBottomDragChange = false;
				sorticon->dragRect.top = sorticon->dragRect.top + 128;
				sorticon->dragRect.bottom = sorticon->dragRect.bottom + 128;
			}
			if (bRightDragChange)
			{
				bRightDragChange = false;
				sorticon->dragRect.left = sorticon->dragRect.left + 128;
				sorticon->dragRect.right = sorticon->dragRect.right + 128;
			}
		}

		if (PtInRect(sorticon->dragRect, mousePoint))
		{
			dragDlg->MoveWindow(mousePoint.x + 2, mousePoint.y + 2, 128, 128);
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
}

BOOL AllButtonList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (dragDlg)
		{
			ReleaseCapture();
			bDragActivation = false;
			dragDlg->ShowWindow(SW_HIDE);
			delete dragDlg;
			dragDlg = nullptr;
		}
	}
	else if (pMsg->message == WM_LBUTTONDOWN)
	{
		for (int i = 0; i < allButtonVector.size(); i++)
		{
			if (pMsg->hwnd == allButtonVector.at(i)->m_hWnd)
			{
				if (allButtonVector.at(i)->strButtonName == _T("Base"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					//allButtonVector.at(i)->DisConnect();
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("Engineering"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("StopWatch"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("Converter"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("DateCal"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("WorkTimer"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("NotePad"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("BaseTimer"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("WorldClock"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon1"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon2"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
				else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon3"))
				{
					CreateDragButton(allButtonVector.at(i));
					dragDlg->MoveWindow(pMsg->pt.x + 2, pMsg->pt.y + 2, 128, 128);
					return TRUE;
				}
			}
		}
	}
	else if (pMsg->message == WM_MOUSEMOVE)
	{
		if (bDragActivation)
		{
			if (DragActivation(pMsg->pt))
			{
				//dragDlg->newButton->DisConnect();
				//dragDlg->Invalidate();
				return TRUE;
			}
		}


		if (pMsg->hwnd == this->m_hWnd)
		{
			if (!bHoverBase || !bHoverEngineering || !bStopWatch || !bConverter || !bDateCal || !bWorkTimer || !bNotePad || !bBaseTimer || !bWorldClock || !bComingSoon1 || !bComingSoon2 || !bComingSoon3)
			{
				//hoverButton = nullptr;
				HoverSignal(true, 0);
				CtlToTop();
			}
		}
		else
		{
			for (int i = 0; i < allButtonVector.size(); i++)
			{
				if (pMsg->hwnd == allButtonVector.at(i)->m_hWnd)
				{
					if (allButtonVector.at(i)->strButtonName == _T("Base"))
					{
						if (bHoverBase)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bHoverBase);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
							break;
						}

					}
					else if (allButtonVector.at(i)->strButtonName == _T("Engineering"))
					{
						if (bHoverEngineering)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bHoverEngineering);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
							break;
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("StopWatch"))
					{
						if (bStopWatch)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bStopWatch);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
							break;
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("Converter"))
					{
						if (bConverter)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bConverter);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("DateCal"))
					{
						if (bDateCal)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bDateCal);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("WorkTimer"))
					{
						if (bWorkTimer)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bWorkTimer);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("NotePad"))
					{
						if (bNotePad)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bNotePad);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("BaseTimer"))
					{
						if (bBaseTimer)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bBaseTimer);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("WorldClock"))
					{
						if (bWorldClock)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bWorldClock);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon1"))
					{
						if (bComingSoon1)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bComingSoon1);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon2"))
					{
						if (bComingSoon2)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bComingSoon2);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
					else if (allButtonVector.at(i)->strButtonName == _T("ComingSoon3"))
					{
						if (bComingSoon3)
						{
							//hoverButton = allButtonVector.at(i);
							HoverSignal(true, &bComingSoon3);
							CtlToTop();
							allButtonVector.at(i)->BringWindowToTop();
						}
					}
				}
			}
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


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


