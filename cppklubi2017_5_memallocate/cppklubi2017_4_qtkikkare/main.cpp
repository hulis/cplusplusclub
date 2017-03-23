#include <stdlib.h>
#include <new>
#include <string.h>

class Yolo
{
private:
	int i;
public:
	Yolo(int i) : i(i) {}
};

int main()
{
	char memory[128] = {0}; // {} alustaa nollaksi.
	memset(memory, 0, sizeof(memory)); //c-kielellä. #include <string.h>
	//Yolo* yolo1 = new Yolo(5); // heap
	Yolo* yolo2 = new (memory)Yolo(5);
	Yolo* yolo3 = new (memory + sizeof(Yolo))Yolo(10);

	Yolo* ptrToYolo2 = reinterpret_cast<Yolo*>(memory);
	Yolo* ptrToYolo3 = reinterpret_cast<Yolo*>(memory + 4);
	//satic_cast
	//dynamic_cast
	//reinterpret_cast
	//const_cast
	
	return 0;
}