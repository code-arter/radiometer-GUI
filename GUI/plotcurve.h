#include<QChart>
#include<QLineSeries>
#include<QString>
#include<QValueAxis>
#include<QPen>
#include <QtCharts/QtCharts>
QChart * createSpectrumChart(int xlabel_code,int ylabel_code,QLineSeries * m_series_Spectrum,
float min_x,float max_x,float min_y,float max_y);
