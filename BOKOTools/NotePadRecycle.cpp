// NotePadRecycle.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "NotePadRecycle.h"
#include "NotePad.h"
#include "afxdialogex.h"


// NotePadRecycle 대화 상자

IMPLEMENT_DYNAMIC(NotePadRecycle, CDialogEx)

NotePadRecycle::NotePadRecycle(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NOTEPAD_RECYCLE, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
}

NotePadRecycle::~NotePadRecycle()
{
}

void NotePadRecycle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NotePadRecycle, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// NotePadRecycle 메시지 처리기

// 메모를 복구할떈 폴더 정보를 읽어 존재하면 해당폴더로 없으면 전부 기타폴더에 들어가게설정
// 폴더복구할땐 seq번호 맨 마지막의 + 1로 설정

BOOL NotePadRecycle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());

	notepad = (NotePad*)pParent;


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void NotePadRecycle::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
}


BOOL NotePadRecycle::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void NotePadRecycle::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	this->ShowWindow(SW_HIDE);
	notepad->m_btn_trash.ToggleClickChange();
	//CDialogEx::OnOK();
	//CDialogEx::OnClose();
}


HBRUSH NotePadRecycle::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void NotePadRecycle::Init(ViewNoteList recycleNoteList, ViewFolderList recycleFolderList)
{
	this->recycleNoteList = recycleNoteList;
	this->recycleFolderList = recycleFolderList;
}

CRect NotePadRecycle::SetNoteButtonPosition(int nNoteIndex)
{
	int nStartPos_Valy = 30;

	int nPictureSize_x = 365;
	int nPictureSize_y = 40;

	int nPictureToPictureMargin_y = 2;

	CRect ButtonPos;

	nStartPos_Valy += ((nPictureSize_y + nPictureToPictureMargin_y) * (nNoteIndex));
	nStartPos_Sumy = nStartPos_y + nStartPos_Valy;

	ButtonPos = { nStartPos_x, nStartPos_Sumy, nStartPos_x + nPictureSize_x, nStartPos_Sumy + nPictureSize_y };
	return ButtonPos;
}

CRect NotePadRecycle::SetFolderButtonPosition(int nFolderIndex)
{
	int nStartPos_Valx = 30;
	int nStartPos_Valy = 30;

	int nPictureSize_x = 64;
	int nPictureSize_y = 64 + 20;

	int nPictureToPictureMargin_y = 20;
	int nPictureToPictureMargin_x = 30;
	CRect ButtonPos;

	nStartPos_Valy += ((nPictureSize_y + nPictureToPictureMargin_y) * (nFolderIndex / 4));
	nStartPos_y = nStartPos_Valy;
	nStartPos_Sumy = nStartPos_y;

	nStartPos_Valx += ((nPictureSize_x + nPictureToPictureMargin_x) * (nFolderIndex % 4));
	nStartPos_x = nStartPos_Valx;
	nStartPos_Sumx = nStartPos_x;

	ButtonPos = { nStartPos_Valx, nStartPos_Valy, nStartPos_Valx + nPictureSize_x, nStartPos_Valy + nPictureSize_y };
	return ButtonPos;
}

void NotePadRecycle::LoadRecycleData()
{
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.csf = CustomScroll::CUSTOM_SCROLL_FLAGS_VERTICAL;
	csi.nAllPageSize = 0;
	csi.nOnePageSize = 500;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	nStartPos_x = 30;
	nStartPos_y = 30;
	nStartPos_Sumx = 30;
	nStartPos_Sumy = 30;

	for (int i = 0; i < recycleFolderList.Size(); i++)
	{
		FolderItem0* recycleFolder = recycleFolderList.At(i);
		CRect folderRect = SetFolderButtonPosition(i);
		recycleFolder->ShowWindow(true);
		recycleFolder->MoveWindow(folderRect.left, folderRect.top);

		if (nStartPos_Sumy >= 500 * scroll.GetLineCount())
			scroll.LineEnd();
	}

	nStartPos_x = 30;
	nStartPos_y += 84;

	for (int i = 0; i < recycleNoteList.Size(); i++)
	{
		NoteItem* recycleNote = recycleNoteList.At(i);
		CRect noteRect = SetNoteButtonPosition(i);
		recycleNote->ShowWindow(true);
		recycleNote->ShowLock(recycleNote->IsLock());
		recycleNote->MoveWindow(noteRect.left, noteRect.top);

		if (nStartPos_Sumy >= 500 * scroll.GetLineCount())
			scroll.LineEnd();
	}

	scroll.ExecuteScrollPos(currentTheme);

	Invalidate();
}

void NotePadRecycle::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	scroll.OperateScroll(nSBCode, nPos);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL NotePadRecycle::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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
