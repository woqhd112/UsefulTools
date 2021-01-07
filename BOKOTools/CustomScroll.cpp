#include "pch.h"
#include "CustomScroll.h"

CustomScroll::CustomScroll()
{

}

CustomScroll::~CustomScroll()
{
	Destroy();
}

void CustomScroll::Destroy()
{
	csi = { CUSTOM_SCROLL_TYPE_DEFAULT, 0, 0, 0, 0, SB_VERT };
	for (int i = 0; i < (int)buttonVector.size(); i++)
	{
		CGdipButton* button = buttonVector.at(i);
		delete button;
		button = nullptr;
	}
	buttonVector.clear();
	buttonRect.clear();
	nLineCount = 0;
	nCurrentLinePos = 0;
	bOneButtonLight = false;
}

void CustomScroll::Create(CWnd* pDialogCtl)
{
	thisCtlDialog = pDialogCtl;
	csi = { CUSTOM_SCROLL_TYPE_DEFAULT, 0, 0, 0, 0, SB_VERT };
	nLineCount = 0;
	nCurrentLinePos = 0;
	nButtonID = 30000;
	bOneButtonLight = false;
}

void CustomScroll::Initialize(CustomScrollInfo csi)
{
	this->csi = csi;
}

void CustomScroll::LineEnd()
{
	csi.nAllPageSize += csi.nOnePageSize;
	nLineCount++;
}

void CustomScroll::LineDelete()
{
	csi.nAllPageSize -= csi.nOnePageSize;
	nLineCount--;
}

void CustomScroll::IncreaseScroll()
{
	LineEnd();
	if (csi.cst == CUSTOM_SCROLL_TYPE_BUTTON)
	{
		CGdipButton* button = new CGdipButton;
		button->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), thisCtlDialog, nButtonID++);
		button->ShowWindow(SW_SHOW);

		CRect dialogRect;
		thisCtlDialog->GetWindowRect(dialogRect);

		int nButtonWidth = 10;
		int nButtonHeight = 10;
		int nButtonPos = (dialogRect.Height() - 10 - 47) / nLineCount;
		int nButtonPos_x = 10;
		int nButtonPos_y = 20;

		for (int i = 0; i < nLineCount; i++)
		{
			nButtonPos_y += 12;
		}

		CRect scrollPos;
		scrollPos = { nButtonPos_x, nButtonPos_y, nButtonPos_x + nButtonWidth, nButtonPos_y + nButtonHeight };
		buttonVector.push_back(button);
		buttonRect.push_back(scrollPos);

		button->MoveWindow(scrollPos);
		button->LoadStdImage(currentTheme->GetScrollIcon().nNormalID, _T("PNG"));	// 여기에 테마 스크롤 버튼 namal
		button->LoadHovImage(currentTheme->GetScrollIcon().nHoverID, _T("PNG"));	// 여기에 테마 스크롤 버튼 hover
		button->LoadAltImage(currentTheme->GetScrollIcon().nClickID, _T("PNG"));	// 여기에 테마 스크롤 버튼 namal
		button->m_bUseMouseEvent = false;

		if (bOneButtonLight)
		{
			bOneButtonLight = false;
			for (int i = 0; i < buttonVector.size(); i++)
			{
				buttonVector.at(i)->ShowWindow(SW_SHOW);
			}
		}
	}
	else
	{

	}
}

// CustomScrollType이 버튼인경우만 사용할것.
void CustomScroll::ExecuteScrollPos(ThemeData* currentTheme)
{
	this->currentTheme = currentTheme;
	if (csi.cst == CUSTOM_SCROLL_TYPE_BUTTON)
	{
		if (nLineCount == 0) return;

		CRect dialogRect;
		thisCtlDialog->GetWindowRect(dialogRect);

		CGdipButton* button;
		

		int nButtonWidth = 10;
		int nButtonHeight = 10;
		int nButtonPos = (dialogRect.Height() - 10 - 47) / nLineCount;
		int nButtonPos_x = 10;
		int nButtonPos_y = 20;

		for (int i = 1; i <= nLineCount; i++)
		{
			button = new CGdipButton;
			button->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), thisCtlDialog, nButtonID++);
			button->ShowWindow(SW_SHOW);

			nButtonPos_y += 12;

			CRect scrollPos;
			scrollPos = { nButtonPos_x, nButtonPos_y, nButtonPos_x + nButtonWidth, nButtonPos_y + nButtonHeight };
			buttonVector.push_back(button);
			buttonRect.push_back(scrollPos);

			button->MoveWindow(scrollPos);
			button->LoadStdImage(currentTheme->GetScrollIcon().nNormalID, _T("PNG"));	// 여기에 테마 스크롤 버튼 namal
			button->LoadHovImage(currentTheme->GetScrollIcon().nHoverID, _T("PNG"));	// 여기에 테마 스크롤 버튼 hover
			button->LoadAltImage(currentTheme->GetScrollIcon().nClickID, _T("PNG"));	// 여기에 테마 스크롤 버튼 namal
			button->m_bUseMouseEvent = false;
		}
		buttonVector.at(0)->UseHoverEvent();
		if (nLineCount == 1)
		{
			for (int i = 0; i < buttonVector.size(); i++)
			{
				buttonVector.at(i)->ShowWindow(SW_HIDE);
				bOneButtonLight = true;
			}
		}
	}
	else
	{
		LoadScroll(csi.nOnePageSize);
	}
}

