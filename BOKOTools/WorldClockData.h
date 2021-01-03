#pragma once
#include "atlstr.h"

/* �Ϸ��� ����
�ƽþ�
-���Ű��ź
-��Ű��ź
-ī���彺ź
-�ε�
-�̾Ḷ
-����
-�߱�
-�븸
-�ʸ���
-�ε��׽þ�
-����
-���ѹα�
-�Ϻ�
����
-���þ�
*/
enum GreenWichWorldClockData
{
	RUSIA_MOSKVA = 201,
	UZBEKISTAN_TASHKENT = 401,	
	PAKISTAN_ISLAMABAD = 402,
	KAZAKHSTAN_NURSULTAN = 501,
	INDIA_NEWDELHI = 551,
	MYANMAR_NAEPIDO = 651,
	MONGOLIA_ULAANBAATAR = 701,
	CHINA_BEIJING = 702,
	TAIWAN_TAIPEI = 703,
	PHILIPPINES_MANILA = 704,
	INDONESIA_JAKARTA = 705,
	NORTH_KOREA_PYONGYANG = 801,
	SOUTH_KOREA_SEOUL = 802,
	JAPAN_TOKYO = 803,
};

CString GetWorldCityName(GreenWichWorldClockData cwcd)
{
	CString strReturnCityName = _T("");
	if		(cwcd == UZBEKISTAN_TASHKENT) strReturnCityName = _T("���Ű��ź Ÿ����Ʈ");
	else if (cwcd == PAKISTAN_ISLAMABAD) strReturnCityName = _T("��Ű��ź �̽��󸶹ٵ�");
	else if (cwcd == KAZAKHSTAN_NURSULTAN) strReturnCityName = _T("ī���彺ź ������ź");
	else if (cwcd == INDIA_NEWDELHI) strReturnCityName = _T("�ε� ������");
	else if (cwcd == MYANMAR_NAEPIDO) strReturnCityName = _T("�̾Ḷ ���ǵ�");
	else if (cwcd == MONGOLIA_ULAANBAATAR) strReturnCityName = _T("���� ������丣");
	else if (cwcd == CHINA_BEIJING) strReturnCityName = _T("�߱� ����¡");
	else if (cwcd == TAIWAN_TAIPEI) strReturnCityName = _T("�븸 Ÿ�̺���");
	else if (cwcd == PHILIPPINES_MANILA) strReturnCityName = _T("�ʸ��� ���Ҷ�");
	else if (cwcd == INDONESIA_JAKARTA) strReturnCityName = _T("�ε��׽þ� ��ī��Ÿ");
	else if (cwcd == NORTH_KOREA_PYONGYANG) strReturnCityName = _T("���� ���");
	else if (cwcd == SOUTH_KOREA_SEOUL) strReturnCityName = _T("���ѹα� ����");
	else if (cwcd == JAPAN_TOKYO) strReturnCityName = _T("�Ϻ� ����");
	else if (cwcd == RUSIA_MOSKVA) strReturnCityName = _T("���þ� ��ũ��");
}