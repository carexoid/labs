#include "client.h"

Client::Client(QObject* parent) : QObject(parent){
    _sok = new QTcpSocket(this);
    _blockSize = 0;

    qDebug() << connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    //connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}

Client::Client(QTcpSocket* sok, QObject* parent) : QObject(parent){
    _sok = sok;
    _blockSize = 0;
    qDebug() << connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
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
        case Client::AutReqCom:{
            QString clientName;
            in >> clientName;
            qDebug() << clientName;
            _name = clientName;
        }
        break;
        case Client::FindUserCom:{
            QString userName;
            in >> userName;
            qDebug() << userName;
            for (int i = 0; i < _allClients->size() ; i++)
            if (_allClients->at(i)->_name == userName){
                QByteArray blockOut;
                QDataStream out(&blockOut, QIODevice::WriteOnly);
                out << (quint16)0 << (quint8)Client::FindUserCom << userName;
                out.device()->seek(0);
                out << (quint16)(blockOut.size() - sizeof(quint16));
                _sok->write(blockOut);
            }
        }
        break;
        case Client::NewTxtMsgCom:{
            QString fullMsg;
            in >> fullMsg;
            qDebug() << fullMsg;
            QString rcvr;
            int i = 0;
            while(fullMsg[i] != ':'){
                rcvr += fullMsg[i];
                fullMsg.remove(i,1);
            }
            if (_name != rcvr){
                fullMsg = _name + fullMsg;
                qDebug() << rcvr;
                for (int i = 0; i < _allClients->size() ; i++)
                    if (_allClients->at(i)->_name == rcvr){
                        QByteArray blockOut;
                        QDataStream out(&blockOut, QIODevice::WriteOnly);
                        out << (quint16)0 << (quint8)Client::NewTxtMsgCom << fullMsg;
                        out.device()->seek(0);
                        out << (quint16)(blockOut.size() - sizeof(quint16));
                        _allClients->at(i)->_sok->write(blockOut);
                    }
            }
        }

        break;
    case Client::NewImgMsgCom:{

        QListWidgetItem myPicToSend;
        in >> myPicToSend;
        QString fullMsg = myPicToSend.text();
        qDebug() << fullMsg;
        QString rcvr;
        int i = 0;
        while(fullMsg[i] != ':'){
            rcvr += fullMsg[i];
            fullMsg.remove(i,1);
        }
        if (_name != rcvr){
            fullMsg = _name + fullMsg;
            myPicToSend.setText(fullMsg);
            qDebug() << rcvr;
            for (int i = 0; i < _allClients->size() ; i++)
                if (_allClients->at(i)->_name == rcvr){
                    QByteArray blockOut;
                    QDataStream out(&blockOut, QIODevice::WriteOnly);
                    out << (quint16)0 << (quint8)Client::NewImgMsgCom <<myPicToSend;
                    out.device()->seek(0);
                    out << (quint16)(blockOut.size() - sizeof(quint16));
                    _allClients->at(i)->_sok->write(blockOut);
                }
        }
    }

    break;
    }
}

void Client::onSokConnected(){
    qDebug() << "connected";
}

void Client::onSokDisconnected(){
    qDebug() << "disconected";
}
