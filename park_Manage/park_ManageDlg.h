#include <cstring>
#include "ManageDlg.h"
#include "visitorDlg.h"

// park_ManageDlg.h : ͷ�ļ�
//

#pragma once


// Cpark_ManageDlg �Ի���
class Cpark_ManageDlg : public CDialogEx
{
// ����
public:
	Cpark_ManageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PARK_MANAGE_DIALOG };

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
	CString Username;
	CString Userkey;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
