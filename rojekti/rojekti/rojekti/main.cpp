#include <SFML/Graphics.hpp>
#include <stdint.h>

class Player{
public:
	sf::RectangleShape paddle;
	sf::Vector2f velocity;
private:
};

int main()
{
	int32_t width = 720;
	int32_t height = 640;
	int32_t radius = 20;

	sf::RenderWindow window(sf::VideoMode(width, height), "Pong");
	sf::CircleShape shape(radius);
	shape.setFillColor(sf::Color::Green);

	sf::Vector2<float> velocity(0, 0);

	float speed = 0.5f;

	Player player;
	player.paddle = sf::RectangleShape (sf::Vector2f(10.f, 100.f));
	player.paddle.setFillColor(sf::Color(255, 0, 0)); //punainen
	player.velocity = sf::Vector2f(0, 0);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		const sf::Vector2<float>& position = shape.getPosition();

		if (position.x <= 0) velocity.x = 1;
		if (position.x + radius * 2 >= width) velocity.x = -1;
		if (position.y <= 0) velocity.y = 1;
		if (position.y + radius * 2 >= height) velocity.y = -1;

		player.velocity = sf::Vector2f(0, 0); //ei liikuta

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player.velocity.y = -1; //ylöspäin
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player.velocity.y = 1; //alaspäin
		// TODO jos joku haluaa ni x suunnassa

		const sf::Vector2f& playerPos = player.paddle.getPosition();

		if (playerPos.y < 0) player.paddle.setPosition(
			playerPos.x + player.velocity.x * speed,
			0);
		else if (playerPos.y > height - 100) player.paddle.setPosition(
			playerPos.x + player.velocity.x * speed,
			height - 100); // <---- tuohon pitää saada paddle korkeus

		player.paddle.setPosition(
			playerPos.x + player.velocity.x * speed,
			playerPos.y + player.velocity.y * speed
			);

		shape.setPosition(
			position.x + velocity.x * speed,
			position.y + velocity.y * speed
			);

		window.clear();
		window.draw(shape);
		window.draw(player.paddle);
		window.display();
	}

	return 0;
}