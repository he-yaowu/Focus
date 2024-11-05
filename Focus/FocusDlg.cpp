
// FocusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Focus.h"
#include "FocusDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFocusDlg 对话框

// 定义定时器的ID
#define TIMER_ID 1

const char* CONFIG_FILE = "config.txt"; // 配置文件路径
// 从配置文件读取设置
void CFocusDlg::ReadConfig() 
{
	Config config = {"配置1", 10, 120, 20, 10, 26, "R"}; // 默认设置
    std::ifstream inFile(CONFIG_FILE);
	if (!inFile.is_open())
	{
		m_VecConfig.push_back(config);
		m_listConfig.AddString(config.config_name.c_str());
		CString str;
		str.Format("%d",config.move_Up_times);
		m_Editbox[2].SetWindowTextA(str.GetString());
		str.Format("%d",config.move_Up_pixel);
		m_Editbox[3].SetWindowTextA(str.GetString());
		str.Format("%d",config.Interval);
		m_Editbox[4].SetWindowTextA(str.GetString());
		str.Format("%d",config.move_Down_times);
		m_Editbox[5].SetWindowTextA(str.GetString());
		str.Format("%d",config.move_Down_pixel);
		m_Editbox[6].SetWindowTextA(str.GetString());

		str.Format("%s",config.hotkey.c_str());
		m_Editbox[7].SetWindowTextA(str.GetString());

		m_listConfig.SetCurSel(0);

		str.Format("当前配置：%s",config.config_name.c_str());
		m_CurSelectText.SetWindowTextA(str.GetString());
		return;
	}
	m_VecConfig.clear();
	while (inFile.good()) {
		inFile >> config.config_name >> config.move_Up_times >> config.move_Up_pixel >> config.Interval >> config.move_Down_times >> config.move_Down_pixel >> config.hotkey;
		m_VecConfig.push_back(config);
    }
	inFile.close();
	for(size_t i = 0; i < m_VecConfig.size(); i++)
	{
		Config config = m_VecConfig[i];
		m_listConfig.AddString(config.config_name.c_str());
		if(i == 0)
		{
			CString str;
			str.Format("%d",m_VecConfig[0].move_Up_times);
			m_Editbox[2].SetWindowTextA(str.GetString());
			str.Format("%d",m_VecConfig[0].move_Up_pixel);
			m_Editbox[3].SetWindowTextA(str.GetString());
			str.Format("%d",m_VecConfig[0].Interval);
			m_Editbox[4].SetWindowTextA(str.GetString());
			str.Format("%d",m_VecConfig[0].move_Down_times);
			m_Editbox[5].SetWindowTextA(str.GetString());
			str.Format("%d",m_VecConfig[0].move_Down_pixel);
			m_Editbox[6].SetWindowTextA(str.GetString());
			str.Format("%s",m_VecConfig[0].hotkey.c_str());
			m_Editbox[7].SetWindowTextA(str.GetString());
			m_listConfig.SetCurSel(i);

			str.Format("当前配置：%s",config.config_name.c_str());
			m_CurSelectText.SetWindowTextA(str.GetString());
		}
	}
}

void CFocusDlg::SaveConfig()
{
	std::ofstream inFile(CONFIG_FILE);
	for(size_t i = 0; i < m_VecConfig.size(); i++)
	{
		if(i == m_VecConfig.size() -1)
			inFile << m_VecConfig[i].config_name << " " << m_VecConfig[i].move_Up_times << " " << m_VecConfig[i].move_Up_pixel << " " << m_VecConfig[i].Interval << " " << m_VecConfig[i].move_Down_times << " " << m_VecConfig[i].move_Down_pixel << " " << m_VecConfig[i].hotkey ;
		else
			inFile << m_VecConfig[i].config_name << " " << m_VecConfig[i].move_Up_times << " " << m_VecConfig[i].move_Up_pixel << " " << m_VecConfig[i].Interval << " " << m_VecConfig[i].move_Down_times << " " << m_VecConfig[i].move_Down_pixel << " " << m_VecConfig[i].hotkey <<std::endl;
	}
	inFile.close();
}

