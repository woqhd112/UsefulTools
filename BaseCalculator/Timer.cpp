// Timer.cpp: 구현 파일
//

#include "pch.h"
#include "BaseCalculator.h"
#include "BaseCalculatorDlg.h"
#include "Timer.h"
#include "afxdialogex.h"


// Timer 대화 상자

IMPLEMENT_DYNAMIC(Timer, CDialogEx)

Timer::Timer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TIMER, pParent)
{
	this->pParent = pParent;
}

Timer::~Timer()
{
}

void Timer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Timer, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Timer 메시지 처리기


void Timer::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void Timer::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
	Timer::PostNcDestroy();
}


void Timer::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CBaseCalculatorDlg* parent = (CBaseCalculatorDlg*)pParent;
	parent->bTimer = false;
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL Timer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}
