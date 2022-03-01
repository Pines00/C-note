### map

map特性是所有元素都会根据元素的键值被自动排序。map的所有元素都是pair，同时拥有value和key。pair的第一元素被视为key，第二元素被视为value。map不允许两个元素拥有相同的键值。

**想要修改map元素键值是不行的，但是可以更改map的value值** 因为改变map的元素值会破坏map的组织。因此map的iterator不是const_iterator,而是普通的红黑树下的一个迭代器。

map：客户端对它进行元素新增操作或删除操作，操作之前的所有迭代器，操作完之后仍然有效。

红黑树是一种平衡二叉树，自动排序，所以map以红黑树作为底层机制。map底层所有操作都调用红黑树下的操作。

摘录源码

```c++
template<class Key,class T,class Compare=less<Key>,class Alloc=alloc>//缺省采用递增顺序
class map{
	public:
		typedef Key key_type;//键值类型
    	typedef T data_type;//数据类型
    	typedef pair<const Key,T> value_type;//元素类型（键值/实值）
    private:
    	typedef rb_tree<key_type,value_type,selectlst<value_type>,key_compate,Alloc> rep_type;
    	rep_type t;//以红黑树表现map
    public:
    	typedef typename rep_type::iterator iterator;//map并不像set一样将iterator定义为红黑树的const_iterator。因为它允许用户通过其迭代器修改元素的值。
    /* map一定使用底层红黑树的insert_unique()，而不是insert_equal()，因为map不允许相同键值存在*/
    	map()t(Compare()){}
    	explicit map(const Compare&comp):t(comp){}
    	template<class InputIterator>
        map(InputIterator first,InpurItertaor last):t(Compare()){t.insert_unique(first,last);}
    	map(const map<Key,T,Compare,Alloc>&x):t(x.t){}
    	map<Key,T,Compare,Alloc>& operator=(const map<Key,T,Compare,Alloc>&x){
            t=x.t;
            return *this;
        }
    
    //一个比较重要的取值操作,取pair的第二个值，pair的first和second都是public类型
    T& opreator[](const key_type&k){
        return (*((insert(value_type(k,T()))).first)).second;
    }
    
    pair<iterator,bool> insert(const value_type&x){
        return t.insert_unique(x);}
    } 
}	
```

与set类似，使用自带的成员函数find比较快，实现o(1)时间内完成查找。

### multimap

multimap的特性以及用法与map相同，唯一差别在于它允许键值重复，因此他的插入操作是底层机制红黑树的insert_equal()而非insert_unique()。

代码提要：

```c++
template<class Key,class T,class Compare=less<Key>,class Alloc=alloc>
class multimap{
	typedef 与map相同（iterator不是const_iterator,而是在将key定义为const来保证不变）
	template<class InputIterator>
	multimap(InputIterator first,InputIterator last):t(Compare()){
		t.insert_euqal(first,last);
	}
}
```

