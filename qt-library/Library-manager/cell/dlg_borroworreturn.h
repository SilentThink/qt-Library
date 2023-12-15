#ifndef DLG_BORROWORRETURN_H
#define DLG_BORROWORRETURN_H

#include <QDialog>

namespace Ui {
class Dlg_BorrowOrReturn;
}

class Dlg_BorrowOrReturn : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_BorrowOrReturn(QWidget *parent = nullptr);
    ~Dlg_BorrowOrReturn();

    void setType(int id);

private slots:
    void on_btn_ok_released();

    void on_btn_cancel_released();

private:
    Ui::Dlg_BorrowOrReturn *ui;
    int m_id=-1;
};

#endif // DLG_BORROWORRETURN_H
