/*!
* \file config.h
* \brief ������Ҫ���ӵ�LTS������Ϣ
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
#ifndef MD_CONFIG_H_
#define MD_CONFIG_H_
#pragma once

/// \brief ������
/// �����ų�ʼֵ
int requestId=0;

/// \brief ǰ�õ�ַ
/// ǰ�õ�ַ��ʹ�û���֤ȯ��Ȩ������Ե�ַ
char mdFront[]   ="tcp://211.144.195.163:34513";
char tradeFront[]="tcp://211.144.195.163:34505";
#endif