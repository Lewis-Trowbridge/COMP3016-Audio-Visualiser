#include "utils.h"

std::vector<std::string> splitString(std::string toSplit, std::string delimiter) {
	std::vector<std::string> result = std::vector<std::string>();
	size_t end = toSplit.find(delimiter);
	while (end != std::string::npos) {
		result.push_back(toSplit.substr(0, end));
		toSplit = toSplit.substr(++end);
		end = toSplit.find(delimiter);
	}
	result.push_back(toSplit);
	return result;
}