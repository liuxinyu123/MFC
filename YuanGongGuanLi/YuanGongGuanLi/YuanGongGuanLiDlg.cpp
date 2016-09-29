
// YuanGongGuanLiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YuanGongGuanLi.h"
#include "YuanGongGuanLiDlg.h"
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


// CYuanGongGuanLiDlg 对话框



CYuanGongGuanLiDlg::CYuanGongGuanLiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYuanGongGuanLiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYuanGongGuanLiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CYuanGongGuanLiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CYuanGongGuanLiDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &CYuanGongGuanLiDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_MOD, &CYuanGongGuanLiDlg::OnBnClickedMod)
END_MESSAGE_MAP()


// CYuanGongGuanLiDlg 消息处理程序

BOOL CYuanGongGuanLiDlg::OnInitDialog()
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

	CComboBox* pCom = (CComboBox*)GetDlgItem(IDC_DEPT);
	pCom->AddString("请选择部门");
	pCom->AddString("行政部");
	pCom->AddString("财务部");
	pCom->AddString("人资部");
	pCom->AddString("生产部");
	pCom->AddString("销售部");
	pCom->SetCurSel(0);

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);

	pList->InsertColumn(0, "工号", 0, 150);
	pList->InsertColumn(1, "姓名", 0, 140);
	pList->InsertColumn(2, "部门", 0, 150);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYuanGongGuanLiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CYuanGongGuanLiDlg::OnPaint()
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
HCURSOR CYuanGongGuanLiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CYuanGongGuanLiDlg::OnBnClickedAdd()
{
	CComboBox* pCom = (CComboBox*)GetDlgItem(IDC_DEPT);
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);

	unsigned nSel = pCom->GetCurSel();
	if (nSel == 0)
	{
		AfxMessageBox("请先选择部门 ");
			return;
	}

	unsigned nCount = pList->GetItemCount();
	unsigned i = 0;
	CString str;
	GetDlgItemText(IDC_NUM, str);
	while (i < nCount)
	{
		if (str == pList->GetItemText(i, 0))
		{
			AfxMessageBox("该编号已经存在！");
			return;
		}
		++i;
	}
	pList->InsertItem(nCount, str);
	GetDlgItemText(IDC_NAME, str);
	pList->SetItemText(nCount,1,str);
	GetDlgItemText(IDC_DEPT, str);
	pList->SetItemText(nCount, 2, str);

}


void CYuanGongGuanLiDlg::OnBnClickedDel()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);

	if (!pList->GetSelectedCount())
	{
		AfxMessageBox("请选择一行再删除！");
			return;
	}
	unsigned nSel = pList->GetSelectionMark();
	CString str = "确定要删除 " + pList->GetItemText(nSel, 0) + " 的数据吗？";
	if (AfxMessageBox(str, MB_YESNO) == IDYES)
		pList->DeleteItem(nSel);

}


void CYuanGongGuanLiDlg::OnBnClickedMod()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);

	if (!pList->GetSelectedCount())
	{
		AfxMessageBox("请选择一行再修改！");
			return;
	}

	CComboBox* pCom = (CComboBox*)GetDlgItem(IDC_DEPT);
	if (pCom->GetCurSel() == 0)
	{
		AfxMessageBox("请先选择部门再修改！");
		return;
	}

	unsigned nSel = pList->GetSelectionMark();
	CString str = "确定要修改 " + pList->GetItemText(nSel, 0) + " 的数据吗？";
	if (AfxMessageBox(str, MB_YESNO) == IDNO)
		return;
	GetDlgItemText(IDC_NAME, str);
	pList->SetItemText(nSel, 1, str);
	pCom->GetWindowTextA(str);
	pList->SetItemText(nSel, 2, str);


}
