#define _CRT_SECURE_NO_WARNINGS
#include <fstream> // lukee ja kirjottaa
#include <ostream> // kirjottaa
#include <istream> // lukee
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
voidaan katsoa ja lis‰t‰ uusia drinkkej‰
tallennetaa drinkin ainesosat
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

			int n = std::atoi(count.c_str()) * 2;

			std::vector<std::string> split(n);

			for (int i = 0; i < n; ++i)
			{
				int start = secondSemicolon + 1;
				secondSemicolon = line.find(";", start);
				/* pituus              */
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
		}

		file.close();
	}

	void save()
	{
		std::ofstream file(
			filepath,
			std::ios::out | std::ios::trunc
			);

		for (Drink& drink : drinks)
		{
			file <<
				drink.name << ";" <<
				drink.ingredients.size() << ";";

			for (Ingredient& ing : drink.ingredients)
			{
				file <<
					ing.name << ";" <<
					ing.amount << ";";
			}

			file << std::endl;
		}

		file.close();
	}

	void search(const std::string& drinkName)
	{
		auto it = std::find_if(
			drinks.begin(), // mist‰
			drinks.end(),   // mihin
			// predikaatti
			[&drinkName](const Drink& drink)
		{
			return drink.name == drinkName;
		}
		);

		// lˆytyi
		if (it != drinks.end())
		{
			Drink& drink = *it;
			std::cout << drink.name << " lˆytyy" << std::endl;
		}
	}

	void listDrinks()
	{
		for (Drink& drink : drinks)
		{
			std::cout <<
				drink.name << "\n" <<
				"\t" << "Ainesosat:" << std::endl;

			for (Ingredient& ing : drink.ingredients)
			{
				std::cout <<
					"\t\t" << ing.name << " "
					<< ing.amount << std::endl;
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
			// lopettaa
		case 'q': exit = true; break;
		case 'a': // lis‰t‰
			database.interactiveAddDrink();
			database.save();
			break;
		case 'l': // listata 
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
//asdf