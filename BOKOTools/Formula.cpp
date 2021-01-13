#include "pch.h"
#include "Formula.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Formula::Formula()
{
}


Formula::~Formula()
{
	if (m_symbol)
	{
		delete m_symbol;
		m_symbol = (Symbol*)nullptr;
	}
}

Formula::Symbol* Formula::GetSymbol()
{
	return m_symbol;
}

Formula* Formula::GetInstance()
{
	return this;
}

Formula::Type Formula::GetType()
{
	return m_type;
}

void Formula::SetSymbol(Symbol* pSymbol)
{
	this->m_symbol = pSymbol;
}

void Formula::SetType(Type type)
{
	this->m_type = type;
}


Calculate::Calculate()
{
	bResult = false;
}

Calculate::~Calculate()
{

}

bool Calculate::GetResult()
{
	return bResult;
}

void Calculate::SetResult(bool bResult)
{
	this->bResult = bResult;
}

Formula::Type Calculate::GetInstanceTypeStr(const CString strType)
{
	Formula::Type rType;
	if (strType == _T("＋") || strType == _T("+") ||
		strType == _T("－") || strType == _T("-") ||
		strType == _T("×") || strType == _T("÷") ||
		strType == _T("^") || strType == _T("%") ||
		strType == _T("!") || strType == _T("√"))
	{
		rType = Formula::Type::TYPE_OPERATOR;
	}
	else if (strType == _T("(") || strType == _T(")"))
	{
		rType = Formula::Type::TYPE_BRACKET;
	}
	else if (strType == _T("."))
	{
		rType = Formula::Type::TYPE_DOT;
	}
	else
	{
		bool bDigit = false;
		for (int i = 0; i < strType.GetLength(); i++)
		{
			if (isdigit(strType.GetAt(i)) != 0) bDigit = true;
			else bDigit = false;
		}

		if (bDigit) rType = Formula::Type::TYPE_NUMBER;
		else rType = Formula::Type::TYPE_NONE;
	}

	return rType;
}

