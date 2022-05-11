#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

#define MAX_COINS 10
#define COUP_PRICE 7
#define MIN_PLAYERS 2
#define MAX_PLAYERS 6

using namespace std;


namespace coup
{
    class Game
    {
    private:
        unsigned int _playerIndex;
        vector<string> _players;
        unordered_map<string, bool> _playersInGame;
        int _countInGame;
        bool isActive(unsigned int index);
        
    public:
        Game();
        ~Game();
        string turn();
        vector<string> players();
        string winner();
        bool addPlayer(const string& name);
        bool coupPlayer(const string& player);
        bool deCoupPlayer(const string& player);
        bool isActive(const string& player);
        void setNextInRound();
        void throwIfNotEnoughPlayers();
        bool isGameFull();
        
    };
    
}