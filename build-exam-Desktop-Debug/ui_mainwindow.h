/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListView *bookList;
    QListView *authorList;
    QTextBrowser *AuthorInBook;
    QLabel *BooksLabel;
    QLabel *AuhtorLabel;
    QTextBrowser *BookInfo;
    QLabel *BookInfoLabel;
    QTextBrowser *AuthorInfo;
    QLabel *AuthorInfoLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(860, 641);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        bookList = new QListView(centralWidget);
        bookList->setObjectName(QStringLiteral("bookList"));
        bookList->setGeometry(QRect(30, 40, 271, 341));
        authorList = new QListView(centralWidget);
        authorList->setObjectName(QStringLiteral("authorList"));
        authorList->setGeometry(QRect(570, 40, 271, 341));
        AuthorInBook = new QTextBrowser(centralWidget);
        AuthorInBook->setObjectName(QStringLiteral("AuthorInBook"));
        AuthorInBook->setGeometry(QRect(305, 160, 261, 101));
        BooksLabel = new QLabel(centralWidget);
        BooksLabel->setObjectName(QStringLiteral("BooksLabel"));
        BooksLabel->setGeometry(QRect(30, 20, 75, 18));
        AuhtorLabel = new QLabel(centralWidget);
        AuhtorLabel->setObjectName(QStringLiteral("AuhtorLabel"));
        AuhtorLabel->setGeometry(QRect(570, 20, 75, 18));
        BookInfo = new QTextBrowser(centralWidget);
        BookInfo->setObjectName(QStringLiteral("BookInfo"));
        BookInfo->setGeometry(QRect(30, 410, 391, 161));
        BookInfoLabel = new QLabel(centralWidget);
        BookInfoLabel->setObjectName(QStringLiteral("BookInfoLabel"));
        BookInfoLabel->setGeometry(QRect(30, 390, 75, 18));
        AuthorInfo = new QTextBrowser(centralWidget);
        AuthorInfo->setObjectName(QStringLiteral("AuthorInfo"));
        AuthorInfo->setGeometry(QRect(450, 410, 391, 161));
        AuthorInfoLabel = new QLabel(centralWidget);
        AuthorInfoLabel->setObjectName(QStringLiteral("AuthorInfoLabel"));
        AuthorInfoLabel->setGeometry(QRect(450, 390, 101, 18));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 860, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        BooksLabel->setText(QApplication::translate("MainWindow", "Books", Q_NULLPTR));
        AuhtorLabel->setText(QApplication::translate("MainWindow", "Authors", Q_NULLPTR));
        BookInfoLabel->setText(QApplication::translate("MainWindow", "Book info", Q_NULLPTR));
        AuthorInfoLabel->setText(QApplication::translate("MainWindow", "Author info", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
