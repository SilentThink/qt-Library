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

void Dlg_BookAddOrUpdate::setType(QString ISBN)
{
    m_ISBN = ISBN;
}

void Dlg_BookAddOrUpdate::initInfo(QString ISBN, QString name, QString price, QString writer, QString type, QString nation, int inventory, int total)
{
    ui->le_ISBN->setText(ISBN);
    ui->le_name->setText(name);
    ui->le_price->setText(price);
    ui->le_writer->setText(writer);
    ui->cb_type->setCurrentText(type);
    ui->cb_nation->setCurrentText(nation);
    ui->le_inventory->setText(QString::number(inventory));
    ui->le_cnt->setText(QString::number(total));
}

void Dlg_BookAddOrUpdate::on_btn_ok_released()
{
    if(m_ISBN != nullptr)
    {
        //updata
        QStringList ldata;
        ldata.push_back(m_ISBN);
        ldata.push_back(ui->le_name->text());
        ldata.push_back(ui->le_price->text());
        ldata.push_back(ui->le_writer->text());
        ldata.push_back(ui->cb_type->currentText());
        ldata.push_back(ui->cb_nation->currentText());
        ldata.push_back(ui->le_inventory->text());
        ldata.push_back(ui->le_cnt->text());
        SqlManager::getInstance()->updateBook(ldata);
    }
    else
    {
        //add
        QVector<QStringList> v;
        QStringList ldata;
        ldata.push_back(ui->le_ISBN->text());
        ldata.push_back(ui->le_name->text());
        ldata.push_back(ui->le_price->text());
        ldata.push_back(ui->le_writer->text());
        ldata.push_back(ui->cb_type->currentText());
        ldata.push_back(ui->cb_nation->currentText());
        ldata.push_back(ui->le_cnt->text());
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
