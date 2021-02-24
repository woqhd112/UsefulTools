// NotePad.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "NotePad.h"
#include "FolderDlg.h"
#include "NoteDlg.h"
#include "NotePadRecycle.h"
#include "BOKOToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// NotePad 대화 상자

IMPLEMENT_DYNAMIC(NotePad, CDialogEx)

NotePad::NotePad(int nManualImageID, bool bUsingManual, ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NOTEPAD, pParent)
{
	this->pParent = pParent;
	this->currentTheme = currentTheme; 
	this->bUsingManual = bUsingManual;
	usingManual = new UsingManualDialog(true, IDD_DIALOG_NOTEPAD, nManualImageID, currentTheme);
}

NotePad::~NotePad()
{
	if (notepadlist)
	{
		delete notepadlist;
		notepadlist = nullptr;
	}

	if (folderlist)
	{
		delete folderlist;
		folderlist = nullptr;
	}

	if (usingManual)
	{
		delete usingManual;
		usingManual = nullptr;
	}

	if (notepadrecycle)
	{
		delete notepadrecycle;
		notepadrecycle = nullptr;
	}

	delete notePadManager;
}

void NotePad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_EDIT_BOLD, m_btn_edit_bold);
	DDX_Control(pDX, IDC_BUTTON_EDIT_ITALIC, m_btn_edit_italic);
	DDX_Control(pDX, IDC_BUTTON_EDIT_UNDERLINE, m_btn_edit_underline);
	DDX_Control(pDX, IDC_RICHEDIT_NOTEPAD, m_richedit_note);
	//DDX_Control(pDX, IDC_BUTTON_NOTEPAD_REPORT, m_btn_report);
	DDX_Control(pDX, IDC_STATIC_NOTEPAD_LIST, m_stt_notepad_list);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_TRASH, m_btn_trash);
	DDX_Control(pDX, IDC_STATIC_FOLDER_LIST, m_stt_folderlist);
	DDX_Control(pDX, IDC_BUTTON_ADD_FOLDER, m_btn_addfolder);
	DDX_Control(pDX, IDC_BUTTON_ALL_NOTEFOLDER, m_btn_allfolder);
	DDX_Control(pDX, IDC_BUTTON_OTHER_NOTEFOLDER, m_btn_otherfolder);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_REPORT, m_btn_report);
	DDX_Control(pDX, IDC_BUTTON_NOTEPAD_CREATE_NOTE, m_btn_create_note);
	DDX_Control(pDX, IDC_EDIT_NOTEPAD_LATELY_NOTE, m_edit_lately_note);
}


BEGIN_MESSAGE_MAP(NotePad, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_EDIT_BOLD, &NotePad::OnBnClickedButtonEditBold)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_ITALIC, &NotePad::OnBnClickedButtonEditItalic)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_UNDERLINE, &NotePad::OnBnClickedButtonEditUnderline)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_REPORT, &NotePad::OnBnClickedButtonNotepadReport)
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ALL_NOTEFOLDER, &NotePad::OnBnClickedButtonAllNotefolder)
	ON_BN_CLICKED(IDC_BUTTON_OTHER_NOTEFOLDER, &NotePad::OnBnClickedButtonOtherNotefolder)
	ON_BN_CLICKED(IDC_BUTTON_ADD_FOLDER, &NotePad::OnBnClickedButtonAddFolder)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_CREATE_NOTE, &NotePad::OnBnClickedButtonNotepadCreateNote)
	ON_BN_CLICKED(IDC_BUTTON_NOTEPAD_TRASH, &NotePad::OnBnClickedButtonNotepadTrash)
END_MESSAGE_MAP()


// NotePad 메시지 처리기

void NotePad::InvalidateSame()
{
	notepadlist->Invalidate();
	folderlist->Invalidate();
}

