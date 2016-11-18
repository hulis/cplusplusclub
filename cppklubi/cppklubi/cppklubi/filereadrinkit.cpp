#define _CRT_SECURE_NO_WARNINGS
#include <fstream> // lukee ja kirjoittaa
#include <ostream> // kirjoittaa
#include <istream> // lukee
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void c_style()
{
	FILE* file;
	
	file = fopen("teksti.txt", "a");

	if (file == NULL)
	{
		std::cout << "failed to open file" << std::endl;
	}

	std::string hello("hello world");
	fwrite(
		hello.c_str(),	// pointer mit‰ kirjoitetaan
		sizeof(char),	// paljon elementin koko (meid‰n tapauksessa yksi merkki)
		hello.size(),	// montako elementti‰ kirjoitetaan
		file			// tiedostokahva minne kirjotetaan
		);

	fclose(file);

	FILE* file2;
	file2 = fopen("teksti.txt", "r");

	fseek(file2, 0, SEEK_END); // kelaa tiedosto loppuun
	long fileSize = ftell(file2); // kerro pointerin asema
	fseek(file2, 0, SEEK_SET); // kelaa takaisin alkuun

	/*	file2.seekg(0, std::ios::end); //sama asia kuin yllˆ
	file2.tellg();
	file2.seekg(0, std::ios::beg); */

	char* contents = new char[fileSize +1];

	int pos = fread(
		contents,		//mihin luetaan
		sizeof(char),
		fileSize,		//montako merkki‰ (tavua)
		file2			// mist‰
		);

	contents[pos] = '\0';
	fclose(file2);

	std::cout << contents << std::endl;

	delete[] contents;
}

void cpp_style()
{
	//	std::ofstream file;
	//	std::ifstream file2;
	std::fstream file(
		"teksti.txt",
		//		std::ios::in | std::ios::out | std::ios::trunc); //in = luku, out = kirjotus, trunc = tiedoston tyhjennys 
		std::ios::out | std::ios::app); //std::ios::app jatkaa tiedostoa
	//	file.open("teksti.txt.", std::ios::in | std::ios::out)

	if (!file.is_open())
	{
		std::cout << "failed to open file" << std::endl;
	}

	file << "Hello world" << std::endl;

	file.close();

	std::ifstream file2("teksti.txt", std::ios::in);

	if (!file2.is_open())
	{
		std::cout << "failed to open file" << std::endl;
	}


	std::vector<std::string> lines;
	std::string line;

	while (std::getline(file2, line))
	{
		std::cout << line << std::endl;
	}

	file2.close();

}

/*
voidaan katsoa ja lis‰t‰ uusia drinkkej‰
tallentaa drinkin ainesosat
*/

struct Ingredient
{
	std::string name;
	int amount;
};

struct Drink
{
	std::string name;
	std::vector<Ingredient> ingredients;
};

class DrinkDatabase
{
private:
	std::vector<Drink> drinks;
	std::string filepath;
public:

	DrinkDatabase(const std::string& filepath)
		: filepath(filepath)
	{

	}

	void load()
	{
		std::ifstream file(
			filepath,
			std::ios::in
			);

		std::string line;

		while (std::getline(file, line))
		{
			// alusta 0 => ekaan puolipisteeseen
			int semicolon = line.find(";");
			std::string name = line.substr(0, semicolon);

			int secondSemicolon = line.find(";", semicolon + 1);
			std::string count = line.substr(semicolon + 1, secondSemicolon - (semicolon + 1));

			int n = std::atoi(count.c_str()) * 2; //atoi konverttaa stringin integeriksi

			std::vector<std::string> split(n);

			for (int i = 0; i < n; ++i)
			{
				int start = secondSemicolon + 1;
				secondSemicolon = line.find(";", start);

				split[i] = line.substr(start, secondSemicolon - start);
			}

			Drink drink;
			drink.name = name;

			for (int i = 0; i < n; i += 2)
			{
				Ingredient ingredient;
				ingredient.name = split[i];
				ingredient.amount = std::atoi(split[i + 1].c_str());

				drink.ingredients.push_back(ingredient);
			}

			drinks.push_back(drink);

			/*std::cout << "Name: " << name << std::endl;

			std::cout << "Ingredients: " << std::endl;
			for (int i = 0; i < n; i += 2)
			{
				std::cout << "Name: " << split[i] << ", Count: " << split[i + 1] << std::endl;
			}

			//std::cout << "Name: " << name << std::endl;
			//std::cout << "count: " << count << std::endl;*/
		}

		file.close();
	}

