
// YuanGongGuanLi_V1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YuanGongGuanLi_V1.h"
#include "YuanGongGuanLi_V1Dlg.h"
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


// CYuanGongGuanLi_V1Dlg 对话框



CYuanGongGuanLi_V1Dlg::CYuanGongGuanLi_V1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYuanGongGuanLi_V1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYuanGongGuanLi_V1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CYuanGongGuanLi_V1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CYuanGongGuanLi_V1Dlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &CYuanGongGuanLi_V1Dlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_MOD, &CYuanGongGuanLi_V1Dlg::OnBnClickedMod)
END_MESSAGE_MAP()


// CYuanGongGuanLi_V1Dlg 消息处理程序

BOOL CYuanGongGuanLi_V1Dlg::OnInitDialog()
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

	HWND hWnd = ::GetDlgItem(m_hWnd, IDC_DEPT);
	//m_comb.Attach(hWnd);
	m_comb.SubclassWindow(hWnd);
	hWnd = ::GetDlgItem(m_hWnd, IDC_LIST);
	//m_list.Attach(hWnd);
	m_list.SubclassWindow(hWnd);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_comb.AddString("请选择部门");
	m_comb.AddString("行政部");
	m_comb.AddString("人资部");
	m_comb.AddString("生产部");
	m_comb.AddString("销售部");
	m_comb.SetCurSel(0);

	m_list.InsertColumn(0, "工号", 0, 150);
	m_list.InsertColumn(1, "姓名", 0, 150);
	m_list.InsertColumn(2, "部门", 0, 150);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYuanGongGuanLi_V1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CYuanGongGuanLi_V1Dlg::OnPaint()
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
HCURSOR CYuanGongGuanLi_V1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CYuanGongGuanLi_V1Dlg::DestroyWindow()
{
	//m_comb.Detach();
	//m_list.Detach();
	m_comb.UnsubclassWindow();
	m_list.UnsubclassWindow();

	return CDialogEx::DestroyWindow();
}


void CYuanGongGuanLi_V1Dlg::OnBnClickedAdd()
{
	if (m_comb.GetCurSel() == 0)
	{
		AfxMessageBox("请先选择部门！");
		return;
	}
	unsigned nSel = m_list.GetItemCount(), i = 0;
	CString str;
	GetDlgItemText(IDC_NUM, str);
	while (i < nSel)
	{
		if (m_list.GetItemText(i, 0) == str)
		{
			AfxMessageBox("此工号已经存在！");
				return;
		}
		++i;
	}
	m_list.InsertItem(nSel, str);
	GetDlgItemText(IDC_NAME, str);
	m_list.SetItemText(nSel, 1, str);
	GetDlgItemText(IDC_DEPT, str);
	m_list.SetItemText(nSel, 2, str);

	SetDlgItemText(IDC_NUM, " ");
	SetDlgItemText(IDC_NAME, " ");
	m_comb.SetCurSel(0);
	GetDlgItem(IDC_NUM)->SetFocus();

}


void CYuanGongGuanLi_V1Dlg::OnBnClickedDel()
{
	if (m_list.GetSelectedCount() == 0)
	{
		AfxMessageBox("请选择一行再删除！");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	CString str = "确定要删除 " + m_list.GetItemText(nSel, 0) + " 的数据吗？";
	if (AfxMessageBox(str, MB_YESNO) == IDNO)
		return;
	m_list.DeleteItem(nSel);
}


void CYuanGongGuanLi_V1Dlg::OnBnClickedMod()
{
	if (m_comb.GetCurSel() == 0)
	{
		AfxMessageBox("请先选择部门再修改！");
			return;
	}
	if (m_list.GetItemCount() == 0)
	{
		AfxMessageBox("请选择一行再修改！");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	CString str = "确定要删除 " + m_list.GetItemText(nSel, 0) + " 的数据吗？";
	if (AfxMessageBox(str, MB_YESNO) == IDNO)
		return;
	GetDlgItemText(IDC_NAME, str);
	m_list.SetItemText(nSel, 1, str);
	GetDlgItemText(IDC_DEPT, str);
	m_list.SetItemText(nSel, 2, str);
}
