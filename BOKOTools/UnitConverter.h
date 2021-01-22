#pragma once
#include "ConvertBitTab.h"
#include "ConvertLengthTab.h"
#include "ConvertTimeTab.h"
#include "ConvertWeightTab.h"
#include "ConvertWidthTab.h"
#include "UsingManualDialog.h"

// UnitConverter 대화 상자

class UnitConverter : public CDialogEx
{
	DECLARE_DYNAMIC(UnitConverter)

public:
	UnitConverter(int nManualImageID, bool bUsingManual, ThemeData* currentTheme, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UnitConverter();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONVERTER };
#endif

private:

	CWnd* pParent;
	ThemeData* currentTheme;
	UsingManualDialog* usingManual;
	bool bUsingManual;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();
	afx_msg void OnClose();

private:

	enum PointDescription
	{
		CONVERT_LENGTH_DESC	= 0,
		CONVERT_WIDTH_DESC	= 1,
		CONVERT_WEIGHT_DESC	= 2,
		CONVERT_BIT_DESC	= 3,
		CONVERT_TIME_DESC	= 4,
	};

	CStatic m_stt_tab;

	ConvertBitTab* m_convert_bit;
	ConvertLengthTab* m_convert_length;
	ConvertTimeTab* m_convert_time;
	ConvertWeightTab* m_convert_weight;
	ConvertWidthTab* m_convert_width;

	CRect converterBorderRect;

	CalculateButton m_btn_length;
	CalculateButton m_btn_width;
	CalculateButton m_btn_weight;
	CalculateButton m_btn_time;
	CalculateButton m_btn_bit;

	PointDescription pointDesc;
	bool bClickTab;

public:
	afx_msg void OnBnClickedButtonLength();
	afx_msg void OnBnClickedButtonWidth();
	afx_msg void OnBnClickedButtonWeight();
	afx_msg void OnBnClickedButtonTimec();
	afx_msg void OnBnClickedButtonBit();

	afx_msg void OnPaint();
};
