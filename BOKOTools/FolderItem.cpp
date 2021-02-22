#include "pch.h"
#include "FolderItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW 
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static unsigned int s_ButtonID = 75000;

FolderItem0::FolderItem0(ThemeData* currentTheme, CWnd* pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;

	folderButton = new CGdipButton;
	folderStatic = new CalculateStatic;
	strFolderName = _T("");
	nFolderSize = 0;
	nFolderSequence = 0;
	nFolderColorIndex = 0;
	folderRect = { 0, 0, 64, 84 };
}

FolderItem0::~FolderItem0()
{
	if (folderButton)
	{
		folderButton->DestroyWindow();
		delete folderButton;
		folderButton = nullptr;
	}

	if (folderStatic)
	{
		folderStatic->DestroyWindow();
		delete folderStatic;
		folderStatic = nullptr;
	}
}

void FolderItem0::Initialize(FolderInit init)
{
	ExecuteFolderInitData(init);

	// button create
	folderButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), pParent, s_ButtonID++);
	folderStatic->Create(_T(""), SS_CENTER, CRect(0 ,0 ,0, 0), pParent, s_ButtonID++);

	// button initialize
	FolderImageInit(nFolderColorIndex, nFolderSize);
	folderButton->EnableToggle();
	folderButton->strButtonName = strFolderName;
	folderStatic->Initialize(15, currentTheme->GetThemeFontName());

	// button sizing
	folderButton->MoveWindow(0, 0, 64, 64);
	folderStatic->MoveWindow(0, 0, 64, 20);

	ShowWindow(false);
}

void FolderItem0::FolderImageInit(int nFolderColorIndex, int nFolderSize)
{
	folderButton->DisConnect();
	folderButton->DeleteImage();
	if (nFolderSize > 0)	// 폴더가 차있을때
	{
		if (nFolderColorIndex == 1)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_1_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_1_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_1_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 2)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_2_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_2_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_2_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 3)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_3_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_3_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_3_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 4)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_4_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_4_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_4_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 5)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_5_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_5_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_5_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 6)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_6_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_6_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_6_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 7)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_7_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_7_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_FULL_COLORINDEX_7_CLICK, _T("PNG"));
		}
	}
	else // 폴더가 비어있을때
	{
		if (nFolderColorIndex == 1)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_1_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_1_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_1_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 2)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_2_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_2_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_2_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 3)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_3_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_3_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_3_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 4)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_4_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_4_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_4_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 5)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_5_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_5_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_5_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 6)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_6_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_6_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_6_CLICK, _T("PNG"));
		}
		else if (nFolderColorIndex == 7)
		{
			folderButton->LoadStdImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_7_NOMAL, _T("PNG"));
			folderButton->LoadHovImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_7_HOVER, _T("PNG"));
			folderButton->LoadAltImage(IDB_PNG_NOTEPAD_EMPTY_COLORINDEX_7_CLICK, _T("PNG"));
		}
	}
}

void FolderItem0::MoveWindow(int nLeft, int nTop)
{
	folderButton->SetWindowPos(NULL, nLeft, nTop, 0, 0, SWP_NOSIZE);
	folderStatic->SetWindowPos(NULL, nLeft, nTop + 64, 0, 0, SWP_NOSIZE);
	folderRect.left = nLeft;
	folderRect.top = nTop;
	folderRect.right = nLeft + 64;
	folderRect.bottom = nTop + 84;
}

void FolderItem0::ShowWindow(bool isShow)
{
	folderButton->ShowWindow(isShow ? SW_SHOW : SW_HIDE);
	folderStatic->ShowWindow(isShow ? SW_SHOW : SW_HIDE);
}

void FolderItem0::Update(FolderInit init)
{
	ExecuteFolderInitData(init);
	FolderImageInit(init.nFolderColorIndex, init.nFolderSize);
	folderStatic->SetWindowTextW(init.strFolderName);
}

void FolderItem0::ExecuteFolderInitData(FolderInit init)
{
	this->strFolderName = init.strFolderName;
	this->nFolderSize = init.nFolderSize;
	this->nFolderSequence = init.nFolderSequence;
	this->folder = init.folder;
	this->nFolderColorIndex = init.nFolderColorIndex;
	this->createTime = init.createTime;
	this->updateTime = init.updateTime;
}

void FolderItem0::SetFolderName(CString strFolderName)
{
	this->strFolderName = strFolderName;
}

void FolderItem0::SetFolderSize(int nFolderSize)
{
	this->nFolderSize = nFolderSize;
}

void FolderItem0::SetFolderSequence(int nFolderSequence)
{
	this->nFolderSequence = nFolderSequence;
}

void FolderItem0::SetFolderColorIndex(int nFolderColorIndex)
{
	this->nFolderColorIndex = nFolderColorIndex;
}

void FolderItem0::SetFolder(FolderItem0::Folder folder)
{
	this->folder = folder;
}

void FolderItem0::SetCreateTime(CTime createTime)
{
	this->createTime = createTime;
}

void FolderItem0::SetUpdateTime(CTime updateTime)
{
	this->updateTime = updateTime;
}

CString FolderItem0::GetFolderName()
{
	return strFolderName;
}

int FolderItem0::GetFolderSize()
{
	return nFolderSize;
}

int FolderItem0::GetFolderSequence()
{
	return nFolderSequence;
}

int FolderItem0::GetFolderColorIndex()
{
	return nFolderColorIndex;
}

CRect FolderItem0::GetFolderRect()
{
	return folderRect;
}

FolderItem0::Folder FolderItem0::GetFolder()
{
	return folder;
}

CTime FolderItem0::GetCreateTime()
{
	return createTime;
}

CTime FolderItem0::GetUpdateTime()
{
	return updateTime;
}