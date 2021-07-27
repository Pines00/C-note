### 确定public继承是is-a关系

C++进行面向对象编程，最重要的一个规则是public inheritance意味着is-a关系。令class D以public形式继承 class B，便是告诉编译器，每一个类型为D的对象，同时也是一个类型为B的对象，反之不成立。

```
class Person{}
class Student:public Person{}
人的概念比学生更一般化，学生是人的一种特殊形式。
```

这个观点只限于public继承。只有当Student以public形式继承PersonC++行为才会如上描述。private继承的意义与此不同。

但是is-a关系要建立合适的继承机制，例如鸟会飞，企鹅是鸟，企鹅不会飞。

**案例**

正方形与矩形之间的继承关系

```
class Rectangle{
public:
	virtual void setHeight(int newHeight);
	virtual void setWidth(int newWidth);
	virtual int height()const;
	virtual int width()const;
};
void makeBihher(Rectangle& r){
	int oldHeight=r.height();
	r.setWidth(r.width()+10);
	assert(r.height()==oldHeight);
}
上面的assert结果永远为真。因为makeBigger只改变R的宽度；r的高度没有被改变
现在：
class Square:public Rectangle{};
Square s;
assert(s.width()==s.height());//对于正方形来说是正确的的
makeBigger(s);//增加其面积
assert(s.width()==s.height());//对所有正方形来说应该仍为真

```

但是

* 调用makeBigger之前,s的高度和宽度相同
* 在makeBigger函数内，s的宽度改变，但高度不变
* makeBigger返回之后，s的高度和宽度想同？？？？？不同了

这个案例的困难之处在于，可以实施于矩形身上的事情，却不能施行与正方形身上。但是public继承主张能够施行与base class对象身上的每件事，也可以释行于derived class身上。编译器会通过编译，但是逻辑上是错误的。

is-a并非是唯一存在于class之间的关系，另外两个常见的关系是has-a和is-implemented-in-terms-of（根据某物实现出）。将上述这些重要的相互关系中任何一个误塑为is-a而造成的错误设计，在C++中并不罕见，所以要了解类之间的差异。



**总结** 

* public继承意味着is-a关系，适用于base class身上的每一件事情一定也适用于derived class身上，因为每一个derived class对象也都是一个base  class对象。