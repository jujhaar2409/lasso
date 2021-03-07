cmake_minimum_required(VERSION 3.17)
project(lasso)

set(CMAKE_CXX_STANDARD 14)

include_directories(.
        /Users/jujhaar/code/downloads/simplecpp/include
        /opt/X11/include)

add_executable(lasso
        coin.cpp
        coin.h
        display.cpp
        display.h
        lasso.cpp
        lasso.h
        random.cpp
        random.h
        constants.h
        main.cpp
        MovingObject.cpp
        MovingObject.h
        game.cpp
        game.h
        timing.h)
