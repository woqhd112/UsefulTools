// NotePadList.cpp: 구현 파일
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
}

NotePadList::~NotePadList()
{
	
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
		targetNote->tagButton->SetWindowTextW(strTagCount);
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

bool NotePadList::InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName)
{

	return true;
}

BOOL NotePadList::DragEventUp(HWND upHWND, CPoint upPoint, NoteItem* findnote)
{
	BOOL bReturn = FALSE;
	if (ExistDragDlg())
	{

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
	
	return bReturn;
}

BOOL NotePadList::DetectionPtInRect(const RECT* lprc, POINT pt)
{
	// 마우스가 rect에 포함되어 있고
	// 마우스 좌표가 중앙보다 작을경우 (rect에서 상단에 위치할경우 /정중앙도 포함)
	if (lprc->bottom >= pt.y && lprc->top <= pt.y &&
		lprc->left <= pt.x && lprc->right >= pt.x &&
		(lprc->bottom - ((lprc->bottom - lprc->top) / 2)) >= pt.y)
	{
		notePosState = NOTE_POS_STATE_HALF_UP;
		return TRUE;
	}
	// 마우스가 rect에 포함되어 있고
	// 마우스 좌표가 중앙보다 클경우 (rect에서 하단에 위치할경우)
	else if (lprc->bottom >= pt.y && lprc->top <= pt.y &&
		lprc->left <= pt.x && lprc->right >= pt.x &&
		(lprc->bottom - ((lprc->bottom - lprc->top) / 2)) < pt.y)
	{
		notePosState = NOTE_POS_STATE_HALF_DOWN;
		return TRUE;
	}
	// 그밖 (모두 포함안되는 경우)
	else
	{
		notePosState = NOTE_POS_STATE_NONE;
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

		int nLocToPos = ButtonLocationToPos(convertPoint);

		CRect rect = SetButtonPosition(nLocToPos);
		/*TRACE(L"pt x : %ld\n", convertPoint.x);
		TRACE(L"pt y : %ld\n", convertPoint.y);
		TRACE(L"loc : %d\n", nLocToPos);
		TRACE(L"rect left : %ld\n", rect.left);
		TRACE(L"rect top : %ld\n", rect.top);
		TRACE(L"rect width : %d\n", rect.Width());
		TRACE(L"rect height : %d\n", rect.Height());*/
		if (DetectionPtInRect(rect, convertPoint))
		{
			if (nEventPos != nLocToPos)
			{
				if (notePosState == NOTE_POS_STATE_HALF_UP)	// 마우스 포인트가 노트의 상단부분에 있을때
				{
					NoteItem* eventItem = viewNoteList.at(findnote->GetFolderSequence()).at(nLocToPos);	// 마우스 위치에있는 노트아이템을 찾는다
					if (eventItem != findnote)	// 찾은 노트아이템과 들어올린 노트와 다를때만 
					{
						ViewNoteList notelists = viewNoteList.at(findnote->GetFolderSequence());
					
						std::iter_swap(notelists.begin() + nEventPos, notelists.begin() + nLocToPos);
						int nSwapName = 0;
						NoteItem* eventSwapItem = notelists.at(nEventPos);
						NoteItem* findSwapItem = notelists.at(nLocToPos);

						nSwapName = findSwapItem->GetNoteName();
						eventSwapItem->SetNoteName(findSwapItem->GetNoteName());
						findSwapItem->SetNoteName(nSwapName);

						CRect eventChangeRect = SetButtonPosition(nEventPos);
						eventItem->MoveWindow(eventChangeRect.left, eventChangeRect.top);
						
						CString strEventNoteTagSequnce = eventItem->GetNoteTagSequence();
						eventItem->SetNoteTagSequence(findnote->GetNoteTagSequence());
						findnote->SetNoteTagSequence(strEventNoteTagSequnce);

						nEventPos = nLocToPos;
					}
				}
				else if (notePosState == NOTE_POS_STATE_HALF_DOWN)
				{
					NoteItem* eventItem = viewNoteList.at(findnote->GetFolderSequence()).at(nLocToPos);	// 마우스 위치에있는 노트아이템을 찾는다
					if (eventItem != findnote)	// 찾은 노트아이템과 들어올린 노트와 다를때만 
					{
						ViewNoteList notelists = viewNoteList.at(findnote->GetFolderSequence());

						std::iter_swap(notelists.begin() + nEventPos, notelists.begin() + nLocToPos);
						int nSwapName = 0;
						NoteItem* eventSwapItem = notelists.at(nEventPos);
						NoteItem* findSwapItem = notelists.at(nLocToPos);

						nSwapName = findSwapItem->GetNoteName();
						eventSwapItem->SetNoteName(findSwapItem->GetNoteName());
						findSwapItem->SetNoteName(nSwapName);

						CRect eventChangeRect = SetButtonPosition(nEventPos);
						eventItem->MoveWindow(eventChangeRect.left, eventChangeRect.top);

						CString strEventNoteTagSequnce = eventItem->GetNoteTagSequence();
						eventItem->SetNoteTagSequence(findnote->GetNoteTagSequence());
						findnote->SetNoteTagSequence(strEventNoteTagSequnce);

						nEventPos = nLocToPos;
					}
				}
			}
		}
		else
		{
		
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