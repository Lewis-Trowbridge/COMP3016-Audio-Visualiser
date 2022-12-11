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

    TEST_CASE("Mesh init from file reads texture coordinate information correctly") {
        Mesh mesh = Mesh();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.texCoords.size() == 24);

        CHECK(mesh.texCoords[0].x == 0.625f);
        CHECK(mesh.texCoords[0].y == 0.5f);

        CHECK(mesh.texCoords[23].x == 0.375f);
        CHECK(mesh.texCoords[23].y == 0.5f);
    }

    TEST_CASE("Mesh init from file reads texture coordinate information correctly") {
        Mesh mesh = Mesh();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.normals.size() == 6);

        CHECK(mesh.normals[0].x == 0.0f);
        CHECK(mesh.normals[0].y == 1.0f);
        CHECK(mesh.normals[0].z == 0.0f);

        CHECK(mesh.normals[5].x == 0.0f);
        CHECK(mesh.normals[5].y == 0.0f);
        CHECK(mesh.normals[5].z == -1.0f);
    }

    TEST_CASE("Mesh init from file reads vertex index/face information correctly") {
        Mesh mesh = Mesh();
        mesh.initFromFile("media/models/cube.obj");
        REQUIRE(mesh.indices.size() == 36);

        CHECK(mesh.indices[0].x == 2);
        CHECK(mesh.indices[0].y == 1);
        CHECK(mesh.indices[0].z == 1);

        CHECK(mesh.indices[1].x == 15);
        CHECK(mesh.indices[1].y == 2);
        CHECK(mesh.indices[1].z == 1);

        CHECK(mesh.indices[2].x == 21);
        CHECK(mesh.indices[2].y == 3);
        CHECK(mesh.indices[2].z == 1);

        CHECK(mesh.indices[33].x == 18);
        CHECK(mesh.indices[33].y == 21);
        CHECK(mesh.indices[33].z == 6);

        CHECK(mesh.indices[34].x == 1);
        CHECK(mesh.indices[34].y == 23);
        CHECK(mesh.indices[34].z == 6);

        CHECK(mesh.indices[35].x == 5);
        CHECK(mesh.indices[35].y == 24);
        CHECK(mesh.indices[35].z == 6);
    }
}
