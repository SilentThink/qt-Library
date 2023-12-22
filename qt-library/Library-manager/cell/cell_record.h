#ifndef CELL_RECORD_H
#define CELL_RECORD_H

#include <QStandardItemModel>
#include <QWidget>
#include "lib/sqlmanager.h"

namespace Ui {
class Cell_record;
}

class Cell_record : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_record(QWidget *parent = nullptr);
    ~Cell_record();
    void freshPage(QString strCondition="");

private slots:

    void on_le_search_textChanged(const QString &arg1);

private:
    Ui::Cell_record *ui;
    QStandardItemModel m_model;
};

#endif // CELL_RECORD_H