Formula::Operator Calculate::GetInstanceOperTypeStr(const CString strType)
{
	Formula::Operator rOperator;
	if (strType == _T("＋") || strType == _T("+"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_PLUS;
	}
	else if (strType == _T("－") || strType == _T("-"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_MINUS;
	}
	else if (strType == _T("×"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_MULTIPLE;
	}
	else if (strType == _T("÷"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_DIVIDE;
	}
	else if (strType == _T("^"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_EXPONENTIATION;
	}
	else if (strType == _T("%"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_REMAINDER;
	}
	else if (strType == _T("!"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_FACTORIAL;
	}
	else if (strType == _T("√"))
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_ROOT;
	}
	else
	{
		rOperator = Formula::Operator::OPERATOR_TYPE_NONE;
	}

	return rOperator;
}

Formula::Bracket Calculate::GetInstanceBraTypeStr(const CString strType)
{
	Formula::Bracket rBracket;
	if (strType == _T("("))
	{
		rBracket = Formula::Bracket::BRACKET_TYPE_OPEN;
	}
	else if(strType == _T(")"))
	{
		rBracket = Formula::Bracket::BRACKET_TYPE_CLOSE;
	}
	else
	{
		rBracket = Formula::Bracket::BRACKET_TYPE_NONE;
	}

	return rBracket;
}

void Calculate::SwapByOperator(Formula::Symbol* thisSymbol, Formula::Symbol* targetSymbol)
{
	int nSwap = 0;
	if (targetSymbol->m_priority > thisSymbol->m_priority)
	{
		nSwap = targetSymbol->m_priority;
		targetSymbol->m_priority = thisSymbol->m_priority;
		thisSymbol->m_priority = nSwap;
	}
}

// 연산자 우선순위
// + = - < * = / < % < ^ < √ < !
void Calculate::SwapSymbolPriority(std::vector<Formula::Symbol*>& vSymbol)
{
	int nSwap = 0;
	for (int i = 0; i < (int)vSymbol.size(); i++)
	{
		Formula::Symbol* thisSymbol = vSymbol.at(i);
		Formula::Type thisType = thisSymbol->m_type;
		int nThisPriority = thisSymbol->m_priority;

		for (int j = 0; j < (int)vSymbol.size(); j++)
		{
			Formula::Symbol* targetSymbol = vSymbol.at(j);
			Formula::Type targetType = targetSymbol->m_type;
			int nTargetPriority = targetSymbol->m_priority;

			if (thisSymbol->m_depth == targetSymbol->m_depth &&
				thisType == Formula::Type::TYPE_OPERATOR && 
				targetType == Formula::Type::TYPE_OPERATOR)
			{
				Formula::Operator thisOperator = thisSymbol->m_typestruct.typeOperator;
				Formula::Operator targetOperator = targetSymbol->m_typestruct.typeOperator;
				if (thisOperator == Formula::Operator::OPERATOR_TYPE_PLUS && targetOperator == Formula::Operator::OPERATOR_TYPE_MULTIPLE) // priority + < x
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_PLUS && targetOperator == Formula::Operator::OPERATOR_TYPE_DIVIDE) // priority + < /
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_PLUS && targetOperator == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION) // priority + < ^
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_PLUS && targetOperator == Formula::Operator::OPERATOR_TYPE_REMAINDER) // priority + < %
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_PLUS && targetOperator == Formula::Operator::OPERATOR_TYPE_ROOT) // priority + < √
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_PLUS && targetOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL) // priority + < !
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MINUS && targetOperator == Formula::Operator::OPERATOR_TYPE_MULTIPLE) // priority - < x
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MINUS && targetOperator == Formula::Operator::OPERATOR_TYPE_DIVIDE) // priority - < /
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MINUS && targetOperator == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION) // priority - < ^
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MINUS && targetOperator == Formula::Operator::OPERATOR_TYPE_REMAINDER) // priority - < %
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MINUS && targetOperator == Formula::Operator::OPERATOR_TYPE_ROOT) // priority - < √
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MINUS && targetOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL) // priority - < !
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MULTIPLE && targetOperator == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION) // priority x < ^
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MULTIPLE && targetOperator == Formula::Operator::OPERATOR_TYPE_REMAINDER) // priority x < %
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MULTIPLE && targetOperator == Formula::Operator::OPERATOR_TYPE_ROOT) // priority x < √
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_MULTIPLE && targetOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL) // priority x < !
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_DIVIDE && targetOperator == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION) // priority / < ^
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_DIVIDE && targetOperator == Formula::Operator::OPERATOR_TYPE_REMAINDER) // priority / < %
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_DIVIDE && targetOperator == Formula::Operator::OPERATOR_TYPE_ROOT) // priority / < √
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_DIVIDE && targetOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL) // priority / < !
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_REMAINDER && targetOperator == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION) // priority % < ^
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_REMAINDER && targetOperator == Formula::Operator::OPERATOR_TYPE_ROOT) // priority % < √
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_REMAINDER && targetOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL) // priority % < !
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION && targetOperator == Formula::Operator::OPERATOR_TYPE_ROOT) // priority ^ < √
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION && targetOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL) // priority ^ < !
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
				else if (thisOperator == Formula::Operator::OPERATOR_TYPE_ROOT && targetOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL) // priority √ < !
				{
					SwapByOperator(thisSymbol, targetSymbol);
				}
			}
		}
	}
}

