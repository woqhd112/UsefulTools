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

// 명도가 높으면 밝은색 낮으면 어두운색
inline int GetBrightness(int nRv, int nGv, int nBv)
{
	int nMax = nRv;
	int nMin = nRv;

	if (nMax < nGv) nMax = nGv;
	if (nMin > nGv) nMin = nGv;
	if (nMax < nBv) nMax = nBv;
	if (nMin > nBv) nMin = nBv;

	// nRv, nGv, nBv가 전부 동일
	if (nMax == nRv && nMin == nRv)
	{
		nMin = nGv;	// 그냥 nGv값을 최소값으로 설정 nRv만 아니면된다..
	}

	double dFirstBrightness = round(static_cast<double>(nMax) / 2.125);
	double dLastBrightness = round(static_cast<double>(nMin) / 2.125);

	return static_cast<int>(dFirstBrightness + dLastBrightness);
}
