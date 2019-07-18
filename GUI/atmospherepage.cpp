#include "atmospherepage.h"
#include "ui_atmospherepage.h"

AtmosPherePage::AtmosPherePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtmosPherePage)
{
    ui->setupUi(this);
    this->atmos_add_mix_dialog = new AtmosAddDialog(this);
    this->atmos_add_pressure_dialog = new AtmosAddDialog(this);
}

AtmosPherePage::~AtmosPherePage()
{
    delete ui;
    delete atmos_add_mix_dialog;
    delete atmos_add_pressure_dialog;
}

void AtmosPherePage::on_pushButton_clicked()
{
    this->atmos_add_mix_dialog->show();
}

void AtmosPherePage::on_pushButton_2_clicked()
{
    this->atmos_add_pressure_dialog->show();
}
