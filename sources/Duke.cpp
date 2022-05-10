#include "Duke.hpp"
using coup::Duke;


Duke::Duke(Game& game, const string& name) : Player(game, name, "Duke")
{
}

Duke::~Duke()
{

}

void Duke::block(Player& other)
{
    // check the blocking incident
    throwForBlocking(other);

    vector<string> act = other.getLastAction();
    if (act.size() != 1 || act[0] != "foreign_aid")
    {
        throw runtime_error("foreign_aid hasn't been occured");
    }
    other.cleanLastAction();
    other.incCoins(-2);
}

void Duke::tax()
{
    //using the one only coin addition
    Player::income();

    //if reached here there were no warnings
    _coins += 2;
    _lastAction = vector<string>{"tax"};
}
