### stack and queue

#### stack

stack是以deque为基础建立的，将deque作为缺省状态使用。

```
template<class T,class Sequence=deque>
class stack{
	
}
```

也可以将list作为底层容器。

queue也一样

#### heap

heap底层是一个完全二叉树，可以用一个array来存储所有的节点，当完全二叉树某个节点位于array的i处时，其左子节点位于2i，右子树位于2i+1，父节点位于i/2；即用数组来表示一个完全二叉树。所只需要一个数组和heap算法（用来插入元素、删除元素、取极值），但是用vector来替代heap更好，可以动态增长；

根据元素排列方式。可分为大根堆和小根堆。

heap算法：

​	push_heap算法。新插入元素放在vector最后一个元素后。但为了满足max-heap，需要调整节点次序；