//Alexey Belkin
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QCryptographicHash>
#include <QThread>
#include <QDebug>
#include <QMessageBox>
extern "C"{
    #include "gost3411-2012-core.h"
}
GOST34112012Context *CTX;
unsigned char digest[64];
unsigned char hexdigest[129];
uint sizeHash=64;
QString fname="";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

MyClass::MyClass(QObject *parent) :
    QObject(parent)
{
    needStop = false;
}
void MyClass::stop()
{
    needStop = true;
}
void MyClass::MyCalcMD5()
{
emit set_max(0);
        QCryptographicHash hash(QCryptographicHash::Md5);
        QFile file(fname);
        if (file.open(QIODevice::ReadOnly) )
          {

            while (!file.atEnd()) {
            QByteArray line = file.read(1024);
            hash.addData(line);
          }
        }
        file.close();
        QString rez = hash.result().toHex().data();
        emit sendString(rez);emit set_max(100);emit change_value(100);
emit finished();emit sendStringDone("Complete");
}
static void
reverse_order(unsigned char *in, size_t len)
{
    unsigned char c;
    unsigned int i, j;

    for (i = 0, j = (unsigned int) len - 1; i < j; i++, j--)
    {
        c = in[i];
        in[i] = in[j];
        in[j] = c;
    }
}

static void
convert_to_hex(unsigned char *in, unsigned char *out, size_t len,
        const unsigned int eflag)
{
    unsigned int i;
    char ch[3];

    if (len > 64) len = 64;

    memset(out, 0, 129);

    /* eflag is set when little-endian output requested */
    if (eflag) reverse_order(in, len);

    for (i = 0; i < len; i++)
    {
        sprintf(ch, "%02x", (unsigned char) in[i]);
        strncat((char *) &out[0], ch, 2);
    }
}
void MyClass::GOST2012(){
emit set_max(0);
    QFile file(fname);
    emit sendStringFileName(fname);
    CTX = (GOST34112012Context*)(malloc(sizeof(GOST34112012Context)));
    if(sizeHash==64)
        GOST34112012Init(CTX, 512);
    if(sizeHash==32)
        GOST34112012Init(CTX, 256);

     if (file.open(QIODevice::ReadOnly) )
               {
                 while (!file.atEnd()) {
                 QByteArray line = file.read(1024);
                 GOST34112012Update(CTX, (unsigned char*)(line.data()), line.size());
               }
             }
             file.close();
             GOST34112012Final(CTX, &digest[0]);
     convert_to_hex(digest, hexdigest, sizeHash, 1);//eflag=1 (в Госте в таком виде хеш получается)// eflag=0 наоборот развернут
     QString rez = (char*)hexdigest;
    // QString rez = (char*)digest;
    //  rez   = rez.toLocal8Bit().toHex();
             GOST34112012Cleanup(CTX);

    emit sendString(rez);emit set_max(100);emit change_value(100);emit finished();emit sendStringDone("Complete");
}
void MainWindow::on_pushButton_clicked()
{   fname = QFileDialog::getOpenFileName(this, tr("Open File"),0,0);
    ui->label_3->setText("Calculating...");
    QThread *thread = new QThread;  // создаём поток... вначале он создаётся остановленным

    MyClass *job = new MyClass; // создаём экземпляр нашего класса
    job->moveToThread(thread);

    if(ui->rb_MD5->isChecked()){

        connect(thread,SIGNAL(started()),job,SLOT(MyCalcMD5())); // когда поток стартует, то начать выполнение работы нашего класса
        connect(job,SIGNAL(sendString(QString)),ui->lineEdit_2,SLOT(setText(QString)));
    }
    if(ui->rb_G2012->isChecked()){
       connect(thread,SIGNAL(started()),job,SLOT(GOST2012()));
       connect(job,SIGNAL(sendString(QString)),ui->lineEdit,SLOT(setText(QString)));
    }
    connect(job,SIGNAL(finished()),thread,SLOT(quit())); // когда работа будет завершена, завершить поток
            connect(job,SIGNAL(finished()),job,SLOT(deleteLater())); // когда работа будет завершена, удалить наш экземпляр класса
            connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater())); // когда поток остановится, удалить его
thread->start();
connect(job,SIGNAL(change_value(int)),ui->progressBar_2,SLOT(setValue(int)));
connect(job,SIGNAL(set_max(int)),ui->progressBar_2,SLOT(setMaximum(int)));
connect(job,SIGNAL(sendStringDone(QString)),ui->label_3,SLOT(setText(QString)));
connect(job,SIGNAL(sendStringFileName(QString)),ui->label_2,SLOT(setText(QString)));

}


void MainWindow::on_rb512_clicked()
{
    sizeHash=64;
}

void MainWindow::on_rb256_clicked()
{
    sizeHash=32;
}


void MainWindow::on_actionAbout_triggered()
{
      QMessageBox msgBox;
      msgBox.setText("©2013 MyHash v1.0\nАвтор: Белкин Алексей\nДля вычисления контрольной суммы по ГОСТ3411-2012 в программе использован алгоритм, разработанный Алексеем Дегтяревым (streebog.net)");
      msgBox.exec();
    //qDebug()<<"About";
}
