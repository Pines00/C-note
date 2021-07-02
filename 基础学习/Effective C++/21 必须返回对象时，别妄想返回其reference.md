#### 21 必须返回对象时，别妄想返回其reference

考虑一个有理数的class，内含一个函数用来计算两个有理数的乘积

```C++
class Rational{
public:
	Rational(int numerator=0,int denominator=1);
private:
	int n,d;
friend const Rational operator*(const Rational& lhs,const Rational &rhs);
};
```

这里通过value返回计算结果，这样不仅仅是需要付出构造和析构的代价这样简单

如果用reference，就不需要付出代价，但是reference只是一个名称，代表某个真实存在的对象，上面operator* 为例，如果返回一个reference，后者一定指向存在的Rational对象，内含两个Rational对象的乘积。但是事实是不存在的，需要自己创建对象，看下面代码



函数创建新对象途径有二，在stack空间或在heap空间创建。如果定义一个local变量，就在stack空间创建对象。

```c++

const Rational& operator*(const Rational&lhs,const Rational& rhs){
	Rational result(lhs.n*rhs.n, lhs.d*rhs.s);
}
```

这里会引发严重的问题，不仅需要使用构造函数和析构函数，更严重的是：这个函数返回一个reference指向result，但result是一个local对象，local对象在函数退出之前被销毁了。所以这里的reference指向的是一个已经被销毁的对象。

**事实是任何函数如果返回一个reference指向某个local对象，都会出现严重错误**



于是尝试在heap中构造一个对象，并返回reference指向它。

```
const Rational& operator*(const Rational& lhs,const Rational& rhs){
	Rational *result=new Rational(lhs.n*rhs.n ,lhs.d*rhs.d);
	return *result;
}
```

这里问题更严重，除了需要付出构造函数调用的代价，出现新问题，new出来的空间谁来delete。即使良好的使用了delete释放了空间，但是如果出现下面问题

````
Rational w,x,y,z
w=x*y*z;
这里调用了两次operator* ，因而两次使用new，也就需要两次使用delete。但是却没有合理的办法让operator*使用者进行调用两次delete。百分百出现内存泄露。
````

使用static 对象更容易出问题，所以必须返回新对象的正确写法是：那就返回一个新对象

对于本例正确的写法是

```c++
inline const Rational operator*(const Rational& lhs,const Rational& rhs){
	return Rational(lhs.n*rhs.n,lhs.d*rhs.d);
}
```

当然必须得承受operator* 返回值的构造成本和析构成本。

总结：绝不要返回pointer或reference指向一个local stack对象，或赶回reference指向一个heap-allocated对象，或返回pointer或reference指向一个local static对象而有可能同时需要多个这样的对象。