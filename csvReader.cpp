// implementation file for csvReader

#include "csvReader.h"
#include <iostream>

CSVReader::CSVReader() // constructor
{

}


std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFile) // function implementation
{
	std::vector<OrderBookEntry> entries; // return vector of order book entries
	return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
	std::vector<std::string> tokens; // return vector of strings
	return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) // return single OBE
{
	double price, amount;
	if (tokens.size() != 5)
	{
		std::cout << "Bad line!" << std::endl;
		throw std::exception{};
	}
	try {
		price = std::stod(tokens[3]);
		amount = std::stod(tokens[4]);

	}
	catch (const std::exception& e)
	{
		std::cout << "Bad float! " << tokens[3] << std::endl;
		std::cout << "Bad float! " << tokens[4] << std::endl;
		throw;
	}

	OrderBookEntry obe{price,
						amount,
						tokens[0],
						tokens[1],
						OrderBookEntry::stringToOrderBookType(tokens[2])};
	return obe;
}