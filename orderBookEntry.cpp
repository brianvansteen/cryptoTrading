// implementation file

#include "orderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _ordertype)

    :price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    ordertype{ _ordertype }
{

}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    if (s == "bid")
    {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}