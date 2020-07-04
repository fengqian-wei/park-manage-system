#pragma once
#include "resource.h"
#include "DBOperation.h"
#include <opencv2\opencv.hpp>
#include "CvvImage.h"
#include <string>  
#include <fstream>  
#include <sstream>  
#include <iostream>
using namespace std;
using namespace cv;
// carInDlg �Ի���

class carInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(carInDlg)

public:
	carInDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~carInDlg();
	CRect rect;
	CDC *pDC;
	HDC hDC;
	CvCapture* Capture;
	IplImage* frame;
// �Ի�������
	enum { IDD = IDD_DIALOG3 };
	string readFileIntoString(char * filename);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString carInlien;
	CString carIntype;
	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
