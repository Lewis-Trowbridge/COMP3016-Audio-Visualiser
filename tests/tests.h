/**
* DO NOT MODIFY! 
* Test File for the FileReader
* A final version will be relased close to the deadline with mroe detailed tests.
*/
#pragma once 
#include <string>
#include "../Project.h" 
#include "../AudioProvider.h"
//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


TEST_SUITE("AudioProvider") {
    TEST_CASE("AudioProvider returns true when opening an existing file successfully") {
        AudioProvider provider = AudioProvider();
        CHECK(provider.openFile("media/audio/tone.mp3") == true);
    }

    TEST_CASE("AudioProvider returns false when reading a nonexistant file") {
        AudioProvider provider = AudioProvider();
        CHECK(provider.openFile("fakefile.mp3") == false);
    }

    TEST_CASE("AudioProvider returns PCM data from valid file") {
        AudioProvider provider = AudioProvider();
        provider.openFile("media/audio/tone.mp3");
        std::vector<float> actual = provider.getFrame();
        CHECK(actual.size() > 0);
    }
}
