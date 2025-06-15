#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QMessageBox>
#include "widget.h"
#include "common.h"
#include "ClientSocket.h"


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();


private slots:
    void on_btn_login_clicked();
    void on_btn_exit_clicked();
private:
    Ui::LoginDialog *ui;
};


#endif // LOGINDIALOG_H
