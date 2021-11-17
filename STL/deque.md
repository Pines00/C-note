### deque

vector是单向开口的连续线性空间，deque是双向开口的连续线性空间。可以在头尾两端分别做元素的插入和删除操作。vector也可以在头尾进行操作，但是头部操作效率奇差。

#### deque与vector差异

* deque允许常数内对头端进行元素的插入或移除操作
* deque没有容量观念，因为是动态的分段连续空间组合而成，随时可以添加一段新的空间并连接起来。而vector需要申请一块更大的空间，然后复制元素，再释放就空间
* deque迭代器不是普通指针，复杂度较高，多以除非必要，尽可能选择使用vector而不是deque。

#### deque中继器

deque由一段一段定量连续空间构成。一旦有必要在deque的前端或微端增加新空间，便配置一段连续空间，串接在整个deque的头端或尾端。deque就是在这些分段的定量连续空间上，维护其整体连续的假象，并提供随机存取的接口，避开了“重新分配、复制、释放”的轮回，代价则是复杂的迭代器架构。

deque采用一块map（一小块连续空间）作为主控。其中每个元素都是指针，指向另一端较大的连续线性空间，称为缓冲区（deque的存储空间主体）。

![deque_map](C:\Users\mzx\Desktop\deque_map.png)

#### deque迭代器

deque 的++ 和--要维护连续整体的任务。首先必须能够指出分段连续空间在哪，其次能判断自己是否已经处于其所在缓冲区的边缘，如果是，一旦前进或后退时就必须跳跃至下一个或上一个缓冲区。为了能够正确跳跃，deque必须随时掌握控制中心（map）。

```
template<class T,class Ref,class Ptr,size_t Bufsiz>
struct _deque_iterator{//不继承iterator
	T * cur;此迭代器所指缓冲区中current元素
	T* first;此迭代器所指缓冲区的头
	T* last;此迭代器所指缓冲区的尾部（其中包含了缓冲区没用完的备用空间）
	map_pointer node;指向管控中心
}
```

![image-20211117211102252](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211117211102252.png)

这是他们之间的关系，迭代器中定义了四个元素，分别是上述代码中定义的四个，前三个指向缓冲区中的是三个元素，其中node节点指向中控器中的节点，然后中控器节点指向buffer。

举个例子：产生一个deque<int>，并令其缓冲区大小为32，于是每个缓冲区可容纳8个元素，让deque拥有20个元素。那么就需要三个缓冲区。所以map中用到3和node，迭代器start中cur指向了deque中第一个元素，finish中的cur指向了deque中的最后一个元素。

![image-20211117212112153](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211117212112153.png)

deque迭代器操作中，这里只列出一个跳node的函数，其他还是看书

```
void set_node(map_pointer new_node){
	node=new_node;//将目前的node切换为传进来的下一个node（缓冲区的node）
	first=*new_node;将迭代器first设为new_node中的首地址，合理
	last=first+difference_type(buffer_size());最后一个元素设为缓冲区大小的最后。
}

self& operator++(){
	++cur;
	if(curr==last){
		set_node(node+1);
		cur=first;
	}
	return *this;
}
```

#### deque的数据结构

deque除了维护一个map指针外，也维护start,finish两个迭代器。分别指向第一缓冲区的第一个元素和最后缓冲区的最后一个元素。此外必须记住目前的map大小。因为一旦mao所提供的阶段不足，就必须重新分配更大的一块map。

```
class deque{
	iterator start;指向第一个节点
	iterator finish;指向最后一个节点
	map_pointer map;指向map
	size_type map_size;map内有多少指针，即map的大小
}
```

#### deque的构造与内存管理



#### deque的常用操作

```
deque.push_back();插入尾部元素
deque.pop_back();删除尾部元素
deque.push_front();插入头部元素
deque.pop_front();删除头部元素
deque.size()返回容器中实际数据的个数
deque.at(index);传回索引idx所指数据，如果index越界，就抛出out of range
```

