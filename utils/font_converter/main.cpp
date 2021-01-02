#include "convertfontdialog.h"
#include <QApplication>

#include "../../display/fonts/DefaultFonts.h"

int main(int argc, char *argv[])
{
/*
    {
        FontConverter f;
        QString name = "FONT8x15";
        f.saveBitmapFont(name+".c", FONT8x15, name);
        return 0;
    }
*/
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("BalmerDX");
    //QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Font Converter");

    ConvertFontDialog w;
    w.show();

    return a.exec();
}
