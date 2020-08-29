//
//  Game.hpp
//  Block Game
//
//  Created by Furkan Yıldırım on 29.08.2020.
//  Copyright © 2020 Furkan Yıldırım. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game {
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    
    //Private functions
    void initVariables();
    void initWindow();
    
public:
    //Constructors
    Game();
    virtual ~Game();
    
    //Accessors
    const bool getWindowIsOpen() const;
    
    //Functions
    void pollEvent();
    void update();
    void render();
};

#endif /* Game_hpp */
