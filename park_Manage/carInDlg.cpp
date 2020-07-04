// carInDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "park_Manage.h"
#include "carInDlg.h"
#include "afxdialogex.h"


// carInDlg �Ի���

IMPLEMENT_DYNAMIC(carInDlg, CDialogEx)

carInDlg::carInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(carInDlg::IDD, pParent)
	, carInlien(_T(""))
	, carIntype(_T(""))
{
		char * fn="D:\\����ͼƬ\\carlien.txt";  
	string a =readFileIntoString(fn);  
	carInlien.Format("%s", a.c_str());
	//WinExec("D:\\EasyPR1\\demo.exe", SW_SHOW);
	//Sleep(10000); 
}

carInDlg::~carInDlg()
{
}

void carInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, carInlien);
	DDX_Text(pDX, IDC_EDIT2, carIntype);
	SetTimer(1, 200, NULL);
}


BEGIN_MESSAGE_MAP(carInDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &carInDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &carInDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &carInDlg::OnEnChangeEdit1)
//	ON_WM_PAINT()
ON_WM_TIMER()
END_MESSAGE_MAP()


// carInDlg ��Ϣ�������
string carInDlg::readFileIntoString(char * filename)  
{  
ifstream ifile(filename);  
//���ļ����뵽ostringstream����buf��  
ostringstream buf;  
char ch;  
int i = 0;
while(buf&&ifile.get(ch)&&(ch!=10))  
{
	if (i>=5)
	buf.put(ch);
	i++;
}
//������������buf�������ַ���  
return buf.str();  
}  

void carInDlg::OnBnClickedOk()
{
	//UpdateData(false);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(true);
    CDBOperation dbOper;
    bool bConn = dbOper.ConnToDB("Provider=MSDAORA;Persist Security Info=True;Data Source=xe", "system", "83240007");
    if (false == bConn)
    {
        MessageBox("�������ݿ���ִ���");
        return;
    }

    char sql[255] = {0};
    _RecordsetPtr pRst;
	//ִ�в������
	if((carInlien!="")&&(carIntype!=""))
    {
		sprintf_s(sql, "insert into CARINFO(CARLICENCE, CARTYPE, TIMECARIN,TIMECAROUT,CARFEE) values('%s', %s, sysdate, null, 0)",carInlien,carIntype);
        pRst = dbOper.ExecuteWithResSQL(sql);
		MessageBox("�������ɹ�","�ɹ�");
	}
	else
		MessageBox("�����복�ƺ���ͳ������ͺ����ύ","ʧ��");
}


void carInDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    CDialogEx::OnCancel();
}


void carInDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	//SetTimer(1, 500, NULL);
//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



void carInDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 pDC = GetDlgItem(IDC_STATIC_haha)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_STATIC_haha)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    frame = cvLoadImage("D:\\����ͼƬ\\car.jpg"); //ͼƬ��ȡ·�������Լ��趨  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
    ReleaseDC(pDC);
	CDialogEx::OnTimer(nIDEvent);
}
