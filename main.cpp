//
//  main.cpp
//  Block Game
//
//  Created by Furkan Yıldırım on 29.08.2020.
//  Copyright © 2020 Furkan Yıldırım. All rights reserved.
//

#include <iostream>
#include "Game.hpp"

int main(int argc, const char * argv[]) {
    
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    
    //Init Game Engine
    Game game;
    
    // Game Loop
    while (game.getWindowIsOpen()){
        //Update
        game.update();
        
        //Render
        game.render();
    }
    
    // End of Game
    
    return 0;
}
