// ManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "park_Manage.h"
#include "ManageDlg.h"
#include "afxdialogex.h"


// ManageDlg 对话框

IMPLEMENT_DYNAMIC(ManageDlg, CDialogEx)

ManageDlg::ManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManageDlg::IDD, pParent)
	, lookcar(_T(""))
{

}

ManageDlg::~ManageDlg()
{
}

void ManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, carInfoList);
	DDX_Text(pDX, IDC_EDIT1, lookcar);
}


BEGIN_MESSAGE_MAP(ManageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ManageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &ManageDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ManageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &ManageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ManageDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON5, &ManageDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &ManageDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ManageDlg 消息处理程序


void ManageDlg::OnBnClickedButton1()
{
		DWORD dwStyle = carInfoList.GetExtendedStyle();     
		dwStyle |= LVS_EX_FULLROWSELECT;
		dwStyle |= LVS_EX_GRIDLINES;
		while (true)
		{
		 if (!carInfoList.DeleteColumn(0)) 
            break;
        }
		carInfoList.DeleteAllItems();
		carInfoList.SetExtendedStyle(dwStyle);
		carInfoList.InsertColumn(0, _T("车牌号"), LVCFMT_LEFT, 100);
		carInfoList.InsertColumn(1, _T("入库时间"), LVCFMT_LEFT, 100);
		carInfoList.InsertColumn(3, _T("收费标准"), LVCFMT_LEFT, 100);
		carInfoList.InsertColumn(4, _T("已产生费用）"), LVCFMT_LEFT, 80); 
		
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
		int i = 0;
		if (lookcar=="")
		{
			//执行查询语句
			sprintf_s(sql, "select * from CAR_IN");
			pRst = dbOper.ExecuteWithResSQL(sql);
			while (!pRst->adoEOF)
			{
				carInfoList.InsertItem(i, (LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARLICENCEVIEW"))));
				carInfoList.SetItemText(i, 2,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARTYPEVIEW"))));
				carInfoList.SetItemText(i, 1,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("TIMECARINVIEW"))));
				carInfoList.SetItemText(i, 3,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARFEEVIEW")))); 
				i++;
				pRst->MoveNext();	
			}
		}
		else
		{
			//执行查询语句
			sprintf_s(sql, "select * from CAR_IN where CARLICENCEVIEW = '%s'",lookcar);
			pRst = dbOper.ExecuteWithResSQL(sql);
		           if (NULL == pRst)
					{
						MessageBox("无该车辆信息，请重新输入车牌号码进行查询","失败");
						system("PAUSE");
						return;
					}
					if (pRst->adoEOF)
					{
						pRst->Close();
						printf("There is no records in this table\n");
						return;
					}
				
			//else
			//{
				carInfoList.InsertItem(0, (LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARLICENCEVIEW"))));
				carInfoList.SetItemText(0, 2,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARTYPEVIEW"))));
				carInfoList.SetItemText(0, 1,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("TIMECARINVIEW"))));
				carInfoList.SetItemText(0, 3,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARFEEVIEW")))); 
			//}
		}
}


void ManageDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	    while (true)
		{
		 if (!carInfoList.DeleteColumn(0)) 
            break;
        }
		carInfoList.DeleteAllItems();
	  carInfoList.InsertColumn(0, _T("车辆类型"), LVCFMT_LEFT, 100);
	  carInfoList.InsertColumn(3, _T("收费标准($/h)"), LVCFMT_LEFT, 100);

    CDBOperation dbOper;
    bool bConn = dbOper.ConnToDB("Provider=MSDAORA;Persist Security Info=True;Data Source=xe", "system", "83240007");
    if (false == bConn)
    {
        MessageBox("连接数据库出现错误");
        return;
    }
	char sql[255] = {0};
    _RecordsetPtr pRst;
	int i = 0;
	//执行查询语句
    sprintf_s(sql, "select * from FEESTAND");
    pRst = dbOper.ExecuteWithResSQL(sql);
    while (!pRst->adoEOF)
    {
        carInfoList.InsertItem(i, (LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARTYPE"))));
        carInfoList.SetItemText(i, 1,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("FEE")))); 
        i++;
		pRst->MoveNext();	
    }
    
}


void ManageDlg::OnBnClickedButton4()
{
	MessageBox("开关门闸成功！","门闸控制");
}


void ManageDlg::OnBnClickedOk()
{
	carInDlg carIn;
	carIn.DoModal();
	//CDialogEx::OnOK();
}


void ManageDlg::OnBnClickedCancel()
{

	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void ManageDlg::OnBnClickedButton5()
{
	carOutDlg carOut;
	carOut.DoModal();
}


void ManageDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	openCameraDlg Camera;
	Camera.DoModal();
}
