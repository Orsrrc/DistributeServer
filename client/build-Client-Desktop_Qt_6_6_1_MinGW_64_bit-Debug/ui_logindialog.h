/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QTextEdit *textEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *input_username;
    QTextEdit *input_password;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_login;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_exit;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(584, 283);
        textEdit = new QTextEdit(LoginDialog);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(20, 10, 161, 131));
        widget = new QWidget(LoginDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(200, 30, 371, 81));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(widget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        input_username = new QTextEdit(widget);
        input_username->setObjectName("input_username");

        verticalLayout->addWidget(input_username);

        input_password = new QTextEdit(widget);
        input_password->setObjectName("input_password");

        verticalLayout->addWidget(input_password);


        horizontalLayout->addLayout(verticalLayout);

        widget1 = new QWidget(LoginDialog);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(220, 140, 311, 131));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_login = new QPushButton(widget1);
        btn_login->setObjectName("btn_login");

        horizontalLayout_2->addWidget(btn_login);

        horizontalSpacer = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btn_exit = new QPushButton(widget1);
        btn_exit->setObjectName("btn_exit");

        horizontalLayout_2->addWidget(btn_exit);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Password:", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        btn_exit->setText(QCoreApplication::translate("LoginDialog", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
