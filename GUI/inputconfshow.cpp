#include "inputconfshow.h"
#include "ui_inputconfshow.h"

InputConfShow::InputConfShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputConfShow)
{
    ui->setupUi(this);
}

InputConfShow::~InputConfShow()
{
    delete ui;
}

void InputConfShow::setInputConf(QString input_str)
{
    this->ui->textEdit->setText(input_str);

}
