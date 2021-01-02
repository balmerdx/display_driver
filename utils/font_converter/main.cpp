#include "convertfontdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("BalmerDX");
    //QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Font Converter");

    ConvertFontDialog w;
    w.show();

    return a.exec();
}
