
#include "DelegationBaseVersion.h"
#include<iostream>
using namespace std;
BaseA::BaseA()
{
	cout << "constructing BaseA object... " << endl;
}


BaseA::~BaseA()
{
	cout << "deconstructing BaseA object... " << endl;
}

void BaseA::Do(int eventId)
{
	cout << "doing BaseA ... " << endl;
}

BaseB::BaseB():m_ptra(nullptr)
{
	cout << "constructing BaseB object... " << endl;
}

BaseB::~BaseB()
{
	cout << "deconstructing BaseB object... " << endl;
}

void BaseB::OnEvent(int eventId)
{
	m_ptra->Do(eventId);
}
