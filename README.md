# walotta的BookStore软件开发文档

* 作者：walotta(韦中敬)
* version：*1.0*

---

### *main.cpp*

* 执行初始化，调用`init()`，若为初次运行则生成必要文件，建立用户
* 运行`BookStore`后台

---

### *BPlusTree*

* 由一个h与cpp组成

* 设计为一个模版类，含有参数`KeyType`、`Size(块的大小限制)`、`Name(储存文件名)`、`IdType`

* 其功能为提供一个B+树类（`MyBpt`），内部含有`StoragePool`类对象进行存储，实现`key`到`id`的映射

* 该类的功能为对一个数据存储文件建立索引（即建立一棵B+树），并负责生成一个索引文件，进行储存

* 该类内部只实现对于特定`key`值返回其在`StoragePool`中的id值

* 含有一个头数据点，指明头数据在储存池中的`id`值

* 储存为块状储存，保证存储块大小固定，即提供一个数据类存储

* 块的头部含有一个`bool`值储存是否为叶节点`(IfLeaves)`，`true`为叶节点，叶节点维护双向链表结构

  |       接口       |                     功能                      |
  | :--------------: | :-------------------------------------------: |
  | `insert(key,id)` |     插入数据点，构建`key`与`id`的对应关系     |
  |  `delete(key)`   |             删除`key`对应的数据点             |
  |   `find(key)`    | 查找`key`对应的数据，返回`id`，属性为`vector` |

---

### *StoragePool*

* 为储存池类，进行底层对于书的信息存储文件的操作，实现`O(1)`的读取删除，并维护储存空间的回收

* 设计为模版类，实例化时要求为其指明存储的文件名`(FILENAME)`与储存的块的类型`(T)`

* 对外接口类似于虚拟内存，提供一个数字寻址的功能，对于给定的`id`值返回其对应的储存块

* 内部有一个储存块指针，向文件中写入储存块，用`id*size`进行寻址

* 在储存池头部有一个`head`数据点，用于储存下一个可用块的`id`，若为-1，说明应当在文件末写入

* 删除块时，将被删除的块的`id`写入`head`数据点，在被删除块的位置写入原`head`值

* 写入块时，先查询`head`数据点，若为覆写，则将`head`的值修改

  |       接口       |                       功能                        |
  | :--------------: | :-----------------------------------------------: |
  | `add(const T &)` | 将`T`对应的数据写入文件，并返回储存位置对应的`id` |
  |   `delete(id)`   |                 删除`id`对应的块                  |
  |  `update(id,T)`  |                  更新`id`对应块                   |
  |    `get(id)`     |               返回`id`对应的块对象                |

  

---

### *FileStorage*

* 由一个h与cpp组成

* 设计为模版类，功能为实现对文件的单或多索引储存，实例化时要求给出存储的类的类型`(T)`、主`Key(MainKey)`

* 要求存在一个`key`属性为储存值存在且唯一的`KeyType`，为`MainKey`

* 内部包含多个`BPlusTree`类对象，一个`StoragePool`类的存储类型实例，实现将书的数据的存入、删除、查询、修改

  |         接口          |                    功能                     |
  | :-------------------: | :-----------------------------------------: |
  | `AddMoreKey(keyType)` |    加入一个`key`的索引，建立一个索引文件    |
  |      `Insert(T)`      |          插入一个数据，并维护索引,          |
  |   `Delete(MainKey)`   |                根据主值删除                 |
  |  `Find(KeyType,Key)`  | 根据提供的`Key`寻找，返回一个对象的`vector` |
  |    `Give(MainKey)`    |              根据主值返回对象               |
  |       `Give()`        |             返回当前选中的对象              |
  |    `GiveMainKey()`    |             返回当前对象的主值              |
  |   `Select(MainKey)`   |             选中主值对应的对象              |
  |      `Update(T)`      |        更新选中块，同步更改选中属性         |
  | `AddKey(keytype,key)` |        为当前选中的对象增加`key`属性        |

---

### *BookManage*

* 含有`FileStorage<BookBlock,ISBN>`对象

* 含有一个`BookBlock`类，储存某一本书的相关信息，并`operator <`用于`sort`，依据为`ISBN`

* `PS：keyType`总共有`ISBN、name、author、keyword`4种，其中`ISBN`为`MainKey`

