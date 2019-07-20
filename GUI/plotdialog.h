#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include <QtCharts/QtCharts>
namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(QWidget *parent = nullptr);
    ~PlotDialog();

    void set_plot(QChart *chart);

    void set_init(QStringList &phi, QStringList &umu, QStringList &distance);


private slots:
    void on_pushButton_clicked();

private:
    Ui::PlotDialog *ui;
};

#endif // PLOTDIALOG_H
