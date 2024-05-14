#pragma once
class BaseA
{
	 
public:
	BaseA();
	~BaseA();
	void Do(int eventId);
};
class BaseB
{

public:
	BaseB();
	~BaseB();
	void OnEvent(int eventId);

	BaseA* m_ptra;
};
