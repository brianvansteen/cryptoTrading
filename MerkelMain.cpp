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
    std::cout << "1: Print help commands:" << std::endl;

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
    std::cout << "7: Exit the trading platform!" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl << std::endl;
}

void MerkelMain::printHelp() // menu 1
{
    std::cout << "MerkleRex and Advisorbot are a trading platform." << std::endl << std::endl;
    std::cout << "The help commands are as follows below." << std::endl<<std::endl;
    std::cout << "If you want help for a specific command, enter as follow:" << std::endl;
    std::cout << "  help <cmd>" << std::endl <<std::endl;
    std::cout << "- prod:" << std::endl;
    std::cout <<"   print a list of currency trading products." << std::endl<<std::endl;
    std::cout << "- min:"<<std::endl;
    std::cout << "  find the minimum bid or minimum ask, for a specific product in the current time period." << std::endl << std::endl;
    std::cout << "- max:" << std::endl;
    std::cout << "  find the minimum bid or minimum ask, for a specific product in the current time period." << std::endl << std::endl;
    std::cout << "- avg:" << std::endl;
    std::cout << "  compute the average bid or ask, for a specific product, for a specific number of time periods." << std::endl << std::endl;
    std::cout << "- predict:" << std::endl;
    std::cout << "  predict the maximum or minimum bid or ask, for a specific product, in the next time period." << std::endl << std::endl;
    std::cout << "- my own:" << std::endl;
    std::cout << "  cccccc....... " <<std::endl <<std::endl;
    std::cout << "- time:" << std::endl;
    std::cout << "  print the current time period." << std::endl <<std::endl;
    std::cout << "- step:" << std::endl;
    std::cout << "  complete the current time period, and move to the next time period." << std::endl<<std::endl;
    std::cout << "When implementing a help command, please make sure to enter all required parameters!" << std::endl << std::endl;
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
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "You have funds to complete the ask transaction!" << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout<< "You do not have sufficient funds to complete the ask transaction!" << std::endl;
            }
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
    std::cout << "Enter product, price and amount." << std::endl;
    std::cout << "E.g. ETH/BTC,200,0.5 - with no spaces" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Bad input! Please re-enter in this format with no spaces: ETH/BTC,200,0.5" << std::endl;
    }
    else
    {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "You have funds to complete the ask transaction!" << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "You do not have sufficient funds to complete the ask transaction!" << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "MerkelMain::makeBid Bad User Input" << std::endl;
        }
    }

    std::cout << "You entered an offer of: " << input << std::endl << std::endl;
}

void MerkelMain::printWallet() // menu 5
{
    std::cout << "Your wallet is FULL!" << std::endl << std::endl;
    std::cout << "You wallet: " << wallet.toString() << std::endl;
}

void MerkelMain::continueTrade() // menu 6
{
    std::cout << "Going to next time frame." << std::endl << std::endl;

    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "Matching: " << p << std::endl << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime); // vector of OBEs sales
        std::cout << "Sales: " << sales.size() << std::endl;

        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sales price: " << sale.price << ", sales amount: " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                wallet.processSale(sale);
            }

        }
    }
    currentTime = orderBook.getNextTime(currentTime); // update time
}

int MerkelMain::userInput()
{
    int userInput = 0;
    std::string line;
    std::cout << "Make a selection from the options:" << std::endl;
    std::getline(std::cin, line);
    if (line.find("help"))
    {
        std::cout << "HELP found!" << std::endl;
    }
    try {
        userInput = std::stoi(line);
    }
    catch (const std::exception& e)
    {
        std::cout << "Please enter a valid number, not " << line << "!" << std::endl;
    }
    // std::cin >> userInput;
    std::cout << "You selected: " << userInput << std::endl <<std::endl;
    return userInput;
}

void MerkelMain::processUserInput(int userInput)
{
    if (userInput < 1) // not valid selection
    {
        std::cout << "This is not a valid selection. Please select a value from the menu." << std::endl;
    }
    else if (userInput == 1)
    {
        printHelp();
    }
    else if (userInput == 2)
    {
        exchangeStats();
    }
    else if (userInput == 3)
    {
        makeAsk();
    }
    else if (userInput == 4)
    {
        makeBid();
    }
    else if (userInput == 5)
    {
        printWallet();
    }
    else if (userInput == 6)
    {
        continueTrade();
    }
    else if (userInput == 7)
    {
        std::cout << "Exiting the program!" << std::endl << std::endl;
        exitSession();
    }
    else if (userInput > 7)
    {
        std::cout << "This is not a valid selection. Please select a value from the menu." << std::endl << std::endl;
    }
}

int MerkelMain::exitSession()
{
    exit(0);
}