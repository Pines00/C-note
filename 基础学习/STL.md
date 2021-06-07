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

使用迭代器来遍历容器可以用如下格式

```
list<double>::iterator pr;
for(pr=score.begin();pr!=scores.end();pr++){
	cout<<*pr<<endl;
}
```

但是在C++11中可以使用自动类型推断可进一步简化：

```
for(autp pr=scores.begin();pr!=scores.end();pr++{
	cout<<*pr<<end
}
```

#### 迭代器

* 指针作为迭代器 

  将指针作为迭代器 具体有两个例子

  ```c++
  1.
  const int SIZE=100;
  double Receipt[SIZE];
  sort(Receipt,Receipt+SIZE);  在这种迭代过程中是支持超尾操作的。
  
  2.
  int cast[10]={1,2,3,4,5,6,7,7};
  vector<int> dice[10];
  copy(cast,cast+10,dice.begin());
  ```

  

#### 函数对象

可以将类当做一个函数来使用，通过重载运算符（）来实现。

```
class Myadd{
public:
int operator()(int v1,int b2){
	return v1+v2;
}
};
void test01(){
	Myadd myadd;
	cout<<myadd(10,10)<<endl;
}
```

谓词：

* 返回bool类型的仿函数称为谓词

* 如果operator()接受一个参数，那么叫做一元谓词

* 若果operator()接受两个参数，那么叫做二元谓词

  

#### String 

string 是一个类，并不是一个关键字

string与char *区别：char*是一个指针，string是一个类，类内部封装了char* ，管理字符串，

string构造函数：

```
string();
string(const char* s );使用字符换s初始化  string str = "hello world"
string(const string& str);赋值字符串 string str1;string str2="ret"; str1=str2;
string(int n,char c);使用n个字符c初始化 string str = 'a';
```

string赋值操作：

```
string& perator=(const char *s);将字符串赋值给当前的字符串
string& perator=(const string &s);将字符串s赋给当前的字符串
string& perator=( char c);字符赋值给当前的字符串
string& assign(const char *S); str.assign("ertert");
string& assign(const char *s,int n);把字符串前n个字符赋给当前字符串
string& assign(const string&s)
string& assign(int n, char c)用n个字符c赋给当前字符串

```

string 字符串拼接

```
string& operator+=(const char *str);
string& operator+=(const char c);
string& operator+=(const string &str);
string &append(const char *s);
string& append(const char *s,int n)字符串s的前n个拼接到字符串结尾
string& append(conststring&s)
string& append(const string &s,int pos,int n)字符串s中从pos开始的n个字符连接到字符串结尾

```

string字符串查找

```
int find(const string& str,int pos=0)const;从字符串pos开始查找，第一次出现str的位置
int find(const char*s,int pos=0)const;
int find(const charc ,int pos=0)const;查找字符c出现的第一次位置
将find换成rfind  是查找对应字符或字符串最后一次出现的地方
string &replace(int pos,int n,const string & str)从pos开始n个字符替换为str
string &replace(int pos,int n,const char*s);
//最后两个写两个例子
string str1= "rterterter";
str1.place(1,2,"1111");
此时str1变为   r1111rterter

```

字符串比较

将其按ASCLL码进行对比

```
=返回0，>返回1，<返回-1
int compare(const string &s)const;
int compare(const char *s)const;
这两个都是字符串比较
```

string  字符存取

````
string中单个字符串存取方式有两种
一种是已经重载字符串的[]
char &operator[](int n);
char &at(int n);
````

string 字符串进行插入和删除操作

```
string &insert(int pos,const char *s);
string &insert(int pos ,const string& str);
string & insert(int pos,int n,char c);在制定位置插入n个字符c
string& erase(int pos,int n=pos)；删除从pos开始的n个字符

！！！ 插入和删除的起始下标都是从0开始

```

string子串：从字符串中获取想要的子串

```
string substr(int pos=0,int n=npos)const;
返回由pos开始的n个字符串组成的字符串
```

#### deque

双端数组，可以对头端进行插入操作

deque对头部的插入速度比vector快，vector访问元素时速度会比deque快

构造函数

```
deque<T> deqT;
deque(begin,end);构造函数将beg，end区间中的元素拷贝给本身
deque(n,elem)构造函数将n个elem拷贝给本身
deque(const deque &deq);拷贝构造函数
写几个例子
#include<deque>
void printDeque(const deque<int>&d){
for(deque<int>::const_iterator it=begin();it!=d.end();it++{
	cout<<*it<<;
}
}
void test01(){
	deque<int>d1;
	for(int i=0;i<10;i++){
		d1.push_back(i);
	}
deque<int>d2(d1.begin(),d1.end());对应第二个构造函数
deque<int>d3(10,100)//生成10个100
printDeque(d3);
deque<int>d4 =d3;
printDeque(d4);
}
```

deque赋值操作

```
deque & opreator=(const deque &deq);//重载等号操作符
assign(begin,end);
assign(n,elem);将n个elem拷贝赋值给本身
```

