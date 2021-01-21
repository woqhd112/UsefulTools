#include "pch.h"
#include "CustomXml.h"

namespace CustomXml
{
	void CreateConfigFile(CString& strFullPath)
	{
		TCHAR chFilePath[256] = { 0, };
		GetModuleFileName(NULL, chFilePath, 256);
		strFullPath = (LPCTSTR)chFilePath;
		int nLen = strFullPath.ReverseFind('\\');

		if (nLen > 0)
		{
			strFullPath = strFullPath.Left(nLen);
		}

		CFileFind rootFind;
		if (rootFind.FindFile(strFullPath + _T("\\BOKOTools"))) {
			strFullPath += _T("\\BOKOTools");
		}
		rootFind.Close();

		CreateDefaultDirectory(strFullPath, _T("\\Config"));
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
}