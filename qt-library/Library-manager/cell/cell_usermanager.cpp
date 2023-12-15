#include "cell_usermanager.h"
#include "ui_cell_usermanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>

Cell_UserManager::Cell_UserManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_UserManager)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    //设置不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_model.setHorizontalHeaderLabels(QStringList{"用户id","年级","部门","用户名","密码","昵称","权限"});
#if 0
    for(int i=0;i<10;i++)
    {
        QList<QStandardItem*> items;
        items.append(new QStandardItem("1"));
        items.append(new QStandardItem("1年一班"));
        items.append(new QStandardItem("机械工程"));
        items.append(new QStandardItem("zhangsan"));
        items.append(new QStandardItem("123"));
        items.append(new QStandardItem("张三"));
        items.append(new QStandardItem("学生"));
        m_model.appendRow(items);
    }
#endif

}

Cell_UserManager::~Cell_UserManager()
{
    delete ui;
}

void Cell_UserManager::freshPage(QString strCondition)
{
    //查询数据库并显示
    auto l = SqlManager::getInstance()->getUsers(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"用户id","年级","部门","用户名","密码","昵称","权限"});
    for(int i=0;i<l.size();i++)
    {
        QList<QStandardItem*> items;
        for(int j=0;j<l[i].size();j++)
        {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
}

void Cell_UserManager::on_btn_del_released()
{
    //删除用户
    int r = ui->tableView->currentIndex().row();
    if(r<0)
    {
        QMessageBox::information(nullptr,"错误","无选中用户");
    }
    else
    {
        auto id = m_model.item(r,0)->text();
        SqlManager::getInstance()->delUser(id);
        freshPage();
    }
}

void Cell_UserManager::on_btn_import_released()
{
    //导入用户
    auto strPath = QFileDialog::getOpenFileName(nullptr,"输入文件路径");

    if(!strPath.isEmpty())
    {
        QFile f(strPath);
        f.open(QFile::ReadOnly);
        qDebug()<<f;
        QVector<QStringList> vecData;

        while(!f.atEnd())
        {
            QString str = QString::fromLocal8Bit(f.readLine());

            qDebug()<<str;
            auto l = str.split(",");
            if(l.size()!=6)
            {
                QMessageBox::information(nullptr,"信息","导入失败");
                return;
            }
            l[l.size()-1] = l[l.size()-1].chopped(2);
            vecData.push_back(l);
        }

        SqlManager::getInstance()->addUsers(vecData);
        freshPage();
    }

}

void Cell_UserManager::on_le_search_textChanged(const QString &arg1)
{
    //查找用户
    QString strCond = QString("where username like '%%1%' or nickname like '%%1%'").arg(arg1);
    freshPage(strCond);
}
