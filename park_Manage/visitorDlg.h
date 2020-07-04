#pragma once
#include "afxcmn.h"


// visitorDlg 对话框

class visitorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(visitorDlg)

public:
	visitorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~visitorDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl usercarInfoList;
	afx_msg void OnBnClickedOk();
	CString vistorCarLice;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
};
