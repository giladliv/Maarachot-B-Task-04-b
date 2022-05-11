#pragma once

#include <iostream>
#include <string>
#include "Player.hpp"

using namespace std;
#define COIN_STL 2

namespace coup
{
    class Captain : public Player
    {
    private:
        /* data */
    public:
        Captain(Game& game, const string& name);
        ~Captain();
        void block(Player& player);
        void steal(Player& player);
    };
    
    
}