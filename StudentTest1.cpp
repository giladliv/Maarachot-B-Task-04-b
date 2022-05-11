/**
 * Test file to check the correctness of coup game
 *
 * @author Raz Gavrieli -> razgavrieli@gmail.com
 * @since 2022-04
 */

#include "Player.hpp"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "Game.hpp"
using namespace coup;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

#include "doctest.h"

TEST_CASE("GAME SCENARIO 1") {
    Game scenario1{};

    Duke PlayerONE{scenario1, "Player ONE"};
	Assassin PlayerTWO{scenario1, "Player TWO"};
	Duke PlayerTHREE{scenario1, "Player THREE"};
	Contessa PlayerFOUR{scenario1, "Player FOUR"};
    vector<Player*> Players = {&PlayerONE, &PlayerTWO, &PlayerTHREE, &PlayerFOUR};

    CHECK_EQ(PlayerTWO.role(), "Assassin");
    CHECK_EQ(PlayerONE.role(), PlayerTHREE.role()); // Two players can have the same role

    CHECK_EQ(scenario1.players().size(), 4);
    CHECK_NOTHROW(PlayerONE.income());
    CHECK_THROWS(PlayerTHREE.income()); // Its Player Two's turn

    CHECK_EQ(PlayerONE.coins(), 1);
    CHECK_EQ(PlayerTHREE.coins(), 0);
    for (size_t i = 1; i < Players.size(); i++)
    {
        CHECK_NOTHROW(Players.at(i)->income());
    }
    for (size_t j = 0; j < 2; j++)
    {
        for (size_t i = 0; i < Players.size(); i++)
        {
            CHECK_NOTHROW(Players.at(i)->income());
        }
    }

    for (size_t i = 0; i < Players.size(); i++)
    {
        CHECK_EQ(Players.at(i)->coins(), 3); // everyone has 3 coins
    }

    CHECK_THROWS(PlayerONE.coup(PlayerTWO)); // Player ONE doesn't have enough coins to coup
    CHECK_NOTHROW(PlayerONE.tax());
    CHECK_NOTHROW(PlayerTWO.coup(PlayerONE)); // Player TWO is an assassin and can coup with 3 coins
    CHECK_EQ(scenario1.players().size(), 3); // Player ONE is out of the game
    CHECK_EQ(PlayerTHREE.coins(), 3);
    CHECK_NOTHROW(PlayerTHREE.tax());
    CHECK_EQ(PlayerTHREE.coins(), 6);
    CHECK_THROWS(PlayerTWO.income()); // Its not Player TWO's turn
    CHECK_NOTHROW(PlayerFOUR.block(PlayerTWO)); // Contessa blocks the coup and ..
    CHECK_EQ(scenario1.players().size(), 4); // .. Player ONE returns to the game
    CHECK_THROWS(PlayerTWO.income()); // Its not Player TWO's turn, Keep in mind that Player one returns to the same order
    CHECK_EQ(PlayerONE.coins(), 6);
    PlayerFOUR.foreign_aid();
    CHECK_NOTHROW(PlayerONE.income());
    CHECK_EQ(PlayerONE.coins(), 7);
    CHECK_THROWS(PlayerTWO.coup(PlayerFOUR)); // not enough coins
    CHECK_NOTHROW(PlayerTWO.foreign_aid());
    CHECK_THROWS(PlayerTHREE.block(PlayerONE)); // Player THREE can't block income which is Player ONE's last move
    CHECK_NOTHROW(PlayerTHREE.block(PlayerTWO)); // Player THREE can block Player TWO's foreign aid.
    CHECK_NOTHROW(PlayerTHREE.tax());
    PlayerFOUR.foreign_aid();
    PlayerONE.income();
    PlayerTWO.income();
    PlayerTHREE.income();
    CHECK_NOTHROW(PlayerFOUR.coup(PlayerONE));
    CHECK_NOTHROW(PlayerTWO.foreign_aid());
    CHECK_NOTHROW(PlayerTHREE.block(PlayerTWO));
    PlayerTHREE.coup(PlayerFOUR);
    PlayerTWO.foreign_aid();
    PlayerTHREE.tax();
    PlayerTWO.coup(PlayerTHREE);
    CHECK_EQ(scenario1.players().size(), 1);
    CHECK_EQ(scenario1.winner(), "Player TWO");
}

