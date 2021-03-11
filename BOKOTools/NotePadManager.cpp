#include "pch.h"
#include "NotePadManager.h"
#include "NotePadList.h"
#include "FolderList.h"
#include "NotePadRecycle.h"


NotePadManager::NotePadManager(ThemeData* currentTheme)
{
	this->currentTheme = currentTheme;
	bInit = false;
	strLatelyNoteContent = _T("");
	viewState = NOTE_VIEW_ALL;

}

NotePadManager::~NotePadManager()
{
	for (int i = 0; i < m_allNoteList.Size(); i++)
	{
		ViewNoteList deleteNoteList = m_allNoteList.At(i);
		for (int j = 0; j < deleteNoteList.Size(); j++)
		{
			NoteItem* deleteNote = deleteNoteList.At(j);
			delete deleteNote;
			deleteNote = nullptr;
		}
		deleteNoteList.Clear();
	}
	m_otherNoteList.Clear();
	m_allNoteList.Clear();

	for (int i = 0; i < m_allFolderList.Size(); i++)
	{
		FolderItem0* deleteFolder = m_allFolderList.At(i);
		delete deleteFolder;
		deleteFolder = nullptr;
	}
	m_allFolderList.Clear();

	for (int i = 0; i < m_recycleNoteList.Size(); i++)
	{
		NoteItem* deleteNote = m_recycleNoteList.At(i);
		delete deleteNote;
		deleteNote = nullptr;
	}
	m_recycleNoteList.Clear();

	for (int i = 0; i < (int)m_recycleFolderList.Size(); i++)
	{
		FolderItem0* deleteFolder = m_recycleFolderList.At(i);
		ViewNoteList deleteNoteList = deleteFolder->GetFolder();
		for (int j = 0; j < deleteNoteList.Size(); j++)
		{
			NoteItem* deleteNote = deleteNoteList.At(j);
			delete deleteNote;
			deleteNote = nullptr;
		}
		deleteNoteList.Clear();

		delete deleteFolder;
		deleteFolder = nullptr;
	}
	m_recycleFolderList.Clear();

	delete xmlManager;
	xmlManager = nullptr;
}

void NotePadManager::Init(NotePadList* pNotePadList, FolderList* pFolderList, NotePadRecycle* pRecycleDlg)
{
	bInit = true;
	xmlManager = new NotePadXMLManager(currentTheme, this);
	xmlManager->Init(pNotePadList, pFolderList, pRecycleDlg);
}

bool NotePadManager::LoadNotePadData()
{
	if (!bInit) return false;

	xmlManager->LoadNotePad();
	

	m_otherNoteList = m_allNoteList.At(0);

	return true;
}

void NotePadManager::UpdateViewNoteList(NotePadContainer<ViewNoteList> updateViewNoteList)
{
	m_viewNoteList = updateViewNoteList;
}

void NotePadManager::AddFolder(FolderItem0* newFolder)
{
	m_allFolderList.Push(newFolder);
	m_allNoteList.Push({});
	m_viewNoteList = {};
}

void NotePadManager::AddNote(NoteItem* newNote)
{
	if (m_viewNoteList.At(0) == m_otherNoteList)
	{
		m_viewNoteList.At(0).Push(newNote);
	}

	m_otherNoteList.Push(newNote);
	m_allNoteList.At(0) = m_otherNoteList;
}

