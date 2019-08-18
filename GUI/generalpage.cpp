#include "generalpage.h"
#include "ui_generalpage.h"
#include "mainwindow.h"


GeneralPage::GeneralPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralPage)
{
    ui->setupUi(this);

    this->set_single_mode(true);
    this->on_comboBox_multi_set_activated(0);
    this->ui->pushButton_source_file_2->hide();
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
    QString path = this->ui->lineEdit_out_file->text();
    QString x_label;
    QString y_label;
    if(this->ui->comboBox_output_user->currentIndex() == 2)
        x_label = '0';
    else
        x_label = '1';

    if(this->ui->comboBox_output_process->currentText() == "per_nm")
        y_label = '0';
    else
        y_label = '1';
    QString plot_path = QString("%1-%2-%3").arg(path).arg(x_label).arg(y_label);
    if(this->ui->comboBox_global_mode->currentIndex() == 0)
        this->ui->lineEdit_plot_file->setText(plot_path);
    else {
        this->ui->lineEdit_plot_file->setText(path);
    }
}

void GeneralPage::on_pushButton_save_run_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,QStringLiteral("保存为"),"test.out");
    if(!path.isEmpty())
    {
        this->ui->lineEdit_out_file->setText(path);
        this->call_main_run();
    }

    QString x_label;
    QString y_label;
    if(this->ui->comboBox_output_user->currentIndex() == 2)
        x_label = '0';
    else
        x_label = '1';

    if(this->ui->comboBox_output_process->currentText() == "per_nm")
        y_label = '0';
    else
        y_label = '1';
    QString plot_path = QString("%1-%2-%3").arg(path).arg(x_label).arg(y_label);
    if(this->ui->comboBox_global_mode->currentIndex() == 0)
        this->ui->lineEdit_plot_file->setText(plot_path);
    else {
        this->ui->lineEdit_plot_file->setText(path);
    }
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
    QString path=QFileDialog::getSaveFileName(this,QStringLiteral("另存为"),"test.conf");
    if(!path.isEmpty())
    {
        this->ui->lineEdit_conf_file->setText(path);

        this->call_main_save_conf();
    }
}

void GeneralPage::on_pushButton_open_plot_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\");
    if(!path.isEmpty())
    {
        this->ui->lineEdit_plot_file->setText(path);

        emit GeneralSavePlotEvent(path);
    }

}

void GeneralPage::on_pushButton_plot_clicked()
{
    QString path = this->ui->lineEdit_plot_file->text();
    if(!path.isEmpty())
    {
        emit GeneralSavePlotEvent(path);
    }
}

void GeneralPage::on_pushButton_conf_load_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,QStringLiteral("载入"),"C:\\",tr("All Files (*);;Text Files (*.txt)"));
    if(!path.isEmpty())
    {
        this->ui->lineEdit_conf_file->setText(path);
        emit GeneralLoadConfEvent(path);
    }

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
    if(mark)
    {
        this->ui->comboBox_multi_set->setCurrentIndex(0);
        this->ui->comboBox_multi_set->setDisabled(true);
    }
    else
    {
        this->ui->comboBox_multi_set->setDisabled(false);
    }
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

void GeneralPage::on_comboBox_multi_set_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "观测俯仰角")
    {
        this->ui->lineEdit_umu_start->setDisabled(false);
        this->ui->lineEdit_umu_end->setDisabled(false);
        this->ui->lineEdit_umu_step->setDisabled(false);

        this->ui->lineEdit_phi_start->setDisabled(false);
        this->ui->lineEdit_phi_end->setDisabled(true);
        this->ui->lineEdit_phi_step->setDisabled(true);

        this->ui->lineEdit_height_start->setDisabled(false);
        this->ui->lineEdit_height_end->setDisabled(true);
        this->ui->lineEdit_height_step->setDisabled(true);

    }
    else if(arg1 == "观测方位角")
    {
        this->ui->lineEdit_umu_start->setDisabled(false);
        this->ui->lineEdit_umu_end->setDisabled(true);
        this->ui->lineEdit_umu_step->setDisabled(true);

        this->ui->lineEdit_phi_start->setDisabled(false);
        this->ui->lineEdit_phi_end->setDisabled(false);
        this->ui->lineEdit_phi_step->setDisabled(false);

        this->ui->lineEdit_height_start->setDisabled(false);
        this->ui->lineEdit_height_end->setDisabled(true);
        this->ui->lineEdit_height_step->setDisabled(true);

    }
    else if(arg1 == "距离")
    {
        this->ui->lineEdit_umu_start->setDisabled(false);
        this->ui->lineEdit_umu_end->setDisabled(true);
        this->ui->lineEdit_umu_step->setDisabled(true);

        this->ui->lineEdit_phi_start->setDisabled(false);
        this->ui->lineEdit_phi_end->setDisabled(true);
        this->ui->lineEdit_phi_step->setDisabled(true);

        this->ui->lineEdit_height_start->setDisabled(false);
        this->ui->lineEdit_height_end->setDisabled(false);
        this->ui->lineEdit_height_step->setDisabled(false);

    }
    else
    {
        this->ui->lineEdit_umu_end->setDisabled(true);
        this->ui->lineEdit_umu_step->setDisabled(true);

        this->ui->lineEdit_phi_end->setDisabled(true);
        this->ui->lineEdit_phi_step->setDisabled(true);

        this->ui->lineEdit_height_end->setDisabled(true);
        this->ui->lineEdit_height_step->setDisabled(true);
    }
}

void GeneralPage::on_comboBox_global_mode_currentIndexChanged(const QString &arg1)
{

}

void GeneralPage::on_comboBox_multi_set_activated(int index)
{
    if(index == 0)
    {
        this->ui->lineEdit_umu_end->setDisabled(true);
        this->ui->lineEdit_umu_step->setDisabled(true);

        this->ui->lineEdit_phi_end->setDisabled(true);
        this->ui->lineEdit_phi_step->setDisabled(true);

        this->ui->lineEdit_height_end->setDisabled(true);
        this->ui->lineEdit_height_step->setDisabled(true);
    }
}

void GeneralPage::on_pushButton_source_file_2_clicked()
{
    this->ui->lineEdit_source_file->clear();
}

void GeneralPage::on_lineEdit_source_file_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        this->ui->pushButton_source_file_2->hide();
    else
        this->ui->pushButton_source_file_2->show();
}

void GeneralPage::on_pushButton_save_run_clicked(bool checked)
{

}
