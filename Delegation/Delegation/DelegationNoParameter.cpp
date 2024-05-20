#include "DelegationNoParameter.h"
#include <iostream>
using namespace std;
CStaticDelegate::CStaticDelegate(Func f):m_ptrFunc (f)
{
	
}

void CStaticDelegate::invoke()
{
	if (m_ptrFunc)
	{
		m_ptrFunc();
	}
}

IDelegate* createDelegate(Func func)
{
	IDelegate* ptDelegateObj = new CStaticDelegate(func);
	return ptDelegateObj;
}



void MyA::say()
{
	cout << "我太开心了" << endl;
}

void CMultiDelegate::operator()()
{
	for (auto it = m_lstDelegate.begin(); it != m_lstDelegate.end(); it++)
	{
		IDelegate* ptrDelegate = (*it);
		if (ptrDelegate)
		{
			ptrDelegate->invoke();
		}
	}
}

CMultiDelegate & CMultiDelegate::operator+=(IDelegate * ptrDelegate)
{
	if (ptrDelegate)
	{
		bool bEqual = false;
		for (auto it = m_lstDelegate.begin(); it != m_lstDelegate.end(); it++)
		{
			IDelegate* p = *it;
			if (p && p == ptrDelegate)
			{
				bEqual =true;
				break;
			}
		}
		if (!bEqual)
		{
			m_lstDelegate.emplace_back(ptrDelegate);
		}
	}
	return *this;
}

CMultiDelegate & CMultiDelegate::operator-=(IDelegate * ptrDelegate)
{
	if (ptrDelegate)
	{
		
		for (auto it = m_lstDelegate.begin(); it != m_lstDelegate.end(); it++)
		{
			IDelegate* p = *it;
			if (p && p == ptrDelegate)
			{
				delete p;
				p = nullptr;
				m_lstDelegate.erase(it);
				break;
			}
		}
	}
	return *this;
}
