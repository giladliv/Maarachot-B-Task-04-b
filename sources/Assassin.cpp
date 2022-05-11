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
    // if there is more than 7 coins for assasin he makes only coup
    if (_coins >= COUP_PRICE)
    {
        Player::coup(player);
        return;
    }
    
    //if assassin have les then 7 coins then he can assasin regularly

    // first add 4 coins
    _coins += COINS_DIFF;

    try
    {
        // by using the coup older function we will pay only 3
        Player::coup(player);
        _lastAction = vector<string>{"assasination", player.getName()};
    }
    catch(const std::exception& e)
    {
        // if there were bad action then retrive 4 coins
        _coins -= COINS_DIFF;
        if (string(e.what()) == "you cannot coup - you have less than 7 coins")
        {
            throw runtime_error("you cannot coup - you have less than 3 coins");
        }
        throw (e);
    }
    
    
}