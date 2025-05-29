/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *selectVideoButton;
    QPushButton *selectOutputFolderButton;
    QPushButton *startButton;
    QLabel *videoPathLabel;
    QLabel *outputPathLabel;
    QSpinBox *frequencySpinBox;
    QComboBox *formatComboBox;
    QProgressBar *progressBar;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QMenu *menuVideo_to_Picture;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        selectVideoButton = new QPushButton(centralwidget);
        selectVideoButton->setObjectName("selectVideoButton");
        selectVideoButton->setGeometry(QRect(40, 60, 80, 24));
        selectOutputFolderButton = new QPushButton(centralwidget);
        selectOutputFolderButton->setObjectName("selectOutputFolderButton");
        selectOutputFolderButton->setGeometry(QRect(40, 130, 80, 24));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(40, 320, 80, 24));
        videoPathLabel = new QLabel(centralwidget);
        videoPathLabel->setObjectName("videoPathLabel");
        videoPathLabel->setGeometry(QRect(140, 61, 571, 20));
        outputPathLabel = new QLabel(centralwidget);
        outputPathLabel->setObjectName("outputPathLabel");
        outputPathLabel->setGeometry(QRect(140, 130, 571, 21));
        frequencySpinBox = new QSpinBox(centralwidget);
        frequencySpinBox->setObjectName("frequencySpinBox");
        frequencySpinBox->setGeometry(QRect(40, 200, 51, 25));
        formatComboBox = new QComboBox(centralwidget);
        formatComboBox->setObjectName("formatComboBox");
        formatComboBox->setGeometry(QRect(40, 260, 72, 24));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(40, 380, 251, 23));
        progressBar->setValue(24);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 180, 71, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 240, 61, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuVideo_to_Picture = new QMenu(menubar);
        menuVideo_to_Picture->setObjectName("menuVideo_to_Picture");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuVideo_to_Picture->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        selectVideoButton->setText(QCoreApplication::translate("MainWindow", "Valitse video", nullptr));
        selectOutputFolderButton->setText(QCoreApplication::translate("MainWindow", "Valitse kansio", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Aloita", nullptr));
        videoPathLabel->setText(QCoreApplication::translate("MainWindow", "File path", nullptr));
        outputPathLabel->setText(QCoreApplication::translate("MainWindow", "File path", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Freimiv\303\244li", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Formaatit", nullptr));
        menuVideo_to_Picture->setTitle(QCoreApplication::translate("MainWindow", "Video to Picture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
