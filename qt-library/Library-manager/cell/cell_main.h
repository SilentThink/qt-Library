#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include <QMainWindow>
#include "cell_bookmanager.h"
#include "cell_record.h"
#include "cell_usermanager.h"
#include "cell_help.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Cell_Main; }
QT_END_NAMESPACE

class Cell_Main : public QMainWindow
{
    Q_OBJECT

public:
    Cell_Main(QWidget *parent = nullptr);
    ~Cell_Main();
    static Cell_Main* instance;
    static Cell_Main* getInstance(){
        if(instance == nullptr) {
            instance = new Cell_Main();
        }
        return instance;
    }
    void initPage();
    void freshAll();

public slots:
    void dealMenu();
private:
    Ui::Cell_Main *ui;
    Cell_BookManager *m_bookPage;
    Cell_UserManager *m_userPage;
    Cell_record *m_recordPage;
    Cell_help *m_help;
};
#endif // CELL_MAIN_H
