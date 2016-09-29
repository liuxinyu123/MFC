
// MultiThread8Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultiThread8.h"
#include "MultiThread8Dlg.h"
#include "afxdialogex.h"
#include "afxmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

CCriticalSection critical_section;
char g_Array[10];

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


// CMultiThread8Dlg �Ի���



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


// CMultiThread8Dlg ��Ϣ�������

BOOL CMultiThread8Dlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMultiThread8Dlg::OnPaint()
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
