// carOutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "park_Manage.h"
#include "carOutDlg.h"
#include "afxdialogex.h"


// carOutDlg �Ի���

IMPLEMENT_DYNAMIC(carOutDlg, CDialogEx)

carOutDlg::carOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(carOutDlg::IDD, pParent)
	, carOutLience(_T(""))
	, carOutFeenum(0)
{
		char * fn="D:\\����ͼƬ\\carlien.txt";  
	string a =readFileIntoString(fn);  
	carOutLience.Format("%s", a.c_str());


	    CDBOperation dbOper;
		bool bConn = dbOper.ConnToDB("Provider=MSDAORA;Persist Security Info=True;Data Source=xe", "system", "83240007");
		if (false == bConn)
		{
			MessageBox("�������ݿ���ִ���");
			return;
		}

		char sql[255] = {0};
		_RecordsetPtr pRst;
		  //ִ�в�ѯ���
			sprintf_s(sql, "select CARFEEVIEW from CAR_IN Where CARLICENCEVIEW ='%s'",carOutLience);
			pRst = dbOper.ExecuteWithResSQL(sql);
			    if (NULL == pRst)
					{
						printf("��ѯ���ݳ��ִ���\n");
						return;
					}
					if (pRst->adoEOF)
					{
						pRst->Close();
						return;
					}
					carOutFeenum = pRst->GetCollect(_variant_t("CARFEEVIEW"));

		}


carOutDlg::~carOutDlg()
{
}
string carOutDlg::readFileIntoString(char * filename)  
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
void carOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_EDIT1, carOutlicen);
//	DDX_Control(pDX, IDC_EDIT2, carOutFee);
	DDX_Text(pDX, IDC_EDIT1, carOutLience);
	DDX_Text(pDX, IDC_EDIT2, carOutFeenum);
	SetTimer(1, 200, NULL);
}


BEGIN_MESSAGE_MAP(carOutDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL2, &carOutDlg::OnBnClickedCancel2)
	ON_BN_CLICKED(IDOK2, &carOutDlg::OnBnClickedOk2)
	ON_EN_CHANGE(IDC_EDIT1, &carOutDlg::OnEnChangeEdit1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// carOutDlg ��Ϣ�������


void carOutDlg::OnBnClickedCancel2()
{
	CDialogEx::OnCancel();
}


void carOutDlg::OnBnClickedOk2()
{
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

	if(carOutLience!="")
    {

		sprintf_s(sql, "update CARINFO set TIMECAROUT= sysdate,CARFEE = (trunc(abs((TIMECARIN - TIMECAROUT)*24))*(select FEE from FEESTAND where CARINFO.CARTYPE = FEESTAND.CARTYPE)) where CARLICENCE = '%s'",carOutLience);
        pRst = dbOper.ExecuteWithResSQL(sql);
				
		sprintf_s(sql, "update CARINFO set CARFEE = (trunc(abs((TIMECARIN - TIMECAROUT)*24))*(select FEE from FEESTAND where CARINFO.CARTYPE = FEESTAND.CARTYPE)) where CARLICENCE = '%s'",carOutLience);
        pRst = dbOper.ExecuteWithResSQL(sql);
		//ִ�в�ѯ���
        sprintf_s(sql, "select CARFEE FROM CARINFO where CARLICENCE = '%s'",carOutLience);
        pRst = dbOper.ExecuteWithResSQL(sql);

		if (NULL == pRst)
		{
			MessageBox("�޸ó�����Ϣ,����ʧ��","ʧ��");
			return;
		}
		if (pRst->adoEOF)
		{
			pRst->Close();
			MessageBox("�޸ó�����Ϣ,����ʧ��","ʧ��");
			return;
		}

        carOutFeenum = pRst->GetCollect(_variant_t("CARFEE"));
        sprintf_s(sql, "��������ɹ�,��ȡ����%d",carOutFeenum);
		MessageBox(sql,"�ɹ�");
		UpdateData(false);
	}
	else
		MessageBox("�����복�ƺ�����ٳ���","ʧ��");
}


void carOutDlg::OnEnChangeEdit1()
{
	
}


void carOutDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	   pDC = GetDlgItem(IDC_STATIC_haha_1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_STATIC_haha_1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    frame = cvLoadImage("D:\\����ͼƬ\\car.jpg"); //ͼƬ��ȡ·�������Լ��趨  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
    ReleaseDC(pDC);
	CDialogEx::OnTimer(nIDEvent);
}
