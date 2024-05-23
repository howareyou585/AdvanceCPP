#pragma once
#include<functional>
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