BOOL NotePad::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(currentTheme->GetFunctionBkColor());
	m_topBrush.CreateSolidBrush(currentTheme->GetFunctionBkColor());
	m_bottomBrush.CreateSolidBrush(RGB(255, 255, 255));
	
	this->SetWindowPos(NULL, 0, 0, MARGIN_X(435), MARGIN_Y(674), SWP_NOMOVE);

	m_btn_edit_bold.MoveWindow(20, 20, 25, 25);
	m_btn_edit_italic.MoveWindow(50, 20, 25, 25);
	m_btn_edit_underline.MoveWindow(80, 20, 25, 25);
	m_btn_create_note.MoveWindow(390, 20, 25, 25);
	m_richedit_note.MoveWindow(20, 50, 395, 120);
	m_stt_notepad_list.MoveWindow(20, 320, 395, 254);
	m_btn_report.MoveWindow(365, 125, 64, 64);
	wrapBorderRect = { 15, 45, 405, 175 };
	wrapCenterRect = { 20, 50, 415, 170 };

	m_btn_allfolder.MoveWindow(20, 200, 30, 110);
	m_btn_otherfolder.MoveWindow(60, 200, 30, 110);
	m_stt_folderlist.MoveWindow(100, 200, 270, 110);
	m_btn_addfolder.MoveWindow(370, 200, 45, 110);
	m_btn_trash.MoveWindow(350, 584, 64, 64);
	m_edit_lately_note.MoveWindow(20, 584, 330, 64);

	m_btn_otherfolder.GetWindowRect(otherButtonRect);
	m_btn_trash.GetWindowRect(trashButtonRect);
	ScreenToClient(otherButtonRect);
	ScreenToClient(trashButtonRect);

	m_btn_edit_bold.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_edit_italic.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_edit_underline.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_create_note.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);
	m_btn_edit_bold.m_bUseMouseTextItalicEvent = true;
	m_btn_edit_italic.m_bUseMouseTextItalicEvent = true;
	m_btn_edit_underline.m_bUseMouseTextItalicEvent = true;
	m_btn_edit_bold.SetTextColor(currentTheme->GetTextColor());
	m_btn_edit_italic.SetTextColor(currentTheme->GetTextColor());
	m_btn_edit_underline.SetTextColor(currentTheme->GetTextColor());
	m_btn_create_note.SetTextColor(currentTheme->GetTextColor());


	m_btn_report.LoadStdImage(IDB_PNG_NOTEPAD_REPORT_NOMAL, _T("PNG"));
	m_btn_report.LoadHovImage(IDB_PNG_NOTEPAD_REPORT_HOVER, _T("PNG"));
	m_btn_report.LoadAltImage(IDB_PNG_NOTEPAD_REPORT_CLICK, _T("PNG"));

	/*m_btn_allfolder.LoadStdImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);
	m_btn_allfolder.LoadHovImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);
	m_btn_allfolder.LoadAltImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);

	m_btn_otherfolder.LoadStdImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);
	m_btn_otherfolder.LoadHovImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);
	m_btn_otherfolder.LoadAltImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);*/

	/*m_btn_addfolder.LoadStdImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);
	m_btn_addfolder.LoadHovImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);
	m_btn_addfolder.LoadAltImage(IDB_PNG_TEST_IMAGE, _T("PNG"), true);*/
	m_btn_allfolder.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 30);
	m_btn_allfolder.SetWindowTextW(_T("\n전\n체"));
	m_btn_allfolder.SetTextColor(currentTheme->GetTextColor());
	m_btn_otherfolder.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 30);
	m_btn_otherfolder.SetWindowTextW(_T("\n기\n타"));
	m_btn_otherfolder.SetTextColor(currentTheme->GetTextColor());
	m_btn_addfolder.Initialize(currentTheme->GetButtonColor(), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 30);
	m_btn_addfolder.SetWindowTextW(_T("+"));
	m_btn_addfolder.SetTextColor(currentTheme->GetTextColor());

	m_btn_report.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_richedit_note.ModifyStyle(0, WS_CLIPSIBLINGS, 0);

	m_btn_report.BringWindowToTop();

	thisFont.CreateFontW(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		currentTheme->GetThemeFontName());

	m_richedit_note.SetFont(&thisFont);
	m_edit_lately_note.Initialize(25, currentTheme->GetThemeFontName());

	CRect notepadlistRect, folderlistRect, dragRect;
	m_stt_notepad_list.GetWindowRect(notepadlistRect);
	m_stt_folderlist.GetWindowRect(folderlistRect);
	this->GetWindowRect(dragRect);

	notePadManager = new NotePadManager(currentTheme);

	notepadlist = new NotePadList(notePadManager, currentTheme, this);
	notepadlist->Create(IDD_DIALOG_NOTEPAD_LIST, &m_stt_notepad_list);
	notepadlist->MoveWindow(0, 0, notepadlistRect.Width(), notepadlistRect.Height());
	notepadlist->ShowWindow(SW_SHOW);

	folderlist = new FolderList(notePadManager, currentTheme, this);
	folderlist->Create(IDD_DIALOG_FOLDER_LIST, &m_stt_folderlist);
	folderlist->MoveWindow(0, 0, folderlistRect.Width(), folderlistRect.Height());
	folderlist->ShowWindow(SW_SHOW);

	notepadrecycle = new NotePadRecycle(currentTheme, this);
	notepadrecycle->Create(IDD_DIALOG_NOTEPAD_RECYCLE, this);
	
	LoadNotePad();


	if (notePadManager->m_recycleNoteList.empty() && notePadManager->m_recycleFolderList.empty())
	{
		m_btn_trash.LoadStdImage(IDB_PNG_NOTEPAD_RECYCLE_EMPTY_NOMAL, _T("PNG"));
		m_btn_trash.LoadHovImage(IDB_PNG_NOTEPAD_RECYCLE_EMPTY_HOVER, _T("PNG"));
		m_btn_trash.LoadAltImage(IDB_PNG_NOTEPAD_RECYCLE_EMPTY_CLICK_FULL_NOMAL, _T("PNG"));
	}
	else
	{
		m_btn_trash.LoadStdImage(IDB_PNG_NOTEPAD_RECYCLE_EMPTY_CLICK_FULL_NOMAL, _T("PNG"));
		m_btn_trash.LoadHovImage(IDB_PNG_NOTEPAD_RECYCLE_FULL_HOVER_CLICK, _T("PNG"));
		m_btn_trash.LoadAltImage(IDB_PNG_NOTEPAD_RECYCLE_FULL_HOVER_CLICK, _T("PNG"));
	}
	m_btn_trash.EnableToggle();

	notepadlist->LoadNotePad(notePadManager->m_allNoteList);
	folderlist->LoadFolder(notePadManager->m_allFolderList);

	if (bUsingManual)
	{
		usingManual->Create(IDD_DIALOG_USING_MANUAL, GetDesktopWindow());
		usingManual->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void NotePad::SetLatelyNote(CString strLatelyNote)
{
	strLatelyNoteContent = strLatelyNote;
	m_edit_lately_note.SetWindowTextW(strLatelyNoteContent);
}


void NotePad::LoadNotePad()
{
	notePadManager->Init(notepadlist, folderlist, notepadrecycle);
	if (notePadManager->LoadNotePadData())
	{
		SetLatelyNote(notePadManager->GetLatleyNoteContent());
		notepadrecycle->Init(notePadManager->m_recycleNoteList, notePadManager->m_recycleFolderList);
	}
}

void NotePad::LoadAllNote()
{
	notePadManager->SetNoteView(notePadManager->m_allNoteList, NotePadManager::NOTE_VIEW_ALL);
	notepadlist->LoadNotePad(notePadManager->m_viewNoteList);
}

void NotePad::LoadOtherNote()
{
	std::vector<ViewNoteList> allocnotelist;  
	allocnotelist.push_back(notePadManager->m_otherNoteList);
	notePadManager->SetNoteView(allocnotelist, NotePadManager::NOTE_VIEW_OTHER);
	notepadlist->LoadNotePad(notePadManager->m_viewNoteList);
}

void NotePad::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void NotePad::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	NotePad::PostNcDestroy();
}

