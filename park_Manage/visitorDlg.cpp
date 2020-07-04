// visitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "park_Manage.h"
#include "visitorDlg.h"
#include "afxdialogex.h"


// visitorDlg 对话框

IMPLEMENT_DYNAMIC(visitorDlg, CDialogEx)

visitorDlg::visitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(visitorDlg::IDD, pParent)
	, vistorCarLice(_T(""))
{

}

visitorDlg::~visitorDlg()
{
}

void visitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, usercarInfoList);
	DDX_Text(pDX, IDC_EDIT1, vistorCarLice);
}


BEGIN_MESSAGE_MAP(visitorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &visitorDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &visitorDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// visitorDlg 消息处理程序


void visitorDlg::OnBnClickedOk()
{
		DWORD dwStyle = usercarInfoList.GetExtendedStyle();     
		dwStyle |= LVS_EX_FULLROWSELECT;
		dwStyle |= LVS_EX_GRIDLINES;
		while (true)
		{
		 if (!usercarInfoList.DeleteColumn(0)) 
            break;
        }
		usercarInfoList.DeleteAllItems();
		usercarInfoList.SetExtendedStyle(dwStyle);
		usercarInfoList.InsertColumn(0, _T("车牌号"), LVCFMT_LEFT, 100);
		usercarInfoList.InsertColumn(1, _T("入库时间"), LVCFMT_LEFT, 100);
		usercarInfoList.InsertColumn(3, _T("收费标准"), LVCFMT_LEFT, 100);
		usercarInfoList.InsertColumn(4, _T("已产生费用）"), LVCFMT_LEFT, 80); 
		
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
	    if (vistorCarLice=="")
		{
			//执行查询语句
			sprintf_s(sql, "select * from CAR_IN");
			pRst = dbOper.ExecuteWithResSQL(sql);
			    if (NULL == pRst)
					{
						printf("查询数据出现错误！\n");
						system("PAUSE");
						return;
					}
					if (pRst->adoEOF)
					{
						pRst->Close();
						printf("There is no records in this table\n");
						return;
					}
			while (!pRst->adoEOF)
			{
				usercarInfoList.InsertItem(i, (LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARLICENCEVIEW"))));
				usercarInfoList.SetItemText(i, 2,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARTYPEVIEW"))));
				usercarInfoList.SetItemText(i, 1,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("TIMECARINVIEW"))));
				usercarInfoList.SetItemText(i, 3,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARFEEVIEW")))); 
				i++;
				pRst->MoveNext();	
			}
		}
		else
		{
			//执行查询语句
			sprintf_s(sql, "select * from CAR_IN where CARLICENCEVIEW = '%s'",vistorCarLice);
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
				usercarInfoList.InsertItem(0, (LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARLICENCEVIEW"))));
				usercarInfoList.SetItemText(0, 2,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARTYPEVIEW"))));
				usercarInfoList.SetItemText(0, 1,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("TIMECARINVIEW"))));
				usercarInfoList.SetItemText(0, 3,(LPSTR)(LPCSTR)_bstr_t(pRst->GetCollect(_variant_t("CARFEEVIEW")))); 
		}
}


void visitorDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	@TN
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
