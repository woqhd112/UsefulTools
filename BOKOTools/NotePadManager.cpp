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
	//m_allNoteList.FreeAll();
	m_otherNoteList.Clear();
	m_allNoteList.Clear();

	for (int i = 0; i < m_allFolderList.Size(); i++)
	{
		FolderItem0* deleteFolder = m_allFolderList.At(i);
		delete deleteFolder;
		deleteFolder = nullptr;
	}
	m_allFolderList.Clear();
	//m_allFolderList.FreeAll();

	for (int i = 0; i < m_recycleNoteList.Size(); i++)
	{
		NoteItem* deleteNote = m_recycleNoteList.At(i);
		delete deleteNote;
		deleteNote = nullptr;
	}
	m_recycleNoteList.Clear();
	//m_recycleNoteList.FreeAll();

	for (int i = 0; i < (int)m_recycleFolderList.Size(); i++)
	{
		FolderItem0* deleteFolder = m_recycleFolderList.At(i);
		ViewNoteList deleteNoteList = deleteFolder->GetFolder();
		//deleteNoteList.FreeAll();
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
}

void NotePadManager::Init(NotePadList* pNotePadList, FolderList* pFolderList, NotePadRecycle* pRecycleDlg)
{
	this->pNotePadList = pNotePadList;
	this->pFolderList = pFolderList;
	this->pRecycleDlg = pRecycleDlg;
	bInit = true;
}

