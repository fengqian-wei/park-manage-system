#include <cstring>
#include "ManageDlg.h"
#include "visitorDlg.h"

// park_ManageDlg.h : 头文件
//

#pragma once


// Cpark_ManageDlg 对话框
class Cpark_ManageDlg : public CDialogEx
{
// 构造
public:
	Cpark_ManageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PARK_MANAGE_DIALOG };

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
	CString Username;
	CString Userkey;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
