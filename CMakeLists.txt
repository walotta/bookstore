cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code
        src/main.cpp
        src/include/BPlusTree.h
        src/include/FileStorage.h
        src/include/StoragePool.h
        src/BookManage.cpp
        src/BookManage.h
        src/UserManage.cpp
        src/UserManage.h
        src/CMD.cpp
        src/CMD.h
        src/Log.cpp
        src/Log.h
        src/Finance.cpp
        src/Finance.h
        src/include/ErrorMessage.h
        src/UserLog.cpp
        src/include/HashMap.h
        src/include/HashMap.cpp
        src/include/MyString.hpp
        src/include/cache.hpp)