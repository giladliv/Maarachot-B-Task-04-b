#pragma once

#include <iostream>
#include <string>
#include "Player.hpp"

using namespace std;


namespace coup
{
    class Duke : public Player
    {
    private:
        /* data */
    public:
        Duke(Game& game, const string& name);
        ~Duke();
        void block(Player& other);
        void tax();
    };
    
    
}