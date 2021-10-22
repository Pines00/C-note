#### 这是最重要的部分 Variadic Templates

还是和之前的多个模板参数一样

* variable number ：利用参数个数逐一递减的特性，实现递归函数调用，使用function template完成
* 参数类型：利用参数个数逐一递减导致参数类型也逐一递减的特性实现递归继承或递归复合，以class template完成

```
void func(){}
template<typename T,typename... Types>
void func(const T& firstArg,const Types&... args){
	func(args...);
}
```

例如这两个

```
void print(const T &first,const Types&... other){
    cout<<first<<endl;
    print(other...);
}

void print(const Types&... other){
    
}

这两个可以同时出现，但是编译器会调用比较特化的那个，这里的第一个。
```

```
#include<iostream>
#include<bitset>
using namespace std;
struct _Iter_less_iter{
    template<typename iterator1,typename iterator2>
    bool operator()(iterator1 it1,iterator2 it2)const{
        return *it1<*it2;
    }
};
_Iter_less_iter _iter_less_iter(){
    return _Iter_less_iter();
}
void print(){

}
template<typename T,typename ...Types>
void print(const T &first,const Types&... other){
    cout<<first<<endl;
    print(other...);
}
template<typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first,ForwardIterator last){
    return _max_element(first,last,_iter_less_iter());
}


template<typename ForwardIterator,typename _Compare>
ForwardIterator _max_element(ForwardIterator first,ForwardIterator last,_Compare _comp){
    if(first==last)return first;
    ForwardIterator result=first;
    while(++first!=last){
        if(_comp(result,first)){
            result=first;
        }
    }
    return result;
}
template<typename T>
T max(initializer_list<T> l){
    return *max_element(l.begin(),l.end());
}
int main(){
   // print(7.5,"rwer",bitset<16>(377),42);
    cout<<max({45,234,25,645,67,4645,6,456456})<<endl;
    return 0;
}

输出“456456
```

