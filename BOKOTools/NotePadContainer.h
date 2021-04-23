#pragma once
#include <vector>
#include <algorithm>


template<typename T>
class NotePadContainer
{

public:

	NotePadContainer()
	{
		nCurrentIndex = 0;
	}

	NotePadContainer(std::vector<T>& allocObject)
	{
		nCurrentIndex = 0;
		notepadObject = allocObject;
	}

	~NotePadContainer()
	{
	
	}

	T& At(int nObjectIndex)
	{
		//pointerObject = notepadObject.at(nObjectIndex);

		//return pointerObject;
		nCurrentIndex = nObjectIndex;
		return notepadObject.at(nObjectIndex);
	}

	T Begin()
	{
		return (T)notepadObject.begin();
	}

	T End()
	{
		return notepadObject.at((int)notepadObject.size() - 1);
	}

	bool Empty()
	{
		if (notepadObject.empty())
			return true;

		return false;
	}

	void Push(T pushObject)
	{
		notepadObject.push_back(pushObject);
	}

	int Size()
	{
		return (int)notepadObject.size();
	}

	T& Pop(int nObjectIndex)
	{
		T object = notepadObject.at(nObjectIndex);
		notepadObject.erase(notepadObject.begin() + nObjectIndex);

		return &object;
	}

	T& Pop()
	{
		T object = notepadObject.end();
		notepadObject.erase(notepadObject.end());

		return &object;
	}

	void Swap(int nChangeIndex1, int nChangeIndex2)
	{
		std::iter_swap(notepadObject.begin() + nChangeIndex1, notepadObject.begin() + nChangeIndex2);
	}

	void Erase(int nObjectIndex)
	{
		if ((notepadObject.size() - 1) < nObjectIndex)
			return;

		notepadObject.erase(notepadObject.begin() + nObjectIndex);
	}

	void Clear()
	{
		notepadObject.clear();
	}

	void Assign(NotePadContainer<T> targetObject, int nBeginIndex, int nEndIndex)
	{
		notepadObject.clear();
		for (int i = nBeginIndex; i <= nEndIndex; i++)
		{
			notepadObject.push_back(targetObject.At(i));
		}
		targetObject.Clear();
	}

	bool Find(T searchObject, T& findReturnObject)
	{
		bool bFind = false;

		if ((notepadObject.size() - 1) < nObjectIndex)
			return bFind;

		for (int i = 0; i < (int)notepadObject.size(); i++)
		{
			T targetObject = notepadObject.at(i);
			if (targetObject == searchObject)
			{
				bFind = true;
				findReturnObject = &targetObject;
				break;
			}
		}

		return bFind;
	}

	bool Find(int nSearchIndex, T& findReturnObject)
	{
		bool bFind = false;

		if ((notepadObject.size() - 1) < nObjectIndex)
			return bFind;

		for (int i = 0; i < (int)notepadObject.size(); i++)
		{
			T targetObject = notepadObject.at(i);
			T searchObject = notepadObject.at(nSearchIndex);
			if (targetObject == searchObject)
			{
				bFind = true;
				findReturnObject = &searchObject;
				break;
			}
		}

		return bFind;
	}

	/*void FreeAll()
	{
		for (int i = 0; i < (int)notepadObject.size(); i++)
		{
			T freeObject = notepadObject.at(i);
			delete freeObject;
			freeObject = NULL;
		}
		notepadObject.clear();
	}*/

	/*bool operator == (NotePadContainer<T>& t1)
	{
		return (t1.pointerObject == pointerObject);
	}*/

	bool operator == (NotePadContainer<T>& t1)
	{
		return (notepadObject == t1.notepadObject);
	}

	/*NotePadContainer<T>& operator = (NotePadContainer<T>& t1)
	{
		notepadObject.assign(t1.Begin(), t1.End());

		return this;
	}

	std::vector<T>& operator = (std::vector<T>& t1)
	{
		notepadObject = t1;

		return notepadObject;
	}*/

	T& operator = (T& t1)
	{
		if (nCurrentIndex > notepadObject.size() - 1)
			return nullptr;

		T returnT = notepadObject.at(nCurrentIndex);
		returnT = t1;

		return returnT;
	}

private:

	std::vector<T> notepadObject;

	T pointerObject;

	int nCurrentIndex;

};

