#include "cell_bookmanager.h"
#include "ui_cell_bookmanager.h"
#include "lib/sqlmanager.h"
#include "dlg_bookaddorupdate.h"
#include "dlg_borroworreturn.h"
#include "dlg_borroworreturn.h"

#include <QMessageBox>

Cell_BookManager::Cell_BookManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_BookManager)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    //设置不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    freshPage();
}

Cell_BookManager::~Cell_BookManager()
{
    delete ui;
}

void Cell_BookManager::freshPage(QString strCondition)
{
    //刷新页面，获取所有图书信息
    auto l = SqlManager::getInstance()->getBooks(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"书籍id","书名","价格","类型1","类型2","类型3","数量"});
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

void Cell_BookManager::on_btn_add_released()
{
    //增加图书
    Dlg_BookAddOrUpdate dlg(this);
    dlg.setType(-1);
    dlg.setWindowTitle("增加图书");
    dlg.show();
    int ret = dlg.exec();
    if(ret == 1)
    {
        freshPage();
    }
}

void Cell_BookManager::on_btn_change_released()
{
    //修改图书
    Dlg_BookAddOrUpdate dlg(this);
    int id= -1;
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this,"错误","请选中你要修改的图书");
    }
    else
    {
        QVariant selectValue = m_model.data(selectedIndexes.first(),Qt::DisplayRole);
        id = selectValue.toInt();
        dlg.setType(id);
        dlg.setWindowTitle("增加图书");
        dlg.show();
        int ret = dlg.exec();
        if(ret == 1)
        {
            freshPage();
        }
    }

}

void Cell_BookManager::on_btn_return_released()
{
    //归还图书
    Dlg_BorrowOrReturn dlg;
    dlg.setWindowTitle("增加图书");
    dlg.show();
    int ret = dlg.exec();
    if(ret == 1)
    {
        freshPage();
    }
}

void Cell_BookManager::on_btn_borrow_released()
{
    //借阅图书
    Dlg_BorrowOrReturn dlg;
    dlg.setWindowTitle("借阅图书");
    dlg.show();
    int id= -1;
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this,"错误","请选中你要借阅的图书");
    }
    else
    {
        QVariant selectValue = m_model.data(selectedIndexes.first(),Qt::DisplayRole);
        id = selectValue.toInt();
        dlg.setType(id);
        dlg.setWindowTitle("增加图书");
        dlg.show();
        int ret = dlg.exec();
        if(ret == 1)
        {
            freshPage();
        }
    }
}

void Cell_BookManager::on_btn_del_released()
{
    //删除图书
    int r = ui->tableView->currentIndex().row();
    if(r<0)
    {
        QMessageBox::information(nullptr,"错误","无选中图书");
    }
    else
    {
        QString id = m_model.item(r,0)->text();
        QString str = SqlManager::getInstance()->delBook(id);
        QMessageBox::information(nullptr,"信息",str.isEmpty()?"删除成功":str);
        freshPage();
    }
}


void Cell_BookManager::on_le_search_textChanged(const QString &arg1)
{
    //查找图书
    QString strCond = QString("where name like '%%1%' or type1 like '%%1%'").arg(arg1);
    freshPage(strCond);
}
