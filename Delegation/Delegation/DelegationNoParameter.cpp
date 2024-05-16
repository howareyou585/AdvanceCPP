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
