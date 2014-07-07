/*!
* \file mdspi.cpp
* \brief ����ӿ�ʵ��
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
#include "mdspi.h"
#include <iostream>
#include <vector>
#include "windows.h"

using namespace std;
#pragma warning(disable : 4996)

extern int requestId;  
extern HANDLE g_hEvent;

void mdspi::OnRspError(CSecurityFtdcRspInfoField *pRspInfo,
	int nRequestID, bool bIsLast)
{
	IsErrorRspInfo(pRspInfo);
}

void mdspi::OnFrontDisconnected(int nReason)
{
	cerr<<" ��Ӧ | �����ж�..." 
		<< " reason=" << nReason << endl;
}

void mdspi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr<<" ��Ӧ | ������ʱ����..." 
		<< " TimerLapse = " << nTimeLapse << endl;
}

void mdspi::OnFrontConnected()
{
	cerr<<" ���ӽ���ǰ��...�ɹ�"<<endl;
	SetEvent(g_hEvent);
}

void mdspi::ReqUserLogin(TSecurityFtdcBrokerIDType	appId,
	TSecurityFtdcUserIDType	userId,	TSecurityFtdcPasswordType	passwd)
{
	CSecurityFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, appId);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	int ret = pUserApi->ReqUserLogin(&req, ++requestId);
	cerr<<" ���� | ���͵�¼..."<<((ret == 0) ? "�ɹ�" :"ʧ��") << endl;	
	//SetEvent(g_hEvent);
}

void mdspi::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin,
	CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin)
	{
		cerr<<" ��Ӧ | ��¼�ɹ�...��ǰ������:"
			<<pRspUserLogin->TradingDay<<endl;
	}
	if(bIsLast) SetEvent(g_hEvent);
}

void mdspi::SubscribeMarketData(char* instIdList, char* exchangeID)
{
	vector<char*> list;
	char *token = strtok(instIdList, ",");
	while( token != NULL ){
		list.push_back(token); 
		token = strtok(NULL, ",");
	}
	unsigned int len = list.size();
	char** pInstId = new char* [len];  
	for(unsigned int i=0; i<len;i++)  pInstId[i]=list[i]; 
	int ret=pUserApi->SubscribeMarketData(pInstId, len,exchangeID);
	cerr<<" ���� | �������鶩��... "<<((ret == 0) ? "�ɹ�" : "ʧ��")<< endl;
	//SetEvent(g_hEvent);
}

void mdspi::OnRspSubMarketData(
	CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, 
	CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr<<" ��Ӧ |  ���鶩��...�ɹ�"<<endl;
	if(bIsLast)  SetEvent(g_hEvent);
}

void mdspi::OnRspUnSubMarketData(
	CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
	CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr<<" ��Ӧ |  ����ȡ������...�ɹ�"<<endl;
	if(bIsLast)  SetEvent(g_hEvent);
}

void mdspi::OnRtnDepthMarketData(
	CSecurityFtdcDepthMarketDataField *pDepthMarketData)
{
	cerr<<" ���� | ��Լ:"<<pDepthMarketData->InstrumentID
		<<" �ּ�:"<<pDepthMarketData->LastPrice
		<<" ��߼�:" << pDepthMarketData->HighestPrice
		<<" ��ͼ�:" << pDepthMarketData->LowestPrice
		<<" ��һ��:" << pDepthMarketData->AskPrice1 
		<<" ��һ��:" << pDepthMarketData->AskVolume1 
		<<" ��һ��:" << pDepthMarketData->BidPrice1
		<<" ��һ��:" << pDepthMarketData->BidVolume1
		<<" �ֲ���:"<< pDepthMarketData->OpenInterest <<endl;
}

bool mdspi::IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo)
{	
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret){
		cerr<<" ��Ӧ | "<<pRspInfo->ErrorMsg<<endl;
	}
	return ret;
}