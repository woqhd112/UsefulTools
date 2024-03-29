﻿// SortButtonList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "SortButtonList.h"
#include "SortIcon.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// SortButtonList 대화 상자

IMPLEMENT_DYNAMIC(SortButtonList, CDialogEx)

SortButtonList::SortButtonList(CtlVector ctlVector, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SORT, pParent)
{
	this->ctlVector = ctlVector;
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	nButtonID = 40000;
	nEmptyDrawLineID = 50000;

	nStdID = 0;
	nHovID = 0;
	nAltID = 0;
	strButtonName = _T("");

	/*
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
	bComingSoon3 = true;*/

	nLineEndCount = 0;

	bSortButtonHoverEvent = false;
}

SortButtonList::~SortButtonList()
{
	DeleteButonVector(sortButtonVector);
	DeleteButonVector(iconMoveButtonVector);
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

	this->SetBackgroundImage(currentTheme->GetMainBkIconID());

	sorticon = (SortIcon*)pParent;
	saveCtlVector = ctlVector;
	LoadSortButton(ctlVector);
	
	Init(this, sorticon, BIND_HALF, MODE_BUTTONVIEW);

	DrawEmptyLine();
	EnableEmptyLine(SW_HIDE);

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

int SortButtonList::ButtonLocationToPos(POINT pt)
{
	int nResult = -1;

	int nStartPos_x = 35;
	int nStartPos_y = 20;
	int nPictureSize = 128;

	int nPictureToPictureMargin_y = 30;
	int nPictureToPictureMargin_x = 20;

	int nPosX = pt.x;
	int nPosY = pt.y;

	int nCount = 0;
	bool bFind = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (nPosX >= nStartPos_x + (nPictureSize + nPictureToPictureMargin_x) * j && nPosX <= nStartPos_x + nPictureSize + (nPictureToPictureMargin_x + nPictureSize) * j &&
				nPosY >= nStartPos_y + (nPictureSize + nPictureToPictureMargin_y) * i && nPosY <= nStartPos_y + nPictureSize + (nPictureSize + nPictureToPictureMargin_y) * i)
			{
				nResult = nCount;
				bFind = true;
				break;
			}
			nCount++;
		}
		if (bFind) break;
	}

	return nResult;
}

bool SortButtonList::ExistButtonPos(int nButtonIndex)
{
	bool bExistButtonPos = false;
	for (int i = 0; i < (int)saveCtlVector.size(); i++)
	{
		std::vector<int> saveCtl = saveCtlVector.at(i);
		if (saveCtl.at(2) == (nButtonIndex + 1) + (9 * (scroll.GetCurrentLinePos() - 1)))
		{
			bExistButtonPos = true;
		}
	}

	if (nButtonIndex == -1)
		bExistButtonPos = true;
	
	return bExistButtonPos;
}

