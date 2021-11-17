### list

list是一个双向链表，与vector不同，也就是说可以随便插入删除。永远是常数时间。

#### list的节点

```
template<class T>{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
}
一个标准的双向链表的节点
```

#### list的迭代器

list迭代器必须具备前移、后移能力，因此list提供的是Bidirectional Iterator。基本是按照线性表的存取来设计。

````
	struct list_iterator:public mystl::iterator<mystl::bidirectional_iterator_tag, T> {
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		typedef typename node_traits<T>::base_ptr base_ptr;
		typedef typename node_traits<T>::node_ptr node_ptr;
		typedef list_iterator<T> self; 
		base_ptr node_;//用来指向当前节点

		//构造函数
		list_iterator() = default;
		list_iterator(base_ptr x):node_(x) {}
		list_iterator(node_ptr x) :node_(x->as_base()) {}
		list_iterator(const list_iterator& rhs) :node_(rhs.node_) {}
		//重载操作符
		reference operator*()const {
			return node_->as_node()->value;
		}
		pointer operator->()const { return &(operator*()); }
		self& operator++()const {//++i
			MYSTL_DEBUG(node_!=nullptr);
			node_ = node_->next;
			return *this;
		}
		self operator++(int) {//表示i++
			self tmp = *this;
			++*this;
			return tmp;
		}
		self& operator--() {//返回其引用类型
			MYSTL_DEBUG(node_!=nullptr);
			node_ = node_->prev;
			return *this;
		}
			/*return *this
			返回的是当前对象的克隆或者本身
			（若返回类型为A， 则是克隆， 若返回类型为A & ， 则是本身 ）
			。return this返回当前对象的地址（指向当前对象的指针）*/
		self operator--(int) {
			self temp = *this;
			--* this;
			return temp;
		}
		bool operator==(const self& rhs)const {
			return node_ == rhs.node_;
		}
		bool operator!=(cnost self& rhs)const {
			return !(node_ == rhs.node_);
		}
	};
````

#### list的构造与内存管理