CFocusDlg::CFocusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFocusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsRunning = false;
	m_bActive = false;
	m_bUpComplete = false;
	m_bDownComplete = false;
	m_bInterval = false;
	m_nUp = 0;
	m_nDown = 0;
	m_keyMap["A"] = 65;m_keyMap["a"] = 65;
	m_keyMap["B"] = 66;m_keyMap["b"] = 66;
	m_keyMap["C"] = 67;m_keyMap["c"] = 67;
	m_keyMap["D"] = 68;m_keyMap["d"] = 68;
	m_keyMap["D"] = 69;m_keyMap["e"] = 69;
	m_keyMap["F"] = 70;m_keyMap["f"] = 70;
	m_keyMap["G"] = 71;m_keyMap["g"] = 71;
	m_keyMap["H"] = 72;m_keyMap["h"] = 72;
	m_keyMap["I"] = 73;m_keyMap["i"] = 73;
	m_keyMap["J"] = 74;m_keyMap["j"] = 74;
	m_keyMap["K"] = 75;m_keyMap["k"] = 75;
	m_keyMap["L"] = 76;m_keyMap["l"] = 76;
	m_keyMap["M"] = 77;m_keyMap["m"] = 77;
	m_keyMap["N"] = 78;m_keyMap["n"] = 78;
	m_keyMap["O"] = 79;m_keyMap["o"] = 79;
	m_keyMap["P"] = 80;m_keyMap["p"] = 80;
	m_keyMap["Q"] = 81;m_keyMap["q"] = 81;
	m_keyMap["R"] = 82;m_keyMap["r"] = 82;
	m_keyMap["S"] = 83;m_keyMap["s"] = 83;
	m_keyMap["T"] = 84;m_keyMap["t"] = 84;
	m_keyMap["U"] = 85;m_keyMap["u"] = 85;
	m_keyMap["V"] = 86;m_keyMap["v"] = 86;
	m_keyMap["W"] = 87;m_keyMap["w"] = 87;
	m_keyMap["X"] = 88;m_keyMap["x"] = 88;
	m_keyMap["Y"] = 89;m_keyMap["y"] = 89;
	m_keyMap["Z"] = 90;m_keyMap["z"] = 90;
}

void CFocusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listConfig);
	DDX_Control(pDX, IDOK, m_button);
	DDX_Control(pDX, IDC_EDIT1, m_editName);
	DDX_Control(pDX, IDC_EDIT3, m_Editbox[2]);
	DDX_Control(pDX, IDC_EDIT4, m_Editbox[3]);
	DDX_Control(pDX, IDC_EDIT5, m_Editbox[4]);
	DDX_Control(pDX, IDC_EDIT6, m_Editbox[5]);
	DDX_Control(pDX, IDC_EDIT7, m_Editbox[6]);
	DDX_Control(pDX, IDC_EDIT8, m_Editbox[7]);
	DDX_Control(pDX, IDC_STATIC2, m_staticText);
	DDX_Control(pDX, IDC_STATIC1, m_CurSelectText);
	DDX_Control(pDX, IDC_STATIC3, m_URLText);
}

BEGIN_MESSAGE_MAP(CFocusDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_MESSAGE(WM_HOTKEY, &CFocusDlg::OnHotKey)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFocusDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFocusDlg::OnBnClickedCancel)
	ON_WM_TIMER() // 添加WM_TIMER的消息映射
	ON_LBN_DBLCLK(IDC_LIST1, &CFocusDlg::OnLbnDblclkList1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CFocusDlg::OnLbnSelchangeList1)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CFocusDlg::OnBnClickedButton_New)
	ON_BN_CLICKED(IDC_BUTTON3, &CFocusDlg::OnBnClickedButton_Delete)
	ON_BN_CLICKED(IDC_BUTTON4, &CFocusDlg::OnBnClickedButton_Default)
	ON_EN_CHANGE(IDC_EDIT3, &CFocusDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CFocusDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CFocusDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CFocusDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CFocusDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CFocusDlg::OnEnChangeEdit8)	
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// CFocusDlg 消息处理程序

BOOL CFocusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ReadConfig();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

HBRUSH CFocusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_STATIC2) { // 检查控件ID
		// 设置文本颜色
		if(m_bActive == false)
			pDC->SetTextColor(RGB(255, 0, 0)); // 红色
		//pDC->SetBkColor(RGB(0, 255, 0));	//绿色
		else
			pDC->SetTextColor(RGB(0, 155, 0)); // 绿色
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		pDC->SetTextColor(RGB(0, 155, 0)); // 绿色
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC3)
	{
		pDC->SetTextColor(RGB(0, 0, 200)); // 绿色
	}
	return hbr;
}


