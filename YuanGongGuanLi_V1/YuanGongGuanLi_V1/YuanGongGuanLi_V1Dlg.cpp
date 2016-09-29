
// YuanGongGuanLi_V1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YuanGongGuanLi_V1.h"
#include "YuanGongGuanLi_V1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CYuanGongGuanLi_V1Dlg �Ի���



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


// CYuanGongGuanLi_V1Dlg ��Ϣ�������

BOOL CYuanGongGuanLi_V1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	HWND hWnd = ::GetDlgItem(m_hWnd, IDC_DEPT);
	//m_comb.Attach(hWnd);
	m_comb.SubclassWindow(hWnd);
	hWnd = ::GetDlgItem(m_hWnd, IDC_LIST);
	//m_list.Attach(hWnd);
	m_list.SubclassWindow(hWnd);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_comb.AddString("��ѡ����");
	m_comb.AddString("������");
	m_comb.AddString("���ʲ�");
	m_comb.AddString("������");
	m_comb.AddString("���۲�");
	m_comb.SetCurSel(0);

	m_list.InsertColumn(0, "����", 0, 150);
	m_list.InsertColumn(1, "����", 0, 150);
	m_list.InsertColumn(2, "����", 0, 150);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYuanGongGuanLi_V1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		AfxMessageBox("����ѡ���ţ�");
		return;
	}
	unsigned nSel = m_list.GetItemCount(), i = 0;
	CString str;
	GetDlgItemText(IDC_NUM, str);
	while (i < nSel)
	{
		if (m_list.GetItemText(i, 0) == str)
		{
			AfxMessageBox("�˹����Ѿ����ڣ�");
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
		AfxMessageBox("��ѡ��һ����ɾ����");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	CString str = "ȷ��Ҫɾ�� " + m_list.GetItemText(nSel, 0) + " ��������";
	if (AfxMessageBox(str, MB_YESNO) == IDNO)
		return;
	m_list.DeleteItem(nSel);
}


void CYuanGongGuanLi_V1Dlg::OnBnClickedMod()
{
	if (m_comb.GetCurSel() == 0)
	{
		AfxMessageBox("����ѡ�������޸ģ�");
			return;
	}
	if (m_list.GetItemCount() == 0)
	{
		AfxMessageBox("��ѡ��һ�����޸ģ�");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	CString str = "ȷ��Ҫɾ�� " + m_list.GetItemText(nSel, 0) + " ��������";
	if (AfxMessageBox(str, MB_YESNO) == IDNO)
		return;
	GetDlgItemText(IDC_NAME, str);
	m_list.SetItemText(nSel, 1, str);
	GetDlgItemText(IDC_DEPT, str);
	m_list.SetItemText(nSel, 2, str);
}
