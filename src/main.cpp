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
            //cout<<'#'<<i<<' '<<cmd<<endl;
            //bookStoreManager.showPri();
            bookStoreManager.run_command(cmd);
            //cout<<" ! "<<endl;
            //bookStoreManager.sudo_show();
        }catch(const error& o)
        {
            //cout<<"Invalid\n";
            cout<<i<<' '<<o.get()<<endl;
        }
    }
    return 0;
}