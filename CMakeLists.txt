cmake_minimum_required(VERSION 4.1)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)

add_executable(ImageProcessing main.cpp
        classes/Size.h
        classes/Size.cpp
        classes/Point.h
        classes/Point.cpp
        classes/Rectangle.h
        classes/Rectangle.cpp
        classes/Image.cpp
        classes/Image.h
        "classes/ImageProcessing.h"
        classes/ImageProcessing.cpp
        classes/Drawing.h
        classes/Drawing.cpp)
