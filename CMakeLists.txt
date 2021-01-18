cmake_minimum_required(VERSION 3.17)
project(bookstore)

set(CMAKE_CXX_STANDARD 14)

add_executable(bookstore
        src/main.cpp
        src/include/BPlusTree.hpp
        src/include/FileStorage.hpp
        src/include/StoragePool.hpp
        src/BookManage.cpp
        src/BookManage.h
        src/UserManage.cpp
        src/UserManage.h
        src/CMD.cpp
        src/CMD.h
        src/Log.cpp
        src/Log.h
        src/Finance.cpp
        src/Finance.h)