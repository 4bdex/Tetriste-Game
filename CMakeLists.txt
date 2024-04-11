cmake_minimum_required(VERSION 3.16)
project(Tetriste LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/bin)


add_executable(Tetriste src/main.cpp src/MainMenuScreen.cpp src/GameOverScreen.cpp src/Game.cpp src/GameBoard.cpp src/ShapeLibrary.cpp src/LeaderBoardScreen.cpp src/PauseScreen.cpp src/DifficultyScreen.cpp src/ControlsScreen.cpp)
target_include_directories(Tetriste PRIVATE src/headers)
target_link_libraries(Tetriste PRIVATE sfml-graphics sfml-window)
target_compile_features(Tetriste PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Tetriste
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Tetriste>
        VERBATIM)
endif()

install(TARGETS Tetriste)