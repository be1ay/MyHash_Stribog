/*
 * Copyright (c) 2021, Aleksei Belkin <mailbelkin@gmail.com>.
 * All rights reserved.
*/
#include "appcore.h"
#include <QFile>
#include <QUrl>
#include <QThread>
#include <QCoreApplication>
extern "C"{
    #include "gost3411-2012/gost3411-2012-core.h"
}
AppCore::AppCore(QObject *parent)
{
    Q_UNUSED(parent)
}

AppCore::~AppCore()
{
}
void AppCore::calculateHash(QString str){
    QUrl fileUrl(str);
    QFile file(fileUrl.toLocalFile());
    if(!file.exists())
        return;
    setBusy(true);
    GOST34112012Context *CTX;
    CTX = (GOST34112012Context*)(malloc(sizeof(GOST34112012Context)));
    unsigned char digest[64];
    unsigned char hexdigest[129];
    if(m_sizeHash==64)
        GOST34112012Init(CTX, 512);
    if(m_sizeHash==32)
        GOST34112012Init(CTX, 256);

    if (file.open(QIODevice::ReadOnly)){
        while (!file.atEnd()){
            QCoreApplication::processEvents();
            QByteArray line = file.read(4096);
            GOST34112012Update(CTX, (unsigned char*)(line.data()), line.size());
        }
        file.close();
    }
    GOST34112012Final(CTX, &digest[0]);
    convert_to_hex(digest, hexdigest, m_sizeHash, m_eflag);//eflag=1 (в Госте в таком виде хеш получается)// eflag=0 наоборот развернут
    QString rez = (char*)hexdigest;
    GOST34112012Cleanup(CTX);
    emit sendToQml(rez);
    setBusy(false);
}

void AppCore::receiveCheckBoxState(bool state)
{
    m_eflag =state;

}
static void reverse_order(unsigned char *in, size_t len)
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

void AppCore::convert_to_hex(unsigned char *in, unsigned char *out, size_t len,
        bool eflag)
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
