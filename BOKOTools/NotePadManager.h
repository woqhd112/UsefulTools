#pragma once
#include "NotePadXMLManager.h"

#define TAG_COLOR_1	RGB(245, 85, 79)
#define TAG_COLOR_2	RGB(252, 184, 74)
#define TAG_COLOR_3	RGB(115, 215, 108)
#define TAG_COLOR_4	RGB(131, 94, 224)
#define TAG_COLOR_5	RGB(160, 160, 160)
#define TAG_COLOR_6	RGB(224, 153, 94)
#define TAG_COLOR_7	RGB(94, 165, 224)

class NotePadList;
class FolderList;
class NotePadRecycle;

class NotePadManager
{
	friend class NotePadXMLManager;
	//typedef std::vector<NoteItem*> ViewNoteList;
	//typedef std::vector<FolderItem0*> ViewFolderList;
	typedef NotePadContainer<NoteItem*> ViewNoteList;
	typedef NotePadContainer<FolderItem0*> ViewFolderList;

public:

	NotePadManager(ThemeData* currentTheme);
	~NotePadManager();


private:

	ThemeData* currentTheme;
	

	NotePadXMLManager* xmlManager;

	CString strLatelyNoteContent;

	bool bInit;

private:


public:

	enum FolderViewState
	{
		NOTE_VIEW_ALL = 0,
		NOTE_VIEW_OTHER = 1,
		NOTE_VIEW_FOLDER = 2
	};

	NotePadContainer<ViewNoteList> m_allNoteList;
	NotePadContainer<ViewNoteList> m_viewNoteList;
	ViewNoteList m_otherNoteList;
	ViewFolderList m_allFolderList;

	ViewNoteList m_recycleNoteList;
	ViewFolderList m_recycleFolderList;

	FolderViewState viewState;

	void Init(NotePadList* pNotePadList, FolderList* pFolderList, NotePadRecycle* pRecycleDlg);
	bool LoadNotePadData();

	void UpdateFolderVector(ViewNoteList updateNoteList, int nUpdateIndex);
	void UpdateViewNoteList(NotePadContainer<ViewNoteList> updateViewNoteList);
	void UpdateAllNoteVector(ViewNoteList updateNoteList, int nUpdateIndex);
	void UpdateAllFolderVector(FolderItem0* updateFolder, int nUpdateIndex);
	void UpdateRecycleNoteVector(NoteItem* updateNote, int nUpdateIndex);

	void SetNoteView(NotePadContainer<ViewNoteList> viewNoteList ,FolderViewState viewState);

	void AddFolder(FolderItem0* newFolder);
	void AddNote(NoteItem* newNote);
	void UpdateNoteSwap(ViewNoteList& variableNoteList, NoteItem* findNote, int nFindVariableFolderSequence);
	ViewNoteList FolderChange(ViewNoteList& variableNoteList, NoteItem* findNote, int nFindVariableFolderSequence, int nSelectVariableFolderSequence);
	void RecycleNote(ViewNoteList& variableNoteList, NoteItem* findNote, int nFindVariableFolderSequence);

	int MaxFolderSequence();
	CString GetLatleyNoteContent();
	COLORREF GetTagColorFromIndex(int nIndex);
	int GetIndexFromTagColor(COLORREF tagcolor);
	CTime GetTimeCal(CString strTime);
	CString GetTimeCal(CTime calTime);
	int EraseNoteList(ViewNoteList& variableNoteList, NoteItem* findNote);

	// m_allNoteList, m_viewNoteList, m_otherNoteList, m_allFolderList 모두 erase 되었는지 확인 후 사용
	NoteItem* NoteByRecycleParentSwap(NoteItem* updateNote);
	NoteItem* RecycleByNoteParentSwap(NoteItem* updateNote);

	void CreateFolderXml(NotePadXMLManager::FolderSaveData folderdata);
	void UpdateFolderXml(NotePadXMLManager::FolderSaveData origindata, NotePadXMLManager::FolderSaveData updatedata);
	void SaveFolderXml(NotePadXMLManager::FolderSaveData folderdata);
	void CreateNoteXml(NotePadXMLManager::NoteSaveData notedata);
	void SaveNoteXml(NotePadXMLManager::NoteSaveData notedata);
	void UpdateNoteXml(NotePadXMLManager::NoteSaveData origindata, NotePadXMLManager::NoteSaveData updatedata);
	void RecycleNoteXml(NotePadXMLManager::NoteSaveData origindata);

private:


public:

	//struct NoteSaveData
	//{
	//	CString strUpdateTime;
	//	CString strCreateTime;
	//	int nNoteName;
	//	int nLock;
	//	int nFolderSequence;
	//};

	//struct FolderSaveData
	//{
	//	CString strUpdateTime;
	//	CString strCreateTime;
	//	CString strFolderName;
	//	COLORREF folderTagColor;
	//	int nFolderSequence;
	//	int nSize;
	//};

	//void RecycleNoteXml(NoteSaveData origindata);
	//void SaveNoteXml(NoteSaveData notedata);
	//void UpdateNoteXml(NoteSaveData origindata, NoteSaveData updatedata);
	//void CreateNoteXml(NoteSaveData notedata);
	//void SaveFolderXml(FolderSaveData folderdata);
	//void UpdateFolderXml(FolderSaveData origindata, FolderSaveData updatedata);


};
