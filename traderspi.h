/*!
* \file traderspi.h
* \brief ʵ�ֽ��׽ӿ�
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
#ifndef ORDER_TRADERSPI_H_
#define ORDER_TRADERSPI_H_
#pragma once

#include "api/trade/win/public/SecurityFtdcTraderApi.h"

class traderspi:public CSecurityFtdcTraderSpi
{
public:

	traderspi(CSecurityFtdcTraderApi* api):pUserApi(api){};

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///��¼������Ӧ
	virtual void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CSecurityFtdcInstrumentField *pInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CSecurityFtdcTradingAccountField *pTradingAccount, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CSecurityFtdcInvestorPositionField *pInvestorPosition, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������������Ӧ
	virtual void OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);	

	///����Ӧ��
	virtual void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	virtual void OnHeartBeatWarning(int nTimeLapse);	

	///����֪ͨ
	virtual void OnRtnOrder(CSecurityFtdcOrderField *pOrder);

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CSecurityFtdcTradeField *pTrade);

public:

	///�û���¼����
	void ReqUserLogin(TSecurityFtdcBrokerIDType	appId,
		TSecurityFtdcUserIDType	userId,TSecurityFtdcPasswordType	passwd);
	
	///�����ѯ��Լ
	void ReqQryInstrument(TSecurityFtdcInstrumentIDType instId);
	
	///�����ѯ�ʽ��˻�
	void ReqQryTradingAccount();
	
	///�����ѯͶ���ֲ߳�
	void ReqQryInvestorPosition(TSecurityFtdcInstrumentIDType instId);
	
	///����¼������
	void ReqOrderInsert(TSecurityFtdcInstrumentIDType instId,
		TSecurityFtdcDirectionType dir, TSecurityFtdcCombOffsetFlagType kpp,
		TSecurityFtdcPriceType price,   TSecurityFtdcVolumeType vol, 
		TSecurityFtdcExchangeIDType exchangID);
	
	///������������
	void ReqOrderAction(TSecurityFtdcSequenceNoType orderSeq);

	// �Ƿ��յ��ɹ�����Ӧ
	bool IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo);

	void PrintOrders();
	void PrintTrades();

private:
	CSecurityFtdcTraderApi* pUserApi;
};

#endif