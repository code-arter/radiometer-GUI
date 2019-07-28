#include "singledialog.h"
#include "ui_singledialog.h"

SingleDialog::SingleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleDialog)
{
    ui->setupUi(this);

    this->image_dialog = new ImageDialog(this);
    this->image_dialog->setWindowTitle("画图");
    this->image_dialog->hide();
}

SingleDialog::~SingleDialog()
{
    delete ui;
}

void SingleDialog::on_pushButton_clicked()
{
    QString x_label = this->ui->comboBox_x->currentText();
    this->x_label = x_label;
    int x_mark = -1, y_mark = -1;
    if(x_label == "波长")
    {
        x_mark = -1;
    }
    else
    {
        x_mark = 1;
    }
    int y_index = this->ui->comboBox_y->currentIndex();
    if(y_index == 0)
        y_mark = 0;
    else if(y_index == 1)
        y_mark = 1;
    else if(y_index == 2)
        y_mark = 2;
    else if(y_index == 3)
        y_mark = 3;
    else if(y_index == 4)
        y_mark = 5;
    qDebug() << y_index;
    QList<QPointF> m_data;
    double x_min, x_max,  y_min, y_max;
    this->make_points(this->line_list, m_data, x_min, x_max, y_min, y_max);

    QLineSeries *test_line = new QLineSeries();
    test_line->append(m_data);
    QChart * plot = createSpectrumChart(x_mark, y_mark, test_line, x_min, x_max, y_min, y_max);
    this->image_dialog->set_plot(plot);
    this->image_dialog->show();
}

int SingleDialog::make_points(QVector<QString> &line_list, QList<QPointF> &data_list, double &x_min, double &x_max, double &y_min, double &y_max)
{
    x_min = 99999999999;
    x_max = 0.0;
    y_min = 99999999999;
    y_max = 0.0;
    for(int index = 0; index < line_list.size(); index++)
    {
        QStringList sl =line_list[index].split(" ", QString::SkipEmptyParts);
        if(sl.size() == 0)
            continue;

        double x = sl.at(0).toDouble();
        if(this->x_label == "波长")
            x = x / 1000.0;
        double y = sl.at(1).toDouble();
        if(x < x_min)
            x_min = x;
        if(x > x_max)
            x_max = x;
        if(y < y_min)
            y_min = y;
        if(y > y_max)
            y_max = y;
        data_list.append(QPointF(x, y));
    }
    return 0;
}
void SingleDialog::set_init(QVector<QString> &line_list)
{
    this->line_list = line_list;
}