bool NotePadManager::LoadNotePadData()
{
	if (!bInit) return false;

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
					CString strNoteFolderSequence = markUp.GetAttrib(_T("seq"));

					CTime createNoteTime = GetTimeCal(strNoteCreateTime);
					CTime updateNoteTime = GetTimeCal(strNoteUpdateTime);


					int nNoteFolderSequence = _ttoi(strNoteFolderSequence);
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
						NoteItem* newNote = new NoteItem(currentTheme, pNotePadList);
						NoteItem::NoteInit noteinit;
						noteinit.nNoteName = _ttoi(strNoteName);
						noteinit.nFolderSequence = nNoteFolderSequence;
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

						allocFolder.Push(newNote);
					}
					else
					{
						AfxMessageBox(_T("노트정보를 읽지 못하였습니다."));
					}
				}
				markUp.OutOfElem();
				m_allNoteList.Push(allocFolder);

				// 여기에 FolderItem 할당
				FolderItem0* newFolder = new FolderItem0(currentTheme, pFolderList);
				FolderItem0::FolderInit folderinit;
				folderinit.strFolderName = strFolderName;
				folderinit.nFolderSequence = nFolderSequence;
				folderinit.nFolderSize = nFolderSize;
				folderinit.nFolderColorIndex = nFolderColorIndex;
				folderinit.folder = allocFolder;
				folderinit.createTime = createFolderTime;
				folderinit.updateTime = updateFolderTime;

				newFolder->Initialize(folderinit);

				m_allFolderList.Push(newFolder);
			}
			markUp.OutOfElem();
		}

		if (markUp.FindElem(_T("recy")))
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

				markUp.IntoElem();
				ViewNoteList allocFolder;
				while (markUp.FindElem(_T("note")))
				{
					int nNoteName = 0;
					CString strNoteName;
					strNoteName.Format(_T("%d"), nNoteName);
					CString strNotePath;
					//CString strNoteName = markUp.GetAttrib(_T("name"));
					CString strLocked = markUp.GetAttrib(_T("lock"));
					CString strNoteCreateTime = markUp.GetAttrib(_T("create"));
					CString strNoteUpdateTime = markUp.GetAttrib(_T("update"));
					CString strNoteFolderSequence = markUp.GetAttrib(_T("seq"));

					CTime createNoteTime = GetTimeCal(strNoteCreateTime);
					CTime updateNoteTime = GetTimeCal(strNoteUpdateTime);


					int nNoteFolderSequence = _ttoi(strNoteFolderSequence);
					int nLocked = _ttoi(strLocked);
					if (nLocked <= 0) nLocked = 0;
					else nLocked = 1;
					bool bLocked = (bool)nLocked;

					CustomXml::GetModulePath(strNotePath);
					strNotePath += (_T("\\Note\\r") + strFolderSequence + strNoteName + _T(".txt"));

					NoteFile file;
					CString strNoteContent = _T("");
					if (file.NoteRead(strNotePath, strNoteContent))
					{
						NoteItem* newNote = new NoteItem(currentTheme, pRecycleDlg);
						NoteItem::NoteInit noteinit;
						noteinit.nNoteName = nNoteName;
						noteinit.nFolderSequence = nNoteFolderSequence;
						noteinit.strNoteContent = strNoteContent;
						noteinit.tagColor = folderColor;
						noteinit.isLock = bLocked;
						noteinit.nFolderSize = nFolderSize;
						noteinit.createTime = createNoteTime;
						noteinit.updateTime = updateNoteTime;

						newNote->Initialize(noteinit);

						allocFolder.Push(newNote);
					}
					else
					{
						AfxMessageBox(_T("노트정보를 읽지 못하였습니다."));
					}
					nNoteName++;
				}
				markUp.OutOfElem();

				// 여기에 FolderItem 할당
				FolderItem0* newFolder = new FolderItem0(currentTheme, pRecycleDlg);
				FolderItem0::FolderInit folderinit;
				folderinit.strFolderName = strFolderName;
				folderinit.nFolderSequence = nFolderSequence;
				folderinit.nFolderSize = nFolderSize;
				folderinit.nFolderColorIndex = nFolderColorIndex;
				folderinit.folder = allocFolder;
				folderinit.createTime = createFolderTime;
				folderinit.updateTime = updateFolderTime;

				newFolder->Initialize(folderinit);

				m_recycleFolderList.Push(newFolder);
			}

			while (markUp.FindElem(_T("note")))
			{
				int nNoteName = 0;
				CString strNoteName;
				strNoteName.Format(_T("%d"), nNoteName);
				CString strNotePath;
				//CString strNoteName = markUp.GetAttrib(_T("name"));
				CString strLocked = markUp.GetAttrib(_T("lock"));
				CString strNoteCreateTime = markUp.GetAttrib(_T("create"));
				CString strNoteUpdateTime = markUp.GetAttrib(_T("update"));
				CString strNoteFolderSequence = markUp.GetAttrib(_T("seq"));

				CTime createNoteTime = GetTimeCal(strNoteCreateTime);
				CTime updateNoteTime = GetTimeCal(strNoteUpdateTime);


				int nNoteFolderSequence = _ttoi(strNoteFolderSequence);
				int nLocked = _ttoi(strLocked);
				if (nLocked <= 0) nLocked = 0;
				else nLocked = 1;
				bool bLocked = (bool)nLocked;

				CustomXml::GetModulePath(strNotePath);
				strNotePath += (_T("\\Note\\sr") + strNoteFolderSequence + strNoteName + _T(".txt"));

				NoteFile file;
				CString strNoteContent = _T("");
				if (file.NoteRead(strNotePath, strNoteContent))
				{
					NoteItem* newNote = new NoteItem(currentTheme, pRecycleDlg);
					NoteItem::NoteInit noteinit;
					noteinit.nNoteName = nNoteName;
					noteinit.nFolderSequence = nNoteFolderSequence;
					noteinit.strNoteContent = strNoteContent;
					noteinit.tagColor = TAG_COLOR_5;
					noteinit.isLock = bLocked;
					noteinit.nFolderSize = 0;
					noteinit.createTime = createNoteTime;
					noteinit.updateTime = updateNoteTime;

					newNote->Initialize(noteinit);

					m_recycleNoteList.Push(newNote);
				}
				else
				{
					AfxMessageBox(_T("노트정보를 읽지 못하였습니다."));
				}
				nNoteName++;
			}

			markUp.OutOfElem();
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

		NotePadManager::NoteSaveData updateNote;
		updateNote.nFolderSequence = saveNote->GetFolderSequence();
		updateNote.nLock = saveNote->IsLock();
		updateNote.nNoteName = saveNote->GetNoteName();
		updateNote.strCreateTime = GetTimeCal(saveNote->GetCreateTime());
		updateNote.strUpdateTime = GetTimeCal(bUpdateNote ? CTime::GetCurrentTime() : saveNote->GetUpdateTime());

		SaveNoteXml(updateNote);
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
	NotePadManager::NoteSaveData originNoteData, updateNoteData;
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

	UpdateNoteXml(originNoteData, updateNoteData);

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
	NotePadManager::NoteSaveData recycleNoteData;
	recycleNoteData.nFolderSequence = findNote->GetFolderSequence();
	recycleNoteData.nLock = findNote->IsLock();
	recycleNoteData.nNoteName = findNote->GetNoteName();
	recycleNoteData.strCreateTime = GetTimeCal(findNote->GetCreateTime());
	recycleNoteData.strUpdateTime = GetTimeCal(findNote->GetUpdateTime());
	RecycleNoteXml(recycleNoteData);

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

		NotePadManager::NoteSaveData updateNote;
		updateNote.nFolderSequence = saveNote->GetFolderSequence();
		updateNote.nLock = saveNote->IsLock();
		updateNote.nNoteName = saveNote->GetNoteName();
		updateNote.strCreateTime = GetTimeCal(saveNote->GetCreateTime());
		updateNote.strUpdateTime = GetTimeCal(saveNote->GetUpdateTime());

		SaveNoteXml(updateNote);
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
	NoteItem* newNote = new NoteItem(currentTheme, pRecycleDlg);
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
	NoteItem* newNote = new NoteItem(currentTheme, pNotePadList);
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

