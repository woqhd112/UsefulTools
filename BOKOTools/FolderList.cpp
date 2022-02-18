// FolderList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "NotePadList.h"
#include "FolderList.h"
#include "NotePad.h"
#include "afxdialogex.h"


// FolderList 대화 상자

IMPLEMENT_DYNAMIC(FolderList, CDialogEx)

FolderList::FolderList(NotePadManager* notePadManager, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FOLDER_LIST, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	this->notePadManager = notePadManager;

	nButtonCount = 0;
	nLineEndCount = 0;
	nEventPos = 0;
	nEventFolderSequence = 0;
	bThread = false;
	bPressMaintain = false;
	bThreadDownEvent = false;
	undoFolder = nullptr;
	downFolder = nullptr;
	dragSectorPos = DRAG_SECTOR_FOLDER;
}

FolderList::~FolderList()
{
	//folderlist.clear();
}

void FolderList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FolderList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(PRESS_MAINTAIN, &FolderList::OnPressMaintain)
	ON_MESSAGE(FOLDER_VIEW, &FolderList::OnFolderView)
END_MESSAGE_MAP()


// FolderList 메시지 처리기


BOOL FolderList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());
	
	notepad = (NotePad*)pParent;

	Init(this, notepad, BIND_REGULAR, MODE_BUTTONVIEW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void FolderList::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
}


