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
