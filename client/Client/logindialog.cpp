#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)

{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btn_login_clicked()
{
    int state = 1;
    Client client;
    client.sendLoginInfo( );
    client.receiveLoginInfo(state);
    if( state == LOGINSUSSESS )
    {
        QMessageBox::information(this, (QString)"info", (QString)"login sussess");
        QWidget *mainWidget  = new Widget();
        this->close();
        mainWidget->showMaximized();
    }
    else
    {
        QMessageBox::critical(this, (QString)"Error", (QString)"login fail");
    }

}

void LoginDialog::on_btn_exit_clicked()
{
    this->close();
}

