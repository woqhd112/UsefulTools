#pragma once
#include "atlstr.h"
#include <vector>

class Formula
{
public:
	enum Type
	{
		TYPE_NONE			= 0,
		TYPE_OPERATOR		= 1,
		TYPE_NUMBER			= 2,
		TYPE_DOT			= 3,
		TYPE_BRACKET		= 4,
	};

	enum Bracket
	{
		BRACKET_TYPE_NONE	= 0,
		BRACKET_TYPE_OPEN	= 1,
		BRACKET_TYPE_CLOSE	= 2
	};

	enum Operator
	{
		OPERATOR_TYPE_NONE				= 0,
		OPERATOR_TYPE_PLUS				= 1,
		OPERATOR_TYPE_MINUS				= 2,
		OPERATOR_TYPE_MULTIPLE			= 3,
		OPERATOR_TYPE_DIVIDE			= 4,
		OPERATOR_TYPE_EXPONENTIATION	= 5,
		OPERATOR_TYPE_REMAINDER			= 6,
		OPERATOR_TYPE_ROOT				= 7,
		OPERATOR_TYPE_FACTORIAL			= 8
	};

	struct TypeStruct
	{
		Bracket typeBracket = BRACKET_TYPE_NONE;
		Operator typeOperator = OPERATOR_TYPE_NONE;
	};

	Formula();
	~Formula();


	struct Symbol
	{
		CString m_type_str;
		int m_priority = 0;
		int m_depth = 0;
		Type m_type = TYPE_NONE;
		TypeStruct m_typestruct;
	};


	Symbol* GetSymbol();
	Formula* GetInstance();
	Type GetType();

	void SetSymbol(Symbol* pSymbol);
	void SetType(Type type);


private:
	Symbol* m_symbol;
	Type m_type;

};

class Calculate
{
public:
	Calculate();
	~Calculate();

	bool GetResult();
	void SetResult(bool bResult);

	bool FormulaCondition(CString strText);
	CString ResultOperate(CString strText);
	Formula::Type GetInstanceTypeStr(const CString strType);
	Formula::Operator GetInstanceOperTypeStr(const CString strType);
	Formula::Bracket GetInstanceBraTypeStr(const CString strType);
	bool IsDot(CString strText);
	

private:
	std::vector<Formula::Symbol*> vSymbol;
	bool bResult;

	void GrantByFormula(CString strText);
	std::vector<Formula::Symbol*> MergeNumber(std::vector<Formula::Symbol*> vSymbol);
	void SetSymbolDepth(std::vector<Formula::Symbol*>& vSymbol);
	void SetSymbolPriority(std::vector<Formula::Symbol*>& vSymbol);
	void SwapSymbolPriority(std::vector<Formula::Symbol*>& vSymbol);
	void PeelBracketToFormula(std::vector<Formula::Symbol*>& vSymbol);
	CString CalculateToVector(std::vector<Formula::Symbol*>& vSymbol);

	int FindCharCount(CString strTarget, char cSplit);
	int MaxPriority(std::vector<Formula::Symbol*> vFormula);
	int MaxDepth(std::vector<Formula::Symbol*> vSymbol);
	bool Calculator(Formula::Operator type, double dFormula1, double dFormula2, CString& strResult);
	bool IsBracket(CString strText);
	CString ConvertSymbol(CString strText, bool isResult);
	void SwapByOperator(Formula::Symbol* thisSymbol, Formula::Symbol* targetSymbol);
	void ClearVector(std::vector<Formula::Symbol*>& formatVector);
	void NewAllocateSymbol(std::vector<Formula::Symbol*>& vSymbol, Formula::Operator oOperator, CString strFormula, int nIdx);
};

