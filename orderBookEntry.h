// specification file

#pragma once // if below included once already, do not include again
#include<string>

enum class OrderBookType { bid, ask, unknown };

class OrderBookEntry // name of the class
{
public:

    OrderBookEntry(double _price,
        double _amount,
        std::string _timestamp,
        std::string _product,
        OrderBookType _ordertype);

    static OrderBookType stringToOrderBookType(std::string s);

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType ordertype;
};