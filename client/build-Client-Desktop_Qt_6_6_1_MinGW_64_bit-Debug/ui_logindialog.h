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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLineEdit *lineEdit;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *edit_username;
    QLineEdit *edit_password;
    QComboBox *btn_protocol;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *edit_IPAdress;
    QLabel *label_4;
    QLineEdit *edit_Port;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_login;
    QPushButton *btn_exit;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->setWindowModality(Qt::NonModal);
        LoginDialog->setEnabled(true);
        LoginDialog->resize(584, 364);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginDialog->sizePolicy().hasHeightForWidth());
        LoginDialog->setSizePolicy(sizePolicy);
        LoginDialog->setFocusPolicy(Qt::NoFocus);
        LoginDialog->setContextMenuPolicy(Qt::DefaultContextMenu);
        lineEdit = new QLineEdit(LoginDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(50, 0, 451, 51));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(28);
        font.setWeight(QFont::Black);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        lineEdit->setFont(font);
        lineEdit->setFrame(false);
        lineEdit->setDragEnabled(false);
        lineEdit->setReadOnly(true);
        layoutWidget = new QWidget(LoginDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(60, 60, 451, 261));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(true);
        label->setFont(font1);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        verticalLayout_2->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        edit_username = new QLineEdit(layoutWidget);
        edit_username->setObjectName("edit_username");
        edit_username->setEchoMode(QLineEdit::Normal);

        verticalLayout->addWidget(edit_username);

        edit_password = new QLineEdit(layoutWidget);
        edit_password->setObjectName("edit_password");
        edit_password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(edit_password);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        btn_protocol = new QComboBox(layoutWidget);
        btn_protocol->addItem(QString());
        btn_protocol->addItem(QString());
        btn_protocol->setObjectName("btn_protocol");

        verticalLayout_3->addWidget(btn_protocol);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        edit_IPAdress = new QLineEdit(layoutWidget);
        edit_IPAdress->setObjectName("edit_IPAdress");

        horizontalLayout_3->addWidget(edit_IPAdress);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        edit_Port = new QLineEdit(layoutWidget);
        edit_Port->setObjectName("edit_Port");

        horizontalLayout_3->addWidget(edit_Port);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btn_login = new QPushButton(layoutWidget);
        btn_login->setObjectName("btn_login");

        horizontalLayout_2->addWidget(btn_login);

        btn_exit = new QPushButton(layoutWidget);
        btn_exit->setObjectName("btn_exit");

        horizontalLayout_2->addWidget(btn_exit);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        lineEdit->setText(QCoreApplication::translate("LoginDialog", "    \345\214\272\345\235\227\351\223\276\344\273\277\347\234\237\346\250\241\346\213\237\347\263\273\347\273\237", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Password:", nullptr));
        btn_protocol->setItemText(0, QCoreApplication::translate("LoginDialog", "Tcp", nullptr));
        btn_protocol->setItemText(1, QCoreApplication::translate("LoginDialog", "Udp", nullptr));

        label_3->setText(QCoreApplication::translate("LoginDialog", "IPAddress", nullptr));
        label_4->setText(QCoreApplication::translate("LoginDialog", "Port", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        btn_exit->setText(QCoreApplication::translate("LoginDialog", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
