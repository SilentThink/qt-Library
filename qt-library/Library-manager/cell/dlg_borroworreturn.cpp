#include "dlg_borroworreturn.h"
#include "ui_dlg_borroworreturn.h"
#include "lib/sqlmanager.h"
#include <QMessageBox>

Dlg_BorrowOrReturn::Dlg_BorrowOrReturn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_BorrowOrReturn)
{
    ui->setupUi(this);
}

Dlg_BorrowOrReturn::~Dlg_BorrowOrReturn()
{
    delete ui;
}

void Dlg_BorrowOrReturn::setType(QString ISBN)
{
    m_ISBN = ISBN;
    if(m_ISBN != nullptr)
    {
        this->ui->le_ISBN->setText(ISBN);
    }
}

void Dlg_BorrowOrReturn::on_btn_ok_released()
{
    if(m_ISBN != nullptr)
    {
        //borrow
        QStringList ldata;
        ldata.push_back(ui->le_userid->text());
        ldata.push_back(ui->le_ISBN->text());
        ldata.push_back(ui->le_startdate->text());
        ldata.push_back(ui->le_enddate->text());
        SqlManager::getInstance()->borrowBook(m_ISBN);
        SqlManager::getInstance()->addRecord(ldata);
    }
    else
    {
        //return
        QStringList ldata;
        ldata.push_back(ui->le_userid->text());
        ldata.push_back(ui->le_ISBN->text());
        SqlManager::getInstance()->returnBook(ui->le_ISBN->text());
        SqlManager::getInstance()->delRecord(ldata);
    }
    setResult(1);
    this->hide();
}

void Dlg_BorrowOrReturn::on_btn_cancel_released()
{
    setResult(0);
    this->hide();
}

void Dlg_BorrowOrReturn::on_le_userid_textChanged(const QString &arg1)
{
    QString ISBN = ui->le_ISBN->text();
    QString strCond = QString("where userid is '%1' and bookISBN is '%2'")
            .arg(arg1)
            .arg(ISBN);
    auto l = SqlManager::getInstance()->getRecord(strCond);
    if(l.size()>1)
        QMessageBox::warning(nullptr,"错误","有相同的借阅记录重复");
    else if(l.size()==1)
    {
        ui->le_startdate->setText(QString(l[0][2]));
        ui->le_enddate->setText(QString(l[0][3]));
    }
}

void Dlg_BorrowOrReturn::on_le_ISBN_textChanged(const QString &arg1)
{
    QString userid = ui->le_userid->text();
    QString strCond = QString("where userid like '%1' and bookISBN like '%2'")
            .arg(userid)
            .arg(arg1);
    auto l = SqlManager::getInstance()->getRecord(strCond);
    if(l.size()>1)
        QMessageBox::warning(nullptr,"错误","有相同的借阅记录重复");
    else if(l.size()==1)
    {
        ui->le_startdate->setText(QString(l[0][2]));
        ui->le_enddate->setText(QString(l[0][3]));
    }
}
