#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <Player.h>
#include <Input.h>
#include <Debug.h>



int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a sprite to display
	sf::Texture sprite_sheet;
	if (!sprite_sheet.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture mouse_texture;
	if (!mouse_texture.loadFromFile("assets\\mouse.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup a mouse Sprite
	sf::Sprite mouse;
	mouse.setTexture(mouse_texture);
	mouse.setOrigin(mouse.getGlobalBounds().width / 2, mouse.getGlobalBounds().height / 2);

	//Setup mouse AABB
	c2AABB aabb_mouse;
	aabb_mouse.min = c2V(mouse.getPosition().x, mouse.getPosition().y);
	aabb_mouse.max = c2V(mouse.getGlobalBounds().width, mouse.getGlobalBounds().width);

	//Setup mouse Circle
	c2Circle circle_mouse;
	circle_mouse.p = c2V(mouse.getPosition().x, mouse.getPosition().y);
	circle_mouse.r = mouse.getGlobalBounds().height/2;

	//Setup mouse Ray
	c2Ray ray_mouse;
	//Setup mouse Capsule
	c2Capsule capsule_mouse;
	//Setup mouse Polygon
	c2Poly polygon_mouse;

	// Setup Players Default Animated Sprite
	AnimatedSprite animated_sprite(sprite_sheet);
	animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));


	// Setup Players AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	aabb_player.max = c2V(animated_sprite.getGlobalBounds().width / animated_sprite.getFrames().size(), 
		animated_sprite.getGlobalBounds().height / animated_sprite.getFrames().size());

	//Setup Players Circle
	c2Circle circle_player;
	circle_player.p = c2V(animated_sprite.getPosition().x + animated_sprite.getGlobalBounds().height / 2,
						  animated_sprite.getPosition().y + animated_sprite.getGlobalBounds().width / 2);
	circle_player.r = animated_sprite.getGlobalBounds().height / 2;
	//Setup Players Ray
	c2Ray ray_player;
	//Setup Players Capsule
	c2Capsule capsule_player;
	//Setup Players Polygon
	c2Poly polygon_player;

	// Setup the Player
	Player player(animated_sprite);
	Input input;

	// Collision result
	int result = 0;
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		mouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		// Update mouse AABB
		aabb_mouse.min = c2V(mouse.getPosition().x, mouse.getPosition().y);
		aabb_mouse.max = c2V(mouse.getGlobalBounds().width, mouse.getGlobalBounds().width);

		// update mouse circle
		circle_mouse.p = c2V(mouse.getPosition().x, mouse.getPosition().y);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					input.setCurrent(Input::Action::LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					input.setCurrent(Input::Action::RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					input.setCurrent(Input::Action::UP);
				}
				break;
			default:
				input.setCurrent(Input::Action::IDLE);
				break;
			}
		}

		// Handle input to Player
		player.handleInput(input);

		// Update the Player
		player.update();

		// Check for collisions

		
		

		//result = c2AABBtoAABB(aabb_mouse, aabb_player);
		//result = c2CircletoAABB(circle_mouse, aabb_player);

		result = c2CircletoCircle(circle_mouse, circle_player);
		std::cout << ((result != 0) ? ("Collision") : "") << std::endl;
		if (result){
			player.getAnimatedSprite().setColor(sf::Color(255,0,0));
		}
		else {
			player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());
		window.draw(mouse);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};