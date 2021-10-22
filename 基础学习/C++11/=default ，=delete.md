#### =default ，=delete

如果自行定义了一个构造函数，编译器就不会给一个default 构造函数

如果强制加上=default 就可以重新获得并使用default 构造函数

只有构造函数才能default，拷贝构造函数与拷贝赋值函数是不能default的，也就是说只能有一个

 =delete是用来阻止拷贝，当某些类不用来拷贝时候，使用=delete来防止编译器自动生成默认的拷贝构造函数活拷贝赋值函数



=default只能用在类内 

=delete能用在任何函数中