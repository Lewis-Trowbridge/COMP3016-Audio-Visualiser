#pragma once
#include <vector>
#include <algorithm>
#include <kissfft.hh>

class FrequencyProvider {
public:
	// Returns the amount in buckets of frequencies of a given set of floats on a scale of 0-1
	std::vector<float> getFrequencies(std::vector<float>* data, size_t buckets);
};