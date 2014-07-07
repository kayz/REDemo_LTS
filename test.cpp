/*!
* \file test.cpp
* \brief ʾ������������
*
* ����Ŀ�ǻ��ڻ�������LTS֤ȯ�ӿڿ�����ʾ����������չʾ�����LTS
* �����½��п�����ʾ��������ʾ��LTS����ӿڵĵ��ã��ڱ�д�����Ŀʱ
* ���Բο���
* �ɶ�����Ϣ�ṩ��Դ�����´���ɴ�http://github.com/REInfo��ȡ��
* �Ϻ�������Ϣ�Ƽ����޹�˾�ṩ֤ȯ���ڻ�����Ȩ���ֻ����г����ס����㡢
* ���ҵ��Ŀͻ������Ʒ���
*
* \author Christian
* \version 1.0
* \date 2014-6-16
* 
*/
#include "test.h"

void test_order(void)
{
	//��ʼ��UserApi
	CSecurityFtdcTraderApi* pUserApi = CSecurityFtdcTraderApi::CreateFtdcTraderApi();
	traderspi* pUserSpi = new traderspi(pUserApi);
	pUserApi->RegisterSpi((CSecurityFtdcTraderSpi*)pUserSpi);         // ע���¼���
	pUserApi->SubscribePublicTopic(SECURITY_TERT_RESTART);			  // ע�ṫ����
	pUserApi->SubscribePrivateTopic(SECURITY_TERT_RESTART);			  // ע��˽����
	pUserApi->RegisterFront(tradeFront);							  // ע�ύ��ǰ�õ�ַ

	pUserApi->Init();
	ShowTraderCommand(pUserSpi,true); 
	pUserApi->Join();  
	pUserApi->Release();
}


void test_md(void)
{
	///��ʼ��UserApi
	CSecurityFtdcMdApi* pUserApi=CSecurityFtdcMdApi::CreateFtdcMdApi();
	mdspi* pUserSpi=new mdspi(pUserApi); ///�����ص����������MdSpi
	pUserApi->RegisterSpi(pUserSpi);			 /// �ص�����ע��ӿ���
	pUserApi->RegisterFront(mdFront);		     /// ע������ǰ�õ�ַ
	pUserApi->Init();      ///�ӿ��߳�����, ��ʼ����
	ShowMdCommand(pUserSpi,true); 
	pUserApi->Join();      ///�ȴ��ӿ��߳��˳�
	pUserApi->Release(); ///�ӿڶ����ͷ�
}
void main(int argc, const char* argv[]){
	g_hEvent=CreateEvent(NULL, true, false, NULL); 

	if(argc < 2)  cerr<<"ʹ�ò��� --md �� --trade."<<endl;  
	else if(strcmp(argv[1],"--md")==0)    test_md();
	else if(strcmp(argv[1],"--trade")==0) test_order();

}