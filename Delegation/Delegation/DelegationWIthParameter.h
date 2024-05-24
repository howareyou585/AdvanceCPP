#pragma once
#include<functional>
#include<list>
using namespace;
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
	CMemberFuctionDelegateMultiParameters(ctype& obj, memFuncPtr ptrMemberFunc)
	{
		m_object = obj;
		m_ptrMemFunc = ptrMemberFunc;
	}
public:
	virtual ReturnType invoke(paramTypes ... parameters) override
	{
		return (m_object.*m_ptrMemFunc)(parameters...);
	}

private:
	ctype m_object;
	memFuncPtr m_ptrMemFunc ;
};

template<typename ReturnType, typename ...parameters>
class CMultiDelegateMultiParameters
{
public:
	 
	CMultiDelegateMultiParameters& operator+=(IDelegateMultiParameters<ReturnType, parameters...>*ptrIDelegate)
	{
		if (ptrIDelegate)
		{
			m_list.emplace_back(ptrIDelegate);
		}
	}
private:
	list<IDelegateMultiParameters<ReturnType, parameters...>*>m_list;
};