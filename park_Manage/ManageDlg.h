#pragma once
#include "afxcmn.h"
#include "openCameraDlg.h"

// ManageDlg �Ի���

class ManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ManageDlg)

public:
	ManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManageDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl carInfoList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton5();
	CString lookcar;
	afx_msg void OnBnClickedButton2();
};
