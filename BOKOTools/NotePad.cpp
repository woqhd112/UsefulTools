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

	for (int i = 0; i < (int)allNoteList.size(); i++)
	{
		ViewNoteList deleteNoteList = allNoteList.at(i);
		for (int j = 0; j < (int)deleteNoteList.size(); j++)
		{
			NoteItem* deleteNote = deleteNoteList.at(j);
			delete deleteNote;
			deleteNote = nullptr;
		}
		deleteNoteList.clear();
	}
	otherNoteList.clear();
	allNoteList.clear();

	for (int i = 0; i < (int)allFolderList.size(); i++)
	{
		FolderItem0* deleteFolder = allFolderList.at(i);
		delete deleteFolder;
		deleteFolder = nullptr;
	}
	allFolderList.clear();

	for (int i = 0; i < (int)recycleNoteList.size(); i++)
	{
		NoteItem* deleteNote = recycleNoteList.at(i);
		delete deleteNote;
		deleteNote = nullptr;
	}
	recycleNoteList.clear();

	for (int i = 0; i < (int)recycleFolderList.size(); i++)
	{
		FolderItem0* deleteFolder = recycleFolderList.at(i);
		delete deleteFolder;
		deleteFolder = nullptr;
	}
	recycleFolderList.clear();
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

bool NotePad::CreateDefaultNoteXml(CMarkup* markUp, CString strFullPath)
{
	bool bReturn = false;
	CFileFind xmlFind;
	if (!xmlFind.FindFile(strFullPath))
	{
		markUp->AddElem(_T("NotePad"));
		markUp->IntoElem();
		markUp->AddElem(_T("bin"));
		markUp->AddElem(_T("recy"));

		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
}

void NotePad::UpdateNoteXml(NoteSaveData origindata, NoteSaveData updatedata)
{
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		if (markUp.FindElem(_T("bin")))
		{
			markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{
				if (_ttoi(markUp.GetAttrib(_T("seq"))) == origindata.nFolderSequence)
				{
					int nResetNoteName = 0;
					int nFolderSize = _ttoi(markUp.GetAttrib(_T("size")));
					markUp.SetAttrib(_T("size"), nFolderSize == 0 ? nFolderSize : nFolderSize - 1);
					markUp.IntoElem();
					while (markUp.FindElem(_T("note")))
					{
						if (_ttoi(markUp.GetAttrib(_T("name"))) == origindata.nNoteName)
						{
							markUp.RemoveElem();
						}
						else
						{
							markUp.SetAttrib(_T("name"), nResetNoteName);
							nResetNoteName++;
						}
					}
					markUp.OutOfElem();
				}
				else if (_ttoi(markUp.GetAttrib(_T("seq"))) == updatedata.nFolderSequence)
				{
					markUp.SetAttrib(_T("size"), _ttoi(markUp.GetAttrib(_T("size"))) + 1);
					markUp.IntoElem();
					markUp.AddElem(_T("note"));
					markUp.AddAttrib(_T("name"), updatedata.nNoteName);
					markUp.AddAttrib(_T("lock"), updatedata.nLock);
					markUp.AddAttrib(_T("create"), updatedata.strCreateTime);
					markUp.AddAttrib(_T("update"), updatedata.strUpdateTime);
					markUp.OutOfElem();
				}
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePad::SaveNoteXml(NoteSaveData notedata)
{
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		if (markUp.FindElem(_T("bin")))
		{
			markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{
				if (_ttoi(markUp.GetAttrib(_T("seq"))) == notedata.nFolderSequence)
				{
					markUp.IntoElem();
					while (markUp.FindElem(_T("note")))
					{
						if (_ttoi(markUp.GetAttrib(_T("name"))) == notedata.nNoteName)
						{
							markUp.SetAttrib(_T("lock"), notedata.nLock);
							markUp.SetAttrib(_T("update"), notedata.strUpdateTime);
						}
					}
				}
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePad::CreateNoteXml(NoteSaveData notedata)
{
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		if (markUp.FindElem(_T("bin")))
		{
			markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{
				if (_ttoi(markUp.GetAttrib(_T("seq"))) == notedata.nFolderSequence)
				{
					markUp.IntoElem();
					markUp.AddElem(_T("note"));
					markUp.AddAttrib(_T("name"), notedata.nNoteName);
					markUp.AddAttrib(_T("lock"), notedata.nLock);
					markUp.AddAttrib(_T("create"), notedata.strCreateTime);
					markUp.AddAttrib(_T("update"), notedata.strUpdateTime);
				}
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePad::SaveFolderXml(FolderSaveData folderdata)
{
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		if (markUp.FindElem(_T("bin")))
		{
			markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{
				if (_ttoi(markUp.GetAttrib(_T("seq"))) == folderdata.nFolderSequence)
				{
					markUp.SetAttrib(_T("name"), folderdata.strFolderName);
					markUp.SetAttrib(_T("tagcolor"), GetIndexFromTagColor(folderdata.folderTagColor));
					markUp.SetAttrib(_T("size"), folderdata.nSize);
					markUp.SetAttrib(_T("update"), folderdata.strUpdateTime);
				}
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePad::UpdateFolderXml(FolderSaveData origindata, FolderSaveData updatedata)
{
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		if (markUp.FindElem(_T("bin")))
		{
			markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{
				if (_ttoi(markUp.GetAttrib(_T("seq"))) == origindata.nFolderSequence)
				{
					markUp.SetAttrib(_T("seq"), updatedata.nFolderSequence);
					markUp.SetAttrib(_T("name"), updatedata.strFolderName);
					markUp.SetAttrib(_T("tagcolor"), GetIndexFromTagColor(updatedata.folderTagColor));
					markUp.SetAttrib(_T("size"), updatedata.nSize);
					markUp.SetAttrib(_T("update"), updatedata.strUpdateTime);
				}
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePad::CreateFolderXml(FolderSaveData folderdata)
{
	CMarkup markUp;
	CString strFullPath = _T("");
	CustomXml::CreateConfigFile(strFullPath);
	strFullPath += _T("\\NotePad.conf");
	if (CustomXml::LoadConfigXml(&markUp, strFullPath))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();
		markUp.FindElem(_T("bin"));
		markUp.IntoElem();

		markUp.AddElem(_T("folder"));
		markUp.AddAttrib(_T("seq"), folderdata.nFolderSequence);
		markUp.AddAttrib(_T("name"), folderdata.strFolderName);
		markUp.AddAttrib(_T("tagcolor"), GetIndexFromTagColor(folderdata.folderTagColor));
		markUp.AddAttrib(_T("size"), folderdata.nSize);
		markUp.AddAttrib(_T("create"), folderdata.strCreateTime);
		markUp.AddAttrib(_T("update"), folderdata.strUpdateTime);
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

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


	notepadlist = new NotePadList(currentTheme, this);
	notepadlist->Create(IDD_DIALOG_NOTEPAD_LIST, &m_stt_notepad_list);
	notepadlist->MoveWindow(0, 0, notepadlistRect.Width(), notepadlistRect.Height());
	notepadlist->ShowWindow(SW_SHOW);

	folderlist = new FolderList(currentTheme, this);
	folderlist->Create(IDD_DIALOG_FOLDER_LIST, &m_stt_folderlist);
	folderlist->MoveWindow(0, 0, folderlistRect.Width(), folderlistRect.Height());
	folderlist->ShowWindow(SW_SHOW);


	LoadNotePad();
	SetLatelyNote(strLatelyNoteContent);
	otherNoteList = allNoteList.at(0);

	if (recycleNoteList.empty() && recycleFolderList.empty())
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

	notepadlist->LoadNotePad(allNoteList);
	folderlist->LoadFolder(allFolderList);

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

COLORREF NotePad::GetTagColorFromIndex(int nIndex)
{
	if (nIndex == 1) return TAG_COLOR_1;
	else if (nIndex == 2) return TAG_COLOR_2;
	else if (nIndex == 3) return TAG_COLOR_3;
	else if (nIndex == 4) return TAG_COLOR_4;
	else if (nIndex == 5) return TAG_COLOR_5;
	else if (nIndex == 6) return TAG_COLOR_6;
	else if (nIndex == 7) return TAG_COLOR_7;

	return NULL;
}

int NotePad::GetIndexFromTagColor(COLORREF tagcolor)
{
	if (tagcolor == TAG_COLOR_1) return 1;
	else if (tagcolor == TAG_COLOR_2) return 2;
	else if (tagcolor == TAG_COLOR_3) return 3;
	else if (tagcolor == TAG_COLOR_4) return 4;
	else if (tagcolor == TAG_COLOR_5) return 5;
	else if (tagcolor == TAG_COLOR_6) return 6;
	else if (tagcolor == TAG_COLOR_7) return 7;

	return 0;
}

CTime NotePad::GetTimeCal(CString strTime)
{
	CString strYear, strMonth, strDay, strHour, strMinute, strSecond;

	AfxExtractSubString(strYear, strTime, 0, '-');
	AfxExtractSubString(strMonth, strTime, 1, '-');
	AfxExtractSubString(strDay, strTime, 2, '-');
	AfxExtractSubString(strHour, strTime, 3, '-');
	AfxExtractSubString(strMinute, strTime, 4, '-');
	AfxExtractSubString(strSecond, strTime, 5, '-');

	CTime returnTime(_ttoi(strYear), _ttoi(strMonth), _ttoi(strDay), _ttoi(strHour), _ttoi(strMinute), _ttoi(strSecond));

	return returnTime;
}

CString NotePad::GetTimeCal(CTime calTime)
{
	CString strReturnTime;
	strReturnTime.Format(_T("%04d-%02d-%02d-%02d-%02d-%02d"), calTime.GetYear(), calTime.GetMonth(), calTime.GetDay(), calTime.GetHour(), calTime.GetMinute(), calTime.GetSecond());

	return strReturnTime;
}

void NotePad::LoadNotePad()
{
	bool bSavedXml = false;
	CMarkup markUp;
	CString szRoot = _T("");
	CustomXml::CreateConfigFile(szRoot);
	szRoot += _T("\\NotePad.conf");

	CTime compareUpdateNoteTime;
	if (CustomXml::LoadConfigXml(&markUp, szRoot))
	{
		markUp.FindElem(_T("NotePad"));
		markUp.IntoElem();

		if (markUp.FindElem(_T("bin")))
		{
			markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{
				CString strFolderSequence = markUp.GetAttrib(_T("seq"));
				CString strFolderName = markUp.GetAttrib(_T("name"));
				CString strTagColor = markUp.GetAttrib(_T("tagcolor"));
				CString strFolderSize = markUp.GetAttrib(_T("size"));
				CString strFolderCreateTime = markUp.GetAttrib(_T("create"));
				CString strFolderUpdateTime = markUp.GetAttrib(_T("update"));

				CTime createFolderTime = GetTimeCal(strFolderCreateTime);
				CTime updateFolderTime = GetTimeCal(strFolderUpdateTime);

				int nFolderColorIndex = _ttoi(strTagColor);
				COLORREF folderColor = GetTagColorFromIndex(nFolderColorIndex);
				int nFolderSequence = _ttoi(strFolderSequence);
				int nFolderSize = _ttoi(strFolderSize);

			
				/* folderseq 가 0 이면 other폴더
				* 그외엔 생성폴더
				* 총합이 all폴더
				*/
				markUp.IntoElem();
				ViewNoteList allocFolder;
				while (markUp.FindElem(_T("note")))
				{
					CString strNotePath;
					CString strNoteName = markUp.GetAttrib(_T("name"));
					CString strLocked = markUp.GetAttrib(_T("lock"));
					CString strNoteCreateTime = markUp.GetAttrib(_T("create"));
					CString strNoteUpdateTime = markUp.GetAttrib(_T("update"));

					CTime createNoteTime = GetTimeCal(strNoteCreateTime);
					CTime updateNoteTime = GetTimeCal(strNoteUpdateTime);

					

					int nLocked = _ttoi(strLocked);
					if (nLocked <= 0) nLocked = 0;
					else nLocked = 1;
					bool bLocked = (bool)nLocked;

					CustomXml::GetModulePath(strNotePath);
					strNotePath += (_T("\\Note\\") + strFolderSequence + strNoteName + _T(".txt"));

					NoteFile file;
					CString strNoteContent = _T("");
					if (file.NoteRead(strNotePath, strNoteContent))
					{
						NoteItem* newNote = new NoteItem(currentTheme, notepadlist);
						NoteItem::NoteInit noteinit;
						noteinit.nNoteName = _ttoi(strNoteName);
						noteinit.nFolderSequence = nFolderSequence;
						noteinit.strNoteContent = strNoteContent;
						noteinit.tagColor = folderColor;
						noteinit.isLock = bLocked;
						noteinit.nFolderSize = nFolderSize;
						noteinit.createTime = createNoteTime;
						noteinit.updateTime = updateNoteTime;

						if (updateNoteTime > compareUpdateNoteTime)
						{
							strLatelyNoteContent = noteinit.strNoteContent;
						}

						newNote->Initialize(noteinit);
						
						allocFolder.push_back(newNote);
					}
					else
					{
						AfxMessageBox(_T("노트정보를 읽지 못하였습니다."));
					}
				}
				markUp.OutOfElem();
				allNoteList.push_back(allocFolder);

				// 여기에 FolderItem 할당
				FolderItem0* newFolder = new FolderItem0(currentTheme, folderlist);
				FolderItem0::FolderInit folderinit;
				folderinit.strFolderName = strFolderName;
				folderinit.nFolderSequence = nFolderSequence;
				folderinit.nFolderSize = nFolderSize;
				folderinit.nFolderColorIndex = nFolderColorIndex;
				folderinit.folder = allocFolder;
				folderinit.createTime = createFolderTime;
				folderinit.updateTime = updateFolderTime;

				newFolder->Initialize(folderinit);

				allFolderList.push_back(newFolder);
			}
		}

		if (markUp.FindElem(_T("recy")))
		{
			/*markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{

			}*/
		}
	}
	else
	{
		CString strFullPath = _T("");
		CustomXml::GetModulePath(strFullPath);
		CustomXml::CreateDefaultDirectory(strFullPath, _T("\\Note"));
		if (CreateDefaultNoteXml(&markUp, szRoot)) bSavedXml = true;
		if (bSavedXml)
		{
			CustomXml::SaveXml(&markUp, szRoot);
		}
	}
}

void NotePad::LoadAllNote()
{
	notepadlist->LoadNotePad(allNoteList);
}

void NotePad::LoadOtherNote()
{
	std::vector<ViewNoteList> allocnotelist;  
	allocnotelist.push_back(otherNoteList); 
	notepadlist->LoadNotePad(allocnotelist); 
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
	for (int i = 0; i < (int)allFolderList.size(); i++)
	{
		FolderItem0* targetFolder = allFolderList.at(i);
		if (targetFolder == folderlist->downFolder)
		{
			targetFolder->folderButton->ToggleClickChange();
			folderlist->downFolder = nullptr;
			folderlist->undoFolder = nullptr;
		}
	}
}


void NotePad::OnBnClickedButtonOtherNotefolder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoadOtherNote();
	for (int i = 0; i < (int)allFolderList.size(); i++)
	{
		FolderItem0* targetFolder = allFolderList.at(i);
		if (targetFolder == folderlist->downFolder)
		{
			targetFolder->folderButton->ToggleClickChange();
			folderlist->downFolder = nullptr;
			folderlist->undoFolder = nullptr;
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
		folderinit.nFolderSequence = (int)allFolderList.size();
		folderinit.nFolderSize = 0;
		folderinit.nFolderColorIndex = GetIndexFromTagColor(createTagColor);
		folderinit.folder = { };
		folderinit.createTime = CTime::GetCurrentTime();
		folderinit.updateTime = folderinit.createTime;

		FolderSaveData folderdata;
		folderdata.strFolderName = strCreateFolderName;
		folderdata.folderTagColor = createTagColor;
		folderdata.nFolderSequence = (int)allFolderList.size();
		folderdata.nSize = 0;
		folderdata.strCreateTime = GetTimeCal(folderinit.createTime);
		folderdata.strUpdateTime = folderdata.strCreateTime;

		CreateFolderXml(folderdata);

		newFolder->Initialize(folderinit);
		allFolderList.push_back(newFolder);
		allNoteList.push_back({});
		notepadlist->viewNoteList.push_back({});
		notepadlist->baseViewNoteList.push_back({});
		folderlist->LoadFolder(allFolderList);
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

void NotePad::UpdateAllNoteVector(ViewNoteList updateNoteList, int nUpdateIndex)
{
	std::vector<ViewNoteList> newAllocNoteList;
	for (int i = 0; i < nUpdateIndex; i++)
	{
		newAllocNoteList.push_back(allNoteList.at(i));
	}
	newAllocNoteList.push_back(updateNoteList);
	for (int i = (int)newAllocNoteList.size(); i < (int)allNoteList.size(); i++)
	{
		newAllocNoteList.push_back(allNoteList.at(i));
	}
	allNoteList.assign(newAllocNoteList.begin(), newAllocNoteList.end());

	if (nUpdateIndex == 0) otherNoteList = updateNoteList;	// 만약 업데이트 인덱스가 0번(기타)일 경우 other벡터도 업데이트
}

void NotePad::UpdateAllFolderVector(FolderItem0* updateFolder, int nUpdateIndex)
{
	ViewFolderList newAllocFolderList;
	for (int i = 0; i < nUpdateIndex; i++)
	{
		newAllocFolderList.push_back(allFolderList.at(i));
	}
	newAllocFolderList.push_back(updateFolder);
	for (int i = (int)newAllocFolderList.size(); i < (int)allFolderList.size(); i++)
	{
		newAllocFolderList.push_back(allFolderList.at(i));
	}
	allFolderList.assign(newAllocFolderList.begin(), newAllocFolderList.end());
}

void NotePad::OnBnClickedButtonNotepadTrash()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NotePadRecycle recycle(currentTheme, this);
	if (recycle.DoModal() == IDOK)
	{

	}
}
