#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);

    this->chartView = NULL;
}

ImageDialog::~ImageDialog()
{
    delete ui;
}

void ImageDialog::set_plot(QChart *plot)
{
    this->chartView = new QChartView(this);
    this->chartView->setChart(plot);
    chartView->resize(700, 500);
}

void ImageDialog::on_pushButton_clicked()
{
    QString save_path=QFileDialog::getSaveFileName(this,QStringLiteral("另存为"), "chart.png", "*.png");
    if(!save_path.isEmpty() && chartView != NULL)
    {
        QScreen * screen = QGuiApplication::primaryScreen();
        QPixmap p = screen->grabWindow(chartView->winId());
        QImage image = p.toImage();
        image.save(save_path);
        /*
        if(this->chartView != NULL)
        {
            delete this->chartView;
            this->chartView = NULL;
        }
        */
    }
}
