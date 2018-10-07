/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCarregar_imagem;
    QAction *actionSalvar_imagem;
    QAction *actionSmoothing;
    QAction *actionArestas;
    QAction *actionHaar;
    QAction *actionHaar_inverso;
    QAction *actionCarregar_resultado;
    QAction *actionRealce_em_Haar;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *inputLabel;
    QLabel *outputLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1058, 605);
        actionCarregar_imagem = new QAction(MainWindow);
        actionCarregar_imagem->setObjectName(QStringLiteral("actionCarregar_imagem"));
        actionSalvar_imagem = new QAction(MainWindow);
        actionSalvar_imagem->setObjectName(QStringLiteral("actionSalvar_imagem"));
        actionSmoothing = new QAction(MainWindow);
        actionSmoothing->setObjectName(QStringLiteral("actionSmoothing"));
        actionArestas = new QAction(MainWindow);
        actionArestas->setObjectName(QStringLiteral("actionArestas"));
        actionHaar = new QAction(MainWindow);
        actionHaar->setObjectName(QStringLiteral("actionHaar"));
        actionHaar_inverso = new QAction(MainWindow);
        actionHaar_inverso->setObjectName(QStringLiteral("actionHaar_inverso"));
        actionCarregar_resultado = new QAction(MainWindow);
        actionCarregar_resultado->setObjectName(QStringLiteral("actionCarregar_resultado"));
        actionRealce_em_Haar = new QAction(MainWindow);
        actionRealce_em_Haar->setObjectName(QStringLiteral("actionRealce_em_Haar"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        inputLabel = new QLabel(centralWidget);
        inputLabel->setObjectName(QStringLiteral("inputLabel"));
        inputLabel->setEnabled(true);
        inputLabel->setMinimumSize(QSize(512, 512));
        inputLabel->setAutoFillBackground(false);
        inputLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        inputLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(inputLabel);

        outputLabel = new QLabel(centralWidget);
        outputLabel->setObjectName(QStringLiteral("outputLabel"));
        outputLabel->setMinimumSize(QSize(512, 512));
        outputLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        outputLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(outputLabel);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1058, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionCarregar_imagem);
        mainToolBar->addAction(actionSalvar_imagem);
        mainToolBar->addAction(actionCarregar_resultado);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSmoothing);
        mainToolBar->addAction(actionArestas);
        mainToolBar->addAction(actionHaar);
        mainToolBar->addAction(actionHaar_inverso);
        mainToolBar->addAction(actionRealce_em_Haar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CG - T2 - Modelo", Q_NULLPTR));
        actionCarregar_imagem->setText(QApplication::translate("MainWindow", "Carregar imagem", Q_NULLPTR));
        actionSalvar_imagem->setText(QApplication::translate("MainWindow", "Salvar imagem", Q_NULLPTR));
        actionSmoothing->setText(QApplication::translate("MainWindow", "Smoothing", Q_NULLPTR));
        actionArestas->setText(QApplication::translate("MainWindow", "Arestas", Q_NULLPTR));
        actionHaar->setText(QApplication::translate("MainWindow", "Haar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionHaar->setToolTip(QApplication::translate("MainWindow", "Haar", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionHaar_inverso->setText(QApplication::translate("MainWindow", "Haar inverso", Q_NULLPTR));
        actionCarregar_resultado->setText(QApplication::translate("MainWindow", "Carregar resultado", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCarregar_resultado->setToolTip(QApplication::translate("MainWindow", "Carregar resultado", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionRealce_em_Haar->setText(QApplication::translate("MainWindow", "Realce em Haar ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRealce_em_Haar->setToolTip(QApplication::translate("MainWindow", "Real\303\247a imagem de Haar", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        inputLabel->setText(QString());
        outputLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
