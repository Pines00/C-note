#### for 的另外一种形式

```
for(decl:coll){
	statement
}

for(int i:{1,2,3,4,5}){
	cout<<i<<endl;
}

vector<double> vec;
for(auto elem:vec){//这样需要copy到elem
	cout<<elem<<endl;
}
for(auto& elem:vec){//直接用引用，避免赋值操作，快一点
	elem*=3;
}
```

