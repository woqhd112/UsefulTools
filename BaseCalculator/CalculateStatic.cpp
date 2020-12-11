// CalculateStatic.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "CalculateStatic.h"


// CalculateStatic

IMPLEMENT_DYNAMIC(CalculateStatic, CStatic)

CalculateStatic::CalculateStatic()
{

}

CalculateStatic::~CalculateStatic()
{
}


BEGIN_MESSAGE_MAP(CalculateStatic, CStatic)
END_MESSAGE_MAP()



// CalculateStatic 메시지 처리기

void CalculateStatic::Initialize(int nFontSize, CString strFontName)
{
	thisFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	this->SetFont(&thisFont);

}

