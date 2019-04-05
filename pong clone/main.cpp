#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cmath>
#include "constants.h"

int main()
{
	double ballAngle{ 0.f }; //changed later

	//open SFML window
	sf::RenderWindow window(sf::VideoMode(constants::windowWidth, constants::windowHeight),
		"Pong Clone", sf::Style::Close);

	//cap FPS
	window.setFramerateLimit(60);

	//Ball definition and setup
	sf::CircleShape ball(constants::ballRadius);
	ball.setFillColor(sf::Color::Green);
	ball.setOrigin(sf::Vector2f(constants::ballRadius, constants::ballRadius));
	ball.setPosition(sf::Vector2f(constants::windowWidth / 2, constants::windowHeight / 2));


	//Left paddle definition and setup
	sf::RectangleShape leftPaddle(sf::Vector2f(constants::paddleWidth, constants::paddleHeight));
	leftPaddle.setFillColor(sf::Color::Green);
	leftPaddle.setOrigin(sf::Vector2f(constants::paddleWidth / 2, constants::paddleHeight / 2));
	leftPaddle.setPosition(sf::Vector2f(constants::paddleWidth / 2, constants::windowHeight / 2));


	//Right paddle defintion and set up
	sf::RectangleShape rightPaddle(sf::Vector2f(constants::paddleWidth, constants::paddleHeight));
	rightPaddle.setFillColor(sf::Color::Green);
	rightPaddle.setOrigin(sf::Vector2f(constants::paddleWidth / 2, constants::paddleHeight / 2));
	rightPaddle.setPosition(sf::Vector2f(constants::windowWidth -
		(constants::paddleWidth / 2), constants::windowHeight / 2));

	//game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//closing the screen
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//left paddle up and down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			rightPaddle.setPosition(sf::Vector2f(rightPaddle.getPosition().x,
				rightPaddle.getPosition().y - constants::paddleSpeed));
		if (rightPaddle.getPosition().y - constants::paddleHeight / 2 < 0)
			rightPaddle.setPosition(sf::Vector2f(rightPaddle.getPosition().x,
				0 + constants::paddleHeight / 2));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			rightPaddle.setPosition(sf::Vector2f(rightPaddle.getPosition().x,
				rightPaddle.getPosition().y + constants::paddleSpeed));
		if (rightPaddle.getPosition().y + constants::paddleHeight / 2 > constants::windowHeight)
			rightPaddle.setPosition(sf::Vector2f(rightPaddle.getPosition().x,
				constants::windowHeight - constants::paddleHeight / 2));

		//right paddle up and down no bound checking
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			leftPaddle.setPosition(sf::Vector2f(leftPaddle.getPosition().x,
				leftPaddle.getPosition().y - constants::paddleSpeed));
		if (leftPaddle.getPosition().y - constants::paddleHeight / 2 < 0)
			leftPaddle.setPosition(sf::Vector2f(leftPaddle.getPosition().x,
				0 + constants::paddleHeight / 2));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			leftPaddle.setPosition(sf::Vector2f(leftPaddle.getPosition().x,
				leftPaddle.getPosition().y + constants::paddleSpeed));
		if (leftPaddle.getPosition().y + constants::paddleHeight / 2 > constants::windowHeight)
			leftPaddle.setPosition(sf::Vector2f(leftPaddle.getPosition().x,
				constants::windowHeight - constants::paddleHeight / 2));

		//move the ball
		ball.move(sf::Vector2f(std::cos(ballAngle) * constants::ballSpeed, std::sin(ballAngle) * constants::ballSpeed));

		//ball collision with top and bottom of screen
		if ((ball.getPosition().y - constants::ballRadius <= 0))
		{
			ballAngle = -ballAngle;
			ball.setPosition(ball.getPosition().x, constants::ballRadius + 0.1f);
		}
		if (ball.getPosition().y + constants::ballRadius >= constants::windowHeight)
		{
			ballAngle = -ballAngle;
			ball.setPosition(ball.getPosition().x, constants::windowHeight - constants::ballRadius - 0.1f);
		}

		//if the ball is on the left side of the screen
		if (ball.getPosition().x - constants::ballRadius <= constants::paddleWidth)
		{
			//if the balls y position is between the top and bottom of the left paddle
			if ((ball.getPosition().y < (leftPaddle.getPosition().y + (constants::paddleHeight / 2))) &&
				(ball.getPosition().y > (leftPaddle.getPosition().y - (constants::paddleHeight / 2))))
			{
				if (ball.getPosition().y > leftPaddle.getPosition().y)
					ballAngle = constants::pi - ballAngle + (std::rand() % 20) * constants::pi / 180;
				else
					ballAngle = constants::pi - ballAngle - (std::rand() % 20) * constants::pi / 180;
			}
			//if the balls y position is NOT between the top and bottom of the left paddle
			else
			{
				window.close();
			}
		}

		//if the ball is on the right side of the screen
		if ((ball.getPosition().x + constants::ballRadius) >= (constants::windowWidth - constants::paddleWidth))
		{
			//if the balls y position is between the top and bottom of the right paddle
			if ((ball.getPosition().y < (rightPaddle.getPosition().y + (constants::paddleHeight / 2))) &&
				(ball.getPosition().y > (rightPaddle.getPosition().y - (constants::paddleHeight / 2))))
			{
				if (ball.getPosition().y > rightPaddle.getPosition().y)
					ballAngle = constants::pi - ballAngle + (std::rand() % 20) * constants::pi / 180;
				else
					ballAngle = constants::pi - ballAngle - (std::rand() % 20) * constants::pi / 180;
			}
			//if the balls y position is NOT between the top and bottom of the right paddle
			else
			{
				window.close();
			}
		}

		//clear console
		system("cls");

		//logging console stuff
		std::cout << "Ball pos x: " << ball.getPosition().x << " Ball pos y: " << ball.getPosition().y << std::endl;
		std::cout << "Left paddle y: " << leftPaddle.getPosition().y << std::endl;
		std::cout << "Right paddle y: " << rightPaddle.getPosition().y << std::endl;

		//clearn the screen with a black color
		window.clear(sf::Color::Black);

		//window.draw(...) which items should be drawn
		window.draw(ball);
		window.draw(leftPaddle);
		window.draw(rightPaddle);

		//draws elements to screen
		window.display();
	}

	return 0;
}