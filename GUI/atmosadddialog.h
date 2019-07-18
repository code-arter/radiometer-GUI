#ifndef ATMOSADDDIALOG_H
#define ATMOSADDDIALOG_H

#include <QDialog>
#include "commonfunction.h"

namespace Ui {
class AtmosAddDialog;
}

class AtmosAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AtmosAddDialog(QWidget *parent = nullptr);
    ~AtmosAddDialog();

    QString get_output_str();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::AtmosAddDialog *ui;
    QString output_str;

};

#endif // ATMOSADDDIALOG_H
