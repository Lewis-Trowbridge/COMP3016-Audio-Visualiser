/**
* DO NOT MODIFY! 
* Test File for the FileReader
* A final version will be relased close to the deadline with mroe detailed tests.
*/
#pragma once 
#include <string>
#include "../Project.h" 
#include "../AudioProvider.h"
#include "../FrequencyProvider.h"
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
    
    TEST_CASE("AudioProvider gets the length of a frame from a given MP3 in seconds") {
        AudioProvider provider = AudioProvider();
        provider.openFile("media/audio/tone.mp3");
        double actual = provider.getLengthOfFrameInSeconds();
        CHECK(actual == 0.026122448979591838);
    }
}

TEST_SUITE("FrequencyProvider") {
    TEST_CASE("FrequencyProvider gets a given number of frequency buckets for a given MP3 frame") {
        // TODO: Replace this with some sample data
        AudioProvider audioProvider = AudioProvider();
        audioProvider.openFile("media/audio/tone.mp3");
        std::vector<float> actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();
        actual = audioProvider.getFrame();

        FrequencyProvider provider = FrequencyProvider();
        
        size_t buckets = 16;

        std::vector<float> result = provider.getFrequencies(&actual, buckets);
        REQUIRE(result.size() == buckets);
    }
}

TEST_SUITE("Drawer") {
    TEST_CASE("Drawer create returns valid new Mesh") {
        Drawer drawer = Drawer();
        Mesh mesh = *drawer.create();
        CHECK(mesh.vertices.size() == 0);
        CHECK(mesh.indices.size() == 0);
        CHECK(mesh.texCoords.size() == 0);
        CHECK(mesh.normals.size() == 0);
    }
}

TEST_SUITE("Mesh") {
    TEST_CASE("Mesh init from file reads vertex information correctly") {
        Drawer drawer = Drawer();
        Mesh mesh = *drawer.create();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.vertices.size() == 108);

        CHECK(mesh.vertices[0] == 1.0f);
        CHECK(mesh.vertices[1] == 1.0f);
        CHECK(mesh.vertices[2] == -1.0f);

        CHECK(mesh.vertices[105] == 1.0f);
        CHECK(mesh.vertices[106] == -1.0f);
        CHECK(mesh.vertices[107] == -1.0f);
    }

    TEST_CASE("Mesh init from file reads texture coordinate information correctly") {
        Drawer drawer = Drawer();
        Mesh mesh = *drawer.create();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.texCoords.size() == 72);

        CHECK(mesh.texCoords[0] == 0.625f);
        CHECK(mesh.texCoords[1] == 0.5f);

        CHECK(mesh.texCoords[70] == 0.375f);
        CHECK(mesh.texCoords[71] == 0.5f);
    }

    TEST_CASE("Mesh init from file reads normal information correctly") {
        Drawer drawer = Drawer();
        Mesh mesh = *drawer.create();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.normals.size() == 108);

        CHECK(mesh.normals[0] == 0.0f);
        CHECK(mesh.normals[1] == 1.0f);
        CHECK(mesh.normals[2] == 0.0f);

        CHECK(mesh.normals[105] == 0.0f);
        CHECK(mesh.normals[106] == 0.0f);
        CHECK(mesh.normals[107] == -1.0f);
    }

    TEST_CASE("Mesh init from file reads vertex index/face information correctly") {
        Drawer drawer = Drawer();
        Mesh mesh = *drawer.create();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.indices.size() == 36);

        CHECK(mesh.indices[0] == 0);
        CHECK(mesh.indices[1] == 1);
        CHECK(mesh.indices[2] == 2);

        CHECK(mesh.indices[33] == 33);
        CHECK(mesh.indices[34] == 34);
        CHECK(mesh.indices[35] == 35);
    }
}
