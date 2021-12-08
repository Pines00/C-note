### RB-tree

**性质**

1. 每个节点或者是黑丝，或者是红色
2. 根节点是黑色
3. 每个叶子结点是黑色（叶子结点是指为空的叶子结点
4. 如果一个节点是红色，那么他的子节点一定是黑色
5. 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点

**插入**

将红黑树当做一个二叉查找树，将节点插入；然后将节点着色为红色；最后通过旋转和重新着色等方法来修正 该树，使之成为一个红黑树。

* 将红黑树当做一颗二叉查找树，将节点插入。

* 将插入节点着色为红色

  * 将插入节点着色为红色，不会违背特性5，少违背一条特性，就意味着处理的情况越少。

* 通过一系列旋转或着色等操作，使之重新成为一颗红黑树

  * 对于特性1，已经将他涂成红色，不会违背
  * 对于特性2，在第一步中，将红黑树当做二叉查找树，然后执行插入操作。根据二叉查找树的特点，插入操作不会改变根节点。所以根节点仍然是黑色。
  * 对于特性3，叶子结点是指空叶子结点，插入非空节点不会对他们造成影响。
  * 对于特性4，有可能违背的

  接下来，就是想办法使之满足特性4，就可以将树重新构造成红黑树

  根据被插入节点的度节点的情况，可以将“上节点z被着色为红色节点，并插入二叉树”划分三种情况来处理

1. 被插入节点是根节点，：直接把此节点涂为黑色。

2. 被插入节点的父节点是黑色：什么也不需要做，节点被插入后，仍然是红黑树

3. 被插入节点的父节点是红色：处理情况要分为三种

   * case1：当前节点的父节点是红色的，且当前节点的祖父节点的另一个节点（叔叔节点）也是红色

     * 将父节点设为黑色
     * 将叔叔节点设为黑色
     * 将祖父节点设为红色
     * 将祖父节点设为当前节点（红色节点）；之后继续对当前节点进行操作

     谈谈理解：当前节点和父节点都是红色，违背特性4，所以将父节点设置黑色解决这个问题；但是将父节点由红色变成黑色，违背了特性5：因为此时包含父节点的分支总数增加1.解决这个问题的办法是将祖父节点由黑色变成红色，同时将叔叔节点由红色变为黑色。这样能解决包含父节点的分支黑色节点总数增加了1的问题。然后一次向上解决这个问题，直到根节点，那么将根节点设为黑色。图中插入35之后引发的问题。

     ![image-20211121160551968](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211121160551968.png)

   * case2：当前节点的父节点是红色，叔叔节点是黑色或没有叔叔节点，且当前节点是父节点的右孩子，父节点是祖父节点的左孩子：

     * 将父节点作为新的当前节点
     * 以新的当前节点为指点进行左旋

   * case3：当前节点的父节点是红色，叔叔节点是黑色或没有，且当前节点是其父节点左孩子，父节点是祖父节点的左孩子

     * 将父节点设为黑色
     * 将祖父节点设为红色
     * 以祖父节点为支点进行右旋

   总之思想就是将红色节点移到根节点；然后将根节点设为黑色。



#### R_-Btree的节点设计

红黑树有红黑两色，并且拥有左右子节点。此外还安排一个父节点（因为经常上溯父节点）

```
typedef  bool _rb_tree_color_type;
const _rb_tree_color_type _rb_tree_red =false;//红色为0
const _rb_tree_color_type _rb_tree_black=true;//黑色为1

struct _rb_tree_node_base{
	typedef _rb_tree_color_type color_type;
	typedef _rb_tree_node_base* base_ptr;
	color_type color;//节点颜色。非红即黑
	base_ptr parent;
	base_ptr left;
	base_ptr right;
	
	static base_ptr minimum(base_ptr x){//一直向左走，就会找到最小值，这就是二叉搜索树的特性
		while(x->left!=0)x=x->left;
		return x;
	}
	
	static base_ptr maximum(base_ptr x){
		while(x->right!=0)x=x->right;
		return x;
}
}
template <class Value>
struct _rb_tree_node:public _rb_tree_node_base{
	typedef _rb_tree_node<Value>* link_type;//下一个节点
	Value value_field;//节点值
}
```

#### RB—tree的迭代器

RB-tree迭代器实现为两层。_ rb_tree_node 继承自_rb_tree_node_base. _ rb_tree_iterator 继承自 _rb_tree_base_iterator.

![image-20211202143524361](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211202143524361.png)

这个图，_rb_tree_base_iterator中包含一个指向 _rb_tree_node_base的节点，一个自加，一个自减。然后下面 _rb_tree_iterator继承 _rb_tree_base_iterator。并且 _rb_tree_node继承 _rb_tree_node_base。这样他们四个关系就很清晰了。

RB-tree迭代器属于双向迭代器，但不具备随机定位能力。迭代器的前进操作operator++()调用了其父类的increment()，后退操作operator--()调用了父类迭代器decrement()。

```
基层迭代器
struct _rb_tree_base_iterator{
	typedef _rb_tree_node_base::base_ptr  base_ptr;
	typedef bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	base_ptr node;//这个用来与容器之间产生一个连结关系；
	
	void increment(){}//这里就不去实现他
	void decrement(){}//这是迭代器递减操作，具体不实现
};

真正的迭代器
template<class Value,class Ref,class Ptr>
struct _rb_tree_iterator:public _rb_tree_base_iterator{
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typdef _rb_tree_iterator<Value,Value&,Value*> iterator;
	typdef _rb_tree_iterator<Value,const Value&,const Value*> const_iterator;
	typdef _rb_tree_iterator<Value,Ref,Ptr>  self;
	typedef _rb_tree_node<Value>*  link_type;
	
	_rb_tree_iterator(){}
	_rb_tree_iterator(link_type x){node=x;}
	_rb_tree_iterator(const iterator& it){node=it.node;}
	
	reference operator*()const {return link_type(node)->value_field;}
	pointer operator->()const {return &(operator*());}
	
	self& operator++(){increment();return *this}
	self operator++(int){
		self tmp=*this;
		increment();
		return tmp;
	}
	self& opeartor--(){decrement();return *this;}
	self operator--(int){
		self tmp=*this;
		decrement();
		return tmp;
	}
}
```

#### RB-tree的数据结构

