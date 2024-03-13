#include "lampa.h"
#include "ui_lampa.h"

#include <QMetaEnum>


Lampa::Lampa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lampa)
{
    ui->setupUi(this);
    setKontroler();
}

Lampa::~Lampa()
{
    delete ui;
}

void Lampa::on_IpAddress_textChanged(const QString &arg1)
{
    QString isCorrect ="0";

    if(arg1=="..."){
        isCorrect="";

    }
    else{
        QHostAddress isValid(arg1);
        if(QAbstractSocket::IPv4Protocol==isValid.protocol()){
            isCorrect="1";
        }
    }
    ui->IpAddress->setProperty("isCorrect",isCorrect);
    style()->polish(ui->IpAddress);
}


void Lampa::on_connect_clicked()
{
    if(kontroler.currentState()==QAbstractSocket::ConnectedState)
        kontroler.disconnectFromServer();
    else{
        auto ip=ui->IpAddress->text();
        auto port=ui->port->value();
        kontroler.connectWithServer(ip,port);
    }
}

void Lampa::lampaConnected()
{
    ui->messages->addItem("Lampa Connected");
    ui->connect->setText("Disconnect");
    style()->polish(ui->messages);
}

void Lampa::lampaDisconnected()
{
    ui->messages->addItem("Lampa Disconnected");
    ui->connect->setText("Connect");
    style()->polish(ui->messages);

}

void Lampa::lampaStateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->messages->addItem(metaEnum.valueToKey(state));
    style()->polish(ui->messages);

}

void Lampa::lampaErrorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    ui->messages->addItem(metaEnum.valueToKey(error));
    style()->polish(ui->messages);

}

void Lampa::setKontroler()
{
    connect(&kontroler,&Kontroler::connected,this, &Lampa::lampaConnected);
    connect(&kontroler,&Kontroler::disconnected,this, &Lampa::lampaDisconnected);
    connect(&kontroler,&Kontroler::stateChanged,this, &Lampa::lampaStateChanged);
    connect(&kontroler,&Kontroler::errorOccurred,this, &Lampa::lampaErrorOccurred);
}

