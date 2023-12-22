#include "cell_usermanager.h"
#include "ui_cell_usermanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include "dlg_adduser.h"

Cell_UserManager::Cell_UserManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_UserManager)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    //设置不可编辑
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_model.setHorizontalHeaderLabels(QStringList{"用户id","年级","部门","用户名","密码","昵称","权限"});
    //自适应宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "确认", "您确定要删除此用户吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            SqlManager::getInstance()->delUser(id);
            QMessageBox::information(nullptr,"信息","删除成功");
            freshPage();
        }
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
            if(l.size()!=7)
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
    QString strCond = QString("where username like '%%1%' or nickname like '%%1%' or userid like '%%1%'").arg(arg1);
    freshPage(strCond);
}

void Cell_UserManager::on_btn_addUser_released()
{
    //增加用户
    dlg_addUser dlg;
    dlg.setWindowTitle("增加用户");
    dlg.show();
    int ret = dlg.exec();
    if(ret == 1)
        freshPage();
}
