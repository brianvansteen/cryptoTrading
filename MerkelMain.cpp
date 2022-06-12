// implementation file

#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "orderBookEntry.h"
#include "csvReader.h"

MerkelMain::MerkelMain() // constructor is for creating instance of object and ensure it is ready to be used
{

}

void MerkelMain::init() // start the object running
{
    // loadOrderBook(); // call function
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = userInput(); // 1 - 7
        processUserInput(input); // 1 - 7
    }
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

    std::cout << "=======================================" << std::endl << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl << std::endl;
}

void MerkelMain::printHelp() // menu 1
{
    std::cout << "This is a trading platform." << std::endl << std::endl;
}

void MerkelMain::exchangeStats() // menu 2
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl; // what are the products; timestamps also works
        
        // std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, "2020/03/17 17:01:24.884492");
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

        std::cout << "Asks seen: " << entries.size() << std::endl;

        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Delta is: " << OrderBook::getDelta(entries) << std::endl;
        // std::cout << "Delta is: " << OrderBook::getLowPrice(entries) / OrderBook::getHighPrice(entries) << std::endl;
        std::cout << std::endl;
    }

    //std::cout << "Market is volatile." << std::endl << std::endl;
    //std::cout << "The order book contains: " << orders.size() << " entries." << std::endl << std::endl;
    ////std::cout << "Order book contains: " <<std::endl;
    //unsigned int bids = 0;
    //unsigned int asks = 0;
    //for (OrderBookEntry& e : orders) // interate over orders
    //{
    //    if (e.ordertype == OrderBookType::ask)
    //    {
    //        asks++;
    //    }
    //    if (e.ordertype == OrderBookType::bid)
    //    {
    //        bids++;
    //    }
    //}
    //std::cout << "OrderBook asks: " << asks << std::endl;
    //std::cout << "OrderBook bids: " << bids << std::endl << std::endl;
}

void MerkelMain::makeAsk() // menu 3
{
    std::cout << "Make an offer (ask)." << std::endl;
    std::cout << "Enter product, price and amount." << std::endl;
    std::cout << "E.g. ETH/BTC,200,0.5 - with no spaces" << std::endl;
    std::string input;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Bad input! Please re-enter in this format with no spaces: ETH/BTC,200,0.5" << std::endl;
    }
    else
    {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            orderBook.insertOrder(obe);
        }
        catch (const std::exception & e)
        {
            std::cout << "MerkelMain::makeAsk Bad User Input" << std::endl;
        }
    }

    std::cout << "You entered an offer of: " << input << std::endl << std::endl;

}

void MerkelMain::makeBid() // menu 4
{
    std::cout << "Make a bid." << std::endl << std::endl;
}

void MerkelMain::printWallet() // menu 5
{
    std::cout << "Your wallet is FULL!" << std::endl << std::endl;
    std::cout << "You wallet: " << wallet.toString() << std::endl;
}

void MerkelMain::continueTrade() // menu 6
{
    std::cout << "Going to next time frame." << std::endl << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime); // vector of OBEs sales
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales)
    {
        std::cout << "Sales price: " << sale.price << ", sales amount: " << sale.amount << std::endl;
    }
    currentTime = orderBook.getNextTime(currentTime); // update time
}

int MerkelMain::userInput()
{
    int userSelection = 0;
    std::string line;
    std::cout << "Make a selection from the options:" << std::endl;
    std::getline(std::cin, line);
    try {
        userSelection = std::stoi(line);
    }
    catch (const std::exception& e)
    {
        std::cout << "Please enter a valid number, not " << line << "!" << std::endl;
    }
    // std::cin >> userSelection;
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
        makeAsk();
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