TEST_CASE("GAME SCENARIO 2") {
    Game scenario2{};

    Duke PlayerONE{scenario2, "Player ONE"};
	Assassin PlayerTWO{scenario2, "Player TWO"};
	Captain PlayerTHREE{scenario2, "Player THREE"};
    vector<Player*> Players = {&PlayerONE, &PlayerTWO, &PlayerTHREE};

    CHECK_EQ(PlayerTHREE.role(), "Captain");

    CHECK_EQ(scenario2.players().size(), 3);
    CHECK_NOTHROW(PlayerONE.tax()); // 3 (COINS)
    CHECK_THROWS(PlayerTHREE.income());  // Player TWO's turn. Not THREE's
    CHECK_NOTHROW(PlayerTWO.income());// 1 (COINS)
    CHECK_EQ(PlayerTWO.coins(), 1);
    CHECK_NOTHROW(PlayerTHREE.steal(PlayerTWO));  // THREE 1, TWO 0 (COINS)
    CHECK_EQ(PlayerONE.coins(), 3);
    CHECK_EQ(PlayerTHREE.coins(), 1);
    CHECK_EQ(PlayerTWO.coins(), 0);
    for (size_t j = 0; j < 5; j++)
    {
        for (size_t i = 0; i < Players.size(); i++)
        {
            CHECK_NOTHROW(Players.at(i)->income()); // ADD 5 COINS TO EACH PLAYER
        }
    }
    CHECK_EQ(PlayerTHREE.coins(), 6);
    CHECK_EQ(PlayerTWO.coins(), 5);
    CHECK_EQ(PlayerONE.coins(), 8);
    CHECK_NOTHROW(PlayerONE.coup(PlayerTHREE));
    CHECK_THROWS(scenario2.winner()); // Game not over
    CHECK_EQ(PlayerONE.coins(), 1);
    CHECK_EQ(scenario2.players().size(), 2);
    CHECK_THROWS(PlayerTWO.coup(PlayerTHREE)); // PLAYER THREE ALREADY DEAD
    CHECK_EQ(scenario2.players().size(), 2);
    CHECK_NOTHROW(PlayerTWO.coup(PlayerONE));
    CHECK_EQ(scenario2.players().size(), 1);
    CHECK_THROWS(PlayerONE.coup(PlayerTWO)); // PLAYER ONE ALREADY DEAD
    CHECK_EQ(scenario2.winner(), "Player TWO");
}

TEST_CASE("GAME SCENARIO 3") {
    Game scenario3{};

    Ambassador PlayerONE{scenario3, "Player ONE"};
	Contessa PlayerTWO{scenario3, "Player TWO"};
    Duke PlayerTHREE{scenario3, "Player THREE"};
    vector<Player*> Players = {&PlayerONE, &PlayerTWO, &PlayerTHREE};

    for (size_t j = 0; j < 8; j++)
    {
        for (size_t i = 0; i < Players.size(); i++)
        {
            CHECK_NOTHROW(Players.at(i)->income());
        }
        CHECK_EQ(PlayerONE.coins(), j+1);
        CHECK_EQ(PlayerTWO.coins(), j+1);
        CHECK_EQ(PlayerTHREE.coins(), j+1);
    }

    CHECK_NOTHROW(PlayerONE.transfer(PlayerTWO, PlayerTHREE));
    CHECK_EQ(PlayerTWO.coins(), 7);
    CHECK_EQ(PlayerTHREE.coins(), 9);
    CHECK_NOTHROW(PlayerTWO.coup(PlayerTHREE));
    CHECK_THROWS(PlayerONE.coup(PlayerTHREE)); // player three already dead
    CHECK_NOTHROW(PlayerONE.coup(PlayerTWO));
    CHECK_EQ(scenario3.winner(), "Player ONE");
}