bool SortButtonList::InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName)
{
	if (ExistButtonPos(nButtonVectorIndex))
	{
		return false;
	}

	int nButtonCtlID = 0;
	int nStaticCtlID = 0;
	if (strButtonName == _T("Base"))
	{
		nButtonCtlID = IDC_BUTTON_BASE_GDI;
		nStaticCtlID = IDC_STATIC_BASE;
	}
	else if (strButtonName == _T("Engineering"))
	{
		nButtonCtlID = IDC_BUTTON_CALCULATOR_GDI;
		nStaticCtlID = IDC_STATIC_ENGINEERING;
	}
	else if (strButtonName == _T("StopWatch"))
	{
		nButtonCtlID = IDC_BUTTON_STOPWATCH_GDI;
		nStaticCtlID = IDC_STATIC_STOPWATCH;
	}
	else if (strButtonName == _T("Converter"))
	{
		nButtonCtlID = IDC_BUTTON_CONVERTER_GDI;
		nStaticCtlID = IDC_STATIC_CONVERTER;
	}
	else if (strButtonName == _T("DateCal"))
	{
		nButtonCtlID = IDC_BUTTON_DATE_GDI;
		nStaticCtlID = IDC_STATIC_DATE;
	}
	else if (strButtonName == _T("WorkTimer"))
	{
		nButtonCtlID = IDC_BUTTON_TIMER_GDI;
		nStaticCtlID = IDC_STATIC_TIMER1;
	}
	else if (strButtonName == _T("NotePad"))
	{
		nButtonCtlID = IDC_BUTTON_NOTEPAD_GDI;
		nStaticCtlID = IDC_STATIC_NOTEPAD;
	}
	else if (strButtonName == _T("BaseTimer"))
	{
		nButtonCtlID = IDC_BUTTON_BASE_TIMER_GDI;
		nStaticCtlID = IDC_STATIC_BASE_TIMER;
	}
	else if (strButtonName == _T("WorldClock"))
	{
		nButtonCtlID = IDC_BUTTON_WORLD_CLOCK_GDI;
		nStaticCtlID = IDC_STATIC_WORLD_CLOCK;
	}
	else if (strButtonName == _T("ComingSoon1"))
	{
		nButtonCtlID = IDC_BUTTON_COMINGSOON_GDI1;
		nStaticCtlID = 0;
	}
	else if (strButtonName == _T("ComingSoon2"))
	{
		nButtonCtlID = IDC_BUTTON_COMINGSOON_GDI2;
		nStaticCtlID = 0;
	}
	else if (strButtonName == _T("ComingSoon3"))
	{
		nButtonCtlID = IDC_BUTTON_COMINGSOON_GDI3;
		nStaticCtlID = 0;
	}

	CGdipButton* button = new CGdipButton;
	button->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nButtonCtlID + nButtonID);
	button->ShowWindow(SW_SHOW);

	CRect ButtonPos = SetButtonPosition(nButtonVectorIndex);

	button->strButtonName = strButtonName;
	button->LoadStdImage(nStdID, _T("PNG"));
	button->LoadHovImage(nHovID, _T("PNG"));
	button->LoadAltImage(nAltID, _T("PNG"));
		
	sortButtonVector.push_back(button);
	button->MoveWindow(ButtonPos);
	
	std::vector<int> newCtlVector;
	newCtlVector = { nButtonCtlID , nStaticCtlID , (nButtonVectorIndex + 1) + (9 * (scroll.GetCurrentLinePos() - 1)) };

	ButtonBringToTop();

	for (int i = 0; i < saveCtlVector.size(); i++)
	{
		if (saveCtlVector.at(i).at(0) == newCtlVector.at(0))
		{
			//TRACE(L"같은곳에서 자리이동 button pos : %d\n", nButtonVectorIndex);
			saveCtlVector.at(i).at(2) = nButtonVectorIndex + 1;
			return true;
		}
	}
	//TRACE(L"새로추가 button pos : %d\n", nButtonVectorIndex);
	saveCtlVector.push_back(newCtlVector);

	return true;
}


void SortButtonList::LoadSortButton(CtlVector ctlVector)
{
	DeleteButonVector(sortButtonVector);

	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.csf = CustomScroll::CUSTOM_SCROLL_FLAGS_VERTICAL;
	csi.nAllPageSize = 0;
	csi.nOnePageSize = 504 - 40 + 9;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	CGdipButton* button;

	for (int i = 0; i < (int)ctlVector.size(); i++)
	{
		button = new CGdipButton;
		button->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, ctlVector.at(i).at(0) + nButtonID);
		button->ShowWindow(SW_SHOW);

		CRect ButtonPos = SetButtonPosition(ctlVector.at(i).at(2) - 1);

		button->strButtonName = sorticon->GetButtonNameByButtonID(ctlVector.at(i).at(0));
		button->LoadStdImage(sorticon->GetFunctionIconByButtonID(ctlVector.at(i).at(0)).nNormalID, _T("PNG"));
		button->LoadHovImage(sorticon->GetFunctionIconByButtonID(ctlVector.at(i).at(0)).nHoverID, _T("PNG"));
		button->LoadAltImage(sorticon->GetFunctionIconByButtonID(ctlVector.at(i).at(0)).nClickID, _T("PNG"));

		sortButtonVector.push_back(button);
		button->MoveWindow(ButtonPos);
	}

	int nMax = ctlVector.at(0).at(2) - 1;
	for (int i = 0; i < ctlVector.size(); i++)
	{
		if (ctlVector.at(i).at(2) - 1 > nMax)
		{
			nMax = ctlVector.at(i).at(2) - 1;
		}
	}
	nLineEndCount = nMax / 9;

	//nLineEndCount = ctlVector.at(ctlVector.size() - 1).at(2) / 9;
	for (int i = 0; i <= nLineEndCount; i++)
	{
		scroll.LineEnd();
	}

	scroll.ExecuteScrollPos(currentTheme);
}

HBRUSH SortButtonList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	//if (nCtlColor == CTLCOLOR_DLG) // 다이얼로그일 경우
	//{
	//	CBrush B;
	//	B.CreateStockObject(NULL_BRUSH);
	//	pDC->SetBkMode(TRANSPARENT); // 투명 설정 
	//	
	//	return B;
	//}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void SortButtonList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	sorticon->Invalidate();
	for (int i = 0; i < (int)iconMoveButtonVector.size(); i++)
	{
		iconMoveButtonVector.at(i)->DisConnect();
	}
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

