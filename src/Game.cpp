#include "Game.h"
#include "Utils.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

Game::Game() : mRenderWindow{sf::VideoMode{280, 324 }, "Tetris", sf::Style::Default},
mTexture(), mSeparationLine(), mTetromino(nullptr), mPreview(nullptr), mGrid(),
mHighScore(), mElapsedTime(sf::Time::Zero), mID(getRandomNumber(7)){

    mSeparationLine.setSize(sf::Vector2f{1.f, 18.f * 18.f});
    mSeparationLine.setPosition(sf::Vector2f{10.f * 18.f, 0});
    mSeparationLine.setFillColor(sf::Color::Red);
    if(!mTexture.loadFromFile("Blocks.png")){
        std::cout << "Game::Game() - could not load mTexture\n";
    };
    mGrid = std::make_unique<Grid>(sf::Vector2i{10, 18}, *this);
    createTetromino();
}


void Game::run() {
    sf::Clock clock;
    sf::Time deltaTime{sf::Time::Zero};
    while(mRenderWindow.isOpen()){
        sf::Time trigger{sf::seconds(85.f / (85.f + (mHighScore.getLevel() * (mHighScore.getLevel() * 5.f))))};
        deltaTime = clock.restart();
        mElapsedTime += deltaTime;
        processEvents();
        if(paused == false){
        update(deltaTime);
        }
        if(mElapsedTime > trigger) {
            mElapsedTime = sf::Time::Zero;
            proceed(Direction::Down);
        }
        render();

    }
}

void Game::update(const sf::Time &dt) {
    mGrid->update(dt);
    mHighScore.update(dt);
    if(!mTetromino) {
        if(mGrid->isToRemoveBlocks()){
            return;
        }
        createTetromino();
    }
}

void Game::rotate() {
    if(!mTetromino) return;
    mTetromino->rotate();
    if(!isValidMovement(mTetromino->getBlockPositions())){
        mTetromino->revertState();
    }
}

void Game::processEvents() {
    sf::Event e;
    while (mRenderWindow.pollEvent(e)) {
        if (e.type == sf::Event::Closed) mRenderWindow.close();
        else if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Down) {
                proceed(Direction::SoftDown);
            } else if (e.key.code == sf::Keyboard::Right) {
                proceed(Direction::Right);
            } else if (e.key.code == sf::Keyboard::Left) {
                proceed(Direction::Left);
            } else if (e.key.code == sf::Keyboard::Space) {
                rotate();
            }
            if(e.key.code == sf::Keyboard::Enter){
                paused = false;
                mGrid->clean();
                mHighScore.reset();
            }
        }
    }
}

void Game::render() {
    mRenderWindow.clear(sf::Color::Blue);
    mHighScore.draw(mRenderWindow);
    mGrid->draw(mRenderWindow);
    if(mTetromino) mRenderWindow.draw(*mTetromino);

    mRenderWindow.draw(*mPreview);
    mRenderWindow.draw(mSeparationLine);
    mRenderWindow.display();
}

void Game::proceed(Direction dir) {
    if(!mTetromino) return;

    if(isValidMovement(mTetromino->getFutureBlockPositions(dir))){
        mTetromino->move(dir);
        if(dir == Direction::SoftDown) mHighScore.addSoftScore(1);
    }
    else{
        if(dir == Direction::Down || dir == Direction::SoftDown) {
            int id = mTetromino->getID();
            mGrid->addBlock(id, mTetromino->getBlockPositions());
            mTetromino.reset(nullptr);
            mHighScore.sumSoftScore();
        }
    }
}

bool Game::isValidMovement(std::array<sf::Vector2i, 4> block) {
    for(int i = 0; i < 4; ++i){
        if(block[i].x < 0 ||block[i].x > 9 || block[i].y > 17){
            return false;
        }
        if(isOccupied(block[i].x, block[i].y)){
            return false;
        }
    }
    return true;
}

bool Game::isOccupied(int x, int y) {
    return mGrid->getField(x,y)->mOccupied;
}

void Game::createTetromino() {
   mTetromino.reset(new Tetromino{mTexture, mID});

   if(mGrid->isOccupied(mTetromino->getBlockPositions())){
        paused = true;
    }
    mID = getRandomNumber(7);
    mPreview.reset(new Tetromino{mTexture, mID});
    mPreview->setPosition(sf::Vector2i{11, 12});
}
