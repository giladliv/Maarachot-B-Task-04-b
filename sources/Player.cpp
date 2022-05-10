#include "Player.hpp"

using coup::Player;

Player::Player(Game& game, const string& name, const string& role) : _game(game), _coins(0)
{
    _name = name;
    _role = role;
}

Player::~Player()
{
}

void Player::throwIfMaxCoins()
{
    if (_coins >= MAX_COINS)
    {
        throw runtime_error("you cannot do this action\n"
                            "you reached 10 coins - you can only make a \"coup\" action");
    }
}

void Player::throwIfNotYourTurn()
{
    if (_game.turn() != _name)
    {
        throw runtime_error("this is not your turn");
    }
}

void Player::income()
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotYourTurn();   // check if this is the player's turn
    throwIfMaxCoins();      // check if the player doesnwt reach to the max coin number
    
    // increase the coins number by 1
    _coins++;
    
    // update the action
    _lastAction = vector<string>{"income"};

    // set the next player in game
    _game.setNextInRound();

}

void Player::foreign_aid()
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotYourTurn();   // check if this is the player's turn
    throwIfMaxCoins();      // check if the player doesnwt reach to the max coin number

    // increase the coins number by 2
    _coins += 2;
    
    // update the action
    _lastAction = vector<string>{"foreign_aid"};

    // set the next player in game
    _game.setNextInRound();
    
}

void Player::coup(Player& player)
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotYourTurn();
    throwIfNotInSameGame(player);
    
    // if player have less than 7 than that is illegal
    if (_coins < COUP_PRICE)
    {
        string sErr = string("you cannot coup - you have less than 7 coins");
        throw runtime_error(sErr);
    }

    // remove the coins number and remove from active ones
    _coins -= COUP_PRICE;
    if (!_game.coupPlayer(player._name))
    {
        throw runtime_error("coup on illegal player - not active");
    }

    // update the action
    _lastAction = vector<string>{"coup", player.getName()};

    // set the next player in game
    _game.setNextInRound();

}

string Player::role() const
{
    return _role;
}

int Player::coins() const
{
    return _coins;
}

void Player::throwIfNotInSameGame(const Player& player)
{
    if (&(this->_game) != &(player._game))
    {
        throw runtime_error("the games of the players are not the same");
    }
}

void Player::incCoins(int diff)
{
    _coins += diff;
}

vector<string> Player::getLastAction()
{
    return _lastAction;
}

void Player::throwForBlocking(Player& player, const vector<string>& roles = {})
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotInSameGame(player);
        player.throwIfNotYourTurn();
    // check that the player ia an assasin
    for (string roleOther: roles)
    {
        if (player.role() != roleOther)
        {
            throw runtime_error("the player must be: " + roleOther);
        }
    }

    // check thatit isnt the players turn
    
}