#pragma once
#include"identity.h"
#include"computerRoom.h"
#include<vector>
class Student :public Identity {
public :
	Student();
	Student(int id,string name,string pwd);

	virtual void openMenu();
	void applyOrder();
	void showMyOrder();
	void showAllOrder();
	void cancelOreder();
	int m_Id;
	vector<ComputerRoom> vCom;
};