void NotePadManager::UpdateNoteSwap(ViewNoteList& variableNoteList, NoteItem* findNote, int nFindVariableFolderSequence)
{
	// 스왑한 노트정보를 현재 상속된 폴더에 업데이트한다.
	UpdateFolderVector(variableNoteList, nFindVariableFolderSequence);

	// 스왑한 노트정보를 notepad에 있는 전체폴더에 업데이트한다.
	UpdateAllNoteVector(variableNoteList, nFindVariableFolderSequence);

	// 업데이트한 노트정보를 메모장에 업데이트한다.
	CString strFullPath = _T("");
	NoteFile updateNoteContentFile;
	CustomXml::GetModulePath(strFullPath);
	strFullPath += _T("\\Note");
	for (int i = 0; i < variableNoteList.Size(); i++)
	{
		bool bUpdateNote = false;
		NoteItem* saveNote = variableNoteList.At(i);
		if (saveNote == findNote)
		{
			bUpdateNote = true;
		}

		saveNote->SetNoteName(i);

		CString strNoteName;
		strNoteName.Format(_T("%s\\%d%d.txt"), strFullPath, saveNote->GetFolderSequence(), i);
		updateNoteContentFile.NoteWrite(strNoteName, saveNote->GetNoteContent());

		NotePadXMLManager::NoteSaveData updateNote;
		updateNote.nFolderSequence = saveNote->GetFolderSequence();
		updateNote.nLock = saveNote->IsLock();
		updateNote.nNoteName = saveNote->GetNoteName();
		updateNote.strCreateTime = GetTimeCal(saveNote->GetCreateTime());
		updateNote.strUpdateTime = GetTimeCal(bUpdateNote ? CTime::GetCurrentTime() : saveNote->GetUpdateTime());

		xmlManager->SaveNoteXml(updateNote);
	}
}

NotePadManager::ViewNoteList NotePadManager::FolderChange(ViewNoteList& variableNoteList, NoteItem* findNote, int nFindVariableFolderSequence, int nSelectVariableFolderSequence)
{
	// 현재 노트를 현재 폴더에서 지운다
	int nDeleteNoteIndex = EraseNoteList(variableNoteList, findNote);

	// 현재 폴더 갱신
	FolderItem0* updateFolder = m_allFolderList.At(nFindVariableFolderSequence);
	FolderItem0::FolderInit updateFolderInit;

	int nUpdateFolderSize = updateFolder->GetFolderSize() - 1;
	updateFolderInit.folder = variableNoteList;
	updateFolderInit.nFolderColorIndex = updateFolder->GetFolderColorIndex();
	updateFolderInit.nFolderSequence = updateFolder->GetFolderSequence();
	updateFolderInit.nFolderSize = nUpdateFolderSize;
	updateFolderInit.strFolderName = updateFolder->GetFolderName();
	updateFolder->Update(updateFolderInit);

	UpdateAllNoteVector(variableNoteList, nFindVariableFolderSequence);
	UpdateAllFolderVector(updateFolder, nFindVariableFolderSequence);


	// 현재 노트를 선택한 폴더에 추가한다
	ViewNoteList insertNoteList = m_allNoteList.At(nSelectVariableFolderSequence);
	FolderItem0* insertFolder = m_allFolderList.At(nSelectVariableFolderSequence);
	FolderItem0::FolderInit selectFolderInit;

	NoteItem::NoteInit updateinit;
	updateinit.isLock = findNote->IsLock();
	updateinit.nFolderSequence = nSelectVariableFolderSequence;
	updateinit.nFolderSize = insertNoteList.Size() + 1;
	updateinit.nNoteName = insertNoteList.Size();
	updateinit.strNoteContent = findNote->GetNoteContent();
	updateinit.tagColor = GetTagColorFromIndex(insertFolder->GetFolderColorIndex());
	updateinit.createTime = findNote->GetCreateTime();
	updateinit.updateTime = CTime::GetCurrentTime();
	findNote->Update(updateinit);

	// 선택 폴더 갱신
	insertNoteList.Push(findNote);
	int nSelectFolderSize = insertFolder->GetFolderSize() + 1;
	selectFolderInit.folder = insertNoteList;
	selectFolderInit.nFolderColorIndex = insertFolder->GetFolderColorIndex();
	selectFolderInit.nFolderSequence = insertFolder->GetFolderSequence();
	selectFolderInit.nFolderSize = nSelectFolderSize;
	selectFolderInit.strFolderName = insertFolder->GetFolderName();
	selectFolderInit.createTime = insertFolder->GetCreateTime();
	selectFolderInit.updateTime = updateinit.updateTime;
	insertFolder->Update(selectFolderInit);

	UpdateAllNoteVector(insertNoteList, nSelectVariableFolderSequence);
	UpdateAllFolderVector(insertFolder, nSelectVariableFolderSequence);

	// 업데이트한 노트정보를 xml에 저장한다.
	NotePadXMLManager::NoteSaveData originNoteData, updateNoteData;
	originNoteData.nFolderSequence = nFindVariableFolderSequence;
	originNoteData.nLock = updateinit.isLock;
	originNoteData.nNoteName = nDeleteNoteIndex;
	originNoteData.strCreateTime = _T("");
	originNoteData.strUpdateTime = _T("");

	updateNoteData.nFolderSequence = nSelectVariableFolderSequence;
	updateNoteData.nLock = updateinit.isLock;
	updateNoteData.nNoteName = updateinit.nNoteName;
	updateNoteData.strCreateTime = GetTimeCal(updateinit.createTime);
	updateNoteData.strUpdateTime = GetTimeCal(updateinit.updateTime);

	xmlManager->UpdateNoteXml(originNoteData, updateNoteData);

	NoteFile file;
	CString strFullPath;
	CustomXml::GetModulePath(strFullPath);
	strFullPath += _T("\\Note\\");
	// 업데이트한 노트이름으로 메모장이름을 변경한다.
	file.NoteRename(strFullPath, NoteFile::DEFAULT_NOTE, originNoteData.nFolderSequence, originNoteData.nNoteName, updateNoteData.nFolderSequence, updateNoteData.nNoteName);

	// 삭제된 폴더의 노트들의 이름을 정렬한다.
	for (int i = 0; i < variableNoteList.Size(); i++)
	{
		NoteItem* noteitem = variableNoteList.At(i);
		int nFolderSequence = noteitem->GetFolderSequence();
		file.NoteRename(strFullPath, NoteFile::DEFAULT_NOTE, nFolderSequence, noteitem->GetNoteName(), nFolderSequence, i);
	}

	return insertNoteList;
}

