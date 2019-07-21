#include "mainwindow.h"
#include "generalpage.h"
#include <QApplication>
//#include <QCoreApplication>

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags( w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    w.setWindowTitle("大气反演模型仿真");
    w.resize(900, 650);
    w.show();

    return a.exec();
}

