
// MultiThread8Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultiThread8.h"
#include "MultiThread8Dlg.h"
#include "afxdialogex.h"
#include "afxmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CCriticalSection critical_section;
char g_Array[10];

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMultiThread8Dlg 对话框



CMultiThread8Dlg::CMultiThread8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultiThread8Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiThread8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_D, m_ctrlD);
	DDX_Control(pDX, IDC_W, m_ctrlW);
}

BEGIN_MESSAGE_MAP(CMultiThread8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_WRITEW, &CMultiThread8Dlg::OnBnClickedWritew)
	ON_BN_CLICKED(IDC_WRITED, &CMultiThread8Dlg::OnBnClickedWrited)
END_MESSAGE_MAP()


// CMultiThread8Dlg 消息处理程序

BOOL CMultiThread8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMultiThread8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMultiThread8Dlg::OnPaint()
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
HCURSOR CMultiThread8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT WriteW(LPVOID pParam)
{
	
	CEdit* pEdit = reinterpret_cast<CEdit*>(pParam);
	pEdit->SetWindowText("");
	critical_section.Lock();
	memset(g_Array, '\0', sizeof(g_Array));
	for (int i = 0; i < 10; ++i)
	{
		pEdit->SetWindowText(g_Array);
		g_Array[i] = 'W';
		
		Sleep(1000);
	}
	pEdit->SetWindowText(g_Array);
	critical_section.Unlock();
	return 0;
}

UINT WriteD(LPVOID pParam)
{
	
	CEdit* pEdit = reinterpret_cast<CEdit*>(pParam);
	pEdit->SetWindowText("");
	critical_section.Lock();
	memset(g_Array, '\0', sizeof(g_Array));
	for (int i = 0; i < 10; ++i)
	{
		pEdit->SetWindowText(g_Array);
		g_Array[i] = 'D';
		
		Sleep(1000);
	}
	pEdit->SetWindowText(g_Array);
	critical_section.Unlock();
	return 0;
}

void CMultiThread8Dlg::OnBnClickedWritew()
{
	CWinThread* pWriteW = AfxBeginThread(WriteW, &m_ctrlW, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	pWriteW->ResumeThread();
}



void CMultiThread8Dlg::OnBnClickedWrited()
{
	CWinThread* pWriteD = AfxBeginThread(WriteD, &m_ctrlD, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	pWriteD->ResumeThread();
}
