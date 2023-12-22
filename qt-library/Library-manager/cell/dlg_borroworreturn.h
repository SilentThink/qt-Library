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

    void setType(QString ISBN);

private slots:
    void on_btn_ok_released();

    void on_btn_cancel_released();

    void on_le_userid_textChanged(const QString &arg1);

    void on_le_ISBN_textChanged(const QString &arg1);

private:
    Ui::Dlg_BorrowOrReturn *ui;
    QString m_ISBN=nullptr;
};

#endif // DLG_BORROWORRETURN_H
