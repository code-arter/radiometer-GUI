#include "atmospherepage.h"
#include "ui_atmospherepage.h"

AtmosPherePage::AtmosPherePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtmosPherePage)
{
    ui->setupUi(this);
    QStringList mix_header = QStringList();
    mix_header << "类型(o2/h2o/co2/no2/ch4/n2o/f11/f12/f22)" << "值";

    QStringList modify_header = QStringList();
    modify_header << "类型(O3/O2/H2O/CO2/NO2/BRO/\nOCLO/HCHO/O4/SO2/CH4/N2O/CO/N2)" << "值" << "单位(du/cm_2/mm)";

    this->atmos_add_mix_dialog = new AtmosAddDialog(QString("混合比设置"), mix_header, this);
    this->atmos_add_modify_dialog = new AtmosAddDialog(QString("柱体含量设置"), modify_header, this);

    this->ui->pushButton_atmos_define_clear->hide();
    this->ui->pushButton_mixing_ratio_clear->hide();
    this->ui->pushButton_mol_modify_clear->hide();

    connect(this->atmos_add_mix_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_mix_clicked(QString)));
    connect(this->atmos_add_modify_dialog, SIGNAL(AddDialogSaveEvent(QString)),this,SLOT(on_add_page_modify_clicked(QString)));

}

AtmosPherePage::~AtmosPherePage()
{
    delete ui;
    delete atmos_add_mix_dialog;
    delete atmos_add_modify_dialog;
}

void AtmosPherePage::on_pushButton_clicked()
{
    this->atmos_add_mix_dialog->show();
}

void AtmosPherePage::on_pushButton_2_clicked()
{
    this->atmos_add_modify_dialog->show();
}

void AtmosPherePage::on_pushButton_3_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_atmos_define->setText(path);
}

void AtmosPherePage::on_add_page_mix_clicked(QString val)
{
    this->ui->lineEdit_mixing_ratio->setText(val);
}

void AtmosPherePage::on_add_page_modify_clicked(QString val)
{
    this->ui->lineEdit_mol_modify->setText(val);

}

void AtmosPherePage::on_pushButton_4_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_atmos_define->setText(path);
}

void AtmosPherePage::on_lineEdit_atmos_define_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        this->ui->pushButton_atmos_define_clear->hide();
    else
        this->ui->pushButton_atmos_define_clear->show();
}

void AtmosPherePage::on_pushButton_atmos_define_clear_clicked()
{
    this->ui->lineEdit_atmos_define->clear();

}

void AtmosPherePage::on_lineEdit_mixing_ratio_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        this->ui->pushButton_mixing_ratio_clear->hide();
    else
        this->ui->pushButton_mixing_ratio_clear->show();
}

void AtmosPherePage::on_pushButton_mol_modify_clear_clicked()
{
    this->ui->lineEdit_mol_modify->clear();

}

void AtmosPherePage::on_lineEdit_mol_modify_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        this->ui->pushButton_mol_modify_clear->hide();
    else
        this->ui->pushButton_mol_modify_clear->show();
}

void AtmosPherePage::on_pushButton_mixing_ratio_clear_clicked()
{
    this->ui->lineEdit_mixing_ratio->clear();
}
