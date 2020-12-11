#pragma once
#include "ConvertButton.h"

// ConvertWeightTab 대화 상자

class ConvertWeightTab : public CDialogEx
{
	DECLARE_DYNAMIC(ConvertWeightTab)

public:
	ConvertWeightTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConvertWeightTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_WEIGHT };
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
