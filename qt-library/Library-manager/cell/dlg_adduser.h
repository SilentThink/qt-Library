#ifndef DLG_ADDUSER_H
#define DLG_ADDUSER_H

#include <QDialog>

namespace Ui {
class dlg_addUser;
}

class dlg_addUser : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_addUser(QWidget *parent = nullptr);
    ~dlg_addUser();

private slots:
    void on_btn_ok_released();

    void on_btn_cancel_released();

private:
    Ui::dlg_addUser *ui;
};

#endif // DLG_ADDUSER_H
