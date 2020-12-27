#pragma once

inline int MinRGBColor(int nRv, int nCalcv)
{
	if (nRv - nCalcv < 0) return 0;
	return nRv - nCalcv;
}

inline int MaxRGBColor(int nRv, int nCalcv)
{
	if (nRv + nCalcv > 255) return 255;
	return nRv + nCalcv;
}

// ���� ������ ������ ������ ��ο��
inline int GetBrightness(int nRv, int nGv, int nBv)
{
	int nMax = nRv;
	int nMin = nRv;

	if (nMax < nGv) nMax = nGv;
	if (nMin > nGv) nMin = nGv;
	if (nMax < nBv) nMax = nBv;
	if (nMin > nBv) nMin = nBv;

	// nRv, nGv, nBv�� ���� ����
	if (nMax == nRv && nMin == nRv)
	{
		nMin = nGv;	// �׳� nGv���� �ּҰ����� ���� nRv�� �ƴϸ�ȴ�..
	}

	double dFirstBrightness = round(static_cast<double>(nMax) / 2.125);
	double dLastBrightness = round(static_cast<double>(nMin) / 2.125);

	return static_cast<int>(dFirstBrightness + dLastBrightness);
}
