

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
	
	int currentBoundaryTest = 0;


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



	sf::Font m_font;
	if (!m_font.loadFromFile("assets\\ARLRDBD.ttf"))
	{
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}
	sf::Text m_text[2];
	for (int i = 0; i < 2; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setCharacterSize(15);
		m_text[i].setFillColor(sf::Color::White);
		m_text[i].setPosition(50 + (i * 400), 500);
	}
	m_text[0].setString("Press Up To Cycle Boundary Tests ");


	// Setup a mouse Sprite
	sf::Sprite mouse;
	mouse.setTexture(mouse_texture);


	
	//mouse.setOrigin(mouse.getGlobalBounds().width / 2, mouse.getGlobalBounds().height / 2);

	//Setup mouse AABB
	c2AABB aabb_mouse;
	aabb_mouse.min = c2V(mouse.getPosition().x, mouse.getPosition().y);
	aabb_mouse.max = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y + mouse.getGlobalBounds().height);

	//Setup mouse Circle
	c2Circle circle_mouse;
	circle_mouse.p = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width / 2.0, mouse.getPosition().y + mouse.getGlobalBounds().height / 2.0);
	circle_mouse.r = mouse.getGlobalBounds().height/2.0;

	//Setup mouse Ray
	c2Ray ray_mouse;
	ray_mouse.p = c2V(mouse.getPosition().x, mouse.getPosition().y);
	ray_mouse.d = c2Norm(c2V(1,1));
	ray_mouse.t = sqrt((mouse.getGlobalBounds().width * mouse.getGlobalBounds().width)+(mouse.getGlobalBounds().height * mouse.getGlobalBounds().height));
	//Setup mouse Capsule
	c2Capsule capsule_mouse;
	capsule_mouse.a = c2V(mouse.getPosition().x, mouse.getPosition().y + mouse.getGlobalBounds().height /2.0f);
	capsule_mouse.b = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y + mouse.getGlobalBounds().height / 2.0f);
	capsule_mouse.r = mouse.getGlobalBounds().height / 2.0;
	//Setup mouse Polygon
	c2Poly * polygon_mouse = new c2Poly;
	polygon_mouse->count = 4;
	polygon_mouse->verts[0] = c2V(mouse.getPosition().x,mouse.getPosition().y );
	polygon_mouse->verts[1] = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y);
	polygon_mouse->verts[2] = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y + mouse.getGlobalBounds().height);
	polygon_mouse->verts[3] = c2V(mouse.getPosition().x, mouse.getPosition().y + mouse.getGlobalBounds().height);
	













	// Setup Players Default Animated Sprite
	AnimatedSprite animated_sprite(sprite_sheet);




	animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	animated_sprite.setPosition(400,300);

	

	// Setup Players AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	aabb_player.max = c2V(animated_sprite.getPosition().x + animated_sprite.getGlobalBounds().width / animated_sprite.getFrames().size(), animated_sprite.getPosition().y + animated_sprite.getGlobalBounds().height / animated_sprite.getFrames().size());

	//Setup Players Circle
	c2Circle circle_player;
	circle_player.p = c2V(animated_sprite.getPosition().x + ((animated_sprite.getGlobalBounds().width / 2.0) / (animated_sprite.getFrames().size())),
						  animated_sprite.getPosition().y + ((animated_sprite.getGlobalBounds().height / 2.0) / (animated_sprite.getFrames().size())));
	
	
	circle_player.r = (animated_sprite.getGlobalBounds().height / 2.0) / (animated_sprite.getFrames().size());
	//Setup Players Ray
	c2Ray ray_player;
	ray_player.p = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	ray_player.d = c2Norm(c2V(1, 1));
	ray_player.t = sqrt((animated_sprite.getGlobalBounds().width / (animated_sprite.getFrames().size())* animated_sprite.getGlobalBounds().width / (animated_sprite.getFrames().size())) + (animated_sprite.getGlobalBounds().height / (animated_sprite.getFrames().size())* animated_sprite.getGlobalBounds().height / (animated_sprite.getFrames().size())));

	//Setup Players Capsule
	c2Capsule capsule_player;
	capsule_player.a = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y + ((animated_sprite.getGlobalBounds().height/2.0) / (animated_sprite.getFrames().size())));
	capsule_player.b = c2V(animated_sprite.getPosition().x + (animated_sprite.getGlobalBounds().width / (animated_sprite.getFrames().size())), animated_sprite.getPosition().y + ((animated_sprite.getGlobalBounds().height/2.0) / (animated_sprite.getFrames().size())));
	capsule_player.r = (animated_sprite.getGlobalBounds().height / 2.0) / (animated_sprite.getFrames().size());
	//Setup Players Polygon
	c2Poly * polygon_player = new c2Poly;
	polygon_player->count = 4;
	polygon_player->verts[0] = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	polygon_player->verts[1] = c2V(animated_sprite.getPosition().x + animated_sprite.getGlobalBounds().width / (animated_sprite.getFrames().size()), animated_sprite.getPosition().y);
	polygon_player->verts[2] = c2V(animated_sprite.getPosition().x + animated_sprite.getGlobalBounds().width / (animated_sprite.getFrames().size()), animated_sprite.getPosition().y + animated_sprite.getGlobalBounds().height / (animated_sprite.getFrames().size()));
	polygon_player->verts[3] = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y + animated_sprite.getGlobalBounds().height / (animated_sprite.getFrames().size()));

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
		aabb_mouse.max = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y +mouse.getGlobalBounds().width);

		// update mouse circle
		circle_mouse.p = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width / 2.0, mouse.getPosition().y + mouse.getGlobalBounds().height / 2.0);

		//update mouse capsule
		capsule_mouse.a = c2V(mouse.getPosition().x, mouse.getPosition().y + mouse.getGlobalBounds().height / 2.0f);
		capsule_mouse.b = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y + mouse.getGlobalBounds().height / 2.0f);
	
		// update mouse polygon
		polygon_mouse->verts[0] = c2V(mouse.getPosition().x, mouse.getPosition().y);
		polygon_mouse->verts[1] = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y);
		polygon_mouse->verts[2] = c2V(mouse.getPosition().x + mouse.getGlobalBounds().width, mouse.getPosition().y + mouse.getGlobalBounds().height);
		polygon_mouse->verts[3] = c2V(mouse.getPosition().x, mouse.getPosition().y + mouse.getGlobalBounds().height);
		
		// update mouse ray
		ray_mouse.p = c2V(mouse.getPosition().x, mouse.getPosition().y);
		ray_mouse.d = c2Norm(c2V(1, 1));
		ray_mouse.t = sqrt((mouse.getGlobalBounds().width * mouse.getGlobalBounds().width) + (mouse.getGlobalBounds().height * mouse.getGlobalBounds().height));

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
					currentBoundaryTest++;
					if (currentBoundaryTest == 12)
					{
						currentBoundaryTest = 0;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					
					
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


		
		

		c2Raycast cast;

		
		c2CastRay(ray_mouse, &aabb_player, NULL, C2_AABB, &cast);
		


		switch (currentBoundaryTest)
		{
		case 0:
			result = c2AABBtoAABB(aabb_mouse, aabb_player);
			m_text[1].setString("Current Test: AABB to AABB");
			break;
		case 1:
			result = c2AABBtoCapsule(aabb_mouse, capsule_player);
			m_text[1].setString("Current Test: AABB to CAPSULE");

			break;
		case 2:
			result = c2AABBtoPoly(aabb_mouse, polygon_player, NULL);
			m_text[1].setString("Current Test: AABB to POLYGON");

			break;
		case 3:
			result = c2RaytoAABB(ray_player, aabb_mouse, &cast);
			m_text[1].setString("Current Test: AABB to RAY");

			break;
		case 4:
			result = c2CircletoAABB(circle_mouse, aabb_player);
			m_text[1].setString("Current Test: CIRCLE to AABB");

			break;
		case 5:
			result = c2CircletoCircle(circle_mouse, circle_player);
			m_text[1].setString("Current Test: CIRCLE to CIRCLE");

			break;
		case 6:
			result = c2RaytoCircle(ray_player, circle_mouse, & cast);
			m_text[1].setString("Current Test: CIRCLE to RAY");

			break;
		case 7:
			result = c2CircletoPoly(circle_mouse, polygon_player, NULL);
			m_text[1].setString("Current Test: CIRCLE to POLYGON");

			break;
		case 8:
			result = c2RaytoPoly(ray_mouse, polygon_player, NULL, &cast);
			m_text[1].setString("Current Test: RAY to POLYGON");

			break;
		case 9:
			result = c2RaytoCapsule(ray_mouse, capsule_player, &cast);
			m_text[1].setString("Current Test: RAY to CAPSULE");

			break;
		case 10:
			result = c2RaytoCircle (ray_mouse, circle_player, &cast);
			m_text[1].setString("Current Test: RAY to CIRCLE");

			break;
		case 11:
			result = c2RaytoAABB(ray_mouse, aabb_player, &cast);
			m_text[1].setString("Current Test: RAY to AABB");

			break;
		default:
			break;
		}




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

		for (int i = 0; i < 2; i++)
		{
			window.draw(m_text[i]);
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};


