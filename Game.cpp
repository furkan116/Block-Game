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
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    
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
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
    
    
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

void Game::updateMousePositiosn(){
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
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
    
    for (auto &e : this->enemies) {
        e.move(0.f, 5.f);
    }
}

void Game::update(){
    this->pollEvent();
    this->updateMousePositiosn();
    this->updateEnemies();
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
