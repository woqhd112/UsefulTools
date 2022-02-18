#include "pch.h"
#include "NotePadXMLManager.h"
#include "NotePadManager.h"
#include "NotePadList.h"
#include "FolderList.h"
#include "NotePadRecycle.h"


NotePadXMLManager::NotePadXMLManager(ThemeData* currentTheme, NotePadManager* pManager)
{
	this->currentTheme = currentTheme;
	this->pManager = pManager;
}

NotePadXMLManager::~NotePadXMLManager()
{

}

void NotePadXMLManager::Init(NotePadList* pNotePadList, FolderList* pFolderList, NotePadRecycle* pRecycleDlg)
{
	this->pNotePadList = pNotePadList;
	this->pFolderList = pFolderList;
	this->pRecycleDlg = pRecycleDlg;
}

void NotePadXMLManager::LoadNotePad()
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

				CTime createFolderTime = pManager->GetTimeCal(strFolderCreateTime);
				CTime updateFolderTime = pManager->GetTimeCal(strFolderUpdateTime);

				int nFolderColorIndex = _ttoi(strTagColor);
				COLORREF folderColor = pManager->GetTagColorFromIndex(nFolderColorIndex);
				int nFolderSequence = _ttoi(strFolderSequence);
				int nFolderSize = _ttoi(strFolderSize);


				/* folderseq 가 0 이면 other폴더
				* 그외엔 생성폴더
				* 총합이 all폴더
				*/
				markUp.IntoElem();
				NotePadManager::ViewNoteList allocFolder;
				while (markUp.FindElem(_T("note")))
				{
					CString strNotePath;
					CString strNoteName = markUp.GetAttrib(_T("name"));
					CString strLocked = markUp.GetAttrib(_T("lock"));
					CString strNoteCreateTime = markUp.GetAttrib(_T("create"));
					CString strNoteUpdateTime = markUp.GetAttrib(_T("update"));
					CString strNoteFolderSequence = markUp.GetAttrib(_T("seq"));

					CTime createNoteTime = pManager->GetTimeCal(strNoteCreateTime);
					CTime updateNoteTime = pManager->GetTimeCal(strNoteUpdateTime);


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
							pManager->strLatelyNoteContent = noteinit.strNoteContent;
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
				pManager->m_allNoteList.Push(allocFolder);

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

				pManager->m_allFolderList.Push(newFolder);
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

				CTime createFolderTime = pManager->GetTimeCal(strFolderCreateTime);
				CTime updateFolderTime = pManager->GetTimeCal(strFolderUpdateTime);

				int nFolderColorIndex = _ttoi(strTagColor);
				COLORREF folderColor = pManager->GetTagColorFromIndex(nFolderColorIndex);
				int nFolderSequence = _ttoi(strFolderSequence);
				int nFolderSize = _ttoi(strFolderSize);

				markUp.IntoElem();
				NotePadManager::ViewNoteList allocFolder;
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

					CTime createNoteTime = pManager->GetTimeCal(strNoteCreateTime);
					CTime updateNoteTime = pManager->GetTimeCal(strNoteUpdateTime);


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

				pManager->m_recycleFolderList.Push(newFolder);
			}

			while (markUp.FindElem(_T("note")))
			{
				int nNoteName = 0;
				//CString strNoteName;
				//strNoteName.Format(_T("%d"), nNoteName);
				CString strNotePath;
				CString strNoteName = markUp.GetAttrib(_T("name"));
				CString strLocked = markUp.GetAttrib(_T("lock"));
				CString strNoteCreateTime = markUp.GetAttrib(_T("create"));
				CString strNoteUpdateTime = markUp.GetAttrib(_T("update"));
				CString strNoteFolderSequence = markUp.GetAttrib(_T("seq"));

				CTime createNoteTime = pManager->GetTimeCal(strNoteCreateTime);
				CTime updateNoteTime = pManager->GetTimeCal(strNoteUpdateTime);

				nNoteName = _ttoi(strNoteName);
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

					pManager->m_recycleNoteList.Push(newNote);
				}
				else
				{
					AfxMessageBox(_T("노트정보를 읽지 못하였습니다."));
				}
				//nNoteName++;
			}

			markUp.OutOfElem();
		}

		if (pManager->m_allNoteList.Empty())
		{
			NotePadContainer<NoteItem*> addNoteList;
			pManager->m_allNoteList.Push(addNoteList);
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

bool NotePadXMLManager::CreateDefaultNoteXml(CMarkup* markUp, CString strFullPath)
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
		CString strCreateTime = pManager->GetTimeCal(createTime);
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

		pManager->m_allNoteList.Push({});
		pManager->m_allFolderList.Push(newFolder);

		bReturn = true;
	}
	xmlFind.Close();

	return bReturn;
}

