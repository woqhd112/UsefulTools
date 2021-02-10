// FolderDlg.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "FolderDlg.h"
#include "afxdialogex.h"


// FolderDlg 대화 상자

IMPLEMENT_DYNAMIC(FolderDlg, CDialogEx)

FolderDlg::FolderDlg(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/, COLORREF tagColor /*= TAG_COLOR_5*/)
	: CDialogEx(IDD_DIALOG_CREATE_FOLDER, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	this->tagColor = tagColor;
}

FolderDlg::~FolderDlg()
{
}

void FolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_COLORINDEX_1, m_btn_colorindex_1);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_COLORINDEX_2, m_btn_colorindex_2);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_COLORINDEX_3, m_btn_colorindex_3);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_COLORINDEX_4, m_btn_colorindex_4);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_COLORINDEX_5, m_btn_colorindex_5);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_COLORINDEX_6, m_btn_colorindex_6);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_COLORINDEX_7, m_btn_colorindex_7);
	DDX_Control(pDX, IDC_EDIT_NOTEPAD_FOLDER_NAME, m_edit_foldername);
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
	this->SetBackgroundColor(tagColor);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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


void FolderDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH FolderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
