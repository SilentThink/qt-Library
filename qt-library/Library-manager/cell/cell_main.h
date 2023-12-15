#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include <QMainWindow>
#include "cell_bookmanager.h"
#include "cell_record.h"
#include "cell_usermanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Cell_Main; }
QT_END_NAMESPACE

class Cell_Main : public QMainWindow
{
    Q_OBJECT

public:
    Cell_Main(QWidget *parent = nullptr);
    ~Cell_Main();
    void initPage();

public slots:
    void dealMenu();
private:
    Ui::Cell_Main *ui;
    Cell_BookManager *m_bookPage;
    Cell_UserManager *m_userPage;
    Cell_record *m_recordPage;
};
#endif // CELL_MAIN_H
