#include "client.h"

Client::Client(QObject* parent) : QObject(parent){
    _sok = new QTcpSocket(this);

    qDebug() << connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    //connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}



void Client::onSokReadyRead(){
    QDataStream in(_sok);
    qDebug() << "trig";
    if(_blockSize == 0){
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> _blockSize;
    }

    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        _blockSize = 0;

    quint8 command;
    in >> command;

    switch (command){
        case 1:{
            QString userName;
            in >> userName;
            qDebug() << userName;
            for (int i = 0; i < _allClients->size() ; i++)
            if (_allClients->at(i)->_name == userName){
                qDebug() << userName;
            }
         break;



        }
    }
}

void Client::onSokConnected(){
    qDebug() << "connected";
}

void Client::onSokDisconnected(){}
