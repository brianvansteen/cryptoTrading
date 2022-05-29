// cryptoTrading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include<algorithm>
#include<vector>

#include "orderBookEntry.h"
#include "MerkelMain.h"
#include "csvReader.h"


int main()
{
    MerkelMain app{};
    app.init();
    return 0;
}

//    while (true) {

//        printMenu();

//        int userSelection = userInput();

//        processUserInput(userSelection);

//    };
