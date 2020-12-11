// ConvertTimeTab.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "ConvertTimeTab.h"
#include "afxdialogex.h"


// ConvertTimeTab 대화 상자

IMPLEMENT_DYNAMIC(ConvertTimeTab, CDialogEx)

ConvertTimeTab::ConvertTimeTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_TIME, pParent)
{

}

ConvertTimeTab::~ConvertTimeTab()
{
}

void ConvertTimeTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ICON_TIME, m_btn_icon);
}


BEGIN_MESSAGE_MAP(ConvertTimeTab, CDialogEx)
END_MESSAGE_MAP()


// ConvertTimeTab 메시지 처리기


void ConvertTimeTab::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL ConvertTimeTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetBackgroundColor(RGB(250, 250, 250));

	m_btn_icon.Initialize(RGB(255, 255, 255), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS);
	m_btn_icon.InsertImage(IDB_PNG_TIMEC_NOMAL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
