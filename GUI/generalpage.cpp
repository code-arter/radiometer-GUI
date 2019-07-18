#include "generalpage.h"
#include "ui_generalpage.h"
#include "mainwindow.h"


GeneralPage::GeneralPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralPage)
{
    ui->setupUi(this);

    this->set_single_mode(true);
}

GeneralPage::~GeneralPage()
{
    delete ui;
}

void GeneralPage::on_pushButton_run_clicked()
{
    if(this->ui->lineEdit_out_file->text().isEmpty())
    {
        this->on_pushButton_save_run_clicked();
    }
    else {
        this->call_main_run();
    }
}

void GeneralPage::on_pushButton_load_clicked()
{
    ;
}

void GeneralPage::on_pushButton_save_run_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,QStringLiteral("保存为"),"test.out",tr("Text Files(*.txt)"));

    this->ui->lineEdit_out_file->setText(path);
    this->ui->lineEdit_plot_file->setText(path);

    this->call_main_run();
}

void GeneralPage::call_main_run()
{
    QString path = this->ui->lineEdit_out_file->text();
    if(!path.isEmpty())
        emit GeneralSaveOutEvent(path);
}

void GeneralPage::call_main_save_conf()
{
    QString path = this->ui->lineEdit_conf_file->text();
    if(!path.isEmpty())
        emit GeneralSaveConfEvent(path);
}

void GeneralPage::on_pushButton_conf_save_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,QStringLiteral("另存为"),"test.conf",tr("Text Files(*.txt)"));
    if(!path.isEmpty())
    {
        this->ui->lineEdit_conf_file->setText(path);

        this->call_main_save_conf();
    }
}

void GeneralPage::on_pushButton_open_plot_clicked()
{
    QString path;
    if(this-ui->lineEdit_plot_file->text().isEmpty())
    {
        path=QFileDialog::getSaveFileName(this,QStringLiteral("保存为"),"test.plot",tr("Text Files(*.txt)"));
    }
    else {
        path = this->ui->lineEdit_plot_file->text();
    }
    this->ui->lineEdit_plot_file->setText(path);

    emit GeneralSaveOutEvent(path);

}

void GeneralPage::on_pushButton_plot_clicked()
{
    this->on_pushButton_open_plot_clicked();
}

void GeneralPage::on_pushButton_conf_load_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_conf_file->setText(path);

    emit GeneralLoadConfEvent(path);
}

void GeneralPage::on_comboBox_global_mode_currentTextChanged(const QString &arg1)
{
    ;
}

void GeneralPage::on_comboBox_global_mode_currentIndexChanged(int index)
{
    if(index == 0)
    {
        this->set_single_mode(true);
    }
    else {
        this->set_single_mode(false);
    }
}

void GeneralPage::set_single_mode(bool mark)
{
    this->ui->lineEdit_phi_end->setDisabled(mark);
    this->ui->lineEdit_phi_step->setDisabled(mark);
    this->ui->lineEdit_umu_end->setDisabled(mark);
    this->ui->lineEdit_umu_step->setDisabled(mark);
    this->ui->lineEdit_height_end->setDisabled(mark);
    this->ui->lineEdit_height_step->setDisabled(mark);
}

double GeneralPage::calculate_wave(double input)
{
    if(input != 0.0)
        return 10000 / input;
    else {
        return 0.0;
    }

}

void GeneralPage::on_lineEdit_wavelength_start_textEdited(const QString &arg1)
{
    double wavecount = this->calculate_wave(arg1.toDouble());
    this->ui->lineEdit_wavecount_start->setText(QString::number(wavecount,10,5));
}

void GeneralPage::on_lineEdit_wavecount_start_textEdited(const QString &arg1)
{
    double wavelength = this->calculate_wave(arg1.toDouble());
    this->ui->lineEdit_wavelength_start->setText(QString::number(wavelength,10,5));
}

void GeneralPage::on_lineEdit_wavelength_end_textEdited(const QString &arg1)
{
    qDebug() << arg1;
    double wavecount = this->calculate_wave(arg1.toDouble());
    this->ui->lineEdit_wavecount_end->setText(QString::number(wavecount,10,5));
}

void GeneralPage::on_lineEdit_wavecount_end_textEdited(const QString &arg1)
{
    double wavelength = this->calculate_wave(arg1.toDouble());
    this->ui->lineEdit_wavelength_end->setText(QString::number(wavelength,10,5));
}

void GeneralPage::on_pushButton_source_file_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    this->ui->lineEdit_source_file->setText(path);
}
