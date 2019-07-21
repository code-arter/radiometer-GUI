#include "atmosadddialog.h"
#include "ui_atmosadddialog.h"

AtmosAddDialog::AtmosAddDialog(QString main_name, QStringList header_list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AtmosAddDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(main_name);

    this->init_tab_widget(header_list);

}
void AtmosAddDialog::init_tab_widget(QStringList col_header, int row_count)
{
    ui->tableWidget->setColumnCount(col_header.size());
    ui->tableWidget->setRowCount(row_count);

    /* 设置 tableWidget */
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->setColumnWidth(1, 500);

    ui->tableWidget->setHorizontalHeaderLabels(col_header);

    ui->tableWidget->verticalHeader()->setVisible(false); // 隐藏水平header
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);   // 单个选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个
}


AtmosAddDialog::~AtmosAddDialog()
{
    delete ui;
}
QString AtmosAddDialog::get_val()
{

}
void AtmosAddDialog::on_buttonBox_accepted()
{
    QString outptu_str = this->get_output_str();
    emit AddDialogSaveEvent(outptu_str);
}
QString AtmosAddDialog::get_output_str()
{
    QString output_str;

    for(int i=0; i<ui->tableWidget->rowCount(); i++)
    {
        QString column_str;
        for(int j=0; j< ui->tableWidget->columnCount(); j++)
        {
            if(ui->tableWidget->item(i, j) != NULL)
            {
                if(column_str.isEmpty())
                    column_str = ui->tableWidget->item(i, j)->text();
                else
                    column_str = column_str + ' ' + (ui->tableWidget->item(i, j)->text());
            }
        }
        if(!column_str.isEmpty())
        {
            QString item_str = column_str;

            if(output_str.isEmpty())
                output_str = item_str;
            else {
                output_str = output_str + "; " + item_str;
            }

        }
    }
    //qDebug() << output_str;
    this->output_str = output_str;
    return output_str;
}

void AtmosAddDialog::on_buttonBox_clicked(QAbstractButton *button)
{

}
