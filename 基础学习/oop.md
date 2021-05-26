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

### 运算符重载的另一个示例

#### 头文件

```
#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>
namespace VECTOR {
	class Vector {
	public:
		enum Mode
		{
			RECT,POL
		};
	private:
		double x;
		double y;
		double mag;	//向量长度
		double ang;//向量方向
		Mode mode;
		void set_mag();
		void set_ang();
		void set_x();
		void set_y();
	public:
		Vector();
		Vector(double n1,double n2,Mode form=RECT);
		void reset(double n1, double n2, Mode form = RECT);
		~Vector();
		double xval()const { return x; }
		double yval()const { return y; }
		double magval()const { return mag; }
		double angval()const { return ang; }
		void polar_mode();
		void rect_mode();

		Vector operator+(const	Vector& b)const;
		Vector operator-(const	Vector& b)const;
		Vector operator-()const;
		Vector operator*(double n)const;


		friend Vector operator*(double n, const Vector& a);
		friend std::ostream& operator<<(std::ostream& os, const Vector& v);
	};
}
#endif // !1
实现类
#include<cmath>
#include"vector.h"
using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;
namespace VECTOR {
	const double Rad_to_deg = 45.0 / atan(1.0);
	//初始化各个函数
	void Vector::set_mag() {
		mag = sqrt(x * x + y * y);
	}
	void Vector::set_ang() {
		if (x==0.0&&y==0.0)
		{
			ang = 0.0;
		}
		else ang = atan2(y, x);
	}
	void Vector::set_x() {
		x = mag * cos(ang);
	}
	void Vector::set_y() {
		y = mag * sin(ang);
	}
	//开始写构造函数
	Vector::Vector() {
		x = y = mag = ang = 0.0;
		mode = RECT;
	}
	Vector::Vector(double n1,double n2,Mode form) {
		mode = form;
		if (form == RECT)
		{
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if(form == POL){
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else {
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}
	void Vector::reset(double n1, double n2, Mode form) {
		mode = form;
		if (form == RECT)
		{
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else {
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}
	Vector::~Vector() {}
	void Vector::polar_mode() {
		mode = POL;
	}
	void Vector::rect_mode() {
		mode = RECT;
	}
	//重构运算符
	Vector Vector::operator+(const	 Vector& b)const {
		return Vector(x + b.x, y + b.y);
	}
	Vector Vector::operator-(const	 Vector& b)const {
		return Vector(x - b.x, y - b.y);
	}
	Vector Vector::operator-()const {
		return Vector(-x,-y);
	}
	Vector Vector::operator*(double n)const {
		return Vector(n*x,n*y);
	}
	//友元函数
	Vector operator*(double n, const Vector& a) {
		return a * n;
	}
	std::ostream& operator <<(std::ostream& os, const Vector& v) {
		if (v.mode == Vector::RECT)
		{
			os << "(x,y)=(" << v.x << "," << v.y << ")";
		}
		else if(v.mode==Vector::RECT){
			os << "(m,a)=(" << v.mag << "," << v.ang * Rad_to_deg << ")";
		}
		else
		{
			os << " invalid";
		}
		return os;
	}
}


测试类  #include<iostream>
#include<cstdlib>
#include<ctime>
#include"vector.h"
int main() {
	using namespace std;
	using VECTOR::Vector;
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	cout << "shuru mu biao juli";
	while (cin>>target)
	{
		cout << "shuru buchang ";
		if (!(cin >> dstep)) { break; }
		while (result.magval()<target)
		{
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::POL);
			result = result + step;
			steps ++ ;
		}
		cout << steps << "..." << result << endl;
		result.polar_mode();
		cout << result << endl;
		cout << result.magval() / steps << endl;
		steps = 0;
		result.reset(0.0, 0.0);

	}
	cin.clear();
	return 0;
}

```

