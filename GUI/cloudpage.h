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

    void on_pushButton_wc_file_clear_clicked();

    void on_pushButton_wc_set_clear_clicked();

    void on_pushButton_wc_modify_clear_clicked();

    void on_pushButton_ic_file_clear_clicked();

    void on_pushButton_ic_set_clear_clicked();

    void on_pushButton_ic_modify_clear_clicked();

    void on_pushButton_ic_fu_clear_clicked();

    void on_pushButton_ic_raytracing_clear_clicked();

    void on_pushButton_cloud_fraction_clear_clicked();

    void on_pushButton_cloudcover_clear_clicked();

    void on_lineEdit_wc_file_textChanged(const QString &arg1);

    void on_lineEdit_wc_set_textChanged(const QString &arg1);

    void on_lineEdit_wc_modify_textChanged(const QString &arg1);

    void on_lineEdit_ic_file_textChanged(const QString &arg1);

    void on_lineEdit_ic_set_textChanged(const QString &arg1);

    void on_lineEdit_ic_modify_textChanged(const QString &arg1);

    void on_lineEdit_ic_fu_textChanged(const QString &arg1);

    void on_lineEdit_ic_raytracing_file_windowIconTextChanged(const QString &iconText);

    void on_lineEdit_ic_raytracing_file_textChanged(const QString &arg1);

    void on_lineEdit_cloud_fraction_file_textChanged(const QString &arg1);

    void on_lineEdit_cloudcover_textChanged(const QString &arg1);

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
