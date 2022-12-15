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
        REQUIRE(mesh.vertices.size() == 72);

        CHECK(mesh.vertices[0] == 1.0f);
        CHECK(mesh.vertices[1] == 1.0f);
        CHECK(mesh.vertices[2] == -1.0f);

        CHECK(mesh.vertices[36] == -1.0f);
        CHECK(mesh.vertices[37] == 1.0f);
        CHECK(mesh.vertices[38] == -1.0f);
    }

    TEST_CASE("Mesh init from file reads texture coordinate information correctly") {
        Mesh mesh = Mesh();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.texCoords.size() == 48);

        CHECK(mesh.texCoords[0] == 0.625f);
        CHECK(mesh.texCoords[1] == 0.5f);

        CHECK(mesh.texCoords[46] == 0.375f);
        CHECK(mesh.texCoords[47] == 0.5f);
    }

    TEST_CASE("Mesh init from file reads texture coordinate information correctly") {
        Mesh mesh = Mesh();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.normals.size() == 18);

        CHECK(mesh.normals[0] == 0.0f);
        CHECK(mesh.normals[1] == 1.0f);
        CHECK(mesh.normals[2] == 0.0f);

        CHECK(mesh.normals[15] == 0.0f);
        CHECK(mesh.normals[16] == 0.0f);
        CHECK(mesh.normals[17] == -1.0f);
    }

    TEST_CASE("Mesh init from file reads vertex index/face information correctly") {
        Mesh mesh = Mesh();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.indices.size() == 108);

        CHECK(mesh.indices[0] == 2);
        CHECK(mesh.indices[1] == 1);
        CHECK(mesh.indices[2] == 1);

        CHECK(mesh.indices[3] == 15);
        CHECK(mesh.indices[4] == 2);
        CHECK(mesh.indices[5] == 1);

        CHECK(mesh.indices[6] == 21);
        CHECK(mesh.indices[7] == 3);
        CHECK(mesh.indices[8] == 1);

        CHECK(mesh.indices[99] == 18);
        CHECK(mesh.indices[100] == 21);
        CHECK(mesh.indices[101] == 6);

        CHECK(mesh.indices[102] == 1);
        CHECK(mesh.indices[103] == 23);
        CHECK(mesh.indices[104] == 6);

        CHECK(mesh.indices[105] == 5);
        CHECK(mesh.indices[106] == 24);
        CHECK(mesh.indices[107] == 6);
    }
}
