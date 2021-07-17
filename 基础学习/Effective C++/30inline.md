### inline

使用inline可以使函数不需要承受函数调用带来的额外开销。

除此之外，编译器最优化机制来浓缩inline代码，所以编译器会对他执行语境相关的最优化。

但是inline函数的整体观念是，将对此函数的每一个调用都已函数本体替换。这样做可能增加目标码大小。过度使用inline或造成程序体积太大。会造成频繁的换页行为（虚拟内存分页的操作体统）降低cache的命中率。

* inline是一个对编译器的申请，而不是强制命令。这项申请可以隐喻提出，也可以明确提出。隐喻方式是将函数定义域class定义式内

```
class Person{
public :
	int age() const{return theAge;}//一个隐喻的inline申请：
private:
	int theAge;
}
```

这样的函数通常是成员函数，但是友元函数也可以被定义与class内，如果是那样，他们使被隐喻声明为inline。

* 也可以明确的申请为inline

```
template<tyname T>
inline const T& std::max(const T&a ,const T&b){return a<b?b:a}
```

#### template 与inline 

inline函数通常被置于头文件内，因为大多数编译过程中进行inlining。inline函数和template两者通常被定义域头文件内。

template通常被置于头文件内，因为他一旦被使用，编译器为了将它具体化，需要知道它长什么样子。

template的具体化与inlining无关。如果根据此template具体实现出来的函数都应该inlined，那么就将此template声明为inline；这就是上面那个案例的行为。但是如果写的template没有理由要求所具现的每一个函数都是inlined，就应该避免将这个template声明为inline。

   大部分的编译器拒绝太过复杂的函数inlining，而所有对virtual函数的调用都会是inlining落空，因为virtual意味着直到运行期才确定调用哪个函数； 