bool NotePadManager::CreateDefaultNoteXml(CMarkup* markUp, CString strFullPath)
{
	bool bReturn = false;
	CFileFind xmlFind;
	if (!xmlFind.FindFile(strFullPath))
	{
		markUp->AddElem(_T("NotePad"));
		markUp->IntoElem();
		markUp->AddElem(_T("bin"));
		markUp->IntoElem();
		markUp->AddElem(_T("folder"));
		markUp->AddAttrib(_T("seq"), 0);
		markUp->AddAttrib(_T("name"), _T("other"));
		markUp->AddAttrib(_T("tagcolor"), 5);
		markUp->AddAttrib(_T("size"), 0);
		CTime createTime = CTime::GetCurrentTime();
		CString strCreateTime = GetTimeCal(createTime);
		markUp->AddAttrib(_T("create"), strCreateTime);
		markUp->AddAttrib(_T("update"), strCreateTime);
		markUp->OutOfElem();
		markUp->AddElem(_T("recy"));

		FolderItem0* newFolder = new FolderItem0(currentTheme, pFolderList);
		FolderItem0::FolderInit folderinit;
		folderinit.strFolderName = _T("other");
		folderinit.nFolderSequence = 0;
		folderinit.nFolderSize = 0;
		folderinit.nFolderColorIndex = TAG_COLOR_5;
		folderinit.folder = {};
		folderinit.createTime = createTime;
		folderinit.updateTime = createTime;

		m_allNoteList.Push({});
		m_allFolderList.Push(newFolder);

		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
}

CString NotePadManager::GetTimeCal(CTime calTime)
{
	CString strReturnTime;
	strReturnTime.Format(_T("%04d-%02d-%02d-%02d-%02d-%02d"), calTime.GetYear(), calTime.GetMonth(), calTime.GetDay(), calTime.GetHour(), calTime.GetMinute(), calTime.GetSecond());

	return strReturnTime;
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

CString NotePadManager::GetLatleyNoteContent()
{
	return strLatelyNoteContent;
}

void NotePadManager::RecycleNoteXml(NoteSaveData origindata)
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
			}
			markUp.OutOfElem();
		}

		if (markUp.FindElem(_T("recy")))
		{
			markUp.IntoElem();
			int nNoteNameCount = 0;
			while (markUp.FindElem(_T("note")))
			{
				if (_ttoi(markUp.GetAttrib(_T("seq"))) == origindata.nFolderSequence)
					nNoteNameCount++;
			}

			markUp.AddElem(_T("note"));
			markUp.AddAttrib(_T("seq"), origindata.nFolderSequence);
			markUp.AddAttrib(_T("name"), nNoteNameCount);
			markUp.AddAttrib(_T("lock"), origindata.nLock);
			markUp.AddAttrib(_T("create"), origindata.strCreateTime);
			markUp.AddAttrib(_T("update"), origindata.strUpdateTime);
			markUp.OutOfElem();
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePadManager::UpdateNoteXml(NoteSaveData origindata, NoteSaveData updatedata)
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
					markUp.AddAttrib(_T("seq"), updatedata.nFolderSequence);
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

void NotePadManager::SaveNoteXml(NoteSaveData notedata)
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
							markUp.SetAttrib(_T("seq"), notedata.nFolderSequence);
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

void NotePadManager::CreateNoteXml(NoteSaveData notedata)
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
					markUp.AddAttrib(_T("seq"), notedata.nFolderSequence);
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

void NotePadManager::SaveFolderXml(FolderSaveData folderdata)
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

void NotePadManager::UpdateFolderXml(FolderSaveData origindata, FolderSaveData updatedata)
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

void NotePadManager::CreateFolderXml(FolderSaveData folderdata)
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
