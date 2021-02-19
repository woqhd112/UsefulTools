﻿// NotePadList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "NotePadList.h"
#include "NotePad.h"
#include "NoteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// NotePadList 대화 상자

IMPLEMENT_DYNAMIC(NotePadList, CDialogEx)

NotePadList::NotePadList(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NOTEPAD_LIST, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	nButtonID = 70000;
	nStaticID = 75000;
	nLockID = 80000;
	nButtonCount = 0;
	nLineEndCount = 0;
	nLineCount = 0;
	nEventPos = 0;
	noteClickState = NOTE_CLICK_STATE_NONE;
	notePosState = NOTE_POS_STATE_NONE;
	dragSectorPos = DRAG_SECTOR_NOTE;
	postMousePoint = { 0, 0 };
	nSelectFolderSequence = 0;
	bMousePointFolderAccess = false;
}

NotePadList::~NotePadList()
{
	viewNoteList.clear();
}

void NotePadList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NotePadList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// NotePadList 메시지 처리기


BOOL NotePadList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());
	notepad = (NotePad*)pParent;

	Init(this, notepad->GetParent(), BIND_REGULAR, MODE_MOUSEPOINT);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void NotePadList::LoadNotePad(std::vector<ViewNoteList> allFolderList)
{
	for (int i = 0; i < (int)this->viewNoteList.size(); i++)
	{
		ViewNoteList notelist = this->viewNoteList.at(i);
		if (notelist.size() > 0)
		{
			for (int j = 0; j < (int)notelist.size(); j++)
			{
				notelist.at(j)->ShowWindow(false);
			}
		}
	}

	nButtonCount = 0;
	nLineEndCount = 0;
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.csf = CustomScroll::CUSTOM_SCROLL_FLAGS_VERTICAL;
	csi.nAllPageSize = 0;
	csi.nOnePageSize = 252;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	for (int i = 0; i < (int)allFolderList.size(); i++)
	{
		ViewNote(allFolderList.at(i));
	}
	viewNoteList = allFolderList;
	baseViewNoteList = allFolderList;
	
	for (int i = 0; i <= nLineEndCount; i++)
	{
		scroll.LineEnd();
	}

	scroll.ExecuteScrollPos(currentTheme);
	Invalidate();
}

CRect NotePadList::SetButtonPosition(int nItemCount)
{
	int nStartPos_x = 25;
	int nStartPos_y = 2;
	int nPictureSize_x = 365;
	int nPictureSize_y = 40;

	int nPictureToPictureMargin_y = 2;
	//int nPictureToPictureMargin_x = 30;
	CRect ButtonPos;

	nStartPos_y += ((nPictureSize_y + nPictureToPictureMargin_y) * (nItemCount));

	//nStartPos_x += ((nPictureSize + nPictureToPictureMargin_x) * (nItemCount % 4));

	ButtonPos = { nStartPos_x, nStartPos_y, nStartPos_x + nPictureSize_x, nStartPos_y + nPictureSize_y };
	return ButtonPos;
}

void NotePadList::UpdateNotePad(NoteItem* updateNote, CString strContent, bool isLock)
{
	NoteItem::NoteInit init;
	init.nNoteName = updateNote->GetNoteName();
	init.nFolderSequence = updateNote->GetFolderSequence();
	init.strNoteContent = strContent;
	init.tagColor = updateNote->GetTagColor();
	init.isLock = isLock;
	init.nFolderSize = updateNote->GetFolderSize();
	updateNote->Update(init);

	// Note 폴더에 파일추가
	CString strTextPath = _T("");
	CString strNoteName, strFolderSequence;
	strNoteName.Format(_T("%d"), init.nNoteName);
	strFolderSequence.Format(_T("%d"), init.nFolderSequence);
	CustomXml::GetModulePath(strTextPath);
	strTextPath += (_T("\\Note\\") + strFolderSequence + strNoteName + _T(".txt"));

	NoteFile file;
	if (file.NoteWrite(strTextPath, strContent))
	{
		NotePad::NoteSaveData saveNote;
		saveNote.nFolderSequence = init.nFolderSequence;
		saveNote.nLock = init.isLock;
		saveNote.nNoteName = init.nNoteName;

		notepad->SaveNoteXml(saveNote);
		LoadNotePad(viewNoteList);
	}
}

