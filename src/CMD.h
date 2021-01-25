//
// Created by wzj on 2021/1/18.
//

#ifndef BOOKSTORE_CMD_H
#define BOOKSTORE_CMD_H
#include <sstream>
#include <string>
#include "Log.h"
#include "BookManage.h"
#include "Finance.h"
#include "UserManage.h"
using namespace std;
class CMD
{
private:
    Log log;
    BookMange bookManege;
    Finance finance;
    UserMange userMange;
    void hasMoreToken(stringstream &t)
    {
        string a="";
        t>>a;
        if(!a.empty())throw error("Too many token");
    }
public:
    void run_command(const string& in);

    
};
#endif //BOOKSTORE_CMD_H
