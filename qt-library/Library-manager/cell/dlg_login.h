#ifndef DIG_LOGIN_H
#define DIG_LOGIN_H

#include <QDialog>

namespace Ui {
class Dlg_Login;
}

class Dlg_Login : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Login(QWidget *parent = nullptr);
    ~Dlg_Login();

private slots:
    void on_btn_login_released();

    void on_btn_exit_released();

private:
    Ui::Dlg_Login *ui;
};

#endif // DIG_LOGIN_H
