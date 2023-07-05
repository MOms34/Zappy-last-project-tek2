/********************************************************************************
** Form generated from reading UI file 'designermgDFUL.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERMGDFUL_H
#define DESIGNERMGDFUL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnexionMenu
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *IP_edit;
    QLineEdit *Port_edit;
    QSpacerItem *verticalSpacer_3;
    QPushButton *start;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ConnexionMenu)
    {
        ConnexionMenu->setObjectName(QString::fromUtf8("ConnexionMenu"));
        ConnexionMenu->resize(1920, 1080);
        ConnexionMenu->setMinimumSize(QSize(1920, 1080));
        ConnexionMenu->setMaximumSize(QSize(1920, 1080));
        ConnexionMenu->setStyleSheet(QString::fromUtf8("QWidget#ConnexionMenu {\n"
"    border-image: url(\"/home/omay/delivery/Tech2/Semestre_1/Zappy/B-YEP-400-MPL-4-1-zappy-gaetan.darrort/GUI/assets/menu/background.png\") 0 0 0 0 stretch stretch;\n"
"}\n"
"QLineEdit {\n"
"	border-radius: 29px;\n"
"	color: rgb(55, 55, 156);\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"	background-color: rgb(92, 92, 255	);\n"
"	font-size: 18px;\n"
"}\n"
"QLineEdit::hover {\n"
"	background-color: rgb(80, 80, 222);\n"
"}\n"
"QLineEdit::Focus {\n"
"	background-color: rgb(80, 80, 222);\n"
"}\n"
"\n"
"QPushButton {\n"
"	border-radius: 37px;\n"
"	color: #FFF;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"	background-color: rgb(92, 92, 255	);\n"
"	font-size: 30px;\n"
"}\n"
"QPushButton::hover {\n"
"	background-color: rgb(80, 80, 222);\n"
"}\n"
"QPushButton::Pressed {\n"
"	background-color: rgb(70, 70, 222);\n"
"}\n"
"\n"
""));
        verticalLayout_2 = new QVBoxLayout(ConnexionMenu);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        IP_edit = new QLineEdit(ConnexionMenu);
        IP_edit->setObjectName(QString::fromUtf8("IP_edit"));
        IP_edit->setMinimumSize(QSize(310, 60));
        IP_edit->setMaximumSize(QSize(310, 60));

        verticalLayout->addWidget(IP_edit, 0, Qt::AlignHCenter);

        Port_edit = new QLineEdit(ConnexionMenu);
        Port_edit->setObjectName(QString::fromUtf8("Port_edit"));
        Port_edit->setMinimumSize(QSize(310, 60));
        Port_edit->setMaximumSize(QSize(310, 60));

        verticalLayout->addWidget(Port_edit, 0, Qt::AlignHCenter);

        verticalSpacer_3 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);

        start = new QPushButton(ConnexionMenu);
        start->setObjectName(QString::fromUtf8("start"));
        start->setMinimumSize(QSize(330, 75));
        start->setMaximumSize(QSize(330, 75));

        verticalLayout->addWidget(start, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ConnexionMenu);

        QMetaObject::connectSlotsByName(ConnexionMenu);
    } // setupUi

    void retranslateUi(QWidget *ConnexionMenu)
    {
        ConnexionMenu->setWindowTitle(QCoreApplication::translate("ConnexionMenu", "Form", nullptr));
        IP_edit->setInputMask(QString());
        IP_edit->setPlaceholderText(QCoreApplication::translate("ConnexionMenu", "IP Adress", nullptr));
        Port_edit->setInputMask(QString());
        Port_edit->setPlaceholderText(QCoreApplication::translate("ConnexionMenu", "Port", nullptr));
        start->setText(QCoreApplication::translate("ConnexionMenu", "START", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnexionMenu: public Ui_ConnexionMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERMGDFUL_H
