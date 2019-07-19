#include "mainwindow.h"
#include "generalpage.h"
#include <QApplication>
//#include <QCoreApplication>

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w("D:/work_software/language/python.exe", "D:/project/qt/radiometer/build-GUI-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/debug/process_qt_input.py");
    w.setWindowFlags( w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    w.setWindowTitle("大气反演模型仿真");
    w.show();

    return a.exec();
}

