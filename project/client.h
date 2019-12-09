
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QInputDialog>

#include "mainwindow.h"

class MainWindow;

class Client : public QObject{
    Q_OBJECT
    friend class MainWindow;
public:
    explicit Client(QObject* parent = 0);
    static const quint8 AutReqCom = 0;
    static const quint8 FindUserCom = 1;
    static const quint8 NewTxtMsgCom = 2;
private slots:
    void onSokReadyRead();
    void onSokConnected();
    void onSokDisconnected();

private:
    MainWindow* _mainWin;

    QTcpSocket *_sok;
    QString _name;
    quint16 _blockSize;



};

#endif // CLIENT_H
