#ifndef DLG_BOOKADDORUPDATE_H
#define DLG_BOOKADDORUPDATE_H

#include <QDialog>

namespace Ui {
class Dlg_BookAddOrUpdate;
}

class Dlg_BookAddOrUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_BookAddOrUpdate(QWidget *parent = nullptr);
    ~Dlg_BookAddOrUpdate();

    void setType(int id);

private slots:
    void on_btn_ok_released();

    void on_btn_cancel_released();

private:
    Ui::Dlg_BookAddOrUpdate *ui;
    int m_id=-1;
};

#endif // DLG_BOOKADDORUPDATE_H
