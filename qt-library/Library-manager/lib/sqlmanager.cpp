#include "sqlmanager.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
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

void SqlManager::addUser(QVector<QStringList> v)
{
    m_db.transaction();
    QSqlQuery q(m_db);
    for(auto it:v)
    {
        QString strSql = QString("insert into user VALUES(NULL,'%1','%2','%3','%4','%5','%6')")
                .arg(it[0])
                .arg(it[1])
                .arg(it[2])
                .arg(it[3])
                .arg(it[4])
                .arg(it[5])
                ;
        bool ret = q.exec(strSql);
        if(!ret)
        {
            qDebug()<<q.lastError().text();
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
        QString strSql = QString("insert into book VALUES(NULL,'%1','%2','%3','%4','%5','%6')")
                .arg(it[0])
                .arg(it[1])
                .arg(it[2])
                .arg(it[3])
                .arg(it[4])
                .arg(it[5])
                ;
        bool ret = q.exec(strSql);
        if(!ret)
        {
            qDebug()<<q.lastError().text();
        }
    }
    m_db.commit();
}

void SqlManager::updateBooks(QStringList ldata)
{
    QSqlQuery q(m_db);
    QString strSql = QString("UPDATE book "
                             "SET name ='%1',price='%2',type1='%3',type2='%4',type3='%5',cnt=%6 "
                             "WHERE bookid=%7")
            .arg(ldata[1])
            .arg(ldata[2])
            .arg(ldata[3])
            .arg(ldata[4])
            .arg(ldata[5])
            .arg(ldata[6].toInt())
            .arg(ldata[0].toInt())
            ;

    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
}

QString SqlManager::delBook(QString strId)
{
    QString strRet;
    QSqlQuery q(m_db);
    QString strSql = QString("delete from book where bookid=%1").arg(strId);
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
        strRet = "删除失败，请检查";
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

    QString strSql = QString("insert into record VALUES(NULL,'%1','%2','%3','%4')")
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
    QString strSql = QString("delete from record where userid=%1 and bookid=%2")
            .arg(l[0])
            .arg(l[1])
            ;
    bool ret = q.exec(strSql);
    if(!ret)
    {
        qDebug()<<q.lastError().text();
    }
}

QString SqlManager::clearRecord()
{

}
