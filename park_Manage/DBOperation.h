#pragma once
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")
class CDBOperation
{
public:
    //��ʼ�����ݿ������Ҫ�Ķ���
    CDBOperation(void);
    ~CDBOperation(void);
    //���������ݿ�
    bool ConnToDB(char *ConnectionString, char *UserID, char *Password);

    //���ݿ��������
    //��ѯ���� ɾ���Լ����
    _RecordsetPtr ExecuteWithResSQL(const char *);
    //bool ExecuteNoResSQL(const char *);//delete and add

private:
    void PrintErrorInfo(_com_error &);

private:
    //��ʼ�����ݿ����ӡ������¼��
    _ConnectionPtr CreateConnPtr();
    _CommandPtr CreateCommPtr();
    _RecordsetPtr CreateRecsetPtr();

private:
    //���ݿ�������Ҫ�����ӡ������������
    _ConnectionPtr m_pConnection;
    _CommandPtr m_pCommand;
};
