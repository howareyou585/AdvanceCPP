#pragma once
//��̬�汾ʵ��ί�л���
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

