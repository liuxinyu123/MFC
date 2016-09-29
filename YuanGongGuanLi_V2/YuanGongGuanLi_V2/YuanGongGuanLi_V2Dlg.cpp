
// YuanGongGuanLi_V2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YuanGongGuanLi_V2.h"
#include "YuanGongGuanLi_V2Dlg.h"
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


// CYuanGongGuanLi_V2Dlg 对话框



CYuanGongGuanLi_V2Dlg::CYuanGongGuanLi_V2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYuanGongGuanLi_V2Dlg::IDD, pParent)
	, m_bEnglish(FALSE)
	, m_bFrench(FALSE)
	, m_bJanpanese(FALSE)
	, m_bKorean(FALSE)
	, m_nGrade(0)
	, m_nSex(0)
	, m_szNum(_T(""))
	, m_szName(_T(""))
	, m_date(COleDateTime::GetCurrentTime())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYuanGongGuanLi_V2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ENGLISH, m_bEnglish);
	DDX_Check(pDX, IDC_FRENCH, m_bFrench);
	DDX_Check(pDX, IDC_JANPANESE, m_bJanpanese);
	DDX_Check(pDX, IDC_KOREAN, m_bKorean);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Radio(pDX, IDC_GRADE, m_nGrade);
	//  DDX_Radio(pDX, IDC_SEX, m_bSex);
	DDX_Radio(pDX, IDC_SEX, m_nSex);
	DDX_Text(pDX, IDC_NUM, m_szNum);
	DDX_Text(pDX, IDC_NAME, m_szName);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_date);
}

BEGIN_MESSAGE_MAP(CYuanGongGuanLi_V2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CYuanGongGuanLi_V2Dlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CYuanGongGuanLi_V2Dlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_MODIFY, &CYuanGongGuanLi_V2Dlg::OnBnClickedModify)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CYuanGongGuanLi_V2Dlg::OnNMClickList)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CYuanGongGuanLi_V2Dlg 消息处理程序

BOOL CYuanGongGuanLi_V2Dlg::OnInitDialog()
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

	m_list.InsertColumn(0, "工号", 0, 90);
	m_list.InsertColumn(1, "姓名", 0, 90);
	m_list.InsertColumn(2, "性别", 0, 40);
	m_list.InsertColumn(3, "入职日期", 0, 100);
	m_list.InsertColumn(4, "学历", 0, 60);
	m_list.InsertColumn(5, "外语", 0, 150);
	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	ReadInfo();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYuanGongGuanLi_V2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CYuanGongGuanLi_V2Dlg::OnPaint()
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
HCURSOR CYuanGongGuanLi_V2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CYuanGongGuanLi_V2Dlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	unsigned i= 0,nSel = m_list.GetItemCount();
	while (i < nSel)
	{
		if (m_szNum == m_list.GetItemText(i, 0))
		{
			AfxMessageBox("此工号已经存在！");
			return;
		}
		++i;
	}
	m_list.InsertItem(nSel, m_szNum);
	m_list.SetItemText(nSel, 1, m_szName);
	m_list.SetItemText(nSel, 2, m_nSex ? "女" : "男");
	m_list.SetItemText(nSel, 3, m_date.Format("%Y/%m/%d"));
	CString str;
	switch (m_nGrade)
	{
	case 0:
		str = "高中";
		break;
	case 1:
		str = "本科";
		break;
	case 2:
		str = "硕士";
		break;
	case 3:
		str = "博士";
		break;
	default:
		str = "高中";
		break;
	}
	m_list.SetItemText(nSel, 4, str);
	str = "";
	(((str += m_bEnglish ? "英语 " : "") += m_bJanpanese ? "日语 " : "")
		+= m_bFrench ? "法语 " : "" )+= m_bKorean ? "韩语 " : "";
	m_list.SetItemText(nSel, 5, str);
/*	m_list.SetItemText(nSel, 2, m_szName);
	m_list.SetItemText(nSel, 2, m_szName);*/
	//UpdateData(FALSE);

}


void CYuanGongGuanLi_V2Dlg::OnBnClickedDelete()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox("请选中一行再删除！");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	if (IDOK == AfxMessageBox("确定要删除吗？", MB_OKCANCEL))
	{
		m_list.DeleteItem(nSel);
	}
}