void CFocusDlg::OnHotKeyPressed()
{
    if (m_bIsRunning || m_bActive == false)
    {
        //AfxMessageBox(_T("任务正在执行，请稍候..."));
        return;
    }

    m_bIsRunning = TRUE;
	GetCursorPos(&m_beginPos); 

    // 在此添加您要执行的任务代码
    // ...
    // 任务完成后，重置标志位
    //m_bIsRunning = FALSE;
	m_bUpComplete = false;
	m_bDownComplete = false;
	m_nUp = 0;
	m_nDown = 0;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFocusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFocusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFocusDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	 // 处理键盘按键释放事件
    // nChar 参数包含了被释放的键的虚拟键码
    // nRepCnt 参数表示按键被按住然后释放的次数
    // nFlags 参数包含了额外的信息，例如是否同时按下了Shift键

    // 例如，可以在这里根据nChar的值来执行不同的操作
    switch(nChar)
    {
        case 'A':
            // 处理'A'键被释放的事件
            break;
        // ... 其他case处理 ...
    }

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}

// 移动鼠标
void MoveMouseUp(int yOffset) 
{
	POINT p;
	GetCursorPos(&p);
	//SetCursorPos(p.x, p.y - yOffset);
	mouse_event(MOUSEEVENTF_MOVE, 0, -yOffset, 0, 0);
}

void MoveMouseDown(int yOffset) 
{
	POINT p;
	GetCursorPos(&p);
	//SetCursorPos(p.x, p.y + yOffset);
	mouse_event(MOUSEEVENTF_MOVE, 0, yOffset, 0, 0);
}

// 启动定时器
void CFocusDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (nIDEvent == TIMER_ID)
    {
       // 定时器事件处理代码
		if(m_bIsRunning == true)
		{
			CString str;
			m_Editbox[2].GetWindowTextA(str);
			int move_up_times = atoi(str.GetString());
			m_Editbox[3].GetWindowTextA(str);
			int up_pixel = atoi(str.GetString());

			m_Editbox[4].GetWindowTextA(str);
			int Interval = atoi(str.GetString());

			m_Editbox[5].GetWindowTextA(str);
			int move_down_times = atoi(str.GetString());
			m_Editbox[6].GetWindowTextA(str);
			int down_pixel = atoi(str.GetString());

			POINT p;
			GetCursorPos(&p);
			
			if(m_bUpComplete == false)
			{
				//if((m_beginPos.y - move_up) <  p.y && p.y > 0)
				if(m_nUp < move_up_times)
				{
					m_nUp++;
					MoveMouseUp(up_pixel);
				}
				else
				{
					m_bUpComplete = true;
					m_timeUpcomplete = GetTickCount();
					GetCursorPos(&m_beginPos);
				}
			}

			if(int(GetTickCount() - m_timeUpcomplete) >= Interval && m_bUpComplete == true)
			{
				m_bInterval = true;
			}
			if(m_bDownComplete == false && m_bUpComplete == true && m_bInterval == true)
			{
				//int screenHeight = GetSystemMetrics(SM_CYSCREEN)-5;
				//if((m_beginPos.y + move_Down) >  p.y && p.y <= screenHeight)
				if(m_nDown < move_down_times)
				{
					m_nDown++;
					MoveMouseDown(down_pixel);
				}
				else
					m_bDownComplete = true;
			}
			if(m_bUpComplete == true && m_bDownComplete == true)
			{
				m_bIsRunning = false;
				m_bInterval = false;
				m_nUp = 0;
				m_nDown = 0;
			}
		}
    }
    CDialogEx::OnTimer(nIDEvent);
}

LRESULT  CFocusDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
    if (wParam == 100)
    {
        OnHotKeyPressed();
    }
	return 0; // 返回0表示消息已被处理
}

void CFocusDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UnregisterHotKey(m_hWnd, 100);
	if(m_bActive == false)
	{		
		SetTimer(TIMER_ID, 1, NULL);
		m_button.SetWindowTextA("暂停");
		m_bActive = true;
		m_staticText.SetWindowText("已 激 活");
		
		CString str;
		m_Editbox[7].GetWindowTextA(str);

		// 注册快捷键，例如 'R' 键
		int hotkey = m_keyMap[str.GetString()];
		RegisterHotKey(m_hWnd, 100, 0, hotkey);  // 'm_HotKey' 是用户选择的快捷键
	}
	else
	{
		KillTimer(TIMER_ID);
		m_button.SetWindowTextA("激活");
		m_bActive = false;
		m_staticText.SetWindowText("未 激 活");
	}
}


void CFocusDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CFocusDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CFocusDlg::OnLbnSelchangeList1()
{
	const int index = m_listConfig.GetCurSel();
	if(index < 0 || index >= (int)m_VecConfig.size())
		return;
	CString str;
	str.Format("%d",m_VecConfig[index].move_Up_times);
	m_Editbox[2].SetWindowTextA(str.GetString());
	str.Format("%d",m_VecConfig[index].move_Up_pixel);
	m_Editbox[3].SetWindowTextA(str.GetString());
	str.Format("%d",m_VecConfig[index].Interval);
	m_Editbox[4].SetWindowTextA(str.GetString());
	str.Format("%d",m_VecConfig[index].move_Down_times);
	m_Editbox[5].SetWindowTextA(str.GetString());
	str.Format("%d",m_VecConfig[index].move_Down_pixel);
	m_Editbox[6].SetWindowTextA(str.GetString());
	str.Format("%s",m_VecConfig[index].hotkey.c_str());
	m_Editbox[7].SetWindowTextA(str.GetString());

	if(m_bActive == false)
	{
		UnregisterHotKey(m_hWnd, 100);
		m_Editbox[7].GetWindowTextA(str);

		// 注册快捷键，例如 'R' 键
		int hotkey = m_keyMap[str.GetString()];
		RegisterHotKey(m_hWnd, 100, 0, hotkey);  // 'm_HotKey' 是用户选择的快捷键
	}
	CString select;
	m_listConfig.GetText(index, select);
	str.Format("当前配置：%s",select.GetString());
	m_CurSelectText.SetWindowTextA(str.GetString());
}

void CFocusDlg::OnBnClickedButton_New()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取列表项的位置
	m_editName.ShowWindow(SW_SHOW);
    m_editName.SetFont(m_listConfig.GetFont());
	m_editName.SetWindowTextA("");
    m_editName.SetFocus();
    m_editName.SetSel(0, -1);
}

void CFocusDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	 // 检查点击位置是否在CStatic控件内
    CRect rectStatic;
    m_URLText.GetWindowRect(&rectStatic); // 替换m_staticControl为你的CStatic控件的成员变量
    ScreenToClient(&rectStatic);

    if (rectStatic.PtInRect(point))
    {
        // 点击位置在CStatic控件内，打开网页
        ShellExecute(NULL, _T("open"), _T("https://www.zqgame.com"), NULL, NULL, SW_SHOWNORMAL);
		return;
    }

    // 你的代码逻辑
	CString strText;
	m_editName.GetWindowTextA(strText);
	if(strText == "")
		return;
	m_listConfig.AddString(strText);
	Config config = {"配置1", 10, 120, 20, 10, 26, "R"}; // 默认设置
	config.config_name = strText.GetString();
	m_VecConfig.push_back(config);
	int count = m_listConfig.GetCount();
	m_listConfig.SetCurSel(count-1);
	SetEditText(config);
	SaveConfig();

	m_editName.ShowWindow(SW_HIDE);
	m_editName.SetWindowTextA("");
}

void CFocusDlg::OnBnClickedButton_Delete()
{
	int nResponse = MessageBox(_T("你确定要删除吗？"), _T("确认"), MB_YESNO);
	if (nResponse == IDYES)
	{
		// 用户点击了“是”按钮
		// 在这里执行相应的操作
		int index = m_listConfig.GetCurSel();
		if(index <= -1)
			return;
		m_listConfig.DeleteString(index);
		m_VecConfig.erase(m_VecConfig.begin()+index);

		SaveConfig();
	}
	else if(nResponse == IDNO)
	{
		 // 用户点击了“否”按钮
		 // 在这里执行相应的操作
	}
}

void CFocusDlg::OnBnClickedButton_Default()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_listConfig.GetCurSel();
	if(index <= -1)
		return;
	Config config = {"配置1", 10, 120, 20, 10, 26, "R"}; // 默认设置
	SetEditText(config);
}

