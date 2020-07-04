// openCameraDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "park_Manage.h"
#include "openCameraDlg.h"
#include "afxdialogex.h"


// openCameraDlg 对话框

IMPLEMENT_DYNAMIC(openCameraDlg, CDialogEx)

openCameraDlg::openCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(openCameraDlg::IDD, pParent)
{
	ImgNum = 0;
}

openCameraDlg::~openCameraDlg()
{
}

void openCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(openCameraDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &openCameraDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &openCameraDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &openCameraDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// openCameraDlg 消息处理程序


void openCameraDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	 Capture = cvCreateCameraCapture(0); //  
    if (Capture==0)  
    {  
        MessageBox(_T("无法连接摄像头！！！"));  
        return;  
    }  
  
    frame = cvQueryFrame(Capture); //从摄像头或者文件中抓取并返回一帧  
    pDC = GetDlgItem(IDC_STATIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
    GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
    ReleaseDC(pDC);  
  
    SetTimer(1, 25, NULL); //定时器，定时时间和帧率一致 
}


void openCameraDlg::OnTimer(UINT_PTR nIDEvent)
{
    pDC = GetDlgItem(IDC_STATIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    frame = cvQueryFrame(Capture); //从摄像头或者文件中抓取并返回一帧  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //复制该帧图像     
      
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
      
    CDialogEx::OnTimer(nIDEvent);  
}


void openCameraDlg::OnBnClickedButton3()
{
	 if (!Capture)  
    {  
        MessageBox(_T("没有打开摄像头！！！"));  
        return;  
    }  
      
    cvReleaseCapture(&Capture);  
  
    pDC = GetDlgItem(IDC_STATIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    frame = cvLoadImage("D:\\车牌图片\\beijng.jpg"); //图片读取路径可以自己设定  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
    ReleaseDC(pDC);  
}


void openCameraDlg::OnBnClickedButton2()
{
	 m_grabframe = frame;  
    if (m_grabframe == 0)  
    {  
        MessageBox(_T("摄像头已关闭，无法捕捉图像！！！"));  
        return;  
    }  
      
    CString ImagePath=TEXT("D:\\车牌图片\\");  
  
  
    if (!PathIsDirectory(ImagePath))  
  
    {  
        CreateDirectory(ImagePath, 0);//不存在则创建  
        MessageBox(_T("车牌图片文件夹已创建！！！"));  
        return;  
    }  
    char ImagesName[100];  
  
    ImgNum = ImgNum + 1;
    sprintf_s(ImagesName, "%s%.2d%s", "D:\\车牌图片\\", ImgNum, ".jpg");  
      
    IplImage * m_snap = cvCreateImage(cvGetSize(m_grabframe), m_grabframe->depth, m_grabframe->nChannels);  
    cvCopy(m_grabframe, m_snap, NULL);  
    cvSaveImage(ImagesName, m_snap); //把图像写入指定文件夹的文件中去  
  
    //以下代码是完成图像的显示过程  
    pDC = GetDlgItem(IDC_STATIC_1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_STATIC_1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(m_snap, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备环境的矩形框内  
}
