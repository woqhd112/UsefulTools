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

FolderList::FolderList(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FOLDER_LIST, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;

	nButtonCount = 0;
	nLineEndCount = 0;
}

FolderList::~FolderList()
{
}

void FolderList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FolderList, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// FolderList 메시지 처리기


BOOL FolderList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionSubColor());
	notepad = (NotePad*)pParent;

	Init(this, notepad->GetParent(), BIND_REGULAR);

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

	return CDialogEx::PreTranslateMessage(pMsg);
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
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_HORZ;
	csi.nOnePageSize = 252;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	ViewFolder(allFolderList);

	for (int i = 0; i <= nLineEndCount; i++)
	{
		scroll.LineEnd();
	}

	scroll.ExecuteScrollPos(currentTheme);
}

void FolderList::ViewFolder(ViewFolderList folderlist)
{
	for (int i = 1; i < (int)folderlist.size(); i++)
	{
		FolderItem0* targetFolder = folderlist.at(i);
		CRect folderRect;
		folderRect = SetButtonPosition(nButtonCount - ((scroll.GetCurrentLinePos() - 1) * 5));
		targetFolder->ShowWindow(true);
		targetFolder->MoveWindow(folderRect.left, folderRect.top);
		targetFolder->folderStatic->SetWindowTextW(targetFolder->GetFolderName());
		nButtonCount++;
		if (nButtonCount > 1)
		{
			if ((nButtonCount - 1) % 4 == 0)
				nLineEndCount++;
		}
	}
}

CRect FolderList::SetButtonPosition(int nItemCount)
{
	int nStartPos_x = 20;
	int nStartPos_y = 10;
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

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL FolderList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
