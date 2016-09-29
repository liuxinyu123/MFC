
// YuanGongGuanLi_V2Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "ATLComTime.h"


// CYuanGongGuanLi_V2Dlg 对话框
class CYuanGongGuanLi_V2Dlg : public CDialogEx
{
// 构造
public:
	CYuanGongGuanLi_V2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YUANGONGGUANLI_V2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
