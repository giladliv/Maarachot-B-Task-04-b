#include "doctest.h"
#include "Player.hpp"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "Game.hpp"

#include <exception>

using namespace coup;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace doctest;

TEST_CASE("Full-Game"){
   	Game game_1{};
	Assassin assassin{game_1, "Yossi"};
	Ambassador ambassador{game_1, "Meirav"};
	Contessa contessa{game_1, "Gilad"};
    CHECK_NOTHROW(assassin.foreign_aid());
    CHECK_NOTHROW(ambassador.foreign_aid());
    CHECK_NOTHROW(contessa.foreign_aid());
    CHECK_NOTHROW(assassin.income());
    CHECK_NOTHROW(ambassador.transfer(contessa,ambassador));
    CHECK_NOTHROW(contessa.foreign_aid());
    CHECK_NOTHROW(assassin.coup(contessa));
    CHECK_NOTHROW(ambassador.foreign_aid());
    CHECK_NOTHROW(assassin.foreign_aid());
    CHECK_NOTHROW(ambassador.foreign_aid());
    CHECK_NOTHROW(assassin.foreign_aid());
    CHECK_NOTHROW(ambassador.coup(assassin));
    CHECK_EQ(game_1.winner(),"Meirav");
}

TEST_CASE("Bad Cases")
{
    SUBCASE("TOO-MUCH PLAYERS")
    {
        Game game_1{};
        Duke duke(game_1, "Moshe");
	    Assassin assassin{game_1, "Yossi"};
	    Ambassador ambassador{game_1, "Meirav"};
	    Captain captain{game_1, "Reut"};
	    Contessa contessa{game_1, "Gilad"};
        Duke duke2{game_1,"Gabi"};
        for(int i=0;i<10;i++)
        {
           switch(i%5){
               case 0: try{Duke duke3(game_1,"Fail") ;CHECK_EQ(true,false);}catch(exception &e){CHECK_EQ(true,true);} break;
               case 1: try{Assassin assassin1(game_1,"Fail") ;CHECK_EQ(true,false);}catch(exception &e){CHECK_EQ(true,true);} break;
               case 2: try{Ambassador ambassador1(game_1,"Fail") ;CHECK_EQ(true,false);}catch(exception &e){CHECK_EQ(true,true);} break;
               case 3: try{Captain captain1(game_1,"Fail") ;CHECK_EQ(true,false);}catch(exception &e){CHECK_EQ(true,true);} break;
               case 4: try{Contessa contessa1(game_1,"Fail") ;CHECK_EQ(true,false);}catch(exception &e){CHECK_EQ(true,true);} break;
           }
        }
    }
    SUBCASE("TOO-FEW PLAYERS")
    {
        Game game_1{};
        Duke duke(game_1, "Moshe");
        for(int i=0;i<10;i++)
        {
            CHECK_THROWS(duke.income());
            CHECK_THROWS(duke.foreign_aid());
        }
    }
    SUBCASE("NOT PLAYERS TURN")
    {
        Game game_1{};
        Duke duke(game_1, "Moshe");
	    Assassin assassin{game_1, "Yossi"};
	    Ambassador ambassador{game_1, "Meirav"};
	    Captain captain{game_1, "Reut"};
	    Contessa contessa{game_1, "Gilad"};
        CHECK_THROWS(assassin.foreign_aid());
        CHECK_THROWS(ambassador.foreign_aid());
        CHECK_THROWS(captain.steal(duke));
        duke.income();
        CHECK_THROWS(contessa.foreign_aid());
    }
    SUBCASE("ILLEGAL ACTION")
    {
        Game game_1{};
        Duke duke(game_1, "Moshe");
	    Assassin assassin{game_1, "Yossi"};
	    Ambassador ambassador{game_1, "Meirav"};
	    Captain captain{game_1, "Reut"};
	    Contessa contessa{game_1, "Gilad"};
        CHECK_THROWS(duke.coup(assassin));
        duke.income();
        assassin.foreign_aid();
	ambassador.income();
        CHECK_THROWS(assassin.coup(duke));
        CHECK_THROWS(captain.block(duke));
        captain.steal(duke);
        CHECK_THROWS(contessa.block(assassin));
        contessa.income();
    }
}
TEST_CASE("CHECK Game")
{
    Game game_1{};
    Duke duke(game_1, "Moshe");
	Assassin assassin{game_1, "Yossi"};
	Ambassador ambassador{game_1, "Meirav"};
	Captain captain{game_1, "Reut"};
	Contessa contessa{game_1, "Gilad"};
    vector<string>names={"Moshe","Yossi","Meirav","Reut","Gilad"};
    for(unsigned i=0; i<game_1.players().size() && i<names.size();i++)
    {
        CHECK_EQ(names[i],game_1.players()[i]);
    }
    duke.tax();
    assassin.foreign_aid();
    ambassador.transfer(duke,assassin);
    captain.steal(duke);
    contessa.foreign_aid();
    duke.tax();
    assassin.coup(duke);
    names={"Yossi","Meirav","Reut","Gilad"};
    for(unsigned i=0; i<game_1.players().size() && i<names.size();i++)
    {
        CHECK_EQ(names[i],game_1.players()[i]);
    }
    contessa.block(assassin);
    names={"Moshe","Yossi","Meirav","Reut","Gilad"};
    for(unsigned i=0; i<game_1.players().size() && i<names.size();i++)
    {
        CHECK_EQ(names[i],game_1.players()[i]);
    }

}
