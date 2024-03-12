#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDialog;
    loginDialog.showMinimized();
    return a.exec();
}
