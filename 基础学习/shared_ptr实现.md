### pointer-like classes智能指针

shared-ptr

```
#include<string>
#include<iostream>
using namespace std;
template<typename T>
class Shared_ptr {
private:
	T* ptr;
	int* count;
public:
	Shared_ptr() :count(0), ptr((T*)0) {}
	Shared_ptr(T* p):count(new int(1)),ptr(p){}
	Shared_ptr(Shared_ptr<T>& other) :count(&(++* other.count)), ptr(other.ptr) {}//&(++* other.count）这个意思other的count与copy之后的Shared_ptr共用一个count

	T& operator*() {
		return *ptr;
	}
	T* operator->() {
		return ptr;
	}
	Shared_ptr<T>& operator=(Shared_ptr<T>& other) {
		if (this == &other) {
			return *this;
		}
		++* other.count;
		if (this->ptr && -- * this->count == 0) {
			delete count;//代表this->count;
			delete ptr;
		}
		this->ptr = other.ptr;
		this->count = other.count;
		return *this;
	}

	~Shared_ptr() {
		if (ptr && -- * count == 0) {
			delete count;
			delete ptr;
		}
	}
	int getRef() {
		return *count;
	}
};
int main(int argc, const char* argv[])
{
	Shared_ptr<string> pstr(new string("abc"));
	cout << "pstr:" << pstr.getRef() << " " << *pstr << endl;

	Shared_ptr<string> pstr2(pstr);
	cout << "pstr:" << pstr.getRef() << " " << *pstr << endl;
	cout << "pstr2:" << pstr2.getRef() << " " << *pstr2 << endl;

	Shared_ptr<string> pstr3(new string("hao"));
	cout << "pstr3:" << pstr3.getRef() << " " << *pstr3 << endl;

	pstr3 = pstr2;
	cout << "pstr:" << pstr.getRef() << " " << *pstr << endl;
	cout << "pstr2:" << pstr2.getRef() << " " << *pstr2 << endl;
	cout << "pstr3:" << pstr3.getRef() << " " << *pstr3 << endl;


	return 0;
}
结果在下面
```

![image-20211102211608685](C:\Users\mzx\AppData\Roaming\Typora\typora-user-images\image-20211102211608685.png)

