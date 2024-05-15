#pragma once
//多态版本实现委托机制
#include<list>
using namespace std;
class EventCallBase
{
public:
	virtual void Do(int eventId) = 0;
	//virtual ~EventCallBase() = 0;
};
class EventCallA :public EventCallBase
{
public:
	virtual void Do(int eventId) override;
};

class EventCallB :public EventCallBase
{
public:
	virtual void Do(int eventId) override;
};
class Receiver
{
public:
	void AddEventCaller(EventCallBase* ptrCaller);
	void OnEvent(int eventId);
private:
	list<EventCallBase *>  m_lstCaller;
};

//system 是一个第三方提供的类
class System
{
public:
	void Maximize(void) { printf("Window is maximized.\r\n"); }
};
class EventCallSystem :public EventCallBase
{
public:
	virtual void Do(int eventId) override;
public:
	System* m_ptrSystem;
};
