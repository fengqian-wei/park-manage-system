#pragma once
#include "afxcmn.h"


// visitorDlg �Ի���

class visitorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(visitorDlg)

public:
	visitorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~visitorDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl usercarInfoList;
	afx_msg void OnBnClickedOk();
	CString vistorCarLice;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
};
