#include "batchdialog.h"
#include "ui_batchdialog.h"

BatchDialog::BatchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchDialog)
{
    ui->setupUi(this);

    this->image_dialog = new ImageDialog(this);
    this->image_dialog->setWindowTitle("画图");
    //this->image_dialog;
    this->image_dialog->hide();
}

BatchDialog::~BatchDialog()
{
    delete ui;
}

void BatchDialog::read_conf(QString path, QVector<QString> &line_list)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        line_list.append(line);
    }
    file.close();
}

void BatchDialog::set_init(QString dir)
{

    this->plot_dir = dir;
    this->ui->comboBox_plot_phi->clear();
    this->ui->comboBox_plot_umu->clear();
    this->ui->comboBox_plot_distance->clear();
    this->ui->comboBox_quantity->setDisabled(true);

    QVector<QString> key_list;
    this->read_conf(dir + "/key_path", key_list);
    this->output_process = key_list[0].split(",");
    this->output_quantity = key_list[1].split(",");
    this->plot_regex = key_list[2].split("-");
    this->plot_x = this->plot_regex[0];
    this->plot_y = this->plot_regex[1];

    this->phi = key_list[3].split(",");
    this->umu = key_list[4].split(",");
    this->distance = key_list[5].split(",");

    for(int index = phi.size() - 1; index >= 0; index--)
    {
        this->ui->comboBox_plot_phi->addItem(phi[index]);
    }
    for(int index = umu.size() - 1; index >= 0; index--)
    {
        this->ui->comboBox_plot_umu->addItem(umu[index]);
    }
    for(int index = distance.size() - 1; index >= 0; index--)
    {
        this->ui->comboBox_plot_distance->addItem(distance[index]);
    }
}

int BatchDialog::make_points(QVector<QString> &line_list, QList<QPointF> &data_list, double &x_min, double &x_max, double &y_min, double &y_max)
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
        double y = sl.at(1).toDouble();
        if(this->ui->comboBox->currentIndex() == 0)
        {
            double c = 2.998e8;
            if(this->x_label == "波长")
            {
                if(this->plot_x == '0')
                {
                    x = x / 1000.0;
                }
                else
                {
                    x = 10000.0 / x;
                }
            }
            else
            {
                if(this->plot_x == '0')
                {
                    x = x / 1000.0;
                    x = 10000.0 / x;
                }
            }
            if(this->y_label == 0)
            {
                if(this->plot_y == '1')
                {
                    y = y * 3.1415926 * c / x / x /100000000;
                }
            }
            else if(this->y_label == 1)
            {
                if(this->plot_y == '0')
                {
                    y = y * 100000000 * x * x / c / 3.1415926;
                }
            }
        }

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

