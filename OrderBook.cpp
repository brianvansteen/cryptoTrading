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
	std::vector<std::string> products; // define vector

	std::map<std::string, bool> prodMap; // dictionary 'prodMap'
 
	for (OrderBookEntry& e : orders) // from orders above, using OrderBookEntry class
	{
		// prodMap[e.timestamp] = true; // key is timestamp from OBE class; value is 'true'
		prodMap[e.product] = true; // key is product from OBE class; value is 'true'
	}

	// now flatten the map to a vector of strings
	for (auto const& e : prodMap) // variable type is 'auto'
	{
		products.push_back(e.first); // first is the key, i.e. product
	}

	return products; // function called from MerkelMain 'exchangestats' menu #2
}

// return vector of Orders according to the sent filters of type (bid or ask), product and timestamp (i.e. 'currentTime)
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> orders_sub;

	for (OrderBookEntry& e : orders)
	{
		if (e.ordertype == type && // bid or ask
			e.product == product && // for the product available
			e.timestamp == timestamp) // for specific time stamp
		{
			orders_sub.push_back(e);
		}
	}

	return orders_sub; // function called from MerkelMain 'exchangestats' menu #2
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
}

double OrderBook::getDelta(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price < min)min = e.price;
	}

	double max = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price > max)max = e.price;
	}

	return min / max;
}


std::string OrderBook::getEarliestTime()
{
	return orders[0].timestamp; // timestamp of first order
}

std::string OrderBook::getNextTime(std::string timestamp)
{
	std::string next_timestamp = "";
	for (OrderBookEntry& e : orders)
	{
		if (e.timestamp > timestamp)
		{
			next_timestamp = e.timestamp;
				break;
		}
	}
	if (next_timestamp == "")
	{
		next_timestamp = orders[0].timestamp; // timestamp of first order
	}
	return next_timestamp; // used for 'currentTime'
};