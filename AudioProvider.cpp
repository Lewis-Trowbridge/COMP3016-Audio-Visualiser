#include "AudioProvider.h"

AudioProvider::AudioProvider() {
	lameFlags = lame_init();
	hipFlags = hip_decode_init();
}

bool AudioProvider::openFile(std::string filename) {
	std::ifstream stream(filename);
	if (stream.good()) {
		currentStream = &stream;
		return true;
	}
	return false;
}