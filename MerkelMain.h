#pragma once
class MerkelMain
{
public:
	MerkelMain();
    void init();
    void printMenu();
    void printHelp(); // menu 1
    void exchangeStats(); // menu 2
    void makeOffer(); // menu 3
    void makeBid(); // menu 4
    void printWallet(); // menu 5
    void continueTrade(); // menu 6
    int userInput();
    void processUserInput(int userSelection);
    
};
