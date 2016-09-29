
// NotePadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NotePad.h"
#include "NotePadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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


// CNotePadDlg 对话框



CNotePadDlg::CNotePadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNotePadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotePadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT, m_edit);
}

BEGIN_MESSAGE_MAP(CNotePadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, &CNotePadDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, &CNotePadDlg::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE, &CNotePadDlg::OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, &CNotePadDlg::OnFileClose)
	ON_COMMAND(ID_FORMAT_FONT, &CNotePadDlg::OnFormatFont)
END_MESSAGE_MAP()


// CNotePadDlg 消息处理程序

BOOL CNotePadDlg::OnInitDialog()
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

void CNotePadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNotePadDlg::OnPaint()
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
HCURSOR CNotePadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotePadDlg::OnFileOpen()
{
	LPCTSTR szFilter = "文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFilter);
	if (IDCANCEL == dlg.DoModal())
		return;
	CFile file;
	if (!file.Open(dlg.GetPathName(), CFile::modeRead))
	{
		AfxMessageBox("文件打开失败！");
		return;
	}
	CFileStatus state;
	file.GetStatus(state);
	char *pText = new char[state.m_size + 1];
	if (!file.Read(pText, state.m_size))
	{
		AfxMessageBox("文件读取失败！");
		return;
	}
	pText[state.m_size] = 0;
	SetDlgItemText(IDC_TEXT, pText);
	delete []pText;
}


void CNotePadDlg::OnFileNew()
{
	CString str;
	GetDlgItemText(IDC_TEXT, str);
	if (str.IsEmpty())
		return;
	if (IDCANCEL == AfxMessageBox("是否保存当前文档？", MB_OKCANCEL))
		return;
	OnFileSave();
	SetDlgItemText(IDC_TEXT, "");
}


void CNotePadDlg::OnFileSave()
{
	// TODO:  在此添加命令处理程序代码
}


void CNotePadDlg::OnFileClose()
{
	EndDialog(IDCANCEL);
}


void CNotePadDlg::OnFormatFont()
{
	LOGFONT lf = { 0 };
	if (m_font.GetSafeHandle())
		m_font.GetLogFont(&lf);
	CFontDialog dlg(&lf);
	if (IDCANCEL == dlg.DoModal())
		return;
	
	dlg.GetCurrentFont(&lf);
	m_font.DeleteObject();
	m_font.CreateFontIndirectA(&lf);
	m_edit.SetFont(&m_font);
}