TEST_CASE("Assassination with more than 7 coins") {
    /*
        This specific test checks if a coup made by an assassin is blockable by contessa.
        Later in the game the assassin will have more than 7 coins, 
        and if he coups it will cost him 7 coins and will be unblockable by the contessa.
    */
    Game scenario4{};
    Assassin assassin{scenario4, "Player ONE"};
    Contessa contessa{scenario4, "Player TWO"};
    Duke duke{scenario4, "Player THREE"};

    std::vector<Player*> Players = {&assassin, &contessa, &duke};
    for (size_t j = 0; j < 5; j++)
    {
        for (size_t i = 0; i < Players.size(); i++)
        {
           CHECK_NOTHROW( Players.at(i)->income());
        }
    }
    CHECK_NOTHROW(assassin.coup(duke)); // Assassin can coup with 3 coins
    CHECK_EQ(assassin.coins(), 2); // The coup cost the assassin only 3 coins.
    CHECK_EQ(scenario4.players().size(), 2); // Player THREE is out of the game
    CHECK_NOTHROW(contessa.block(assassin)); // Player THREE is back in the game
    CHECK_EQ(scenario4.players().size(), 3);
    CHECK_EQ(assassin.coins(), 2); // The block of the contessa DID NOT refund the assassin.
    CHECK_NOTHROW(contessa.income()); 
    CHECK_NOTHROW(duke.income());
    for (size_t j = 0; j < 3; j++)
    {
        for (size_t i = 0; i < Players.size(); i++)
        {
            if (i==0) {
                CHECK_NOTHROW(Players.at(i)->foreign_aid());
            } else {
                CHECK_NOTHROW(Players.at(i)->income());
            }
        }
    }
    CHECK_EQ(assassin.coins(), 8); // Assassin has now 8 coins, so he can coup without being blocked by contessa.
    CHECK_EQ(scenario4.players().size(), 3);
    CHECK_NOTHROW(assassin.coup(duke)); // Player THREE is out of the game
    CHECK_EQ(assassin.coins(), 1); // The coup cost the assassin 7 coins and is unblockable.
    CHECK_EQ(scenario4.players().size(), 2);
    CHECK_THROWS(contessa.block(assassin)); // Read explanation at lines 158-160
    CHECK_EQ(scenario4.players().size(), 2); // Player THREE is still out of the game, the contessa couldn't block the assassin
    CHECK_EQ(assassin.coins(), 1); 
}

TEST_CASE("Ambassador transfer test") {
    /*
        This specific test checks the correctness of transfer 
    */
    Game scenario5{};
    Assassin assassin{scenario5, "Player ONE"};
    Ambassador ambassador{scenario5, "Player TWO"};
    Duke duke{scenario5, "Player THREE"};
    std::vector<Player*> Players = {&assassin, &ambassador, &duke};
    assassin.income();
    CHECK_THROWS(ambassador.transfer(duke, assassin)); // not enough money to transfer from duke, you can't transfer zero coins
    ambassador.income();
    duke.income();
    CHECK_EQ(assassin.coins(), 1);
    CHECK_EQ(ambassador.coins(), 1);
    CHECK_EQ(duke.coins(), 1);
    for (size_t j = 0; j < 4; j++)
    {
        for (size_t i = 0; i < Players.size(); i++)
        {
           CHECK_NOTHROW( Players.at(i)->income());
        }
    }
    CHECK_EQ(assassin.coins(), 5);
    CHECK_EQ(ambassador.coins(), 5);
    CHECK_EQ(duke.coins(), 5);
    assassin.income();
    CHECK_EQ(assassin.coins(), 6);
    CHECK_NOTHROW(ambassador.transfer(assassin, duke)); // transfer one coin from assassin to duke
    CHECK_EQ(assassin.coins(), 5);
    CHECK_EQ(ambassador.coins(), 5);
    CHECK_EQ(duke.coins(), 6);

}