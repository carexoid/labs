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
    QString msgText = "Me: " + ui->msgEdit->toPlainText();
    if (msgText != "Me: ")
        ui->msgList->addItem(msgText);
    ui->msgEdit->clear();
    addToChatHistory(QListWidgetItem(msgText),ui->chatLists->currentRow());
}

void MainWindow::on_sendPhotoButton_clicked()
{
    QString msgText = ui->msgEdit->toPlainText();
    QString picPath = QFileDialog::getOpenFileName(this, tr("Open image"), QString(), tr("Image Files (*.png *.jpg *.bmp)"));
    QListWidgetItem *myPic = new QListWidgetItem(QIcon(picPath),"Me: " + msgText);
    myPic->setText("Me: " + msgText);
    //myPic->setSizeHint(QSize(300,300));
    if (picPath != "")
        ui->msgList->addItem(myPic);
    ui->msgEdit->clear();
    addToChatHistory(*myPic,ui->chatLists->currentRow());

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
    ui->chatLists->addItem(chatName);
    chats.push_back(QVector<QListWidgetItem>());
    ui->chatLists->setCurrentRow(chats.size() - 1);
}

void MainWindow::canAddNewChat(QString chatName, bool flag){
    if (flag)
        addNewChat(chatName);

}

