#include <QApplication>
#include "logindialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // LoginDialog *loginDialog = new LoginDialog();
   //loginDialog->showMinimized();

  //  if(loginDialog->exec() == QDialog::Accepted)
 //  {
    MainWindow mainwindow;
    mainwindow.showMaximized();
 //  }


    return a.exec();
}
