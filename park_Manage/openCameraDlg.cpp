// openCameraDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "park_Manage.h"
#include "openCameraDlg.h"
#include "afxdialogex.h"


// openCameraDlg �Ի���

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


// openCameraDlg ��Ϣ�������


void openCameraDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 Capture = cvCreateCameraCapture(0); //  
    if (Capture==0)  
    {  
        MessageBox(_T("�޷���������ͷ������"));  
        return;  
    }  
  
    frame = cvQueryFrame(Capture); //������ͷ�����ļ���ץȡ������һ֡  
    pDC = GetDlgItem(IDC_STATIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
    GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
    ReleaseDC(pDC);  
  
    SetTimer(1, 25, NULL); //��ʱ������ʱʱ���֡��һ�� 
}


void openCameraDlg::OnTimer(UINT_PTR nIDEvent)
{
    pDC = GetDlgItem(IDC_STATIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    frame = cvQueryFrame(Capture); //������ͷ�����ļ���ץȡ������һ֡  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //���Ƹ�֡ͼ��     
      
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
      
    CDialogEx::OnTimer(nIDEvent);  
}


void openCameraDlg::OnBnClickedButton3()
{
	 if (!Capture)  
    {  
        MessageBox(_T("û�д�����ͷ������"));  
        return;  
    }  
      
    cvReleaseCapture(&Capture);  
  
    pDC = GetDlgItem(IDC_STATIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    frame = cvLoadImage("D:\\����ͼƬ\\beijng.jpg"); //ͼƬ��ȡ·�������Լ��趨  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
    ReleaseDC(pDC);  
}


void openCameraDlg::OnBnClickedButton2()
{
	 m_grabframe = frame;  
    if (m_grabframe == 0)  
    {  
        MessageBox(_T("����ͷ�ѹرգ��޷���׽ͼ�񣡣���"));  
        return;  
    }  
      
    CString ImagePath=TEXT("D:\\����ͼƬ\\");  
  
  
    if (!PathIsDirectory(ImagePath))  
  
    {  
        CreateDirectory(ImagePath, 0);//�������򴴽�  
        MessageBox(_T("����ͼƬ�ļ����Ѵ���������"));  
        return;  
    }  
    char ImagesName[100];  
  
    ImgNum = ImgNum + 1;
    sprintf_s(ImagesName, "%s%.2d%s", "D:\\����ͼƬ\\", ImgNum, ".jpg");  
      
    IplImage * m_snap = cvCreateImage(cvGetSize(m_grabframe), m_grabframe->depth, m_grabframe->nChannels);  
    cvCopy(m_grabframe, m_snap, NULL);  
    cvSaveImage(ImagesName, m_snap); //��ͼ��д��ָ���ļ��е��ļ���ȥ  
  
    //���´��������ͼ�����ʾ����  
    pDC = GetDlgItem(IDC_STATIC_1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_STATIC_1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(m_snap, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�����ľ��ο���  
}
