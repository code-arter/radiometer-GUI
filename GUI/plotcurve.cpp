//创建光谱曲线表格 -->  更新数据

//创建表格
#include"plotcurve.h"

QChart * createSpectrumChart(int xlabel_code,int ylabel_code,QLineSeries * m_series_Spectrum,float min_x,float max_x,float min_y,float max_y)
{
   
        Qstring Yl_Rad_spec_waveLen="光谱辐射亮度(w/m^2·Sr·nm)";
        Qstring Yl_Rad_spec_waveNum="光谱辐射亮度(w/m^2·Sr·cm-1)";
        Qstring Yl_Rad_inte="积分辐射亮度(w/m^2·Sr)";
        Qstring Yl_BT="辐射亮温(Kevin)";
        Qstring Yl_Transmit="透过率";
	
        Qstring Xl_Pitch_Angle="俯仰角(DEG)";
        Qstring Xl_Amuze_Angle="方位角(DEG)";
        Qstring Xl_Ailtude="海拔高度(Km)";
        Qstring Xl_spec_waveLen="波长(μm)";
        Qstring Xl_spec_waveNum="波数(cm-1)";
	
	
	min_x=min_x*0.95;
	max_x=max_x*1.05;
	min_y=min_y*0.95;
	max_y=max_y*1.05;
	
	

	//对光谱数据进行管理
	QChart *chart = new QChart();
        chart->setTitle("辐射曲线");
	chart->legend()->hide();
	chart->addSeries(m_series_Spectrum);
	QValueAxis* axisX = new QValueAxis();
	QValueAxis* axisY = new QValueAxis();

	//设置坐标轴显示的范围
	axisX->setMin(min_x);
	axisX->setMax(max_x);
	axisX->setTickCount(10);

	axisY->setMin(min_y);
	axisY->setMax(max_y);
	
	//设置坐标轴上的格点
	axisY->setTickCount(5);
	//设置坐标轴的颜色，粗细，设置网格显示
	axisY->setLinePenColor(QColor(Qt::darkBlue));
	axisY->setGridLineColor(QColor(Qt::darkBlue));
	axisY->setGridLineVisible(true);
	QPen penY1(Qt::darkBlue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        //QPen penY2(Qt::darkGreen, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	axisY->setLinePen(penY1);
	axisX->setLinePen(penY1); 
	
        switch (xlabel_code)
        {
         case 0:
            axisX->setTitleText(Yl_Rad_spec_waveLen);
            break;
        case 1:
            axisX->setTitleText(Xl_spec_waveNum);
            break;
        case 2:
            axisX->setTitleText(Xl_Pitch_Angle);
            break;
        case 3:
            axisX->setTitleText(Xl_Amuze_Angle);
            break;
        case 4:
            axisX->setTitleText(Xl_Ailtude);
            break;
        default:
             axisX->setTitleText(Xl_spec_waveLen);

        }


        switch (ylabel_code)
        {
         case 0:
            axisY->setTitleText(Yl_Rad_spec_waveLen);
            break;
        case 1:
            axisY->setTitleText(Yl_Rad_spec_waveNum);
            break;
        case 2:
            axisY->setTitleText(Yl_Rad_inte);
            break;
        case 3:
            axisY->setTitleText(Yl_BT);
            break;
        case 4:
            axisY->setTitleText(Xl_Ailtude);
            break;
        case 5:
             axisY->setTitleText(Yl_Transmit);
        default:
             axisY->setTitleText(Yl_Rad_spec_waveLen);
        }

	//把坐标轴添加到chart中，
	//addAxis函数的第二个参数是设置坐标轴的位置，
	//只有四个选项，下方：Qt::AlignBottom，左边：Qt::AlignLeft，右边：Qt::AlignRight，上方：Qt::AlignTop
	chart->addAxis(axisX, Qt::AlignBottom);
        chart->adAxis(axisY, Qt::AlignLeft);
 
	//将点变成线
	m_series_Spectrum->attachAxis(axisX);
	m_series_Spectrum->attachAxis(axisY);

	return chart;
}