void SortButtonList::EnableEmptyLine(int bShow)
{
	for (int i = 0; i < (int)iconMoveButtonVector.size(); i++)
	{
		CGdipButton* lineButton = iconMoveButtonVector.at(i);
		CRect posRect = SetButtonPosition(i);
		lineButton->MoveWindow(posRect);
		lineButton->ShowWindow(bShow);
		lineButton->DisConnect();
	}
}

void SortButtonList::DrawEmptyLine()
{
	for (int i = 0; i < 9; i++)
	{
		CRect Pos = SetButtonPosition(i);

		CGdipButton* iconMoveButton = new CGdipButton;
		iconMoveButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nEmptyDrawLineID++);
		iconMoveButton->ShowWindow(SW_SHOW);
		iconMoveButton->MoveWindow(Pos.left, Pos.top, 128, 128);

		iconMoveButton->LoadStdImage(IDB_PNG_ICON_MOVE_NOMAL, _T("PNG"));
		iconMoveButton->LoadHovImage(IDB_PNG_ICON_MOVE_HOVER, _T("PNG"));
		iconMoveButton->LoadAltImage(IDB_PNG_ICON_MOVE_NOMAL, _T("PNG"));
		iconMoveButton->m_bUseMouseEvent = false;

		if (i < sortButtonVector.size())
		{
			sortButtonVector.at(i)->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
			iconMoveButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
			sortButtonVector.at(i)->BringWindowToTop();
		}

		iconMoveButtonVector.push_back(iconMoveButton);
	}

	ButtonBringToTop();
}

void SortButtonList::ButtonBringToTop()
{
	for (int i = 0; i < (int)sortButtonVector.size(); i++)
	{
		CGdipButton* sortButton = sortButtonVector.at(i);
		for (int j = 0; j < (int)iconMoveButtonVector.size(); j++)
		{
			CGdipButton* lineButton = iconMoveButtonVector.at(j);
			sortButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
			lineButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
			sortButton->BringWindowToTop();
		}
	}
}




//void SortButtonList::HoverSignal(bool bSignal, bool* bSignalItem)
//{
//	if (bSignalItem == &bHoverBase) bHoverBase = !bSignal;
//	else bHoverBase = bSignal;
//	if (bSignalItem == &bHoverEngineering) bHoverEngineering = !bSignal;
//	else bHoverEngineering = bSignal;
//	if (bSignalItem == &bStopWatch) bStopWatch = !bSignal;
//	else bStopWatch = bSignal;
//	if (bSignalItem == &bConverter) bConverter = !bSignal;
//	else  bConverter = bSignal;
//	if (bSignalItem == &bDateCal) bDateCal = !bSignal;
//	else bDateCal = bSignal;
//	if (bSignalItem == &bWorkTimer) bWorkTimer = !bSignal;
//	else bWorkTimer = bSignal;
//	if (bSignalItem == &bNotePad) bNotePad = !bSignal;
//	else bNotePad = bSignal;
//	if (bSignalItem == &bBaseTimer) bBaseTimer = !bSignal;
//	else bBaseTimer = bSignal;
//	if (bSignalItem == &bWorldClock) bWorldClock = !bSignal;
//	else bWorldClock = bSignal;
//	if (bSignalItem == &bComingSoon1) bComingSoon1 = !bSignal;
//	else bComingSoon1 = bSignal;
//	if (bSignalItem == &bComingSoon2) bComingSoon2 = !bSignal;
//	else bComingSoon2 = bSignal;
//	if (bSignalItem == &bComingSoon3) bComingSoon3 = !bSignal;
//	else bComingSoon3 = bSignal;
//
//}

void SortButtonList::DeleteButonVector(ButtonVector& buttonVector)
{
	for (int i = 0; i < buttonVector.size(); i++)
	{
		CGdipButton* deleteButton = buttonVector.at(i);
		deleteButton->DestroyWindow();
		delete deleteButton;
		deleteButton = nullptr;
	}
	buttonVector.clear();
}