void NotePadList::AddNotePad(CString strContent, bool isLock)
{
	int nNoteName = (int)notepad->otherNoteList.size() + 1;
	NoteItem* newNote = new NoteItem(currentTheme, this);
	NoteItem::NoteInit noteinit;
	noteinit.nNoteName = nNoteName;
	noteinit.nFolderSequence = 0;
	noteinit.strNoteContent = strContent;
	noteinit.tagColor = TAG_COLOR_5;
	noteinit.isLock = isLock;
	noteinit.nFolderSize = nNoteName;

	newNote->Initialize(noteinit);
	notepad->otherNoteList.push_back(newNote);
	notepad->allNoteList.at(0) = notepad->otherNoteList;

	// Note 폴더에 파일추가
	CString strTextPath = _T("");
	CString strNoteName;
	strNoteName.Format(_T("%d"), nNoteName);
	CustomXml::GetModulePath(strTextPath);
	strTextPath += (_T("\\Note\\0") + strNoteName + _T(".txt"));

	NoteFile file;
	if (file.NoteWrite(strTextPath, strContent))
	{
		NotePad::NoteSaveData saveNote;
		saveNote.nFolderSequence = 0;
		saveNote.nLock = 0;
		saveNote.nNoteName = nNoteName;

		NotePad::FolderSaveData saveFolder;
		saveFolder.folderTagColor = TAG_COLOR_5;
		saveFolder.nFolderSequence = 0;
		saveFolder.nSize = nNoteName;
		saveFolder.strFolderName = _T("other");

		notepad->CreateNoteXml(saveNote);
		notepad->SaveFolderXml(saveFolder);
		LoadNotePad({ notepad->otherNoteList });
	}
}

void NotePadList::ViewNote(ViewNoteList notelist)
{
	for (int i = 0; i < (int)notelist.size(); i++)
	{
		NoteItem* targetNote = notelist.at(i);
		CRect noteRect;
		noteRect = SetButtonPosition(nButtonCount - ((scroll.GetCurrentLinePos() - 1) * 6));
		targetNote->ShowWindow(true);
		targetNote->ShowLock(targetNote->IsLock() ? true : false);
		targetNote->MoveWindow(noteRect.left, noteRect.top);
		CString strTagCount;
		strTagCount.Format(_T("%d"), nButtonCount + 1);
		targetNote->SetNoteTagSequence(strTagCount);
		nButtonCount++;
		if (nButtonCount > 1)
		{
			if ((nButtonCount - 1) % 6 == 0)
				nLineEndCount++;
		}
	}
}


int NotePadList::ButtonLocationToPos(POINT pt)
{
	int nResult = -1;

	int nStartPos_x = 25;
	int nStartPos_y = 2;
	int nPictureSize_x = 365;
	int nPictureSize_y = 40;

	int nPictureToPictureMargin_y = 2;

	int nPosX = pt.x;
	int nPosY = pt.y;

	for (int i = 0; i < 6; i++)
	{
		if (nPosY >= nStartPos_y + (nPictureSize_y + nPictureToPictureMargin_y) * i && nPosY <= nStartPos_y + nPictureSize_y + (nPictureSize_y + nPictureToPictureMargin_y) * i)
		{
			nResult = i;
			break;
		}
	}

	return nResult;
}

