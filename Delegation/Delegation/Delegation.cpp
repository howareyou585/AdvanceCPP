// Delegation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include "DelegationBaseVersion.h"
#include "DelegationPolymorphicVersion.h"
#include "DelegationNoParameter.h"
#include <memory>


void say()
{
	cout << "你好" << endl;
}
int main()
{
    std::cout << "Hello World!\n"; 
	//基本版
	/*BaseB baseB;
	BaseA baseA;
	baseB.m_ptra =&baseA;
	baseB.OnEvent(12);*/

	//多态版
	/*auto ptrEventA = make_shared<EventCallA>();
	auto ptrEventB = make_shared <EventCallB>();
	auto ptrEventSystem = make_shared<EventCallSystem>();
	ptrEventSystem->m_ptrSystem = new System();
	Receiver r;
	r.AddEventCaller(ptrEventA.get());
	r.AddEventCaller(ptrEventB.get());
	r.AddEventCaller(ptrEventSystem.get());
	
	r.OnEvent(12);*/
	CMultiDelegate onclick;
	auto ptrDelegate = createDelegate(say);
	onclick += ptrDelegate;
	MyA *ptrA = new MyA();

	auto ptrDelegate2 = createDelegate(ptrA, &MyA::say);
	onclick += ptrDelegate2;
	//md.operator+=(ptrDelegate);
	//md.operator+=(ptrDelegate2);
	onclick();
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
