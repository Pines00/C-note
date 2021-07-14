### 避免返回handles指向对象内部成分

案例：假设程序涉及矩形。每个矩形由左上角和右上角表示。为了让一个Rectangle对象尽可能小，可能会决定不把定义矩形的点存放在Rectangle对象内，而是放在一个辅助的struct内再让Rectangle去指它：

```C++
class Point{
public :
	Point(int x,int y);
	void setX(int newVal);
	void setY(int newVal);
};
struct RectData{
	Point ulhc;
	Point lrhc;
};
class Rectangle{
public:
	//这两个函数用于计算Rectangle范围
	Point &upperLeft()const{return pData->ulhc;}
	Point &lowerRight()const{return pData->lrhc;}
private:
	std::tr1::shared_ptr<RectData> pData;
}
```

这样可以通过编译，但确实错误的。实际上自我矛盾。upperLeft和lowerRight被声明为const成员函数，他们目的只是提供客户一个得知Rectangle相关坐标点的方法，而不是让客户修改Rectangle。但是两个函数返回reference指向private内部数据，调用者于是可以通过reference更改内部数据：

```
Point coord1(0,0);
Point coord2(100,100);
const Rectangle rec(coord1,coord2);
rec.upperLeft().setX(50);
```

这里可以使用返回的reference（指向rec内部的Point成员变量）来更改成员。但rec其实应该是不可变的（const）.

成员变量的封装性最多只等于“返回其reference”的函数访问级别。虽然ulhc和lrhc都被声明为private，实际上却是public，因为public函数upperLeft和lowerRight传出他们的reference。

如果const成员函数传出一个reference，后者所指数据与对象自身有关联，而它又被存储于对象之外，那么这个函数的调用者可以修改那笔数据。这是bitwise constness的一个附带结果。

无论返回指针或者迭代器，相同情况也想通，统统被称为Handles，返回这种handle，会带来降低对象封装性的风险。同时，也可能导致调用const成员函数却造成对象状态被更改。



解决这种问题的办法就是对返回类型加上const

```
class Rectangle{
public:
	//这两个函数用于计算Rectangle范围
	const Point &upperLeft()const{return pData->ulhc;}
	const Point &lowerRight()const{return pData->lrhc;}
private:
	std::tr1::shared_ptr<RectData> pData;
}
```

这样就不可以修改了。

总结：

​	避免返回handles（包括reference、指针、迭代器）指向对象内部。遵守这个条款可增加封装性，帮助const成员函数的行为像个const，并将发生“虚吊号码牌”的可能性降至最低