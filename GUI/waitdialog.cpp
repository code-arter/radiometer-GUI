#include "waitdialog.h"
#include "ui_waitdialog.h"

WaitDialog::WaitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitDialog)
{
    ui->setupUi(this);

    this->set_init_status(true);
}

WaitDialog::~WaitDialog()
{
    delete ui;
}

void WaitDialog::set_progress_bar(int number)
{
    this->ui->progressBar->setValue(number);
}

void WaitDialog::set_init_status(bool mark)
{
    this->ui->buttonBox->setDisabled(mark);
    //this->setWindowFlags(Qt::WindowCloseButtonHint);
    if(mark)
        this->set_progress_bar(0);
    else
    {
        this->set_progress_bar(100);
        this->ui->textEdit->setText("运行成功！");
    }

}
void WaitDialog::setText(QString out_str)
{
    this->ui->textEdit->setText(out_str);

}
