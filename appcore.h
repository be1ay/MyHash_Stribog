/*
 * Copyright (c) 2021, Aleksei Belkin <mailbelkin@gmail.com>.
 * All rights reserved.
*/
#ifndef APPCORE_H
#define APPCORE_H
#include <QObject>

class AppCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)
public:
    explicit AppCore(QObject *parent = 0);
    ~AppCore();

    bool busy() const
    {
        return m_busy;
    }

signals:
    void sendToQml(QString hashSum);
    void busyChanged(bool busy);

public slots:
    void calculateHash(QString);
    void receiveCheckBoxState(bool);
    void rb256Checked(){m_sizeHash=32;}
    void rb512Checked(){m_sizeHash=64;}


    void setBusy(bool busy)
    {
        if (m_busy == busy)
            return;

        m_busy = busy;
        emit busyChanged(m_busy);
    }

private:
    void convert_to_hex(unsigned char *in, unsigned char *out, size_t len,
            bool eflag);
    bool m_eflag=false;
    uint m_sizeHash=64;
    bool m_busy=false;
};

#endif // APPCORE_H
