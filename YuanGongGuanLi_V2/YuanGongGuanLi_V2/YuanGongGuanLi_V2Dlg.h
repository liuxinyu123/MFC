
// YuanGongGuanLi_V2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ATLComTime.h"


// CYuanGongGuanLi_V2Dlg �Ի���
class CYuanGongGuanLi_V2Dlg : public CDialogEx
{
// ����
public:
	CYuanGongGuanLi_V2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YUANGONGGUANLI_V2_DIALOG };

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
private:
	BOOL m_bEnglish;
	BOOL m_bFrench;
	BOOL m_bJanpanese;
	BOOL m_bKorean;
	CListCtrl m_list;
	int m_nGrade;
//	BOOL m_bSex;
	int m_nSex;
	CString m_szNum;
	CString m_szName;
public:
	COleDateTime m_date;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedModify();
	void ReadSeclectRow(unsigned nSel);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	void ReadInfo();
};
