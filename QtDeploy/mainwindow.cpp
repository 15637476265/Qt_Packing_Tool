#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QDesktopServices>
#include <QTextCursor>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initArgument();
    initObjects();
    initWidgets();
    initSignals();
}

MainWindow::~MainWindow()
{
//    workThread->quit();
//    workThread->wait();
    delete ui;
}

void MainWindow::setCommand(QString data)
{
    temp = data;
    command = temp + "/bin/windeployqt.exe";
}


void MainWindow::on_toolButton_clicked()
{
    appPathAndName = QFileDialog::getOpenFileName(this, tr("Save File"),
                                           "/home/test.exe",
                                           tr("APP (*.exe *.EXE)"));
    exeName=appPathAndName.section('/', -1);
    appName = exeName.section('.',0,0);
    appPath = appPathAndName.left(appPathAndName.lastIndexOf("/"));
    ui->AppPath->setText(appPath);
    ui->appName->setText(appName);
    ui->Run->setDisabled(false);
}


void MainWindow::on_Run_clicked()
{
    setBtnVisible(false);
    modifyArument();
    progress->runApplication(command,argument);
    emit StartProcess();
    ui->reserve_temp->setText(command);
}


void MainWindow::Command_out(QString strDisplay)
{
    ui->textBrowser->setText(strDisplay);
}

void MainWindow::initSignals()
{
    QObject::connect(progress,SIGNAL(CommandOutput(QString)),this,SLOT(Command_out(QString)),Qt::QueuedConnection);
    QObject::connect(progress,SIGNAL(finished(int)),this,SLOT(ProcessFinished(int)),Qt::DirectConnection);
    QObject::connect(this,SIGNAL(StartProcess(void)),progress,SLOT(startProcess(void)),Qt::DirectConnection);
    QObject::connect(progress,SIGNAL(processFinished(int)),this,SLOT(ProcessFinished(int)),Qt::QueuedConnection);
}

void MainWindow::initWidgets()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
    setBtnVisible(false);
}

void MainWindow::initObjects()
{
    //workThread = new QThread(this);
    progress = new MyProcess(this);
//    workThread->start();
//    progress->moveToThread(workThread);
}

void MainWindow::initArgument()
{
    //command = "C:/Qt/Qt5.12.0/5.12.0/msvc2015_64/bin/windeployqt.exe";
    command = readSystemEnv();
}

void MainWindow::modifyArument()
{
    argument.clear();
    argument.insert(0,appPathAndName);
    if(ui->CB_QML->isChecked()){
        argument<<tempArgu.at(0);
        argument<<tempArgu.at(1);
    }

    if(ui->CB_WebKit->isChecked()){
        argument<<"--no-webkit2";
    }

    if(ui->CB_3D->isChecked()){
        argument<<"--no-system-d3d-compiler";
    }

    if(ui->CB_Release->isChecked()){
        argument<<"--release";
    }

    if(ui->CB_Runtime->isChecked()){
        argument<<"--no-compiler-runtime";
    }

}

void MainWindow::setBtnVisible(bool data)
{
    ui->Run->setEnabled(data);
}

QString MainWindow::readSystemEnv()
{
    QString path = QProcessEnvironment::systemEnvironment().value("QTDIR");
    path.replace(QRegExp("\\\\"), "/");
    if(path == ""){
        path = temp;
    }
    path+="/bin/windeployqt.exe";
    return path;
}

void MainWindow::on_qmldir_textChanged(const QString &arg1)
{
    qDebug()<<arg1;
    tempArgu.clear();
    qmlPath = arg1;
    tempArgu.append("--qmldir");
    tempArgu.append(arg1);
}

void MainWindow::ProcessFinished(int id)
{
    if(0 == id){
        progress->stop();
        setBtnVisible(true);
        ui->textBrowser->append("\n");
        ui->textBrowser->append("\n");
        ui->textBrowser->append("\n");
        ui->textBrowser->append("\n");
        ui->textBrowser->append("Sucessed!");
        ui->textBrowser->moveCursor(QTextCursor::End);
        ui->OpenDir->setEnabled(true);
    }else{
        qDebug()<<__FUNCTION__<<"--->CrashExit";
    }

}

void MainWindow::on_TB_qmldir_clicked()
{
    qmlPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                             "/home",
                                                             QFileDialog::ShowDirsOnly
                                                             | QFileDialog::DontResolveSymlinks);
    qDebug()<<qmlPath;
    ui->qmldir->setText(qmlPath);
}

void MainWindow::on_CB_QML_toggled(bool checked)
{
    ui->qmldir->setDisabled(!checked);
    ui->TB_qmldir->setDisabled(!checked);
}


void MainWindow::on_OpenDir_clicked()
{
    QDesktopServices::openUrl(QUrl(appPath, QUrl::TolerantMode));
}

void MainWindow::on_Btn_clear_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::on_action_triggered()
{
    about.show();
}

void MainWindow::on_AppPath_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setBtnVisible(true);
}

void MainWindow::on_actionQTDIR_triggered()
{
    QMessageBox::information(this, "QTDIR说明", "本文件夹下的conf目录conf.ini文件修改QTDIR", QMessageBox::Yes , QMessageBox::Yes);
}

void MainWindow::on_lineEdit_editingFinished()
{
    qtCompilePath = ui->pathC->text();
}
