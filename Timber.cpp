// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <sstream>

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
	VideoMode vm(1366, 768);

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
	spriteBee.setPosition(-100, 0);

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
	spriteCloud1.setPosition(2000, 0);
	spriteCloud2.setPosition(2000, 0);
	spriteCloud3.setPosition(2000, 0);

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

	//Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 30.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Track whether the game is running
	bool pause = true;

	//Draw some texts
	int score = 0;

	Text startText;
	Text scoreText;

	//Choosing a font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//Set the font to our message
	startText.setFont(font);
	scoreText.setFont(font);

	//Assign the messages
	startText.setString("Press Enter to start the game!");
	scoreText.setString("Score = 0");

	//Assign size to those messages
	startText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//Assign colors to them
	startText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	//Position the texts
	FloatRect textrect = startText.getLocalBounds();

	startText.setOrigin(textrect.left + textrect.width / 2.0f,
		textrect.top + textrect.height / 2.0f);
	
	startText.setPosition(1980 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	while (window.isOpen())
	{
		//Handle the player's input
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			pause = false;

			//Reset the score and time
			score = 0;
			timeRemaining = 30;
		}

		/*
		*****************
		Updating the scene
		*****************
		*/

		if (!pause)
		{
			//Randomize the height for the bee
			srand((int)time(0) * 10);
			float beeHeight = (rand() % 500) + 500;

			//Randomize the height for cloud 1
			srand((int)time(0) * 10);
			float cloud1Height = (rand() % 50) + 10;

			//Randomize the height for cloud 2
			srand((int)time(0) * 20);
			float cloud2Height = (rand() % 150) + 50;

			//Randomize the height for cloud 3
			srand((int)time(0) * 30);
			float cloud3Height = (rand() % 250) + 50;

			//Measure the time
			Time dt = clock.restart();

			//Subtract from the amount of time remaining;
			timeRemaining -= dt.asSeconds();
			//Resize the time bar based on the remaining time
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining,
							timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				//Pause the game
				pause = true;

				//Change the message shown to the player
				startText.setString("Out of Time!!!");

				//Reposition the text based on the new size
				FloatRect textrect = startText.getLocalBounds();

				startText.setOrigin(textrect.left + textrect.width / 2.0f,
					textrect.top + textrect.height / 2.0f);

				startText.setPosition(1980 / 2.0f, 1080 / 2.0f);
			}

			//Setup the bee	
			if (!beeActive)
			{
				//How fast is the bee 
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;
				spriteBee.setPosition(2000, beeHeight);
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

				//Reset cloud 1 position when pressed enter
				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					spriteBee.setPosition(-300, beeHeight);
				}
			}

			//Manages the clouds
			//Cloud1
			if (!cloud1Active)
			{
				//How fast is the first cloud 
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200) + 10;
				spriteCloud1.setPosition(-300, cloud1Height);
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
				
				//Reset cloud 1 position when pressed enter
				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					spriteCloud1.setPosition(-300, cloud1Height);
				}
			}

			//Cloud2
			if (!cloud2Active)
			{
				//How fast is the second cloud 
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200) + 10;
				spriteCloud2.setPosition(-300, cloud2Height);
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

				//Reset cloud 2 position when pressed enter
				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					spriteCloud2.setPosition(-300, cloud2Height);
				}
			}

			//Cloud3
			if (!cloud3Active)
			{
				//How fast is the third cloud 
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200) + 10;
				spriteCloud3.setPosition(-200, cloud3Height);
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

				//Reset cloud 3 position when pressed enter
				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					spriteCloud3.setPosition(-300, cloud3Height);
				}
			}

			//Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

		}// End if (!paused)

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

		//Draw the score
		window.draw(scoreText);

		//Draw the time bar
		window.draw(timeBar);

		if (pause)
		{
			//Draw the starting Text
			window.draw(startText);
		}

		//Show everything that we just drew
		window.display();
	}

	return 0;
}
