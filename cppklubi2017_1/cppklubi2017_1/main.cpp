#include <iostream>
#include <vector>
#include <map>
#include <unordered_map> // C++ 11
#include <queue>
#include <stack>
#include <array>
#include <string>

template <typename Ty>
class OwnStack
{
private:
	std::vector<Ty> data;

public:
	size_t size()
	{
		return data.size();
	}

	void push(Ty i)
	{
		data.push_back(i);
	}

	Ty peek()
	{
		return data.back();
	}

	Ty pop()
	{
		Ty last = data.back();
		data.pop_back();
		return last;
	}
};

enum Language{
	LANGUAGE_SWE = 0,
	LANGUAGE_ENG = 1

};

std::string languageToString(Language lang)
{
	switch (lang)
	{
	case LANGUAGE_SWE:
		return "Ruotsi";
	case LANGUAGE_ENG:
		return "Englanti";
	default:
		return "";
	}
}

int main()
{
	struct LanguagePair
	{
		Language lang; //minkä kielinen käännös
		std::string translation; // itse käännös

		LanguagePair(Language lang, std::string translation)
			: lang(lang), translation(translation)
		{

		}
	};

	std::map<std::string, std::vector<LanguagePair>> sanakirja;
	sanakirja["kirja"].emplace_back(Language::LANGUAGE_SWE, "bocker");
	sanakirja["kirja"].emplace_back(Language::LANGUAGE_ENG, "book");

	sanakirja["tyttö"].emplace_back(Language::LANGUAGE_SWE, "flickan");
	sanakirja["tyttö"].emplace_back(Language::LANGUAGE_ENG, "girl");

	std::cout << "Anna sana minkä haluat kääntää: ";
	std::string input;
	std::cin >> input;

	if (sanakirja.count(input) == 0)
	{
		std::cout << "ei ole sanaa " << input << std::endl;
	}
	else
	{
		std::cout << "Sanan " << input << " kaannokset  ovat:" << std::endl;
		auto& vec = sanakirja[input];
		for (size_t i = 0; i < vec.size(); ++i)
		{
			std::cout << vec[i].translation << " " << languageToString(vec[i].lang) << std::endl;
		}
	}

	return 0;
}

/*int main()
{
	//std::array<int, 10> arr; //int taulukko[10]
	//arr[0] = 5;
	//arr[1] = 6;
	std::vector<int> arr;
	arr.push_back(5); //0
	arr.push_back(6); //1
	arr.back() = 7; //6->7
	arr.front() = 13; //5-13
	arr.pop_back(); // poistaa viimeisen

	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << "item at " << i << " value =" << arr[i] << std::endl;
	}


	// std::array<int,10>::iterator it sama kuin auto it C++ 11
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		std::cout << " value = " << *it << std::endl;
	}

	// range based for C++ 11
	for (auto a : arr)
	{
		std::cout << " value = " << a << std::endl;
	}
	return 0;
}*/