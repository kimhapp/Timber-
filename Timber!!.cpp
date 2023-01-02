// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <sstream>

// Make code easier to type with "using namespace"
using namespace sf;

//Declearing functions
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite spriteBranch[NUM_BRANCHES];

//Where is the player/branch?
//Left or Right?
enum class sides { LEFT, RIGHT, NONE};
sides branchPosition[NUM_BRANCHES];

int main()
{
	/*
	//Create video mode object if 1980 x 1080
	VideoMode vm(1980, 1080);
	//Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	*/

	//Create video mode obeject if lower res
	VideoMode vm(1360, 768);

	//Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	View view(sf::FloatRect(0, 0, 1980, 1080));
	window.setView(view);

	//Create a bg sprite
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
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

	//Create 3 cloud sprites from 1 texture
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	const int NUM_CLOUD = 3;
	Sprite spriteCloud[NUM_CLOUD];
	for (int sC = 0; sC < NUM_CLOUD; sC++)
	{
		spriteCloud[sC].setTexture(textureCloud);
		spriteCloud[sC].setPosition(2000, 0);
	}

	//Are the clouds moving?
	bool cloudActive[NUM_CLOUD] = {false, false, false};

	//How fast can the clouds move;
	float cloudSpeed[NUM_CLOUD] = { 0.0f, 0.0f, 0.0f };

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
	Text Text[2];

	//Choosing a font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	for (int txt = 0; txt < 2; txt++)
	{
		//Set up font for our Text
		Text[txt].setFont(font);

		//Assign colors to them
		Text[txt].setFillColor(Color::White);
	}
	//Assign the messages
	Text[0].setString("Press Enter to start the game!");
	Text[1].setString("Score = 0");

	//Assign size to those messages
	Text[0].setCharacterSize(75);
	Text[1].setCharacterSize(100);

	//Position the texts
	FloatRect textrect = Text[0].getLocalBounds();

	Text[0].setOrigin(textrect.left + textrect.width / 2.0f,
		textrect.top + textrect.height / 2.0f);

	Text[0].setPosition(1980 / 2.0f, 1080 / 2.0f);

	Text[1].setPosition(20, 20);

	//Prepare 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	for (int tB = 0; tB < NUM_BRANCHES; tB++)
	{
		spriteBranch[tB].setTexture(textureBranch);
		spriteBranch[tB].setPosition(-2000, -2000);

		//Set the sprite's position to dead center
		//We can then spin it around without changing its position
		spriteBranch[tB].setOrigin(220, 20);
	}

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);

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

			beeActive = false;

			cloudActive[0] = false;
			cloudActive[1] = false;
			cloudActive[2] = false;

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
				Text[0].setString("Out of Time!!!");

				//Reposition the text based on the new size
				FloatRect textrect = Text[0].getLocalBounds();

				Text[0].setOrigin(textrect.left + textrect.width / 2.0f,
					textrect.top + textrect.height / 2.0f);

				Text[0].setPosition(1980 / 2.0f, 1080 / 2.0f);
			}

			//Setup the bee	
			if (!beeActive)
			{
				//Randomize the height for the bee
				srand((int)time(0) * 10);
				float beeHeight = (rand() % 500) + 500;

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
				if (spriteBee.getPosition().x < 0)
				{
					//Set it up ready to be a whole new bee next frame
					beeActive = false;
				}
			}

			//Manages the clouds
			float cloudHeight[3] = { 0.0f, 0.0f, 0.0f };
			for (int r = 0; r < NUM_CLOUD; r++)
			{
				if (!cloudActive[r])
				{
					//Randomize the height for all clouds
					srand((int)time(0) * ((r + 1) * 10));
					cloudHeight [r] = (rand() % ((r + 1) * 50)) + ((r + 1) * 50);

					//How fast is the cloud 
					srand((int)time(0) * 10);
					cloudSpeed[r] = ((rand() % 200) + (r * 5) * 10);
					spriteCloud[r].setPosition(-300, cloudHeight[r]);
					cloudActive[r] = true;
				}

				else
					//Move the cloud
				{
					spriteCloud[r].setPosition(
						spriteCloud[r].getPosition().x + (cloudSpeed[r] * dt.asSeconds()),
						spriteCloud[r].getPosition().y);

					//Has it reached the edge of the screen yet?
					if (spriteCloud[r].getPosition().x > 2000)
					{
						//Set it up ready to be a whole new cloud next frame
						cloudActive[r] = false;
					}
				}
			}

			//Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			Text[1].setString(ss.str());

			//Update the branch sprites
			for (int p = 0; p < NUM_BRANCHES; p++)
			{
				float branchHeight = p * 150;

				if (branchPosition[p] == sides::LEFT)
				{
					//Move the sprite to the leftside
					spriteBranch[p].setPosition(610, branchHeight);

					//Flip the sprite around
					spriteBranch[p].setRotation(180);
				}
				else if (branchPosition[p] == sides::RIGHT)
				{
					//Move the sprite to the right side
					spriteBranch[p].setPosition(1330, branchHeight);

					//Flip the sprite around
					spriteBranch[p].setRotation(0);
				}
				else
				{
					//Hide the branch
					spriteBranch[p].setPosition(3000, branchHeight);
				}
			}

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
		for (int dC = 0; dC < NUM_CLOUD; dC++)
		{
			window.draw(spriteCloud[dC]);
		}

		//Draw the branches
		for (int dB = 0; dB < NUM_BRANCHES; dB++)
		{
			window.draw(spriteBranch[dB]);
		}

		//Draw the tree
		window.draw(spriteTree);

		//Draw the bee
		window.draw(spriteBee);

		//Draw the score
		window.draw(Text[1]);

		//Draw the time bar
		window.draw(timeBar);

		if (pause)
		{
			//Draw the starting Text
			window.draw(Text[0]);
		}

		//Show everything that we just drew
		window.display();
	}
}

//Function Definition
void updateBranches(int seed)
{
	//Move all the branches down one place
	for (int uB = NUM_BRANCHES - 1; uB > 0; uB--)
	{
		branchPosition[uB] = branchPosition[uB - 1];
	}

	//Spawn the new branch at position 0
	//LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int rB = (rand() % 5);

	switch (rB)
	{
	case 0:
		branchPosition[0] = sides::LEFT;
		break;
	case 1:
		branchPosition[0] = sides::RIGHT;
		break;
	default:
		branchPosition[0] = sides::NONE;
		break;
	}
}