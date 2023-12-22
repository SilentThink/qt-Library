#include "dlg_adduser.h"
#include "ui_dlg_adduser.h"
#include "lib/sqlmanager.h"

dlg_addUser::dlg_addUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_addUser)
{
    ui->setupUi(this);
}

dlg_addUser::~dlg_addUser()
{
    delete ui;
}

void dlg_addUser::on_btn_ok_released()
{
    //确定
    QVector<QStringList> v;
    QStringList ldata;
    ldata.push_back(ui->le_userid->text());
    ldata.push_back(ui->le_grade->text());
    ldata.push_back(ui->cb_apartment->currentText());
    ldata.push_back(ui->le_username->text());
    ldata.push_back(ui->le_password->text());
    ldata.push_back(ui->le_nickname->text());
    ldata.push_back(ui->cb_auth->currentText());
    v.push_back(ldata);
    SqlManager::getInstance()->addUsers(v);

    setResult(1);
    this->hide();
}

void dlg_addUser::on_btn_cancel_released()
{
    //取消
    setResult(0);
    this->hide();
}
