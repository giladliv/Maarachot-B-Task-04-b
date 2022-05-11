#include "Contessa.hpp"
using coup::Contessa;

Contessa::Contessa(Game& game, const string& name) : Player(game, name, "Contessa")
{
}

Contessa::~Contessa()
{

}

void Contessa::block(Player& player)
{
    // check the blocking incident
    throwForBlocking(player, {"Assassin"});

    // check his last action
    vector<string> act = player.getLastAction();
    if (act.size() != 2 || act[0] != "assasination")
    {
        throw runtime_error("assasination hasn't been occured");
    }

    // make the decouping
    if (!_game.deCoupPlayer(act[1]))
    {
        throw runtime_error("blocking failed");
    }

    // clean his last action
    player.cleanLastAction();
}