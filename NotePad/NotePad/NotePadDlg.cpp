
// NotePadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NotePad.h"
#include "NotePadDlg.h"
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


// CNotePadDlg �Ի���



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


// CNotePadDlg ��Ϣ�������

BOOL CNotePadDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNotePadDlg::OnPaint()
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
HCURSOR CNotePadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotePadDlg::OnFileOpen()
{
	LPCTSTR szFilter = "�ı��ļ� (*.txt)|*.txt|�����ļ� (*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFilter);
	if (IDCANCEL == dlg.DoModal())
		return;
	CFile file;
	if (!file.Open(dlg.GetPathName(), CFile::modeRead))
	{
		AfxMessageBox("�ļ���ʧ�ܣ�");
		return;
	}
	CFileStatus state;
	file.GetStatus(state);
	char *pText = new char[state.m_size + 1];
	if (!file.Read(pText, state.m_size))
	{
		AfxMessageBox("�ļ���ȡʧ�ܣ�");
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
	if (IDCANCEL == AfxMessageBox("�Ƿ񱣴浱ǰ�ĵ���", MB_OKCANCEL))
		return;
	OnFileSave();
	SetDlgItemText(IDC_TEXT, "");
}


void CNotePadDlg::OnFileSave()
{
	// TODO:  �ڴ���������������
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
