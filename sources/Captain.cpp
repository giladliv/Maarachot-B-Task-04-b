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
    // before each move that ocured update that the game has been started - even if not good
    _game.updateGameSession();

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

void Captain::steal(Player& player)
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotYourTurn();   // check if this is the player's turn
    throwIfMaxCoins();      // check if the player doesnwt reach to the max coin number
    throwIfNotInSameGame(player);


    // if there are less then 2 coins then thake the players amount
    int amount = (player.coins() < COIN_STL) ? player.coins() : COIN_STL;

    player.incCoins(-amount);
    this->incCoins(amount);

    // update the action
    _lastAction = vector<string>{"steal", player.getName()};

    // set the next player in game
    _game.setNextInRound();


}