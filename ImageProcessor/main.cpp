#include <QApplication>
#include "ImageProcessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageProcessor w;
    w.show();

    return a.exec();
}
