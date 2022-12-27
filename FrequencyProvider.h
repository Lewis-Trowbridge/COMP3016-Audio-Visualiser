#pragma once
#include <vector>
#include <algorithm>
#include <kissfft.hh>

class FrequencyProvider {
public:
	std::vector<float> getFrequencies(std::vector<float>* data, size_t buckets);
};