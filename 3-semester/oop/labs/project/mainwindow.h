#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"

#include <QMainWindow>
#include<QListWidgetItem>
#include <QTcpServer>

class Client;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void canAddNewChat(QString chatName, bool flag);

    void receiveTxtMsg(QString fullMsg);

    void receiveImg(QListWidgetItem* myPic);

private slots:
    void on_actionNew_chat_triggered();

    void on_sendingButton_clicked();

    void on_sendPhotoButton_clicked();

    void on_chatLists_currentRowChanged(int currentRow);


private:
    Ui::MainWindow *ui;

    int _chatsNum = 0;

    QVector<QVector<QListWidgetItem> > chats;

    Client *myClient;

    void setNewMsgList(int row);

    void addToChatHistory(QListWidgetItem  item, int row);

    void addNewChat(QString chatName);


};

#endif // MAINWINDOW_H
