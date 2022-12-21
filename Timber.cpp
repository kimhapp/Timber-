// Include important C++ libraries here
#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
	/*
	//Create video mode object if 1980 x 1080
	VideoMode vm(1980, 1080);

	//Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	*/

	//Create video mode obeject if lower res
	VideoMode vm(1360, 1080);

	//Create and open a window for the game
	RenderWindow window(vm, "Timber!!!");
	View view(sf::FloatRect(0, 0, 1980, 1080));
	window.setView(view);

	//Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	//Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	//Create a sprite
	Sprite spriteBackground;

	//Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	//Set the sprite to cover screen
	spriteBackground.setPosition(0, 0);

	//Create a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	//Create a bee sprite
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 0);

	//Is the bee currently moving?
	bool beeActive = false;

	//How fast can the bee can fly
	float beeSpeed = 0.0f;

	//Create 3 cloud sprite from 1 texture
	Texture textureCloud;

	//Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");

	//3 new sprites with the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	//Position the clouds at a different height
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	//Are the clouds moving?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	//How fast can the clouds move;
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//variable to control time itself
	Clock clock;
	
	while (window.isOpen())
	{
		//Handle the player's input
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		*****************
		Updating the scene
		*****************
		*/
		Time dt = clock.restart();

		//Setup the bee	
		if (!beeActive)
		{
			//How fast is the bee 
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			//How high is the bee
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500; 
			spriteBee.setPosition(2000, height);
			beeActive = true;
		}
		else
		//Move the bee
		{
			spriteBee.setPosition(
				spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
				spriteBee.getPosition().y);

			//Has the bee reached the left-hand edge of the scree yet
			if (spriteBee.getPosition().x < -100)
			{
				//Set it up ready to be a whole new bee next frame
				beeActive = false;
			}
		}

		//Manages the clouds
		//Cloud1
		if (!cloud1Active)
		{
			//How fast is the first cloud 
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);

			//How high is the first cloud
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;
		}
		else
		//Move the first cloud
		{
			spriteCloud1.setPosition(
				spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
				spriteCloud1.getPosition().y);

			//Has the first cloud reached the left-hand edge of the screen yet?
			if (spriteCloud1.getPosition().x > 1920)
			{
				//Set it up ready to be a whole new cloud next frame
				cloud1Active = false;
			}
		}

		//Cloud2
		if (!cloud2Active)
		{
			//How fast is the second cloud 
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);

			//How high is the second cloud
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(-200, height);
			cloud2Active = true;
		}
		else
			//Move the second cloud
		{
			spriteCloud2.setPosition(
				spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
				spriteCloud2.getPosition().y);

			//Has the second cloud reached the left-hand edge of the screen yet?
			if (spriteCloud2.getPosition().x > 1920)
			{
				//Set it up ready to be a whole new cloud next frame
				cloud2Active = false;
			}
		}

		//Cloud3
		if (!cloud3Active)
		{
			//How fast is the third cloud 
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);

			//How high is the third cloud
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(-200, height);
			cloud3Active = true;
		}
		else
			//Move the third cloud
		{
			spriteCloud3.setPosition(
				spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
				spriteCloud3.getPosition().y);

			//Has the third cloud reached the left-hand edge of the screen yet?
			if (spriteCloud3.getPosition().x > 1920)
			{
				//Set it up ready to be a whole new cloud next frame
				cloud3Active = false;
			}
		}


                /*
		**************
		Draw the scene
		**************
		*/
		
		//Clear everything from the last frame
		window.clear();

		//Draw the game scene here
		window.draw(spriteBackground);

		//Draw the clouds here
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		//Draw the tree
		window.draw(spriteTree);

		//Draw the bee
		window.draw(spriteBee);

		//Show everything that we just drew
		window.display();
	}

	return 0;
}
