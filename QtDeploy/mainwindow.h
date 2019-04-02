#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myprocess.h"
#include "about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCommand(QString);

private slots:
    void on_toolButton_clicked();
    void on_Run_clicked();
    //void on_Command_out(QByteArray);
    void Command_out(QString);
    void on_qmldir_textChanged(const QString &arg1);
    void ProcessFinished(int);
    void on_TB_qmldir_clicked();

    void on_CB_QML_toggled(bool checked);

    void on_OpenDir_clicked();

    void on_Btn_clear_clicked();

    void on_action_triggered();

    void on_AppPath_textChanged(const QString &arg1);

    void on_actionQTDIR_triggered();

    void on_lineEdit_editingFinished();

signals:
    void StartProcess(void);


private:
    Ui::MainWindow *ui;
    void initSignals();
    void initWidgets();
    void initObjects();
    void initArgument();
    void modifyArument();
    void setBtnVisible(bool);
    QString readSystemEnv();
private:
    QString qmlPath;
    QString appPathAndName;
    QString appPath;
    QString exeName;
    QString appName;
    QString temp;

    MyProcess *progress;
    About about;

    //QThread *workThread;
private:
    QString command;
    QStringList argument;
    QStringList tempArgu;
    QString qtCompilePath;
};

#endif // MAINWINDOW_H
