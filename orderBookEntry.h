// header file is the specification file; not how class works, only how to use it

#pragma once // if below class included once already, do not include again
#include<string>

enum class OrderBookType { bid, ask, unknown };

class OrderBookEntry // namespace of the class OrderBookEntry
{
public:
    // specify constructor since already in the class
    OrderBookEntry(double _price,
        double _amount,
        std::string _timestamp,
        std::string _product,
        OrderBookType _ordertype);

    // static - non-changing
    static OrderBookType stringToOrderBookType(std::string s); // function converts from string to OrderBookType enum, string as argument

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType ordertype;
};