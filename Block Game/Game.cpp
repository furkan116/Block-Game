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
    
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    this->window = new sf::RenderWindow(this->videoMode, "Block Game", sf::Style::Titlebar | sf::Style::Close);
}

//Constructors
Game:: Game() {
    this->initVariables();
    this->initWindow();
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

void Game::update(){
    this->pollEvent();
}

void Game::render(){
    this->window->clear();// Clear old frame
    
    //Draw Game Objects
    
    this->window->display();//Draw your game
    
}
