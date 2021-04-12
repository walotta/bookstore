//
// Created by wzj on 2021/1/18.
//

#ifndef BOOKSTORE_BOOKMANAGE_H
#define BOOKSTORE_BOOKMANAGE_H
#include "include/FileStorage.h"

class BookBlock
{
public:
    enum KeyType{isbn,name,author,keyword};
    MyString keyStorage[4];
    double price=-1;
    int quantity=0;
    bool operator<(const BookBlock& o)
    {
        return keyStorage[isbn]<o.keyStorage[isbn];
    }
};

class BookMange
{
private:
    FileStorage<BookBlock>* storage;
    vector<string> KeyList;
    void removeMark(string &o);

public:
    BookMange();
    ~BookMange();

    //添加选中的书的指定数量
    void AddBook(int number);

    //删除选中的书的指定数目
    void DeleteBook(int number);

    //删除ISBN指定的书的指定数量
    void DeleteBook(const string& ISBN,int number);

    //选中书本，若无则创建
    int Select(const string& ISBN);

    void Select(int id);

    //删除选中的原书数据，换为新数据,同时更新索引
    void UpdateBook(const BookBlock& newBlock);

    //返回选中的块对象
    BookBlock GetBook();

    BookBlock GetBook(const string& ISBN);

    //展示所有书,cout输出
    void show();

    //根据key展示所有书，cout输出
    void show(const string& keyType,const string& key);

    void ClearSelect();

    void Select_pure(const string& ISBN);

};
#endif //BOOKSTORE_BOOKMANAGE_H
