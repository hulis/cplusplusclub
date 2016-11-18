#include <iostream>

struct Foo{
	int i;
	int j;
};

int main()
{
	// C++ tyylin dynaminen alloc
	Foo* foo = new Foo;
	foo->j = 10;
	foo->i = 20;

	// Käytetään foota...
	// ...
	// ...
	// ...

	delete foo;

	// C tyyliin
	Foo* bar = (Foo*)malloc(sizeof(Foo));
	bar->j = 30;
	bar->i = 40;

	// Käytetään baria..
	// ...
	// ...
	// ...

	free(bar);

	system("pause");

	return 0;
}

/*Foo* createFoo(int i, int j)
{
	Foo* foo = new Foo();

	foo->i = i;
	foo->j = j;

	return foo;
}

void leakingFunction()
{
	Foo* foo = new Foo;

	
}

void leakingFunction()
{
	void* mem = malloc(sizeof(Foo)); // Allokoidaan Foo
	Foo* foo = (Foo*)mem;			 // Tehdään konversio

	foo->j = 12;
	foo->i = 10;

	free(mem);

}*/