void CYuanGongGuanLi_V2Dlg::OnBnClickedModify()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox("请选中一行再修改！");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	if (IDCANCEL == AfxMessageBox("确定要修改吗？", MB_OKCANCEL))
		return;
	UpdateData();
	m_list.SetItemText(nSel,0, m_szNum);
	m_list.SetItemText(nSel, 1, m_szName);
	m_list.SetItemText(nSel, 2, m_nSex ? "女" : "男");
	m_list.SetItemText(nSel, 3, m_date.Format("%Y/%m/%d"));
	CString str;
	switch (m_nGrade)
	{
	case 0:
		str = "高中";
		break;
	case 1:
		str = "本科";
		break;
	case 2:
		str = "硕士";
		break;
	case 3:
		str = "博士";
		break;
	default:
		str = "高中";
		break;
	}
	m_list.SetItemText(nSel, 4, str);
	str = "";
	(((str += m_bEnglish ? "英语 " : "") += m_bJanpanese ? " 日语 " : "")
		+= m_bFrench ? " 法语 " : "") += m_bKorean ? " 韩语" : "";
	m_list.SetItemText(nSel, 5, str);
	
}


void CYuanGongGuanLi_V2Dlg::ReadSeclectRow(unsigned nSel)
{
	m_szNum = m_list.GetItemText(nSel, 0);
	m_szName = m_list.GetItemText(nSel, 1);
	CString str;
	str = m_list.GetItemText(nSel, 2);
	if (str == "男")
		m_nSex = 0;
	else
		m_nSex = 1;
	str = m_list.GetItemText(nSel, 3);
	m_date.ParseDateTime(str);
	str = m_list.GetItemText(nSel, 4);
	if (str == "高中")
		m_nGrade = 0;
	else if (str == "本科")
		m_nGrade = 1;
	else if (str == "硕士")
		m_nGrade = 2;
	else
		m_nGrade = 3;

	str = m_list.GetItemText(nSel, 5);
	m_bEnglish = static_cast<bool>(str.Find("英") + 1);
	m_bJanpanese = static_cast<bool>(str.Find("日") + 1);
	m_bFrench = static_cast<bool>(str.Find("法") + 1);
	m_bKorean = static_cast<bool>(str.Find("韩") + 1);
	
	UpdateData(FALSE);

}


void CYuanGongGuanLi_V2Dlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (!m_list.GetItemCount())
		return;
	unsigned nSel = m_list.GetSelectionMark();
	ReadSeclectRow(nSel);
	*pResult = 0;
}


void CYuanGongGuanLi_V2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	CFile file;
	if (!file.Open("./info.dat", CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox("文件创建时失效！");
		return;
	}
	unsigned i = 0, nCount = m_list.GetItemCount();
	SInfo info;
	CString str, szGrade = "高中本科硕士博士";
	
	while (i < nCount)
	{
		m_list.GetItemText(i, 0, info.sNum, sizeof(info.sNum));
		m_list.GetItemText(i, 1, info.sName, sizeof(info.sName));
		str = m_list.GetItemText(i,2);
		info.nSex = (str == "男") ? 0 : 1;
		m_list.GetItemText(i, 3, info.sDate, sizeof(info.sDate));
		str = m_list.GetItemText(i, 4);
		info.nGrade = static_cast<unsigned>(szGrade.Find(str)/4);
		str = m_list.GetItemText(i, 5);
		info.sbLanguage[0] = static_cast<bool>(str.Find("英") + 1);
		info.sbLanguage[1] = static_cast<bool>(str.Find("日") + 1);
		info.sbLanguage[2] = static_cast<bool>(str.Find("法") + 1);
		info.sbLanguage[3] = static_cast<bool>(str.Find("韩") + 1);
		file.Write(&info, sizeof(info));
		++i;
	}
}


void CYuanGongGuanLi_V2Dlg::ReadInfo()
{
	CFile file;
	if (!file.Open("info.dat", CFile::modeRead | CFile::shareDenyNone))
		//AfxMessageBox("文件初始化失败！");
		return;
	
	SInfo info;
 	unsigned i = 0;
	CString str, szGrade = "高中本科硕士博士";
	while (file.Read(&info, sizeof(info)) == sizeof(info))
	{
		m_list.InsertItem(i, info.sNum);
		m_list.SetItemText(i, 1, info.sName);
		m_list.SetItemText(i, 2, info.nSex ? "女" : "男");
		m_list.SetItemText(i, 3, info.sDate);
		if (info.nGrade == 0)
			str = "高中";
		if (info.nGrade == 1)
			str = "本科";
		if (info.nGrade == 2)
			str = "硕士";
		if (info.nGrade == 3)
			str = "博士";

		//str.Format("%s", szGrade.GetAt(2 * info.nGrade));
		m_list.SetItemText(i, 4, str);
		str = "";
		(((str += info.sbLanguage[0] ? "英语" : "") += info.sbLanguage[1] ? " 日语" : "") += info.sbLanguage[2] ?
			" 法语" : "") += info.sbLanguage[3] ? " 韩语" : "";
		m_list.SetItemText(i, 5, str);
		++i;
	}
}
