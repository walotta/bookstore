//
// Created by wzj on 2021/1/18.
//

#include "Log.h"

Log::Log()
{
    storage=new StoragePool<LogStorage,Size>("Log.dat");
    size=storage->readExtraBlock();
}

Log::~Log()
{
    storage->writeExtraBlock(size);
    delete storage;
}

void Log::write(const string &UserName, const string &CMD)
{
    storage->add(LogStorage(UserName,CMD));
    size++;
}

void Log::print()
{
    MyString tem_name;
    cout<<"[log of all]\n";
    for(int i=0;i<size.n;i++)
    {
        LogStorage tem=storage->get(i);
        if(tem_name=="")tem_name=tem.name;
        if(tem.name==tem_name)
        {
            cout<<'\t'<<tem.cmd<<'\n';
        }else
        {
            cout<<"change User to "<<tem.name<<"\n";
            cout<<'\t'<<tem.cmd<<'\n';
            tem_name=tem.name;
        }
    }
    cout<<"[log of all finished]\n";
}
