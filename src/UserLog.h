//
// Created by wzj on 2021/1/25.
//

#ifndef LOCAL_TEST_USERLOG_H
#define LOCAL_TEST_USERLOG_H
#include <iostream>
#include <string>
#include "include/FileStorage.h"

using namespace std;
class UserLog
{
private:
    class LogStorage
    {
    public:
        MyString name;
        MyString cmd;
        LogStorage()= default;
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

    UserLog();

    ~UserLog();

    void write(const string& UserName,const string& CMD);

    void print(const string& UserName);
};
#endif //LOCAL_TEST_USERLOG_H
