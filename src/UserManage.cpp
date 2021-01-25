//
// Created by wzj on 2021/1/18.
//

#include "UserManage.h"

UserMange::UserMange()
{
    storage=new FileStorage<UserStorage>(vector<string>(1,"user"),"UserManage");
    if(storage->empty())
    {
        UserStorage root;
        root.name="root";
        root.privilege=7;
        root.psd="sjtu";
        storage->Insert(root,"root");
    }
    logManage=new UserLog;
    now.user.privilege=0;
}

UserMange::~UserMange()
{
    delete storage;
    delete logManage;
}

void UserMange::Login(const string &name, const string &psd)
{
    vector<UserStorage> tem;
    tem=storage->Find("user",name);
    if(tem.empty())throw error("login user name not find");
    if(psd.empty())
    {
        if(now.user.privilege<=tem[0].privilege)throw error("please enter psd");
    }else
    {
        if(psd!=tem[0].psd)throw error("psd error");
    }
    now.selectBookName="";
    now.user=tem[0];
    stateStorage.push(now);
    memory.insert(name);
    logManage->write((string)now.user.name,"Login");
}

void UserMange::Logout()
{
    if(stateStorage.empty())throw error("logout failed because you didn't Login");
    stateStorage.pop();
    memory.erase((string)now.user.name);
    if(stateStorage.empty())
    {
        now.user.privilege=0;
    }else
    {
        now=stateStorage.top();
    }
    logManage->write((string)now.user.name,"Logout");
}

void UserMange::UserAdd(const string &name, const string &psd, int pri,const string& other_name)
{
    if(pri==1||pri<now.user.privilege)
    {
        if(storage->Find("user",name).empty())
        {
            UserStorage newUser;
            newUser.name=name;
            newUser.privilege=pri;
            newUser.psd=psd;
            newUser.other_name=other_name;
            storage->Insert(newUser,name);
        }else
        {
            throw error("user exited cannot add");
        }
    }else
    {
        throw error("cannot add higher pri user");
    }
    logManage->write((string)now.user.name,"add user "+name+' '+other_name);
}

void UserMange::DeleteUser(const string &name)
{
    if(now.user.privilege!=7)throw error("only delete user in root");
    vector<UserStorage> tem;
    tem=storage->Find("user",name);
    if(tem.empty())throw error("user not find when delete");
    if(tem[0].privilege==7)throw error("cannot delete root");
    if(memory.count(name))
    {
        throw error("delete user is active");
    }else
    {
        storage->Delete(name);
    }
    logManage->write((string)now.user.name,"delete user "+name);
}

void UserMange::ResetPasswd(const string &name, const string &old_psd,const string &new_psd)
{
    vector<UserStorage> tem;
    tem=storage->Find("user",name);
    if(tem.empty())throw error("psd change user name not find");
    if(old_psd.empty())
    {
        if(now.user.privilege!=7)throw error("please enter old psd");
    }else
    {
        if(tem[0].psd!=old_psd)throw error("old psd wrong");
    }
    tem[0].psd=new_psd;
    storage->Update(tem[0],name);
    logManage->write((string)now.user.name,"reset passed of "+name);
}

int UserMange::NowPrivilege() const
{
    return now.user.privilege;
}

string UserMange::NowUserName() const
{
    return std::string(now.user.name);
}

void UserMange::ShowLog()
{
    logManage->write((string)now.user.name,"Show Log");
    logManage->print(string(now.user.name));
}

void UserMange::ShowLog(const string &username)
{
    logManage->write((string)now.user.name,"Show Log of "+username);
    logManage->print(username);
}

bool UserMange::AskPrivilege(int pri) const
{
    if(pri<now.user.privilege)return true;
    return false;
}

void UserMange::WriteLog(const string &CMD)
{
    logManage->write((string)now.user.name,CMD);
}