void BatchDialog::on_pushButton_clicked()
{
    QString plot_method = this->ui->comboBox->currentText();
    QString phi = this->ui->comboBox_plot_phi->currentText();
    QString umu = this->ui->comboBox_plot_umu->currentText();
    QString distance = this->ui->comboBox_plot_distance->currentText();
    QString output_process = this->ui->comboBox->currentText();
    QString output_quantity = this->ui->comboBox_quantity->currentText();

    if(plot_method == "spectral")
    {
        QString filename = QString("%1_%2_radiance_spectral").arg(umu).arg(distance);
        QString filepath = QString("%1/%2").arg(this->plot_dir).arg(filename);

        QFileInfo file_info(filepath);
        if(!file_info.exists())
        {
            QMessageBox::information(NULL, "警告", "找不到对应的输出文件！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }

        QVector<QString> line_list;
        this->read_conf(filepath, line_list);

        QList<QPointF> m_data;
        double x_min, x_max,  y_min, y_max;

        //add for choose x and y
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
        this->y_label = y_index;

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

        this->make_points(line_list, m_data, x_min, x_max, y_min, y_max);

        QLineSeries *test_line = new QLineSeries();
        test_line->append(m_data);


        QChart * plot_1 = createSpectrumChart(x_mark, y_mark, test_line, x_min, x_max, y_min, y_max);

        this->image_dialog->set_plot(plot_1);
        this->image_dialog->show();
    }
    else
    {
        QVector<QString> line_points;
        int x_mark = -1;
        int y_mark = 2;
        if(this->phi.size() != 1)
        {
            x_mark = 3;
            QString filename = QString("%1_%2_%3_integrate").arg(umu).arg(distance).arg(output_quantity);
            QString filepath = QString("%1/%2").arg(this->plot_dir).arg(filename);
            QFileInfo file_info(filepath);
            if(!file_info.exists())
            {
                QMessageBox::information(NULL, "警告", "找不到对应的输出文件！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                return;
            }

            QVector<QString> line_list;
            this->read_conf(filepath, line_list);

            QString first_line;
            for(int index =0 ;index < line_list.size(); index++)
            {
                if(!line_list[index].isEmpty())
                    first_line = line_list[index];
            }
            QStringList phi_list = first_line.split(" ", QString::SkipEmptyParts);
            for(int index =0 ;index < this->phi.size(); index++)
            {
                line_points.append(QString("%1 %2").arg(this->phi[index]).arg(phi_list[index+1]));
            }
        }
        else if(this->umu.size() != 1)
        {
            x_mark = 2;
            for(int index =0 ;index < this->umu.size(); index++)
            {
                QString filename = QString("%1_%2_%3_integrate").arg(this->umu[index]).arg(distance).arg(output_quantity);
                QString filepath = QString("%1/%2").arg(this->plot_dir).arg(filename);
                QFileInfo file_info(filepath);
                if(!file_info.exists())
                {
                    QMessageBox::information(NULL, "警告", "找不到对应的输出文件！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    return;
                }

                QVector<QString> line_list;
                this->read_conf(filepath, line_list);

                QString first_line;
                for(int index =0 ;index < line_list.size(); index++)
                {
                    if(!line_list[index].isEmpty())
                        first_line = line_list[index];
                }
                QStringList phi_list = first_line.split(" ", QString::SkipEmptyParts);
                QString points = QString("%1 %2").arg(this->umu[index]).arg(phi_list[1]);
                line_points.append(points);
            }
        }
        else if(this->distance.size() != 1)
        {
            x_mark = 4;
            for(int index =0 ;index < this->distance.size(); index++)
            {
                QString filename = QString("%1_%2_%3_integrate").arg(umu).arg(this->distance[index]).arg(output_quantity);
                QString filepath = QString("%1/%2").arg(this->plot_dir).arg(filename);
                QFileInfo file_info(filepath);
                if(!file_info.exists())
                {
                    QMessageBox::information(NULL, "警告", "找不到对应的输出文件！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    return;
                }

                QVector<QString> line_list;
                this->read_conf(filepath, line_list);

                QString first_line;
                for(int index =0 ;index < line_list.size(); index++)
                {
                    if(!line_list[index].isEmpty())
                        first_line = line_list[index];
                }
                QStringList phi_list = first_line.split(" ", QString::SkipEmptyParts);

                QString points = QString("%1 %2").arg(this->distance[index]).arg(phi_list[1]);
                line_points.append(points);
            }
        }

        QList<QPointF> m_data;
        double x_min, x_max,  y_min, y_max;
        this->make_points(line_points, m_data, x_min, x_max, y_min, y_max);

        QLineSeries *test_line = new QLineSeries();
        test_line->append(m_data);
        QChart * plot_2 = createSpectrumChart(x_mark, y_mark, test_line, x_min, x_max, y_min, y_max);
        //this->image_dialog->resize(600, 400);
        this->image_dialog->set_plot(plot_2);
        this->image_dialog->show();
    }
}

void BatchDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "spectral")
    {
        this->ui->comboBox_quantity->setDisabled(true);
        this->ui->comboBox_x->setDisabled(false);
        this->ui->comboBox_y->setDisabled(false);
    }
    else {
        this->ui->comboBox_quantity->setDisabled(false);
        this->ui->comboBox_x->setDisabled(true);
        this->ui->comboBox_y->setDisabled(true);
    }
}

void BatchDialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    ;
}
