#include "aerosolpage.h"
#include "ui_aerosolpage.h"

AerosolPage::AerosolPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AerosolPage)
{
    ui->setupUi(this);
}

AerosolPage::~AerosolPage()
{
    delete ui;
}
