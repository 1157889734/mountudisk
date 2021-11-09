#ifndef CHECKUDISK_H
#define CHECKUDISK_H

#include <QThread>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "usbcheck.h"
#include "runCmd.h"

class usbCheck;
class runCmd;
class checkUdisk : public QObject
{
    Q_OBJECT
public:
    explicit checkUdisk(QObject *parent = 0);
    bool checking();
    void started();
    ~checkUdisk();

public slots:
    void getName(QStringList,int statue);
private:
    QThread *thread;
    usbCheck *check;
    QStringList usbPathList;
};

#endif // CHECKUDISK_H
