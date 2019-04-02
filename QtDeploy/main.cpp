#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication::setOrganizationName("zxx");
    QApplication::setOrganizationDomain("zxx.com");
    QApplication::setApplicationName("zxxx");


    QApplication a(argc, argv);
    MainWindow w;

    QSettings *configIni = new QSettings("./conf/conf.ini", QSettings::IniFormat);
    QString Result = configIni->value("/QTDIR/PATH").toString();
    if(Result == ""){
        configIni->setValue("/QTDIR/PATH", "C:/Qt/Qt5.12.0/5.12.0/msvc2015_64");
        Result = "C:/Qt/Qt5.12.0/5.12.0/msvc2015_64";
    }
    w.setCommand(Result);

    w.show();

    return a.exec();
}