BOOL FolderList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONUP)
	{
		// press 1초이상 동작 이벤트 활성화
		if (bPressMaintain)
		{
			bPressMaintain = false;
			if (bThread)
			{
				bThread = false;
				DWORD nExitCode = NULL;

				GetExitCodeThread(thrMaintain->m_hThread, &nExitCode);
				if (TerminateThread(thrMaintain->m_hThread, nExitCode) != 0)
				{
					delete thrMaintain;
					thrMaintain = nullptr;
				}
			}
			FolderItem0* findfolder = FindFolderButton(pMsg->hwnd);
			if (downFolder)
			{
				if (DragEventUp(pMsg->hwnd, pMsg->pt, downFolder))
					return TRUE;
				else
				{
					//CloseDragEvent();
				}
			}
			return TRUE;
		}
		else // press 1초이상 동작 이벤트 비활성화
		{

			if (bThread)
			{
				bThread = false;
				DWORD nExitCode = NULL;
				GetExitCodeThread(thrMaintain->m_hThread, &nExitCode);
				if (TerminateThread(thrMaintain->m_hThread, nExitCode) != 0)
				{
					delete thrMaintain;
					thrMaintain = nullptr;
				}
			}

			if (downFolder)
			{
				if (pMsg->hwnd == downFolder->folderButton->m_hWnd)
				{
					PostMessage(FOLDER_VIEW, 0, 0);
				}
				else
				{
					return TRUE;
				}
			}
			else
			{
				return TRUE;
			}
		}
	}
	else if (pMsg->message == WM_LBUTTONDOWN)
	{
		FolderItem0* findfolder = FindFolderButton(pMsg->hwnd);
		if (findfolder != nullptr)
		{
			downFolder = findfolder;
			dragPoint = pMsg->pt;
			PostMessage(PRESS_MAINTAIN, 0, 0);
		}
		return TRUE;
	}
	else if (pMsg->message == WM_MOUSEMOVE)
	{
		dragPoint = pMsg->pt;

		FolderItem0* findfolder = FindFolderButton(pMsg->hwnd);

		if (findfolder != nullptr)
		{
			if (bThreadDownEvent)
			{
				SetDownEvent(pMsg->hwnd, pMsg->pt, downFolder);
				bThreadDownEvent = false;
			}
		}
		if (DragEventMove(pMsg->hwnd, pMsg->pt, findfolder))
			return TRUE;
		else
		{
			/*if (IsState() == 0)
			{
				CloseDragEvent();
			}*/
		}
	}
	else  if (pMsg->message == WM_LBUTTONDBLCLK)
	{
		FolderItem0* findfolder = FindFolderButton(pMsg->hwnd);
		if (findfolder != nullptr)
		{
			UpdateFolder(findfolder);
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

FolderItem0* FolderList::FindFolderButton(HWND clickWND)
{
	for (int i = 0; i < notePadManager->m_allFolderList.Size(); i++)
	{
		FolderItem0* findFolder = notePadManager->m_allFolderList.At(i);
		if (findFolder->folderButton->m_hWnd == clickWND)
		{
			return findFolder;
		}
	}

	return nullptr;
}

UINT FolderList::thrPressMaintainButton(LPVOID method)
{
	FolderList* thisMethod = (FolderList*)method;

	thisMethod->StartPressMaintainButton();

	return 0;
}

void FolderList::StartPressMaintainButton()
{
	int nPressCount = 0;
	bThread = true;
	while (bThread)
	{
		nPressCount += 100;
		Sleep(100);
		if (nPressCount >= 1000)
		{
			bPressMaintain = true;
			bThread = false;
			
			DragEventDown(nullptr, dragPoint, downFolder);
		}
	}
}

HBRUSH FolderList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(currentTheme->GetFunctionTextColor());
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void FolderList::LoadFolder(ViewFolderList allFolderList, bool bUseScrollEvent)
{
	nButtonCount = 0;
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.csf = CustomScroll::CUSTOM_SCROLL_FLAGS_HORIZON;
	csi.cse = CustomScroll::CUSTOM_SCROLL_EVENT_INCREASE_COUNT_LINE;
	csi.nAllPageSize = 0;
	csi.nOnePageSize = 74;
	csi.nScrollPos = 0;
	csi.nCseMaxCount = 3;
	scroll.Initialize(csi);

	viewFolderlist = allFolderList;
	ViewFolder(allFolderList);

	for (int i = 0; i < nButtonCount; i++)
	{
		scroll.LineEnd();
	}

	scroll.ExecuteScrollPos(currentTheme);

	if (bUseScrollEvent)
	{
		for (int i = 0; i < scroll.GetLineCount(); i++)
		{
			OnHScroll(SB_PAGEDOWN, 0, GetScrollBarCtrl(SB_HORZ));
		}
	}
}

void FolderList::ViewFolder(ViewFolderList folderlist)
{
	for (int i = 1; i < folderlist.Size(); i++)
	{
		FolderItem0* targetFolder = folderlist.At(i);
		CRect folderRect;
		folderRect = SetButtonPosition(nButtonCount - ((scroll.GetCurrentLinePos() - 1) * 5));
		targetFolder->ShowWindow(true);
		targetFolder->MoveWindow(folderRect.left, folderRect.top);
		nButtonCount++;
		if (nButtonCount > 1)
		{
			if ((nButtonCount - 1) % 4 == 0)
				nLineEndCount++;
		}
	}
}

int FolderList::ButtonLocationToPos(POINT pt)
{
	int nResult = -1;

	int nStartPos_x = 20;
	int nStartPos_y = 20;
	int nPictureSize = 64;

	int nPictureToPictureMargin_x = 10;

	int nPosX = pt.x;
	int nPosY = pt.y;

	for (int i = 0; i < 4; i++)
	{
		if (nPosX >= nStartPos_x + (nPictureSize + nPictureToPictureMargin_x) * i && nPosX <= nStartPos_x + nPictureSize + (nPictureSize + nPictureToPictureMargin_x) * i)
		{
			nResult = i;
			break;
		}
	}

	return nResult;
}

int FolderList::LocationAndScrollToFolderSequence(int nLocToPos)
{
	int nReturnSequence = -1;
	if (nLocToPos == -1) return nReturnSequence;

	// 첫스크롤일때
	if (scroll.GetCseLineCount() == 1)
	{
		nReturnSequence = nLocToPos;
	}
	else
	{
		nReturnSequence = nLocToPos + (scroll.GetCseLineCount() - 1);
	}

	return nReturnSequence;
}

CRect FolderList::SetButtonPosition(int nItemCount)
{
	int nStartPos_x = 20;
	int nStartPos_y = 20;
	int nPictureSize = 64;

	int nPictureToPictureMargin_x = 10;
	//int nPictureToPictureMargin_x = 30;
	CRect ButtonPos;

	nStartPos_x += ((nPictureSize + nPictureToPictureMargin_x) * (nItemCount));

	//nStartPos_x += ((nPictureSize + nPictureToPictureMargin_x) * (nItemCount % 4));

	ButtonPos = { nStartPos_x, nStartPos_y, nStartPos_x + nPictureSize, nStartPos_y + nPictureSize };
	return ButtonPos;
}

void FolderList::SetDownEvent(HWND downHWND, CPoint downPoint, FolderItem0* findfolder)
{
	POINT convertPoint = downPoint;
	ScreenToClient(&convertPoint);
	nEventPos = ButtonLocationToPos(convertPoint);
	nEventFolderSequence = LocationAndScrollToFolderSequence(nEventPos);
	ExecuteDragEvent(findfolder->folderButton, findfolder->folderStatic);	
	SetSizeDragDlg(CRect(downPoint.x + 2, downPoint.y + 2, downPoint.x + 2 + 64, downPoint.y + 2 + 64));
	findfolder->ShowWindow(false);
	bThreadDownEvent = false;
}

BOOL FolderList::DragEventUp(HWND upHWND, CPoint upPoint, FolderItem0* findfolder)
{
	BOOL bReturn = FALSE;
	if (ExistDragDlg())
	{
		POINT convertPoint = upPoint;
		ScreenToClient(&convertPoint);

		// 현재 마우스 포인트가 노트리스트 영역에 있을 경우
		if (dragSectorPos == DRAG_SECTOR_NOTE)
		{

		}
		// 현재 마우스 포인트가 폴더리스트 영역에 있을 경우
		else if (dragSectorPos == DRAG_SECTOR_FOLDER)
		{
			// 폴더 위치 변경

		}
		// 현재 마우스 포인트가 부모창 영역에 있을 경우
		else if (dragSectorPos == DRAG_SECTOR_PARENT)
		{
			POINT parentPoint = upPoint;
			notepad->ScreenToClient(&parentPoint);
			if (PtInRect(notepad->trashButtonRect, parentPoint) || PtInRect(notepad->recycleRect, upPoint))
			{
				if (notePadManager->RecycleFolder(findfolder, nEventFolderSequence + 1) == false)	// +1은 seq 0은 항상 other이 들어가있기 때문
				{
					LoadFolder(notePadManager->m_allFolderList, true);
					return FALSE;
				}
				
				// viewfolder 전역변수 추가할거면 여기에 업데이트함수 생성해서 호출해야함

				Invalidate();
				// 쓰레기통이 켜져있으면 쓰레기통 화면도 갱신한다.
				notepad->InvalidateRecycle();
			}
		}

		DeleteDragDlg();
		bReturn = TRUE;
		CloseDragEvent();
	}

	return bReturn;
}

BOOL FolderList::DragEventDown(HWND downHWND, CPoint downPoint, FolderItem0* findfolder)
{
	BOOL bReturn = FALSE;
	bThreadDownEvent = true;
	
	bReturn = TRUE;

	return bReturn;
}

BOOL FolderList::DragEventMove(HWND moveHWND, CPoint movePoint, FolderItem0* findfolder)
{
	BOOL bReturn = FALSE;
	if (IsDragging(notepad->dragRect, movePoint))
	{
		POINT convertPoint = movePoint;
		ScreenToClient(&convertPoint);

		CRect folderSortRect;
		this->GetClientRect(folderSortRect);

		if (PtInRect(folderSortRect, convertPoint))
		{
			dragSectorPos = DRAG_SECTOR_FOLDER;

			int nFolderLocToPos = ButtonLocationToPos(convertPoint);
			int nLocAndScrollToFolderSequence = LocationAndScrollToFolderSequence(nFolderLocToPos);
			TRACE(L"eventpos : %d\n", nEventPos);
			TRACE(L"locpos : %d\n", nFolderLocToPos);
			TRACE(L"eventseq : %d\n", nEventFolderSequence);
			TRACE(L"locseq : %d\n", nLocAndScrollToFolderSequence);
			CRect folderSortRect = SetButtonPosition(nFolderLocToPos);

			if (nLocAndScrollToFolderSequence == -1) return FALSE;
			if (viewFolderlist.Empty()) return FALSE;
			if (nLocAndScrollToFolderSequence > (viewFolderlist.Size() - 1) || nEventFolderSequence > (viewFolderlist.Size() - 1)) return FALSE;
			if (nLocAndScrollToFolderSequence == nEventFolderSequence) return FALSE;

			if (PtInRect(folderSortRect, convertPoint))
			{
				FolderItem0* targetFolder = viewFolderlist.At(nLocAndScrollToFolderSequence);	// 드래그해서 갖다댄 폴더

				nEventFolderSequence = nLocAndScrollToFolderSequence;
				nEventPos = nFolderLocToPos;
				TRACE(L"폴더 접근\n");
			}
			// notepadlist 처럼 view 컨테이너 하나 생성해서 처리해야함
		}
		else
		{
			CRect noteInsertRect;
			notepad->notepadlist->GetWindowRect(noteInsertRect);
			ScreenToClient(noteInsertRect);

			// 마우스가 노트리스트에 접근했을 때
			if (PtInRect(noteInsertRect, convertPoint))
			{
				dragSectorPos = DRAG_SECTOR_NOTE;

			}
			// 마우스가 부모창에 접근했을 때
			else
			{
				dragSectorPos = DRAG_SECTOR_PARENT;

				POINT parentPoint = movePoint;
				POINT recyclePoint = movePoint;
				notepad->ScreenToClient(&parentPoint);
				notepad->notepadrecycle->ScreenToClient(&recyclePoint);

				// 마우스가 쓰레기통버튼에 접근했을때 호버이벤트 발생
				if (PtInRect(notepad->trashButtonRect, parentPoint))
				{
					notepad->m_btn_trash.UseHoverEvent();
				}
				else
				{
					notepad->m_btn_trash.UseLeaveEvent();
				}
			}
		}

		bReturn = TRUE;
	}

	return bReturn;
}


void FolderList::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	Invalidate();
	for (int i = 0; i < notePadManager->m_allFolderList.Size(); i++)
	{
		FolderItem0* folder = notePadManager->m_allFolderList.At(i);
		folder->folderButton->DisConnect();
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL FolderList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (scroll.GetLineCount() > 1)
	{
		UINT nFlag = scroll.OperateWheel(zDelta);
		if (nFlag == SB_PAGEUP && scroll.GetCurrentLinePos() <= 0) { scroll.SetDefaultLinePos(); }
		else if (nFlag == SB_PAGEDOWN && scroll.GetCurrentLinePos() == scroll.GetCseMaxLineCount()) {}
		else { OnHScroll(nFlag, 0, GetScrollBarCtrl(SB_HORZ)); }
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


afx_msg LRESULT FolderList::OnPressMaintain(WPARAM wParam, LPARAM lParam)
{
	thrMaintain = AfxBeginThread(thrPressMaintainButton, this);

	return 0;
}


afx_msg LRESULT FolderList::OnFolderView(WPARAM wParam, LPARAM lParam)
{
	// 폴더 클릭 시 notepadlist 초기화하고 해당 메모로만 출력

	if (undoFolder != downFolder)
	{
		if (undoFolder)
			undoFolder->folderButton->ToggleClickChange();
		std::vector<ViewNoteList> allFolder;
		allFolder.push_back(downFolder->GetFolder());
		notePadManager->SetNoteView(allFolder, NotePadManager::NOTE_VIEW_FOLDER);
		notepad->notepadlist->LoadNotePad(notePadManager->m_viewNoteList);
		undoFolder = downFolder;
	}
	else
	{
		downFolder = nullptr;
		undoFolder = nullptr;
		notepad->LoadAllNote();
	}

	return 0;
}

void FolderList::UpdateFolder(FolderItem0* folderItem)
{
	COLORREF updateColor = notePadManager->GetTagColorFromIndex(folderItem->GetFolderColorIndex());
	CString strUpdateFolderName = folderItem->GetFolderName();
	FolderDlg createFolder(FOLDER_UPDATE, currentTheme, &updateColor, &strUpdateFolderName, this);

	if (createFolder.DoModal() == IDOK)
	{
		FolderItem0::FolderInit updateFolder;
		updateFolder.nFolderSequence = folderItem->GetFolderSequence();
		updateFolder.nFolderSize = (int)folderItem->GetFolderSize();
		updateFolder.strFolderName = strUpdateFolderName;
		updateFolder.nFolderColorIndex = notePadManager->GetIndexFromTagColor(updateColor);
		updateFolder.folder = folderItem->GetFolder();
		updateFolder.createTime = folderItem->GetCreateTime();
		updateFolder.updateTime = CTime::GetCurrentTime();
		folderItem->Update(updateFolder);

		ViewNoteList notelist = folderItem->GetFolder();
		for (int i = 0; i < notelist.Size(); i++)
		{
			NoteItem* noteItem = notelist.At(i);
			NoteItem::NoteInit updateNote;
			updateNote.isLock = noteItem->IsLock();
			updateNote.nFolderSequence = updateFolder.nFolderSequence;
			updateNote.nFolderSize = updateFolder.nFolderSize;
			updateNote.nNoteName = noteItem->GetNoteName();
			updateNote.strNoteContent = noteItem->GetNoteContent();
			updateNote.tagColor = updateColor;
			noteItem->Update(updateNote);
		}

		NotePadXMLManager::FolderSaveData saveFolder;
		saveFolder.folderTagColor = updateColor;
		saveFolder.nFolderSequence = updateFolder.nFolderSequence;
		saveFolder.nSize = updateFolder.nFolderSize;
		saveFolder.strFolderName = strUpdateFolderName;
		saveFolder.strCreateTime = notePadManager->GetTimeCal(updateFolder.createTime);
		saveFolder.strUpdateTime = notePadManager->GetTimeCal(updateFolder.updateTime);

		notePadManager->SaveFolderXml(saveFolder);
		notepad->InvalidateSame();
	}
}
