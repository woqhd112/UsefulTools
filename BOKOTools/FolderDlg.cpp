// FolderDlg.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "FolderDlg.h"
#include "afxdialogex.h"


// FolderDlg 대화 상자

IMPLEMENT_DYNAMIC(FolderDlg, CDialogEx)

FolderDlg::FolderDlg(int nFolderMode, ThemeData* currentTheme, COLORREF* tagColor, CString* strFolderName,  CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE_FOLDER, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
	this->nFolderMode = nFolderMode;
	this->tagColor = tagColor;
	this->strFolderName = strFolderName;
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
	DDX_Control(pDX, IDC_STATIC_FOLDER_COLORINDEX, m_stt_colorindex);
	DDX_Control(pDX, IDC_STATIC_FOLDER_NAME, m_stt_folder_name);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_FOLDER_SAVE, m_btn_save);
}


BEGIN_MESSAGE_MAP(FolderDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_COLORINDEX_1, &FolderDlg::OnBnClickedButtonNotepadColorindex1)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_COLORINDEX_2, &FolderDlg::OnBnClickedButtonNotepadColorindex2)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_COLORINDEX_3, &FolderDlg::OnBnClickedButtonNotepadColorindex3)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_COLORINDEX_4, &FolderDlg::OnBnClickedButtonNotepadColorindex4)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_COLORINDEX_5, &FolderDlg::OnBnClickedButtonNotepadColorindex5)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_COLORINDEX_6, &FolderDlg::OnBnClickedButtonNotepadColorindex6)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_COLORINDEX_7, &FolderDlg::OnBnClickedButtonNotepadColorindex7)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_FOLDER_SAVE, &FolderDlg::OnBnClickedButtonNotepadFolderSave)
END_MESSAGE_MAP()


// FolderDlg 메시지 처리기


BOOL FolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (nFolderMode == FOLDER_CREATE)
	{
		this->SetWindowTextW(_T("폴더 생성"));
		this->SetBackgroundColor(TAG_COLOR_5);
		m_edit_foldername.SetWindowTextW(_T(""));
	}
	else
	{
		this->SetWindowTextW(_T("폴더 수정"));
		this->SetBackgroundColor(*tagColor);
		m_edit_foldername.SetWindowTextW(*strFolderName);
	}
	this->SetWindowPos(NULL, 0, 0, MARGIN_X(240), MARGIN_Y(240), SWP_NOMOVE);

	m_stt_colorindex.MoveWindow(20, 20, 200, 30);
	m_btn_colorindex_1.MoveWindow(20, 50, 20, 20);
	m_btn_colorindex_2.MoveWindow(50, 50, 20, 20);
	m_btn_colorindex_3.MoveWindow(80, 50, 20, 20);
	m_btn_colorindex_4.MoveWindow(110, 50, 20, 20);
	m_btn_colorindex_5.MoveWindow(140, 50, 20, 20);
	m_btn_colorindex_6.MoveWindow(170, 50, 20, 20);
	m_btn_colorindex_7.MoveWindow(200, 50, 20, 20);
	m_stt_folder_name.MoveWindow(20, 100, 200, 30);
	m_edit_foldername.MoveWindow(20, 130, 200, 50);
	m_btn_save.MoveWindow(80, 190, 100, 30);

	m_stt_colorindex.Initialize(20, currentTheme->GetThemeFontName());
	m_stt_folder_name.Initialize(20, currentTheme->GetThemeFontName());
	m_btn_colorindex_1.Initialize(TAG_COLOR_1, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_colorindex_2.Initialize(TAG_COLOR_2, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_colorindex_3.Initialize(TAG_COLOR_3, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_colorindex_4.Initialize(TAG_COLOR_4, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_colorindex_5.Initialize(TAG_COLOR_5, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_colorindex_6.Initialize(TAG_COLOR_6, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_colorindex_7.Initialize(TAG_COLOR_7, CMFCButton::FlatStyle::BUTTONSTYLE_3D);
	m_btn_save.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_save.SetTextColor(currentTheme->GetTextColor());

	editFont.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		currentTheme->GetThemeFontName());
	m_edit_foldername.SetFont(&editFont);
	m_edit_foldername.LimitText(20);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void FolderDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
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
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(currentTheme->GetFunctionTextColor());
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void FolderDlg::OnBnClickedButtonNotepadColorindex1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SetBackgroundColor(TAG_COLOR_1);
	selectColor = TAG_COLOR_1;
}


void FolderDlg::OnBnClickedButtonNotepadColorindex2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SetBackgroundColor(TAG_COLOR_2);
	selectColor = TAG_COLOR_2;
}


void FolderDlg::OnBnClickedButtonNotepadColorindex3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SetBackgroundColor(TAG_COLOR_3);
	selectColor = TAG_COLOR_3;
}


void FolderDlg::OnBnClickedButtonNotepadColorindex4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SetBackgroundColor(TAG_COLOR_4);
	selectColor = TAG_COLOR_4;
}


void FolderDlg::OnBnClickedButtonNotepadColorindex5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SetBackgroundColor(TAG_COLOR_5);
	selectColor = TAG_COLOR_5;
}


void FolderDlg::OnBnClickedButtonNotepadColorindex6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SetBackgroundColor(TAG_COLOR_6);
	selectColor = TAG_COLOR_6;
}


void FolderDlg::OnBnClickedButtonNotepadColorindex7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->SetBackgroundColor(TAG_COLOR_7);
	selectColor = TAG_COLOR_7;
}


void FolderDlg::OnBnClickedButtonNotepadFolderSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strFolderNameText;
	m_edit_foldername.GetWindowTextW(strFolderNameText);
	if (strFolderNameText.IsEmpty())
	{
		MessageBox(_T("폴더명을 입력하세요."));
		m_edit_foldername.SetFocus();
		return;
	}
	*tagColor = selectColor;
	*strFolderName = strFolderNameText;
	FolderDlg::OnOK();
}
