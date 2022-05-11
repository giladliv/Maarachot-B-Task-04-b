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


    _game.moveAmount(srcPlyr.getRoleAndName(), dstPlyr.getRoleAndName(), 1, false);

    // update the action
    _lastAction = vector<string>{"transfer", srcPlyr.getRoleAndName(), dstPlyr.getRoleAndName()};

    // set the next player in game
    _game.setNextInRound();
}

void Ambassador::block(Player& player)
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotInSameGame(player);
    
    throwForBlocking(player, {"Captain"});

    // check his last action
    vector<string> act = player.getLastAction();
    if (act.size() != 3 || act[0] != "steal")       // vector: action, name, amount
    {
        throw runtime_error("not blocking a steal act");
    }

    int amount = 0;
    try
    {
        amount = stoi(act[2]);
    }
    catch(const std::exception& e)
    {
        throw runtime_error("error: corrupted number of amout in log");
    }
    
    // take from the blocked player and move to th player, no available is needed
    _game.moveAmount(player.getRoleAndName(), act[1], amount, false);

    player.cleanLastAction();
    
    // after good blocking update that "The Game Is On" (Sherlock Holmes)
    _game.updateGameSession();
}