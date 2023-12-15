#include "dlg_borroworreturn.h"
#include "ui_dlg_borroworreturn.h"
#include "lib/sqlmanager.h"

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

void Dlg_BorrowOrReturn::setType(int id)
{
    this->m_id = id;
    if(id!=-1)
    {
        this->ui->le_bookid->setText(QString::number(m_id));
    }
}

void Dlg_BorrowOrReturn::on_btn_ok_released()
{
    if(m_id != -1)
    {
        //borrow
        QStringList ldata;
        ldata.push_back(ui->le_userid->text());
        ldata.push_back(ui->le_bookid->text());
        ldata.push_back(ui->le_startdate->text());
        ldata.push_back(ui->le_enddate->text());

        SqlManager::getInstance()->addRecord(ldata);
    }
    else
    {
        //return
        QStringList ldata;
        ldata.push_back(ui->le_userid->text());
        ldata.push_back(ui->le_bookid->text());
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