deque的大小操作：

* deque.empty():判断容器是否为空
* deque.size()返回容器中元素个数
* deque.resize(num)：重新制定容器的长度为num，若容器边长，则以默认值填充，如果容器变短，则末尾超出部分元素被删除
* deque.resize(num,elem);重新指定容器的长度为num若容器变长，则以elem值填充新位置，若容器变短，则删除末尾超出容器长度的元素

deque插入和删除

```
1.在两端操作
push_back(elem);容器尾部插入元素
push_front(elem);容器头部插入元素
pop_back()删除元素最后一个元素
pop_front()删除容器第一个元素

2.指定位置操作
insert(pos,elem);在pos位置插入一个elem元素的拷贝，返回新数据的位置
insert(pos,n,elem);在pos位置插入n个elem数据，无返回值
insert(pos,beg,end);在pos位置插入[beg,end)区间的数据，无返回值
clear();清空容器的所有数据
erase(beg,end)删除[beg,end)区间的数据，返回下一个数据的位置
erase(pos)删除pos位置的数据，返回下一个数据的位置

```

deque数据存取：

```
at(int index)//返回索引值所知数据
operator[]//返回索引所指数据
fornt();返回容器中第一个元素数据
back();返回容器中最后一个元素数据
```

排序：

```
sort(iterator beg,iterator end)
```

#### stack

栈容器对外接口

```
构造函数：
stack<T> stk;
stack(const stack &stk);

赋值操作：
stack& operator=(const stack &stk)

数据存取：
push(elem)向栈顶添加元素
pop();从栈顶一处第一个元素
top()返回栈顶元素

大小操作：
empty();判断栈是否为空
size();返回栈的大小
```

queue:队列的对外接口

```
queue<T> que;
queue(const queue &que);

赋值操作:
queue& operator=(const queue &que);

数据存取：
push(elem)往队尾添加元素
pop();从队头移除第一个元素
back()返回最后一个元素
front()返回第一个元素

大小操作
empty()判断是否为空
size()返回栈的大小

```

#### List

将数据进行链式存储，在物理存储中非连续内存的存储结构，数据元素按逻辑顺序是通过链表中的指针链接实现

由一系列节点组成，数据域和指针域

list是一个双向循环链表

优点：

* 采用动态存储分配，不会造成内存浪费和溢出
* 链表执行插入和删除 操作十分方便，修改指针即可，不需要移动大量元素

缺点：

* 链表虽然灵活，但是遍历额外开销较大，只能顺序遍历

```
构造函数：
list<T> l;
list(begin,end);
list(n.elem);
list(const list &l);

赋值与交换
assign(beg,end)
assign(n,elem)
list& operator=(const list &lst)
swap(lst);

大小操作：
size()
empty()
resize(num)
resize(num,elem)

对list容器 插入和删除
push_back(elem)尾部插入元素
pop_back()删除容器中最后一个元素
push_front(elem)在容器开头插入一个元素
pop_front()
insert(pos,elem);在pos位置插入元素elem，返回新数据的位置
insert(pos,n,elem) 在pos位置插入n个elem数据，无返回值
insert(pos,beg,end);字pos位置插入[beg,end）区间的数据，无返回值
clear()移除容器的所有数据
erase（beg,end）删除[beg,end)区间的数据，返回下一个数据位置
erase(pos)删除pos位置的数据，返回下一个数据的位置
remove(elem)删除容器中所有与elem值匹配的元素


存取：
front()返回第一个元素
back()返回最后一个元素

reverse()反转链表
sort()链表排序

```

#### set/mutiset 容器

所有元素都会在插入时自动排序，底层是二叉树实现

set与mutiset区别

* set不允许容器中有重复的元素
* mutiset允许容器中有重复的元素

```
set构造与赋值
set<T> st;
set(const set &st)

赋值
set& operator=(const set &st);

大小问题
size()
empty()
swap(st)

插入和删除
insert(elem)
clear()
erase(pos)
erase(begin,end)
erase(elem)

set查找和统计
find(key)查找key是否存在，返回key的元素迭代器，若不存在返回set.end()
count(key)统计key的元素个数
```



#### set 与mutiset

* set不可以插入重复数据，而multiset可以
* set插入数据的同时会返回插入结果，表示插入是否成功
* multiset不会检测数据,因此可以插入重复数据

```c++
pair对组：承兑出现的数据，利用对组可以返回两个数据
创建方式：
pair<type,type> p(value1,vlaue2);
pair<type,type>p=make_pair(value1,value2);


#include <string>
//对组创建 void test01() {
pair<string, int> p(string("Tom"), 20);
cout << "姓名：    " <<  p.first << " 年龄：    " << p.second << endl; pair<string, int> p2 = make_pair("Jerry", 10);
cout << "姓名：    " << p2.first << " 年龄：    " << p2.second << endl; }


set排序：
    默认排序规则从小到大
    利用仿函数（函数对象），可以改变排序规则
写个例子
    class MyCompare{
        public :
        bool operator()(int v1,int v2){
            return v1>v2;
        }
    };
void test01(){
    set<int> s1; 
    s1.insert(10); 
    s1.insert(40); 
    s1.insert(20); 
    s1.insert(30);
    s1.insert(50);
    //默认从小到大
for (set<int>::iterator it = s1.begin(); it != s1.end(); it++) 
{ cout << *it << " ";
}
cout << endl;
    
    //指定排序规则
set<int,MyCompare> s2; 
    s2.insert(10);
	s2.insert(40);
    s2.insert(20); 
    s2.insert(30); 
    s2.insert(50);
}
```

