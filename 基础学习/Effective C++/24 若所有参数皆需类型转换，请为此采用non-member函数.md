#### 24 若所有参数皆需类型转换，请为此采用non-member函数

考虑这样一个例子

````c++
class Rational{
public:
	Rational(int numerator=0,int denominator=1);
	int numeratir()const;//这两个为分子和分母	
	nit denominator()const;
private:
	...
};
````

当想支持算术运算的时候，不确定是否该有member函数，non-member函数。只知道有理数相和Rational class相关，因此很自然的在Rational class内实现operator*。会写成下面这种形式

```
class Rational{
public:	
	const Rational operator*(const Rational& rhs)const;
};
这个设计是的能够将两个Rational类型相乘
Rational oneEighth(1,8);
Rational oneHalf(1,2);
Rational result=oneHalf*oneEighth;
result = result*oneEighth;
但是我希望可以支持混合式运算，也就是拿Rational和别的类型相乘（int）,会发现只有一半行得通
result=oneHalf*2;行得通
result= 2*oneHalf;错误

这是为什么？
这等同于
result=oneHalf.operator*(2);
result=2.operator*(oneHalf);错误
原因：
	oneHalf是一个Rational类型的对象，所以编译器调用该函数没问题。然而整数2并不是相应的class，也就没有operator*成员函数。编译器赢回尝试寻找可被调用的non-member operator*函数。

```

`result=oneHalf.operator*(2);`之所以能够调用成功，是因为发生了隐式类型转换。编译器知道正在传递一个int，而函数需要的是Rational；但它知道只要调用Rational构造函数，并赋予所提供的的int，就可以变出一个适当的Rational来。

有点类似于下面这种情况：

````
const Rational temp(2);相当于建立一个暂时的Rational对象。
result=oneHalf*temp;
这只涉及non-explicit构造函数，如果Rational构造函数时explicit，那么两种情况都不能通过编译。

然而真正的原因是为什么
result=oneHalf*2;行得通
result= 2*oneHalf;错误

只有当参数被列于参数列内，这个参数才是隐式类型转换的合格参与者。地位相当于“被调用之成员函数所隶属的那个对象（this对象，对象本身）”，这种情况绝不是隐式转换的合格参与者。这就是当第二种的this对象是2，但2并不是一个Rational对象。
````

**解决这个问题的办法就是让operator* 成为一个non-member函数，便允许编译器在每一个实参上执行隐式类型转换。**

```
class Rational{
	...
};
const Rational operator*(const Rational& lhs,const Rational& rhs){
	return Rational(lhs.numerator()*rhs.numerator(),lhs.denominator()*rhs.denominator());
}
Rational oneFourth(1,4);
Rational result;
result=oneFourth*2;
result=2*oneFoutth;
这样就可以了
```

总结：

* 如果需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member