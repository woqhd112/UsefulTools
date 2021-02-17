#include "pch.h"
#include "NoteItem.h"

static unsigned int n_ButtonID = 70000;

NoteItem::NoteItem()
{

}

NoteItem::NoteItem(ThemeData* currentTheme, CWnd* pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;

	lockButton = new CGdipButton;
	noteButton = new CalculateButton;
	tagButton = new CalculateButton;
	wrapButton = new CalculateButton;
	strNoteTitle = _T("");
	strNoteContent = _T("");
	nNoteName = 0;
	nFolderSize = 0;
	nFolderSequence = 0;
	isLock = false;
	noteRect = { 0, 0, 365, 40 };
	isCreating = false;
}

NoteItem::~NoteItem()
{
	if (noteButton)
	{
		noteButton->DestroyWindow();
		delete noteButton;
		noteButton = nullptr;
	}

	if (lockButton)
	{
		lockButton->DestroyWindow();
		delete lockButton;
		lockButton = nullptr;
	}

	if (tagButton)
	{
		lockButton->DestroyWindow();
		delete lockButton;
		lockButton = nullptr;
	}

	if (wrapButton)
	{
		lockButton->DestroyWindow();
		delete lockButton;
		lockButton = nullptr;
	}
}

void NoteItem::Initialize(NoteInit init)
{
	ExecuteNoteInitData(init);

	// button create
	wrapButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), pParent, n_ButtonID++);
	lockButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), wrapButton, n_ButtonID++);
	noteButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), wrapButton, n_ButtonID++);
	tagButton->Create(_T(""), BS_PUSHBUTTON | BS_CENTER, CRect(0, 0, 0, 0), wrapButton, n_ButtonID++);

	// button initialize
	wrapButton->Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 15);
	wrapButton->m_bUseMouseBkGroundColorEvent = false;
	lockButton->LoadStdImage(IDB_PNG_NOTELIST_LOCK, _T("PNG"));
	lockButton->LoadHovImage(IDB_PNG_NOTELIST_LOCK, _T("PNG"));
	lockButton->LoadAltImage(IDB_PNG_NOTELIST_LOCK, _T("PNG"));
	noteButton->Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 25);
	noteButton->SetWindowTextW(strNoteTitle);
	tagButton->Initialize(init.tagColor, CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, currentTheme->GetThemeFontName(), 20);

	// button sizing
	wrapButton->MoveWindow(0, 0, 365, 40);
	tagButton->MoveWindow(0, 0, 20, 40);
	lockButton->MoveWindow(20, 10, 20, 20);
	noteButton->MoveWindow(40, 5, 320, 30);

	// button z-order
	/*wrapButton->ModifyStyle(0, WS_CLIPSIBLINGS, 0);
	tagButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	lockButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	noteButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	tagButton->BringWindowToTop();
	lockButton->BringWindowToTop();
	noteButton->BringWindowToTop();*/

	// button show
	ShowWindow(false);
	//lockButton->ShowWindow(SW_HIDE);
	isCreating = true;
}

bool NoteItem::IsCreating()
{
	return isCreating;
}

void NoteItem::MoveWindow(int nLeft, int nTop)
{
	wrapButton->SetWindowPos(NULL, nLeft, nTop, 0, 0, SWP_NOSIZE);
	//tagButton->SetWindowPos(NULL, nLeft, nTop, 0, 0, SWP_NOSIZE);
	//lockButton->SetWindowPos(NULL, nLeft + 30, nTop + 10, 0, 0, SWP_NOSIZE);
	//noteButton->SetWindowPos(NULL, nLeft + 60, nTop + 5, 0, 0, SWP_NOSIZE);
	noteRect.left = nLeft;
	noteRect.top = nTop;
	noteRect.right = nLeft + 365;
	noteRect.bottom = nTop + 40;
}

void NoteItem::ShowWindow(bool isShow)
{
	wrapButton->ShowWindow(isShow ? SW_SHOW : SW_HIDE);
	tagButton->ShowWindow(isShow ? SW_SHOW : SW_HIDE);
	lockButton->ShowWindow(isShow ? SW_SHOW : SW_HIDE);
	noteButton->ShowWindow(isShow ? SW_SHOW : SW_HIDE);
}

void NoteItem::ShowLock(bool isShow)
{
	lockButton->ShowWindow(isShow ? SW_SHOW : SW_HIDE);
}

void NoteItem::ExecuteNoteInitData(NoteInit init)
{
	strNoteContent = init.strNoteContent;
	strNoteTitle = strNoteContent.Left(18);
	tagColor = init.tagColor;
	nNoteName = init.nNoteName;
	nFolderSize = init.nFolderSize;
	isLock = init.isLock;
	nFolderSequence = init.nFolderSequence;
}

void NoteItem::Update(NoteInit init)
{
	ExecuteNoteInitData(init);
	tagButton->SetFaceColor(init.tagColor);
	noteButton->SetWindowTextW(init.strNoteContent.Left(18));
	ShowLock(init.isLock);
}

void NoteItem::SetNoteContent(CString strNoteContent)
{
	this->strNoteContent = strNoteContent;
	this->strNoteTitle = strNoteContent.Left(18);
	noteButton->SetWindowTextW(strNoteTitle);
}

void NoteItem::SetTagColor(COLORREF tagColor)
{
	this->tagColor = tagColor;
}

void NoteItem::SetFolderSize(int nFolderSize)
{
	this->nFolderSize = nFolderSize;
}

void NoteItem::SetLockSetting(bool isLock)
{
	this->isLock = isLock;
}

void NoteItem::SetFolderSequence(int nFolderSequence)
{
	this->nFolderSequence = nFolderSequence;
}

void NoteItem::SetNoteName(int nNoteName)
{
	this->nNoteName = nNoteName;
}

void NoteItem::SetNoteTagSequence(int nNoteSequnece)
{
	CString strNoteSequence;
	strNoteSequence.Format(_T("%d"), nNoteSequnece);
	SetNoteTagSequence(strNoteSequence);
}

void NoteItem::SetNoteTagSequence(CString strNoteSequnece)
{
	tagButton->SetWindowTextW(strNoteSequnece);
}

CString NoteItem::GetNoteTagSequence()
{
	CString strFindNoteSequence;
	tagButton->GetWindowTextW(strFindNoteSequence);
	return strFindNoteSequence;
}

int NoteItem::GetFolderSequence()
{
	return nFolderSequence;
}

bool NoteItem::IsLock()
{
	return isLock;
}

int NoteItem::GetFolderSize()
{
	return nFolderSize;
}

COLORREF NoteItem::GetTagColor()
{
	return tagColor;
}

CString NoteItem::GetNoteTitle()
{
	return strNoteTitle;
}

CString NoteItem::GetNoteContent()
{
	return strNoteContent;
}

CRect NoteItem::GetNoteRect()
{
	return noteRect;
}

int NoteItem::GetNoteName()
{
	return nNoteName;
}