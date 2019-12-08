#include "client.h"

Client::Client(QObject* parent): QObject(parent) {
    _sok = new QTcpSocket(this);

    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    //connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    //connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}


void Client::onSokReadyRead(){

}

void Client::onSokDisconnected(){}
