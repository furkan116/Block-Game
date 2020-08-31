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

void Game::initEnemies() {
    
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(0.5f, 0.5f);
    this->enemy.setFillColor(sf::Color::Cyan);
    
    
}

//Constructors
Game:: Game() {
    this->initVariables();
    this->initWindow();
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
    
    this->enemy.setPosition(static_cast<float>(rand()% static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),  0.f);
    
    this->enemy.setFillColor(sf::Color::Green);
    
    this->enemies.push_back(this->enemy);
}

void Game::updateMousePositions(){
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
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
                
        this->enemies[i].move(0.f, 4.f);
        
        //If the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
        
    }
    
    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        
        if (this->mouseHeld == false) {
            
            this->mouseHeld = true;
            bool deleted = false;
            
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    //Gain points
                    this->points += 10.f;
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
        this->updateEnemies();
    }
    
    if(this->health <= 0) {
        this->endGame = true;
    }
}

void Game::renderEnemies() {
    
    for (auto &e : this->enemies) {
        this->window->draw(e);
    }
}


void Game::render(){
    this->window->clear();// Clear old frame

    //Draw Game Objects
    this->renderEnemies();
    
    this->window->display();//Draw your game
    
}
