#pragma once
#include<functional>
#include<list>
#include<iostream>
using  namespace std;
template<typename ReturnType, typename ...paramTypes>
class IDelegateMultiParameters
{
public:
	virtual ReturnType  invoke(paramTypes ... parameters) = 0;
};

template<typename ReturnType, typename ... paramTypes>
class CCommonDelegateMultiParameters :
	public IDelegateMultiParameters<ReturnType, paramTypes...>
{
public:
	//using ptrFunc = ReturnType(*)(paramTypes... parameters);
	
	CCommonDelegateMultiParameters(function<ReturnType(paramTypes...)> pf)
	{
		m_ptrFunc = pf;
	}
	virtual ReturnType invoke(paramTypes ... parameters)
	{
		ReturnType ret;
		if (m_ptrFunc)
		{
			ret = m_ptrFunc(parameters...);
		}
		return ret;
	}
private:
	function<ReturnType(paramTypes...)> m_ptrFunc;
};


template<typename ReturnType, typename ctype, typename ... paramTypes>
class CMemberFuctionDelegateMultiParameters :
	public IDelegateMultiParameters< ReturnType, paramTypes...>
{
public:
	using memFuncPtr = ReturnType(ctype::*)(paramTypes...);
	CMemberFuctionDelegateMultiParameters(ctype* obj, memFuncPtr ptrMemberFunc)
	{
		m_object = obj;
		m_ptrMemFunc = ptrMemberFunc;
	}
public:
	virtual ReturnType invoke(paramTypes ... parameters) override
	{
		return (m_object->*m_ptrMemFunc)(parameters...);
	}

private:
	ctype* m_object;
	memFuncPtr m_ptrMemFunc ;
};

template<typename ReturnType, typename ...parameters>
class CMultiDelegateMultiParameters
{
public:
	 
	~CMultiDelegateMultiParameters()
	{
		for (auto it = m_list.begin(); it != m_list.end(); )
		{
			IDelegateMultiParameters<ReturnType, parameters...>*ptrIDelegate = *it;
			if (ptrIDelegate)
			{
				delete ptrIDelegate;
				ptrIDelegate;
				it = m_list.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	CMultiDelegateMultiParameters& operator+=(IDelegateMultiParameters<ReturnType, parameters...>*ptrIDelegate)
	{
		if (ptrIDelegate)
		{
			m_list.emplace_back(ptrIDelegate);
		}
		return *this;
	}
	CMultiDelegateMultiParameters& operator-=(IDelegateMultiParameters<ReturnType, parameters...>* ptrIDelegate)
	{
		if (ptrIDelegate)
		{
			auto it = find(m_list.begin(), m_list.end(), ptrIDelegate);
			if ( it!=m_list.end())
			{
				m_list.erase(it);
			}
		}
		return *this;
	}
	void operator()(parameters... ps)
	{
		for (auto it = m_list.begin(); it != m_list.end(); it++)
		{
			IDelegateMultiParameters<ReturnType, parameters...>* ptrItem = *it;
			if(ptrItem)
			{
				ReturnType rt = ptrItem->invoke(ps...);
				cout << "rt = " << rt << endl;
			}
		}
	}
private:
	list<IDelegateMultiParameters<ReturnType, parameters...>*>m_list;
};

//创建普通函数的IDelegate 对象
template<typename ReturnType, typename ...parameters>
IDelegateMultiParameters<ReturnType, parameters...>* CreateDelegateWithMultiParamters(ReturnType(*ptrCommonFunc)(parameters...))
{
	return new CCommonDelegateMultiParameters<ReturnType, parameters...>(ptrCommonFunc);
}

//创建成员函数的IDelegate 对象
template<typename ReturnType, typename ctype, typename ...parameters>
IDelegateMultiParameters<ReturnType, parameters...>* CreateDelegateWithMultiParamters(ctype* ptrObject, ReturnType(ctype::*ptrMemeberFunc)(parameters...))
{
	return new CMemberFuctionDelegateMultiParameters<ReturnType, ctype, parameters...>(ptrObject, ptrMemeberFunc);
}