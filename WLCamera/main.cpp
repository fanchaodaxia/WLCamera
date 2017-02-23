#include <QCoreApplication>
#include <wlcamera.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WLCamera c;
    return a.exec();
}
