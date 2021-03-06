#include "mainwindow.h"
#include "client.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myClient = new Client();
    while (myClient->_name == "")
        myClient->_name = QInputDialog::getText(this, tr("Enter as"), tr("User name"));
    myClient->_sok->connectToHost(QHostAddress::LocalHost,7000);
    myClient->_mainWin = this;
    ui->myNick->setText("My nick: " + myClient->_name);
    if(myClient->_sok->waitForConnected(-1))
          qDebug() << "connected";

    qDebug() << myClient->_name;

//    QTextStream txtStream(myClient->_sok);
//    txtStream << myClient->_name;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_chat_triggered()
{
    QString chatName = QInputDialog::getText(this, tr("Find user"), tr("User name"));
    if(chatName != ""){
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << (quint16)0 << (quint8)Client::FindUserCom << chatName;
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));
        myClient->_sok->write(block);
        qDebug() << myClient->_sok->peerPort();
        //if(chatName != "")
        //addNewChat(chatName);

    }

}

void MainWindow::on_sendingButton_clicked()
{
    QString msgText = ui->msgEdit->toPlainText();
    QString myMsg = "Me: " + msgText;
    QString rcvr = ui->chatLists->currentItem()->text();
    if (msgText != ""){
        ui->msgList->addItem(myMsg);
        ui->msgEdit->clear();
        addToChatHistory(QListWidgetItem(myMsg),ui->chatLists->currentRow());
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << (quint16)0 << (quint8)Client::NewTxtMsgCom << rcvr + ": " + msgText;
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));
        myClient->_sok->write(block);
        qDebug() << myClient->_sok->peerPort();
        //if(chatName != "")
        //addNewChat(chatName);
    }
}

void MainWindow::on_sendPhotoButton_clicked()
{
    QString msgText = ui->msgEdit->toPlainText();
    QString picPath = QFileDialog::getOpenFileName(this, tr("Open image"), QString(), tr("Image Files (*.png *.jpg *.bmp)"));
    QListWidgetItem *myPic = new QListWidgetItem(QIcon(picPath),"Me: " + msgText);
    QImage img (picPath);
    QString rcvr = ui->chatLists->currentItem()->text();
    myPic->setText("Me: " + msgText);
    //myPic->setSizeHint(QSize(300,300));
    if (picPath != "")
        ui->msgList->addItem(myPic);
    ui->msgEdit->clear();
    addToChatHistory(*myPic,ui->chatLists->currentRow());
    QListWidgetItem myPicToSend(QIcon(picPath),rcvr + ": " + msgText);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << (quint8)Client::NewImgMsgCom << myPicToSend;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    myClient->_sok->write(block);


}

void MainWindow::on_chatLists_currentRowChanged(int currentRow)
{
    qDebug() << currentRow;
    setNewMsgList(currentRow);
}

void MainWindow::setNewMsgList(int row){
    ui->msgList->clear();
    for(const auto& item: chats[row]){
        qDebug() << &item;
        ui->msgList->addItem(new QListWidgetItem(item));
    }
}

void MainWindow::addToChatHistory(QListWidgetItem item,int row){
    chats[row].push_back(item);
}

void MainWindow::addNewChat(QString chatName){
    _chatsNum++;
    ui->chatLists->addItem(chatName);
    chats.push_back(QVector<QListWidgetItem>());
    ui->chatLists->setCurrentRow(chats.size() - 1);
}

void MainWindow::canAddNewChat(QString chatName, bool flag){
    if (flag)
        addNewChat(chatName);
}

void MainWindow::receiveTxtMsg(QString fullMsg){
    QString rcvr;
    int i = 0;
    while (fullMsg[i] != ':')
        rcvr += fullMsg[i++];
    qDebug() << rcvr;
    bool flag = false;
    for (int i = 0; i < _chatsNum; i++)
        if (ui->chatLists->item(i)->text() == rcvr){
            flag = true;
            qDebug() << rcvr;
            if (ui->chatLists->currentRow() == i)
                ui->msgList->addItem(fullMsg);
            addToChatHistory(QListWidgetItem(fullMsg),i);
        }
    if (!flag){
        _chatsNum++;
        ui->chatLists->addItem(rcvr);
        chats.push_back(QVector<QListWidgetItem>());
        addToChatHistory(QListWidgetItem(fullMsg),chats.size() - 1);

    }

}

void MainWindow::receiveImg(QListWidgetItem* myPic){
    QString fullMsg = myPic->text();
    QString rcvr;
    int i = 0;
    while (fullMsg[i] != ':')
        rcvr += fullMsg[i++];
    qDebug() << rcvr;
    bool flag = false;
    for (int i = 0; i < _chatsNum; i++)
        if (ui->chatLists->item(i)->text() == rcvr){
            flag = true;
            qDebug() << rcvr;
            if (ui->chatLists->currentRow() == i)
                ui->msgList->addItem(myPic);
            addToChatHistory(QListWidgetItem(*myPic),i);
        }
    if (!flag){
        _chatsNum++;
        ui->chatLists->addItem(rcvr);
        chats.push_back(QVector<QListWidgetItem>());
        addToChatHistory(QListWidgetItem(*myPic),chats.size() - 1);

    }

}
