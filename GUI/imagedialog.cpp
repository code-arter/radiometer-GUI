#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);

    this->chartView = new QChartView(this);
}

ImageDialog::~ImageDialog()
{
    delete ui;
}

void ImageDialog::set_plot(QChart *plot)
{
    this->chartView->setChart(plot);
    chartView->resize(600, 400);
}

void ImageDialog::on_pushButton_clicked()
{
    QString save_path=QFileDialog::getSaveFileName(this,QStringLiteral("另存为"), "chart.png", "*.png");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(chartView->winId());
    QImage image = p.toImage();
    image.save(save_path);
}
