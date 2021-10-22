#### Uniform Initialization 

 统一初始化过程

```C++
以前初始化：
Rect r1={1,2,3,4,&a,&b};
Rect r1(1,2,3,4);
int ia[6]={,12,3,4,5,};

现在就可以使用{}统一化
   int values[]{1,2,3,4};
	vector<int> v{1,2,3,4,5}
	complex<double> c{4.0,3.0};
```

实际上，编译器将{1,2,3}等做出一个initializer_list< T> ，关联到一个arrary<T,n>.调用函数时该array内的元素可被编译器分解逐一给函数。但若函数参数是initializer_list< T>,调用者不能给整个T参数，然后他们会被自动转我一个initializer_list< T>传入。

#### Initializer Lists

```C++
int i;i没有被定义
int j{};j被初始化为0
int *p;p没有被定义
int *q{};q被初始化为空指针

而且使用initializer_list是不能类型转化的
例如
int x3{5.0};error
int x3={5.3};error
char c2{999};error
```

#### initializer_list<>

```
void print(std::initializer_list<int> vals){
	for(auto p=vals.begin();p!=vals.end();++p){
		std::cout<<*p<<endl;
	}
}

print(1,2,3,4,5);//可以使用多个参数，但是只能是同一种类型



#include<iostream>
using namespace std;
class P{
public:
    P(int a,int b){
        cout<<"1"<<endl;
    }

    P(std::initializer_list<int> val){
        cout<<"initializer"<<endl;
    }
};
int main(){
    P p(1,2);
    P q{1,2};
    P r{1,2,3,4};
//这里测试了两个情况下选择那个构造函数
    return 0;
}
如果没有initializer，那么使用  P q{1,2};时候会把initializer拆解成一个个。
```

