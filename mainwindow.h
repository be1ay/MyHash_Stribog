#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_rb512_clicked();

    void on_rb256_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;


};
class MyClass : public QObject
{
    Q_OBJECT

public:
    explicit MyClass(QObject *parent = 0);

private:
    bool needStop; // эта переменная нам будет сигнализировать, что пора завершать работу

signals:
    void finished();  // сигнал будем вызвать, когда закончили работу
    void sendString(QString); // через этот сигнал будем общаться с главным окном
    void sendStringDone(QString);
    void sendStringFileName(QString);
    void change_value(int value); // изменить value
    void set_max(int value);

public slots:

    void MyCalcMD5();
    void GOST2012();
   // void start(); // в этом слоте будут выполняться все действия
    void stop(); // этот слот будет говорить нам, что пора завершать работу (просто сделает needStop=true)
};
#endif // MAINWINDOW_H
/*
//mainwindow.h
public:
    QString labelText();
    void setLabelText(QString string);

//mainwindow.cpp
QString MainWindow::labelText() {
    return ui->label->text();
}

void MainWindow::setLabelText(QString text) {
    ui->label->setText(text);
}
*/
