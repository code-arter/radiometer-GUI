#include "mainwindow.h"
#include "generalpage.h"
#include <QApplication>
#include "commonfunction.h"

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString splash_path = QCoreApplication::applicationDirPath() + "/image/gui_splash.jpeg";


    qInstallMessageHandler(myMsgOutput);
    qDebug() << "for test";

    QPixmap pixmap(splash_path);
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();
    MainWindow w;
    w.setWindowFlags( w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    w.setWindowTitle("大气反演模型仿真");
    w.resize(900, 650);
    w.show();
    splash.finish(&w);


    return app.exec();
}

