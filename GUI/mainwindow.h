#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "generalpage.h"
#include "atmospherepage.h"
#include "inputconfshow.h"
#include "aerosolpage.h"
#include "cloudpage.h"
#include "transmodelpage.h"
#include "waitdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString python_path, QString scripts_path, QWidget *parent = 0);
    ~MainWindow();

    void init_widget_list();
    void get_input();
    QString get_output_str();

    void load_conf(QString path);
    void set_conf(QVector<QString> &line_list);
    void read_conf(QString path, QVector<QString> &line_list);
    void clear_conf();

    QString read_all(QString path);


    void call_python(QString out_path);


private slots:
    void on_general_page_conf_clicked(QString path);
    void on_general_page_conf_load_clicked(QString path);

    void on_general_page_out_clicked(QString path);
    void on_general_page_plot_clicked(QString path);

    void on_tabWidget_currentChanged(int index);
    void on_readoutput();

private:
    GeneralPage *general_page;
    AtmosPherePage *atmosphere_page;
    AerosolPage *aerosol_page;
    CloudPage *cloud_page;
    TransModelPage *trans_mode_page;
    InputConfShow *input_conf_page;

    WaitDialog *wait_dialog;

    QString python_path;
    QString scripts_path;

    QProcess *p;
    QString std_out_path;


    QVector<QPushButton *> button_list;
    QVector<QLineEdit *> edit_list;
    QVector<QComboBox *> box_list;
    QMap<QString, QString> widget_map;

    QMap<QString, QLineEdit *> edit_map;
    QMap<QString, QComboBox *> box_map;
    QString out_path;

    Ui::MainWindow *ui;

signals:
    void GeneralSaveConfEvent(QString path);
    void GeneralSaveOutEvent(QString path);
    void GeneralSavePlotEvent(QString path);
    void GeneralLoadConfEvent(QString path);
};

#endif // MAINWINDOW_H
