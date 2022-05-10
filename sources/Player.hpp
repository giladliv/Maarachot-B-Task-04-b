#pragma once

#include <iostream>
#include <string>
#include "Game.hpp"


using namespace std;
using coup::Game;

namespace coup
{
    class Player
    {
        public:
            const string getName();
            ~Player();
            void income();
            void foreign_aid();
            virtual void coup(Player& player);
            string role() const;
            int coins() const;
            void throwIfNotYourTurn();
            void incCoins(int diff);
            vector<string> getLastAction();
            void cleanLastAction() {_lastAction.clear();}
            
        private:            
            string _name;
            string _role;
        
        protected:
            // only ones who can create the game can change the couping
            Player(Game& game, const string& name, const string& role = "");
            Game& _game;
            int _coins;
            vector<string> _lastAction;
            void throwIfMaxCoins();
            void throwIfNotInSameGame(const Player& player);
            void throwForBlocking(Player& player, const vector<string>& roles = {});
    };
    
    
    
}