BOOL SortButtonList::DragEventUp(HWND upHWND, CPoint upPoint, CGdipButton* findbutton)
{
	BOOL bReturn = FALSE;
	if (ExistDragDlg())
	{
		POINT convertPoint = upPoint;
		sorticon->ScreenToClient(&convertPoint);
		convertPoint.x = convertPoint.x - 10;
		convertPoint.y = convertPoint.y - 10;

		int nLocToPos = ButtonLocationToPos(convertPoint);

		CRect rect = SetButtonPosition(nLocToPos);

		POINT revertPoint = upPoint;
		sorticon->ScreenToClient(&revertPoint);
		CRect revertButtonRect;
		sorticon->allButtonList->GetWindowRect(revertButtonRect);
		sorticon->ScreenToClient(revertButtonRect);

		bool bCursorRevertButton = false;
		if (PtInRect(revertButtonRect, revertPoint))
		{
			for (int i = 0; i < (int)sortButtonVector.size(); i++)
			{
				CGdipButton* button = sortButtonVector.at(i);
				if (sortButtonVector.at(i) == downButton)
				{
					int nButtonCtlID = sortButtonVector.at(i)->GetDlgCtrlID() - nButtonID;
					for (int j = 0; j < saveCtlVector.size(); j++)
					{
						if (nButtonCtlID == saveCtlVector.at(j).at(0))
						{
							saveCtlVector.erase(saveCtlVector.begin() + j);
						}
					}

					for (int j = 0; j < sorticon->allButtonList->ctlVector.size(); j++)
					{
						if (sorticon->allButtonList->ctlVector.at(j).at(0) == nButtonCtlID)
						{
							sorticon->allButtonList->ctlVector.erase(sorticon->allButtonList->ctlVector.begin() + j);
							break;
						}
					}
					sorticon->allButtonList->LoadAllButton();

					sortButtonVector.erase(sortButtonVector.begin() + i);
					button->DestroyWindow();
					delete button;
					button = nullptr;
					bCursorRevertButton = true;
					break;
				}
			}
		}

		if (!bCursorRevertButton)
		{
			if (PtInRect(rect, convertPoint))
			{
				if (InsertNewButton(nLocToPos, nStdID, nHovID, nAltID, strButtonName))
				{
					for (int i = 0; i < sortButtonVector.size(); i++)
					{
						if (sortButtonVector.at(i) == downButton)
						{
							CGdipButton* button = sortButtonVector.at(i);
							sortButtonVector.erase(sortButtonVector.begin() + i);
							button->DestroyWindow();
							delete button;
							button = nullptr;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < sortButtonVector.size(); i++)
					{
						sortButtonVector.at(i)->ShowWindow(SW_SHOW);
					}
				}
			}
			else
			{
				for (int i = 0; i < sortButtonVector.size(); i++)
				{
					sortButtonVector.at(i)->ShowWindow(SW_SHOW);
				}
			}
		}

		DeleteDragDlg();
		nStdID = 0;
		nHovID = 0;
		nAltID = 0;
		strButtonName = _T("");
		EnableEmptyLine(SW_HIDE);

		bReturn = TRUE;

		CloseDragEvent();
	}
	return bReturn;
}

BOOL SortButtonList::DragEventDown(HWND downHWND, CPoint downPoint, CGdipButton* findbutton)
{
	BOOL bReturn = FALSE;
	CGdipButton* findButton = NULL;
	if (FindButtonSame(sortButtonVector, downHWND, &findButton))
	{
		if (findButton != NULL)
		{
			ExecuteDragEvent(findButton);
			nStdID = findButton->nStdImageID;
			nHovID = findButton->nHovImageID;
			nAltID = findButton->nAltImageID;
			strButtonName = findButton->strButtonName;
			SetSizeDragDlg(CRect(downPoint.x + 2, downPoint.y + 2, downPoint.x + 2 + 128, downPoint.y + 2 + 128));
			downButton = findButton;
			findButton->ShowWindow(SW_HIDE);
			EnableEmptyLine(SW_SHOW);
			bReturn = TRUE;
		}
	}
	return bReturn;
}

BOOL SortButtonList::DragEventMove(HWND moveHWND, CPoint movePoint, CGdipButton* findbutton)
{
	BOOL bReturn = FALSE;
	if (IsDragging(sorticon->dragRect, movePoint))
	{
		POINT convertPoint = movePoint;
		sorticon->ScreenToClient(&convertPoint);
		convertPoint.x = convertPoint.x - 10;
		convertPoint.y = convertPoint.y - 10;

		int nLocToPos = ButtonLocationToPos(convertPoint);

		CRect rect = SetButtonPosition(nLocToPos);
		if (PtInRect(rect, convertPoint))
		{
			if (nLocToPos != -1)
			{
				bSortButtonHoverEvent = true;
				iconMoveButtonVector.at(nLocToPos)->UseHoverEvent();
			}
		}
		else
		{
			if (bSortButtonHoverEvent)
			{
				bSortButtonHoverEvent = false;
				for (int i = 0; i < (int)iconMoveButtonVector.size(); i++)
				{
					iconMoveButtonVector.at(i)->UseLeaveEvent();
				}
			}
		}
		bReturn = TRUE;
	}

	return bReturn;
}

BOOL SortButtonList::FindButtonSame(ButtonVector findVector, HWND findTargetHWND, CGdipButton** returnButton)
{
	BOOL bSuccess = FALSE;
	for (int i = 0; i < (int)findVector.size(); i++)
	{
		if (findTargetHWND == findVector.at(i)->m_hWnd)
		{
			*returnButton = findVector.at(i);
			bSuccess = TRUE;
			break;
		}
	}
	return bSuccess;
}

BOOL SortButtonList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다
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
