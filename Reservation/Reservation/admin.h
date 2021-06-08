#pragma once
#include"identity.h"
#include<fstream>
#include<vector>
#include"student.h"
#include"teacher.h"
class Manager :public Identity {
public :
	Manager();
	Manager(string name,string pwd);
	virtual void openMenu();
	void add();
	void showPerson();
	void showComputer();
	void cleanFile();
	void initVector();
	vector<Student> vstu;
	vector<Teacher> vtea;
	bool checkRepeat(int id, int type);
};