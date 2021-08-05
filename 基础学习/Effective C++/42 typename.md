### 42 typename 

typename有两个用途

1. 在template声明式中，class和typename一样

   ```
   template<class T>
   class Widget;
   
   template<typename T>
   class Widget;
   ```

2. 先了解一个概念，从属名称与嵌套从属名称

   ```
   template<typename C>
   void print(const C& container){
   	if(container.size()>=2){
   		C::const_iterator iter(container.begin());
   		++iter;
   		int value=*iter;
   		std::cout<<value;
   	}
   }
   ```

   这里面有两个local变量iter和value。iter类型是C::const_iterator,实际是什么取决于template参数C。template内出现的名称如果相依于某个template参数，称为从属名称。如果从属名称在class内呈倩桃妆，称之为嵌套从属名称。

   嵌套从属名称可能导致解析困难

   ```
   比如这样
   template<typename C>
   void print(cnost C& container){
   	C::const_iterator*x;
   	...
   }
   ```

   这样声明一个变量x，他是一个指针，指向一个C::const_iterator。之所以这样，是我们已经知道他是一个类型，但是如果C::const_iterator不是个类型（比如全局变量名称就叫这个），可能就会解析为一种类型乘上x。

   如果解析器template中早于一个嵌套从属名称，他便假设这名称不是个类型，除非你告诉他是。

   ```
   template<typename C>
   void print(const C& container){
   	if(container.size()>=2){
   		C::const_iterator iter(container.begin());
   	}
   }
   iter声明式只有在C::const_iterator是个类型的时候才合理，但是没有告诉编译器他是，编译器就假设他不是。所以要告诉编译器他是个类型。只需要放置关键字typename即可
   template<typename C>
   void print(const C& container){
   	if(container.size()>=2){
   		typename C::const_iterator iter(container.begin());
   	}
   }
   ```

   **任何时候当想在template中指涉一个嵌套从属类型名称，就必须在紧邻他的前一个位置上放置typename（还会有一个例外）**

   这一规则例外就是typename不可以出现在base classes list内的嵌套从属类型名称之前，也不可能在成员初值列中作为base class修饰符。

   例如

   ```
   template<typename T>
   class Derived:public Base<T>::Nested{//base class list中不允许
   public:
   	explicit Derived(int x):Base<T>::Nested(x){//成员初值列不允许
   		typename Base<T>::Nested temp;
   	}
   }
   ```

   ​	

   还一个例子关于typename。

   ```
   template<typename IterT>
   void work(IterT iter){
   	typename std::iterator_traits<IterT>::value_type temp(*iter)
   }
   ```

   std::iterator_traits<IterT>::value_type是说“类型为IterT之对象所指之物的类型”。由于std::iterator_traits<IterT>::value_type是一个嵌套从属类型（value_type 被嵌套于iterator_traits<IterT>之内而IterT是个template参数），所以必须在之前放置typename。

   ​	

   但是名称太长可以用typedef来替换名称 

   ```
   typedef typename std::iterator_traits<IterT>::value_type value_type
   ```



**总结**

* 声明template参数时，前缀关键字class和typename可互换。
* 使用关键字typename标识嵌套从属类型名称；但不得在base class lists或成员初值列内以它作为base class修饰符。