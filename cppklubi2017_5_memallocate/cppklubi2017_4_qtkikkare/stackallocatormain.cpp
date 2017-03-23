#include <stdlib.h>
#include <new>
#include <string.h>
#include <iostream>

template <size_t MaxSize>

class StackAllocator
{
	char memory[MaxSize];
	char* p;
	
public:
	StackAllocator()
		: p(NULL)
	{
		memset(memory, 0, sizeof(memory));
		p = memory;
	}

	void* allocate(size_t bytes)
	{
		if (bytes == 0) return NULL;
		// meillä ei ole tilaa
		if (p + bytes > memory + MaxSize) return NULL;

		char* result = p;
		p += bytes;

		return result;
	}
};

#include <assert.h>

template <typename Ty>
class OwnArray
{
	StackAllocator<4096>& allocator;
	void* memory;
	size_t maxElements;
public:
	OwnArray(StackAllocator<4096>& allocator, size_t size)
		: allocator(allocator),
		maxElements(size)
	{
		memory = allocator.allocate(sizeof(Ty) * size);
	}

	const Ty& operator[](size_t index) const
	{
		char* ptr = static_cast<char*>(memory);
		ptr += sizeof(Ty) * index;
		return *reinterpret_cast<Ty*>(ptr);
	}

	Ty& operator[](size_t index)
	{
		return
			const_cast<Ty&>(
			static_cast<const OwnArray<Ty>&>(*this)[index]
			);
	}
};

int main()
{
	StackAllocator<4096> allocator;

	OwnArray<int> arr(allocator, 3);
	arr[0] = 5;
	arr[1] = 10;
	arr[2] = 15;
	std::cout << arr[0] << ", " << arr[1] << ", " << arr[2] << std::endl;

	return 0;
}