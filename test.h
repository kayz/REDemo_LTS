/*!
* \file test.h
* \brief ʾ������������ӿ�
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
#ifndef TEST_H_
#define TEST_H_

#include "config.h"
#include "api/trade/win/public/SecurityFtdcTraderApi.h"
#include "api/trade/win/public/SecurityFtdcMdApi.h"
#include "traderspi.h"
#include "mdspi.h"
#include "windows.h"
#include <iostream>
using namespace std;

HANDLE g_hEvent;

void ShowTraderCommand(traderspi* p, bool print=false){
	if(print){
		cerr<<"-----------------------------------------------"<<endl;
		cerr<<" [1] ReqUserLogin              -- ��¼"<<endl;
		cerr<<" [2] ReqQryInstrument          -- ��ѯ��Լ"<<endl;
		cerr<<" [3] ReqQryTradingAccount      -- ��ѯ�ʽ�"<<endl;
		cerr<<" [4] ReqQryInvestorPosition    -- ��ѯ�ֲ�"<<endl;
		cerr<<" [5] ReqOrderInsert            -- ����"<<endl;
		cerr<<" [6] ReqOrderAction            -- ����"<<endl;
		cerr<<" [7] PrintOrders               -- ��ʾ����"<<endl;
		cerr<<" [8] PrintTrades               -- ��ʾ�ɽ�"<<endl;
		cerr<<" [0] Exit                      -- �˳�"<<endl;
		cerr<<"----------------------------------------------"<<endl;
	}   
	TSecurityFtdcBrokerIDType	    brokerId;
	TSecurityFtdcUserIDType	        userId;
	TSecurityFtdcPasswordType	    passwd;
	TSecurityFtdcInstrumentIDType    instId;
	TSecurityFtdcDirectionType       dir;
	TSecurityFtdcCombOffsetFlagType  kpp;
	TSecurityFtdcPriceType           price;
	TSecurityFtdcVolumeType          vol;
	TSecurityFtdcExchangeIDType		exchangID;
	TSecurityFtdcSequenceNoType      orderSeq;

	int cmd;  cin>>cmd;
	switch(cmd){
	case 1: {
		cerr<<" ���͹�˾���루2011�� > ";cin>>brokerId;
		cerr<<" Ͷ���ߴ��� > ";cin>>userId;
		cerr<<" �������� > ";cin>>passwd;
		p->ReqUserLogin(brokerId,userId,passwd); break;
			}

	case 2: {
		cerr<<" ��Լ���� > "; cin>>instId; 
		p->ReqQryInstrument(instId); break;
			}
	case 3: p->ReqQryTradingAccount(); break;
	case 4: {
		cerr<<" ��Լ���� > "; cin>>instId; 
		p->ReqQryInvestorPosition(instId); break;
			}
	case 5: {
		cerr<<" ��Լ���� > "; cin>>instId; 
		cerr<<" ������0��1�� > "; cin>>dir; 
		cerr<<" ��(0)ƽ(1) > "; cin>>kpp;
		cerr<<" �۸� > "; cin>>price;
		cerr<<" ���� > "; cin>>vol;      
		cerr<<" ����������(sse/sze) > "; cin>>exchangID;              
		p->ReqOrderInsert(instId,dir,kpp,price,vol,exchangID); break;
			}
	case 6: { 
		cerr<<" ��� > "; cin>>orderSeq;
		p->ReqOrderAction(orderSeq);break;
			}
	case 7: p->PrintOrders();break;
	case 8: p->PrintTrades();break;
	case 0: exit(0);
	}  
	WaitForSingleObject(g_hEvent,INFINITE);
	ResetEvent(g_hEvent);
	ShowTraderCommand(p);
}

void ShowMdCommand(mdspi* p, bool print=false){
	if(print){
		cerr<<"-----------------------------------------------"<<endl;
		cerr<<" [1] ReqUserLogin              -- ��¼"<<endl;
		cerr<<" [2] SubscribeMarketData       -- ���鶩��"<<endl;
		cerr<<" [0] Exit                      -- �˳�"<<endl;
		cerr<<"----------------------------------------------"<<endl;
	}
	TSecurityFtdcBrokerIDType appId;
	TSecurityFtdcUserIDType	 userId;
	TSecurityFtdcPasswordType passwd;
	char instIdList[100];
	char exchangID[12];

	int cmd;  cin>>cmd;
	switch(cmd){
	case 1: {
		cerr<<" ���͹�˾���루2011�� > ";cin>>appId;
		cerr<<" Ͷ���ߴ��� > ";cin>>userId;
		cerr<<" �������� > ";cin>>passwd;
		p->ReqUserLogin(appId,userId,passwd); break;
			}
	case 2: {
		cerr<<" ��Լ�����ŷָ������Լ�� > "; cin>>instIdList; 
		cerr<<" ����������((sse/sze)�� > "; cin>>exchangID; 
		p->SubscribeMarketData(instIdList,exchangID); break;
			}
	case 0: exit(0);
	}
	WaitForSingleObject(g_hEvent,INFINITE);
	ResetEvent(g_hEvent);
	ShowMdCommand(p);
}
#endif
