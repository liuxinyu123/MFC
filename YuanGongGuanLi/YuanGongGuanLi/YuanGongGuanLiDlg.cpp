
// YuanGongGuanLiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YuanGongGuanLi.h"
#include "YuanGongGuanLiDlg.h"
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


// CYuanGongGuanLiDlg �Ի���



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


// CYuanGongGuanLiDlg ��Ϣ�������

BOOL CYuanGongGuanLiDlg::OnInitDialog()
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

	CComboBox* pCom = (CComboBox*)GetDlgItem(IDC_DEPT);
	pCom->AddString("��ѡ����");
	pCom->AddString("������");
	pCom->AddString("����");
	pCom->AddString("���ʲ�");
	pCom->AddString("������");
	pCom->AddString("���۲�");
	pCom->SetCurSel(0);

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);

	pList->InsertColumn(0, "����", 0, 150);
	pList->InsertColumn(1, "����", 0, 140);
	pList->InsertColumn(2, "����", 0, 150);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYuanGongGuanLiDlg::OnPaint()
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
		AfxMessageBox("����ѡ���� ");
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
			AfxMessageBox("�ñ���Ѿ����ڣ�");
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
		AfxMessageBox("��ѡ��һ����ɾ����");
			return;
	}
	unsigned nSel = pList->GetSelectionMark();
	CString str = "ȷ��Ҫɾ�� " + pList->GetItemText(nSel, 0) + " ��������";
	if (AfxMessageBox(str, MB_YESNO) == IDYES)
		pList->DeleteItem(nSel);

}


void CYuanGongGuanLiDlg::OnBnClickedMod()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);

	if (!pList->GetSelectedCount())
	{
		AfxMessageBox("��ѡ��һ�����޸ģ�");
			return;
	}

	CComboBox* pCom = (CComboBox*)GetDlgItem(IDC_DEPT);
	if (pCom->GetCurSel() == 0)
	{
		AfxMessageBox("����ѡ�������޸ģ�");
		return;
	}

	unsigned nSel = pList->GetSelectionMark();
	CString str = "ȷ��Ҫ�޸� " + pList->GetItemText(nSel, 0) + " ��������";
	if (AfxMessageBox(str, MB_YESNO) == IDNO)
		return;
	GetDlgItemText(IDC_NAME, str);
	pList->SetItemText(nSel, 1, str);
	pCom->GetWindowTextA(str);
	pList->SetItemText(nSel, 2, str);


}
