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

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void FolderList::LoadFolder()
{

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
