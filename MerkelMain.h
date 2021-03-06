// specification file

#pragma once // if below class included once already, do not include again; otherwise class called every time 'include' written
#include <vector>
#include "orderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain // class definition
{
public:
	MerkelMain(); // constructor

    /*** call this to start the simulation */
    void init(); // call this to start the simulation

private:
    //void loadOrderBook();
    void printMenu();
    void printHelp(); // menu 1
    void exchangeStats(); // menu 2
    void makeAsk(); // menu 3
    void makeBid(); // menu 4
    void printWallet(); // menu 5
    void continueTrade(); // menu 6
    int userInput();
    void processUserInput(int userSelection);

    std::string currentTime;

    int exitSession();

    OrderBook orderBook{ "20200317.csv" };
    //std::vector<OrderBookEntry> orders; // private but object scope

    Wallet wallet;
};

