#ifndef AEROSOLPAGE_H
#define AEROSOLPAGE_H

#include <QWidget>
#include "atmosadddialog.h"

namespace Ui {
class AerosolPage;
}

class AerosolPage : public QWidget
{
    Q_OBJECT

public:
    explicit AerosolPage(QWidget *parent = nullptr);
    ~AerosolPage();

private slots:
    void on_pushButton_9_clicked();

    void on_add_page_file_clicked(QString val);
    void on_add_page_modify_clicked(QString val);

    void on_pushButton_10_clicked();

private:
    Ui::AerosolPage *ui;

    AtmosAddDialog *aeros_add_file_dialog;
    AtmosAddDialog *aeros_add_modify_dialog;


};

#endif // AEROSOLPAGE_H