std::vector<Formula::Symbol*> Calculate::MergeNumber(std::vector<Formula::Symbol*> vSymbol)
{
	std::vector<Formula::Symbol*> perfectSymbol;

	for (int i = 0; i < (int)vSymbol.size(); i++)
	{
		Formula::Symbol* newSymbol;
		Formula::Symbol* thisSymbol = vSymbol.at(i);
		Formula::Type thisType = thisSymbol->m_type;
		CString strThis = thisSymbol->m_type_str;
		int nSuccess = 0;

		for (int j = i; j < (int)vSymbol.size(); j++)
		{
			Formula::Symbol* targetSymbol = vSymbol.at(j);
			Formula::Type targetType = targetSymbol->m_type;
			CString strTarget = targetSymbol->m_type_str;

			if (thisSymbol != targetSymbol)
			{
				if ((thisType == Formula::Type::TYPE_NUMBER && targetType == Formula::Type::TYPE_NUMBER) || 
					(thisType == Formula::Type::TYPE_NUMBER && targetType == Formula::Type::TYPE_DOT) ||
					(thisType == Formula::Type::TYPE_DOT && targetType == Formula::Type::TYPE_NUMBER))
				{
					strThis.AppendFormat(_T("%s"), strTarget);
					nSuccess++;
				}
				else if (thisSymbol->m_typestruct.typeOperator == Formula::Operator::OPERATOR_TYPE_MINUS &&
						targetType == Formula::Type::TYPE_NUMBER)
				{
					strThis.AppendFormat(_T("%s"), strTarget);
					nSuccess++;
					if ((i > 0 && vSymbol.at(i - 1)->m_type == Formula::Type::TYPE_NUMBER) ||
						(i > 0 && vSymbol.at(i - 1)->m_typestruct.typeBracket == Formula::Bracket::BRACKET_TYPE_CLOSE))
					{
						Formula::Symbol* changedPlus = new Formula::Symbol;
						changedPlus->m_type = Formula::Type::TYPE_OPERATOR;
						changedPlus->m_typestruct.typeOperator = Formula::Operator::OPERATOR_TYPE_PLUS;
						changedPlus->m_priority = thisSymbol->m_priority;
						changedPlus->m_type_str = _T("＋");
						perfectSymbol.push_back(changedPlus);
					}
					thisType = Formula::Type::TYPE_NUMBER;
					thisSymbol->m_priority = 0;
				}
				else if (thisSymbol->m_typestruct.typeOperator == Formula::Operator::OPERATOR_TYPE_PLUS &&
						targetType == Formula::Type::TYPE_NUMBER)
				{
					if ((i > 0 && vSymbol.at(i - 1)->m_type != Formula::Type::TYPE_NUMBER && vSymbol.at(i - 1)->m_typestruct.typeBracket != Formula::Bracket::BRACKET_TYPE_CLOSE))
					{
						strThis.AppendFormat(_T("%s"), strTarget);
						nSuccess++;
						thisType = Formula::Type::TYPE_NUMBER;
						thisSymbol->m_priority = 0;
					}
				}
				else if (thisType == Formula::Type::TYPE_NUMBER &&
						targetType != Formula::Type::TYPE_NUMBER)
				{
					newSymbol = new Formula::Symbol;
					newSymbol->m_type = thisType;
					newSymbol->m_typestruct = thisSymbol->m_typestruct;
					newSymbol->m_type_str = strThis;
					if (nSuccess <= 0)
					{
						newSymbol->m_priority = thisSymbol->m_priority;
					}
					break;
				}
				else
				{
					newSymbol = new Formula::Symbol;
					newSymbol->m_type = thisType;
					newSymbol->m_typestruct = thisSymbol->m_typestruct;
					newSymbol->m_type_str = strThis;
					newSymbol->m_priority = thisSymbol->m_priority;
					break;
				}
			}

			if (j == (int)vSymbol.size() - 1)
			{
				newSymbol = new Formula::Symbol;
				newSymbol->m_type = thisType;
				newSymbol->m_typestruct = thisSymbol->m_typestruct;
				newSymbol->m_type_str = strThis;
			}
		}
		perfectSymbol.push_back(newSymbol);
		if (nSuccess > 0) i += (nSuccess);
	}

	return perfectSymbol;
}

int Calculate::MaxPriority(std::vector<Formula::Symbol*> vSymbol)
{
	int nMaxPriority = 0;

	for (int i = 0; i < (int)vSymbol.size(); i++)
	{
		if (nMaxPriority < vSymbol.at(i)->m_priority)
		{
			nMaxPriority = vSymbol.at(i)->m_priority;
		}
	}

	return nMaxPriority;
}

int Calculate::MaxDepth(std::vector<Formula::Symbol*> vSymbol)
{
	int nMaxDepth = 0;

	for (int i = 0; i < (int)vSymbol.size(); i++)
	{
		if (nMaxDepth < vSymbol.at(i)->m_depth)
		{
			nMaxDepth = vSymbol.at(i)->m_depth;
		}
	}

	return nMaxDepth;
}

bool Calculate::FormulaCondition(CString strText)
{
	bool bReturn = true;

	// 1. 괄호가 쌍으로 안적혀있는 경우
	int nOpenCount = FindCharCount(strText, '(');
	int nCloseCount = FindCharCount(strText, ')');
	if (nOpenCount != nCloseCount)
	{
		bReturn = false;
	}

	// 2. 가장 마지막이 숫자가 아닌경우
	CString strLast = (CString)strText.GetAt(strText.GetLength() - 1);
	Formula::Type lastType = GetInstanceTypeStr(strLast);
	Formula::Bracket lastBracket = GetInstanceBraTypeStr(strLast);
	Formula::Operator lastOperator = GetInstanceOperTypeStr(strLast);
	if (lastType != Formula::Type::TYPE_NUMBER &&
		lastBracket != Formula::Bracket::BRACKET_TYPE_CLOSE &&
		lastOperator != Formula::Operator::OPERATOR_TYPE_FACTORIAL)
	{
		bReturn = false;
	}

	return bReturn;
}

