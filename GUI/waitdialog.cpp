#include "waitdialog.h"
#include "ui_waitdialog.h"

WaitDialog::WaitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitDialog)
{
    ui->setupUi(this);

    this->set_init_status(true);
}

WaitDialog::~WaitDialog()
{
    delete ui;
}

void WaitDialog::set_progress_bar(int number)
{
    this->ui->progressBar->setValue(number);
}

void WaitDialog::set_init_status(bool mark)
{
    this->ui->buttonBox->setDisabled(mark);
    if(mark)
        this->set_progress_bar(0);
    else
    {
        this->set_progress_bar(100);
        this->ui->textEdit->setText("运行成功！");
    }

}
void WaitDialog::setText(QString out_str)
{
    this->ui->textEdit->setText(out_str);
}
void WaitDialog::set_path(QString out_str)
{
    PythonThread *python_thread = new PythonThread(out_str);
    python_thread->start();
}


PythonThread::PythonThread(QString out_path)
{
    this->out_path = out_path;
    isStop = false;
}

void PythonThread::closeThread()
{
    isStop = true;
}

void PythonThread::run()
{
    while(!isStop)
    {
        QFile file(this->out_path);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream in(&file);
        QString res_str = in.readAll();
        file.close();
        qDebug() << res_str;
        this->result_str = res_str;

        sleep(5);
    }
}

QString PythonThread::get_result_str()
{
    return this->result_str;
}

