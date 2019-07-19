#ifndef ATMOSPHEREPAGE_H
#define ATMOSPHEREPAGE_H

#include <QWidget>
#include "commonfunction.h"
#include "atmosadddialog.h"

namespace Ui {
class AtmosPherePage;
}

class AtmosPherePage : public QWidget
{
    Q_OBJECT

public:
    explicit AtmosPherePage(QWidget *parent = 0);
    ~AtmosPherePage();

    AtmosAddDialog *atmos_add_mix_dialog;
    AtmosAddDialog *atmos_add_pressure_dialog;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AtmosPherePage *ui;
};

#endif // ATMOSPHEREPAGE_H
