//
//  Game.hpp
//  Block Game
//
//  Created by Furkan Yıldırım on 29.08.2020.
//  Copyright © 2020 Furkan Yıldırım. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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
    
    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    
    //Resources
    sf::Font fonts;
    
    //Text
    sf::Text uiText;
    
    //Game Logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
    
    //Game Objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;
    
    //Private functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();
    
public:
    //Constructors
    Game();
    virtual ~Game();
    
    //Accessors
    const bool getWindowIsOpen() const;
    const bool getEndGame() const;
    
    //Functions
    void spawnEnemy();
    void pollEvent();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();
    
    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();
};

#endif /* Game_hpp */
