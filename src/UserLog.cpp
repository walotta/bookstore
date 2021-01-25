//
// Created by wzj on 2021/1/25.
//

#include "UserLog.h"

UserLog::UserLog()
{
    storage=new StoragePool<LogStorage,Size>("UserLog.dat");
    size=storage->readExtraBlock();
}

UserLog::~UserLog()
{
    storage->writeExtraBlock(size);
    delete storage;
}

void UserLog::write(const string &UserName, const string &CMD)
{
    storage->add(LogStorage(UserName,CMD));
    size++;
}

void UserLog::print(const string &UserName)
{
    cout<<"[log of "<<UserName<<"]\n";
    for(int i=0;i<size.n;i++)
    {
        LogStorage tem=storage->get(i);
        if(tem.name==UserName)
        {
            cout<<'\t'<<tem.cmd<<'\n';
        }
    }
    cout<<"[log of "<<UserName<<" finished]\n";
}
