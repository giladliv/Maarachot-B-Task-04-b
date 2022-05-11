#include "Player.hpp"

using coup::Game;
using coup::Player;

Player::Player(Game& game, const string& name, const string& role) : _game(game), _coins(0), _active(true)
{
    _name = name;
    _role = role;
    // check if game is full
    if (_game.isGameFull())
    {
        throw runtime_error("the game is full");
    }

    // check if game has been started
    if (_game.isGameInSession())
    {
        throw runtime_error("the game has been started - cannot join");
    }

    // check if the player already started
    if (!_game.addPlayer(*this))
    {
        throw ("player name alrady exists");
    }
}

Player::~Player()
{
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

    // first chaeck if couping right
    if (!_game.coupPlayer(player.getRoleAndName()))
    {
        throw runtime_error("coup on illegal player - not active");
    }

    // remove the coins number and remove from active ones
    _coins -= COUP_PRICE;

    // update the action
    _lastAction = vector<string>{"coup", player.getRoleAndName()};

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

/**
 * @brief a uniqe string that identify the player - role and name
 * 
 * @return string 
 */
string Player::getRoleAndName()
{
    return (_role + "::" + _name);
}

/**
 * @brief get if the player is active in the game
 * 
 * @return true 
 * @return false 
 */
bool Player::getActive() const
{
    return _active;
}

/**
 * @brief set activity of player in game
 * 
 * @param status true if active
 */
void Player::setActive(bool status)
{
    _active = status;
}

/**
 * @brief the function throws an exception if the player have 10 coins - for functions that not coup
 * 
 */
void Player::throwIfMaxCoins() const
{
    if (_coins >= MAX_COINS)
    {
        throw runtime_error("you cannot do this action\n"
                            "you reached 10 coins - you can only make a \"coup\" action");
    }
}

/**
 * @brief if it is not the players turn an exception will be thrown
 * 
 */
void Player::throwIfNotYourTurn()
{
    // if not the players turn by id string
    if (!_game.isPlayerTurn(getRoleAndName()))
    {
        throw runtime_error("this is not your turn");
    }
}

/**
 * @brief an exception will be thrown if a player doesn't match the same game - the same object
 * 
 * @param player 
 */
void Player::throwIfNotInSameGame(const Player& player)
{
    if (&(this->_game) != &(player._game))
    {
        throw runtime_error("the games of the players are not the same");
    }
}

/**
 * @brief by giving an integer the coins will added
 * 
 * @param diff 
 */
void Player::incCoins(int diff)
{
    _coins += diff;
}

/**
 * @brief returns the last action that the player did - for non blocking actions
 * 
 * @return vector<string> 
 */
vector<string> Player::getLastAction()
{
    return _lastAction;
}

/**
 * @brief the function check all the parameters for making a blocking action.
 * this is universal check for every blocker
 * 
 * @param player 
 * @param roles specific rolees that player must have
 */
void Player::throwForBlocking(Player& player, const vector<string>& roles)
{
    _game.throwIfNotEnoughPlayers();
    throwIfNotInSameGame(player);

    // check that it isn't the players turn
    if (_game.isPlayerTurn(player.getRoleAndName()))
    {
        throw runtime_error("blocking failed because the blocked player turn has arrived");
    }

    // check that the player ia an assasin
    for (const string& roleOther: roles)
    {
        if (player.role() != roleOther)
        {
            throw runtime_error("the player must be: " + roleOther);
        }
    }
}

/**
 * @brief if game hasn't been started throw an  exception
 * 
 */
void Player::throwIfGameNotInSession()
{
    if (!_game.isGameInSession())
    {
        throw runtime_error("the game hasn't been started");
    }
}