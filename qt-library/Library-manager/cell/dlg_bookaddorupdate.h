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

    void setType(QString ISBN);
    void initInfo(QString ISBN,QString name,QString price,QString writer,QString type,QString nation,int inventory,int total);

private slots:
    void on_btn_ok_released();

    void on_btn_cancel_released();

private:
    Ui::Dlg_BookAddOrUpdate *ui;
    QString m_ISBN=nullptr;
};

#endif // DLG_BOOKADDORUPDATE_H
