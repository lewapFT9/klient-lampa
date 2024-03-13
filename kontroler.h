#ifndef KONTROLER_H
#define KONTROLER_H

#include <QObject>
#include <QTcpSocket>

class Kontroler : public QObject
{
    Q_OBJECT
public:
    explicit Kontroler(QObject *parent = nullptr);
    void connectWithServer(QString ip, int port);
    void disconnectFromServer();
    QAbstractSocket::SocketState currentState();
signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);

private slots:
    void socketStateChanged(QAbstractSocket::SocketState state);


private:
    QTcpSocket socket;
    QString serverIp;
    int ServerPort;
};


#endif // KONTROLER_H
