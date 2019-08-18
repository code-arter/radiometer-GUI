#ifndef BATCHDIALOG_H
#define BATCHDIALOG_H

#include <QDialog>
#include <QtCharts/QtCharts>
#include <imagedialog.h>
#include "plotcurve.h"

namespace Ui {
class BatchDialog;
}

class BatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BatchDialog(QWidget *parent = nullptr);
    ~BatchDialog();

    void set_init(QString dir);

    void read_conf(QString path, QVector<QString> &line_list);

    int make_points(QVector<QString> &line_list, QList<QPointF> &data_list, double &x_min, double &x_max, double &y_min, double &y_max);


private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::BatchDialog *ui;

    QString plot_dir;
    QStringList phi;
    QStringList umu;
    QStringList distance;
    QStringList output_process;
    QStringList output_quantity;
    QStringList plot_regex;

    ImageDialog *image_dialog;

    QString x_label;
    int y_label;


    QString plot_x;
    QString plot_y;
};

#endif // BATCHDIALOG_H
