//
// Created by wzj on 2021/1/18.
//

#include "CMD.h"

void CMD::run_command(const string &in)
{
    stringstream ss;
    ss<<in;
    string token;
    ss>>token;
    if(token.empty())return;
    if(ss.fail())throw error("read cmd error");
    if(token=="su")
    {
        string name;
        string passwd;
        ss>>name;
        ss>>passwd;
        hasMoreToken(ss);
        log.write(userMange.NowUserName(),"su "+name);
        userMange.Login(name,passwd);
        if(userMange.GiveSelectBook()!=-1)bookManege.Select(userMange.GiveSelectBook());
    }else if(token=="logout")
    {
        userMange.AskPrivilege(1);
        log.write(userMange.NowUserName(),"logout");
        userMange.Logout();
        if(userMange.GiveSelectBook()==-1)
        {
            bookManege.ClearSelect();
        }else bookManege.Select(userMange.GiveSelectBook());
    }else if(token=="useradd")
    {
        userMange.AskPrivilege(3);
        string name;
        string passwd;
        int pri;
        string other_name;
        ss>>name>>passwd>>pri>>other_name;
        if(ss.fail())throw error("wrong message in add user");
        if(pri!=7&&pri!=3&&pri!=1)throw error("error pri");
        hasMoreToken(ss);
        log.write(userMange.NowUserName(),"useradd "+name+' '+other_name);
        userMange.UserAdd(name,passwd,pri,other_name);
    }else if(token=="register")
    {
        string name;
        string passwd;
        string other_name;
        ss>>name>>passwd>>other_name;
        if(ss.fail())throw error("wrong message in add user");
        hasMoreToken(ss);
        log.write(userMange.NowUserName(),"register "+name+' '+other_name);
        userMange.UserAdd(name,passwd,1,other_name);
    }else if(token=="delete")
    {
        string name;
        ss>>name;
        hasMoreToken(ss);
        log.write(userMange.NowUserName(),"delete "+name);
        userMange.DeleteUser(name);
    }else if(token=="passwd")
    {
        userMange.AskPrivilege(1);
        string name;
        string psd1;
        string psd2;
        ss>>name>>psd1>>psd2;
        hasMoreToken(ss);
        if(psd2.empty())
        {
            userMange.ResetPasswd(name,"",psd1);
        }else
        {
            userMange.ResetPasswd(name,psd1,psd2);
        }
        log.write(userMange.NowUserName(),"passwd "+name);
    }else if(token=="select")
    {
        if(userMange.NowPrivilege()<3)throw error("you cannot select because of pri");
        string ISBN;
        ss>>ISBN;
        hasMoreToken(ss);
        userMange.ChangeSelectBook(bookManege.Select(ISBN));
        log.write(userMange.NowUserName(),"select "+ISBN);
        userMange.WriteLog("select "+ISBN);
    }else if(token=="modify")
    {
        userMange.AskPrivilege(3);
        string ISBN;
        string name;
        string author;
        string keyword;
        double price=-1;
        token="";
        ss>>token;
        if(token.empty())throw error("please enter modify msg");
        do
        {
            stringstream tem;
            tem<<token;
            //cout<<"[debug]"<<token<<endl;
            string check;
            if(token[0]!='-')throw error("modify error");
            getline(tem,check,'=');
            if(token[1]=='I')
            {
                if(check!="-ISBN")throw error("modify error");
                if(ISBN.empty())
                {
                    tem>>ISBN;
                    hasMoreToken(tem);
                }else
                {
                    throw error("modify error");
                }
            }else if(token[1]=='n')
            {
                if(check!="-name")throw error("modify error");
                if(name.empty())
                {
                    tem>>name;
                    removeMark(name);
                    hasMoreToken(tem);
                }else
                {
                    throw error("modify error");
                }
            }else if(token[1]=='a')
            {
                if(check!="-author")throw error("modify error");
                if(author.empty())
                {
                    tem>>author;
                    removeMark(author);
                    hasMoreToken(tem);
                }else
                {
                    throw error("modify error");
                }
            }else if(token[1]=='k')
            {
                if(check!="-keyword")throw error("modify error");
                if(keyword.empty())
                {
                    tem>>keyword;
                    removeMark(keyword);
                    hasMoreToken(tem);
                }else
                {
                    throw error("modify error");
                }
            }else if(token[1]=='p')
            {
                if(check!="-price")throw error("modify error");
                if(price==-1)
                {
                    double a;
                    tem>>a;
                    //cout<<"[debug]"<<a<<endl;
                    if(a<0)throw error("modify error");
                    price=a;
                    hasMoreToken(tem);
                }else
                {
                    throw error("modify error");
                }
            }else
            {
                throw error("modify error");
            }
            token="";
            ss>>token;
        }while(!token.empty());
        BookBlock now=bookManege.GetBook();
        if(now.price==-1&&price==-1)now.price=0;
        else
        {
            if(price!=-1)now.price=price;
        }
        if(!ISBN.empty())
        {
            if(ISBN==now.keyStorage[BookBlock::isbn])throw error("modify error because repeat ISBN");
            else now.keyStorage[BookBlock::isbn]=ISBN;
        }
        if(!name.empty())now.keyStorage[BookBlock::name]=name;
        if(!author.empty())now.keyStorage[BookBlock::author]=author;
        if(!keyword.empty())now.keyStorage[BookBlock::keyword]=keyword;
        bookManege.UpdateBook(now);
        bookManege.Select((string)now.keyStorage[BookBlock::isbn]);//todo change

        //cout<<"[debug]"<<endl;
        //bookManege.show();
        //cout<<"[debug finish]"<<endl;

        log.write(userMange.NowUserName(),"modify "+ISBN);
        userMange.WriteLog("modify "+ISBN);
    }else if(token=="import")
    {
        userMange.AskPrivilege(3);
        int sum=-1;
        double cost_price=-1;
        ss>>sum>>cost_price;
        hasMoreToken(ss);
        if(cost_price<0||sum<0)throw error("wrong number in import");
        bookManege.AddBook(sum);
        log.write(userMange.NowUserName(),"import "+(string)bookManege.GetBook().keyStorage[BookBlock::isbn]);
        finance.outcome(cost_price);
        userMange.WriteLog("import "+(string)bookManege.GetBook().keyStorage[BookBlock::isbn]);

        //cout<<"[debug]"<<endl;bookManege.show();cout<<"[debug finish]"<<endl;
    }else if(token=="show")
    {
        token="";
        ss>>token;
        if(token=="finance")
        {
            userMange.AskPrivilege(7);
            int times=-1;
            ss>>times;
            hasMoreToken(ss);
            if(times==-1)finance.read();
            else finance.read(times);
            log.write(userMange.NowUserName(),"show finance");
            userMange.WriteLog("show finance");
        }else
        {
            userMange.AskPrivilege(1);
            //cout<<"[debug]"<<token<<endl;
            if(token[0]=='-')
            {
                hasMoreToken(ss);
                stringstream a;
                a<<token;
                string keyType;
                string keyValue;
                getline(a,keyType,'=');
                if(keyType=="-ISBN")
                {
                    a>>keyValue;
                    bookManege.show("isbn",keyValue);
                }else if(keyType=="-name")
                {
                    a>>keyValue;
                    removeMark(keyValue);
                    bookManege.show("name",keyValue);
                }else if(keyType=="-author")
                {
                    a>>keyValue;
                    removeMark(keyValue);
                    bookManege.show("author",keyValue);
                }else if(keyType=="-keyword")
                {
                    a>>keyValue;
                    removeMark(keyValue);
                    bookManege.show("keyword",keyValue);
                }else
                {
                    throw error("show error");
                }
                log.write(userMange.NowUserName(),"show book");
                userMange.WriteLog("show book");
            }else if(token.empty())
            {
                bookManege.show();
                log.write(userMange.NowUserName(),"show");
                userMange.WriteLog("show");
            }else
            {
                throw error("show error");
            }
        }
    }else if(token=="buy")
    {
        //cout<<"[debug]"<<endl;bookManege.show();cout<<"[debug finish]"<<endl;
        if(userMange.NowPrivilege()>=1)
        {
            string ISBN;
            int sum=-1;
            ss>>ISBN>>sum;
            if(sum==-1)throw error("buy wrong");
            bookManege.DeleteBook(ISBN,sum);
            double money=bookManege.GetBook(ISBN).price*sum;
            printf("%.2f\n",money);
            finance.income(money);
            log.write(userMange.NowUserName(),"buy books");
            userMange.WriteLog("buy books");
        }else
        {
            throw error("buy failed because of pri");
        }
    }else if(token=="report")
    {
        ss>>token;
        if(token=="finance")
        {
            userMange.AskPrivilege(7);
            hasMoreToken(ss);
            if(userMange.NowPrivilege()!=7)throw error("report finance failed");
            finance.print();
            log.write(userMange.NowUserName(),"report finance");
            userMange.WriteLog("report finance");
        }else if(token=="employee")
        {
            userMange.AskPrivilege(7);
            hasMoreToken(ss);
            if(userMange.NowPrivilege()!=7)throw error("report employee failed");
            cout<<"Please enter the name of the employee you want to seek:"<<endl;
            string a;
            cin>>a;
            userMange.ShowLog(a);
            log.write(userMange.NowUserName(),"report employee");
        }else if(token=="myself")
        {
            userMange.AskPrivilege(3);
            userMange.ShowLog();
            log.write(userMange.NowUserName(),"report myself");
        }else
        {
            throw error("command not find");
        }
    }else if(token=="log")
    {
        userMange.AskPrivilege(7);
        log.print();
        log.write(userMange.NowUserName(),"log");
        userMange.WriteLog("log");
    }else if(token=="quit")
    {
        log.write(userMange.NowUserName(),"quit");
        userMange.WriteLog("quit");
        exit(0);
    }else if(token=="exit")
    {
        log.write(userMange.NowUserName(),"exit");
        userMange.WriteLog("exit");
        exit(0);
    }else if(token=="help")
    {
        //throw error("command not find");
        cout<<"Help List\n\n";
        cout<<"su [user-id] [passwd] #0:登录到某用户，从高权限用户登录到低权限不需填写密码\n"
              "logout #1:返回到未登录状态\n"
              "useradd [user-id] [passwd] [7/3/1] [name] #3:增加一个指定权限的用户，只能创建小于自己权限的账户\n"
              "register [user-id] [passwd] [name] #0:注册一个带有这些信息的权限1用户\n"
              "delete [user-id] #7:删除某用户\n"
              "passwd [user-id] [old-passwd(if not root)] [new-passwd] #1:root不需要填写旧密码，其余账户需要\n";
        cout<<"select [ISBN] #3:选定ISBN为指定值的图书，若不存在则创建该ISBN的书并将其余信息留空等待modify进行填写\n"
              "modify -ISBN=[ISBN] -name=[name] -author=[author] -keyword=[keyword] -price=[price] #3:参数可省略，也不要求输入顺序，会更新(替换而非添加)上次选中的书至新的信息\n"
              "import [quantity] [cost_price(in total)] #3:将上次选中的书以总共[cost_price]的价格进[quantity]本\n"
              "show -ISBN=[ISBN] -name=[name] -author=[author] -keyword=[keyword] #1:参数可省略，也不要求输入顺序，将匹配的图书以ISBN号排序输出，需要注意该命令参数只支持单参数，如果参数是keyword，只支持单关键词查询\n"
              "show finance [time] #7:time项省略时，输出总的收入与支出;否则输出近[time]次进货、卖出操作(分别算一次)的合计收入支出。\n"
              "buy [ISBN] [quantity] #1:购买该ISBN号的图书[quantity]本\n";
        cout<<"report finance #7:会生成一张赏心悦目的财务报表\n"
              "report employee #7:会生成一张赏心悦目的员工工作情况表\n"
              "log #7:会返回赏心悦目的日志记录\n"
              "report myself #3:返回员工自己的操作记录\n\n";
        cout<<"Help List Finished\n";
    }else
    {
        throw error("command not find");
    }

}

void CMD::removeMark(string &o)
{
    if(o[0]!='\"'||o[o.size()-1]!='\"')throw error("remove mark failed not find mark");
    string tem;
    for(int i=1;i<o.size()-1;i++)
    {
        tem.push_back(o[i]);
    }
    o=tem;
}

void CMD::showPri()
{
    cout<<userMange.NowPrivilege()<<endl;
}

void CMD::sudo_show()
{
    bookManege.show();
}
