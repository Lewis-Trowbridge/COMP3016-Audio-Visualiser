#include "AudioProvider.h"

AudioProvider::AudioProvider() {
	err = 0;
	handle = mpg123_new(NULL, &err);
	mpg123_param(handle, MPG123_REMOVE_FLAGS, MPG123_IGNORE_INFOFRAME, 0.);
}

bool AudioProvider::openFile(std::string filename) {
	err = mpg123_open_fixed(handle, filename.c_str(), MPG123_STEREO, MPG123_ENC_FLOAT_32);
	return err == MPG123_OK;
}

std::vector<float> AudioProvider::getFrame() {
	std::vector<float> mp3Data = std::vector<float>();
	// Assign pointer to memory so that we can make a pointer to it
	float* disposablePointer;
	size_t returnedByteLength;
	off_t offset;
	// Read data while casting to unsigned char pointer to read/reinterpret memory as floats directly
	err = mpg123_decode_frame(handle, &offset, (unsigned char**)&disposablePointer, &returnedByteLength);
	if (err == MPG123_OK) {
		// Create new vector containing data 
		mp3Data = std::vector<float>(disposablePointer, disposablePointer + returnedByteLength / sizeof(float));
	}
	return mp3Data;
}

double AudioProvider::getLengthOfFrameInSeconds() {
	return mpg123_tpf(handle);
}
