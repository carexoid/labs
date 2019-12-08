#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QInputDialog>

class Client : public QObject{
     friend class MainWindow;
public:
    Client();
    const quint8 AutReqCom = 0;
    const quint8 FindUserCom = 1;
    const quint8 NewTxtMsgCom = 2;
private slots:
    void onSokReadyRead();
    void onSokConnected();
    void onSokDisconnected();

private:
    QTcpSocket *_sok;
    QString _name;




};

#endif // CLIENT_H
