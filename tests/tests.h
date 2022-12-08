/**
* DO NOT MODIFY! 
* Test File for the FileReader
* A final version will be relased close to the deadline with mroe detailed tests.
*/
#pragma once 
#include <string>
#include "../Project.h" 
#include "../AudioProvider.h"
#include "../models/ModelDraw.h"
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

    TEST_CASE("AudioProvider returns an empty vector when a file has not been opened") {
        AudioProvider provider = AudioProvider();
        std::vector<float> actual = provider.getFrame();
        CHECK(actual.size() == 0);
    }
}

TEST_SUITE("Mesh") {
    TEST_CASE("Mesh init from file reads vertex information correctly") {
        Mesh mesh = Mesh();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.vertices.size() == 24);

        CHECK(mesh.vertices[0].x == 1.0f);
        CHECK(mesh.vertices[0].y == 1.0f);
        CHECK(mesh.vertices[0].z == -1.0f);

        CHECK(mesh.vertices[12].x == -1.0f);
        CHECK(mesh.vertices[12].y == 1.0f);
        CHECK(mesh.vertices[12].z == -1.0f);
    }
}
