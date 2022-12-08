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

// Taken from: https://stackoverflow.com/questions/3991478/building-a-32-bit-float-out-of-its-4-composite-bytes
float bytesToFloat(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3)
{
	float output;

	*((unsigned char*)(&output) + 3) = b0;
	*((unsigned char*)(&output) + 2) = b1;
	*((unsigned char*)(&output) + 1) = b2;
	*((unsigned char*)(&output) + 0) = b3;

	return output;
}

std::vector<float> AudioProvider::getFrame() {
	std::vector<unsigned char> test = std::vector<unsigned char>();
	unsigned char* audioData = test.data();
	size_t length;
	off_t offset;
	std::vector<float> mp3Data = std::vector<float>();
	err = mpg123_decode_frame(handle, &offset, &audioData, &length);
	if (err == MPG123_OK) {
		for (int i = 0; i < length; i += 4) {
			mp3Data.push_back(bytesToFloat(audioData[i], audioData[i + 1], audioData[i + 2], audioData[i + 3]));
		}
	}
	else {
		mpg123_strerror(handle);
	}
	return mp3Data;
}
