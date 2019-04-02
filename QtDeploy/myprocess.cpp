#include "myprocess.h"
#include <QDebug>
#include <QApplication>

MyProcess::MyProcess(QObject *parent)
{
    Q_UNUSED(parent);
    myProcess = new QProcess;
    myProcess->moveToThread(this);

    myProcess->setProcessChannelMode(QProcess::SeparateChannels);
    myProcess->setReadChannel(QProcess::StandardOutput);
}



MyProcess::~MyProcess()
{
    myProcess->close();

    myProcess->waitForFinished();
//    myProcess->terminate();
//    stop();
//    quit();
//    wait();
    delete myProcess;
    myProcess = nullptr;
}

void MyProcess::runApplication(QString command, QStringList argument)
{
    this->command = command;
    this->arguments = argument;
}


void MyProcess::run()
{
    myProcess->start(command,arguments);
    bool ret = myProcess->waitForFinished();
    if(ret){
        readOut();
        qDebug()<<"exitStatus---->"<<myProcess->exitStatus();
        qDebug()<<"exitCode---->"<<myProcess->exitCode();
        emit processFinished(0);
        myProcess->close();
    }
}

void MyProcess::initSignals()
{
    QObject::connect(myProcess,SIGNAL(finished(int)),this,SIGNAL(finished(int)),Qt::DirectConnection);
    QObject::connect(myProcess, SIGNAL(readyReadStandardOutput()),this,SLOT(readOut()),Qt::AutoConnection);
    QObject::connect(myProcess, SIGNAL(readyReadStandardError()),this,SLOT(errorOut()),Qt::DirectConnection);
    QObject::connect(myProcess, SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(errorDisplay(QProcess::ProcessError)),Qt::DirectConnection);
}

void MyProcess::readOut()
{
    procOutput = QString(myProcess->readAllStandardOutput());
    CommandOutput(procOutput);
}

void MyProcess::errorOut()
{
    qDebug()<<__FUNCTION__;
}

void MyProcess::errorDisplay(QProcess::ProcessError data)
{
    qDebug()<<data<<__FUNCTION__;
}

void MyProcess::startProcess(void)
{
    this->start();
    this->wait();
}


void MyProcess::stop()
{
//    QMutexLocker locker(&m_mutex);
//    is_running = false;
        quit();
        wait();
}
