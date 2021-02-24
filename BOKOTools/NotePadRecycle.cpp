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

void NotePadRecycle::LoadRecycleData()
{
	int nStart_x = 30;
	int nStart_y = 30;
	// 일단 정렬은 임시임
	int nMarginValue = 0;

	for (int i = 0; i < (int)recycleFolderList.size(); i++)
	{
		FolderItem0* recycleFolder = recycleFolderList.at(i);
		recycleFolder->ShowWindow(true);
		recycleFolder->MoveWindow(nStart_x, nStart_y + nMarginValue);
		nMarginValue += 90;
	}


	for (int i = 0; i < (int)recycleNoteList.size(); i++)
	{
		NoteItem* recycleNote = recycleNoteList.at(i);
		recycleNote->ShowWindow(true);
		recycleNote->ShowLock(recycleNote->IsLock());
		recycleNote->MoveWindow(nStart_x, nStart_y + nMarginValue);
		nMarginValue += 90;
	}

	Invalidate();
}