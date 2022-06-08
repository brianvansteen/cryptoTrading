// specification file for constructors

#pragma once // if below class included once already, do not include again
#include "orderBookEntry.h"
#include <vector>
#include <string>


class CSVReader // new class
{
	public: // constructor
		CSVReader();
		// stateless function, so can be static, since no state needed for constructor
		static std::vector<OrderBookEntry> readCSV(std::string csvFile); // takes as argument csvFile; return vector of OBE objects

	private:
		static std::vector<std::string> tokenise(std::string csvLine, char separator); // tokenise function
		static OrderBookEntry stringsToOBE(std::vector<std::string> strings); // vector of strings from tokenise and convert to OBE
};

