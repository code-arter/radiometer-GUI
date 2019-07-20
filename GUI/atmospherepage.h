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
    AtmosAddDialog *atmos_add_modify_dialog;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_add_page_mix_clicked(QString val);
    void on_add_page_modify_clicked(QString val);



private:
    Ui::AtmosPherePage *ui;
};

#endif // ATMOSPHEREPAGE_H
