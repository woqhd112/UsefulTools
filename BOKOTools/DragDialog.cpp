﻿// DragDialog.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "DragDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// DragDialog 대화 상자

IMPLEMENT_DYNAMIC(DragDialog, CDialogEx)

DragDialog::DragDialog(CGdipButton* eventButton, CalculateStatic* eventStatic, int nButtonWidth, int nButtonHeight, bool nBindPicture, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DRAG, pParent)
{
	this->hoverButton = eventButton;
	this->hoverStatic = eventStatic;
	this->pParent = pParent;
	this->nButtonWidth = nButtonWidth;
	this->nButtonHeight = nButtonHeight;
	this->nBindPicture = nBindPicture;
}

DragDialog::~DragDialog()
{
	if (newButton)
	{
		newButton->ShowWindow(SW_HIDE);
		newButton->DestroyWindow();
		delete newButton;
		newButton = nullptr;
	}

	/*if (newStatic)
	{
		newStatic->ShowWindow(SW_HIDE);
		newStatic->DestroyWindow();
		delete newStatic;
		newStatic = nullptr;
	}*/
}

void DragDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DragDialog, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// DragDialog 메시지 처리기


BOOL DragDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	if (hoverButton)
	{
		newButton = new CGdipButton;
		newButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, 50000);

		int nStd = hoverButton->nStdImageID;
		int nHov = hoverButton->nHovImageID;
		int nAlt = hoverButton->nStdImageID;

		newButton->strButtonName = hoverButton->strButtonName;
		newButton->LoadStdImage(nStd, _T("PNG"), nBindPicture);
		newButton->LoadHovImage(nHov, _T("PNG"), nBindPicture);
		newButton->LoadAltImage(nAlt, _T("PNG"), nBindPicture);
		newButton->ShowWindow(SW_SHOW);
		newButton->MoveWindow(0, 0, nButtonWidth, nButtonHeight);
	}

	/*if (hoverStatic)
	{
		newStatic = new CalculateStatic;
		newStatic->Create(_T(""), SS_CENTER, CRect(0, 0, 0, 0), this, 50001);
		newStatic->Initialize(15, hoverStatic->strFontName);
		newStatic->ShowWindow(SW_SHOW);
		newStatic->MoveWindow(0, nButtonHeight, nButtonWidth, 20);
		CString strStaticText;
		hoverStatic->GetWindowTextW(strStaticText);
		newStatic->SetWindowTextW(strStaticText);
	}*/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//void DragDialog::Initialize(ThemeData* currentTheme, CGdipButton* eventButton)
//{
//	this->hoverButton = eventButton;
//	this->currentTheme = currentTheme;
//}

void DragDialog::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


HBRUSH DragDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG) // 다이얼로그일 경우
	{
		CBrush B;
		B.CreateStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT); // 투명 설정 

		return B;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void DragDialog::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (newButton)
	{
		//OnCtlColor(this->GetDC(), this, CTLCOLOR_DLG);
		/*newButton->DisConnect();
		newButton->DeleteImage();
		newButton->LoadStdImage(hoverButton->nStdImageID, _T("PNG"), nBindPicture);
		newButton->LoadHovImage(hoverButton->nHovImageID, _T("PNG"), nBindPicture);
		newButton->LoadAltImage(hoverButton->nStdImageID, _T("PNG"), nBindPicture);
		Invalidate();*/
		//newButton->DisConnect();
	}
}
