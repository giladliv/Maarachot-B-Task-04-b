#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include "Player.hpp"

#define MAX_COINS 10
#define COUP_PRICE 7
#define MIN_PLAYERS 2
#define MAX_PLAYERS 6

using namespace std;

namespace coup
{
    class Player;

    class Game
    {
    private:
        unsigned int _playerIndex;
        //vector<string> _players;
        vector<Player*> _players;
        unordered_map<string, Player*> _playersInGame;
        int _countInGame;
        bool _gameInSession;
        bool isActive(unsigned int index);
        
    public:
        Game();
        ~Game();
        string turn();
        vector<string> players();
        string winner();
        bool addPlayer(Player& player);
        bool coupPlayer(const string& player);
        bool deCoupPlayer(const string& player);
        bool isActive(const string& player);
        void setNextInRound();
        void throwIfNotEnoughPlayers();
        bool isGameFull();
        bool isGameInSession() { return _gameInSession; }
        void updateGameSession() { _gameInSession = true; }
        bool isPlayerIn(const string&player);
        bool isPlayerTurn(const string& rname);
        int moveAmount(const string& srcPlyr, const string& dstPlyr, int amount, bool isActiveFlag = true);
        
    };
    
}