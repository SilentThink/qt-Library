#include "cell_bookmanager.h"
#include "ui_cell_bookmanager.h"
#include "lib/sqlmanager.h"
#include "dlg_bookaddorupdate.h"
#include "dlg_borroworreturn.h"
#include "dlg_borroworreturn.h"
#include "cell_main.h"
#include <QTableView>
#include <QMessageBox>

Cell_BookManager::Cell_BookManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_BookManager)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    //设置选中单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //自适应宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    m_model.setHorizontalHeaderLabels(QStringList{"书籍ISBN码","书名","价格","作者","类型","国家","库存","数量"});
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
    dlg.setType(nullptr);
    dlg.setWindowTitle("增加图书");
    dlg.show();
    int ret = dlg.exec();
    if(ret == 1)
    {
        Cell_Main::getInstance()->freshAll();
    }
}

void Cell_BookManager::on_btn_change_released()
{
    //修改图书
    Dlg_BookAddOrUpdate dlg(this);
    QString ISBN= nullptr;
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this,"错误","请选中你要修改的图书");
    }
    else
    {
        QVariant selectValue = m_model.data(selectedIndexes.first(),Qt::DisplayRole);
        ISBN = selectValue.toString();
        dlg.setType(ISBN);
        dlg.setWindowTitle("修改图书");
        dlg.initInfo(m_model.data(selectedIndexes.first(),Qt::DisplayRole).toString(),
                     m_model.data(selectedIndexes.at(1),Qt::DisplayRole).toString(),
                     m_model.data(selectedIndexes.at(2),Qt::DisplayRole).toString(),
                     m_model.data(selectedIndexes.at(3),Qt::DisplayRole).toString(),
                     m_model.data(selectedIndexes.at(4),Qt::DisplayRole).toString(),
                     m_model.data(selectedIndexes.at(5),Qt::DisplayRole).toString(),
                     m_model.data(selectedIndexes.at(6),Qt::DisplayRole).toInt(),
                     m_model.data(selectedIndexes.at(7),Qt::DisplayRole).toInt()
                     );
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
    dlg.setWindowTitle("归还图书");
    dlg.show();
    int ret = dlg.exec();
    if(ret==1)
    {
        freshPage();
    }
}

void Cell_BookManager::on_btn_borrow_released()
{
    //借阅图书
    Dlg_BorrowOrReturn dlg;
    dlg.setWindowTitle("借阅图书");
    QString ISBN=nullptr;
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
    {
        QMessageBox::warning(this,"错误","请选中你要借阅的图书");
    }
    else
    {
        QVariant selectValue = m_model.data(selectedIndexes.first(),Qt::DisplayRole);
        ISBN = selectValue.toString();
        dlg.setType(ISBN);
        dlg.setWindowTitle("借阅图书");
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
        QString id = m_model.item(r,0)->text();// 获取选中行的图书ID

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "确认", "您确定要删除这本图书吗？",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            QString str = SqlManager::getInstance()->delBook(id);
            QMessageBox::information(nullptr,"信息",str.isEmpty()?"删除成功":str);
            freshPage();
        }
    }
}


void Cell_BookManager::on_le_search_textChanged(const QString &arg1)
{
    //查找图书
    QString strCond = QString("where name like '%%1%' or type like '%%1%' or ISBN like '%%1%' or writer like '%%1%'").arg(arg1);
    freshPage(strCond);
}
