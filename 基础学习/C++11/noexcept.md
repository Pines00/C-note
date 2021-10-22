#### noexcept

````
void foo()noexcept;//意思是保证foo这个函数不会抛出异常，如果有异常就会抛出异常直至程序最后调用std::terminate()，然后默认调用std::abort().

如果class中有move动作，一定要加上noexcept
例如
MyString(MyString&& str)noexcept:data(str.data),len(str.len){}
````

#### override

```C++
struct Base{
	virtual void func(float){}
};
struct Derived:Base{
	virtual void func(int) override{}//作用就是派生类想重载这个函数，但是一不小心写错了，编译器就会认为这不是要重载，是重新写了一个函数，所以使用override明确告诉编译器想要重载，这样编译器发现不对劲就会报错。
}
```

#### final

两个作用

```C++
1.
struct Base final{};
struct Derived:Base{};
//表示这个类不可以被继承，是整个继承体系的最后一个环节
2.
struct Base{
	virtual void f()final;
};
struct Derived:Base{
	void f();//就会报错，因为函数加上final表示不可以被重载
}
```