int Calculate::FindCharCount(CString strTarget, char cSplit)
{
	int nCount = 0;
	int nFind = strTarget.Find(cSplit);
	if (nFind != -1) nCount++;
	for (int i = 0; nFind != -1; i++)
	{
		nFind = strTarget.Find(cSplit, nFind + 1);
		if (nFind != -1) nCount++;
	}
	return nCount;
}

void Calculate::PeelBracketToFormula(std::vector<Formula::Symbol*>& vSymbol)
{
	for (int i = 0; i < (int)vSymbol.size(); i++)
	{
		Formula::Symbol* symbol = vSymbol.at(i);
		if (symbol->m_type == Formula::Type::TYPE_BRACKET)
		{
			delete symbol;
			symbol = (Formula::Symbol*)nullptr;
			vSymbol.erase(vSymbol.begin() + i);
			i -= 1;
		}
	}
}

bool Calculate::IsBracket(CString strText)
{
	bool bReturn = false;
	if ((CString)strText.GetAt(0) == _T("(") && (CString)strText.GetAt(strText.GetLength() - 1) == _T(")")) bReturn = true;
	return bReturn;
}

// 해당 괄호의 뎁스 설정
void Calculate::SetSymbolDepth(std::vector<Formula::Symbol*>& vSymbol)
{
	for (int i = 0; i < (int)vSymbol.size(); i++)
	{
		Formula::Symbol* thisSymbol = vSymbol.at(i);
		if (thisSymbol->m_type == Formula::Type::TYPE_OPERATOR)
		{
			int nDepth = 0;
			for (int j = i - 1; j >= 0; j--)
			{
				Formula::Symbol* targetSymbol = vSymbol.at(j);
				if (targetSymbol->m_type == Formula::Type::TYPE_BRACKET)
				{
					if (targetSymbol->m_typestruct.typeBracket == Formula::Bracket::BRACKET_TYPE_OPEN)
					{
						nDepth++;
					}
					else if (targetSymbol->m_typestruct.typeBracket == Formula::Bracket::BRACKET_TYPE_CLOSE)
					{
						nDepth--;
					}
				}
			}
			thisSymbol->m_depth = nDepth;
		}
	}
}

// 뎁스별로 우선순위 설정
void Calculate::SetSymbolPriority(std::vector<Formula::Symbol*>& vSymbol)
{
	int nCount = 0;
	int nMaxDepth = MaxDepth(vSymbol);
	for (int i = nMaxDepth; i >= 0; i--)
	{
		for (int j = 0; j < (int)vSymbol.size(); j++)
		{
			Formula::Symbol* thisSymbol = vSymbol.at(j);
			if (thisSymbol->m_type == Formula::Type::TYPE_OPERATOR)
			{
				if (thisSymbol->m_depth == i)
				{
					thisSymbol->m_priority = ++nCount;
				}
			}
		}
	}
}

CString Calculate::ConvertSymbol(CString strText, bool isResult)
{
	if (!isResult)
	{
		if (GetInstanceOperTypeStr(strText) == Formula::Operator::OPERATOR_TYPE_PLUS)
		{
			strText = _T("+");
		}
		else if (GetInstanceOperTypeStr(strText) == Formula::Operator::OPERATOR_TYPE_MINUS)
		{
			strText = _T("-");
		}
	}
	else
	{
		if (GetInstanceOperTypeStr(strText) == Formula::Operator::OPERATOR_TYPE_PLUS)
		{
			strText = _T("＋");
		}
		else if (GetInstanceOperTypeStr(strText) == Formula::Operator::OPERATOR_TYPE_MINUS)
		{
			strText = _T("－");
		}
	}

	return strText;
}

