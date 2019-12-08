#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_server,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
    if (_server.listen(QHostAddress::LocalHost,7000))
        ui->ServerStatus->setText(tr("Is listening"));
}

void MainWindow::onNewConnection(){
    Client *newClient = new Client();
    newClient->_allClients = &_clients;
    newClient->_sok = _server.nextPendingConnection();
    _clients.append(newClient);
    QTextStream txtStream(newClient->_sok);
    if (newClient->_sok->waitForReadyRead((-1))){
         newClient->_name = txtStream.readLine();
    }

   // qDebug() << txtStream.readLine();
    for (int j = 0; j < _clients.length(); ++j){
        qDebug() << _clients.at(j)->_name;
    }
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << Client::FindUserCom << newClient->_name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    newClient->_sok->write(block);
}

MainWindow::~MainWindow()
{
    delete ui;
}
