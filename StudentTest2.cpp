#include "Game.hpp"
#include "Player.hpp"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "doctest.h"

using namespace coup;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;


TEST_CASE("Build New Game with 2-6 players") {
	try{ // 6 players
		Game game_1{};
		Duke duke{game_1, "p1"};
		Assassin assassin{game_1, "p2"};
		Ambassador ambassador{game_1, "p3"};
		Captain captain{game_1, "p4"};
		Contessa contessa{game_1, "p5"};
		Contessa contessa2{game_1, "p6"};
		CHECK_EQ(true,true);
	} catch(...){
		CHECK_EQ(true,false);
	}

	try{ // 4 players
		Game game_2{};
		Duke duke{game_2, "p1"};
		Assassin assassin{game_2, "p2"};
		Ambassador ambassador{game_2, "p3"};
		Captain captain{game_2, "p4"};
		CHECK_EQ(true,true);
	} catch(...){
		CHECK_EQ(true,false);
	}
}

TEST_CASE("Build New Game with 1 player Or More Than 6 players") {
	Game game_3{}; // build game . add players
	Duke duke{game_3, "p1"};
	CHECK_THROWS(duke.income()); // try to start the game with one player
	Assassin assassin{game_3, "p2"};
	Ambassador ambassador{game_3, "p3"};
	Captain captain{game_3, "p4"};
	Contessa contessa{game_3, "p5"};
	Captain captain2{game_3, "p6"};
	try{ // add more than 6 players
		Ambassador ambassador{game_3, "too many"};
		CHECK_EQ(true,false);
	} catch(...){
		CHECK_EQ(true,true);
	}
}

TEST_CASE("Build New Game With Same Names For Players") {
	Game game_4{}; // build game . add players
	Duke duke{game_4, "p1"};
	Assassin assassin{game_4, "p2"};
	Ambassador ambassador{game_4, "p3"};
	Captain captain{game_4, "p4"};
	Contessa contessa{game_4, "p5"};
	try{
		Contessa contessa3{game_4, "p4"}; // same name, there is no problem
		CHECK_EQ(true,true);
	} catch(...){
		CHECK_EQ(true,false);
	}
}

TEST_CASE("Add Player In Middle Of Game") {
	Game game_5{}; // build game . add players
	Duke duke{game_5, "p1"};
	Assassin assassin{game_5, "p2"};
	Ambassador ambassador{game_5, "p3"};
	duke.income();
	try{
		Ambassador ambassador{game_5, "game already started"};
		CHECK_EQ(true,false);
	} catch(...){
		CHECK_EQ(true,true);
	}
}

TEST_CASE("Coins") {
	Game game_6{}; // build game . add players
	Duke duke{game_6, "Moshe"};
	Assassin assassin{game_6, "Yossi"};
	Ambassador ambassador{game_6, "Meirav"};
	Captain captain{game_6, "Reut"};
	Contessa contessa{game_6, "Gilad"};

	for (int i=0 ; i<9 ; i++){
		duke.income();
		assassin.income();
		ambassador.income();
		captain.income();
		contessa.income();
	}
	// before transfering coins
	CHECK_EQ(duke.coins(),9);
	CHECK_EQ(assassin.coins(),9);
	CHECK_EQ(ambassador.coins(),9);
	CHECK_EQ(captain.coins(),9);
	CHECK_EQ(contessa.coins(),9);

	duke.income(); // 10
	assassin.foreign_aid(); // 11
	ambassador.coup(duke); // 2
	captain.income(); // 10
	contessa.coup(captain); // 2

	// after transfering coins
	CHECK_EQ(assassin.coins(),11);
	CHECK_EQ(ambassador.coins(),2);
	CHECK_EQ(contessa.coins(),2);	
}

TEST_CASE("Roles") {
	Game game_7{}; // build game . add players
	Duke duke{game_7, "Moshe"};
	Assassin assassin{game_7, "Yossi"};
	Ambassador ambassador{game_7, "Meirav"};
	Captain captain{game_7, "Reut"};
	Contessa contessa{game_7, "Gilad"};

	// basic roles test
	CHECK_EQ(duke.role(),"Duke");
	CHECK_EQ(assassin.role(),"Assassin");
	CHECK_EQ(ambassador.role(),"Ambassador");
	CHECK_EQ(captain.role(),"Captain");
	CHECK_EQ(contessa.role(),"Contessa");
}

TEST_CASE("Winner") {
	Game game_8{}; // build game . add players
	Duke duke{game_8, "Moshe"};
	CHECK_THROWS(game_8.winner());
	Assassin assassin{game_8, "Yossi"};
	Ambassador ambassador{game_8, "Meirav"};
	Captain captain{game_8, "Reut"};
	Contessa contessa{game_8, "Gilad"};

	for (int i=0 ; i<7 ; i++){
		duke.income();
		assassin.income();
		ambassador.income();
		captain.income();
		contessa.income();
	}
	// each one has 7 coins, enough for using coup()
	duke.coup(assassin);
	ambassador.coup(contessa);
	captain.coup(ambassador);

	for (int i=0 ; i<7 ; i++){
		duke.income();
		captain.income();
	}
	// each one has 7 coins, enough for using coup()
	duke.coup(captain);

	CHECK_EQ(game_8.winner(),"Moshe"); // the only one to stay in gane

}

