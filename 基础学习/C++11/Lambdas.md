#### Lambdas

本身是一个函数对象，且是inline函数。

可以这样定义

````
[]{std::cout<<"werw";}
或者直接调用
[]{std::cout<<"rwer";}();
或者这样
auto i=[]{std::cout<<"hello lambda";}
i();
````

标准语法

```
[外部变量](参数)mutable throwSpaec ->retTypr{函数体}这是返回类型
int id=0;
auto f=[id]()mutable{
	std::cout<<"id:"<<id<<std::endl;
	++id;
};
id=42;
f();//输出是0
f();//输出是1
f();//输出是2
cout<<id;//输出是42
```



![image-20211020132939112](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211020132939112.png)

传引用的时候，lambda里面的id会受到外部的影响，且里面的变化会影响到外界。

不加mutable是不能对外部id改变的。

在lambda内部也可以定义变量，可以返回值。

#### lambda和decltype

当使用lambda作为一个仿函数或函数对象的时候，需要用decltype来获得lambda的类型。例如传一个仿函数作为hash函数或者排序准则

 ```
 auto cmp=[](const Person&p1,const Person&p2){
 	return p1.lastname()<p2.lastname()||(p1.lastname()==p2.lastname()&&p1.firstname()<p2.firstname()){};
 	std::set<Person,decltype(cmp)> coll(cmp);
 }
 ```

需要用lambda类型来声明set，使用decltype。，此外必须把lambda对象传递给构造函数。如果没有传lambda对象（cmp），否则会调用默认构造函数。但是lambda没有默认构造函数，所以一定会报错。所以使用lambda时候一定要直观一点。

