cmake_minimum_required(VERSION 3.15)

project(visualiser CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(tinyfiledialogs REQUIRED)
find_package(mpg123 CONFIG REQUIRED)
find_package(unofficial-kissfft CONFIG REQUIRED)

add_executable(visualiser Project.cpp Project.h LoadShaders.cpp LoadShaders.h stb_image.h tests/doctest.h tests/tests.h "AudioProvider.h" "AudioProvider.cpp" "FrequencyProvider.h" "FrequencyProvider.cpp" models/FileReader.h models/FileReader.cpp "models/ModelDraw.h" "models/ModelDraw.cpp" "utils/utils.h" "utils/utils.cpp" "Orchestrator.h" "Orchestrator.cpp" "window/ImGUIWindow.h" "window/ImGUIWindow.cpp" "CameraMode.h")
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/media ${CMAKE_CURRENT_BINARY_DIR}/media
)
add_dependencies(visualiser copy_assets)

target_compile_features(visualiser PRIVATE cxx_std_11)

target_link_libraries(visualiser
  PRIVATE
  OpenGL::GL
  GLEW::GLEW
  GLUT::GLUT
  glfw
  glm::glm
  imgui::imgui
  tinyfiledialogs::tinyfiledialogs
  MPG123::libmpg123
  MPG123::libout123
  unofficial::kissfft::kissfft
)