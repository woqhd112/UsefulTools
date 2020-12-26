// SettingTheme.cpp: 구현 파일
//

#include "pch.h"
#include "BOKOTools.h"
#include "BOKOToolsDlg.h"
#include "SettingTheme.h"
#include "afxdialogex.h"


// SettingTheme 대화 상자

IMPLEMENT_DYNAMIC(SettingTheme, CDialogEx)

SettingTheme::SettingTheme(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING_THEME, pParent)
{
	this->pParent = pParent;
}

SettingTheme::~SettingTheme()
{
}

void SettingTheme::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SettingTheme, CDialogEx)
END_MESSAGE_MAP()


// SettingTheme 메시지 처리기


BOOL SettingTheme::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SettingTheme::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}
