//
// Created by wzj on 2021/1/18.
//

#include "BookManage.h"
#include <algorithm>
#include <string>
#include <sstream>

BookMange::BookMange()
{
    KeyList.emplace_back("isbn");
    KeyList.emplace_back("name");
    KeyList.emplace_back("author");
    KeyList.emplace_back("keyword");
    storage=new FileStorage<BookBlock>(KeyList,"BookMange");
}

BookMange::~BookMange()
{
    delete storage;
}

void BookMange::AddBook(int number)
{
    if(storage->HaveSelect())
    {
        BookBlock now=storage->Give();
        now.quantity+=number;
        if(now.quantity>1000000)throw error("Too many books");
        storage->Update(now);
    }else
    {
        throw error("Add Book filed because you don't select");
    }
}

void BookMange::DeleteBook(int number)
{
    if(storage->HaveSelect())
    {
        BookBlock now=storage->Give();
        now.quantity-=number;
        if(now.quantity<0)throw error("Delete Book failed because deleteNumber wrong");
        storage->Update(now);
    }else
    {
        throw error("Delete Book failed because you don't select");
    }
}

void BookMange::DeleteBook(const string &ISBN, int number)
{
    if(storage->HaveSelect())
    {
        MyString tem=(storage->Give()).keyStorage[BookBlock::isbn];
        BookMange::Select_pure(ISBN);
        BookMange::DeleteBook(number);
        BookMange::Select_pure((string)tem);
    }else
    {
        BookMange::Select_pure(ISBN);
        BookMange::DeleteBook(number);
        storage->ClearSelect();
    }
}

void BookMange::Select(const string &ISBN)
{
    vector<BookBlock> f=storage->Find("isbn",ISBN);
    if(f.empty())
    {
        BookBlock new_book;
        new_book.keyStorage[BookBlock::isbn]=ISBN;
        new_book.price=0;
        storage->Insert(new_book,ISBN);
        storage->Select(ISBN);
    }else
    {
        storage->Select(ISBN);
    }
}

void BookMange::UpdateBook(const BookBlock &newBlock)
{
    if(storage->HaveSelect())
    {
        BookBlock old;
        old=storage->Give();
        storage->Update(newBlock,(string)newBlock.keyStorage[BookBlock::isbn]);

        if(old.keyStorage[BookBlock::keyword]!=newBlock.keyStorage[BookBlock::keyword])
        {
            stringstream ss_old;
            ss_old<<old.keyStorage[BookBlock::keyword];
            string key_word_old;
            getline(ss_old,key_word_old,'|');
            while(!key_word_old.empty())
            {
                storage->RemoveKey("keyword",key_word_old);
                key_word_old="";
                getline(ss_old,key_word_old,'|');
            }


            stringstream ss;
            ss<<newBlock.keyStorage[BookBlock::keyword];
            string key_word_;
            do
            {
                getline(ss,key_word_,'|');
                storage->AddKey("keyword",key_word_);
            }while(ss.rdbuf()->in_avail());
        }
        if(old.keyStorage[BookBlock::name]!=newBlock.keyStorage[BookBlock::name])
        {
            if(old.keyStorage[BookBlock::name]!="")storage->RemoveKey("name",(string)old.keyStorage[BookBlock::name]);
            storage->AddKey("name",(string)newBlock.keyStorage[BookBlock::name]);
        }
        if(old.keyStorage[BookBlock::author]!=newBlock.keyStorage[BookBlock::author])
        {
            if(old.keyStorage[BookBlock::author]!="")storage->RemoveKey("author",(string)old.keyStorage[BookBlock::author]);
            storage->AddKey("author",(string)newBlock.keyStorage[BookBlock::author]);
        }


    }
    else throw error("update book failed because you didn't select");
}

BookBlock BookMange::GetBook()
{
    if(!storage->HaveSelect())throw error("give book failed because you didn't select");
    return storage->Give();
}

void BookMange::show()
{
    vector<BookBlock> list=storage->GiveAllBlock();
    sort(list.begin(),list.end());
    for(auto it:list)
    {
        cout<<it.keyStorage[BookBlock::isbn]<<'\t';
        cout<<it.keyStorage[BookBlock::name]<<'\t';
        cout<<it.keyStorage[BookBlock::author]<<'\t';
        cout<<it.keyStorage[BookBlock::keyword]<<'\t';
        printf("%.2f\t",it.price);
        //cout<<it.price<<'\t';
        cout<<it.quantity;
        cout<<"\n";
    }
    if(list.empty())cout<<'\n';
}

void BookMange::show(const string &keyType, const string &key)
{
    vector<BookBlock> list=storage->Find(keyType,key);
    sort(list.begin(),list.end());
    for(auto it:list)
    {
        cout<<it.keyStorage[BookBlock::isbn]<<'\t';
        cout<<it.keyStorage[BookBlock::name]<<'\t';
        cout<<it.keyStorage[BookBlock::author]<<'\t';
        cout<<it.keyStorage[BookBlock::keyword]<<'\t';
        printf("%.2f\t",it.price);
        //cout<<it.price<<'\t';
        cout<<it.quantity;
        cout<<"\n";
    }
    if(list.empty())cout<<'\n';
}

BookBlock BookMange::GetBook(const string &ISBN)
{
    BookBlock ans;
    if(storage->HaveSelect())
    {
        MyString tem=(storage->Give()).keyStorage[BookBlock::isbn];
        BookMange::Select_pure(ISBN);
        ans=BookMange::GetBook();
        BookMange::Select_pure((string)tem);
    }else
    {
        BookMange::Select_pure(ISBN);
        ans=BookMange::GetBook();
        storage->ClearSelect();
    }
    return ans;
}

void BookMange::ClearSelect()
{
    storage->ClearSelect();
}

void BookMange::removeMark(string &o)
{
    if(o[0]!='\"'||o[o.size()-1]!='\"')throw error("remove mark failed not find mark");
    string tem;
    for(int i=1;i<o.size()-1;i++)
    {
        tem.push_back(o[i]);
    }
    o=tem;
}

void BookMange::Select_pure(const string &ISBN)
{
    vector<BookBlock> f=storage->Find("isbn",ISBN);
    if(f.empty())
    {
        throw error("select not find");
    }else
    {
        storage->Select(ISBN);
    }
}
