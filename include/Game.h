#ifndef GAME_H
#define GAME_H
#include "Menu.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Highscore.h"


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>



class Game {
friend class Grid;
public:
    Game();
    void run();
    bool paused ;
private:
    void proceed(Direction dir);
    void update(const sf::Time& dt);
    void rotate();
    void createTetromino();
    bool isValidMovement(std::array<sf::Vector2i, 4> block);
    bool isOccupied(int x, int y);
    void processEvents();
    void render();
	sf::Clock clock;

	void saveHighScore(std::string score, float name);

    sf::RenderWindow                            mRenderWindow;
    sf::Texture                                 mTexture;
    sf::RectangleShape                          mSeparationLine;
    std::unique_ptr<Tetromino>                  mTetromino;
    std::unique_ptr<Tetromino>                   mPreview;
    std::unique_ptr<Grid>                       mGrid;
    Highscore                                   mHighScore;
    sf::Time                                    mElapsedTime;
    int                                         mID;

};
#endif // GAME_H
