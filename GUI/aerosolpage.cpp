#include "aerosolpage.h"
#include "ui_aerosolpage.h"

AerosolPage::AerosolPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AerosolPage)
{
    ui->setupUi(this);

    QStringList mix_header = QStringList();
    mix_header << "文件类型(gg, ssa, tau, explicit, moments)" << "文件名";

    QStringList modify_header = QStringList();
    modify_header << "参数(gg, ssa, tau, tau550)" << "范围设置(set, scale)" << "值";

    this->aeros_add_file_dialog = new AtmosAddDialog(QString("文件设置"), mix_header, this);
    this->aeros_add_modify_dialog = new AtmosAddDialog(QString("参数设置"), modify_header, this);

    connect(this->aeros_add_file_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_file_clicked(QString)));
    connect(this->aeros_add_modify_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_modify_clicked(QString)));
}

AerosolPage::~AerosolPage()
{
    delete ui;
}

void AerosolPage::on_add_page_file_clicked(QString val)
{
    this->ui->lineEdit_aerosol_file->setText(val);
}

void AerosolPage::on_add_page_modify_clicked(QString val)
{
    this->ui->lineEdit_aerosol_modify->setText(val);

}

void AerosolPage::on_pushButton_9_clicked()
{
    this->aeros_add_file_dialog->show();
}

void AerosolPage::on_pushButton_10_clicked()
{
    this->aeros_add_modify_dialog->show();

}
