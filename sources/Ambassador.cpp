#include "Ambassador.hpp"
using coup::Ambassador;

Ambassador::Ambassador(Game& game, const string& name) : Player(game, name, "Ambassador")
{

}

Ambassador::~Ambassador()
{

}

void Ambassador::transfer(Player& srcPlyr, Player& dstPlyr)
{
    _game.throwIfNotEnoughPlayers();
    
    throwIfNotYourTurn();   // check if this is the player's turn
    throwIfMaxCoins();      // check if the player doesnwt reach to the max coin number
    throwIfNotInSameGame(srcPlyr);
    throwIfNotInSameGame(dstPlyr);


    if (srcPlyr.coins() < 1)
    {
        throw runtime_error("the source player have less than 1 coins");
    }

    srcPlyr.incCoins(-1);
    dstPlyr.incCoins(1);

    // update the action
    _lastAction = vector<string>{"transfer", srcPlyr.getName(), dstPlyr.getName()};

    // set the next player in game
    _game.setNextInRound();
}

void Ambassador::block(Player& player)
{
    throwForBlocking(player, {"Captain"});

    // check his last action
    vector<string> act = player.getLastAction();
    if (act.size() != 2 || act[0] != "steal")
    {
        throw runtime_error("not blocking a steal act");
    }

    this->incCoins(-2);
    player.incCoins(2);

    player.cleanLastAction();
}