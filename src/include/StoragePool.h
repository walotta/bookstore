//
// Created by wzj on 2021/1/18.
//

#ifndef BOOKSTORE_STORAGEPOOL_H
#define BOOKSTORE_STORAGEPOOL_H

#include <iostream>
#include <fstream>
using namespace std;

template<class T>
class StoragePool
{
private:
    int WritePoint=-1;//块编号从0开始，-1说明需要写入新块
    int LastBlock=-1;//文件中的最后一块
    fstream pool;
    const int base=2*sizeof(int);
    const string dir="StorageFile/";
    const string StorageFileName;

public:
    StoragePool()=delete;

    explicit StoragePool(const string& FileName):StorageFileName(FileName)
    {
        pool.open(dir+FileName,fstream::in|fstream::out|ios::binary);
        if(pool.fail())
        {
            pool.open(dir+FileName,fstream::out|ios::binary);
            pool.close();
            pool.open(dir+FileName,fstream::in|fstream::out|ios::binary);
            pool.seekp(0,ios::beg);
            WritePoint=-1;
            LastBlock=-1;
            pool.write(reinterpret_cast<const char*>(&WritePoint),sizeof(int));
            pool.write(reinterpret_cast<const char*>(&LastBlock),sizeof(int));
        }else
        {
            pool.seekg(0,ios::beg);
            pool.read(reinterpret_cast<char*>(&WritePoint),sizeof(int));
            pool.read(reinterpret_cast<char*>(&LastBlock),sizeof(int));
        }
    }

    ~StoragePool()
    {
        pool.seekp(0,ios::beg);
        pool.write(reinterpret_cast<const char*>(&WritePoint),sizeof(int));
        pool.write(reinterpret_cast<const char*>(&LastBlock),sizeof(int));
        pool.close();
    }

    int add(const T &block)
    {
        int ans;
        if(WritePoint==-1)
        {
            LastBlock++;
            ans=LastBlock;
            pool.seekp(0,ios::end);
            pool.write(reinterpret_cast<const char*>(&block),sizeof(T));
        }else
        {
            int tem;
            ans=WritePoint;
            pool.seekg(base+WritePoint*sizeof(T),ios::beg);
            pool.read(reinterpret_cast<char*>(&tem),sizeof(int));
            pool.seekp(base+WritePoint*sizeof(T),ios::beg);
            pool.write(reinterpret_cast<const char*>(&block),sizeof(T));
            WritePoint=tem;
        }
        return ans;
    }

    void remove(int id)
    {
        pool.seekp(base+id*sizeof(T),ios::beg);
        pool.write(reinterpret_cast<const char*>(&WritePoint),sizeof(int));
        WritePoint=id;
    }

    void update(int id,const T &block)
    {
        pool.seekp(base+id*sizeof(T),ios::beg);
        pool.write(reinterpret_cast<const char*>(&block),sizeof(T));
    }

    T get(int id)
    {
        T tem;
        pool.seekg(base+id*sizeof(T),ios::beg);
        pool.read(reinterpret_cast<char*>(&tem),sizeof(T));
        return tem;
    }

    void clearAll()
    {
        pool.close();
        pool.open(dir+StorageFileName,ios::out|ios::binary);
        pool.close();
        pool.open(dir+StorageFileName,ios::in|ios::out|ios::binary);
        WritePoint=-1;
        LastBlock=-1;
        pool.seekp(0,ios::beg);
        pool.write(reinterpret_cast<const char*>(&WritePoint),sizeof(int));
        pool.write(reinterpret_cast<const char*>(&LastBlock),sizeof(int));
    }

    int tellSpace()
    {
        return LastBlock;
    }
};

#endif //BOOKSTORE_STORAGEPOOL_H
