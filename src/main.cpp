//
// Created by wzj on 2021/1/25.
//
#include <iostream>
#include "CMD.h"

int main(){
    CMD bookStoreManager;
    string cmd;
    while(getline(cin,cmd))
    {
        try
        {
            bookStoreManager.run_command(cmd);
        }catch(const error& o)
        {
            cout<<"Invalid\n";
        }
    }
    return 0;
}