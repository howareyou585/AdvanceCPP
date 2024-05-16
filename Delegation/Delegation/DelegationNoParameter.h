#pragma once
class IDelegate
{
public:
	virtual void invoke() = 0;
	virtual ~IDelegate() {}
};
typedef void(*Func)();
class CStaticDelegate :public IDelegate
{
public:
	
	CStaticDelegate(Func f);
	virtual void invoke() override;
private:

	Func m_ptrFunc;
};


template <typename T> 
class CMemMethodDelegate :public IDelegate
{
public:
	typedef void (T::*memberFunc)();
	CMemMethodDelegate(T* ptrObj, memberFunc ptrfunc)
	{
		m_ptrObject = ptrObj;
		m_ptrFunc = ptrfunc;
	}
	virtual void invoke() override
	{
		(m_ptrObject->*m_ptrFunc)();
	}
private:
	T* m_ptrObject;
	memberFunc m_ptrFunc;

};



class MyA
{
public:
	void say();

};

IDelegate* createDelegate(Func func);

template<typename T>
IDelegate* createDelegate(T* ptrobj, typename CMemMethodDelegate<T>::memberFunc ptrFunc)
{
	return new CMemMethodDelegate<T>(ptrobj, ptrFunc);
}