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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *input_username;
    QTextEdit *input_password;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_login;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_exit;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->setWindowModality(Qt::NonModal);
        LoginDialog->setEnabled(true);
        LoginDialog->resize(584, 283);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginDialog->sizePolicy().hasHeightForWidth());
        LoginDialog->setSizePolicy(sizePolicy);
        LoginDialog->setFocusPolicy(Qt::NoFocus);
        LoginDialog->setContextMenuPolicy(Qt::DefaultContextMenu);
        textEdit = new QTextEdit(LoginDialog);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(20, 10, 121, 131));
        layoutWidget = new QWidget(LoginDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(170, 10, 381, 131));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        input_username = new QTextEdit(layoutWidget);
        input_username->setObjectName("input_username");

        verticalLayout->addWidget(input_username);

        input_password = new QTextEdit(layoutWidget);
        input_password->setObjectName("input_password");

        verticalLayout->addWidget(input_password);


        horizontalLayout->addLayout(verticalLayout);

        layoutWidget1 = new QWidget(LoginDialog);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 200, 581, 81));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btn_login = new QPushButton(layoutWidget1);
        btn_login->setObjectName("btn_login");

        horizontalLayout_2->addWidget(btn_login);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btn_exit = new QPushButton(layoutWidget1);
        btn_exit->setObjectName("btn_exit");

        horizontalLayout_2->addWidget(btn_exit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Password:", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginDialog", "PushButton", nullptr));
        btn_exit->setText(QCoreApplication::translate("LoginDialog", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
