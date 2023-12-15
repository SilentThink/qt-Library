#include "dlg_bookaddorupdate.h"
#include "ui_dlg_bookaddorupdate.h"
#include "lib/sqlmanager.h"

Dlg_BookAddOrUpdate::Dlg_BookAddOrUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_BookAddOrUpdate)
{
    ui->setupUi(this);
}

Dlg_BookAddOrUpdate::~Dlg_BookAddOrUpdate()
{
    delete ui;
}

void Dlg_BookAddOrUpdate::setType(int id)
{
    m_id = id;
}

void Dlg_BookAddOrUpdate::on_btn_ok_released()
{
    if(m_id != -1)
    {
        //updata
        QStringList ldata;
        ldata.push_back(QString::number(m_id));
        ldata.push_back(ui->le_name->text());
        ldata.push_back(ui->le_price->text());
        ldata.push_back(ui->cb_type1->currentText());
        ldata.push_back(ui->cb_type2->currentText());
        ldata.push_back(ui->cb_type3->currentText());
        ldata.push_back(ui->le_cnt->text());
        SqlManager::getInstance()->updateBooks(ldata);
    }
    else
    {
        //add
        QVector<QStringList> v;
        QStringList ldata;
        ldata.push_back(ui->le_name->text());
        ldata.push_back(ui->le_price->text());
        ldata.push_back(ui->cb_type1->currentText());
        ldata.push_back(ui->cb_type2->currentText());
        ldata.push_back(ui->cb_type3->currentText());
        ldata.push_back(ui->le_cnt->text());
        v.push_back(ldata);
        SqlManager::getInstance()->addBooks(v);
    }
    setResult(1);
    this->hide();
}

void Dlg_BookAddOrUpdate::on_btn_cancel_released()
{
    setResult(0);
    this->hide();
}