CString Calculate::CalculateToVector(std::vector<Formula::Symbol*>& vSymbol)
{
	CString strFormat = _T("0");
	int nStaticPriority = 1;
	int nMaxProirity = MaxPriority(vSymbol);
	while (true)
	{
		for (int i = 0; i < (int)vSymbol.size(); i++)
		{
			Formula::Type symbolType = vSymbol.at(i)->m_type;
			if (symbolType == Formula::Type::TYPE_OPERATOR)
			{
				Formula::Symbol* thisSymbol = vSymbol.at(i);
				int nPriority = thisSymbol->m_priority;
				if (nPriority == nStaticPriority)
				{
					Formula::Symbol* preSymbol;
					Formula::Symbol* sufSymbol;
					try
					{
						preSymbol = vSymbol.at(i - 1);
					}
					catch (const std::out_of_range)
					{
						preSymbol = vSymbol.at(i);
					}
					try
					{
						sufSymbol  = vSymbol.at(i + 1);
					}
					catch (const std::out_of_range)
					{
						sufSymbol = vSymbol.at(i);
					}

					Formula::Operator thisOperator = vSymbol.at(i)->m_typestruct.typeOperator;
					if (!Calculator(thisOperator, _ttof(preSymbol->m_type_str), _ttof(sufSymbol->m_type_str), strFormat))
					{
						return strFormat;
					}

					NewAllocateSymbol(vSymbol, thisOperator, strFormat, i);

					if (thisOperator != Formula::Operator::OPERATOR_TYPE_ROOT)
					{
						delete preSymbol;
						preSymbol = (Formula::Symbol*)nullptr;
					}

					delete thisSymbol;
					thisSymbol = (Formula::Symbol*)nullptr;

					if (thisOperator != Formula::Operator::OPERATOR_TYPE_FACTORIAL)
					{
						delete sufSymbol;
						sufSymbol = (Formula::Symbol*)nullptr;
					}

					nStaticPriority++;
					break;
				}
			}
		}
		if (nStaticPriority > nMaxProirity) break;
	}
	return strFormat;
}

void Calculate::NewAllocateSymbol(std::vector<Formula::Symbol*>& vSymbol, Formula::Operator oOperator, CString strFormula, int nIdx)
{
	int nMaxDynamicLoopCnt = 0;
	int nMinDynamicLoopCnt = 0;
	if (oOperator == Formula::Operator::OPERATOR_TYPE_ROOT)
	{
		nMaxDynamicLoopCnt = nIdx;
		nMinDynamicLoopCnt = nIdx + 2;
	}
	else if (oOperator == Formula::Operator::OPERATOR_TYPE_FACTORIAL)
	{
		nMaxDynamicLoopCnt = nIdx - 1;
		nMinDynamicLoopCnt = nIdx + 1;
	}
	else
	{
		nMaxDynamicLoopCnt = nIdx - 1;
		nMinDynamicLoopCnt = nIdx + 2;
	}

	std::vector<Formula::Symbol*> assignedSymbol;
	for (int j = 0; j < nMaxDynamicLoopCnt; j++)
	{
		assignedSymbol.push_back(vSymbol.at(j));
	}

	Formula::Symbol* newSymbol = new Formula::Symbol;
	newSymbol->m_type = Formula::Type::TYPE_NUMBER;
	newSymbol->m_type_str = strFormula;
	assignedSymbol.push_back(newSymbol);

	for (int j = nMinDynamicLoopCnt; j < (int)vSymbol.size(); j++)
	{
		assignedSymbol.push_back(vSymbol.at(j));
	}

	vSymbol.assign(assignedSymbol.begin(), assignedSymbol.end());
	assignedSymbol.clear();
}

void Calculate::GrantByFormula(CString strText)
{
	for (int i = 0; i < strText.GetLength(); i++)
	{
		CString strAt = (CString)strText.GetAt(i);
		Formula::Symbol* symbol = new Formula::Symbol;
		symbol->m_type = GetInstanceTypeStr(strAt);
		if (symbol->m_type == Formula::Type::TYPE_OPERATOR) symbol->m_typestruct.typeOperator = GetInstanceOperTypeStr(strAt);
		else if (symbol->m_type == Formula::Type::TYPE_BRACKET) symbol->m_typestruct.typeBracket = GetInstanceBraTypeStr(strAt);
		symbol->m_type_str = ConvertSymbol(strAt, false);
		vSymbol.push_back(symbol);
	}
}

CString Calculate::ResultOperate(CString strText)
{
	GrantByFormula(strText);	// 수식에따라 심볼 부여 (타입은 자동 설정됨)
	std::vector<Formula::Symbol*> newSymbolVector = MergeNumber(vSymbol);	// 심볼의 각각의 번호를 경우에따라 합침
	SetSymbolDepth(newSymbolVector);	// 연산자를 괄호에따른 뎁스 설정
	SetSymbolPriority(newSymbolVector);	// 연산자의 뎁스에따라 우선순위 설정
	SwapSymbolPriority(newSymbolVector);	// 연산자의 우선순위를 곱,나누기 / 더하기,빼기에 따라 우선순위 스왑
	PeelBracketToFormula(newSymbolVector);	// 모든 넘버에 등록된 괄호 삭제
	
	CString strResult = ConvertSymbol(CalculateToVector(newSymbolVector), true);

	ClearVector(vSymbol);
	ClearVector(newSymbolVector);
	bResult = true;
	return strResult;
}

