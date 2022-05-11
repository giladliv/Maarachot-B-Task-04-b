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
            Player(Game& game, const string& name, const string& role = "");
            ~Player();
            void income();
            void foreign_aid();
            virtual void coup(Player& player);
            string role() const;
            int coins() const;
            void throwIfNotYourTurn() const;
            void incCoins(int diff);
            vector<string> getLastAction();
            void cleanLastAction() {_lastAction.clear();}
            string getName() {return _name;}
            
            
        private:            
            string _name;
            string _role;
        
        protected:
            // only ones who can create the game can change the couping
            Game& _game;
            int _coins;
            vector<string> _lastAction;
            void throwIfMaxCoins() const;
            void throwIfNotInSameGame(const Player& player);
            void throwForBlocking(Player& player, const vector<string>& roles = {});
    };
    
    
    
}