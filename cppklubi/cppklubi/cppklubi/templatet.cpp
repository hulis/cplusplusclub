#include <iostream>

//class
//typename käytetty yleisimmiten
//struct

template<typename T, typename T2, typename T3>

struct Foo{
	T t;
	T* tptr;

	T2* t2a;
	T3* t3a;

	void call(){
		t.func();

	}
};

int main()
{
	/*Foo<int, float, double> foo;
	int i = foo.t;
	int* a = foo.tptr;*/

	return 0;
}