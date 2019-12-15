#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "book.h"
#include "author.h"
#include "testingback.h"

int main(int argc, char *argv[])
{

    testingFunctions();
    std::cout << "Let's start" << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
