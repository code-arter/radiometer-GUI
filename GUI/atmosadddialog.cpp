#include "atmosadddialog.h"
#include "ui_atmosadddialog.h"

AtmosAddDialog::AtmosAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AtmosAddDialog)
{
    ui->setupUi(this);

}

AtmosAddDialog::~AtmosAddDialog()
{
    delete ui;
}

void AtmosAddDialog::on_buttonBox_accepted()
{
    /*
    QString output_str;
    qDebug() << ui->tableWidget->columnCount();
    qDebug() << ui->tableWidget->rowCount();


    for(int i=0; i<ui->tableWidget->rowCount(); i++)
    {
        QString column_str;
        for(int j=0; j< ui->tableWidget->columnCount(); j++)
        {
            qDebug() << (ui->tableWidget->item(i, j)->isSelected());

            if(column_str.isEmpty())
                ;
            else
                column_str = column_str + ' ' + (ui->tableWidget->item(i, j)->text());

        }

        if(output_str.isEmpty())
            output_str += column_str;
        else
            output_str = output_str + '|'  + column_str;

    }
    qDebug() << output_str;
    this->output_str = output_str;
    */
}
QString AtmosAddDialog::get_output_str()
{
    //return this->output_str;
}

void AtmosAddDialog::on_buttonBox_clicked(QAbstractButton *button)
{

}
