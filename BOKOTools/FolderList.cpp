﻿// FolderList.cpp: 구현 파일
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
	bThread = false;
	bPressMaintain = false;
	undoFolder = nullptr;
	downFolder = nullptr;
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

	Init(this, notepad->GetParent(), BIND_REGULAR, MODE_BUTTONVIEW);

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
			TRACE(_T("스레드 동작함\n"));
			bPressMaintain = false;
			if (downFolder)
			{
				downFolder->folderButton->ToggleClickChange();	//이부분이상함
			}
			return TRUE;
		}
		else // press 1초이상 동작 이벤트 비활성화
		{
			bThread = false;
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
		for (int i = 0; i < notePadManager->m_allFolderList.Size(); i++)
		{
			FolderItem0* folder = notePadManager->m_allFolderList.At(i);
			CGdipButton* folderButton = folder->folderButton;
			if (pMsg->hwnd == folderButton->m_hWnd)
			{
				downFolder = folder;
				PostMessage(PRESS_MAINTAIN, 0, 0);
				break;
			}
		}
	}
	else  if (pMsg->message == WM_LBUTTONDBLCLK)
	{
		for (int i = 0; i < notePadManager->m_allFolderList.Size(); i++)
		{
			if (pMsg->hwnd == notePadManager->m_allFolderList.At(i)->folderButton->m_hWnd)
			{
				UpdateFolder(notePadManager->m_allFolderList.At(i));
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
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
			// 아이콘 들어올리기 함수 실행
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


void FolderList::LoadFolder(ViewFolderList allFolderList)
{
	nButtonCount = 0;
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.csf = CustomScroll::CUSTOM_SCROLL_FLAGS_HORIZON;
	csi.nAllPageSize = 0;
	csi.nOnePageSize = 74;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	ViewFolder(allFolderList);

	for (int i = 0; i < nButtonCount; i++)
	{
		scroll.LineEnd();
	}

	scroll.ExecuteScrollPos(currentTheme);
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
	if (scroll.GetCurrentLinePos() == 1)
	{
		nReturnSequence = nLocToPos;
	}
	else
	{
		nReturnSequence = nLocToPos + (scroll.GetCurrentLinePos() - 1);
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

BOOL FolderList::DragEventUp(HWND upHWND, CPoint upPoint)
{
	BOOL bReturn = FALSE;

	return bReturn;
}

BOOL FolderList::DragEventDown(HWND downHWND, CPoint downPoint)
{
	BOOL bReturn = FALSE;

	return bReturn;
}

BOOL FolderList::DragEventMove(HWND moveHWND, CPoint movePoint)
{
	BOOL bReturn = FALSE;

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
		if (nFlag == SB_PAGEUP && scroll.GetCurrentLinePos() == 1) {}
		else if (nFlag == SB_PAGEDOWN && scroll.GetCurrentLinePos() == scroll.GetLineCount()) {}
		else { OnHScroll(nFlag, 0, GetScrollBarCtrl(SB_HORZ)); }
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


afx_msg LRESULT FolderList::OnPressMaintain(WPARAM wParam, LPARAM lParam)
{
	AfxBeginThread(thrPressMaintainButton, this);

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

		NotePadManager::FolderSaveData saveFolder;
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
