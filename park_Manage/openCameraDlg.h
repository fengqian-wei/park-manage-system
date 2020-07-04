#pragma once
#include "CvvImage.h"
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

// openCameraDlg 对话框

class openCameraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(openCameraDlg)

public:
	openCameraDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~openCameraDlg();
	CvCapture* Capture;
	CvCapture* m_Video;
	IplImage* frame;
	IplImage* m_grabframe;
	CRect rect;
	CDC *pDC;
	HDC hDC;
	CWnd *pwnd;
	int ImgNum ;
// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
