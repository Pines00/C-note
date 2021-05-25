## 类的使用
### 运算符重载：格式operator op (argument-list)
```
写一个示例，重载时间加法运算
 
 头文件add.h 
#pragma once
#ifndef Add_H
#define ADD_H
class Time {
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int h, int m = 0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h=0,int m=0);
	Time operator+(const Time& t)const;          ！！！！注意这里用operator+  下面使用的时候可以直接用加号替代
	void show() const;
};
#endif // !Add_H

实现类方法
#include<iostream>
#include"add.h"
Time::Time() {
	hours = minutes = 0;
}
Time::Time(int h, int m) {
	hours = h;
	minutes = m;
}
void Time::AddMin(int m) {
	minutes += m;
	hours += minutes / 60;
	minutes = minutes % 60;
}
void Time::AddHr(int h) {
	hours += h;
}
void Time::Reset(int h, int m) {
	hours = h;
	minutes = m;
}
Time Time::operator+(const Time& t)const {
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}
void Time::show()const {
	std::cout << hours << "hours" << minutes << "minutes";
}
测试用例
#include<iostream>
#include"add.h"
int main(){
	using std::cout;
	using std::endl;
	Time planning;
	Time coding(2, 40);
	Time fixing(5, 55);
	Time total;
	planning.show();
	cout << endl;
	coding.show();
	cout << endl;

	fixing.show();
	//total = coding.operator+(fixing);
	total = coding + fixing;
	total.show();
	return 0;
}
重载运算符注意点：不能颠覆其应有的含义，例如将减号重载为加；不能自创运算符；可以重载的运算符在书388页表11.1中

```
### 友元函数：
与类成员函数有相同的访问权限，但不是类成员函数
* 首先需要在类中声明 	friend Time operator*(type &x,type &y)
* 在类中声明但是不是成员函数，不能用类来调用。
定义函数过程不需要加类修饰符 Time opreator*(...){}