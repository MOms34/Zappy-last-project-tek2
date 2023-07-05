/********************************************************************************
** Form generated from reading UI file 'setting_menuFQmapl.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SETTING_MENUFQMAPL_H
#define SETTING_MENUFQMAPL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingMenu
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QDial *dial;
    QWidget *page_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SettingMenu)
    {
        if (SettingMenu->objectName().isEmpty())
            SettingMenu->setObjectName(QString::fromUtf8("SettingMenu"));
        SettingMenu->resize(1920, 1080);
        SettingMenu->setStyleSheet(QString::fromUtf8("#SettingMenu {\n"
"    border-image: url(\"/home/omay/delivery/Tech2/Semestre_1/Zappy/B-YEP-400-MPL-4-1-zappy-gaetan.darrort/GUI/assets/menu/background.png\") 0 0 0 0 stretch stretch;\n"
"}\n"
"QDial {\n"
"	border-radius: 53px;\n"
"	color: #FFF;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"	background-color: rgb(92, 92, 255	);\n"
"	font-size: 30px;\n"
"}\n"
"QDial::hover {\n"
"	background-color: rgb(80, 80, 222);\n"
"}\n"
"QDial::pressed {\n"
"	background-color: rgb(70, 70, 222);\n"
"}\n"
"\n"
"QLabel {\n"
"	border-radius: 53px;\n"
"	color: #FFF;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"	background-color: rgb(92, 92, 255	);\n"
"	font-size: 30px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(SettingMenu);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        stackedWidget = new QStackedWidget(SettingMenu);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setMinimumSize(QSize(330, 106));
        stackedWidget->setMaximumSize(QSize(330, 106));
        stackedWidget->setAcceptDrops(false);
        stackedWidget->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 330, 106));
        label->setMinimumSize(QSize(330, 106));
        label->setMaximumSize(QSize(330, 106));
        dial = new QDial(page);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setGeometry(QRect(190, -120, 100, 346));
        dial->setMaximum(100);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setEnabled(true);
        stackedWidget->addWidget(page_2);

        horizontalLayout_2->addWidget(stackedWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SettingMenu);

        QMetaObject::connectSlotsByName(SettingMenu);
    } // setupUi

    void retranslateUi(QWidget *SettingMenu)
    {
        SettingMenu->setWindowTitle(QCoreApplication::translate("SettingMenu", "Form", nullptr));
        label->setText(QCoreApplication::translate("SettingMenu", "     Music", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingMenu: public Ui_SettingMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SETTING_MENUFQMAPL_H
