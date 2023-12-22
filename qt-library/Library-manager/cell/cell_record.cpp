#include "cell_record.h"
#include "ui_cell_record.h"

Cell_record::Cell_record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell_record)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    //设置不可编辑
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //自适应宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    freshPage();
}

Cell_record::~Cell_record()
{
    delete ui;
}

void Cell_record::freshPage(QString strCondition)
{
    //刷新页面，获取所有记录
    auto l = SqlManager::getInstance()->getRecord(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"用户id","书籍ISBN","起始日期","还书截止日期"});
    for(int i=0;i<l.size();i++)
    {
        QList<QStandardItem*> items;
        for(int j=0;j<l[i].size();j++)
        {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
}


void Cell_record::on_le_search_textChanged(const QString &arg1)
{
    //查找记录
    QString strCond = QString("where userid like '%%1%' or bookISBN like '%%1%'").arg(arg1);
    freshPage(strCond);
}
