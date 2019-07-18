#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>

namespace Ui {
class WaitDialog;
}

class WaitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitDialog(QWidget *parent = nullptr);
    ~WaitDialog();

    void set_progress_bar(int number);
    void set_init_status(bool mark);
    void setText(QString out_str);


private:
    Ui::WaitDialog *ui;
};

#endif // WAITDIALOG_H
