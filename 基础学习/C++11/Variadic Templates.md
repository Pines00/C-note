#### Variadic Templates

```C++
template<typename T,typename... Types>//注意这个语法
void print(const T&firstArg,const Type&...Args){
cout<<firstArg<<endl;
print(args...);
}
```

意思是可以接收任意个参数，且类型也为任意类型

可以通过这种方式来做递归，每次都会比上一次少一个参数。

```c++
#include<iostream>
using namespace std;
void printInt(){
    
}//一定需要写一个处理边界的东西，这里指的是函数
template<typename T,typename... Type>
void printInt(const T& a,const Type&... args){
    cout<<a<<endl;
    printInt(args...);
}
int main(){
    printInt(1,2,3,4,5,6,7);
    return 0;
}

sizeof...(args)可以知道args有多少个
    ...就是一个pack，就是一个包
```

类似的

```
template<typename... Types>
void printInt(const Types&... args){
	....
}
这个和上面那个同时存在，
```

注意使用...来做递归时候，一定要写一个终止函数，不然会报错





#### 写个variadic template的例子

```
#include<iostream>
using namespace std;

template<typename... values>class tuple;
template<>class tuple<>{};

template<typename Head,typename... Tail>
class tuple<Head,Tail...>:private tuple<Tail...>
{
	typedef tuple<Tail...>inherited;
	public:
		tuple(){}
		tuple(Head v,Tail... vtail):m_head(v),inherited(vtail...){}
    auto->decltype(m_head) head(){return m_head;}
    inherited& tail(){return *this;}
    protected:
        Head m_head;
};
int main(){
    tuple<int,float,string> t(41,6.3,"nico");
    cout<<t.head();
    t.tail();
    t.tail().head();
    &(t.tail());
}

```

