#include "FrequencyProvider.h"

std::vector<float> FrequencyProvider::getFrequencies(std::vector<float>* data, size_t buckets) {
	
	size_t dataLength = data->size();
	kissfft<float> fft(buckets, false);
	std::vector<std::complex<float>> complexVector = std::vector<std::complex<float>>();
	complexVector.resize(buckets);
	
	fft.transform_real(data->data(), complexVector.data());

	std::vector<float> bucketVector = std::vector<float>();

	// Get intensities in each bucket band
	// We are getting the magnitude, which is what we need to get intensities in each band:
	// https://stackoverflow.com/questions/10304532/why-does-fft-produce-complex-numbers-instead-of-real-numbers
	for (size_t i = 0; i < buckets; i++) {
		bucketVector.push_back(std::abs(complexVector[i]));
	}
	// Noramlise the values from 0 to 1
	float max = *std::max_element(bucketVector.cbegin(), bucketVector.cend());
	for (size_t i = 0; i < buckets; i++) {
		
		bucketVector[i] = bucketVector[i] / max;
	}


	return bucketVector;
}
