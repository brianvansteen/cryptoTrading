#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>


class OrderBook
{
public:
	OrderBook(std::string filename); // constructor reading csv data file

	std::vector<std::string> getKnownProducts(); // return vector of all known products in the dataset
	
	// return vector of Orders according to the sent filters
	std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

	static double getHighPrice(std::vector<OrderBookEntry>& orders);
	static double getLowPrice(std::vector<OrderBookEntry>& orders);
	
private:
	std::vector<OrderBookEntry> orders;
};

