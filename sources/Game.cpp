#include "Game.hpp"
using coup::Game;
using coup::Player;


Game::Game() : _playerIndex(0), _countInGame(0), _gameInSession(false)
{
}

Game::~Game()
{
}

string Game::turn()
{
    if (_countInGame == 0)
    {
        throw runtime_error("there are no players in game");
    }
    return (_players[_playerIndex]->getName());
}

vector<string> Game::players()
{
    vector<string> playersCurr;
    for (unsigned int i = 0; i < _players.size(); i++)
    {
        // if the player is active push it to the end
        if (isActive(i))
        {
            playersCurr.push_back(_players[i]->getName());
        }
    }
    
    return(playersCurr);
}

string Game::winner()
{
    if (_countInGame != 1)
    {
        throw runtime_error("there is no winner yet");
    }
    if (_players.size() == 1)
    {
        throw runtime_error("there is only one player");
    }
    return (players()[0]);
}

bool Game::addPlayer(Player& player)
{
    // get the id string for the player
    string rname = player.getRoleAndName();

    if (_playersInGame.find(rname) != _playersInGame.end())
    {
        return (false);
    }
    
    player.setActive(true);
    _playersInGame[rname] = &player;
    _players.push_back(&player);
    _countInGame++;
    return (true);
}

bool Game::coupPlayer(const string& player)
{
    // if player is nigther active nor exists that return that it didn't succeded
    if (!isActive(player))
    {
        return (false);
    }
    _playersInGame[player]->setActive(false);
    _countInGame--;
    return (true);
    
}

bool Game::deCoupPlayer(const string& player)
{
    // if player is active already or not exists that it failed to to the action
    if (isActive(player) || !isPlayerIn(player))
    {
        return (false);
    }
    _playersInGame[player]->setActive(true);
    _countInGame++;
    return (true);
}

/**
 * @brief checks if player in game
 * 
 * @param player string of the player
 * @return true 
 * @return false 
 */
bool Game::isActive(const string& player)
{
    try
    {
        // if exists return the value
        return (_playersInGame[player]->getActive());
    }
    catch(const std::exception& e)
    {
        return (false);
    }
}

/**
 * @brief same as the string but index of the player in vector
 * 
 * @param index 
 * @return true 
 * @return false 
 */
bool Game::isActive(unsigned int index)
{
    try
    {
        // if exists return the value
        return (_players[index]->getActive());
    }
    catch(const std::exception& e)
    {
        return (false);
    }
}

/**
 * @brief set the index to the next player
 * 
 * @return true 
 * @return false 
 */
void Game::setNextInRound()
{
    if (_countInGame > 1 || (_countInGame == 1 && !isActive(_playerIndex)))
    {
        unsigned int len = _playersInGame.size();
        do
        {
            _playerIndex = ((_playerIndex % len) + 1) % len;
        } while (!isActive(_playerIndex));
        
        // after each (non-block) move that ocured successfuly update that the game has been started
        updateGameSession();
    }

}

void Game::throwIfNotEnoughPlayers()
{
    int len = _players.size();
    if (len < MIN_PLAYERS || len > MAX_PLAYERS)
    {
        throw runtime_error("not valid number of players must be 2-6, there are: " + to_string(len));
    }
}

bool Game::isGameFull()
{
    return (_players.size() >= MAX_PLAYERS);
}

bool Game::isPlayerIn(const string& player)
{
    return (_playersInGame.find(player) != _playersInGame.end());
}

bool Game::isPlayerTurn(const string& rname)
{
    return (isActive(rname) && _playersInGame[rname] == _players[_playerIndex]);
}

int Game::moveAmount(const string& srcPlyr, const string& dstPlyr, int amount, bool isActiveFlag)
{
    if(!isPlayerIn(srcPlyr) || !isPlayerIn(dstPlyr))
    {
        throw runtime_error("one or more of the 2 players are not in the game");
    }
    if (isActiveFlag && (!isActive(srcPlyr) || !isActive(dstPlyr)))
    {
        throw runtime_error("the two players must be active");
    }

    Player& src = *_playersInGame[srcPlyr];
    Player& dest = *_playersInGame[dstPlyr];
    
    // if there are lower amout of coins from src take all of player's coins
    amount = src.coins() < amount ? src.coins() : amount;

    if (amount == 0)
    {
        throw runtime_error("cannot transport 0 coins");
    }

    // make the transphare
    src.incCoins(-amount);  // reduce amount
    dest.incCoins(amount);  // increase amount

    return (amount);
}

