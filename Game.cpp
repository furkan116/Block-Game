//
//  Game.cpp
//  Block Game
//
//  Created by Furkan Yıldırım on 29.08.2020.
//  Copyright © 2020 Furkan Yıldırım. All rights reserved.
//

#include "Game.hpp"


//Private functions
void Game::initVariables() {
    this->window = nullptr;
    
    //Game Logic
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    this->endGame = false;
    
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    this->window = new sf::RenderWindow(this->videoMode, "Block Game", sf::Style::Titlebar | sf::Style::Close);
    
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    
    if (!this->fonts.loadFromFile("../Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font" << std::endl;
    }
}

void Game::initText() {
    
    this->uiText.setFont(this->fonts);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initEnemies() {
    
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
}

//Constructors
Game:: Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game:: ~Game() {
    delete this->window;
}

//Accessors
const bool Game::getWindowIsOpen() const{
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

//Functions
void Game::pollEvent() {
    //Event polling
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
                
        }
    }
}

void Game::spawnEnemy() {
    
    //Spawn enemy random type
    
    this->enemy.setPosition(static_cast<float>(rand()% static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),  0.f);
    
    //Randomize enemy type
    int type = rand() % 5;
    
    switch (type) {
        case 0:
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
            
        case 1:
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
            
        case 2:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Yellow);
            break;
            
        case 3:
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
            
        case 4:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Green);
            break;
            
        default://Error test
            this->enemy.setSize(sf::Vector2f(150.f, 150.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
    }
    
    this->enemies.push_back(this->enemy);
}

void Game::updateMousePositions(){
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText() {
    
    std::stringstream ss;
    
    ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";
    
    this->uiText.setString(ss.str());
}

void Game::updateEnemies() {
    
    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->enemySpawnTimer = 0.f;
            this->spawnEnemy();
        }
        else {
            this->enemySpawnTimer += 1.f;
        }
    }
    
    
    //Move to enemies
    for (int i = 0; i < this->enemies.size(); i++) {
        
        this->enemies[i].move(0.f, 2.f);
        
        //If the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << std::endl;
        }
        
    }
    
    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        
        if (this->mouseHeld == false) {
            
            this->mouseHeld = true;
            bool deleted = false;
            
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //Gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Red) {
                        this->points +=10;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Magenta) {
                        this->points +=8;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Yellow) {
                        this->points +=5;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan) {
                        this->points +=3;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Green) {
                        this->points +=1;
                    }
                    std::cout << "Points: " << this->points << std::endl;
                    
                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
        else {
            this->mouseHeld = false;
        }
        
    }
}

void Game::update(){
    this->pollEvent();
    
    if (this->endGame == false) {
        this->updateMousePositions();
        
        this->updateText();
        
        this->updateEnemies();
    }
    
    if(this->health <= 0) {
        this->endGame = true;
    }
}

void Game::renderText(sf::RenderTarget& target) {
    
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}


void Game::render(){
    this->window->clear();// Clear old frame
    
    //Draw Game Objects
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
    
    this->window->display();//Draw your game
    
}
