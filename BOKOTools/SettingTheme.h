#pragma once


// SettingTheme 대화 상자

class SettingTheme : public CDialogEx
{
	DECLARE_DYNAMIC(SettingTheme)

public:
	SettingTheme(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingTheme();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING_THEME };
#endif

private:

	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
