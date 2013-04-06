#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QList>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>
#include "task.h"

class Controller : public QTcpServer
{
    Q_OBJECT

public:
    Controller( QObject );
    ~Controller();
    explicit Controller(QObject *parent = 0);
    void start();

private:
    QString serverAddr, ipDir;
    int serverPort, ipKey;
    QList<QString> ipList;
    QThreadPool *conPool;

protected:
    void incomingConnection(int handle);

private slots:
    void communicate(int handle);

};

#endif // CONTROLLER_H

