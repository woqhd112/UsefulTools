// CalculateEdit.cpp: 구현 파일
//

#include "pch.h"
#include "GoCabinet.h"
#include "CalculateEdit.h"


// CalculateEdit

IMPLEMENT_DYNAMIC(CalculateEdit, CEdit)

CalculateEdit::CalculateEdit()
{
	m_bExampleText = false;
	m_bFocusOn = false;
}

CalculateEdit::~CalculateEdit()
{
}


BEGIN_MESSAGE_MAP(CalculateEdit, CEdit)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CalculateEdit 메시지 처리기

void CalculateEdit::Initialize(int nFontSize, CString strFontName)
{
	thisFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	this->SetFont(&thisFont);
}

void CalculateEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bExampleText)
	{
		this->SetWindowTextW(_T(""));
		m_bExampleText = false;
	}

	CRect rect;
	GetClientRect(&rect);

	if (PtInRect(&rect, point))
	{
		m_bFocusOn = true;
	}
	else
	{
		m_bFocusOn = false;
	}
	
	CEdit::OnLButtonDown(nFlags, point);
}
