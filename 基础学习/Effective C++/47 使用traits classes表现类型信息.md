### 47 使用traits classes表现类型信息

STL五中迭代器：

* input iterator：只能向前移动，一次一步，客户只可读取而且只能读一次，C++照片那个istream_iterators就是这种
* output iterator:一切只为输出，只能向前移动，一次一步，只可涂写他们所指的东西，而且只能涂写一次例如ostream_iterators
* forward iterator：这种可以做前两个能做的所有事，而且可以多次。
* bidierctional iterator：除了可以向前移动，还可以向后移动，stl的list迭代器就属于这一分类，set，multiset map和mutimap的迭代器都是这一分类。
* random access iterator：可以在常量时间内向前或向后跳跃任意距离。因为迭代器以指针为榜样使用。

这五种迭代器，c++标准库分别提供专属的卷标（tag struct）加以确认：

```
strut input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag{};
```

他们之间是有有效的继承关系，所有的forward 都是input。

当我们使用这样一个advance函数。知道STL迭代器有不同的能力，实现advance的策略之一是采用最低但最普及的迭代器能力，以循环反复递增或递减迭代器。

```
以这样的方式实现advance：
template<typename IterT,typename DistT>
void advance(IterT& iter,DistT d){
	if(iter is a random access iterator){
		iter+=d;
	}else{
		if(d>=0){while(d--)++iter;}
		else{while(d++)--iter;}
	}
}
```

这种做法是判断iter是否为random access iterator，也就是说需要知道类型IterT是否为random access迭代器。就是需要知道他们的类型。就是traits的事情，允许在编译器去的某些类型信息。

Traits可以支持内置类型，但需要把traits信息放于类型自身之外。标准技术是把他们放进一个template及其一个或多个特化版本中。这样的template在标准程序库中有若干个，其中针对迭代器被命名为iterator_traits:

```
template<typename IterT>
struct iterator_traits;
```

虽然是个struct，但是被称为traits classes。iterator_traits的运作方式是，针对每一个类型IterT，在struct iterator_traits<IterT>内一定声明某个typedef名为iterator_category.这个typedef用来确认IterT的迭代器分类。

iterator_traits以两个部分实现。首先要求用户自定义类型必须嵌套一个typedef，名为iterator_category,用来确认适当的卷标结构（tag struct）。例如deque的迭代器可随机访问，所以针对deque迭代器而设计的class

```
template<>
class deque{
public:
	class iterator{
	public:
		typedef random_access_iterator_tag iterator_category;
	};
};
list迭代器 可双向，所以应该是这样：
tempalte<>
class list{
public:
	class iterator{
	public:
		typedef bidirectional_iterator_tag iterator_category;
	};
};
```

对于iterator_traits

```
template<typename IterT>
struct iterator_traits{
	typedef typename IterT::iterator_category iterator_category;
}
```

这对用户自定义行得通，但对指针行不通，因为指针不能嵌套typedef。iterator_traits的第二部分用来对付指针。

为了支持指针迭代器，需要提供一个偏特化的版本。由于指针的行径与random access迭代器类似，所以iterator_traits为指针指定的迭代器类型是

```
template<typename IterT>
struct iterator_traits<IterT*>{
	typename random_access_iterator_tag itertor_category;
}
```

所以实现一个traits class：

* 确认若干希望可取得类型相关信息。例如对迭代器而言，我们希望来取得其分类。
* 为该信息选择一个名称（例如iterator_category)
* 提供一个template和一组特化版本，内含希望支持的类型相关信息。

现在有了iterator_traits，可以对advance实现先前的伪码。

```
template<typename IterT,typename DistT>
void advance(IterT& iter,DistT d){
	if(typeid(typename std::itertor_traits<IterT>::iterator_category==
	typeid(std::random_access_iterator_tag))
	...
}
```

这样看起来还不多，但是IterT类型在编译期间货值，所以iterator_traits<IterT>::itertor_category也可在编译期确定。但if语句是在运行期才会界定。可以在编译期完成的事情，拖到运行期做浪费时间，造成可执行文件膨胀。

解决这个问题的办法就是实现重载版本。不用使用判断，是哪种类型就对应哪一个版本 

```
template<typename IterT,typrname DistT>
void doAdvance(IterT& iter,DistT d,std::random_access_iterator_tag){
	iter+=d;
}
template<typename IterT,typename DistT>
void doAdvance(IterT& iter,DistT d,stdLLbidirectional_iterator_tag){
	if(d>=0){while(d--)++iter;}
	else{
		while(d++)--iter;
	}
}

template<typename IterT,typename DistT>
void doAdvance(IterT & iter DistT d,std::input_iterator_tag){
	if(d<0){
		throw std::out_of_range("Negative distance");//
	}
	while(d--)++iter;
}
```

由于forward_iterator_tag继承自input_iterator_tag,所以上述的doAdvance的input_iterator_tag版本也能够处理forward迭代器。

advance函数会犯，如果面对random access和bidirectional迭代器，则接受正距离和负距离；但如果面对的是forward和input迭代器，移动负距离会导致不明确行为。所以要判断一下。

使用的时候这样就可以

```
template<typename IterT,typename DistT>
void advance(IterT & iter,DistT d){
	doAdvance(iter,d,typename std::iterator_tarits<IterT>::iterator_category());
}
```

**总结**：使用一个traits class

* 建立一组重载函数或函数模板，彼此间的差异只在于各自的traits参数。令每个函数实现码与其接受之traits信息相应和。
* 建立一个控制函数或函数模板，他调用上述那些并传递traits class所提供的信息。





结束：

* traits class使得类型想换信息，在编译期可使用。他们以template和template特化实现完成
* 整合重载技术，traits class有可能在编译期对类型if...else测试。