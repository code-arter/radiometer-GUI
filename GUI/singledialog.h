#ifndef SINGLEDIALOG_H
#define SINGLEDIALOG_H

#include <QDialog>
#include "imagedialog.h"
#include "plotcurve.h"

namespace Ui {
class SingleDialog;
}

class SingleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SingleDialog(QWidget *parent = nullptr);

    void set_init(QString plot_x, QString plot_y, QVector<QString> &line_list);

    int make_points(QVector<QString> &line_list, QList<QPointF> &data_list, double &x_min, double &x_max, double &y_min, double &y_max);

    int convert_x(QVector<QString> &line_list);
    ~SingleDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SingleDialog *ui;

    QVector<QString> line_list;
    QString x_label;
    int y_label;


    QString plot_x;
    QString plot_y;

    ImageDialog *image_dialog;
};

#endif // SINGLEDIALOG_H
