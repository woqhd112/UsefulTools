// NotePadList.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "NotePadList.h"
#include "NotePad.h"
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
}

NotePadList::~NotePadList()
{
	for (int i = 0; i < (int)notebuttonlist.size(); i++)
	{
		CGdipButton* deleteButton = notebuttonlist.at(i);
		deleteButton->DestroyWindow();
		delete deleteButton;
		deleteButton = nullptr;
	}
	notebuttonlist.clear();

	for (int i = 0; i < (int)notetitlelist.size(); i++)
	{
		CalculateStatic* deleteStatic = notetitlelist.at(i);
		deleteStatic->DestroyWindow();
		delete deleteStatic;
		deleteStatic = nullptr;
	}
	notetitlelist.clear();

	if (trashButton)
	{
		trashButton->DestroyWindow();
		delete trashButton;
		trashButton = nullptr;
	}
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

	Init(this, notepad->GetParent(), BIND_REGULAR);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void NotePadList::LoadNotePad()
{
	trashButton = new CGdipButton;
	trashButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nButtonID++);
	trashButton->ShowWindow(SW_SHOW);
	trashButton->LoadStdImage(IDB_PNG_WORLDCLOCK_NOMAL_THEME_DETECTIVE, _T("PNG"), true);
	trashButton->LoadHovImage(IDB_PNG_WORLDCLOCK_HOVER_THEME_DETECTIVE, _T("PNG"), true);
	trashButton->LoadAltImage(IDB_PNG_WORLDCLOCK_CLICK_THEME_DETECTIVE, _T("PNG"), true);
	trashButton->MoveWindow(SetButtonPosition(11));

	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 280 - (94 * 2) + 2;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	// 메모 xml 내용 로드
	// 버튼 생성 및 위치설정
	bool bSavedXml = false;
	CMarkup markUp;
	CString szRoot = _T("");
	CustomXml::CreateConfigFile(szRoot);
	szRoot += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, szRoot))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		while (markUp.FindElem(_T("list")))
		{
			bool isFolder = false;
			CString strNotePath;
			CString strNoteName = markUp.GetAttrib(_T("name"));
			CString strLocked = markUp.GetAttrib(_T("lock"));
			int nLocked = _ttoi(strLocked);
			if (nLocked <= 0) nLocked = 0;
			else nLocked = 1;
			bool bLocked = (bool)nLocked;

			CustomXml::GetModulePath(strNotePath);
			strNotePath += (_T("\\Note\\") + strNoteName + _T(".txt"));
			if ((CString)strNoteName.GetAt(1) == _T("f")) isFolder = true;

			NoteFile file;
			CString strNoteContent = _T("");
			if (file.NoteRead(strNotePath, strNoteContent))
			{
				CString strNoteTitle = strNoteContent.Left(18);

				notelist.push_back({ strNoteTitle, strNoteContent });

				// 버튼생성 함수 (index와 f인지 n인지에 따라서 폴더이미지 또는 노트이미지 생성)
				InsertNewNote(isFolder, strNoteName, strNoteTitle, bLocked);
			}
		}
	}
	else
	{
		if (CreateDefaultNoteXml(&markUp, szRoot)) bSavedXml = true;
		if (bSavedXml)
		{
			CustomXml::SaveXml(&markUp, szRoot);
		}
	}

	for (int i = 0; i <= nLineEndCount; i++)
	{
		scroll.LineEnd();
	}

	scroll.ExecuteScrollPos(currentTheme);
}

CRect NotePadList::SetButtonPosition(int nItemCount)
{
	int nStartPos_x = 25;
	int nStartPos_y = 10;
	int nPictureSize = 64;

	int nPictureToPictureMargin_y = 30;
	int nPictureToPictureMargin_x = 30;
	CRect ButtonPos;

	nStartPos_y += ((nPictureSize + nPictureToPictureMargin_y) * (nItemCount / 4));

	nStartPos_x += ((nPictureSize + nPictureToPictureMargin_x) * (nItemCount % 4));

	ButtonPos = { nStartPos_x, nStartPos_y, nStartPos_x + nPictureSize, nStartPos_y + nPictureSize };
	return ButtonPos;
}

