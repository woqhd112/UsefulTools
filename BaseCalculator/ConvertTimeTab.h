#pragma once
#include "ConvertButton.h"

// ConvertTimeTab 대화 상자

class ConvertTimeTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertTimeTab)

public:
	ConvertTimeTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertTimeTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	ConvertButton m_btn_icon;
};
