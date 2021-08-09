### 44将与参数无关的代码抽离template

使用template可能会导致代码膨胀：其二进制码带着重复的代码、数据。结果就是源码看起来合身而整齐，但是目标码却不是那么回事。

在编写template时，也是做相同的分析，以函数相同的方式避免重复。在non-template代码中，重复很明确：你可以看到两个函数或两个class之间有重复。但是在template代码中，重复是隐晦的：毕竟只存在一份template源码，所以你必须训练自己去感受当template被具现化多次时可能发生的重复

案例:为固定尺寸的正方形矩阵编写一个template。可以支持逆矩阵运算

```
template<typename T,std::size_t n> //n*n矩阵
class SquareMatrix{
public:
	void invert();求逆矩阵
}

调用代码：
SquareMatrix<double,5> sm1;
sm1.invert();
SquareMatrix<double,10> sm2;
sm2.invert();
这里会实现两个invert，但是除了5和10不一样，其他的都一样，会引起代码膨胀。
下面建立一个带值参数的函数
template<typename T>
class SquareMatrixBase{
protected:
	void invert(std::size_t matrixSize);
};
template<typename T,std::size_t n>
class SquareMatrix:private SquareMatrixBase<T>{
private:
	using SquareMatrixBase<T::invert();//避免遮掩base的invert
public:
	void invert(){
		this->invert();//制造一个inline调用，调用base class版的invert（前面条款说过为什么加上this43）
	}
}

```

这里所有矩阵共享同一个invert

但是还有一个问题，SquareMatixBase::invert如何知道该操作什么数据？虽然他从参数中知道矩阵尺寸，但如何知道特定矩阵在哪？只有derived class知道，derived class如何联络其base class做逆运算动作？一个可能的做法就是SquareMatrixBase::invert添加另一个参数，就是个指针，存放着矩阵数据内存的起始点。

另一个办法就是SquareMatrixBase贮存一个指针，指向矩阵数值所在内存

```
template<typename T>
class SquareMatirxBase{
protected:
	SquareMatrixBase(std::size_t n,T* pMem):size(n),pData(pMem){}
	void setDataPtr(T* ptr){
		pData=ptr;
	}
private:
	std::size_t size;
	T* pData;//指针指向矩阵内容
}
允许derived class决定内存分配方式。
template<typename T,std::size_t n>
class SquareMatrix:private SquareMatrixBbase<T>{
public：
	SquareMatrix():SquareMatrixBase<T>(n,data){}
private:
	T data[n*n];
};
```

这种类型的对象不需要动态内存分配，但对象自身可能非常大。另一种做法是把每一个矩阵的数据放进heap(也就是通过new来分配内存)

```
template<typename T,std::size_t n>
class SquareMatrix:private SquareMatrixBase<T>{
public:
	SquareMatrix():SquareMatrixBase<T>(n,0),pData(new T[n*n]){
	this->setDataPtr(pData.get());
	}
	这个方法的思路就是将base class的数据指针设为null，为矩阵内容分配内存，将指向该内存的指针存储起来，然后将他副本交给base class
private:
	boost::scoped_array<T> pData;
}
```



这个条款真是太混乱了，有点看不太明白

暂时跳过

**总结**

* template生成多个class和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系。
* 因非类型模板参数non-type template parameters而造成的代码膨胀，往往可消除，做法是以函数参数或class成员变量template参数
* 因类型参数（type parameters）而造成的代码膨胀，往往可降低，做法是让带有完全相同二进制表述的具体类型共享实现码