bool NotePadList::CreateDefaultNoteXml(CMarkup* markUp, CString strFullPath)
{
	bool bReturn = false;
	CFileFind xmlFind;
	if (!xmlFind.FindFile(strFullPath))
	{
		markUp->AddElem(_T("NotePad"));
		markUp->IntoElem();

		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
}

void NotePadList::AddNotePad(CString strTitle, CString strContent)
{
	notelist.push_back({ strTitle, strContent });

	// 버튼생성 함수 (index와 f인지 n인지에 따라서 폴더이미지 또는 노트이미지 생성)
	CString strButtonName;
	strButtonName.Format(_T("%dn0n"), nButtonCount + 1);
	InsertNewNote(false, strButtonName, strTitle, false);
	if (nButtonCount != 1)
	{
		if ((nButtonCount - 1) % 4 == 0)
			scroll.IncreaseScroll();
	}

	for (int i = scroll.GetCurrentLinePos(); i < scroll.GetLineCount(); i++)
	{
		OnVScroll(SB_PAGEDOWN, 0, GetScrollBarCtrl(SB_VERT));
	}

	// NotePad.conf에 추가
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		markUp.AddElem(_T("list"));
		markUp.AddAttrib(_T("idx"), nButtonCount - 1);
		markUp.AddAttrib(_T("name"), strButtonName);
		markUp.AddAttrib(_T("lock"), 0);
	}
	CustomXml::SaveXml(&markUp, strFullPath);

	// Note 폴더에 파일추가
	CString strTextPath = _T("");
	CustomXml::GetModulePath(strTextPath);
	strTextPath += _T("\\Note\\");

	NoteFile file;
	if (file.NoteWrite(strTextPath + strButtonName + _T(".txt"), strContent))
	{

	}
}

