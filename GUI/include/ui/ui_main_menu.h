/********************************************************************************
** Form generated from reading UI file 'main_menuxFASIY.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAIN_MENUXFASIY_H
#define MAIN_MENUXFASIY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenu
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QPushButton *start;
    QSpacerItem *verticalSpacer_3;
    QPushButton *settings;
    QSpacerItem *verticalSpacer_4;
    QPushButton *exit;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainMenu)
    {
        if (MainMenu->objectName().isEmpty())
            MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        MainMenu->resize(1920, 1080);
        MainMenu->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-radius: 53px;\n"
"	color: #FFF;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"	background-color: rgb(92, 92, 255	);\n"
"	font-size: 30px;\n"
"}\n"
"QPushButton::hover {\n"
"	background-color: rgb(80, 80, 222);\n"
"}\n"
"QPushButton::pressed {\n"
"	background-color: rgb(70, 70, 222);\n"
"}\n"
"QPushButton#settings {\n"
"	background-color: rgb(0, 0, 55);\n"
"	font-size: 30px;\n"
"}\n"
"QPushButton::hover#settings {\n"
"	background-color: rgb(0, 0, 30);\n"
"}\n"
"QPushButton::pressed#settings {\n"
"	background-color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton#exit {\n"
"	background-color: rgb(0, 0, 55);\n"
"	font-size: 30px;\n"
"}\n"
"QPushButton::hover#exit {\n"
"	background-color: rgb(0, 0, 30);\n"
"}\n"
"QPushButton::pressed#settings {\n"
"	background-color: rgb(0, 0, 0);\n"
"}\n"
""));
        centralWidget = new QWidget(MainMenu);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("#centralWidget {\n"
"    border-image: url(\"/home/omay/delivery/Tech2/Semestre_1/Zappy/B-YEP-400-MPL-4-1-zappy-gaetan.darrort/GUI/assets/menu/background.png\") 0 0 0 0 stretch stretch;\n"
"}\n"
""));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 340, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_2);

        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setMinimumSize(QSize(330, 106));
        start->setMaximumSize(QSize(330, 106));
        start->setStyleSheet(QString::fromUtf8(""));
        start->setIconSize(QSize(100, 150));

        verticalLayout_3->addWidget(start, 0, Qt::AlignHCenter|Qt::AlignTop);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_3);

        settings = new QPushButton(centralWidget);
        settings->setObjectName(QString::fromUtf8("settings"));
        settings->setMinimumSize(QSize(330, 106));
        settings->setMaximumSize(QSize(330, 106));
        settings->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(settings, 0, Qt::AlignHCenter|Qt::AlignTop);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_4);

        exit = new QPushButton(centralWidget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setMinimumSize(QSize(330, 106));
        exit->setMaximumSize(QSize(330, 106));
        exit->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(exit, 0, Qt::AlignHCenter|Qt::AlignTop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout_3);

        MainMenu->setCentralWidget(centralWidget);

        retranslateUi(MainMenu);

        QMetaObject::connectSlotsByName(MainMenu);
    } // setupUi

    void retranslateUi(QMainWindow *MainMenu)
    {
        MainMenu->setWindowTitle(QCoreApplication::translate("MainMenu", "ZAPPY - The Game", nullptr));
        start->setText(QCoreApplication::translate("MainMenu", "START", nullptr));
        settings->setText(QCoreApplication::translate("MainMenu", "SETTINGS", nullptr));
        exit->setText(QCoreApplication::translate("MainMenu", "EXIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_MENUXFASIY_H