TEST_CASE("Special Coins Abilities") {
	Game game_9{}; // build game . add players
	Duke duke{game_9, "Moshe"};
	Assassin assassin{game_9, "Yossi"};
	Ambassador ambassador{game_9, "Meirav"};
	Captain captain{game_9, "Reut"};
	Contessa contessa{game_9, "Gilad"};

	for (int i=0 ; i<9 ; i++){
		duke.income();
		assassin.income();
		ambassador.income();
		captain.income();
		contessa.income();
	}
	// each one has 9 coins
	CHECK_NOTHROW(duke.tax()); // add 3 coins
	CHECK_EQ(duke.coins(),12);
	CHECK_NOTHROW(assassin.coup(contessa)); // loss of 7 coins
	CHECK_EQ(assassin.coins(),2);
	CHECK_NOTHROW(ambassador.transfer(captain,duke)); // transfer coins
	CHECK_EQ(captain.coins(),8);
	CHECK_EQ(duke.coins(),13);
	CHECK_NOTHROW(captain.steal(assassin)); // steal coins
	CHECK_EQ(captain.coins(),10);
	CHECK_EQ(assassin.coins(),0);
}

TEST_CASE("Not his turn and Coup when more than 10 coins") {
	Game game_10{}; // build game . add players
	Duke duke{game_10, "Moshe"};
	Assassin assassin{game_10, "Yossi"};
	Ambassador ambassador{game_10, "Meirav"};
	Captain captain{game_10, "Reut"};
	Contessa contessa{game_10, "Gilad"};

	for (int i=0 ; i<9 ; i++){
		duke.income();
		assassin.income();
		ambassador.income();
		captain.income();
		contessa.income();
	}
	// each one has 9 coins
	CHECK_NOTHROW(duke.tax());
	CHECK_THROWS(captain.income()); // not her turn
	CHECK_NOTHROW(assassin.coup(contessa));
	CHECK_THROWS(captain.income()); // not her turn
	CHECK_NOTHROW(ambassador.transfer(captain,duke));
	CHECK_NOTHROW(captain.income());
	CHECK_THROWS(captain.steal(assassin)); // not her turn, already did one
	CHECK_THROWS(duke.foreign_aid()); // duke has more than 10 coins
	CHECK_NOTHROW(duke.coup(ambassador));
	CHECK_NOTHROW(assassin.foreign_aid());
	CHECK_THROWS(game_10.winner()); // game didn't end
}

TEST_CASE("Block") {
	Game game_11{}; // build game . add players
	Assassin assassin{game_11, "Yossi2"};
	Duke duke{game_11, "Moshe"};
	Assassin assassin2{game_11, "Yossi"};
	Ambassador ambassador{game_11, "Meirav"};
	Captain captain{game_11, "Reut"};
	Contessa contessa{game_11, "Gilad"};

	for (int i=0 ; i<6 ; i++){
		assassin.income();
		duke.income();
		assassin2.income();
		ambassador.income();
		captain.income();
		contessa.income();
	}
	// each one has 6 coins
	assassin.coup(ambassador); // assassin 3
	contessa.block(assassin);
	duke.tax(); //duke 9
	assassin2.foreign_aid(); // assassin2 8
	duke.block(assassin2); // assassin2 6
	ambassador.transfer(assassin,contessa); // assassin 2, contessa 7
	captain.steal(contessa); // contessa 5, captain 8
	ambassador.block(captain); // contessa 7, captain 6
	contessa.coup(duke); // contessa 0

	CHECK_EQ(assassin.coins(),2);
	CHECK_EQ(ambassador.coins(),6);
	CHECK_EQ(captain.coins(),6);
	CHECK_EQ(contessa.coins(),0);
}

TEST_CASE("steal or transfer when other have not enough coins, coup when player have not enough coins") {
	Game game_12{}; // build game . add players
	Assassin assassin{game_12, "Yossi2"};
	Duke duke{game_12, "Moshe"};
	Ambassador ambassador{game_12, "Meirav"};
	Captain captain{game_12, "Reut"};
	Contessa contessa{game_12, "Gilad"};
	// each one has 0 coins
	CHECK_THROWS(assassin.coup(duke));
	assassin.income();
	duke.tax();
	CHECK_THROWS(ambassador.transfer(captain, duke));
	ambassador.transfer(duke, contessa);
	captain.steal(contessa);
	contessa.income();

	CHECK_EQ(assassin.coins(),1);
	CHECK_EQ(duke.coins(),2);
	CHECK_EQ(ambassador.coins(),0);
	CHECK_EQ(captain.coins(),1);
	CHECK_EQ(contessa.coins(),1);
}