void NotePadList::InsertNewNote(bool isFolder, CString strFolderName, CString strNoteTitle, bool bLocked)
{
	CRect buttonRect, staticRect, lockRect;
	CGdipButton* newButton = new CGdipButton;
	newButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nButtonID++);
	newButton->strButtonName = strFolderName;
	newButton->LoadStdImage(isFolder ? IDB_PNG_STOPWATCH_NOMAL_THEME_DETECTIVE : IDB_PNG_BASE_NOMAL_THEME_DETECTIVE, _T("PNG"), true);
	newButton->LoadHovImage(isFolder ? IDB_PNG_STOPWATCH_HOVER_THEME_DETECTIVE : IDB_PNG_BASE_HOVER_THEME_DETECTIVE, _T("PNG"), true);
	newButton->LoadAltImage(isFolder ? IDB_PNG_STOPWATCH_CLICK_THEME_DETECTIVE : IDB_PNG_BASE_CLICK_THEME_DETECTIVE, _T("PNG"), true);
	buttonRect = SetButtonPosition(nButtonCount - ((scroll.GetCurrentLinePos() - 1) * 4));
	newButton->MoveWindow(buttonRect);
	nButtonCount++;
	notebuttonlist.push_back(newButton);

	CalculateStatic* newStatic = new CalculateStatic;
	newStatic->Create(strNoteTitle, SS_LEFT, CRect(0, 0, 0, 0), this, nStaticID++);
	newStatic->Initialize(15, currentTheme->GetThemeFontName());
	staticRect = { buttonRect.left, buttonRect.top + buttonRect.Height() + 5, buttonRect.right, buttonRect.top + buttonRect.Height() + 5 + 15 };
	newStatic->MoveWindow(staticRect);
	notetitlelist.push_back(newStatic);

	CGdipButton* newLock = new CGdipButton;
	newLock->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, nLockID++);
	if (bLocked)
	{
		newLock->strButtonName = _T("Lock");
		newLock->LoadStdImage(IDB_PNG_COMINGSOON_THEME_DETECTIVE, _T("PNG"), true);
		newLock->LoadHovImage(IDB_PNG_COMINGSOON_THEME_DETECTIVE, _T("PNG"), true);
		newLock->LoadAltImage(IDB_PNG_BASE_NOMAL_THEME_DETECTIVE, _T("PNG"), true);
	}
	else
	{
		newLock->strButtonName = _T("Non-Lock");
		newLock->LoadStdImage(IDB_PNG_BASE_NOMAL_THEME_DETECTIVE, _T("PNG"), true);
		newLock->LoadHovImage(IDB_PNG_BASE_NOMAL_THEME_DETECTIVE, _T("PNG"), true);
		newLock->LoadAltImage(IDB_PNG_COMINGSOON_THEME_DETECTIVE, _T("PNG"), true);
	}

	newLock->EnableToggle(TRUE);
	lockRect = { buttonRect.left + buttonRect.Width() + 2, buttonRect.top,  buttonRect.left + buttonRect.Width() + 2 + 15, buttonRect.top + 15 };
	newLock->MoveWindow(lockRect);
	lockbuttonlist.push_back(newLock);

	if (nButtonCount > 8)
	{
		newButton->ShowWindow(SW_HIDE);
		newStatic->ShowWindow(SW_HIDE);
		newLock->ShowWindow(SW_HIDE);
	}
	else
	{
		newButton->ShowWindow(SW_SHOW);
		newStatic->ShowWindow(SW_SHOW);
		newLock->ShowWindow(SW_SHOW);
	}

	OnCtlColor(newStatic->GetDC(), newStatic, CTLCOLOR_STATIC);

	if (nButtonCount != 1)
	{
		if ((nButtonCount - 1) % 8 == 0)
			nLineEndCount++;
		if ((nButtonCount - 1) % 4 == 0)
			nLineCount++;
	}
}

