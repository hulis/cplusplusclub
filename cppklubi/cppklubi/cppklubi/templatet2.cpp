#include <iostream>
#include <stdint.h>
#include <string>
#include <algorithm>

template<typename T>
class Vector final {
private:
	uint32_t capacity;
	uint32_t len;

	T* elements;
public:
	Vector() {
		const uint32_t InitialCapacity = 2;

		elements = new T[InitialCapacity];
		capacity = InitialCapacity;
		len = 0;
	}

	void reserve(uint32_t capacity) {
		if (this->capacity <= capacity) {
			uint32_t oldCapacity = this->capacity;
			uint32_t newCapacity = oldCapacity * 2;

			T* newElements = new T[newCapacity];

			//std::memcpy(newElements, elements, sizeof(T) * len);

			for (auto i = 0u; i < oldCapacity; i++)
				newElements[i] = elements[i];

			delete[] elements;

			elements = newElements;
			this->capacity = newCapacity;
		}
	}

	void push_back(T element) {
		reserve(len);

		elements[len++] = element;
	}

	T element_at(uint32_t index) {
		return elements[index];
	}

	bool remove(T element) {
		auto it = std::find_if(begin(), end(),
			[&element](T& elem) { return element == elem; });

		if (it != end()) {
			*it = T();
			return true;
		}

		return false;
	}

	T* begin() {
		return &elements[0];
	}
	T* end() {
		return &elements[len];
	}

	uint32_t get_len() {
		return len;
	}

	~Vector() {
		delete[] elements;
	}
};

struct bar {
	void fnc() {
		std::cout << "fnc called" << std::endl;
	}
};

template<typename T>
void call(T* element) {
	element->fnc();
}

template <size_t N>
struct Sum {
	enum { value = Sum<N - 1>::value + N };
};

template <>
struct Sum<0> {
	enum { value = 0 };
};

/*template <>
Vector<std::string>::Vector() = delete;*/

int main() {

	std::cout << Sum<499>::value << std::endl;
	bar b;
	call<bar>(&b);

	Vector<int> mvec;

	for (int i = 0; i < 16; i++) mvec.push_back(i);
	for (uint32_t i = 0; i < mvec.get_len(); i++)
		std::cout << mvec.element_at(i) << std::endl;

	mvec.remove(5);

	Vector<std::string> jeesus;
	jeesus.push_back("mein");
	jeesus.push_back("awp");
	jeesus.push_back("top");
	jeesus.push_back("kek");

	for (auto i = 0u; i < jeesus.get_len(); i++)
		std::cout << jeesus.element_at(i) << std::endl;

	for (auto jeesus : mvec) {
		std::cout << jeesus << std::endl;
	}

	return 0;
}