void NotePad::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBOKOToolsDlg* parent = (CBOKOToolsDlg*)pParent;
	parent->bNotepad = false;
	delete this;
	CDialogEx::PostNcDestroy();
}



HBRUSH NotePad::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

BOOL NotePad::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}



void NotePad::OnBnClickedButtonEditBold()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	/*long nStart = 0;
	long nEnd = 0;
	m_richedit_note.GetSel(nStart, nEnd);
	CString strText = m_richedit_note.GetSelText();

	CHARFORMAT getcf;
	m_richedit_note.GetSelectionCharFormat(getcf);

	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = getcf.dwMask | CFM_BOLD;
	cf.dwEffects = getcf.dwEffects | CFE_BOLD;
	m_richedit_note.SetSelectionCharFormat(cf);
	m_richedit_note.ReplaceSel(strText);
	m_richedit_note.SetSel(nStart, nEnd);
	m_richedit_note.SetFocus();*/
}


void NotePad::OnBnClickedButtonEditItalic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*long nStart = 0;
	long nEnd = 0;
	m_richedit_note.GetSel(nStart, nEnd);
	CString strText = m_richedit_note.GetSelText();

	CHARFORMAT getcf;
	m_richedit_note.GetSelectionCharFormat(getcf);

	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = getcf.dwMask | CFM_ITALIC;
	cf.dwEffects = getcf.dwEffects | CFE_ITALIC;
	m_richedit_note.SetSelectionCharFormat(cf);
	m_richedit_note.ReplaceSel(strText);
	m_richedit_note.SetSel(nStart, nEnd);
	m_richedit_note.SetFocus();*/
}


void NotePad::OnBnClickedButtonEditUnderline()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*long nStart = 0;
	long nEnd = 0;
	m_richedit_note.GetSel(nStart, nEnd);
	CString strText = m_richedit_note.GetSelText();

	CHARFORMAT getcf;
	m_richedit_note.GetSelectionCharFormat(getcf);

	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = getcf.dwMask | CFM_UNDERLINE;
	cf.dwEffects = getcf.dwEffects | CFE_UNDERLINE;
	m_richedit_note.SetSelectionCharFormat(cf);
	m_richedit_note.ReplaceSel(strText);
	m_richedit_note.SetSel(nStart, nEnd);
	m_richedit_note.SetFocus();*/
}