void NotePadXMLManager::RecycleNoteXml(NoteSaveData origindata)
{
	int nNoteNameCount = 0;
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

void NotePadXMLManager::RecycleFolderXml(FolderSaveData origindata)
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
					markUp.RemoveElem();
				}
			}
			markUp.OutOfElem();
		}

		if (markUp.FindElem(_T("recy")))
		{
			int nLastFolderSequence = 0;
			markUp.IntoElem();
			while (markUp.FindElem(_T("folder")))
			{
				nLastFolderSequence++;
			}

			markUp.AddElem(_T("folder"));
			markUp.AddAttrib(_T("seq"), nLastFolderSequence);
			markUp.AddAttrib(_T("name"), origindata.strFolderName);
			markUp.AddAttrib(_T("tagcolor"), pManager->GetIndexFromTagColor(origindata.folderTagColor));
			markUp.AddAttrib(_T("size"), origindata.nSize);
			markUp.AddAttrib(_T("create"), origindata.strCreateTime);
			markUp.AddAttrib(_T("update"), origindata.strUpdateTime);

			markUp.IntoElem();
			for (int i = 0; i < origindata.folder.Size(); i++)
			{
				NoteItem* updateNote = origindata.folder.At(i);
				markUp.AddElem(_T("note"));
				markUp.AddAttrib(_T("seq"), nLastFolderSequence);
				markUp.AddAttrib(_T("name"), updateNote->GetNoteName());
				markUp.AddAttrib(_T("lock"), updateNote->IsLock());
				markUp.AddAttrib(_T("create"), pManager->GetTimeCal(updateNote->GetCreateTime()));
				markUp.AddAttrib(_T("update"), pManager->GetTimeCal(updateNote->GetUpdateTime()));
			}
			markUp.OutOfElem();

			markUp.OutOfElem();
		}
	}

	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePadXMLManager::UpdateNoteXml(NoteSaveData origindata, NoteSaveData updatedata)
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
					int nSize = _ttoi(markUp.GetAttrib(_T("size")));
					markUp.SetAttrib(_T("size"), nSize + 1);
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

void NotePadXMLManager::SaveNoteXml(NoteSaveData notedata)
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

void NotePadXMLManager::CreateNoteXml(NoteSaveData notedata)
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

void NotePadXMLManager::SaveFolderXml(FolderSaveData folderdata)
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
					markUp.SetAttrib(_T("tagcolor"), pManager->GetIndexFromTagColor(folderdata.folderTagColor));
					markUp.SetAttrib(_T("size"), folderdata.nSize);
					markUp.SetAttrib(_T("update"), folderdata.strUpdateTime);
				}
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePadXMLManager::UpdateFolderXml(FolderSaveData origindata, FolderSaveData updatedata)
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
					markUp.SetAttrib(_T("tagcolor"), pManager->GetIndexFromTagColor(updatedata.folderTagColor));
					markUp.SetAttrib(_T("size"), updatedata.nSize);
					markUp.SetAttrib(_T("update"), updatedata.strUpdateTime);
				}
			}
		}
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}

void NotePadXMLManager::CreateFolderXml(FolderSaveData folderdata)
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
		markUp.AddAttrib(_T("tagcolor"), pManager->GetIndexFromTagColor(folderdata.folderTagColor));
		markUp.AddAttrib(_T("size"), folderdata.nSize);
		markUp.AddAttrib(_T("create"), folderdata.strCreateTime);
		markUp.AddAttrib(_T("update"), folderdata.strUpdateTime);
	}
	CustomXml::SaveXml(&markUp, strFullPath);
}
