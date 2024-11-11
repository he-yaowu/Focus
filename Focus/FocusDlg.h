
// FocusDlg.h : 头文件
//

#pragma once
#include <string>
#include <vector>
#include <map>
#include "afxwin.h"
#include "afxcmn.h"
// 配置项
struct Config {
	std::string config_name;
	int move_Up_times_left;					//上移动次数
    int move_Up_pixel_left;					//每毫秒上推多少像素
	int Interval_left;						//中间暂停间隔
	int move_Down_times_left;				//每毫秒回正多少像素
	int move_Down_pixel_left;				//下移动的像素	
	std::string hotkey_left;					// 热键

	int move_Up_times_right;					//上移动次数
    int move_Up_pixel_right;					//每毫秒上推多少像素
	int Interval_right;						//中间暂停间隔
	int move_Down_times_right;				//每毫秒回正多少像素
	int move_Down_pixel_right;				//下移动的像素	
	std::string hotkey_right;					// 热键

	Config()
	{
		config_name = "配置1";
		move_Up_times_left = 10;
		move_Up_pixel_left = 120;
		Interval_left = 20;
		move_Down_times_left = 10;
		move_Down_pixel_left = 26;
		hotkey_left = "R";

		move_Up_times_right = 10;
		move_Up_pixel_right = 600;
		Interval_right = 20;
		move_Down_times_right = 10;
		move_Down_pixel_right = 200;
		hotkey_right = "M";
	}
};

// CFocusDlg 对话框
class CFocusDlg : public CDialogEx
{
// 构造
public:
	CFocusDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FOCUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void OnHotKeyPressed(int key);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton_New();
	afx_msg void OnBnClickedButton_Delete();
	afx_msg void OnBnClickedButton_Default();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnClose();

	bool m_bIsRunning;
	bool m_bActive;
	bool m_bUpComplete;
	bool m_bDownComplete;
	bool m_bInterval;
	long m_timeUpcomplete;
	int	m_HotKey;
	CListBox m_listConfig;
	CButton  m_button;
	CEdit  m_Editbox[14];
	POINT	 m_beginPos;
	void ReadConfig();
	void SaveConfig();
	void SetEditText(Config config);
	int GetLeftHotKeyNum();
	int GetRightHotKeyNum();
	std::vector<Config> m_VecConfig;
	int m_nUp;
	int m_nDown;
	CStatic m_staticText;				//未激活，已激活
	CStatic m_CurSelectText;			//当前选择的配置
	CStatic m_URLText_left;
	CStatic m_URLText_right;
	CEdit m_editName;					//创建配置输入配置名
	std::map<std::string, int> m_keyMap;
};
