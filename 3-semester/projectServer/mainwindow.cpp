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
    auto newSok = _server.nextPendingConnection();
    Client *newClient = new Client(newSok);
    newClient->_allClients = &_clients;
    _clients.append(newClient);
//    QTextStream txtStream(newClient->_sok);
//    if (newClient->_sok->waitForReadyRead((-1))){
//         newClient->_name = txtStream.readLine();
//    }

//   // qDebug() << txtStream.readLine();
//    for (int j = 0; j < _clients.length(); ++j){
//        qDebug() << _clients.at(j)->_name;
//    }
}

void MainWindow::delClient(QString name){
    for (int i = 0; i < _clients.length(); i++){
        if (_clients.at(i)->_name == name){
            _clients.erase(_clients.begin() + i);
            break;
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
