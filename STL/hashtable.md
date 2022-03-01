### hashtable

#### hashtable 的桶子与节点

STL以开链法完成hash table的图形表述。hashtable表格内的元素为桶子。

![image-20220222205557654](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20220222205557654.png)

下面是hashtable的节点定义

```
template<class Value>
struct _hashtable_node{
	_hashtable_node* next;
	Value val;
}
```

其实类似于链表的定义

#### hashtable的迭代器

```c++
template<class Value,class Key,class HashFcn,class ExtractKey,class EqualKey,class Alloc>
struct _hashtable_iterator{
	typedef hashtable<...>  hashtable;
	typedef _hashtable_iterator<...> iterator;
	typedef _hashtable_const_iterator<...> const_iterator;
	typedef _hashtable_node<Value> node;
	
	node* cur;//迭代器目前所指节点
	hashtable* ht;//保持对容器的连结关系（可能需要从bucket跳到bucket）
	_hashtable_iterator(node* n,hashtable* tab):cur(n),ht(tab){}
	_hashtable_iterator(){}
	reference opetator*()const{return cur->val;}
    pointer operator->()const{return &(operator*());}
    iterator& operator++();
    iterator opreator++(int);
    bool operator==(const iterator& it)const{return cur==it.cur;}
    bool operator!=(const iterator& it)const{return cur!=it.cur;}
};
```

hashtable迭代器必须永远维系整合“buckets vector”的关系，并记录目前所指的节点。其前进操作是首先尝试从目前所指的节点出发，前进一个位置，由于节点被安置于list内，所利用节点的next指针即可轻易达成前进操作。如果目前节点正巧是list的尾端，就跳至下一个bucket身上，那正是指向下一个list的头部节点。

```c++
template<...>
_hashtable_iterator<...>& _hashtable_iterator<...>::operator++(){
	const node* old=cur;
	cur=cur->next;//如果存在就是他，否则进入if
	if(!cur){
		size_type bucket=ht->bkt_num(old->val);//元素落脚于哪一个bucket之内
		while(!cur&&++bucket<ht->buckets.size())//{
			cur=ht->buckets[bucket];
		}
	}
}

template<...>
inline _hashtable_iterator<...> _hashtable_iterator<>::operator++(int){
    iterator tmp=*this;
    ++*this;//调用operator++()
    return tmp;
}
```

#### hashtable 的数据结构

bucket聚合体以vector完成，以利用动态扩充

```c++
template<class Value,class Key,class HashFcn,class ExtractKey,class EqualKey,class Alloc>
class hashtable{
	public:
		typedef HashFcn hasher;//为template型别参数重新顶一个一个名称
		typedef EqualKey key_equal;//为template型别参数重新定义一个名称
		typedef size_t size_type;
	hasher hash;
	key_euqal equals;
	EctractKey get_key;
	typedef __hashtable_node<Value> node;
	typedef simple_alloc<node,Alloc> node_allocator;
	
	vector<node*,Alloc> buckets;//以vector完成
	size_type num_elements;
	
	size_type bucket_count()const{return buckets.size();}
}
```

#### hashtable的构造与内存管理

```
构造函数
hashtable(size_type n,const HashFcn& hf,const EqualKey& eql):
hash(hf),equals(eql),get_key(ExtractKey()),num_elements(0){
	initialize_buckets(n);
}

void initallize_buckets(size_type n){
	const size_type n_buckets=next_size(n);//返回下一个质数个
	buckets.reserve(n_buckets);
	buckets.insert(buckets.end(),n_buckets,(node*)0);
	num_elements=0;
}
```

##### 插入元素

```
pair<iterator,bool> insert_unique(const value_type& obj){
	resize(num_elements+1);//判断是否需要重建表格，如需要就扩充
	return insert_unique_noresize(ojb);
}

resize：拿元素个数（新增的也计入）和bucket vector大小来比较，如果前者大于后者，就重建表格。
需要重新配置就找出下一个质数，重新定义vector设立新的buckets。
然后处理每一个旧的bucket
找到旧的节bucket的起始节点，处理旧的bucket所含的每一个节点。然后找出这个节点在新的bucket中的落点，之后令旧的bucket指向其所对应的串行的下一个节点，将当前节点插入到新的bucket内，成为其对应的串行的第一个节点，回到旧的bucket所指的待处理串行，准备处理下一个节点。

在不需要重建表格的情况下插入新节点，键值不允许重复，如果重复直接返回。
```

#### hash_set

hash_set以hashtable为底层机制。由于hash_set所对应的操作接口，hashtable都提供了，所以几乎所有的hash_set行为都是调用hashtable行为。

运用set能够快速搜索元素，无论底层是红黑树还是hashtable，都可以达成任务。但是set有自动排序的功能，hashset没有。

#### hash_map

hash_map以hashtable为底层机制。hashmap所有操作都是调用hashtable的操作

用map为了快速查找元素，底层无论是rb_tree还是hashtable。hash_map唯一特性就是每个元素有key和value。hash_map的使用方式和map完全相同。
