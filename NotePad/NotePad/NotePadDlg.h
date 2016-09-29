
// NotePadDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CNotePadDlg �Ի���
class CNotePadDlg : public CDialogEx
{
// ����
public:
	CNotePadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NOTEPAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileClose();
	afx_msg void OnFormatFont();
private:
	CEdit m_edit;
	CFont m_font;
};
