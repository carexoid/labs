#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onNewConnection();

private:
    Ui::MainWindow *ui;

    QList<Client* > _clients;
    QTcpServer _server;

};

#endif // MAINWINDOW_H
