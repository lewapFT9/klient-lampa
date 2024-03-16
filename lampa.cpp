#include "lampa.h"
#include "ui_lampa.h"

#include <QMetaEnum>
#include <QMessageBox>


Lampa::Lampa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lampa)
{
    ui->setupUi(this);
    setKontroler();
    lightStatus = "Off";
    lightColor = "Red";
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
    auto message = "Lampa";
    kontroler.send(message);
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

void Lampa::lampaDataReady(QByteArray data)
{
    ui->commands->addItem(QString(data));
}

void Lampa::action(QByteArray data)
{
    QString command= QString(data);
    if(command=="Turn off the light" && lightStatus !="Off"){
        QMessageBox::information(this,"Command","Turning off the light");
        ui->commands->addItem("Done");
        lightStatus = "Off";
    }
    else if(command=="Turn off the light" && lightStatus =="Off"){
        QMessageBox::information(this,"Command","Light is already off");
        ui->commands->addItem("Done");
    }
    else if(command=="Turn on the light" && lightStatus !="On"){
        QMessageBox::information(this,"Command","Turning on the light");
        ui->commands->addItem("Done");
        lightStatus = "On";
    }
    else if(command=="Turn on the light" && lightStatus =="On"){
        QMessageBox::information(this,"Command","Light is already on");
        ui->commands->addItem("Done");
    }
}

void Lampa::setKontroler()
{
    connect(&kontroler,&Kontroler::connected,this, &Lampa::lampaConnected);
    connect(&kontroler,&Kontroler::disconnected,this, &Lampa::lampaDisconnected);
    connect(&kontroler,&Kontroler::stateChanged,this, &Lampa::lampaStateChanged);
    connect(&kontroler,&Kontroler::errorOccurred,this, &Lampa::lampaErrorOccurred);
    connect(&kontroler,&Kontroler::dataReady,this, &Lampa::lampaDataReady);
    connect(&kontroler,&Kontroler::dataReady,this, &Lampa::action);


}

