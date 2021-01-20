//
// Created by wzj on 2021/1/20.
//

#ifndef BOOKSTORE_ERRORMESSAGE_H
#define BOOKSTORE_ERRORMESSAGE_H
#include <exception>
class error: public std::exception
{
private:
    string message;
public:
    error(string mes):std::exception(),message(mes) {}
    string what(){return message;}
};
#endif //BOOKSTORE_ERRORMESSAGE_H
