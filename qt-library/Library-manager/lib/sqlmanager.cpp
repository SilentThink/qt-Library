#include "sqlmanager.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QDateTime>
SqlManager* SqlManager::instance = nullptr;
SqlManager::SqlManager()
{

}

SqlManager::~SqlManager()
{

}

void SqlManager::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString strPath = QCoreApplication::applicationDirPath()+"/db/book.db";
    m_db.setDatabaseName(strPath);
#if 0
    qDebug()<<m_db.open();
#else
    m_db.open();
#endif
}

bool SqlManager::login(QString strUser, QString strPass)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user where username='%1' and password = '%2'").arg(strUser).arg(strPass);
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
    return ret;
}

QVector<QStringList> SqlManager::getUsers(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user %1").arg(strCondition);

    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
    else
    {
        int iCols = q.record().count();
        QStringList l;
        while(q.next())
        {
            l.clear();
            for(int i=0 ;i<iCols ;i++)
            {
                l<<q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlManager::addUsers(QVector<QStringList> v)
{
    m_db.transaction();
    QSqlQuery q(m_db);
    for(auto it:v)
    {
        QString strSql = QString("insert into user VALUES('%1','%2','%3','%4','%5','%6','%7')")
                .arg(it[0]) //学号
                .arg(it[1]) //年级
                .arg(it[2]) //院系
                .arg(it[3]) //账户名
                .arg(it[4]) //密码
                .arg(it[5]) //昵称
                .arg(it[6]) //权限
                ;
        bool ret = q.exec(strSql);
        if(!ret)
        {
            qDebug()<<q.lastError().text();
            QMessageBox::warning(nullptr,"错误","用户已经存在");
        }
    }
    m_db.commit();
}

void SqlManager::delUser(QString strId)
{
    QSqlQuery q(m_db);
    QString strSql = QString("delete from user where userid=%1").arg(strId);
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
}

QVector<QStringList> SqlManager::getBooks(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from book %1").arg(strCondition);

    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
    else
    {
        int iCols = q.record().count();
        QStringList l;
        while(q.next())
        {
            l.clear();
            for(int i=0 ;i<iCols ;i++)
            {
                l<<q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlManager::addBooks(QVector<QStringList> v)
{
    if(v.size()==0)
    {
        return;
    }
    m_db.transaction();
    QSqlQuery q(m_db);
    for(auto it:v)
    {
        QString strSql = QString("insert into book VALUES('%1','%2','%3','%4','%5','%6','%7','%8')")
                .arg(it[0]) //ISBN
                .arg(it[1]) //name
                .arg(it[2]) //price
                .arg(it[3]) //writer
                .arg(it[4]) //type
                .arg(it[5]) //nation
                .arg(it[6]) //inventory
                .arg(it[7]) //total
                ;
        bool ret = q.exec(strSql);
        if(!ret)
        {
            //qDebug()<<q.lastError().text();
            QString strSql = QString("UPDATE book "
                                     "SET inventory = inventory + '%1' ,total = total + '%1' "
                                     "WHERE ISBN='%2' ")
                    .arg(it[7].toInt())
                    .arg(it[0])
                    ;
            q.exec(strSql);
            QMessageBox::warning(nullptr,"提示","书籍已经存在，已增加其数量和库存");
        }
    }
    m_db.commit();
}

void SqlManager::updateBook(QStringList ldata)
{
    QSqlQuery q(m_db);
    QString strSql = QString("UPDATE book "
                             "SET name ='%1',price='%2',writer='%3',type='%4',nation='%5',inventory='%6',total=%7 "
                             "WHERE ISBN=%8")
            .arg(ldata[1])          //name
            .arg(ldata[2])          //price
            .arg(ldata[3])          //writer
            .arg(ldata[4])          //type
            .arg(ldata[5])          //nation
            .arg(ldata[6].toInt())  //inventory
            .arg(ldata[7].toInt())  //total
            .arg(ldata[0])          //ISBN
            ;

    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
}

QString SqlManager::delBook(QString strISBN)
{
    QString strRet;
    QSqlQuery q(m_db);
    QString strSql = QString("delete from book where ISBN=%1").arg(strISBN);
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
        strRet = "删除失败，请检查";
    }
    return strRet;
}

QString SqlManager::returnBook(QString strBookISBN)
{
    QString strRet;
    QSqlQuery q(m_db);
    QString strSql = QString("update book set inventory = inventory + 1 where ISBN=%1").arg(strBookISBN);
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
        strRet = "还书错误,请检查";
    }
    return strRet;
}

QString SqlManager::borrowBook(QString strBookISBN)
{
    QString strRet;
    QSqlQuery q(m_db);
    QString strSql = QString("update book set inventory = inventory - 1 where ISBN=%1").arg(strBookISBN);
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
        strRet = "借书错误,请检查";
    }
    return strRet;
}

QVector<QStringList> SqlManager::getRecord(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from record %1").arg(strCondition);

    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
    else
    {
        int iCols = q.record().count();
        QStringList l;
        while(q.next())
        {
            l.clear();
            for(int i=0 ;i<iCols ;i++)
            {
                l<<q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlManager::addRecord(QStringList l)
{
    if(l.size()==0)
    {
        return;
    }
    QSqlQuery q(m_db);

    QString strSql = QString("insert into record VALUES('%1','%2','%3','%4')")
            .arg(l[0])
            .arg(l[1])
            .arg(l[2])
            .arg(l[3])
            ;
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
}

void SqlManager::delRecord(QStringList l)
{
    QSqlQuery q(m_db);
    QDateTime currentTime= QDateTime::currentDateTime();//获取系统当前的时间
    //QString str = dateTime .toString("yyyy-MM-dd");//格式化时间
    QString strSql = QString("select * from record where userid=%1 and bookISBN=%2")
            .arg(l[0])
            .arg(l[1])
            ;
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
    else
    {
        q.next();
        QString endDate = q.value(3).toString();
        QDateTime endtime = QDateTime::fromString(endDate, "yyyy-MM-dd");
        if(currentTime>endtime)
        {
            QMessageBox::warning(nullptr,"警告","逾期还书！");
        }
    }
    strSql = QString("delete from record where userid=%1 and bookISBN=%2")
            .arg(l[0])
            .arg(l[1])
            ;

    ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
}