BOOL NotePadList::DragEventUp(HWND upHWND, CPoint upPoint, NoteItem* findnote)
{
	BOOL bReturn = FALSE;
	if (ExistDragDlg())
	{
		// 현재 마우스 포인트가 노트리스트 영역에 있을 경우
		if (dragSectorPos == DRAG_SECTOR_NOTE)
		{
			findnote->ShowWindow(true);
			findnote->ShowLock(findnote->IsLock());
			POINT convertPoint = upPoint;
			ScreenToClient(&convertPoint);

			int nLocToPos = ButtonLocationToPos(convertPoint);
			CRect rect = SetButtonPosition(nLocToPos);
			
			// 현재 마우스 포인트가 해당 노트에 있을경우
			if (PtInRect(rect, convertPoint))
			{
				// 스왑한 노트정보를 현재 상속된 폴더에 업데이트한다.
				notepad->folderlist->UpdateFolderVector(saveNoteList, nFindSaveFolderSequence);

				// 스왑한 노트정보를 notepad에 있는 전체폴더에 업데이트한다.
				notepad->UpdateAllNoteVector(saveNoteList, nFindSaveFolderSequence);

				// 업데이트한 노트정보를 메모장에 업데이트한다.
				for (int i = nLocToPos; i < (int)saveNoteList.size(); i++)
				{

					// 이부분 작업중.. lock부분이 조금이상함
					NoteItem* saveNote = saveNoteList.at(i);
					NotePad::NoteSaveData updateNote;
					updateNote.nFolderSequence = saveNote->GetFolderSequence();
					updateNote.nLock = saveNote->IsLock();
					updateNote.nNoteName = saveNote->GetNoteName();

					notepad->SaveNoteXml(updateNote);
				}


				nFindSaveFolderSequence = 0;
				saveNoteList.clear();
				baseViewNoteList = viewNoteList;
			}
			// 현재 마우스 포인트가 노트 밖에 있을 경우 다시 초기로 갱신
			else
			{
				LoadNotePad(baseViewNoteList);
			}
		}
		// 현재 마우스 포인트가 폴더리스트 영역에 있을 경우
		else if (dragSectorPos == DRAG_SECTOR_FOLDER)
		{
			// 폴더 시퀀스가 현재폴더가 아닐때만 적용
			if (nSelectFolderSequence != nFindSaveFolderSequence)
			{
				ViewNoteList updateNoteList;
				if ((int)viewNoteList.size() > 1)
					updateNoteList = viewNoteList.at(nFindSaveFolderSequence);
				else
					updateNoteList = viewNoteList.at(0);

				// 현재 노트를 현재 폴더에서 지운다
				for (int i = 0; i < (int)updateNoteList.size(); i++)
				{
					NoteItem* updateNote = updateNoteList.at(i);
					updateNote->SetFolderSize(updateNote->GetFolderSize() - 1);
					if (updateNote == findnote)
					{
						updateNoteList.erase(updateNoteList.begin() + i);
					}
				}

				UpdateNoteVector(updateNoteList, nFindSaveFolderSequence);

				// 현재 폴더 갱신
				FolderItem0* updateFolder = notepad->folderlist->folderlist.at(nFindSaveFolderSequence);
				updateFolder->SetFolderSize(updateFolder->GetFolderSize() - 1);
				updateFolder->SetFolder(updateNoteList);
				notepad->UpdateAllNoteVector(updateNoteList, nFindSaveFolderSequence);
				notepad->folderlist->UpdateAllFolderVector(updateFolder, nFindSaveFolderSequence);

				// 현재 노트를 선택한 폴더에 추가한다
				ViewNoteList insertNoteList = notepad->allNoteList.at(nSelectFolderSequence);
				FolderItem0* insertFolder = notepad->allFolderList.at(nSelectFolderSequence);

				NoteItem::NoteInit updateinit;
				updateinit.isLock = findnote->IsLock();
				updateinit.nFolderSequence = nSelectFolderSequence;
				updateinit.nFolderSize = (int)insertNoteList.size() + 1;
				updateinit.nNoteName = findnote->GetNoteName();
				updateinit.strNoteContent = findnote->GetNoteContent();
				updateinit.tagColor = notepad->GetTagColorFromIndex(insertFolder->GetFolderColorIndex());
				findnote->Update(updateinit);

				// 선택 폴더 갱신
				insertNoteList.push_back(findnote);
				insertFolder->SetFolderSize(insertFolder->GetFolderSize() + 1);
				insertFolder->SetFolder(insertNoteList);
				notepad->UpdateAllNoteVector(insertNoteList, nSelectFolderSequence);
				notepad->UpdateAllFolderVector(insertFolder, nSelectFolderSequence);
				notepad->folderlist->UpdateAllFolderVector(insertFolder, nSelectFolderSequence);

				// 업데이트한 노트정보를 xml에 저장한다.

				// 업데이트한 노트이름으로 메모장이름을 변경한다.

				nFindSaveFolderSequence = 0;
				saveNoteList.clear();
				baseViewNoteList = viewNoteList;

				int curScrollPos = scroll.GetCurrentLinePos();

				// 현재 폴더 화면 갱신
				LoadNotePad(baseViewNoteList);
				for (int i = 1; i < curScrollPos; i++)
				{
					OnVScroll(SB_PAGEDOWN, 0, GetScrollBarCtrl(SB_VERT));
				}
			}
		}
		// 현재 마우스 포인트가 부모창 영역에 있을 경우
		else if (dragSectorPos == DRAG_SECTOR_PARENT)
		{
			LoadNotePad(baseViewNoteList);	// 일단 임시로 해둠 쓰레기통, 기타폴더도 구분해야함
		}
	}
	
	
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return bReturn;
}

