#pragma once
#include "atlstr.h"

/*
OECD ���Ա� ������ ó��
-ĳ����
-����
-����ũ
-���̽�����
-�븣����
-��Ű
-������
-��������
-������
-���Ϸ���
-���⿡
-����
-������
-������
-����Ʈ����
-�״�����
-����θ�ũ
-��Ż����
-�Ϻ�
-�ɶ���
-ȣ��
-��������
-�߽���
-ü��
-�밡��
-������
-���ѹα�
-���ι�Ű��
-ĥ��
-���κ��Ͼ�
-�̽���
-������Ͼ�
-��Ʈ���
-�����ƴϾ�
-�ݷҺ��
-�ڽ�Ÿ��ī
-���þ�
-���ư�
-�����
-�ε�
-�ε��׽þ�
-�߱�

�̰��Ա� �Ϻ�
-�븸
-�ʸ���
-����

*/

enum GreenWichWorldClockData
{
	CANADA = 0,
	USA = 1,
	ENGLAND = 2,
	DENMARK  = 3,
	ISLAND = 4,
	NORWAY = 5,
	TURKEY = 6,
	SPAIN = 7,
	PORTUGAL = 8,
	FRANCE = 9,
	IRELAND = 10,
	BELGIUM = 11,
	GERMANY = 12,
	GREECE = 13,
	SWEDEN = 14,
	SWISS = 15,
	AUSTRIA = 16,
	NETHERLANDS = 17,
	LUXEMBOURG = 18,
	ITALY = 19,
	FINLAND = 21,
	AUSTRALIA = 22,
	NEWZEALAND = 23,
	MEXICO = 24,
	CZECH = 25,
	HUNGARY = 26,
	POLAND = 27,
	SLOVAKIA = 29,
	CHILE = 30,
	CLOVENIAN = 31,
	ISRAEL = 32,
	ESTONIA = 33,
	LATVIA = 34,
	LITHUANIA = 35,
	COLUMBIA = 36,
	COSTARICA = 37,
	SOUTHAFRICA = 39,
	BRAZIL = 40,
	RUSIA_MOSKVA = 201,
	INDIA_NEWDELHI = 551,
	CHINA_BEIJING = 702,
	TAIWAN_TAIPEI = 703,
	PHILIPPINES_MANILA = 704,
	INDONESIA_JAKARTA = 705,
	NORTHKOREA_PYONGYANG = 801,
	SOUTHKOREA_SEOUL = 802,
	JAPAN_TOKYO = 803,

};

CString GetWorldCityName(GreenWichWorldClockData cwcd)
{
	CString strReturnCityName = _T("");
	
	if (cwcd == INDIA_NEWDELHI) strReturnCityName = _T("�ε� ������");
	else if (cwcd == CHINA_BEIJING) strReturnCityName = _T("�߱� ����¡");
	else if (cwcd == TAIWAN_TAIPEI) strReturnCityName = _T("�븸 Ÿ�̺���");
	else if (cwcd == PHILIPPINES_MANILA) strReturnCityName = _T("�ʸ��� ���Ҷ�");
	else if (cwcd == INDONESIA_JAKARTA) strReturnCityName = _T("�ε��׽þ� ��ī��Ÿ");
	else if (cwcd == NORTHKOREA_PYONGYANG) strReturnCityName = _T("���� ���");
	else if (cwcd == SOUTHKOREA_SEOUL) strReturnCityName = _T("���ѹα� ����");
	else if (cwcd == JAPAN_TOKYO) strReturnCityName = _T("�Ϻ� ����");
	else if (cwcd == RUSIA_MOSKVA) strReturnCityName = _T("���þ� ��ũ��");
}