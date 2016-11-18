#include <iostream>
#include <string>

class Person{ // private, protected, public
private:
	int age;
	std::string name;
public:
	Person(int age, std::string name) :
		age(age), name(name)
	{
		// this->age = age; //�lk�� pliis
		// this->name = name; //tehk� n�in
	}

	//setterit
	void setAge(int newAge)
	{
		age = newAge;
	}
	void setName(std::string name)
	{
		if (name.empty()) return;
		this->name = name;
	}

	// getterit
	int getAge()
	{
		return age;
	}
	std::string getName()
	{
		return name;
	}

	void print()
	{
		std::cout << getName() << " on " << getAge() << std::endl; //luokan sis�ll� ei tarvita aatu.getName
	}

/*	~Person()
	{
		std::cout << name << " tuhottiin" << std::endl;
	}
private:
	int enNayUlospain;*/
};

int main()
{
	Person aatu(5, "aatu");
	Person hitler(133, "hitler");
	Person kebab(715517, "kebab");
	aatu.setAge(55);
	aatu.setName("Pekka");
	aatu.print();
	kebab.print();
	hitler.print();
	//std::cout << aatu.getName() << " on " << aatu.getAge() << std::endl; //k�yt� mieluummin gettereit� ja settereit�
	system("pause");

	return 0;
}