void NotePad::OnBnClickedButtonNotepadReport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strNoteContent;
	m_richedit_note.GetWindowTextW(strNoteContent);
	
	// title, content를 notepadlist에 전달해서 버튼생성
	if (!strNoteContent.IsEmpty())
	{
		notepadlist->AddNotePad(strNoteContent, false);
		SetLatelyNote(strNoteContent);
	}

	m_richedit_note.SetWindowTextW(_T(""));
}


void NotePad::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CRect changeRect;
	GetWindowRect(&changeRect);
	dragRect.SetRect(changeRect.left, changeRect.top, dragRect.right + (changeRect.left - dragRect.left), dragRect.bottom + (changeRect.top - dragRect.top));
}


void NotePad::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CBrush *pOld;
	dc.SelectObject(&m_topBrush);
	dc.PatBlt(wrapBorderRect.left, wrapBorderRect.top, wrapBorderRect.Width(), wrapBorderRect.Height(), PATCOPY);
	pOld = dc.SelectObject(&m_bottomBrush);
	dc.PatBlt(wrapCenterRect.left, wrapCenterRect.top, wrapCenterRect.Width(), wrapCenterRect.Height(), PATCOPY);
	dc.SelectObject(pOld);
}


void NotePad::OnBnClickedButtonAllNotefolder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoadAllNote();
	for (int i = 0; i < (int)notePadManager->m_allFolderList.size(); i++)
	{
		FolderItem0* targetFolder = notePadManager->m_allFolderList.at(i);
		if (targetFolder)
		{
			if (targetFolder == folderlist->downFolder)
			{
				targetFolder->folderButton->ToggleClickChange();
				folderlist->downFolder = nullptr;
				folderlist->undoFolder = nullptr;
			}
		}
	}
}


void NotePad::OnBnClickedButtonOtherNotefolder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoadOtherNote();
	for (int i = 0; i < (int)notePadManager->m_allFolderList.size(); i++)
	{
		FolderItem0* targetFolder = notePadManager->m_allFolderList.at(i);
		if (targetFolder)
		{
			if (targetFolder == folderlist->downFolder)
			{
				targetFolder->folderButton->ToggleClickChange();
				folderlist->downFolder = nullptr;
				folderlist->undoFolder = nullptr;
			}
		}
	}
}


void NotePad::OnBnClickedButtonAddFolder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	COLORREF createTagColor;
	CString strCreateFolderName;
	FolderDlg createFolder(FOLDER_CREATE, currentTheme, &createTagColor, &strCreateFolderName, this);
	if (createFolder.DoModal() == IDOK)
	{
		FolderItem0* newFolder = new FolderItem0(currentTheme, folderlist);
		FolderItem0::FolderInit folderinit;
		folderinit.strFolderName = strCreateFolderName;
		folderinit.nFolderSequence = notePadManager->MaxFolderSequence() + 1;
		folderinit.nFolderSize = 0;
		folderinit.nFolderColorIndex = notePadManager->GetIndexFromTagColor(createTagColor);
		folderinit.folder = { };
		folderinit.createTime = CTime::GetCurrentTime();
		folderinit.updateTime = folderinit.createTime;

		NotePadManager::FolderSaveData folderdata;
		folderdata.strFolderName = strCreateFolderName;
		folderdata.folderTagColor = createTagColor;
		folderdata.nFolderSequence = folderinit.nFolderSequence;
		folderdata.nSize = 0;
		folderdata.strCreateTime = notePadManager->GetTimeCal(folderinit.createTime);
		folderdata.strUpdateTime = folderdata.strCreateTime;

		notePadManager->CreateFolderXml(folderdata);

		newFolder->Initialize(folderinit);
		notePadManager->AddFolder(newFolder);
		notepadlist->LoadNotePad(notePadManager->m_viewNoteList);
		folderlist->LoadFolder(notePadManager->m_allFolderList);
	}
}


void NotePad::OnBnClickedButtonNotepadCreateNote()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bool isLock = false;
	CString strNoteContent;
	if (notepadlist->OpenNoteDlg(NOTE_CREATE, &strNoteContent, &isLock))
	{
		notepadlist->AddNotePad(strNoteContent, isLock);
		SetLatelyNote(strNoteContent);
	}
}

void NotePad::OnBnClickedButtonNotepadTrash()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	notepadrecycle->LoadRecycleData();
	notepadrecycle->MoveWindow(dragRect.right, dragRect.top, 500, 500);
	notepadrecycle->ShowWindow(SW_SHOW);
	/*if(notepadrecycle->DoModal() == IDOK)
	{

		m_btn_trash.ToggleClickChange();
	}*/
}
