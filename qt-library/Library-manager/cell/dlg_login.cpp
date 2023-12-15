#include "dlg_login.h"
#include "ui_dlg_login.h"
#include <QMessageBox>

#define USERNAME "manager"
#define PASSWORD "88888888"

Dlg_Login::Dlg_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_Login)
{
    ui->setupUi(this);
}

Dlg_Login::~Dlg_Login()
{
    delete ui;
}

void Dlg_Login::on_btn_login_released()
{
    QString username = ui->le_user->text();
    QString password = ui->le_password->text();
    if(username==USERNAME&&password==PASSWORD)
    {
        setResult(1);
        hide();
    }
    else
    {
        QMessageBox::warning(nullptr,"登录失败","请输入正确的账号和密码!");
    }
}

void Dlg_Login::on_btn_exit_released()
{
    setResult(0);
    hide();
}
