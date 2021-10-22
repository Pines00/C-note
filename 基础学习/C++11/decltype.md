#### decltype

就是用来获取对象类型一个关键字相当于typeof,结果可以是引用类型。

！！！decltype(())这种双括号永远是一个引用类型

```
const int ci=0;
decltype(ci) x=0;
意思是获取到ci的类型，使用同ci相同类型来定义x
```

三个用途

* used to declare return types

  ```
  template<typename T1,typename T2>
  decltype(x+y) add(T1 x,T2 y){//这样编译不过，因为x和y没有被定义
  
  }
  可以这样使用
   template<typename T1,typename T2>
   auto add(T1 x,T2 y)->decltype(x+y);
  
  ```

* 元编程

* pass the type of a lambda

  ```
  ```

  