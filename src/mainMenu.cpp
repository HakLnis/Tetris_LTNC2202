
#include "mainMenu.h"

/* Descr: Displaying Main menu window
** Param: Window
** Retval: Response (action) on users event  */
Menu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

	// Load menu image from file
	sf::Texture image;
	image.loadFromFile("menu.png");
	sf::Sprite sprite;
	sprite.setTexture(image);

	//Setup clickable regions

	// "Start game menu" button coordinates
	MenuItem playButton;
	playButton.rect.top= 275;
	playButton.rect.height = 58;
	playButton.rect.left = 360;
	playButton.rect.width = 395;
	playButton.action = Play;

	// "High Score menu" button coordinates
	MenuItem highScoreButton;
	highScoreButton.rect.top= 345;
	highScoreButton.rect.height = 69;
	highScoreButton.rect.left = 360;
	highScoreButton.rect.width = 395;
	highScoreButton.action = HighScores;

	// "Help menu" button coordinates
	MenuItem helpButton;
	helpButton.rect.top= 415;
	helpButton.rect.height = 69;
	helpButton.rect.left = 360;
	helpButton.rect.width = 395;
	helpButton.action = Help;

	// "Exit game" button coordinates
	MenuItem exitButton;
	exitButton.rect.top = 485;
	exitButton.rect.height = 69;
	exitButton.rect.left = 360;
	exitButton.rect.width = 395;
	exitButton.action = Exit;

	// Putting new items to list
	_menuItems.push_back(playButton);
	_menuItems.push_back(helpButton);
	_menuItems.push_back(highScoreButton);
	_menuItems.push_back(exitButton);

	// Draw and display window
	window.draw(sprite);
	window.display();

	return Menu::GetMenuResponse(window);
}
