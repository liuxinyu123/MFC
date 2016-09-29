
// NotePad_V1Dlg.h : 头文件
//

#pragma once


// CNotePad_V1Dlg 对话框
class CNotePad_V1Dlg : public CDialogEx
{
// 构造
public:
	CNotePad_V1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NOTEPAD_V1_DIALOG };

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
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};
