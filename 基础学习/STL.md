## STL

#### vector

类似于数组，但是vector可以动态分配内存。

使用方法vector< type> name(size)

vector模板的方法：

* size()大小

* begin()返回一个指向容器中第一个元素的迭代器

* end()返回一个表示超过容器尾的迭代器

* push_back():将元素添加到末尾

* erase()：删除给定区间的元素例如 ` score.erase(score.begin(),score.brgin()+2);` 

  注意删除到后一个参数的前一个元素。

* insert()：接受三个参数，第一个制定元素插入位置，第二个和第三个定义了被插入区间

  例如将new_v中第一个元素外的所有元素插入到old_v矢量的第一个元素前面

  ``` 
  vector<int> old_v;
  vector<int>new_v;
  old_v.insert(old_v.begin(),new_v.begin()+1,new_v.end());
  ```

  

* swap()

迭代器：迭代器是一个名为iterator的typedef  作用域为整个类；

例如使用vector的一个迭代器可以这样使用 

```
vector<double>::iterator pd;
vector<double> scores;
pd=scores.begin();
*pd=22.3;
++pd;
```

三个代表性的STL()

* for_each()
* random_shuffle()
* sort()

使用方法：

```
1.
vector<Review>::iterator pr;
for(pr=books.begin();pr!=books.end();pr++){
	ShowReview(*pr);
}
可以替换为
for_each(books.begin(),books.end(),ShowReview);


2.
random_shuffle(books.begin(),books.end());
接受两个指定区间的迭代器参数，并随机排列该区间中的元素。
```

#### 泛型

为何要使用迭代器。使用迭代器原因是独立于数据结构，独立于存储类型，实现一种通用的算法来实现特定功能。比如在实现find函数过程中。如果数据结构有数组和链表，那么这两种遍历方法完全不同，但是使用迭代器就可以实现不同的数据结构通用遍历。