BOOL NotePadList::DragEventDown(HWND downHWND, CPoint downPoint, NoteItem* findnote)
{
	BOOL bReturn = FALSE;
	ExecuteDragEvent(findnote);

	POINT convertPoint = downPoint;
	ScreenToClient(&convertPoint);

	nEventPos = ButtonLocationToPos(convertPoint);

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	findnote->ShowWindow(false);
	nFindSaveFolderSequence = findnote->GetFolderSequence();
	
	return bReturn;
}

BOOL NotePadList::DetectionPtInRect(const RECT* targetRECT, const RECT* thisRECT, POINT pt)
{
	int nRECTPosError = abs(int(targetRECT->top - thisRECT->top));
	
	if (nRECTPosError > 20)
	{

		if (targetRECT->bottom >= pt.y && targetRECT->top <= pt.y &&
			targetRECT->left <= pt.x && targetRECT->right >= pt.x)
		{
			
			notePosState = NOTE_POS_STATE_HALF_DETECT;
			postMousePoint = pt;
			return TRUE;
		}
		else
		{
			notePosState = NOTE_POS_STATE_NONE;
		}
	}

	return FALSE;
}

BOOL NotePadList::DragEventMove(HWND moveHWND, CPoint movePoint, NoteItem* findnote)
{
	BOOL bReturn = FALSE;
	
	if (IsDragging(CRect(0, 0, 0, 0), movePoint))
	{
		POINT convertPoint = movePoint;
		ScreenToClient(&convertPoint);

		int nNoteLocToPos = ButtonLocationToPos(convertPoint);
		

		CRect findRect = SetButtonPosition(nNoteLocToPos);
		CRect eventRect = SetButtonPosition(nEventPos);
		/*TRACE(L"pt x : %ld\n", convertPoint.x);
		TRACE(L"pt y : %ld\n", convertPoint.y);
		TRACE(L"loc : %d\n", nLocToPos);
		TRACE(L"rect left : %ld\n", findRect.left);
		TRACE(L"rect top : %ld\n", findRect.top);
		TRACE(L"rect width : %d\n", findRect.Width());
		TRACE(L"rect height : %d\n", findRect.Height());*/

		int nJump = nEventPos - nNoteLocToPos;
		int absJump = abs(nJump);

		CRect noteSortRect;
		this->GetClientRect(noteSortRect);
		
		if (PtInRect(noteSortRect, convertPoint))
		{
			dragSectorPos = DRAG_SECTOR_NOTE;
			if (nNoteLocToPos == -1) return FALSE;
			if (DetectionPtInRect(findRect, eventRect, convertPoint))
			{
				if (notePosState == NOTE_POS_STATE_HALF_DETECT)
				{
					// 사이즈가 1보다 클경우는 전체 폴더리스트
					if ((int)viewNoteList.size() > 1)
						saveNoteList = viewNoteList.at(nFindSaveFolderSequence);
					else
						saveNoteList = viewNoteList.at(0);

					if (nNoteLocToPos > ((int)saveNoteList.size() - 1) || nEventPos > ((int)saveNoteList.size() - 1)) return FALSE;

					// 찾은노트아이템이 들어올린 노트보다 위에 있을 경우
					int nSortName = 0;
					CString strSortNoteTagSequence;
					if (absJump >= 1 && nJump > 0)
					{
						for (int i = nEventPos; i > nNoteLocToPos; i--)
						{
							NoteItem* sortNoteItem = saveNoteList.at(i - 1);
							CRect sortRect = SetButtonPosition(i);
							sortNoteItem->MoveWindow(sortRect.left, sortRect.top);

							nSortName = sortNoteItem->GetNoteName();
							sortNoteItem->SetNoteName(nSortName + 1);

							strSortNoteTagSequence = sortNoteItem->GetNoteTagSequence();
							int nNoteTagSequence = _ttoi(strSortNoteTagSequence);
							CString strFormat;
							strFormat.Format(_T("%d"), nNoteTagSequence + 1);
							sortNoteItem->SetNoteTagSequence(strFormat);

						}
						findnote->MoveWindow(findRect.left, findRect.top);
						findnote->SetNoteName(nSortName);
						findnote->SetNoteTagSequence(strSortNoteTagSequence);

						for (int i = nEventPos; i > nNoteLocToPos; i--)
						{
							if (i - 1 < 0) return FALSE;
							std::iter_swap(saveNoteList.begin() + i, saveNoteList.begin() + i - 1);
						}

						UpdateNoteVector(saveNoteList, nFindSaveFolderSequence);

						nEventPos = nNoteLocToPos;
					}
					else if (absJump >= 1 && nJump < 0)
					{
						for (int i = nEventPos; i < nNoteLocToPos; i++)
						{
							NoteItem* sortNoteItem = saveNoteList.at(i + 1);
							CRect sortRect = SetButtonPosition(i);
							sortNoteItem->MoveWindow(sortRect.left, sortRect.top);

							nSortName = sortNoteItem->GetNoteName();
							sortNoteItem->SetNoteName(nSortName - 1);

							strSortNoteTagSequence = sortNoteItem->GetNoteTagSequence();
							int nNoteTagSequence = _ttoi(strSortNoteTagSequence);
							CString strFormat;
							strFormat.Format(_T("%d"), nNoteTagSequence - 1);
							sortNoteItem->SetNoteTagSequence(strFormat);

						}
						findnote->MoveWindow(findRect.left, findRect.top);
						findnote->SetNoteName(nSortName);
						findnote->SetNoteTagSequence(strSortNoteTagSequence);

						for (int i = nEventPos; i < nNoteLocToPos; i++)
						{
							if (i + 1 >= (int)saveNoteList.size()) return FALSE;
							std::iter_swap(saveNoteList.begin() + i, saveNoteList.begin() + i + 1);
						}

						UpdateNoteVector(saveNoteList, nFindSaveFolderSequence);

						nEventPos = nNoteLocToPos;
					}
				}
			}
		}
		else
		{
			notePosState = NOTE_POS_STATE_NONE;

			CRect folderInsertRect;
			notepad->folderlist->GetWindowRect(folderInsertRect);
			ScreenToClient(folderInsertRect);
			
			// 마우스가 폴더리스트에 접근했을 때
			if (PtInRect(folderInsertRect, convertPoint))
			{
				POINT folderPoint = movePoint;
				notepad->folderlist->ScreenToClient(&folderPoint);

				dragSectorPos = DRAG_SECTOR_FOLDER;
				int nFolderLocToPos = notepad->folderlist->ButtonLocationToPos(folderPoint);
				if (nFolderLocToPos == -1) return FALSE;

				CRect findFolderRect = notepad->folderlist->SetButtonPosition(nFolderLocToPos);

				// 마우스가 폴더에 접근했을 때
				if (PtInRect(findFolderRect, folderPoint))
				{
					nSelectFolderSequence = notepad->folderlist->LocationAndScrollToFolderSequence(nFolderLocToPos) + 1;
					ViewFolderList viewFolderList = notepad->folderlist->folderlist;
					FolderItem0* findFolder = viewFolderList.at(nSelectFolderSequence);

					findFolderButton = findFolder->folderButton;
					findFolderButton->UseHoverEvent();
					bMousePointFolderAccess = true;
				}
				// 마우스가 폴더에 접근하지 않았을 때
				else
				{
					// 폴더에 접근한 적이 있을 때 leaveEvent활성화
					if (bMousePointFolderAccess)
					{
						findFolderButton->UseLeaveEvent();
						findFolderButton = nullptr;
						bMousePointFolderAccess = false;
					}
				}
			}
			// 마우스가 부모창에 접근했을 떄
			else
			{
				dragSectorPos = DRAG_SECTOR_PARENT;
			}
		}
		bReturn = TRUE;
	}

	return bReturn;
}

