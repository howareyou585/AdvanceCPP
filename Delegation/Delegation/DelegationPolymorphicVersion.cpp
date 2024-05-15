#include "DelegationPolymorphicVersion.h"
#include<iostream>
using namespace std;

//EventCallA::EventCallA()
//{
//}
//
//
//EventCallA::~EventCallA()
//{
//}
void EventCallA::Do(int eventId)
{
	//cout << "doing EventCallA ... " << endl;
	printf("EventCallerA do event %d.\r\n", eventId);
}
void Receiver::AddEventCaller(EventCallBase * ptrCaller)
{
	if (ptrCaller)
	{
		m_lstCaller.emplace_back(ptrCaller);
	}
}

void Receiver::OnEvent(int eventId)
{
	for (auto it = m_lstCaller.begin(); it != m_lstCaller.end(); it++)
	{
		auto ptrCaller = *it;
		if (ptrCaller)
		{
			ptrCaller->Do(eventId);
		}
	}
}

void EventCallB::Do(int eventId)
{
	printf("EventCallerB do event %d.\r\n", eventId);
}

void EventCallSystem::Do(int eventId)
{
	if (m_ptrSystem)
	{
		m_ptrSystem->Maximize();
	}
}
