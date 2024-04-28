#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)

{
    ui->setupUi(this);

    //fix dialog size
    this->setMaximumSize(550, 350);
    this->setMinimumSize(550,350);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btn_login_clicked()
{
    //ready for send message
    Network client;
    client.createSocket(this, this, ui->btn_protocol->currentIndex());
    if(ui->edit_IPAdress->text() == " ")
    {
        QMessageBox::warning(this, "IP", "IP地址未输入");
    }
    else if(ui->edit_Port->text() == " ")
    {
        QMessageBox::warning(this, "端口", "端口未输入");
    }
    else
    {
        //choose UDP to sent
        if(ui->btn_protocol->currentIndex() == PROTOCOL_UDP)
        {
            client.sendByUdp(ui->edit_username->text(),
                             ui->edit_password->text(),
                             QHostAddress (ui->edit_IPAdress->text() ),
                             ui->edit_Port->text().toUInt());
        }
        //choose TCP to sent
        else if(ui->btn_protocol->currentIndex() == PROTOCOL_TCP)
        {
            client.TcpConnect(
                            QString ( ui->edit_IPAdress->text() ),
                              ui->edit_Port->text().toUInt()
                              );
            client.sendByTcp(ui->edit_username->text(),
                                     ui->edit_password->text()
                                    );
        }
    }
}

void LoginDialog::on_btn_exit_clicked()
{
    this->close();
}

