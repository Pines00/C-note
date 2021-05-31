### C++代码重用

####  私有继承

实现has-a 关系。

使用私有继承，基类的公有成员和保护成员都将成为派生类的私有成员。基类方法不为成为派生对象公有接口的一部分，但是可以再派生类的成员函数中使用他们。（意思派生类可以使用，但是不可以接着往下继承，在派生类中是私有状态）

公有继承就是基类的公有方法称为派生类公有方法，这是is-a关系。

私有继承，基类的公有方法称为派生类的私有方法。这种不完全继承是has-a 关系。

继承关系的时候，默认是私有继承private

总结：父类公有成员和保护成员都作为子类的私有成员，并且不能被这个子类的对象所访问。如果子类再派生出一个孙子类的话，在孙子类是否能访问父类的成员呢？因为父类的成员在子类中只有公有成员和保护成员可以访问，并且属性降级为private，所以孙子类即使是公有继承子类的，也不能访问private成员。所以在私有继承时，父类的成员只能由直接派生子类访问，而无法再往下继承。


#### 多重继承

多重继承必须是用public来声明，格式如下

```c++
class SingingWaiter :public Waiter,Singer{}；
```

如果不使用public 则系统默认private

多继承带来的问题：（虽然我现在没怎么懂，这里留疑）

* 从两个不同基类继承同名方法
* 从两个或者更多相关基类继承同一个类的多个实例

为了解决这个问题，提供了虚基类：虚基类使得从多个类派生出的对象只继承一个基类对象。例如

```
class Singer:virtual public Worker{}
class Waiter:public virtual Worker{}
然后可以将Singing Waiter类定义为:
class SingingWaiter:public Singer,public Waiter{};
```

现在SingingWaiter只包含一个对象副本。

##### 虚基类的新构造函数规则

```c++
class A{
	int a;
public :
	A(int n=0):a(n){};
}
class B:public A{
	int b;
	public :
		B(int m=0,int n=0):A(n),b(m){}//对于非虚基类，B的构造函数只能调用A的构造函数。
}
然而基类函数这种方式不可以。只能显示的调用构造函数worker
例如
SingingWaiter(const Worker &wk,int p=0,int v=Sing::other)
	:Worker(wk),Waiter(wk,p),Singer(wk,v){}
```

##### 多继承使用哪个方法

```c++
例如：SingingWaiter 继承 waiter,singer类，他们都有一个方法show()
SingingWaiter n("mzx",2005,6,so);
n.show();//这个show方法到底是继承哪一个,这就会出现二义性
解决这样的问题就是在调用的时候加上作用域。
n.Singer::show()
也可以在SingingWaiter中重新定义show方法
比如
 void SingingWaiter::show(){
 	Singer::show();
 }
```

#### 类模板（java泛型，但是java已经忘光了，等有时间去做一个小项目熟悉熟悉）

举个例子，比如一个stack普通stack只能用来存储一种类型，模板现在要用一个stack来存储不同的类型，可以实现一个通用的stack。将类型名作为参数传递给模板。

模板类使用 ` template<class Type>`来声明一个模板。

当类模板被调用时候，Type被具体的类型值取代（int ，string等）

使用类模板时候需要声明一个类型来替换Type。例如 ` Stack<int >n;Stack<string>c;`  然后在类方法中，用int来替换类中的所有Type。

说白了，类模板就是在定义类的时候并不知道成员函数或成员变量是什么类型，那好办，就定义类模板，将类中不确定的类型全定义为Type，然后在使用类的时候给类传一个类型就行了。

类似于typedef。但是又有不同。类模板可是使用很多种类型，但是typedef只是变量的另一个名字。

```c++
#include <string>
//类模板
template<class NameType, class AgeType> 
class Person{ 
   public:
	Person(NameType name, AgeType age) {
	this->mName = name; this->mAge = age;
}
	void showPerson() {
		cout << "name: " << this->mName << " age: " << this->mAge << endl;
    }
public:
	NameType mName; AgeType mAge;
};
void test01() {
	// 指定NameType 为string类型，AgeType 为    int类型 Person<string, int>P1("孙悟		空", 999);
	P1.showPerson(); 
}
int main() {
	test01(); 
    system("pause"); 
    return 0;
}
```

使用模板类的时候可以用指针，但是很容易出问题。

* 不正确的使用指针栈：例如将栈Stack<char *>st 来替换string，这意思用char指针而不是string对象来接受输入，因为没有创建用于保存输入字符串的空间。

* 使用char po[40]来替换string po; 虽然分配了空间，但是用于栈中，与栈的原有方法冲突。所以使用失败。

* 使用char *po =new char[40]替代string po; 只有一个po变量，该变量总是指向相同的内存单元。（这里是为什末呢？我也是没搞懂）每次读取新的字符串时候，内存都发生改变，但每次执行压入操作，加入栈中的地址都相同。

下面介绍如何正确的使用栈：

​	让调用程序提供一个指针数组，其中每个指针都指向不同的字符串。然后将这些指向字符串的指针压入栈中。但是实际上就相当于把字符串本身压入栈中。

一些注意事项：不要递归使用模板。使用多个类型的参数。

##### 模板的具体化

1.隐式实例化

​	ArrayTP<int,100> stuff;

​	ArrayTP<int,100> * pt; pt=new ArrayTp<double ,30>;第二条语句导致编译器生成类定义，然后创建对象；

2.显示实例化

​	template class ArrayTP<string,100>;  需要加上template与 class这种情况虽然没有创建或体积类对象，编译器也将生成类声明。

3.显示具体化

​	主要适用于在未特殊类型实例化时对模板进行修改。

定义格式 template <> class Classname< specialized-type-name>{.....}

4.部分具体化

template < class T1,class T2> class Pair{}

template < class T1>class Pair<T1,int>{}这里将T2具体化了，

##### 成员模板

```c++
模板中嵌套模板，使用方法如下；
#include<iostream>
using std::cout;
using std::endl;
template <typename T>
class beta {
private:
	template <typename V>
	class hold {
	private :
		V val;
	public:
		hold(V v = 0) :val(v) {}
		void show()const { cout << val << endl; }
		V Value() const { return val; }
	};
	hold<T>q;//套用了一个模板
	hold<int>n;//这里也是
public:
	beta(T t, int i) :q(t), n(i) {}
	template <typename U>//函数模板
	U blab(U u, T t) {return (n.Value()+q.Value())*u/t}
	void Show()const { q.show(); n.show(); }

};
int main() {
	beta<double >guy(3.5, 3);
	cout << "T:";
	guy.Show();
	cout << "V isset to T,which is double ,then V was set to int \n ";
	cout << guy.blab(10, 2.3) << endl;
	cout << "U" << endl;
	cout << guy.blab(10.0, 2.3);
	return 0;

}
```

