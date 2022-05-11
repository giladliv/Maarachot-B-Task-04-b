#include "Game.hpp"
using coup::Game;


Game::Game() : _playerIndex(0), _countInGame(0)
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
    return (_players[_playerIndex]);
}

vector<string> Game::players()
{
    vector<string> playersCurr;
    for (unsigned int i = 0; i < _players.size(); i++)
    {
        // if the player is active push it to the end
        if (isActive(_players[i]))
        {
            playersCurr.push_back(_players[i]);
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
    return (players()[0]);
}

bool Game::addPlayer(const string& name)
{
    if (_playersInGame.find(name) != _playersInGame.end())
    {
        return (false);
    }
    
    _playersInGame[name] = true;
    _players.push_back(name);
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
    _playersInGame[player] = false;
    _countInGame--;
    return (true);
    
}

bool Game::deCoupPlayer(const string& player)
{
    // if player is active already or not exists that it failed to to the action
    if (isActive(player) || _playersInGame.find(player) == _playersInGame.end())
    {
        return (false);
    }
    _playersInGame[player] = true;
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
        return (_playersInGame[player]);
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
        return (isActive(_players[index]));
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
            _playerIndex = (_playerIndex + 1) % len;
        } while (!isActive(_playerIndex));
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