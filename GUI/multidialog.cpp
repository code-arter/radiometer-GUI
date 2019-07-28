#include "multidialog.h"
#include "ui_plotdialog.h"

PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);

    this->image_dialog = new ImageDialog(this);
    this->image_dialog->setWindowTitle("画图");
    this->image_dialog->hide();
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

void PlotDialog::read_conf(QString path, QVector<QString> &line_list)
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

void PlotDialog::set_init(QString dir)
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
    this->phi = key_list[2].split(",");
    this->umu = key_list[3].split(",");
    this->distance = key_list[4].split(",");
    qDebug() << output_process << output_quantity;
    qDebug() << phi << umu << distance;

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

int PlotDialog::make_points(QVector<QString> &line_list, QList<QPointF> &data_list, double &x_min, double &x_max, double &y_min, double &y_max)
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

void PlotDialog::on_pushButton_clicked()
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

        QVector<QString> line_list;
        this->read_conf(filepath, line_list);

        QList<QPointF> m_data;
        double x_min, x_max,  y_min, y_max;
        this->make_points(line_list, m_data, x_min, x_max, y_min, y_max);

        QLineSeries *test_line = new QLineSeries();
        test_line->append(m_data);
        QChart * plot_1 = createSpectrumChart(-1, -1, test_line, x_min, x_max, y_min, y_max);

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
            qDebug() << phi_list;
            qDebug() << this->phi;
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
                qDebug() << points;
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
                qDebug() << points;
                line_points.append(points);
            }
        }


        QList<QPointF> m_data;
        double x_min, x_max,  y_min, y_max;
        this->make_points(line_points, m_data, x_min, x_max, y_min, y_max);

        QLineSeries *test_line = new QLineSeries();
        test_line->append(m_data);
        QChart * plot_2 = createSpectrumChart(x_mark, y_mark, test_line, x_min, x_max, y_min, y_max);
        this->image_dialog->set_plot(plot_2);
        this->image_dialog->show();
    }
}

void PlotDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "spectral")
    {
        this->ui->comboBox_quantity->setDisabled(true);
    }
    else {
        this->ui->comboBox_quantity->setDisabled(false);
    }
}