#### map/multimap

map中所有元素都是key，value形式，形如python中的字典。

所有元素都会根据元素的key自动排序，他们都属于关联式容器，底层是二叉树

* 优点：可以根据key快速找到value

他们之间的区别：

* map不允许容器中有重复的key值元素
* multimap允许容器中有重复key值元素

```c++
构造和赋值：
map<T1,T2> mp;默认构造函数
map(const map &mp);拷贝构造函数

map& operator=(const map &map);重载等号操作符
大小与交换：
size()容器中元素数目
empty()判断容器是否为空
swap()交换两个集合容器

map插入和删除
insert(elem)插入元素 
clear()删除所有元素
erase(pos)删除pos迭代器所指的元素，返回下一个元素迭代器位置
erase(beg,end)删除区间[beg,end)所有元素，返回下一个元素的迭代器
erase(key)删除容器中为key的元素

map查找和统计
find(key)查找key是否存在，若存在返回该key元素的迭代器；若不存在，返回set.end
count(key)统计key的元素个数

map容器排序
map容器默认排序规则按照key值排序，从小到大，可以利用仿函数可以改变排序规则
利用仿函数改变排序规则


#include<iostream>
#include<map>
using namespace std;
class Mycompare {
public:
	bool operator()(int v1, int v2)const {
		return v1 > v2;
	}
};
void tet01() {
	map<int, int, Mycompare>m;
	m.insert(make_pair(1,50));
	m.insert(make_pair(2, 20));
	m.insert(make_pair(3, 30));
	m.insert(make_pair(4, 40));
	m.insert(make_pair(5, 50));
	for (map<int, int, Mycompare>::iterator it = m.begin(); it != m.end(); it++) {
		cout << "key:" << it->first << " value:" << it->second << endl;
	}
}
int main() {
	tet01(); 
	system("pause"); 
	return 0;
}
```



### 常用算法

#### 遍历

```
for_each(iterator beg,iterator end,_func);遍历容器_func函数或函数对象
transform(iterator beg,iterator end,iterator beg1,_func)搬运容器到另一个容器中
beg1为目标容器的开始迭代器，_func函数或者函数对象
```

#### 查找

```
find(iterator beg,iterator end,value)value查找的元素
返回的是迭代器类型
find_if(iterator beg,iterator end,_Pred);
按值查找，_Pred函数或者谓词（返回bool类型的仿函数）,按条件查找更加灵活，提供的防函数可以改变不同的策略

adjacent_find(iterator beg,iterator end);
查找相邻重复元素，返回相邻元素的第一个位置的迭代器
beg开始迭代器，end结束迭代器

bool binary_search(iterator beg,iterator,end,value)
//查找指定的元素，查到返回true，否则false，！！！在无序序列中不可用

count(iterator beg,iterator end,value)
统计元素出现个数
count_if(iterator beg, iterator end, _Pred);同样_Pred谓词
```

#### 排序

```
sort(iterator beg,iterator end,_Pred);默认从小到大排序
sort(beg,end,greater<int>()); 从大到小的顺序排序


random_shuffle(beg,end)//重新洗牌，打乱顺序.

merge(beg1,end1,beg2,end2,iterator dest)
// beg1 容器1开始迭代器 // end1 容器1结束迭代器 // beg2 容器2开始迭代器 // end2 容器2结束迭代器 // dest 目标容器开始迭代器

reverse(iterator beg,iterator end);反转
```

#### 复制和替换算法

```
copy(beg,end,dest)dest为目标容器的开始
replace(iterator beg, iterator end, oldvalue, newvalue)
replace_if(iterator beg, iterator end, _pred, newvalue)
swap(container c1, container c2);交换连个容器的元素
```

#### 算数生成算法

```
头文件#include <numeric>
accumulate(iterator beg, iterator end, value);计算容器元素累计总和，value为起始值

fill(iterator beg,iterator end,value);像容器中填充元素，beg开始迭代器，end结束迭代器
value填充的值
```

#### 常用的集合算法

```
头文件#include <algorithm>


set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
求两个集合的交集，两个集合必须是有序序列，dest目标容器开始迭代器
目标容器开辟的空间需要从两个容器中取小的值，返回值是交集中最后一个元素的位置

set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);两个集合的并集，返回值是并集中最后一个元素的位置

set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);求两个几个的差集，必须是有序序列，开辟的空间从两个容器取较大值
```