* 添加图书相关接口

  |            接口            |                        功能                        |
  | :------------------------: | :------------------------------------------------: |
  |     `AddBook(number)`      |               添加选中的书的指定数量               |
  |    `DeleteBook(number)`    | 删除选中的书的指定数目，返回一个`bool`表示是否成功 |
  | `DeleteBook(ISBN,number)`  |            删除`ISBN`指定的书的指定数量            |
  |       `Select(ISBN)`       |     选中书本，若无则创建，返回`id`用于外部存储     |
  | `UpdateBook(NewBookBlock)` |    删除选中的原书数据，换为新数据,同时更新索引     |
  |        `GetBook()`         |                  返回选中的块对象                  |
  |          `show()`          |               展示所有书,`cout`输出                |
  |    `show(keyType,key)`     |          根据`key`展示所有书，`cout`输出           |
  |        `memory(id)`        |             给出`id`恢复之前的查找记录             |

  

---

### *UserManage*

* 含有`FileStorage<UserBlock,id>`对象，与一个`Log`对象用于读取、储存用户的日志

* 增加用户管理相关接口

* 实现栈管理的用户登录，储存选中的图书的存储空间的`id`

* 初始化接受文件，若不存在则新建`root`用户

  |        接口         |                        功能                        |
  | :-----------------: | :------------------------------------------------: |
  |       `Login`       |                        登陆                        |
  |      `Logout`       |                        登出                        |
  |      `UserAdd`      |                      添加用户                      |
  |    `DeleteUser`     |                      删除用户                      |
  |    `ResetPasswd`    |                      重设密码                      |
  |   `NowPrivilege`    |                    返回当前权限                    |
  |    `NowUserName`    |                   返回当前用户名                   |
  |     `ShowLog()`     |             展示当前用户的日志到`cout`             |
  |   `ShowLog(User)`   |          展示特定用户的操作日志，权限管理          |
  | `AskPrivilege(pri)` | 返回`bool`显示指定权限当前是否具有，具有返回`true` |

---

### *CMD*

* 提供一个类进行指令的读入与部分输出，负责用户交互，与其余各个底层类通讯

* 进行`log`的管理，分别将数据储存到`MainLog`与用户的个人日志

* 进行指令的分割与异常处理，报错信息为`Invalid\n`

  |     指令类型      |                    功能                    |
  | :---------------: | :----------------------------------------: |
  |       `su`        |     登陆用户，高权限到低权限不需要密码     |
  |     `logout`      |                登出当前用户                |
  |     `useradd`     |                  添加用户                  |
  |    `register`     |             注册一个权限1用户              |
  |     `delete`      |        删除用户，检查是否有删除权限        |
  |     `passwd`      |                  重设密码                  |
  |     `select`      |                   选中书                   |
  |     `modify`      |           更新书的内容，权限管理           |
  |     `import`      |              进货书，权限管理              |
  |      `show`       |                   查询书                   |
  |  `show finance`   | 输出买入卖出记录，会含有次数参数，权限管理 |
  |       `buy`       |            购买书，输出购买花费            |
  | `report finance`  |           生成财务报表，权限管理           |
  | `report employee` |        生成员工工作情况表，权限管理        |
  |       `log`       |           生成工作日志，权限管理           |
  |  `report myself`  |        返回员工的操作记录，权限管理        |
  |      `quit`       |     退出程序，读到`EOF`也执行此条指令      |
  |      `exit`       |                  同`quit`                  |

---

### *Log*

* 用于储存日志，并生成日志文件，使用`ASCII`文件储存，为模版类，要求给出储存信息的文件名

* 初始化函数调用文件，若文件不存在则新建文件，若文件存在则将指针定位到末尾

* 细节：对于用户登录顶格，其余做`\t`缩进

  |      接口       |         功能         |
  | :-------------: | :------------------: |
  | `write(string)` | 将字符串指令写入文件 |
  |    `read()`     | 输出整个文件到`cout` |

---

### *Finance*

* 用于储存财务表，维护每次交易后的前缀和

* 内部实现一个储存类，可以用序号访问，返回当前存储到的最后位置

  |     接口      |          功能          |
  | :-----------: | :--------------------: |
  | `add(in,out)` |     建立下一个储存     |
  |   `read()`    | 输出全部的收支到`cout` |
  | `read(time)`  |  追溯`time`次输出收支  |

  

---

# *WISH YOU CODING WITH HAPPINESS*

