#pragma once
#include "resource.h"
#include "afxwin.h"
#include "DBOperation.h"
#include <opencv2\opencv.hpp>
#include "CvvImage.h"
#include <string>  
#include <fstream>  
#include <sstream>  
#include <iostream>
using namespace std;
using namespace cv;
// carOutDlg 对话框

class carOutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(carOutDlg)

public:
	carOutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~carOutDlg();
	CRect rect;
	CDC *pDC;
	HDC hDC;
	CvCapture* Capture;
	IplImage* frame;
// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	string readFileIntoString(char * filename);
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnBnClickedOk2();
	//CEdit carOutlicen;
	//CEdit carOutFee;
	CString carOutLience;
	int carOutFeenum;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