	void save()
	{
		std::ofstream file(
			filepath,
			std::ios::out | std::ios::trunc
			);

		for (auto& drink : drinks)
		{
			file <<
				drink.name << ";" << drink.ingredients.size() << ";";

			for (Ingredient& ing : drink.ingredients)
			{
				file <<
					ing.name << ";" << ing.amount << ";";
			}

			file << std::endl;
		}

		file.close();
	}

	void search(const std::string& drinkName)
	{
		auto it = std::find_if(
			drinks.begin(),		//mist‰
			drinks.end(),		//mihin
			// predikaatti
			[&drinkName](const Drink& drink)
		{
			if (drinkName.size() != drink.name.size()) return false;

			std::equal(
				drinkName.begin(),
				drinkName.end(),
				drink.name.begin(),
				[](unsigned char a, unsigned char b)
			{
				return ::tolower(a) == ::tolower(b);
			}
			);
			return drink.name == drinkName;
		}
		);

		// lˆytyi
		if (it != drinks.end())
		{
			Drink& drink = *it;

			std::cout << drink.name << " loytyy" << std::endl;
		}
	}

	void listDrinks()
	{
		for (Drink& drink : drinks)
		{
			std::cout << drink.name << "\n" << "\t" << "Ainesosat: " << std::endl;

			for (Ingredient& ing : drink.ingredients)
			{
				std::cout << "\t\t" << ing.name << " " << ing.amount << std::endl;
			}
		}
	}

	void interactiveAddDrink()
	{
		std::cin.ignore(); // hyp‰t‰‰n rivinvaihdon yli

		std::cout << "Name: ";
		std::string name;
		std::getline(std::cin, name);

		std::cout << "Ingredient amount: ";
		int count;
		std::cin >> count;

		std::cin.ignore(); // hyp‰t‰‰n rivinvaihdon yli

		Drink drink;
		drink.name = name;

		std::vector<Ingredient> ingredients;

		for (int i = 0; i < count; ++i)
		{
			Ingredient ingredient;
			std::cout << (i + 1) << ". ainesosan nimi: ";
			std::getline(std::cin, ingredient.name);

			std::cout << "maara: ";
			std::cin >> ingredient.amount;

			std::cin.ignore(); // hyp‰t‰‰n rivinvaihdon yli

			drink.ingredients.push_back(ingredient);
		}

		drinks.push_back(drink);
	}
};

DrinkDatabase database("drinkit.txt");

/*
void addDrink()
{
	std::cin.ignore(); // hyp‰t‰‰n rivinvaihdon yli

	std::cout << "Name: ";
	std::string name;
	std::getline(std::cin, name);

	std::cout << "Ingredient amount: ";
	int count;
	std::cin >> count;

	std::vector<Ingredient> ingredients;

	for (int i = 0; i < count; ++i)
	{
		Ingredient ingredient;
		std::cout << (i + 1) << ". ainesosan nimi: ";
		std::cin >> ingredient.name;

		std::cout << "maara: ";
		std::cin >> ingredient.amount;

		ingredients.push_back(ingredient);
	}

	std::ofstream file(
		"drinkit.txt",
		std::ios::out | std::ios::app
		);

	file << name << ";" << count << ";";
	for (auto& ingredient : ingredients)
	{
		file << ingredient.name << ";" << ingredient.amount << ";";
	}
	file.close();
}

void listDrinks()
{

}
*/

int main()
{
	char op = 0;
	bool exit = false;

	database.load();

	do
	{
		op = getchar();

		switch (op)
		{
		case 'q': exit = true; break; //lopettaa
		case 'a': //lis‰t‰
			database.interactiveAddDrink();
			database.save();
			//addDrink();
			break;
		case 'l': //listata
			database.listDrinks();
			break;
		case 's':
			database.search("Tequila Sunrise");
			break;
		}
	} while (!exit);

	return 0;
}

// http://tinyurl.com/filuja