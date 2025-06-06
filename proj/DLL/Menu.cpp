#include "Menu.h"


Menu::Menu(float width, float height, const std::string& backgroundPath)
{
	if (!font.loadFromFile("NoctraDrip-OutlineMelt.ttf"))
	{
		//errror xd
	}

	if (!backgroundTexture.loadFromFile(backgroundPath)) 
	{
		
	}
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(
		width / backgroundSprite.getLocalBounds().width,
		height / backgroundSprite.getLocalBounds().height
	);

	std::string texts[MAX_NUMBER_OF_ITEMS] = { "Graj", "Opcje", "Wyniki", "Wyjdz" };

	float frameX = 30.f;
	float frameY = 339.f;
	float frameWidth = 398.f;
	float frameHeight = 257.f;

	float optionSpacing = frameHeight / (MAX_NUMBER_OF_ITEMS + 1);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) 
	{
		menu[i].setFont(font);
		menu[i].setCharacterSize(40);
		menu[i].setString(texts[i]);
		menu[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

		sf::FloatRect bounds = menu[i].getLocalBounds();

		// Pozycja wyśrodkowana poziomo 
		menu[i].setPosition(
			frameX + frameWidth / 2.f - bounds.width / 2.f,
			frameY + optionSpacing * (i + 1) - bounds.height / 2.f
		);
	}
	if (!cursorTexture.loadFromFile("rekawicav3.png")) {
		
		
	}

	// ustaw sprite kursora 
	cursorSprite.setTexture(cursorTexture);
	

	// początkowa pozycja kursora 
	sf::FloatRect firstBounds = menu[0].getGlobalBounds();
	cursorSprite.setPosition(
		firstBounds.left + firstBounds.width ,  
		firstBounds.top 
	);

	selectedItemIndex = 0;
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
	window.draw(cursorSprite);
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);

		sf::FloatRect bounds = menu[selectedItemIndex].getGlobalBounds();
		cursorSprite.setPosition(
			bounds.left + bounds.width + 5.f,
			bounds.top 
		);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);

		sf::FloatRect bounds = menu[selectedItemIndex].getGlobalBounds();
		cursorSprite.setPosition(
			bounds.left + bounds.width + 5.f,
			bounds.top 
		);
	}
}