﻿// ConvertWidthTab.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "ConvertWidthTab.h"
#include "afxdialogex.h"


// ConvertWidthTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertWidthTab, CDialogEx)

ConvertWidthTab::ConvertWidthTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_WIDTH, pParent)
{

}

ConvertWidthTab::~ConvertWidthTab()
{
}

void ConvertWidthTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ICON_WIDTH, m_btn_icon);
}


BEGIN_MESSAGE_MAP(ConvertWidthTab, CDialogEx)
END_MESSAGE_MAP()


// ConvertWidthTab 메시지 처리기


void ConvertWidthTab::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL ConvertWidthTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(RGB(250, 250, 250));

	m_btn_icon.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_icon.InsertImage(IDB_PNG_WIDTH_NOMAL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
