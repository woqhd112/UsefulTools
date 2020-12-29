// SortIcon.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "SortIcon.h"
#include "afxdialogex.h"


// SortIcon 대화 상자

IMPLEMENT_DYNAMIC(SortIcon, CDialogEx)

SortIcon::SortIcon(ThemeData* currentTheme, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SORT_ICON, pParent)
{
	this->currentTheme = currentTheme;
	this->pParent = pParent;
}

SortIcon::~SortIcon()
{
}

void SortIcon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SortIcon, CDialogEx)
END_MESSAGE_MAP()


// SortIcon 메시지 처리기
