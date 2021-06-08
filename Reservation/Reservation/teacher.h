#pragma once
#include"identity.h"
class Teacher:public Identity {
public :
	Teacher();
	Teacher(int empid,string name,string pwd);
	virtual void openMenu();
	void showAllOrder();
	void validOrder();
	int m_EmpId;
};