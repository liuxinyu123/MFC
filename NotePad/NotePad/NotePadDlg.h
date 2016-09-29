
// NotePadDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CNotePadDlg 对话框
class CNotePadDlg : public CDialogEx
{
// 构造
public:
	CNotePadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NOTEPAD_DIALOG };

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
