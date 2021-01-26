//
// Created by wzj on 2021/1/25.
//
#include <iostream>
#include "CMD.h"

CMD bookStoreManager;
int main(){
    string cmd;
    int i=0;
    while(getline(cin,cmd))
    {
        try
        {
            i++;
            //cout<<i<<endl;
            bookStoreManager.run_command(cmd);
        }catch(const error& o)
        {
            //cout<<"Invalid\n";
            cout<<i<<' '<<o.get()<<endl;
        }
    }
    return 0;
}