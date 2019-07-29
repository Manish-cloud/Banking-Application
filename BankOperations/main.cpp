#include "bankoperation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BankOperation w;
    w.show();

    return a.exec();
}
