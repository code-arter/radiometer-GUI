#ifndef CLOUDPAGE_H
#define CLOUDPAGE_H

#include <QWidget>
#include "commonfunction.h"
#include "atmosadddialog.h"

namespace Ui {
class CloudPage;
}

class CloudPage : public QWidget
{
    Q_OBJECT

public:
    explicit CloudPage(QWidget *parent = nullptr);
    ~CloudPage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_add_page_wc_set_clicked(QString val);
    void on_add_page_wc_modify_clicked(QString val);
    void on_add_page_ic_set_clicked(QString val);
    void on_add_page_ic_modify_clicked(QString val);
    void on_add_page_ic_fu_clicked(QString val);
    void on_add_page_cloudcover_clicked(QString val);

    void on_pushButton_2_clicked();

private:
    Ui::CloudPage *ui;

    AtmosAddDialog *cloud_add_wc_set_dialog;
    AtmosAddDialog *cloud_add_wc_modify_dialog;
    AtmosAddDialog *cloud_add_ic_set_dialog;
    AtmosAddDialog *cloud_add_ic_modify_dialog;

    AtmosAddDialog *cloud_add_ic_fu_dialog;
    AtmosAddDialog *cloud_add_cloudcover_dialog;

};

#endif // CLOUDPAGE_H
