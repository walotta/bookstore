//
// Created by wzj on 2021/1/18.
//

#ifndef BOOKSTORE_LOG_H
#define BOOKSTORE_LOG_H
#include <iostream>
#include <string>
#include "include/FileStorage.h"

using namespace std;
class Log
{
private:
    class LogStorage
    {
    public:
        MyString name;
        MyString cmd;
        LogStorage()=default;
        explicit LogStorage(const string& _name,const string &_cmd):name(_name),cmd(_cmd){}
    };
    class Size
    {
    public:
        int n;
        explicit Size(){n=0;}
        void operator ++(int)
        {
            n++;
        }
    }size;
    StoragePool<LogStorage,Size>* storage;
public:
    Log();
    ~Log();

    void write(const string &UserName, const string &CMD);

    void print();
};
#endif //BOOKSTORE_LOG_H
