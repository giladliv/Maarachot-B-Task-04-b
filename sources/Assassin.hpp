#pragma once

#include <iostream>
#include <string>
#include "Player.hpp"

#define COINS_DIFF 4

using namespace std;

namespace coup
{
    class Assassin : public Player
    {
    private:
        /* data */
    public:
        Assassin(Game& game, const string& name);
        ~Assassin();

        virtual void coup(Player& player);
    };
    
    
}