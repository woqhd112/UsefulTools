// FolderDlg.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "FolderList.h"
#include "FolderDlg.h"
#include "afxdialogex.h"


// FolderDlg 대화 상자

IMPLEMENT_DYNAMIC(FolderDlg, CDialogEx)

FolderDlg::FolderDlg(FolderItem0* folder, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FOLDER, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	this->folder = folder;
}

FolderDlg::~FolderDlg()
{
}

void FolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FolderDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// FolderDlg 메시지 처리기


BOOL FolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	this->SetWindowTextW(folder->GetFolderName());
	
	folderlist = (FolderList*)pParent;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void FolderDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	folder->folderButton->ToggleClickChange();
	CDialogEx::OnClose();
}


void FolderDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL FolderDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH FolderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