void NotePadList::SaveNoteXml(int nIndex, bool bLocked)
{
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		while (markUp.FindElem(_T("list")))
		{
			if (_ttoi(markUp.GetAttrib(_T("idx"))) == nIndex)
			{
				markUp.SetAttrib(_T("lock"), bLocked ? 1 : 0);
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}


int NotePadList::ButtonLocationToPos(POINT pt)
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
	for (int i = 0; i < nButtonCount_X; i++)
	{
		for (int j = 0; j < nLineCount; j++)
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

bool NotePadList::InsertNewButton(int nButtonVectorIndex, int nStdID, int nHovID, int nAltID, CString strButtonName)
{

	return true;
}

BOOL NotePadList::DragEventUp(HWND upHWND, CPoint upPoint)
{
	BOOL bReturn = FALSE;
	if (ExistDragDlg())
	{
		POINT convertPoint = upPoint;
		notepad->ScreenToClient(&convertPoint);
		convertPoint.x = convertPoint.x - 10;
		convertPoint.y = convertPoint.y - 10;

		int nLocToPos = ButtonLocationToPos(convertPoint);

		CRect rect = SetButtonPosition(nLocToPos);

		if (PtInRect(rect, convertPoint))
		{
			if (InsertNewButton(nLocToPos, GetDragButtonStdID(), GetDragButtonHovID(), GetDragButtonAltID(), GetDragButtonName()))
			{
				for (int i = 0; i < notebuttonlist.size(); i++)
				{
					if (notebuttonlist.at(i) == downButton)
					{
						CGdipButton* button = notebuttonlist.at(i);
						notebuttonlist.erase(notebuttonlist.begin() + i);
						button->DestroyWindow();
						delete button;
						button = nullptr;
						break;
					}
				}
			}
			else
			{
				for (int i = 0; i < notebuttonlist.size(); i++)
				{
					notebuttonlist.at(i)->ShowWindow(SW_SHOW);
				}
			}
		}
		else
		{
			for (int i = 0; i < notebuttonlist.size(); i++)
			{
				notebuttonlist.at(i)->ShowWindow(SW_SHOW);
			}
		}

		DeleteDragDlg();

		bReturn = TRUE;
	}
	return bReturn;
}

BOOL NotePadList::DragEventDown(HWND downHWND, CPoint downPoint)
{
	BOOL bReturn = FALSE;
	CGdipButton* findButton = NULL;
	if (FindButtonSame(notebuttonlist, downHWND, &findButton))
	{
		if (findButton != NULL)
		{
			ExecuteDragEvent(findButton);
			SetSizeDragDlg(CRect(downPoint.x + 2, downPoint.y + 2, downPoint.x + 2 + 128, downPoint.y + 2 + 128));
			downButton = findButton;
			findButton->ShowWindow(SW_HIDE);
			//EnableEmptyLine(SW_SHOW);
			bReturn = TRUE;
		}
	}
	return bReturn;
}

BOOL NotePadList::DragEventMove(HWND moveHWND, CPoint movePoint)
{
	BOOL bReturn = FALSE;
	if (IsDragging(notepad->dragRect, movePoint))
	{
		POINT convertPoint = movePoint;
		notepad->ScreenToClient(&convertPoint);
		convertPoint.x = convertPoint.x - 10;
		convertPoint.y = convertPoint.y - 10;

		int nLocToPos = ButtonLocationToPos(convertPoint);

		CRect rect = SetButtonPosition(nLocToPos);
		/*if (PtInRect(rect, convertPoint))
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
					iconMoveButtonVector.at(i)->UserLeaveEvent();
				}
			}
		}*/
		bReturn = TRUE;
	}

	return bReturn;
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
		for (int i = 0; i < (int)lockbuttonlist.size(); i++)
		{
			CGdipButton* lockButton = lockbuttonlist.at(i);
			if (pMsg->hwnd == lockButton->m_hWnd)
			{
				if (lockButton->strButtonName == _T("Non-Lock"))
				{
					lockButton->strButtonName = _T("Lock");
					SaveNoteXml(i, true);
				}
				else
				{
					lockButton->strButtonName = _T("Non-Lock");
					SaveNoteXml(i, false);
				}
			}
		}

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
	for (int i = 0; i < (int)notebuttonlist.size(); i++)
	{
		notebuttonlist.at(i)->DisConnect();
	}

	if (nSBCode == SB_PAGEDOWN)
	{
		int nLoopStart = (scroll.GetCurrentLinePos() - 1) * 4 + 4;
		int nLoopEnd = nLoopStart + 4 > (int)notebuttonlist.size() ? (int)notebuttonlist.size() : nLoopStart + 4;
		ShowButtonCtl(true, nLoopStart, nLoopEnd);
	}
	else if(nSBCode == SB_PAGEUP)
	{
		int nLoopStart = (scroll.GetCurrentLinePos() - 1) * 4 + 4 + 4;
		int nLoopEnd = nLoopStart + 4 > (int)notebuttonlist.size() ? (int)notebuttonlist.size() : nLoopStart + 4;
		ShowButtonCtl(false, nLoopStart, nLoopEnd);
	}
	
	trashButton->MoveWindow(SetButtonPosition(11));
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void NotePadList::ShowButtonCtl(bool bShow, int nStart, int nEnd)
{
	if (nStart < 0 || nEnd < 0) return;

	for (int i = nStart; i < nEnd; i++)
	{
		CGdipButton* showButton = notebuttonlist.at(i);
		CalculateStatic* showStatic = notetitlelist.at(i);
		CGdipButton* showLock = lockbuttonlist.at(i);
		showButton->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
		showStatic->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
		showLock->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	}
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
