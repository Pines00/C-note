#### 右值引用（Rvalue reference）



左值：是一个变量，可以放在operator=的左侧

右值：只能出现于operator=右侧；

临时对象就是一个右值

```
int foo(){return 5;}
int x=foo();
int* p =&foo();//error，取其reference不可以，因为函数返回值是右值，没法取

地址。
foo()=7;//error
```

当Rvalue出现于operator=（copy assignment）右侧，我们认为对其资源进行偷取/搬移而非copy是合理的那么：

* 1.必须有语法让我们在调用端告诉编译器，这是个右值
* 必须有语法让我们在被调用端专门处理右值的move assignment函数



写一个move版本的class

```:data()
MyString(MyString && str)nocxcept:data(str.data),len(str.len){
	str.eln=0;
	str.data=null;//这很重要，必须要设为null
}
```



