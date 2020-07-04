#include "stdafx.h"
#include "DBOperation.h"



CDBOperation::CDBOperation(void)
{
    CoInitialize(NULL);
    m_pConnection = CreateConnPtr();
    m_pCommand = CreateCommPtr();
}

CDBOperation::~CDBOperation(void)
{
    //m_pCommand->Close();
    m_pConnection->Close();
}

bool CDBOperation::ConnToDB(char *ConnectionString, char *UserID, char *Password)
{
    if (NULL == m_pConnection)
    {
        printf("Failed to create connection\n");
        return false;
    }

    try
    {
        HRESULT hr = m_pConnection->Open(ConnectionString, UserID, Password, NULL);
        if (TRUE == FAILED(hr))
        {
            return false;
        }
        m_pCommand->ActiveConnection = m_pConnection;
        return true;
    }
    catch(_com_error &e)
    {
        PrintErrorInfo(e);
        return false;
    }
}

_RecordsetPtr CDBOperation::ExecuteWithResSQL(const char *sql)
{
    //已经在连接至数据库的时候进行判断了
    //if (NULL == m_pCommand || 0 == m_pConnection->State)
    //{
    //    printf("Failed to create command OR the state of connection is zero\n");
    //    return NULL;
    //}

    //char *query = new char;
    //strcpy(query, sql);
    try
    {
        m_pCommand->CommandText = _bstr_t(sql);
        _RecordsetPtr pRst = m_pCommand->Execute(NULL, NULL, adCmdText);
        return pRst;
        //_variant_t ra;
        //_RecordsetPtr pRst = m_pConnection->Execute((_bstr_t)query, &ra, adCmdText);
    }
    catch(_com_error &e)
    {
        PrintErrorInfo(e);
        return NULL;
    }
}

//bool CDBOperation::ExecuteNoResSQL(const char *sql)
//{
//    //if (NULL == m_pCommand || 0 == m_pConnection->State)
//    //{
//    //    printf();
//    //}
//    try
//    {
//        char *query = NULL;
//        strcpy(query, sql);
//        m_pCommand->CommandText = (_bstr_t)query;
//
//    }
//}

void CDBOperation::PrintErrorInfo(_com_error &e)
{
    printf("Error infomation are as follows\n");
    printf("ErrorNo: %d\nError Message:%s\nError Source:%s\nError Description:%s\n", e.Error(), e.ErrorMessage(), (LPCTSTR)e.Source(), (LPCTSTR)e.Description());
}

_ConnectionPtr CDBOperation::CreateConnPtr()
{
    HRESULT hr;
    _ConnectionPtr connPtr;
    hr = connPtr.CreateInstance(__uuidof(Connection));
    if (FAILED(hr) == TRUE)
    {
        return NULL;
    }
    return connPtr;
}

_CommandPtr CDBOperation::CreateCommPtr()
{
    HRESULT hr;
    _CommandPtr commPtr;
    hr = commPtr.CreateInstance(__uuidof(Command));
    if (FAILED(hr) == TRUE)
    {
        return NULL;
    }
    return commPtr;
}

_RecordsetPtr CDBOperation::CreateRecsetPtr()
{
    HRESULT hr;
    _RecordsetPtr recsetPtr;
    hr = recsetPtr.CreateInstance(__uuidof(    Command));
    if (FAILED(hr) ==TRUE)
    {
        return NULL;
    }
    return recsetPtr;
}
