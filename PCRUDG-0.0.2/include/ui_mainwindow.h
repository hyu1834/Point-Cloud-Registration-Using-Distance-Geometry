/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionRegister;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *menuTitle;
    QFrame *line;
    QLabel *pointCloud1Label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *pointCloud1Path;
    QToolButton *pointCloud1BrowseButton;
    QLabel *pointCloud2Label;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *pointCloud2Path;
    QToolButton *pointCloud2BrowseButton;
    QFrame *line_2;
    QGroupBox *registrationGroup;
    QVBoxLayout *verticalLayout;
    QRadioButton *pc1ToPc2Radio;
    QRadioButton *pc2ToPc1Radio;
    QFrame *line_3;
    QLabel *pointCloudResultLabel;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *pointCloudResultPath;
    QToolButton *pointCloudResultBrowseButton;
    QSpacerItem *verticalSpacer;
    QPushButton *registerButton;
    QVBoxLayout *verticalLayout_3;
    GLWidget *openGLWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *corrLabel;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_7;
    QListWidget *corrListWidget1;
    QVBoxLayout *verticalLayout_6;
    QPushButton *corrDeleteButton1;
    QPushButton *corrExportButton1;
    QVBoxLayout *verticalLayout_5;
    QLabel *corrLabel_2;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_8;
    QListWidget *corrListWidget2;
    QVBoxLayout *verticalLayout_7;
    QPushButton *corrDeleteButton2;
    QPushButton *corrExportButton2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1357, 778);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icon/Icon/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        actionRegister = new QAction(MainWindow);
        actionRegister->setObjectName(QStringLiteral("actionRegister"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_6 = new QHBoxLayout(centralWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        menuTitle = new QLabel(centralWidget);
        menuTitle->setObjectName(QStringLiteral("menuTitle"));
        menuTitle->setAutoFillBackground(false);
        menuTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(menuTitle);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        pointCloud1Label = new QLabel(centralWidget);
        pointCloud1Label->setObjectName(QStringLiteral("pointCloud1Label"));
        pointCloud1Label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(pointCloud1Label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pointCloud1Path = new QLineEdit(centralWidget);
        pointCloud1Path->setObjectName(QStringLiteral("pointCloud1Path"));
        pointCloud1Path->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pointCloud1Path->sizePolicy().hasHeightForWidth());
        pointCloud1Path->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pointCloud1Path);

        pointCloud1BrowseButton = new QToolButton(centralWidget);
        pointCloud1BrowseButton->setObjectName(QStringLiteral("pointCloud1BrowseButton"));

        horizontalLayout->addWidget(pointCloud1BrowseButton);


        verticalLayout_2->addLayout(horizontalLayout);

        pointCloud2Label = new QLabel(centralWidget);
        pointCloud2Label->setObjectName(QStringLiteral("pointCloud2Label"));
        pointCloud2Label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(pointCloud2Label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pointCloud2Path = new QLineEdit(centralWidget);
        pointCloud2Path->setObjectName(QStringLiteral("pointCloud2Path"));
        pointCloud2Path->setEnabled(false);
        sizePolicy.setHeightForWidth(pointCloud2Path->sizePolicy().hasHeightForWidth());
        pointCloud2Path->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(pointCloud2Path);

        pointCloud2BrowseButton = new QToolButton(centralWidget);
        pointCloud2BrowseButton->setObjectName(QStringLiteral("pointCloud2BrowseButton"));

        horizontalLayout_4->addWidget(pointCloud2BrowseButton);


        verticalLayout_2->addLayout(horizontalLayout_4);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        registrationGroup = new QGroupBox(centralWidget);
        registrationGroup->setObjectName(QStringLiteral("registrationGroup"));
        registrationGroup->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(registrationGroup);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pc1ToPc2Radio = new QRadioButton(registrationGroup);
        pc1ToPc2Radio->setObjectName(QStringLiteral("pc1ToPc2Radio"));
        pc1ToPc2Radio->setChecked(true);

        verticalLayout->addWidget(pc1ToPc2Radio);

        pc2ToPc1Radio = new QRadioButton(registrationGroup);
        pc2ToPc1Radio->setObjectName(QStringLiteral("pc2ToPc1Radio"));

        verticalLayout->addWidget(pc2ToPc1Radio);


        verticalLayout_2->addWidget(registrationGroup);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        pointCloudResultLabel = new QLabel(centralWidget);
        pointCloudResultLabel->setObjectName(QStringLiteral("pointCloudResultLabel"));
        pointCloudResultLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(pointCloudResultLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pointCloudResultPath = new QLineEdit(centralWidget);
        pointCloudResultPath->setObjectName(QStringLiteral("pointCloudResultPath"));
        pointCloudResultPath->setEnabled(false);
        sizePolicy.setHeightForWidth(pointCloudResultPath->sizePolicy().hasHeightForWidth());
        pointCloudResultPath->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(pointCloudResultPath);

        pointCloudResultBrowseButton = new QToolButton(centralWidget);
        pointCloudResultBrowseButton->setObjectName(QStringLiteral("pointCloudResultBrowseButton"));

        horizontalLayout_5->addWidget(pointCloudResultBrowseButton);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        registerButton = new QPushButton(centralWidget);
        registerButton->setObjectName(QStringLiteral("registerButton"));
        registerButton->setEnabled(false);

        verticalLayout_2->addWidget(registerButton);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(openGLWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        corrLabel = new QLabel(centralWidget);
        corrLabel->setObjectName(QStringLiteral("corrLabel"));
        corrLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(corrLabel);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        corrListWidget1 = new QListWidget(centralWidget);
        corrListWidget1->setObjectName(QStringLiteral("corrListWidget1"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(corrListWidget1->sizePolicy().hasHeightForWidth());
        corrListWidget1->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(corrListWidget1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        corrDeleteButton1 = new QPushButton(centralWidget);
        corrDeleteButton1->setObjectName(QStringLiteral("corrDeleteButton1"));

        verticalLayout_6->addWidget(corrDeleteButton1);

        corrExportButton1 = new QPushButton(centralWidget);
        corrExportButton1->setObjectName(QStringLiteral("corrExportButton1"));

        verticalLayout_6->addWidget(corrExportButton1);


        horizontalLayout_7->addLayout(verticalLayout_6);


        verticalLayout_4->addLayout(horizontalLayout_7);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        corrLabel_2 = new QLabel(centralWidget);
        corrLabel_2->setObjectName(QStringLiteral("corrLabel_2"));
        corrLabel_2->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(corrLabel_2);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        corrListWidget2 = new QListWidget(centralWidget);
        corrListWidget2->setObjectName(QStringLiteral("corrListWidget2"));
        sizePolicy2.setHeightForWidth(corrListWidget2->sizePolicy().hasHeightForWidth());
        corrListWidget2->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(corrListWidget2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        corrDeleteButton2 = new QPushButton(centralWidget);
        corrDeleteButton2->setObjectName(QStringLiteral("corrDeleteButton2"));

        verticalLayout_7->addWidget(corrDeleteButton2);

        corrExportButton2 = new QPushButton(centralWidget);
        corrExportButton2->setObjectName(QStringLiteral("corrExportButton2"));

        verticalLayout_7->addWidget(corrExportButton2);


        horizontalLayout_8->addLayout(verticalLayout_7);


        verticalLayout_5->addLayout(horizontalLayout_8);


        horizontalLayout_2->addLayout(verticalLayout_5);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_6->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1357, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionRegister);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        mainToolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionRegister->setText(QApplication::translate("MainWindow", "Register", 0));
        menuTitle->setText(QApplication::translate("MainWindow", "Menu", 0));
        pointCloud1Label->setText(QApplication::translate("MainWindow", "Point Cloud 1 Path", 0));
        pointCloud1BrowseButton->setText(QApplication::translate("MainWindow", "...", 0));
        pointCloud2Label->setText(QApplication::translate("MainWindow", "Point Cloud 2 Path", 0));
        pointCloud2BrowseButton->setText(QApplication::translate("MainWindow", "...", 0));
        registrationGroup->setTitle(QApplication::translate("MainWindow", "Registration Order", 0));
        pc1ToPc2Radio->setText(QApplication::translate("MainWindow", "PC1 --> PC2", 0));
        pc2ToPc1Radio->setText(QApplication::translate("MainWindow", "PC2 --> PC1", 0));
        pointCloudResultLabel->setText(QApplication::translate("MainWindow", "Result Point Cloud Path", 0));
        pointCloudResultBrowseButton->setText(QApplication::translate("MainWindow", "...", 0));
        registerButton->setText(QApplication::translate("MainWindow", "Register", 0));
        corrLabel->setText(QApplication::translate("MainWindow", "Correspondence Points 1", 0));
        corrDeleteButton1->setText(QApplication::translate("MainWindow", "Detele", 0));
        corrExportButton1->setText(QApplication::translate("MainWindow", "Export", 0));
        corrLabel_2->setText(QApplication::translate("MainWindow", "Correspondence Points 2", 0));
        corrDeleteButton2->setText(QApplication::translate("MainWindow", "Delete", 0));
        corrExportButton2->setText(QApplication::translate("MainWindow", "Export", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
