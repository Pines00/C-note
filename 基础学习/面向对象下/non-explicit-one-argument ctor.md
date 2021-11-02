#### conversion function 转换函数

```
class Fraction{
	public:
		Fraction(int num,int den=1):m_numerator(num),m_denominator(den){}
		operator double() const{
		return (double)(m_numerator/m_denominator);
		}
	private:
		int m_numerator;
		int m_denominator;
};

```

通过operator type()来转换类型，可以做转为任意类型。

例如要转为string

operator string() const {

}

### non-explicit-one-argument ctor

```
#include<iostream>
#include<typeinfo>
class Fraction {
public:
	Fraction(int num, int den = 1) :m_numerator(num), m_denominator(den) {}
	operator double() const {
		return (double)(m_numerator / m_denominator);
	}
private:
	int m_numerator;
	int m_denominator;
};
class Fraction1 {
public:
	Fraction1(int num, int den = 1) :m_numerator(num), m_denominator(den) {

		}
	Fraction1 operator+(const Fraction1& f) {
		return Fraction1(this->m_denominator+f.m_denominator,this->m_denominator+f.m_denominator);
	}
private:
	int m_numerator;
	int m_denominator;
};
int main() {
	using namespace std;
	Fraction f(3, 4);
	double d = 4 + f;
	cout << typeid(4+f).name();
	cout << typeid(d).name();

	Fraction1 f1(3, 5);
	Fraction1 d2 = f1 + 4;//调用non-explicit ctor将4转为Fraction1(4/1)，然后调用operator+
	cout << typeid(f1 + 4).name();
	return 0;
}
```

这里两个Fraction是做完全相反的事情，第一个是将一个Fraction转换成其他类型，第二个是将其他类型隐式转换成Fraction。

但是如果operator+和隐式转换同时存在，就会导致歧义，因为有两种方式都可以达到目的，视频是这样讲的，但是自己测试的时候结果却不是

```
class Fraction {
public:
	Fraction(int num, int den = 1) :m_numerator(num), m_denominator(den) {}
	operator double() const {
		std::cout << "eee" << std::endl;
		return (double)(m_numerator / m_denominator);
	}
	Fraction operator+(const Fraction& f) {
		std::cout << "+++" << std::endl;
		return Fraction(this->m_denominator + f.m_denominator, this->m_denominator + f.m_denominator);
	}
private:
	int m_numerator;
	int m_denominator;
};
int main() {
	using namespace std;
	Fraction f(3, 4);
	Fraction d = 4 + f;
	cout << typeid(d).name()<<endl;
	cout << typeid(4+f).name() << endl;
	return 0;
}
```

![image-20211102193400310](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211102193400310.png)

结果是调用的double()这个函数。这就搞不懂了，可能编译器有区别

![image-20211102194639277](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211102194639277.png)

但是这样调用就错了

原因：

* 4+f将f转为double，然后用的是内置类型+而不是operator+来运算
* 当第二次调用的时候就出问题了，不知道该调用哪一个。

### explicit-one-argument ctor

```
class Fraction {
public:
	explicit Fraction(int num, int den = 1) :m_numerator(num), m_denominator(den) {}
	operator double() const {
		std::cout << "eee" << std::endl;
		return (double)(m_numerator / m_denominator);
	}
	Fraction operator+(const Fraction& f) {
		std::cout << "+++" << std::endl;
		return Fraction(this->m_denominator + f.m_denominator, this->m_denominator + f.m_denominator);
	}
private:
	int m_numerator;
	int m_denominator;
};
```

Fraction f(3,5);

Fraction d2=f+4;这就错了因为不能将4转为Fraction，必须使用显示转换。