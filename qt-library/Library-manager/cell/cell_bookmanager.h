#ifndef CELL_BOOKMANAGER_H
#define CELL_BOOKMANAGER_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Cell_BookManager;
}

class Cell_BookManager : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_BookManager(QWidget *parent = nullptr);
    ~Cell_BookManager();
    void freshPage(QString strCondition = "");

private slots:
    void on_btn_add_released();

    void on_btn_return_released();

    void on_btn_change_released();

    void on_btn_del_released();

    void on_btn_borrow_released();

    void on_le_search_textChanged(const QString &arg1);

private:
    Ui::Cell_BookManager *ui;
    QStandardItemModel m_model;
};

#endif // CELL_BOOKMANAGER_H
