#ifndef GENERALPAGE_H
#define GENERALPAGE_H

#include <QWidget>
#include "commonfunction.h"


namespace Ui {
class GeneralPage;
}

class GeneralPage : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralPage(QWidget *parent = 0);
    ~GeneralPage();

    void set_single_mode(bool mark);
    double calculate_wave(double input);

    void call_main_run();
    void call_main_save_conf();


signals:
    void GeneralSaveConfEvent(QString path);
    void GeneralSaveOutEvent(QString path);
    void GeneralSavePlotEvent(QString path);
    void GeneralLoadConfEvent(QString path);

private slots:
    void on_pushButton_run_clicked();

    void on_pushButton_save_run_clicked();

    void on_pushButton_conf_save_clicked();

    void on_pushButton_open_plot_clicked();

    void on_pushButton_plot_clicked();

    void on_pushButton_conf_load_clicked();

    void on_comboBox_global_mode_currentIndexChanged(int index);

    void on_lineEdit_wavelength_start_textEdited(const QString &arg1);

    void on_lineEdit_wavecount_start_textEdited(const QString &arg1);

    void on_lineEdit_wavelength_end_textEdited(const QString &arg1);

    void on_lineEdit_wavecount_end_textEdited(const QString &arg1);

    void on_pushButton_source_file_clicked();


    void on_comboBox_multi_set_currentIndexChanged(const QString &arg1);

    void on_comboBox_global_mode_currentIndexChanged(const QString &arg1);

    void on_comboBox_multi_set_activated(int index);

    void on_pushButton_source_file_2_clicked();

    void on_lineEdit_source_file_textChanged(const QString &arg1);

    void on_pushButton_save_run_clicked(bool checked);

private:
    Ui::GeneralPage *ui;
};

#endif // GENERALPAGE_H
