//
// Created by wzj on 2021/1/20.
//

#ifndef BOOKSTORE_ERRORMESSAGE_H
#define BOOKSTORE_ERRORMESSAGE_H

#include <stdexcept>

class error: public std::exception
{
private:
    string message;
public:
    explicit error(const string &mes):message(mes) {}
    //error(const error &o):message(o.message) {}
    string what(){return message;}
    string get()const{return message;}
};
#endif //BOOKSTORE_ERRORMESSAGE_H
