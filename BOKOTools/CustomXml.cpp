#include "pch.h"
#include "CustomXml.h"

namespace CustomXml
{
	void CreateConfigFile(CString& strFullPath)
	{

		GetModulePath(strFullPath);
		CreateDefaultDirectory(strFullPath, _T("\\Config"));
	}

	void GetModulePath(CString& strPath)
	{
		CFileFind rootFind;
		TCHAR chFilePath[256] = { 0, };
		GetModuleFileName(NULL, chFilePath, 256);
		strPath = (LPCTSTR)chFilePath;
		int nLen = strPath.ReverseFind('\\');

		if (nLen > 0)
		{
			strPath = strPath.Left(nLen);
		}

		if (rootFind.FindFile(strPath + _T("\\BOKOTools"))) {
			strPath += _T("\\BOKOTools");
		}
		rootFind.Close();
	}

	void CreateDefaultDirectory(CString& strFullPath, CString strAppendPath)
	{
		CFileFind findPath;
		strFullPath += strAppendPath;
		if (!findPath.FindFile(strFullPath))
		{
			CreateDirectory(strFullPath, NULL);
		}
		findPath.Close();
	}

	void SaveXml(CMarkup* markup, CString strSaveFullPath)
	{
		CString strXML = markup->GetDoc();

		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		JWXml::CXml saveXML;
		saveXML.LoadXml((LPCTSTR)strXML);
		saveXML.SaveWithFormatted(strSaveFullPath);
		saveXML.Close();
		CoUninitialize();
	}

	bool LoadConfigXml(CMarkup* markup, CString strFullPath)
	{
		bool bSavedXml = false;
		if (markup->Load(strFullPath))
		{
			bSavedXml = true;
		}

		return bSavedXml;
	}
}