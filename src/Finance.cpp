//
// Created by wzj on 2021/1/18.
//

#include "Finance.h"

Finance::Finance()
{
    storage=new StoragePool<FinanceStorage,Size>("FinanceStorage");
    size=storage->readExtraBlock();
}

Finance::~Finance()
{
    storage->writeExtraBlock(size);
    delete storage;
}

void Finance::income(double sum)
{
    storage->add(storage->get(size-1)+FinanceStorage(sum,0));
    size++;
}

void Finance::outcome(double sum)
{
    storage->add(storage->get(size-1)+FinanceStorage(0,sum));
    size++;
}

void Finance::read()
{
    FinanceStorage now=storage->get(size-1);
    printf("+ %.2f - %.2f",now.in,now.out);
}

void Finance::read(int time)
{
    FinanceStorage now=storage->get(size-1);
    FinanceStorage before=storage->get(size-time-1);
    now=now-before;
    printf("+ %.2f - %.2f",now.in,now.out);
}

void Finance::print()
{
    cout<<"[Finance print]"<<endl;
    for(int i=1;i<=size-1;i++)
    {
        FinanceStorage now=storage->get(i-1);
        FinanceStorage before=storage->get(i);
        now=now-before;
        printf("+ %.2f - %.2f",now.in,now.out);
    }
    cout<<"[Finance print finished]"<<endl;
}
