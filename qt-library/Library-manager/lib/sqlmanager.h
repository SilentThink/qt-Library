#ifndef SQLMANAGER_H
#define SQLMANAGER_H
#include <QDebug>
#include <QSqlDatabase>

//单例模式
class SqlManager
{
public:
    SqlManager();
    ~SqlManager();

    static SqlManager* instance;
    static SqlManager* getInstance(){
        if(instance == nullptr) {
            instance = new SqlManager();
        }
        return instance;
    }

    //初始化
    void init();
    //登录
    bool login(QString strUser,QString strPass);

    /* 用户管理 */
    //获取所有用户
    QVector<QStringList> getUsers(QString strCondition="");
    //添加用户
    void addUsers(QVector<QStringList> v);
    //删除用户
    void delUser(QString strId);

    /* 图书管理 */
    //获取所有图书
    QVector<QStringList> getBooks(QString strCondition="");
    //增加图书
    void addBooks(QVector<QStringList> v);
    //修改图书
    void updateBook(QStringList ldata);
    //删除图书
    QString delBook(QString strISBN);
    //图书归还
    QString returnBook(QString strBookISBN);
    //图书借阅
    QString borrowBook(QString strBookISBN);
    //获取借阅记录
    QVector<QStringList> getRecord(QString strCondition="");
    //添加借阅记录
    void addRecord(QStringList l);
    //删除借阅记录
    void delRecord(QStringList l);

private:
    QSqlDatabase m_db;

};

#endif // SQLMANAGER_H
