#include "Assassin.hpp"
using coup::Assassin;

Assassin::Assassin(Game& game, const string& name) : Player(game, name, "Assassin")
{
}

Assassin::~Assassin()
{

}

void Assassin::coup(Player& player)
{
    // first add 4 coins
    _coins += COINS_DIFF;

    try
    {
        // by using the coup older function we will pay only 4
        Player::coup(player);
    }
    catch(const std::exception& e)
    {
        _coins -= COINS_DIFF;
        if (string(e.what()) == "you cannot coup - you have less than 7 coins")
        {
            throw runtime_error("you cannot coup - you have less than 7 coins");
        }
        else
        {
            throw (e);
        }
    }
    _lastAction = vector<string>{"assasination", player.getName()};
    
}