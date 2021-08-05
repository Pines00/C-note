### 39 明智使用private继承

* private继承意味着is-implement-in-terms of 。他通常比复合级别低。但是当派生类需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时，这么设计是合理的
* 和复合不同，private继承可以造成empty base最优化。这对致力于“对象尺寸最小化”的程序库开发者而言，可能很重要。

