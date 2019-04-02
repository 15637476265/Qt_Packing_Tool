#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QThread>
#include <QProcess>
#include <QMutexLocker>
#include <QObject>

class MyProcess:public QThread
{
    Q_OBJECT
public:
    MyProcess(QObject *parent = nullptr);
    ~MyProcess();

public:
    void runApplication(QString command,QStringList argument);
    void stop();
protected:
    void run();

signals:
    void CommandOutput(QString);
    void finished(int);
    void processFinished(int);
private:
    void initSignals();

public slots:
    void readOut();
    void errorOut();
    void errorDisplay(QProcess::ProcessError);
    void startProcess(void);
private:
    QProcess *myProcess;
    QString procOutput;
    QMutex m_mutex;
    volatile bool is_running;

private:
    QString command;
    QStringList arguments;
};

#endif // MYPROCESS_H
