#include "mainwindow.h"
#include "generalpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GeneralPage w;
    MainWindow w("D:/work_software/language/python.exe", "D:/project/qt/radiometer-old/GUI/process_qt_input.py");
    QIcon icon("D:\\project\\qt\\radiometer-old\\GUI\\image\\logo.png");
    w.setWindowIcon(icon);
    w.setWindowTitle("大气反演模型仿真");
    w.show();

    return a.exec();
}
