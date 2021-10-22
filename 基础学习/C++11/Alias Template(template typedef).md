#### Alias Template(template typedef)

```C++
template<typename T>
using Vec=std::vector<T,MyAlloc<T>>;！！！！但是这样不能够偏特化或特化
可以写成下面这种形式
Vec<int> coll;
等于
std::vector<int,MyAlloc<int>> coll;

使用宏定义无法达到相同效果
#define Vec<T> template<typename T> std::vector<T,MyAllloc<T>>;
于是
Vec<int>coll;======template<typename T> std::vector<T,MyAllloc<T>>这意思完全变了

使用typedef也无法得到相同效果，因为typedef不接受参数
typedef std::vector<int,MyAlloc<int>> Vec;这没法使用参数，不能替换
```

下面使用一个例子来说明

```c++
void test_moveable(Container cntr,T elem){
	Container<T> c;
	for(long i=0;i<Size;++i)
		c.insert(c.end(),T());
		Container<T> c1(c);
		Container<T> c2(std::move(c));
		c1.swap(c2);
}

下面调用这个函数
test_moveable(list,MyString);//这完全是错误的，调用函数参数必须是一个对象，不能是一个类型，list是一种类型，而不是一个对象
改成这样
template<typename Container>
void test_moveable(Container c){
	typedef typename iterator_traits<typename Container::iterator>::value_type Valtype;
    for(long i=0;i<size;++i){
		c.insert(c.end(),Valtype());
        Container c1(c);
        Container c2(std::move(c));
        c1.swap(c2);
   }
}

然后去调用他:
test_moveable(list<MyString>());//这表示一个临时对象，因为是不能穿类型的
通过模板加萃取的方法就可实现不同容器调用这个函数
```

但是可不可以有这样一种语法，可以模板嵌套模板

#### 于是就有了C++11里面的 template template parameter

```C++
template<typename T,template<class T> class Container>//这句话意思是传进来的第二个模板参数本身是一个模板，这个模板是以T为参数。
  class XCIs{
      private:
      Container<T> c;
      public:
      	XCIs(){
         for(long i=0;i<size;++i){
		c.insert(c.end(),Valtype());
        Container c1(c);
        Container c2(std::move(c));
        c1.swap(c2);
        }
  }
      
  调用的时候可以直接传
   XCIs<Mystring,vector> c1;//这样还是错误的，因为vector模板有两个参数，一个是类型，一个是分配器，但是vector往下面使用的时候只有一个（是没法使用默认的分配器的），所以还是不能用
      
      
template<typename T>
using Vec=vector<T,allocator<T>>;
```

#### Type Alias(类型化名)

 直接看几个例子

```C++
1.	函数指针的一个例子
    //typedef void(*func)(int,int)
    using func=void(*)(int,int);

2.template<typename T>
    struct Container{
        using value_type=T;//等于typedef T value_type      
    }
```

#### using 的使用方法

* using namespace std;或者using std::count;

* using -declarations for class member就是用这个来告诉程序我使用的哪个类里面（例如继承里面经常用的）

* type alias and type template declaration（C++11中的）

  ```
  1.using func=void(*)(int,int);
  2.template<typename T>
  	struct Container{
  		using value_type=T;
  	}
  3.
  template<class CharT>using mystring=std::basic_string<CharT,std::char_traits<CharT>>;
  ```

  
