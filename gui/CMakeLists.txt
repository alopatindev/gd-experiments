cmake_minimum_required(VERSION 2.8)

project(hello)

add_definitions(-std=c++0x -g)

#set(CMAKE_MODULE_PATH  ${PROJECT_SOURCE_DIR}/cmake-extensions/ )
find_package(PkgConfig)

pkg_check_modules(CLANLIB clanCore-2.3 clanDisplay-2.3 clanGL1-2.3 clanApp-2.3
clanSWRender-2.3)

link_directories(
    ${CLANLIB_LIBRARY_DIRS}
)
include_directories(
    ${CLANLIB_INCLUDE_DIRS}
)

add_executable(hello
    hello.cpp
    MyMainWindow.cpp
    MyMainWindow.h
    ui/Widget.cpp
    ui/MainWindow.cpp
    ui/Button.cpp
    ui/MainWindow.h
    ui/Widget.h
    ui/Button.h
    libs/Singleton.h
    libs/String.h
    libs/String.cpp
    libs/DeviceScreen.cpp
    libs/ResourceManager.h
    libs/DeviceScreen.h
    libs/sigslot.h
    graphics/geometry.h
    graphics/Sprite.cpp
    graphics/Sprite.h
    graphics/geometry.cpp
)

target_link_libraries(hello
    ${CLANLIB_LIBRARIES}
)
