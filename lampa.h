#ifndef LAMPA_H
#define LAMPA_H

#include <QMainWindow>
#include <QStyle>
#include <QHostAddress>
#include "kontroler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Lampa;
}
QT_END_NAMESPACE

class Lampa : public QMainWindow
{
    Q_OBJECT

public:
    Lampa(QWidget *parent = nullptr);
    ~Lampa();

private slots:
    void on_IpAddress_textChanged(const QString &arg1);

    void on_connect_clicked();

    void lampaConnected();
    void lampaDisconnected();
    void lampaStateChanged(QAbstractSocket::SocketState);
    void lampaErrorOccurred(QAbstractSocket::SocketError);
    void lampaDataReady(QByteArray data);


private:
    Ui::Lampa *ui;
    Kontroler kontroler;

    void setKontroler();
};
#endif // LAMPA_H
