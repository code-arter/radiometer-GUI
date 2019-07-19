#include "cloudpage.h"
#include "ui_cloudpage.h"

CloudPage::CloudPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CloudPage)
{
    ui->setupUi(this);
}

CloudPage::~CloudPage()
{
    delete ui;
}

void CloudPage::on_pushButton_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_wc_file->setText(path);
}

void CloudPage::on_pushButton_6_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_ic_file->setText(path);
}

void CloudPage::on_pushButton_7_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_ic_raytracing_file->setText(path);
}

void CloudPage::on_pushButton_8_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_cloud_fraction_file->setText(path);
}