void NotePadManager::RecycleNote(ViewNoteList& variableNoteList, NoteItem* findNote, int nFindVariableFolderSequence)
{
	// 해당 노트를 폴더에서 지운다.
	int nDeleteNoteIndex = EraseNoteList(variableNoteList, findNote);
	
	// 해당 폴더를 업데이트한다.
	FolderItem0* updateFolder = m_allFolderList.At(nFindVariableFolderSequence);
	FolderItem0::FolderInit updateFolderInit;

	int nUpdateFolderSize = updateFolder->GetFolderSize() - 1;
	updateFolderInit.folder = variableNoteList;
	updateFolderInit.nFolderColorIndex = updateFolder->GetFolderColorIndex();
	updateFolderInit.nFolderSequence = updateFolder->GetFolderSequence();
	updateFolderInit.nFolderSize = nUpdateFolderSize;
	updateFolderInit.strFolderName = updateFolder->GetFolderName();
	updateFolder->Update(updateFolderInit);

	// 해당 노트를 xml에 업데이트한다.
	NotePadXMLManager::NoteSaveData recycleNoteData;
	recycleNoteData.nFolderSequence = findNote->GetFolderSequence();
	recycleNoteData.nLock = findNote->IsLock();
	recycleNoteData.nNoteName = findNote->GetNoteName();
	recycleNoteData.strCreateTime = GetTimeCal(findNote->GetCreateTime());
	recycleNoteData.strUpdateTime = GetTimeCal(findNote->GetUpdateTime());
	xmlManager->RecycleNoteXml(recycleNoteData);

	// 해당 노트의 파일 이름을 변경한다.
	NoteFile file;
	CString strFullPath;
	CustomXml::GetModulePath(strFullPath);
	strFullPath += _T("\\Note\\");
	// 업데이트한 노트이름으로 메모장이름을 변경한다.
	file.NoteRename(strFullPath, NoteFile::NOTE_BY_SINGLE_RECYCLE_NOTE, recycleNoteData.nFolderSequence, recycleNoteData.nNoteName, recycleNoteData.nFolderSequence, recycleNoteData.nNoteName);

	// 삭제된 메모의 폴더에서 메모이름을 정렬한다.
	for (int i = 0; i < variableNoteList.Size(); i++)
	{
		bool bUpdateNote = false;
		NoteItem* saveNote = variableNoteList.At(i);

		file.NoteRename(strFullPath, NoteFile::DEFAULT_NOTE, recycleNoteData.nFolderSequence, saveNote->GetNoteName(), recycleNoteData.nFolderSequence, i);

		saveNote->SetNoteName(i);

		NotePadXMLManager::NoteSaveData updateNote;
		updateNote.nFolderSequence = saveNote->GetFolderSequence();
		updateNote.nLock = saveNote->IsLock();
		updateNote.nNoteName = saveNote->GetNoteName();
		updateNote.strCreateTime = GetTimeCal(saveNote->GetCreateTime());
		updateNote.strUpdateTime = GetTimeCal(saveNote->GetUpdateTime());

		xmlManager->SaveNoteXml(updateNote);
	}

	UpdateAllNoteVector(variableNoteList, nFindVariableFolderSequence);
	UpdateAllFolderVector(updateFolder, nFindVariableFolderSequence);

	// 해당 노트를 쓰레기통에 추가한다.
	m_recycleNoteList.Push(NoteByRecycleParentSwap(findNote));

}

