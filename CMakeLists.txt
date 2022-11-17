cmake_minimum_required(VERSION 3.15)

project(visualiser CXX)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(tinyfiledialogs REQUIRED)

add_executable(visualiser Project.cpp Project.h LoadShaders.cpp LoadShaders.h stb_image.h tests/doctest.h tests/tests.h)
target_compile_features(visualiser PRIVATE cxx_std_11)

target_link_libraries(visualiser
  PRIVATE
  GLEW::GLEW
  GLUT::GLUT
  glfw
  glm::glm
  tinyfiledialogs::tinyfiledialogs)