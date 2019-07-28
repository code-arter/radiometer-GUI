#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include "plotcurve.h"

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = nullptr);
    ~ImageDialog();

    void set_plot(QChart *plot);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ImageDialog *ui;

    QChartView *chartView;
};

#endif // IMAGEDIALOG_H
