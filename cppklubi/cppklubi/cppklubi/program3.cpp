#include <iostream>
#include <stdint.h>

struct Foo{
	int32_t a;
	//int8_t _pad[3];
	int8_t b;
	//int8_t c;
	//int16_t d;
};

int main()
{
	char* memory = new char[128];

	Foo* foo = (Foo*)&memory[0];

	foo->a = 10;
	foo->b = 20;

	Foo* bar = (Foo*)&memory[3];
	bar->a = 20;

	//std::cout << sizeof(Foo) << std::endl;
	
	system("pause");

	return 0;
}