#pragma once
#include <mpg123.h>
#include <vector>
#include <string>
#include <fstream>

class AudioProvider {
private:
	mpg123_handle* handle;
	int err;
public:
	AudioProvider();
	// Opens a file and returns true if it was successful, false if it was not.
	bool openFile(std::string filename);
	// Returns an MP3 frame of an opened file and moves the position one frame forward. Returns an empty vector if playback has reached the end of the file.
	std::vector<float> getFrame();
	// Returns the length of a single frame in seconds.
	double getLengthOfFrameInSeconds();
};