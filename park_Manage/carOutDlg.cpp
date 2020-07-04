// carOutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "park_Manage.h"
#include "carOutDlg.h"
#include "afxdialogex.h"


// carOutDlg 对话框

IMPLEMENT_DYNAMIC(carOutDlg, CDialogEx)

carOutDlg::carOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(carOutDlg::IDD, pParent)
	, carOutLience(_T(""))
	, carOutFeenum(0)
{
		char * fn="D:\\车牌图片\\carlien.txt";  
	string a =readFileIntoString(fn);  
	carOutLience.Format("%s", a.c_str());


	    CDBOperation dbOper;
		bool bConn = dbOper.ConnToDB("Provider=MSDAORA;Persist Security Info=True;Data Source=xe", "system", "83240007");
		if (false == bConn)
		{
			MessageBox("连接数据库出现错误");
			return;
		}

		char sql[255] = {0};
		_RecordsetPtr pRst;
		  //执行查询语句
			sprintf_s(sql, "select CARFEEVIEW from CAR_IN Where CARLICENCEVIEW ='%s'",carOutLience);
			pRst = dbOper.ExecuteWithResSQL(sql);
			    if (NULL == pRst)
					{
						printf("查询数据出现错误！\n");
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
//将文件读入到ostringstream对象buf中  
ostringstream buf;  
char ch;  
int i = 0;
while(buf&&ifile.get(ch)&&(ch!=10))  
{
	if (i>=5)
	buf.put(ch);
	i++;
}
//返回与流对象buf关联的字符串  
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


// carOutDlg 消息处理程序


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
        MessageBox("连接数据库出现错误");
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
		//执行查询语句
        sprintf_s(sql, "select CARFEE FROM CARINFO where CARLICENCE = '%s'",carOutLience);
        pRst = dbOper.ExecuteWithResSQL(sql);

		if (NULL == pRst)
		{
			MessageBox("无该车辆信息,出库失败","失败");
			return;
		}
		if (pRst->adoEOF)
		{
			pRst->Close();
			MessageBox("无该车辆信息,出库失败","失败");
			return;
		}

        carOutFeenum = pRst->GetCollect(_variant_t("CARFEE"));
        sprintf_s(sql, "车辆出库成功,收取车费%d",carOutFeenum);
		MessageBox(sql,"成功");
		UpdateData(false);
	}
	else
		MessageBox("请输入车牌号码后再出库","失败");
}


void carOutDlg::OnEnChangeEdit1()
{
	
}


void carOutDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	   pDC = GetDlgItem(IDC_STATIC_haha_1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_STATIC_haha_1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    frame = cvLoadImage("D:\\车牌图片\\car.jpg"); //图片读取路径可以自己设定  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
    ReleaseDC(pDC);
	CDialogEx::OnTimer(nIDEvent);
}