void CFocusDlg::SetEditText(Config config)
{
	CString str;
	str.Format("%d",config.move_Up_times);
	m_Editbox[2].SetWindowTextA(str.GetString());
	str.Format("%d",config.move_Up_pixel);
	m_Editbox[3].SetWindowTextA(str.GetString());
	str.Format("%d",config.Interval);
	m_Editbox[4].SetWindowTextA(str.GetString());
	str.Format("%d",config.move_Down_times);
	m_Editbox[5].SetWindowTextA(str.GetString());
	str.Format("%d",config.move_Down_pixel);
	m_Editbox[6].SetWindowTextA(str.GetString());

	str.Format("%s",config.hotkey.c_str());
	m_Editbox[7].SetWindowTextA(str.GetString());
}
BOOL CFocusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CString strText;
		m_editName.GetWindowTextA(strText);
		if(strText != "")
		{
			m_listConfig.AddString(strText);
			Config config = {"配置1", 10, 120, 20, 10, 26, "R"}; // 默认设置
			config.config_name = strText.GetString();
			m_VecConfig.push_back(config);
			int count = m_listConfig.GetCount();
			m_listConfig.SetCurSel(count-1);
			SetEditText(config);
			SaveConfig();

			m_editName.ShowWindow(SW_HIDE);
			m_editName.SetWindowTextA("");
			return TRUE;
		}
		else
		{
			m_editName.ShowWindow(SW_HIDE);
			m_editName.SetWindowTextA("");
		}
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



void CFocusDlg::OnEnChangeEdit3()
{
	const int index = m_listConfig.GetCurSel();
	if(index < 0 || index >= (int)m_VecConfig.size())
		return;
	CString str;
	m_Editbox[2].GetWindowTextA(str);
	if(str == "")
		return;
	int value = atoi(str.GetString());
	if(value > 0)
	{
		m_VecConfig[index].move_Up_times = value;
		SaveConfig();
	}
}


void CFocusDlg::OnEnChangeEdit4()
{
	const int index = m_listConfig.GetCurSel();
	if(index < 0 || index >= (int)m_VecConfig.size())
		return;
	CString str;
	m_Editbox[3].GetWindowTextA(str);
	if(str == "")
		return;
	int value = atoi(str.GetString());
	if(value > 0)
	{
		m_VecConfig[index].move_Up_pixel = value;
		SaveConfig();
	}
}


void CFocusDlg::OnEnChangeEdit5()
{
	const int index = m_listConfig.GetCurSel();
	if(index < 0 || index >= (int)m_VecConfig.size())
		return;
	CString str;
	m_Editbox[4].GetWindowTextA(str);
	if(str == "")
		return;
	int value = atoi(str.GetString());
	if(value > 0)
	{
		m_VecConfig[index].Interval = value;
		SaveConfig();
	}
}


void CFocusDlg::OnEnChangeEdit6()
{
	const int index = m_listConfig.GetCurSel();
	if(index < 0 || index >= (int)m_VecConfig.size())
		return;
	CString str;
	m_Editbox[5].GetWindowTextA(str);
	if(str == "")
		return;
	int value = atoi(str.GetString());
	if(value > 0)
	{
		m_VecConfig[index].move_Down_times = value;
		SaveConfig();
	}
}


void CFocusDlg::OnEnChangeEdit7()
{
	const int index = m_listConfig.GetCurSel();
	if(index < 0 || index >= (int)m_VecConfig.size())
		return;
	CString str;
	m_Editbox[6].GetWindowTextA(str);
	if(str == "")
		return;
	int value = atoi(str.GetString());
	if(value > 0)
	{
		m_VecConfig[index].move_Down_pixel = value;
		SaveConfig();
	}
}


void CFocusDlg::OnEnChangeEdit8()
{
	const int index = m_listConfig.GetCurSel();
	if(index < 0 || index >= (int)m_VecConfig.size())
		return;
	CString str;
	m_Editbox[7].GetWindowText(str);
	if(str == "")
		return;
	std::string sChar = str.GetString();
	int asciiValue = static_cast<int>(sChar[0]);
	if((asciiValue >= 'A' && asciiValue <= 'Z') || (asciiValue >= 'a' && asciiValue <= 'z'))
	{
		// 如果输入超过一个字符，将其截断
		int len = str.GetLength();
		if (str.GetLength() > 1)
		{
			str = str.Left(1);
			m_Editbox[7].SetWindowText(str);
			// 将编辑控件的焦点设置回到开始位置
			m_Editbox[7].SetSel(0, 1);
		}
		m_VecConfig[index].hotkey = str;
		SaveConfig();
	}
	else
	{
		m_Editbox[7].SetWindowText("");
		m_Editbox[7].SetSel(0, 0);
		return;
	}
}

//取消F1 弹帮助窗口
BOOL CFocusDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CDialogEx::OnHelpInfo(pHelpInfo);
}
