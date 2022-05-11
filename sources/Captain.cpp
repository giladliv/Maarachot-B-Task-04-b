#include "Captain.hpp"

using coup::Captain;

Captain::Captain(Game& game, const string& name) : Player(game, name, "Captain")
{

}

Captain::~Captain()
{

}

void Captain::block(Player& player)
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

void Captain::steal(Player& player)
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotYourTurn();   // check if this is the player's turn
    throwIfMaxCoins();      // check if the player doesnwt reach to the max coin number
    throwIfNotInSameGame(player);

    // move from player to current player
    int tCoins = _game.moveAmount(player.getRoleAndName(), getRoleAndName(), COIN_STL);

    // update the action
    _lastAction = vector<string>{"steal", player.getRoleAndName(), to_string(tCoins)};

    // set the next player in game
    _game.setNextInRound();


}