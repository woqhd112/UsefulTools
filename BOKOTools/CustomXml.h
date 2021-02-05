#pragma once
#include "CMarkup/Markup.h"
#include "CXml\Xml.h"
#include "atlstr.h"

namespace CustomXml
{
	void CreateConfigFile(CString& strFullPath);

	void GetModulePath(CString& strPath);

	void CreateDefaultDirectory(CString& strFullPath, CString strAppendPath);

	void SaveXml(CMarkup* markup, CString strSaveFullPath);

	bool LoadConfigXml(CMarkup* markup, CString strFullPath);
}
