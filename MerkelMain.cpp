// implementation file

#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "orderBookEntry.h"

MerkelMain::MerkelMain() // constructor is for creating instance of object and ensure it is ready to be used
{

}

void MerkelMain::init() // start the object running
{
    loadOrderBook();
    int input;
    while (true)
    {
        printMenu();
        input = userInput(); // 1 - 7
        processUserInput(input); // 1 - 7
    }
}

void MerkelMain::loadOrderBook()
{
    orders.push_back(OrderBookEntry{ 10302,
        0.0051824,
        "2020/03/17 17:04:02.2234",
        "BTC/USDT",
        OrderBookType::bid });

    orders.push_back(OrderBookEntry{ 12302,
        0.0081824,
        "2020/03/17 17:08:02.2234",
        "BTC/USDT",
        OrderBookType::ask });

    orders.push_back(OrderBookEntry{ 15751,
        0.021824,
        "2020/03/17 17:18:02.2234",
        "BTC/USDT",
        OrderBookType::ask });
}


/* print the user menu */
void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help:" << std::endl;

    // 2 print exchange statistics
    std::cout << "2: Print exchange statistics:" << std::endl;

    // 3 make a trade offer
    std::cout << "3: Make a trade offer: " << std::endl;

    // 4 make a trade bid
    std::cout << "4: Make a trade bid:" << std::endl;

    // 5 print wallet contents
    std::cout << "5: Print contents of wallet:" << std::endl;

    // 6 continue time line
    std::cout << "6: continue in timeline:" << std::endl;

    // 7 exit
    std::cout << "7: exiting!" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl;
}

void MerkelMain::printHelp() // menu 1
{
    std::cout << "This is a trading platform." << std::endl << std::endl;
}

void MerkelMain::exchangeStats() // menu 2
{
    std::cout << "Market is volatile." << std::endl << std::endl;
    std::cout << "The order book contains: " << orders.size() << " entries." << std::endl << std::endl;
}

void MerkelMain::makeOffer() // menu 3
{
    std::cout << "Make an offer." << std::endl << std::endl;
}

void MerkelMain::makeBid() // menu 4
{
    std::cout << "Make a bid." << std::endl << std::endl;
}

void MerkelMain::printWallet() // menu 5
{
    std::cout << "Your wallet is FULL!" << std::endl << std::endl;
}

void MerkelMain::continueTrade() // menu 6
{
    std::cout << "Going to next time frame." << std::endl << std::endl;
}

int MerkelMain::userInput()
{
    int userSelection;
    std::cout << "Make a selection from the options:" << std::endl;
    std::cin >> userSelection;
    std::cout << "You selected: " << userSelection << std::endl;
    return userSelection;
}

void MerkelMain::processUserInput(int userSelection)
{
    if (userSelection < 1) // not valid selection
    {
        std::cout << "This is not a valid selection. Please select a value from the menu." << std::endl;
    }
    else if (userSelection == 1)
    {
        printHelp();
    }
    else if (userSelection == 2)
    {
        exchangeStats();
    }
    else if (userSelection == 3)
    {
        makeOffer();
    }
    else if (userSelection == 4)
    {
        makeBid();
    }
    else if (userSelection == 5)
    {
        printWallet();
    }
    else if (userSelection == 6)
    {
        continueTrade();
    }
    else if (userSelection > 7) // not valid selection
    {
        std::cout << "This is not a valid selection. Please select a value from the menu." << std::endl << std::endl;
    }
}