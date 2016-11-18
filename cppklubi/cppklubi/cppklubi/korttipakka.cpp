#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // random_shuffle
#include <time.h> // time
#include <stdlib.h> // srand

enum Suit : int //kaikki enumeiden arvot ovat nyt int tyyppisi‰
{
	SuitClub,
	SuitHeart,
	SuitDiamond,
	SuitSpade
};

// forward declaration
std::string suitToString(Suit suit);


struct Card
{
	int rank;
	Suit suit;

	friend std::ostream& operator<<(std::ostream& out, const Card& c)
	{
		out << c.rank << " of " << suitToString(c.suit);
		return out;
	}
};

// otetaan suit enum arvo sis‰‰n ja palautetaan se stringin‰
std::string suitToString(Suit suit)
{
	switch (suit)
	{
	case Suit::SuitClub:
		return "Club";
	case Suit::SuitDiamond:
		return "Diamond";
	case Suit::SuitHeart:
		return "Heart";
	case Suit::SuitSpade:
		return "Spade";
	default:
		return "Not a suit";
	}
}

class Deck
{
private:
	std::vector<Card> cards;

public:
	Deck()
	{
		const int numCards = 13; //const tekee muuttujasta vakion. arvoa ei en‰‰ voi muuttaa
		const int numSuits = 4;

		cards.reserve(numCards * numSuits); //varataan vektoriin tilaa 52 kortille

		for (int suit = 0; suit < numSuits; ++suit)
		{
			for (int rank = 0; rank < numCards; ++rank)
			{
				Card card;
				card.rank = rank + 1;
				card.suit = Suit(suit);

				cards.push_back(card);
			}
		}
	}

	void print()
	{
		const int cardsPerRow = 3;
		int cardCounter = 0;
		for (auto& card : cards) //menn‰‰n yksi elementti eteenp‰in vektorista for loopissa
		{
			std::string suit = suitToString(card.suit); //muutetaan kortin maa enum arvo stringiksi
			int rank = card.rank;

			std::cout << rank << " of " << suit << "\t"; // \t lis‰‰ tabulaattorin rivin loppuun
			++cardCounter;

			if (cardCounter % cardsPerRow == 0)
			{
				std::cout << std::endl;
			}
		}
	}
	
	void shuffle() //metodi luokan sis‰ss‰ ja funktio luokan ulkopuolella
	{
		//let the magic happen
		std::random_shuffle(
			cards.begin(), //mist‰
			cards.end() //mihin
		);
	}

	Card next()
	{
		Card card = cards.back();
		// poistetaan otettu kortti
		cards.pop_back();
		return card;
	}

	bool isInDeck(Card card)
	{
		// taikavoimia
		// std::vector<Card>::iterator
		auto it = std::find_if(
			cards.begin(), // mist‰
			cards.end(), // mihin
			[&card](const Card& other) {	// t‰m‰ on funktio
			return card.rank == other.rank
				&& card.suit == other.suit;
		}
		);
		return it != cards.end();
	}

	bool hasCards()
	{
		return cards.empty();
	}
};

struct Player
{
	Card first;
	Card second;
};

int main()
{
	srand(time(NULL)); //seed
	Deck deck;
	deck.print();
	
	deck.shuffle();

	const int playerCount = 4;

	Player players[playerCount];

	//const int pocketCards = 2;
	for (int player = 0; player < playerCount; ++player)
	{
		//Card card = deck.next();
		players[player].first = deck.next();
		players[player].second = deck.next();
	}

	Card flop1 = deck.next();
	Card flop2 = deck.next();
	Card flop3 = deck.next();
	Card turn = deck.next();
	Card river = deck.next();

	std::cout << std::endl << "FLOP == " << flop1 << " " << flop2 << " " << flop3 << std::endl;
	std::cout << "TURN == " << turn << std::endl;
	std::cout << "RIVER ==" << river << std::endl;

	//std::cout << std::endl << "----- shuffle -----" << std::endl;

	deck.print();
	system("pause");
	return 0;
}