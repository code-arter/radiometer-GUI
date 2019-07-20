#include "plotdialog.h"
#include "ui_plotdialog.h"

PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

void PlotDialog::set_plot(QChart *chart)
{
    //this->ui->graphicsView->setc;
}
void PlotDialog::set_init(QStringList &phi, QStringList &umu, QStringList &distance)
{
    this->ui->comboBox_plot_phi->clear();
    this->ui->comboBox_plot_umu->clear();
    this->ui->comboBox_plot_distance->clear();

    for(int index = 0; index < phi.size(); index++)
    {
        this->ui->comboBox_plot_phi->addItem(phi[index]);
    }
    for(int index = 0; index < umu.size(); index++)
    {
        this->ui->comboBox_plot_umu->addItem(umu[index]);
    }
    for(int index = 0; index < distance.size(); index++)
    {
        this->ui->comboBox_plot_distance->addItem(distance[index]);
    }
    //this->ui->
    //this->ui->graphicsView->setc;
}

void PlotDialog::on_pushButton_clicked()
{
    QString plot_method = this->ui->comboBox->currentText();
    if(plot_method == "spectral")
    {
        ;
    }
    else
    {
        if(this->ui->comboBox_plot_phi->count() != 1)
        {
            ;
        }
        else if(this->ui->comboBox_plot_umu->count() != 1)
        {
            ;
        }
        else if(this->ui->comboBox_plot_distance->count() != 1)
        {
            ;
        }
    }
}