int NotePadManager::EraseNoteList(ViewNoteList& variableNoteList, NoteItem* findNote)
{
	int nDeleteNoteIndex = 0;
	for (int i = 0; i < variableNoteList.Size(); i++)
	{
		NoteItem* updateNote = variableNoteList.At(i);
		updateNote->SetFolderSize(updateNote->GetFolderSize() - 1);
		if (updateNote == findNote)
		{
			nDeleteNoteIndex = i;
			variableNoteList.Erase(i);
		}
	}
	return nDeleteNoteIndex;
}

void NotePadManager::SetNoteView(NotePadContainer<ViewNoteList> viewNoteList, FolderViewState viewState)
{
	this->m_viewNoteList = viewNoteList;
	this->viewState = viewState;
}

void NotePadManager::UpdateAllNoteVector(ViewNoteList updateNoteList, int nUpdateIndex)
{
	NotePadContainer<ViewNoteList> newAllocNoteList;
	for (int i = 0; i < nUpdateIndex; i++)
	{
		newAllocNoteList.Push(m_allNoteList.At(i));
	}
	newAllocNoteList.Push(updateNoteList);
	for (int i = newAllocNoteList.Size(); i < m_allNoteList.Size(); i++)
	{
		newAllocNoteList.Push(m_allNoteList.At(i));
	}
	m_allNoteList.Assign(newAllocNoteList, 0, newAllocNoteList.Size() - 1);

	if (nUpdateIndex == 0) m_otherNoteList = updateNoteList;	// 만약 업데이트 인덱스가 0번(기타)일 경우 other벡터도 업데이트
}


void NotePadManager::UpdateFolderVector(ViewNoteList updateNoteList, int nUpdateIndex)
{
	m_allFolderList.At(nUpdateIndex)->SetFolder(updateNoteList);
}


void NotePadManager::UpdateAllFolderVector(FolderItem0* updateFolder, int nUpdateIndex)
{
	ViewFolderList newAllocFolderList;
	for (int i = 0; i < nUpdateIndex; i++)
	{
		newAllocFolderList.Push(m_allFolderList.At(i));
	}
	newAllocFolderList.Push(updateFolder);
	for (int i = newAllocFolderList.Size(); i < m_allFolderList.Size(); i++)
	{
		newAllocFolderList.Push(m_allFolderList.At(i));
	}
	m_allFolderList.Assign(newAllocFolderList, 0, newAllocFolderList.Size() - 1);
}

void NotePadManager::UpdateRecycleNoteVector(NoteItem* updateNote, int nUpdateIndex)
{
	ViewNoteList newAllocNoteList;
	for (int i = 0; i < nUpdateIndex; i++)
	{
		newAllocNoteList.Push(m_recycleNoteList.At(i));
	}
	newAllocNoteList.Push(updateNote);
	for (int i = newAllocNoteList.Size(); i < m_recycleNoteList.Size(); i++)
	{
		newAllocNoteList.Push(m_recycleNoteList.At(i));
	}
	m_recycleNoteList.Assign(newAllocNoteList, 0, newAllocNoteList.Size() - 1);
}


