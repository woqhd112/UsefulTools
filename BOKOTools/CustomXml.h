#pragma once
#include "CMarkup/Markup.h"
#include "CXml\Xml.h"
#include "atlstr.h"

namespace CustomXml
{
	void CreateConfigFile(CString& strFullPath);

	void CreateDefaultDirectory(CString& strFullPath, CString strAppendPath);

	void SaveXml(CMarkup* markup, CString strSaveFullPath);
}
