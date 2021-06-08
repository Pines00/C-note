#pragma once
#include<iostream>
using namespace std;
class Identity {
public :
	virtual void openMenu() = 0;//纯虚函数，不用写函数体，继承类实现函数。
	string m_name;
	string m_Pwd;
};