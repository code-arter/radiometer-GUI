#include "cloudpage.h"
#include "ui_cloudpage.h"

CloudPage::CloudPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CloudPage)
{
    ui->setupUi(this);

    QStringList wc_set_header = QStringList();
    //wc_set_header << "文件类型(1d)" << "云底高(km)" << "云厚度(km)" << "密度(g/m3)" << "有效粒子半径(um)";
    wc_set_header << "云底高(km)" << "云厚度(km)" << "密度(g/m3)" << "有效粒子半径(um)";

    this->cloud_add_wc_set_dialog = new AtmosAddDialog(QString("混合比设置"), wc_set_header, this);

    QStringList wc_modify_header = QStringList();
    wc_modify_header << "参数(gg, ssa, tau, tau550)" << "范围设置(set, scale)" << "值";
    this->cloud_add_wc_modify_dialog = new AtmosAddDialog(QString("混合比设置"), wc_modify_header, this);

    QStringList ic_set_header = QStringList();
    //ic_set_header << "文件类型(1d)" << "云底高(km)" << "云厚度(km)" << "密度(g/m3)" << "有效粒子半径(um)";
    ic_set_header << "云底高(km)" << "云厚度(km)" << "密度(g/m3)" << "有效粒子半径(um)";

    this->cloud_add_ic_set_dialog = new AtmosAddDialog(QString("混合比设置"), ic_set_header, this);

    QStringList ic_modify_header = QStringList();
    ic_modify_header << "参数(gg, ssa, tau, tau550)" << "范围设置(set, scale)" << "值";
    this->cloud_add_ic_modify_dialog = new AtmosAddDialog(QString("混合比设置"), ic_modify_header, this);

    QStringList ic_fu_header = QStringList();
    ic_fu_header << "id1(reff_def, deltascaling)" << "id2(on, off)" << "值";
    this->cloud_add_ic_fu_dialog = new AtmosAddDialog(QString("混合比设置"), ic_fu_header, this);

    QStringList cloudcover_header = QStringList();
    cloudcover_header << "云类型(wc, ic)" << "云覆盖(0-1)" << "值";
    this->cloud_add_cloudcover_dialog = new AtmosAddDialog(QString("柱体含量设置"), cloudcover_header, this);

    connect(this->cloud_add_wc_set_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_wc_set_clicked(QString)));
    connect(this->cloud_add_wc_modify_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_wc_modify_clicked(QString)));
    connect(this->cloud_add_ic_set_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_ic_set_clicked(QString)));
    connect(this->cloud_add_ic_modify_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_ic_modify_clicked(QString)));
    connect(this->cloud_add_ic_fu_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_wc_ic_fu_clicked(QString)));
    connect(this->cloud_add_cloudcover_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_cloudcover_clicked(QString)));

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

void CloudPage::on_pushButton_9_clicked()
{
    this->cloud_add_wc_set_dialog->show();
}

void CloudPage::on_pushButton_10_clicked()
{
    this->cloud_add_wc_modify_dialog->show();
}

void CloudPage::on_pushButton_11_clicked()
{
    this->cloud_add_ic_set_dialog->show();
}

void CloudPage::on_pushButton_12_clicked()
{
    this->cloud_add_ic_modify_dialog->show();
}

void CloudPage::on_pushButton_15_clicked()
{
    this->cloud_add_ic_fu_dialog->show();
}

void CloudPage::on_pushButton_16_clicked()
{
    this->cloud_add_cloudcover_dialog->show();
}

void CloudPage::on_add_page_wc_set_clicked(QString val)
{
    this->ui->lineEdit_wc_set->setText(val);

}
void CloudPage::on_add_page_wc_modify_clicked(QString val)
{
    this->ui->lineEdit_wc_modify->setText(val);

}
void CloudPage::on_add_page_ic_set_clicked(QString val)
{
    this->ui->lineEdit_ic_set->setText(val);

}
void CloudPage::on_add_page_ic_modify_clicked(QString val)
{
    this->ui->lineEdit_ic_modify->setText(val);

}
void CloudPage::on_add_page_ic_fu_clicked(QString val)
{
    this->ui->lineEdit_ic_fu->setText(val);

}
void CloudPage::on_add_page_cloudcover_clicked(QString val)
{
    this->ui->lineEdit_cloudcover->setText(val);

}

void CloudPage::on_pushButton_2_clicked()
{
    this->ui->lineEdit_wc_file->clear();
}
