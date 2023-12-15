#include "cell_main.h"

#include <QApplication>
#include "dlg_login.h"
#include "lib/sqlmanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SqlManager::getInstance()->init();
    //qDebug()<<"login ret"<<SqlManager::getInstance()->login("xiaoz","123456");

    Dlg_Login dlg;
    int ret = dlg.exec();
    if(ret == 1)
    {
        Cell_Main w;
        w.show();
        return a.exec();
    }
    if(ret == 0)
    {
        exit(0);
        return 0;
    }
    return 0;
}
