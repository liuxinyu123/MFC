
// YuanGongGuanLi_V1Dlg.h : ͷ�ļ�
//

#pragma once


// CYuanGongGuanLi_V1Dlg �Ի���
class CYuanGongGuanLi_V1Dlg : public CDialogEx
{
// ����
	CComboBox m_comb;
	CListCtrl m_list;
public:
	CYuanGongGuanLi_V1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YUANGONGGUANLI_V1_DIALOG };

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
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedMod();
};
