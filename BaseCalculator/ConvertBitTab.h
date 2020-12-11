#pragma once
#include "ConvertButton.h"


// ConvertBitTab 대화 상자

class ConvertBitTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertBitTab)

public:
	ConvertBitTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertBitTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_BIT };
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
