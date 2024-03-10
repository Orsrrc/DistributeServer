#include "logindialog.h""
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    LoginDialog dialog;
    dialog.showMinimized();
    w.setWindowState(Qt::WindowMaximized);
   // w.show();

    return a.exec();
}
