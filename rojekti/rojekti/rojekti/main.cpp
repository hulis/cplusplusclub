#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

class Player{
public:
	sf::RectangleShape paddle;
	sf::Vector2f velocity;
private:
};

bool randomBool(){
	return rand() % 2 == 1;
}

int random(int min, int max)
{
	return min + rand() % (max - min);
}

int main()
{
	srand(time(NULL));

	int32_t width = 720;
	int32_t height = 640;
	int32_t radius = 20;

	sf::RenderWindow window(sf::VideoMode(width, height), "Pong");
	sf::CircleShape shape(radius);
	shape.setFillColor(sf::Color::Green);

	sf::Vector2<float> velocity(0, 0);

	float speed = 0.75f;

	Player player;
	player.paddle = sf::RectangleShape (sf::Vector2f(10.f, 100.f));
	player.paddle.setFillColor(sf::Color(255, 0, 0)); //punainen
	player.velocity = sf::Vector2f(0, 0);

	Player aiPlayer;
	aiPlayer.paddle = sf::RectangleShape(sf::Vector2f(10.0f, 100.f));
	aiPlayer.paddle.setFillColor(sf::Color(0, 0, 255));
	aiPlayer.velocity = sf::Vector2f(0.0f, 0.0f);
	aiPlayer.paddle.setPosition(sf::Vector2f(width - 10.0f, 0.0f));

	sf::Vector2f aiPlayerVelocity;

	const int min_cohension = 0;
	const int max_cohension = 200;
	const int min_frames = 0;
	const int max_frames = 10;

	int current_cohension = 0;
	int current_frame_limit = 0;
	int frames = 0;
	int cohensionDir = 0;

	while (window.isOpen())
	{
		if (frames >= current_frame_limit){
			frames = 0;

			current_cohension = random(
				min_cohension,
				max_cohension
				);

			current_frame_limit = random(
				min_frames,
				max_frames
				);
		}

		if (randomBool())	cohensionDir = 1;
		else				cohensionDir = -1;

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

		sf::Vector2f ballPos = shape.getPosition();
		sf::Vector2f aiPlayerPos = aiPlayer.paddle.getPosition();

		float aicy = aiPlayerPos.y + current_cohension * cohensionDir;

		if (aicy < ballPos.y)
		{
			aiPlayerVelocity.y = 1;
		}

		else
		{
			aiPlayerVelocity.y = -1;
		}

		aiPlayer.paddle.setPosition(
			aiPlayerPos.x,
			aiPlayerPos.y + aiPlayerVelocity.y * speed
			);

		sf::FloatRect playerBounds = player.paddle.getGlobalBounds();
		sf::FloatRect shapeBounds = shape.getGlobalBounds();

		if (playerBounds.intersects(shapeBounds)) {
			velocity.x = 1;

			bool upOrDown = randomBool();

			if (upOrDown)	velocity.y = 1;
			else			velocity.y = -1;
		}

		sf::FloatRect aiBounds = aiPlayer.paddle.getGlobalBounds();

		if (aiBounds.intersects(shapeBounds)){
			velocity.x = -1;
			bool upOrDown = randomBool();

			if (upOrDown)	velocity.y = 1;
			else			velocity.y = -1;
		}
		//alotus
		window.clear();
		window.draw(shape);
		window.draw(player.paddle);
		window.draw(aiPlayer.paddle);

		// loppu
		window.display();

		frames++;
	}

	return 0;
}