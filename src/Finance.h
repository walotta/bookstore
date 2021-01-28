//
// Created by wzj on 2021/1/18.
//

#ifndef BOOKSTORE_FINANCE_H
#define BOOKSTORE_FINANCE_H

#include "include/FileStorage.h"
class Finance
{
private:
    class FinanceStorage
    {
    public:
        double in;
        double out;
        FinanceStorage()
        {
            in=0;
            out=0;
        }
        FinanceStorage(double _in,double _out):in(_in),out(_out){}
        FinanceStorage operator-(const FinanceStorage &o)const
        {
            return FinanceStorage(in-o.in,out-o.out);
        }
        FinanceStorage operator+(const FinanceStorage &o)const
        {
            return FinanceStorage(in+o.in,out+o.out);
        }
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
        int operator -(int i) const
        {
            return n-i;
        }
        bool operator ==(int i)const
        {
            return n==i;
        }
        explicit operator int() const
        {
            return n;
        }
    }size;
    StoragePool<FinanceStorage,Size>* storage;

public:
    Finance();
    ~Finance();

    void income(double sum);
    void outcome(double sum);
    void read();
    void read(int time);
    void print();
};
#endif //BOOKSTORE_FINANCE_H
