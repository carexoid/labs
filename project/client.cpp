#include "client.h"

Client::Client(QObject* parent): QObject(parent) {
    _sok = new QTcpSocket(this);
    _blockSize = 0;
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    //connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}


void Client::onSokReadyRead(){
    qDebug() << "ready";
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
        break;
        case Client::FindUserCom:{
            QString userName;
            in >> userName;
            qDebug() << userName;
            if (userName != "")
                _mainWin->canAddNewChat(userName,true);
        }
         break;





    }

}

void Client::onSokConnected(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << (quint8)Client::AutReqCom << _name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
    qDebug() << block;
}


void Client::onSokDisconnected(){
    qDebug() << "disconnected";
}
