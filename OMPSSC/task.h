#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QtNetwork/QTcpSocket>
#include <iostream>
#include <stdlib.h>
#include <QDateTime>
#include <QProcess>
#include <QUuid>

using namespace std;

class Task : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Task();
    ~Task();
    void run();
    int socketDescriptor;

signals:
    void requestCommunicate(int);

};

#endif // TASK_H
