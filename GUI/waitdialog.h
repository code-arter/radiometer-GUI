#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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

    void set_path(QString out_str);



private:
    Ui::WaitDialog *ui;
};


class PythonThread : public QThread
{
public:
    PythonThread(QString out_path);
    void closeThread();

    QString get_result_str();




protected:
    virtual void run();

private:
    QString out_path;
    volatile bool isStop;       //isStop是易失性变量，需要用volatile进行申明
    QString result_str;
};
#endif // WAITDIALOG_H
