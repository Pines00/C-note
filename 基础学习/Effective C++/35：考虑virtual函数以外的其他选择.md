### 35：考虑virtual函数以外的其他选择

 考虑一个这样的案例，假设正在写一个游戏软件，需要有一个函数来计算血量，提供一个healthValue，返回一个整数，表示人物的健康程度。但是不同的人物计算方式不同，将healthValue声明为virtual是比较正确的事情

````C++
class GameCharacter{
public：
	virtual int healthValue() const;//返回人物的健康指数
	...
};
````

但是并没有声明为pure virtual，因为会有一个缺省的算法来计算血量。

这里提供几个方案来替代这种做法

#### 由Non-virtual interface手法实现Template Method模式

​	这是一个主张virtual函数应该是private。主张上面的案例较好的设计是healthValue为public成员函数，但是让他成为non-virtual，并调用一个private virtual函数进行实际工作

```
class GameCharater{
public:
	int healthValue()const{
		...
		int retValue=doHealthValue();
		...	
		return retVal;
	}
private:
	virtual int doHealthValue()const{
		...//缺省算法
	}
}
在class内定义成员函数，都成为了inline
```

这一设计，通过public non-virtual 成员函数间接调用private virtual函数，称为non-virtual interface手法。所谓Template Method设计模式的一个独特表现形式。把这个non-virtual 函数成为virtual函数的外覆器（wrapper）

优点：在于调用virtual函数之前和之后可以进行一些其他操作（heathValue中的省略号处），比如线程操作的锁，验证条件等。如果直接调用virtual函数，就没有办法做这些事。

但是需要在派生类中定义private virtual函数。但是virtual不一定是private，也可以是protected或public。这都很正常

#### 由函数指针实现Strategy模式

在这里，主张人物健康指数的计算与任务类型无关。可以根据每个任务的构造函数接受一个指针，指向一个健康计算函数（构造的时候指定一个计算函数，这样就可以根据人物的不同采用不同的计算方法）。

```C++
class GameCharacter{
public:
	//指针HealthCalcFunc指向一个GameCharacter常量引用的指针
	typedef int(*HealthCalcFunc)(const GameCharacter&);					
	explicit GameCharacter(HealthClacFunc hc= defaultHealthCalc):
		healthFunc(hc){}
	int healthValue()const{return healthFunc(*this);}
private:
	HealthCalcFunc healthFunc;
};

class EvilBadGuy:public GameCharacter{
public:
	explicit EvilBadGuy(healthCalcFunc hc = defaultHealthCalc)
	:GameCharacter(hc){...}
	
};
int loseHealthQuick(const GameCharacter&);
int loseHealthSlowly(const GameCharacter&);

EvilBadGuy ebg1(loseHealthQuickly);//相同任务采用不同的血量计算方式
EvilBadGuy ebg2(loseHealthSlowly);
```

这个方法所提供的有几个优点

* 同一人物类型之不同实体可以有不同的健康计算函数
* 已知人物之健康指数计算函数可在运行期变更。例如GameCharacter可提供一个成员函数setHealthCalculator，用来替换当前的健康指数计算函数。

#### 由tr1::function 完成Strategy模式

如果不使用函数指针，而是改用一个类型为tr1::function的对象，这些约束全都不见了。

```C++
tr1::function:
class GameCharacter;//和之前一样
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter{
public:
	//使用了一个function
	typedef std::tr1::function<int(const GameCharacter&)>HealthCalcFunc;
	explicit GameCharacter(HealthCalcFunc hc=defaultHealthCalc):
	healthFunc(hc){}
	int healthValue()const {
		return healthFunc(*this);
	}
	...
private:
	HealthCalcFunc healthFunc;
};
```

std::tr1::function<int (const GameCharacter&)>

接受一个reference指向const GameCharacter，并返回int，然后function类型产生的对象可以持有任何与此签名是兼容的可调用物。所谓兼容是这个可调用物的参数可被隐式转换为const GameCharacter& ，而其返回类型可被隐式转换为int。和前一个相比，只是将函数指针替换为更加泛化的tr1::function类型。

**总结**

virtual函数的替换方案

* 使用NVI手法，那是Template Method设计模式的一种特殊形式。它以public non-virtual 成员函数包裹低访问性private或protected的virtual函数
* 将virtual函数替换为函数指针成员变量，这是Strategy设计模式的一种分解表现形式
* 以tr1::function 成员变量替换virtual函数，因而允许使用任何可调用物搭配一个兼容于需求的签名式。这也是Strategy设计模式的某种形式
* 将继承体系内的virtual函数替换为另一个继承体系内的virtual函数。这是Strategy设计模式的传统实现手法。

1. virtual函数的替代方案包括NVI手法以及strategy设计模式的多种形式。NVI手法自身是一个特殊形式的Template Method设计模式
2. 将技能成员函数移到class外部函数，带来的一个缺点是，非成员函数无法访问class的non-public 成员
3. tr1::function 对象的行为就像一般函数指针。这样的对象可接纳“与给定之目标签名式兼容”的所有可调用物