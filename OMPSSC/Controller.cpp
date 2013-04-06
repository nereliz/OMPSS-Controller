#include "Controller.h"

#include <iostream>
#include <QSettings>
#include <QDir>

using namespace std;

Controller::Controller(QObject *parent) :
    QTcpServer(parent)
{
    QString dir = QDir::current().absolutePath();
    QSettings settings( dir+"/config.ini", QSettings::IniFormat );
    settings.beginGroup("user");

    this->conPool = new QThreadPool();
    this->conPool->setMaxThreadCount( 100 );
    this->serverAddr=settings.value( "serverAddress" ).toString();
    this->serverPort=settings.value( "serverPort" ).toInt();
    this->ipDir=settings.value( "ipDir" ).toString();
    this->ipKey = 0;
}

Controller::~Controller()
{
}

void Controller::start()
{
    cout<< "Controller Starting...  \n";

    if( this->serverAddr == "%" )
    {
        this->listen( QHostAddress::Any,this->serverPort );
    }
    else
    {
        QHostAddress hostadd(this->serverAddr);
        this->listen(hostadd,this->serverPort);
    }

    if( this->isListening() )
        cout << "Port listening on " << this->serverAddr.toStdString() << ":" << this->serverPort <<"\n";
    else
    {
        cout << "Port listening on " << this->serverAddr.toStdString() << ":" << this->serverPort << " failed\n";
    }

    cout << "Reading ip lists: \n";
    QDir *directory = new QDir();
    directory->cd( this->ipDir );
    this->ipList = directory->entryList( QDir::Files );

    if( !directory->cd( this->ipDir ) || this->ipList.size() == 0 )
    {
        cout << "There is no nods available.\nExiting....\n";
        exit( 0 );
    }
    cout << "Nodes: \n";
    for( int i =0; i < this->ipList.size(); i++ )
    {
        cout << this->ipList[i].toStdString() << "\n";
    }
}
void Controller::incomingConnection( int handle )
{
    Task *e= new Task();
    e->socketDescriptor=handle;
    connect(e, SIGNAL(requestCommunicate(int)),this ,SLOT(communicate(int)));
    conPool->start(e);
}


void Controller::communicate(int handle )
{
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor( handle );
    socket->waitForReadyRead();
    QByteArray data=socket->readAll();
    QTcpSocket *socketOut = new QTcpSocket();

    int iteration = 0;
    do{
        if( iteration > 0 )
        {
            socketOut->waitForDisconnected();
            socketOut->close();
        }
        socketOut->connectToHost( this->ipList[ this->ipKey ], this->serverPort, QIODevice::ReadWrite );
        this->ipKey = ( this->ipKey + 1 ) % this->ipList.size();
        iteration++;
        if( socketOut->waitForConnected(500) && socketOut->isWritable() )
            break;
    }while( true );

    socketOut->write( data );
    //cout << "'" << QString( data ).toStdString() << "' sent to" << this->ipList[ this->ipKey ].toStdString() << "\n";

    socketOut->waitForReadyRead(500);
    data = socketOut->readAll();
    socketOut->disconnectFromHost();
    socketOut->close();

    //cout << "'" << QString( data ).toStdString() << "' response form " << this->ipList[ this->ipKey ].toStdString() << "\n;";

    socket->write( QString( data ).toStdString().c_str() );
    socket->flush();
    socket->waitForBytesWritten( 500 );
    socket->disconnectFromHost();
    socket->close();

}