NoteItem* NotePadManager::NoteByRecycleParentSwap(NoteItem* updateNote)
{
	NoteItem* newNote = new NoteItem(currentTheme, xmlManager->pRecycleDlg);
	NoteItem::NoteInit noteinit;
	noteinit.nNoteName = updateNote->GetNoteName();
	noteinit.nFolderSequence = updateNote->GetFolderSequence();
	noteinit.strNoteContent = updateNote->GetNoteContent();
	noteinit.tagColor = TAG_COLOR_5;
	noteinit.isLock = updateNote->IsLock();
	noteinit.nFolderSize = updateNote->GetFolderSize();
	noteinit.createTime = updateNote->GetCreateTime();
	noteinit.updateTime = updateNote->GetUpdateTime();

	newNote->Initialize(noteinit);

	return newNote;
}

NoteItem* NotePadManager::RecycleByNoteParentSwap(NoteItem* updateNote)
{
	NoteItem* newNote = new NoteItem(currentTheme, xmlManager->pNotePadList);
	NoteItem::NoteInit noteinit;
	noteinit.nNoteName = updateNote->GetNoteName();
	noteinit.nFolderSequence = updateNote->GetFolderSequence();
	noteinit.strNoteContent = updateNote->GetNoteContent();
	noteinit.tagColor = TAG_COLOR_5;
	noteinit.isLock = updateNote->IsLock();
	noteinit.nFolderSize = updateNote->GetFolderSize();
	noteinit.createTime = updateNote->GetCreateTime();
	noteinit.updateTime = updateNote->GetUpdateTime();

	newNote->Initialize(noteinit);

	return newNote;
}

COLORREF NotePadManager::GetTagColorFromIndex(int nIndex)
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

int NotePadManager::GetIndexFromTagColor(COLORREF tagcolor)
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

CTime NotePadManager::GetTimeCal(CString strTime) 
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

CString NotePadManager::GetTimeCal(CTime calTime)
{
	CString strReturnTime;
	strReturnTime.Format(_T("%04d-%02d-%02d-%02d-%02d-%02d"), calTime.GetYear(), calTime.GetMonth(), calTime.GetDay(), calTime.GetHour(), calTime.GetMinute(), calTime.GetSecond());

	return strReturnTime;
}


int NotePadManager::MaxFolderSequence()
{
	int nMaxSequence = 0;

	for (int i = 0; i < m_allFolderList.Size(); i++)
	{
		FolderItem0* folder = m_allFolderList.At(i);
		int nCompareSequence = folder->GetFolderSequence();
		if (nMaxSequence < nCompareSequence)
			nMaxSequence = nCompareSequence;
	}

	for (int i = 0; i < m_recycleFolderList.Size(); i++)
	{
		FolderItem0* folder = m_recycleFolderList.At(i);
		int nCompareSequence = folder->GetFolderSequence();
		if (nMaxSequence < nCompareSequence)
			nMaxSequence = nCompareSequence;
	}

	return nMaxSequence;
}


CString NotePadManager::GetLatleyNoteContent()
{
	return strLatelyNoteContent;
}
 
void NotePadManager::CreateFolderXml(NotePadXMLManager::FolderSaveData folderdata)
{
	xmlManager->CreateFolderXml(folderdata);
}

void NotePadManager::UpdateFolderXml(NotePadXMLManager::FolderSaveData origindata, NotePadXMLManager::FolderSaveData updatedata)
{
	xmlManager->UpdateFolderXml(origindata, updatedata);
}

void NotePadManager::SaveFolderXml(NotePadXMLManager::FolderSaveData folderdata)
{
	xmlManager->SaveFolderXml(folderdata);
}

void NotePadManager::CreateNoteXml(NotePadXMLManager::NoteSaveData notedata)
{
	xmlManager->CreateNoteXml(notedata);
}

void NotePadManager::SaveNoteXml(NotePadXMLManager::NoteSaveData notedata)
{
	xmlManager->SaveNoteXml(notedata);
}

void NotePadManager::UpdateNoteXml(NotePadXMLManager::NoteSaveData origindata, NotePadXMLManager::NoteSaveData updatedata)
{
	xmlManager->UpdateNoteXml(origindata, updatedata);
}

void NotePadManager::RecycleNoteXml(NotePadXMLManager::NoteSaveData origindata)
{
	xmlManager->RecycleNoteXml(origindata);
}