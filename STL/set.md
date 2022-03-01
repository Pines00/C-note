### set

set特性是所有元素都会根据元素的键值自动被排序。set不是那种key，value类型，set元素的键值就是实值。set不允许有两个元素相同的键值。

set迭代器不可以改变元素的值，因为set元素值就是其键值，改变set的元素值，会破坏set组织。所以set的迭代器是const_iterator，杜绝写入操作。

对set进行元素新增或删除时，操作之前的所有迭代器，在操作完之后都依然有效。

**set 以红黑树作为底层机制** ，set所开放的接口操作，红黑树也提供了。所以几乎所有的set操作，都只是在调用红黑树的操作行为。

```c++
//摘录一点set源码
template<class Key,class Compare=less<Key>,class Alloc=alloc>//缺省情况下采用递增排序
class set{
    typedef rb_tree<key_type,value_type,identity<value_type>,key_compare,Alloc> rep_type;
    rep_type t;//这里体现出了采用红黑树来表现set
    
    typedef typename rep_type::const_iterator iterator;//这里把iterator定义为const_iterator表示set迭代器无法执行写入操作，因为set有一定的次序安排，不允许在任意处进行写入操作。
    
    public:
    	//set的构造函数
    	set():t(Compare()){}
    	explicit set(const Compare& comp):t(comp){}
    	template<class InputIterator>
        set(InputIterator first,InputIterator last):t(Compare)){t.insert_unique(first,last);}//这里set的插入一定要用红黑树的insert_unique函数，不能用insert_equal,因为set不允许相同键值存在。
    set(const set<Key,Compare,Alloc>&x):t(x.t){}//拷贝构造
    //赋值操作符
    set<Key,Compare,Alloc>& operator=(const set<Key,Compare,Alloc>&x){
        t=x.t;
        return *this;
    }
    
    iterator find(const key_type& x)const{return t.find(x);}
    size_type count(const key_type&x)const{return t,count(x);}
}
```

在set中，因为是key类型，所以查找的时候直接用find查找，o(1)时间复杂度，比STL中使用迭代器来得快。

举个例子：

```
1. 使用STL算法find来搜寻元素，可以有效运作，但不是好办法
iter=find(iset.begin(),iset.end(),3);

2.应该直接充分发挥关联式容器的优势，使用本身提供的find函数来查找，
iter=iset.find(3);
```

### multiset

multiset 的特性以及用法和set相同，唯一差别在于他允许键值重复，因此他的插入操作采用的是底层机制红黑树的insert_equal()。

源码摘要：

```
template<class Key,class Compare=less<Key>,class Alloc=alloc>
class multiset{
	typedef 与set想同，都不允许更改键值
	template<class InputIterator>
	multiset(InputIterator fitst,InputIterator last):t(Compare()){t.insert_equal(first,last);}
	
	iterator insert(const value_type&x){
	return t.insert_equal(x);
	}
}
```

