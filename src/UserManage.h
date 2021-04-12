//
// Created by wzj on 2021/1/18.
//

#ifndef BOOKSTORE_USERMANAGE_H
#define BOOKSTORE_USERMANAGE_H

#include <stack>
#include "include/FileStorage.h"
#include "UserLog.h"
#include "unordered_set"

using namespace std;
class UserMange
{
private:
    class UserStorage
    {
    public:
        MyString name;
        MyString other_name;
        int privilege;
        MyString psd;
    };
    class State
    {
    public:
        UserStorage user;
        //string selectBookName;
        int selectBook;
    };
    FileStorage<UserStorage>* storage;
    UserLog *logManage;
    stack<State> stateStorage;
    unordered_set<string> memory;
    State now;
public:
    UserMange();
    ~UserMange();
    void Login(const string &name,const string& psd);
    void Logout();
    void UserAdd(const string &name,const string& psd,int pri,const string& other_name);
    void DeleteUser(const string& name);
    void ResetPasswd(const string &name, const string &old_psd,const string &new_psd);
    int NowPrivilege() const;
    string NowUserName() const;
    void ShowLog();
    void ShowLog(const string& username);
    void AskPrivilege(int pri) const;
    void WriteLog(const string& CMD);
    void ChangeSelectBook(int selectId);
    int GiveSelectBook() const;
};
#endif //BOOKSTORE_USERMANAGE_H
