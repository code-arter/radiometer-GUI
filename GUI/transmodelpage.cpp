#include "transmodelpage.h"
#include "ui_transmodelpage.h"

TransModelPage::TransModelPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransModelPage)
{
    ui->setupUi(this);
}

TransModelPage::~TransModelPage()
{
    delete ui;
}
