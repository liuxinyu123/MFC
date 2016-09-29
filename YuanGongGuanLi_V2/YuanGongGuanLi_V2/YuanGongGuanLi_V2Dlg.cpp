
// YuanGongGuanLi_V2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YuanGongGuanLi_V2.h"
#include "YuanGongGuanLi_V2Dlg.h"
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


// CYuanGongGuanLi_V2Dlg �Ի���



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


// CYuanGongGuanLi_V2Dlg ��Ϣ�������

BOOL CYuanGongGuanLi_V2Dlg::OnInitDialog()
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

	m_list.InsertColumn(0, "����", 0, 90);
	m_list.InsertColumn(1, "����", 0, 90);
	m_list.InsertColumn(2, "�Ա�", 0, 40);
	m_list.InsertColumn(3, "��ְ����", 0, 100);
	m_list.InsertColumn(4, "ѧ��", 0, 60);
	m_list.InsertColumn(5, "����", 0, 150);
	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	ReadInfo();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYuanGongGuanLi_V2Dlg::OnPaint()
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
			AfxMessageBox("�˹����Ѿ����ڣ�");
			return;
		}
		++i;
	}
	m_list.InsertItem(nSel, m_szNum);
	m_list.SetItemText(nSel, 1, m_szName);
	m_list.SetItemText(nSel, 2, m_nSex ? "Ů" : "��");
	m_list.SetItemText(nSel, 3, m_date.Format("%Y/%m/%d"));
	CString str;
	switch (m_nGrade)
	{
	case 0:
		str = "����";
		break;
	case 1:
		str = "����";
		break;
	case 2:
		str = "˶ʿ";
		break;
	case 3:
		str = "��ʿ";
		break;
	default:
		str = "����";
		break;
	}
	m_list.SetItemText(nSel, 4, str);
	str = "";
	(((str += m_bEnglish ? "Ӣ�� " : "") += m_bJanpanese ? "���� " : "")
		+= m_bFrench ? "���� " : "" )+= m_bKorean ? "���� " : "";
	m_list.SetItemText(nSel, 5, str);
/*	m_list.SetItemText(nSel, 2, m_szName);
	m_list.SetItemText(nSel, 2, m_szName);*/
	//UpdateData(FALSE);

}


void CYuanGongGuanLi_V2Dlg::OnBnClickedDelete()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox("��ѡ��һ����ɾ����");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	if (IDOK == AfxMessageBox("ȷ��Ҫɾ����", MB_OKCANCEL))
	{
		m_list.DeleteItem(nSel);
	}
}


void CYuanGongGuanLi_V2Dlg::OnBnClickedModify()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox("��ѡ��һ�����޸ģ�");
		return;
	}
	unsigned nSel = m_list.GetSelectionMark();
	if (IDCANCEL == AfxMessageBox("ȷ��Ҫ�޸���", MB_OKCANCEL))
		return;
	UpdateData();
	m_list.SetItemText(nSel,0, m_szNum);
	m_list.SetItemText(nSel, 1, m_szName);
	m_list.SetItemText(nSel, 2, m_nSex ? "Ů" : "��");
	m_list.SetItemText(nSel, 3, m_date.Format("%Y/%m/%d"));
	CString str;
	switch (m_nGrade)
	{
	case 0:
		str = "����";
		break;
	case 1:
		str = "����";
		break;
	case 2:
		str = "˶ʿ";
		break;
	case 3:
		str = "��ʿ";
		break;
	default:
		str = "����";
		break;
	}
	m_list.SetItemText(nSel, 4, str);
	str = "";
	(((str += m_bEnglish ? "Ӣ�� " : "") += m_bJanpanese ? " ���� " : "")
		+= m_bFrench ? " ���� " : "") += m_bKorean ? " ����" : "";
	m_list.SetItemText(nSel, 5, str);
	
}


void CYuanGongGuanLi_V2Dlg::ReadSeclectRow(unsigned nSel)
{
	m_szNum = m_list.GetItemText(nSel, 0);
	m_szName = m_list.GetItemText(nSel, 1);
	CString str;
	str = m_list.GetItemText(nSel, 2);
	if (str == "��")
		m_nSex = 0;
	else
		m_nSex = 1;
	str = m_list.GetItemText(nSel, 3);
	m_date.ParseDateTime(str);
	str = m_list.GetItemText(nSel, 4);
	if (str == "����")
		m_nGrade = 0;
	else if (str == "����")
		m_nGrade = 1;
	else if (str == "˶ʿ")
		m_nGrade = 2;
	else
		m_nGrade = 3;

	str = m_list.GetItemText(nSel, 5);
	m_bEnglish = static_cast<bool>(str.Find("Ӣ") + 1);
	m_bJanpanese = static_cast<bool>(str.Find("��") + 1);
	m_bFrench = static_cast<bool>(str.Find("��") + 1);
	m_bKorean = static_cast<bool>(str.Find("��") + 1);
	
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
		AfxMessageBox("�ļ�����ʱʧЧ��");
		return;
	}
	unsigned i = 0, nCount = m_list.GetItemCount();
	SInfo info;
	CString str, szGrade = "���б���˶ʿ��ʿ";
	
	while (i < nCount)
	{
		m_list.GetItemText(i, 0, info.sNum, sizeof(info.sNum));
		m_list.GetItemText(i, 1, info.sName, sizeof(info.sName));
		str = m_list.GetItemText(i,2);
		info.nSex = (str == "��") ? 0 : 1;
		m_list.GetItemText(i, 3, info.sDate, sizeof(info.sDate));
		str = m_list.GetItemText(i, 4);
		info.nGrade = static_cast<unsigned>(szGrade.Find(str)/4);
		str = m_list.GetItemText(i, 5);
		info.sbLanguage[0] = static_cast<bool>(str.Find("Ӣ") + 1);
		info.sbLanguage[1] = static_cast<bool>(str.Find("��") + 1);
		info.sbLanguage[2] = static_cast<bool>(str.Find("��") + 1);
		info.sbLanguage[3] = static_cast<bool>(str.Find("��") + 1);
		file.Write(&info, sizeof(info));
		++i;
	}
}


void CYuanGongGuanLi_V2Dlg::ReadInfo()
{
	CFile file;
	if (!file.Open("info.dat", CFile::modeRead | CFile::shareDenyNone))
		//AfxMessageBox("�ļ���ʼ��ʧ�ܣ�");
		return;
	
	SInfo info;
 	unsigned i = 0;
	CString str, szGrade = "���б���˶ʿ��ʿ";
	while (file.Read(&info, sizeof(info)) == sizeof(info))
	{
		m_list.InsertItem(i, info.sNum);
		m_list.SetItemText(i, 1, info.sName);
		m_list.SetItemText(i, 2, info.nSex ? "Ů" : "��");
		m_list.SetItemText(i, 3, info.sDate);
		if (info.nGrade == 0)
			str = "����";
		if (info.nGrade == 1)
			str = "����";
		if (info.nGrade == 2)
			str = "˶ʿ";
		if (info.nGrade == 3)
			str = "��ʿ";

		//str.Format("%s", szGrade.GetAt(2 * info.nGrade));
		m_list.SetItemText(i, 4, str);
		str = "";
		(((str += info.sbLanguage[0] ? "Ӣ��" : "") += info.sbLanguage[1] ? " ����" : "") += info.sbLanguage[2] ?
			" ����" : "") += info.sbLanguage[3] ? " ����" : "";
		m_list.SetItemText(i, 5, str);
		++i;
	}
}
