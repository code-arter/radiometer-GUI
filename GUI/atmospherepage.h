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



    void on_pushButton_4_clicked();

    void on_lineEdit_atmos_define_textChanged(const QString &arg1);

    void on_pushButton_atmos_define_clear_clicked();

    void on_lineEdit_mixing_ratio_textChanged(const QString &arg1);

    void on_pushButton_mol_modify_clear_clicked();

    void on_lineEdit_mol_modify_textChanged(const QString &arg1);

    void on_pushButton_mixing_ratio_clear_clicked();

private:
    Ui::AtmosPherePage *ui;
};

#endif // ATMOSPHEREPAGE_H
