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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *BooksLabel;
    QLabel *booksStatus;
    QLabel *AuhtorLabel;
    QLabel *authorsStatus;
    QListView *bookList;
    QTextBrowser *AuthorInBook;
    QListView *authorList;
    QPushButton *reseter;
    QLabel *BookInfoLabel;
    QLabel *AuthorInfoLabel;
    QTextBrowser *BookInfo;
    QTextBrowser *AuthorInfo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(855, 658);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        BooksLabel = new QLabel(centralWidget);
        BooksLabel->setObjectName(QStringLiteral("BooksLabel"));

        gridLayout->addWidget(BooksLabel, 0, 0, 1, 1);

        booksStatus = new QLabel(centralWidget);
        booksStatus->setObjectName(QStringLiteral("booksStatus"));
        booksStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(booksStatus, 0, 1, 1, 1);

        AuhtorLabel = new QLabel(centralWidget);
        AuhtorLabel->setObjectName(QStringLiteral("AuhtorLabel"));

        gridLayout->addWidget(AuhtorLabel, 0, 4, 1, 1);

        authorsStatus = new QLabel(centralWidget);
        authorsStatus->setObjectName(QStringLiteral("authorsStatus"));
        authorsStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(authorsStatus, 0, 5, 1, 1);

        bookList = new QListView(centralWidget);
        bookList->setObjectName(QStringLiteral("bookList"));

        gridLayout->addWidget(bookList, 1, 0, 2, 2);

        AuthorInBook = new QTextBrowser(centralWidget);
        AuthorInBook->setObjectName(QStringLiteral("AuthorInBook"));

        gridLayout->addWidget(AuthorInBook, 1, 2, 1, 2);

        authorList = new QListView(centralWidget);
        authorList->setObjectName(QStringLiteral("authorList"));

        gridLayout->addWidget(authorList, 1, 4, 2, 2);

        reseter = new QPushButton(centralWidget);
        reseter->setObjectName(QStringLiteral("reseter"));

        gridLayout->addWidget(reseter, 2, 2, 1, 2);

        BookInfoLabel = new QLabel(centralWidget);
        BookInfoLabel->setObjectName(QStringLiteral("BookInfoLabel"));

        gridLayout->addWidget(BookInfoLabel, 3, 0, 1, 2);

        AuthorInfoLabel = new QLabel(centralWidget);
        AuthorInfoLabel->setObjectName(QStringLiteral("AuthorInfoLabel"));

        gridLayout->addWidget(AuthorInfoLabel, 3, 3, 1, 1);

        BookInfo = new QTextBrowser(centralWidget);
        BookInfo->setObjectName(QStringLiteral("BookInfo"));

        gridLayout->addWidget(BookInfo, 4, 0, 1, 3);

        AuthorInfo = new QTextBrowser(centralWidget);
        AuthorInfo->setObjectName(QStringLiteral("AuthorInfo"));

        gridLayout->addWidget(AuthorInfo, 4, 3, 1, 3);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 855, 23));
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
        booksStatus->setText(QString());
        AuhtorLabel->setText(QApplication::translate("MainWindow", "Authors", Q_NULLPTR));
        authorsStatus->setText(QString());
        reseter->setText(QApplication::translate("MainWindow", "Reset filters", Q_NULLPTR));
        BookInfoLabel->setText(QApplication::translate("MainWindow", "Book info", Q_NULLPTR));
        AuthorInfoLabel->setText(QApplication::translate("MainWindow", "Author info", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