NoteItem* NotePadList::FindNoteButton(HWND clickWND)
{
	noteClickState = NOTE_CLICK_STATE_NONE;

	for (int i = 0; i < (int)viewNoteList.size(); i++)
	{
		ViewNoteList notelists = viewNoteList.at(i);
		for (int j = 0; j < (int)notelists.size(); j++)
		{
			if (notelists.at(j)->noteButton->m_hWnd == clickWND)
			{
				noteClickState = NOTE_CLICK_STATE_NOTE;
				return notelists.at(j);
			}
			else if (notelists.at(j)->wrapButton->m_hWnd == clickWND)
			{
				noteClickState = NOTE_CLICK_STATE_WRAP;
				return notelists.at(j);
			}
			else if (notelists.at(j)->tagButton->m_hWnd == clickWND)
			{
				noteClickState = NOTE_CLICK_STATE_TAG;
				return notelists.at(j);
			}
		}
	}
	return nullptr;
}

BOOL NotePadList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		NoteItem* findNote = FindNoteButton(pMsg->hwnd);
		if (findNote != nullptr)
		{
			if (noteClickState == NOTE_CLICK_STATE_TAG)
			{
				if (DragEventUp(pMsg->hwnd, pMsg->pt, findNote)) return TRUE;
			}
			else if (noteClickState == NOTE_CLICK_STATE_NOTE)
			{
				bool isLock = findNote->IsLock();
				CString strNoteContent = findNote->GetNoteContent();
				if (OpenNoteDlg(NOTE_UPDATE, &strNoteContent, &isLock))
				{
					UpdateNotePad(findNote, strNoteContent, isLock);
				}
				return TRUE;
			}
		}
	}
	else if (pMsg->message == WM_LBUTTONDOWN)
	{
		NoteItem* findNote = FindNoteButton(pMsg->hwnd);
		if (findNote != nullptr)
		{
			if (noteClickState == NOTE_CLICK_STATE_TAG)
			{
				if (DragEventDown(pMsg->hwnd, pMsg->pt, findNote)) return TRUE;
			}
			else if (noteClickState == NOTE_CLICK_STATE_NOTE)
			{
				TRACE(L"down note\n");
			}
		}
	}
	else if (pMsg->message == WM_MOUSEMOVE)
	{
		NoteItem* findNote = FindNoteButton(pMsg->hwnd);
		if (findNote != nullptr)
		{
			if (noteClickState == NOTE_CLICK_STATE_TAG)
			{
				if (DragEventMove(pMsg->hwnd, pMsg->pt, findNote)) return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void NotePadList::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


HBRUSH NotePadList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(currentTheme->GetFunctionTextColor());
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void NotePadList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);
	
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL NotePadList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

bool NotePadList::OpenNoteDlg(int nNoteMode, CString* strNoteContent, bool* isLock)
{
	NoteDlg createNote(nNoteMode, currentTheme, strNoteContent, isLock, notepad);
	if (createNote.DoModal() == IDOK)
	{
		return true;
	}
	return false;
}

void NotePadList::UpdateNoteVector(ViewNoteList updateNoteList, int nUpdateIndex)
{
	std::vector<ViewNoteList> newAllocNoteList;
	if ((int)viewNoteList.size() == 1)
	{
		newAllocNoteList.push_back(updateNoteList);
	}
	else
	{
		for (int i = 0; i < nUpdateIndex; i++)
		{
			newAllocNoteList.push_back(viewNoteList.at(i));
		}
		newAllocNoteList.push_back(updateNoteList);
		for (int i = (int)newAllocNoteList.size(); i < (int)viewNoteList.size(); i++)
		{
			newAllocNoteList.push_back(viewNoteList.at(i));
		}
	}
	viewNoteList.assign(newAllocNoteList.begin(), newAllocNoteList.end());
}