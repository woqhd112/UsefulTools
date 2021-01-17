// CalculateStatic.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "CalculateStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CalculateStatic

IMPLEMENT_DYNAMIC(CalculateStatic, CStatic)

CalculateStatic::CalculateStatic()
{
	nFontSize = 0;
	strFontName = _T("");
}

CalculateStatic::~CalculateStatic()
{
}


BEGIN_MESSAGE_MAP(CalculateStatic, CStatic)
END_MESSAGE_MAP()



// CalculateStatic 메시지 처리기

void CalculateStatic::Initialize(int nFontSize, CString strFontName)
{
	this->strFontName = strFontName;
	this->nFontSize = nFontSize;
	thisFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	this->SetFont(&thisFont);

}

void CalculateStatic::InvalidFont(CString strFontName)
{
	this->strFontName = strFontName;
	thisFont.DeleteObject();
	thisFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	this->SetFont(&thisFont);
}
