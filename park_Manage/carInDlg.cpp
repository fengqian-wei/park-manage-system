// carInDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "park_Manage.h"
#include "carInDlg.h"
#include "afxdialogex.h"


// carInDlg 对话框

IMPLEMENT_DYNAMIC(carInDlg, CDialogEx)

carInDlg::carInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(carInDlg::IDD, pParent)
	, carInlien(_T(""))
	, carIntype(_T(""))
{
		char * fn="D:\\车牌图片\\carlien.txt";  
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


// carInDlg 消息处理程序
string carInDlg::readFileIntoString(char * filename)  
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

void carInDlg::OnBnClickedOk()
{
	//UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
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
	//执行插入语句
	if((carInlien!="")&&(carIntype!=""))
    {
		sprintf_s(sql, "insert into CARINFO(CARLICENCE, CARTYPE, TIMECARIN,TIMECAROUT,CARFEE) values('%s', %s, sysdate, null, 0)",carInlien,carIntype);
        pRst = dbOper.ExecuteWithResSQL(sql);
		MessageBox("车辆入库成功","成功");
	}
	else
		MessageBox("请输入车牌号码和车辆类型后再提交","失败");
}


void carInDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
    CDialogEx::OnCancel();
}


void carInDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	//SetTimer(1, 500, NULL);
//#1015

	// TODO:  在此添加控件通知处理程序代码
}



void carInDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 pDC = GetDlgItem(IDC_STATIC_haha)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_STATIC_haha)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    frame = cvLoadImage("D:\\车牌图片\\car.jpg"); //图片读取路径可以自己设定  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
    ReleaseDC(pDC);
	CDialogEx::OnTimer(nIDEvent);
}
