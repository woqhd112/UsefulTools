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

void NotePadList::LoadNotePad(std::vector<ViewNoteList> allFolderList)
{
	scroll.Destroy();

	scroll.Create(this);
	CustomScroll::CustomScrollInfo csi;
	csi.cst = CustomScroll::CUSTOM_SCROLL_TYPE_BUTTON;
	csi.nAllPageSize = 0;
	csi.nKindOfScrollFlags = SB_VERT;
	csi.nOnePageSize = 252;
	csi.nScrollPos = 0;
	scroll.Initialize(csi);

	for (int i = 0; i < (int)allFolderList.size(); i++)
	{
		ViewNote(allFolderList.at(i));
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
	int nStartPos_y = 2;
	int nPictureSize = 40;

	int nPictureToPictureMargin_y = 2;
	//int nPictureToPictureMargin_x = 30;
	CRect ButtonPos;

	nStartPos_y += ((nPictureSize + nPictureToPictureMargin_y) * (nItemCount));

	//nStartPos_x += ((nPictureSize + nPictureToPictureMargin_x) * (nItemCount % 4));

	ButtonPos = { nStartPos_x, nStartPos_y, nStartPos_x + nPictureSize, nStartPos_y + nPictureSize };
	return ButtonPos;
}

void NotePadList::AddNotePad(CString strTitle, CString strContent)
{
	// 버튼생성 함수 (index와 f인지 n인지에 따라서 폴더이미지 또는 노트이미지 생성)
	//CString strButtonName;
	//strButtonName.Format(_T("%dn0n"), nButtonCount + 1);
	//InsertNewNote(false, strButtonName, strContent, false);
	//if (nButtonCount != 1)
	//{
	//	if ((nButtonCount - 1) % 4 == 0)
	//		scroll.IncreaseScroll();
	//}

	//for (int i = scroll.GetCurrentLinePos(); i < scroll.GetLineCount(); i++)
	//{
	//	OnVScroll(SB_PAGEDOWN, 0, GetScrollBarCtrl(SB_VERT));
	//}

	//// NotePad.conf에 추가
	//CMarkup markUp;
	//CString strFullPath = _T("");
	//CustomXml::CreateConfigFile(strFullPath);
	//strFullPath += _T("\\NotePad.conf");
	//if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	//{
	//	markUp.FindElem(_T("NotePad"));
	//	markUp.IntoElem();

	//	markUp.AddElem(_T("list"));
	//	markUp.AddAttrib(_T("idx"), nButtonCount - 1);
	//	markUp.AddAttrib(_T("name"), strButtonName);
	//	markUp.AddAttrib(_T("lock"), 0);
	//}
	//CustomXml::SaveXml(&markUp, strFullPath);

	//// Note 폴더에 파일추가
	//CString strTextPath = _T("");
	//CustomXml::GetModulePath(strTextPath);
	//strTextPath += _T("\\Note\\");

	//NoteFile file;
	//if (file.NoteWrite(strTextPath + strButtonName + _T(".txt"), strContent))
	//{

	//}
}

void NotePadList::ViewNote(ViewNoteList notelist)
{
	for (int i = 0; i < (int)notelist.size(); i++)
	{
		NoteItem* targetNote = notelist.at(i);
		CRect noteRect;
		int n = scroll.GetCurrentLinePos();
		noteRect = SetButtonPosition(nButtonCount - ((scroll.GetCurrentLinePos() - 1) * 5));
		targetNote->ShowWindow(true);
		targetNote->ShowLock(targetNote->IsLock() ? true : false);
		targetNote->MoveWindow(noteRect.left, noteRect.top);
		CString strTagCount;
		strTagCount.Format(_T("%d"), nButtonCount + 1);
		targetNote->tagButton->SetWindowTextW(strTagCount);
		nButtonCount++;
		if (nButtonCount > 1)
		{
			if ((nButtonCount - 1) % 5 == 0)
				nLineEndCount++;
		}
	}
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
	
	return bReturn;
}

BOOL NotePadList::DragEventDown(HWND downHWND, CPoint downPoint)
{
	BOOL bReturn = FALSE;
	
	return bReturn;
}

BOOL NotePadList::DragEventMove(HWND moveHWND, CPoint movePoint)
{
	BOOL bReturn = FALSE;

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