bool Calculate::Calculator(Formula::Operator type, double dFormula1, double dFormula2, CString& strResult)
{
	bool bSuccess = true;
	double dResult = 0;
	if (type == Formula::Operator::OPERATOR_TYPE_DIVIDE)
	{
		if (dFormula2 == 0)
		{
			strResult = _T("0으로 나눌 수 없습니다.");
			bSuccess = false;
		}
		else
		{
			dResult = dFormula1 / dFormula2;
			strResult.Format(_T("%g"), dResult);
		}
	}
	else if (type == Formula::Operator::OPERATOR_TYPE_MULTIPLE)
	{
		dResult = dFormula1 * dFormula2;
		strResult.Format(_T("%g"), dResult);
	}
	else if (type == Formula::Operator::OPERATOR_TYPE_PLUS)
	{
		dResult = dFormula1 + dFormula2;
		strResult.Format(_T("%g"), dResult);
	}
	else if (type == Formula::Operator::OPERATOR_TYPE_MINUS)
	{
		dResult = dFormula1 - dFormula2;
		strResult.Format(_T("%g"), dResult);
	}
	else if (type == Formula::Operator::OPERATOR_TYPE_EXPONENTIATION)
	{
		dResult = pow(dFormula1, dFormula2);
		strResult.Format(_T("%g"), dResult);
	}
	else if (type == Formula::Operator::OPERATOR_TYPE_REMAINDER)
	{
		dResult = fmod(dFormula1, dFormula2);
		strResult.Format(_T("%g"), dResult);
	}
	else if (type == Formula::Operator::OPERATOR_TYPE_ROOT)
	{
		if (dFormula2 < 0)
		{
			strResult = _T("음수로 √계산을 할 수 없습니다.");
			bSuccess = false;
		}
		else
		{
			dResult = sqrt(dFormula2);
			strResult.Format(_T("%g"), dResult);
		}
	}
	else if (type == Formula::Operator::OPERATOR_TYPE_FACTORIAL)
	{
		dResult = 1;
		if (dFormula1 < 0)
		{
			strResult = _T("음수로 !계산을 할 수 없습니다.");
			bSuccess = false;
		}
		else if (dFormula1 - static_cast<unsigned long long>(dFormula1) > 0)
		{
			strResult = _T("소수로 !계산을 할 수 없습니다.");
			bSuccess = false;
		}
		else
		{
			for (unsigned long long i = static_cast<unsigned long long>(dFormula1); i > 0; --i)
			{
				
				dResult *= i;
			}
			strResult.Format(_T("%llu"), dResult);
		}

	}

	return bSuccess;
}


bool Calculate::IsDot(CString strText)
{
	bool bReturn = true;

	Formula::Type type = GetInstanceTypeStr((CString)strText.GetAt(strText.GetLength() - 1));
	if (type != Formula::Type::TYPE_NUMBER)
	{
		bReturn = false;
	}

	if (strText.GetLength() > 1)
	{
		bool bSymbol = false;
		int nIndex = 0;
		CString strSymbol = _T("");
		for (int i = strText.GetLength() - 2; i >= 0; i--)
		{
			CString strPrefix = (CString)strText.GetAt(i);
			Formula::Type preType = GetInstanceTypeStr(strPrefix);
			if (preType == Formula::Type::TYPE_OPERATOR)
			{
				strSymbol = strPrefix;
				bSymbol = true;
				break;
			}
			nIndex++;
		}

		if (bSymbol)
		{
			CString strCheck = _T("");
			AfxExtractSubString(strCheck, strText, 1, *(TCHAR*)(LPCTSTR)strSymbol);
			if (strCheck.Find('.') != -1)
			{
				bReturn = false;
			}
		}
	}

	return bReturn;
}

void Calculate::ClearVector(std::vector<Formula::Symbol*>& formatVector)
{
	for (int i = 0; i < (int)formatVector.size(); i++)
	{
		Formula::Symbol* formatSymbol = formatVector.at(i);
		delete formatSymbol;
		formatSymbol = (Formula::Symbol*)nullptr;
	}
	formatVector.clear();
}