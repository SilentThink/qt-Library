#include "cell_main.h"
#include "ui_cell_main.h"
#include "dlg_login.h"
#include <QPushButton>
Cell_Main* Cell_Main::instance = nullptr;
Cell_Main::Cell_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cell_Main)
    ,m_bookPage(nullptr)
    ,m_userPage(nullptr)
    ,m_recordPage(nullptr)
{
    ui->setupUi(this);
    initPage();
}

Cell_Main::~Cell_Main()
{
    delete ui;
}

void Cell_Main::initPage()
{
    m_userPage = new Cell_UserManager(this);
    m_bookPage = new Cell_BookManager(this);
    m_recordPage = new Cell_record(this);
    m_help = new Cell_help(this);
    ui->stackedWidget->addWidget(m_userPage);
    ui->stackedWidget->addWidget(m_bookPage);
    ui->stackedWidget->addWidget(m_recordPage);
    ui->stackedWidget->addWidget(m_help);
    ui->stackedWidget->setCurrentIndex(0);

    auto l = ui->tool->children();
    for(auto it:l)
    {
        if(it->objectName().contains("btn"))
        {
            connect(static_cast<QPushButton*>(it),&QPushButton::released,this,&Cell_Main::dealMenu);
        }
    }
    m_userPage->freshPage();
}

void Cell_Main::freshAll()
{
    m_bookPage->Cell_BookManager::freshPage();
    m_userPage->Cell_UserManager::freshPage();
    m_recordPage->Cell_record::freshPage();
}

void Cell_Main::dealMenu()
{
    auto str = sender()->objectName();
    do
    {
        if("btn_user"==str)
        {
            m_userPage->freshPage();
            ui->stackedWidget->setCurrentIndex(0);
            break;
        }

        if("btn_book"==str)
        {
            m_bookPage->freshPage();
            ui->stackedWidget->setCurrentIndex(1);
            break;
        }


        if("btn_record"==str)
        {
            m_recordPage->freshPage();
            ui->stackedWidget->setCurrentIndex(2);
            break;
        }

        if("btn_help"==str)
        {
            ui->stackedWidget->setCurrentIndex(3);
            break;
        }
    }while(false);
}
