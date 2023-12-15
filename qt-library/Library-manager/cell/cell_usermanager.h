#ifndef CELL_USERMANAGER_H
#define CELL_USERMANAGER_H

#include <QWidget>
#include <QStandardItemModel>
#include "lib/sqlmanager.h"

namespace Ui {
class Cell_UserManager;
}

class Cell_UserManager : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_UserManager(QWidget *parent = nullptr);
    ~Cell_UserManager();

    void freshPage(QString strCondition="");
private slots:
    void on_btn_del_released();

    void on_btn_import_released();

    void on_le_search_textChanged(const QString &arg1);

private:
    Ui::Cell_UserManager *ui;
    QStandardItemModel m_model;
};

#endif // CELL_USERMANAGER_H
