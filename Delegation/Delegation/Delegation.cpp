// Delegation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include "DelegationBaseVersion.h"
#include "DelegationPolymorphicVersion.h"
#include "DelegationNoParameter.h"
#include "DelegationWIthParameter.h"
#include <memory>

void say()
{
	cout << "你好" << endl;
}
int add(int a, int b)
{
	return a + b;
}
double max(int a, double b,  float c)
{
	double r = 0.0;
	if(a>=b)
	{ 
		r = a;
	}
	else
	{
		r = b;
	}
	if (r < c)
	{
		r = c;
	}
	return r;
}
class MyClass
{
public:
	int add(int a, int b)
	{
		return a + b;
	}
};
int main()
{
    std::cout << "Hello World!\n"; 
	//1.基本版
	/*BaseB baseB;
	BaseA baseA;
	baseB.m_ptra =&baseA;
	baseB.OnEvent(12);*/

	//2.多态版
	/*auto ptrEventA = make_shared<EventCallA>();
	auto ptrEventB = make_shared <EventCallB>();
	auto ptrEventSystem = make_shared<EventCallSystem>();
	ptrEventSystem->m_ptrSystem = new System();
	Receiver r;
	r.AddEventCaller(ptrEventA.get());
	r.AddEventCaller(ptrEventB.get());
	r.AddEventCaller(ptrEventSystem.get());
	
	r.OnEvent(12);*/

	//3.无参数版
	//CMultiDelegate onclick;
	//auto ptrDelegate = createDelegate(say);
	//onclick += ptrDelegate;
	//MyA *ptrA = new MyA();

	//auto ptrDelegate2 = createDelegate(ptrA, &MyA::say);
	//onclick += ptrDelegate2;
	////md.operator+=(ptrDelegate);
	////md.operator+=(ptrDelegate2);
	//onclick();

	//4.有参数版
	

	CCommonDelegateMultiParameters<int, int, int> c(add);
	int ret = c.invoke(10,20);
	cout << "10+20=" << ret << endl;
	CCommonDelegateMultiParameters<double, int, double, float> d(max);
	double m = d.invoke(36, 95.5, 100.0f);
	cout << "max=" << m << endl;

	MyClass mc;
	//function<int(int, int)> funcx = std::bind(&MyClass::add, &mc, std::placeholders::_1, std::placeholders::_2);

	using memberFuncPointer = int(MyClass::*)(int, int);
	memberFuncPointer ptrx = &MyClass::add;
	
	CMemberFuctionDelegateMultiParameters<int, MyClass, int, int> cc(&mc, ptrx);
	cout << "23+96=" << cc.invoke(23, 96) << endl;

	/*MyClass* ptrMc = new MyClass();
	auto ptrCommonFuncDelegate = CreateDelegateWithMultiParamters<int, int, int>(add);
	auto ptrMemberFuncDelegate = CreateDelegateWithMultiParamters<int, MyClass, int, int>(ptrMc, &MyClass::add);
	CMultiDelegateMultiParameters<int,int,int> cdmp;
	cdmp += ptrCommonFuncDelegate;
	cdmp += ptrMemberFuncDelegate;
	cdmp(20,965);*/
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
