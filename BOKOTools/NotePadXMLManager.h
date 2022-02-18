#pragma once
#include "NoteItem.h"
#include "FolderItem.h"
#include "CustomXml.h"
#include "NoteFile.h"

class NotePadManager;

class NotePadList;
class FolderList;
class NotePadRecycle;

class NotePadXMLManager
{
	friend class NotePadManager;
	typedef NotePadContainer<NoteItem*> Folder, ViewNoteList;
public:

	NotePadXMLManager(ThemeData* currentTheme, NotePadManager* pManager);
	~NotePadXMLManager();

	struct NoteSaveData
	{
		CString strUpdateTime;
		CString strCreateTime;
		int nNoteName;
		int nLock;
		int nFolderSequence;
	};

	struct FolderSaveData
	{
		CString strUpdateTime;
		CString strCreateTime;
		CString strFolderName;
		COLORREF folderTagColor;
		Folder folder;
		int nFolderSequence;
		int nSize;
	};

private:


	ThemeData* currentTheme;
	NotePadManager* pManager;
	NotePadList* pNotePadList;
	FolderList* pFolderList;
	NotePadRecycle* pRecycleDlg;

	void Init(NotePadList* pNotePadList, FolderList* pFolderList, NotePadRecycle* pRecycleDlg);
	void LoadNotePad();
	void RecycleNoteXml(NoteSaveData origindata);
	void RecycleFolderXml(FolderSaveData origindata);
	void SaveNoteXml(NoteSaveData notedata);
	void UpdateNoteXml(NoteSaveData origindata, NoteSaveData updatedata);
	void CreateNoteXml(NoteSaveData notedata);
	void SaveFolderXml(FolderSaveData folderdata);
	void UpdateFolderXml(FolderSaveData origindata, FolderSaveData updatedata);
	void CreateFolderXml(FolderSaveData folderdata);
	bool CreateDefaultNoteXml(CMarkup* markUp, CString strFullPath);
};