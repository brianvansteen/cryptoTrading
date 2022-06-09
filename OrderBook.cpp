#include "OrderBook.h"
#include "csvReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

OrderBook::OrderBook(std::string filename) // constructor reading csv data file
{
	orders = CSVReader::readCSV(filename); // vector of order book entries
}


std::vector<std::string> OrderBook::getKnownProducts() // return vector of all known products in the dataset
{
	std::vector<std::string> products;

	std::map<std::string, bool> prodMap;
 
	for (OrderBookEntry& e : orders)
	{
		prodMap[e.product] = true;
	}

	// now flatten the map to a vector of strings
	for (auto const& e : prodMap) // variable type is 'auto'
	{
		products.push_back(e.first); // first is the key
	}

	return products;
}

// return vector of Orders according to the sent filters
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> orders_sub;

	for (OrderBookEntry& e : orders)
	{
		if (e.ordertype == type &&
			e.product == product &&
			e.timestamp == timestamp)
		{
			orders_sub.push_back(e);
		}
	}

	return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
	double max = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price > max)max = e.price;
	}
	return max;
};

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price < min)min = e.price;
	}
	return min;
};