void CustomScroll::ThemeChange(ThemeData* changeTheme)
{
	this->currentTheme = changeTheme;
	for (int i = 0; i < (int)buttonVector.size(); i++)
	{
		buttonVector.at(i)->DisConnect();
		buttonVector.at(i)->LoadStdImage(currentTheme->GetScrollIcon().nNormalID, _T("PNG"));
		buttonVector.at(i)->LoadHovImage(currentTheme->GetScrollIcon().nHoverID, _T("PNG"));
		buttonVector.at(i)->LoadAltImage(currentTheme->GetScrollIcon().nClickID, _T("PNG"));
	}
}

void CustomScroll::LoadScroll(int nThisHeight)
{
	int nScrollMax = 0;
	if (nThisHeight < csi.nAllPageSize)
	{
		nScrollMax = csi.nAllPageSize - 1;
		csi.nOnePageSize = nThisHeight;
		csi.nScrollPos = min(csi.nScrollPos, csi.nAllPageSize - csi.nOnePageSize - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPos = csi.nScrollPos;
	si.nPage = csi.nOnePageSize;
	thisCtlDialog->SetScrollInfo(csi.nKindOfScrollFlags, &si, TRUE);
}

// 이 함수는 OnVScroll 이나 OnHScroll 함수안에서 호출할것.
bool CustomScroll::OperateScroll(int nSBCode, int nPos)
{
	int delta = 0;
	if (csi.nKindOfScrollFlags == SB_VERT)	// 세로 스크롤
	{
		switch (nSBCode)
		{
			case SB_LINEUP:
				delta = -csi.nWheelValue;
				nCurrentLinePos--;
				break;
			case SB_PAGEUP:
				delta = -csi.nOnePageSize;
				nCurrentLinePos--;
				break;
			case SB_THUMBTRACK:
				delta = static_cast<int>(nPos) - csi.nScrollPos;
				break;
			case SB_PAGEDOWN:
				delta = csi.nOnePageSize;
				nCurrentLinePos++;
				break;
			case SB_LINEDOWN:
				delta = csi.nWheelValue;
				nCurrentLinePos++;
				break;
			default:
				return false;
		}

		if (nCurrentLinePos < 0)
		{
			nCurrentLinePos = 0;
			return false;
		}
		if (csi.bLikeButtonEvent)
		{
			if (nCurrentLinePos >= nLineCount)
			{
				nCurrentLinePos = nLineCount - 1;
				return false;
			}
		}

		int scrollpos = csi.nScrollPos + delta;
		int nMaxPos = csi.nAllPageSize - csi.nOnePageSize;

		if (scrollpos < 0)
		{
			delta = -csi.nScrollPos;
		}
		else
		{
			if (scrollpos > nMaxPos)
			{
				delta = nMaxPos - csi.nScrollPos;
			}
		}

		if (delta != 0)
		{
			csi.nScrollPos += delta;
			thisCtlDialog->SetScrollPos(csi.nKindOfScrollFlags, csi.nScrollPos, TRUE);
			thisCtlDialog->ScrollWindow(0, -delta);
			
			if (csi.cst == CUSTOM_SCROLL_TYPE_BUTTON)
			{
				for (int i = 0; i < (int)buttonVector.size(); i++)
				{
					if (nCurrentLinePos == i)
					{
						buttonVector.at(i)->UseHoverEvent();
					}
					else
					{
						buttonVector.at(i)->UserLeaveEvent();
					}
					buttonVector.at(i)->MoveWindow(buttonRect.at(i));
				}
			}
			else
			{

			}

			return true;
		}
	}
	else // 가로 스크롤
	{

	}


	return false;
}

// 이 함수는 OnMouseWheel 함수안에서 호출할것.
// 호출 후 OnVScroll 이나 OnHScroll 호출할것.
UINT CustomScroll::OperateWheel(short zDelta)
{

	UINT nFlag;
	if (zDelta > 0)	// 위스크롤
	{
		if (csi.cst == CUSTOM_SCROLL_TYPE_DEFAULT) nFlag = SB_LINEUP;
		else nFlag = SB_PAGEUP;
	}
	else // 아래스크롤
	{
		if (csi.cst == CUSTOM_SCROLL_TYPE_DEFAULT) nFlag = SB_LINEDOWN;
		else nFlag = SB_PAGEDOWN;
	}

	return nFlag;
}

int CustomScroll::GetLineCount()
{
	return nLineCount;
}

int CustomScroll::GetCurrentLinePos()
{
	return nCurrentLinePos + 1;
}