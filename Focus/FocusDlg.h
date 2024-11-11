
// FocusDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include <vector>
#include <map>
#include "afxwin.h"
#include "afxcmn.h"
// ������
struct Config {
	std::string config_name;
	int move_Up_times_left;					//���ƶ�����
    int move_Up_pixel_left;					//ÿ�������ƶ�������
	int Interval_left;						//�м���ͣ���
	int move_Down_times_left;				//ÿ���������������
	int move_Down_pixel_left;				//���ƶ�������	
	std::string hotkey_left;					// �ȼ�

	int move_Up_times_right;					//���ƶ�����
    int move_Up_pixel_right;					//ÿ�������ƶ�������
	int Interval_right;						//�м���ͣ���
	int move_Down_times_right;				//ÿ���������������
	int move_Down_pixel_right;				//���ƶ�������	
	std::string hotkey_right;					// �ȼ�

	Config()
	{
		config_name = "����1";
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

// CFocusDlg �Ի���
class CFocusDlg : public CDialogEx
{
// ����
public:
	CFocusDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FOCUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CStatic m_staticText;				//δ����Ѽ���
	CStatic m_CurSelectText;			//��ǰѡ�������
	CStatic m_URLText_left;
	CStatic m_URLText_right;
	CEdit m_editName;					//������������������
	std::map<std::string, int> m_keyMap;
};
