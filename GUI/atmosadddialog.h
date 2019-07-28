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
    explicit AtmosAddDialog(QString main_key,  QStringList header_list, QWidget *parent = nullptr);
    ~AtmosAddDialog();

    QString get_output_str();
    void init_tab_widget(QStringList col_header, int row_count=5);



private slots:
    void on_buttonBox_accepted();

private:
    Ui::AtmosAddDialog *ui;
    QString output_str;

signals:
    void AddDialogSaveEvent(QString val);

};

#endif // ATMOSADDDIALOG_H
