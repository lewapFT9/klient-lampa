#include "kontroler.h"

Kontroler::Kontroler(QObject *parent)
    : QObject{parent}
{
    connect(&socket,&QTcpSocket::connected,this, &Kontroler::connected);
    connect(&socket,&QTcpSocket::disconnected,this, &Kontroler::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this, &Kontroler::socketStateChanged);
    connect(&socket,&QTcpSocket::errorOccurred,this, &Kontroler::errorOccurred);


}

void Kontroler::connectWithServer(QString ip, int port)
{
    if(socket.isOpen()){
        if(ip==serverIp && port==ServerPort){
            return;
        }
        socket.close();
    }
    serverIp=ip;
    ServerPort=port;
    socket.connectToHost(serverIp,ServerPort);
}

void Kontroler::socketStateChanged(QAbstractSocket::SocketState state)
{
    if(state==QAbstractSocket::UnconnectedState){
        socket.close();
    }
    emit stateChanged(state);
}
