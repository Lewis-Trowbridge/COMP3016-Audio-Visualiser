#pragma once
#include <vector>
#include <fftwpp/fftw++.h>

class FrequencyProvider {
public:
	FrequencyProvider();
	std::vector<int> getFrequencies(size_t size);
};