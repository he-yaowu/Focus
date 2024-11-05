
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
	int move_Up_times;					//上移动次数
    int move_Up_pixel;					//每毫秒上推多少像素
	int Interval;						//中间暂停间隔
	int move_Down_times;				//每毫秒回正多少像素
	int move_Down_pixel;				//下移动的像素	
	std::string hotkey;					// 热键
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
	void OnHotKeyPressed();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnSelchangeList1();
	bool m_bIsRunning;
	bool m_bActive;
	bool m_bUpComplete;
	bool m_bDownComplete;
	bool m_bInterval;
	long m_timeUpcomplete;
	int	m_HotKey;
	CListBox m_listConfig;
	CButton  m_button;
	CEdit  m_Editbox[8];
	POINT	 m_beginPos;
	void ReadConfig();
	void SaveConfig();
	void SetEditText(Config config);
	std::vector<Config> m_VecConfig;
	int m_nUp;
	int m_nDown;
	CStatic m_staticText;
	CStatic m_CurSelectText;
	CStatic m_URLText;
	CEdit m_editName;
	std::map<std::string, int> m_keyMap;
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
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};
