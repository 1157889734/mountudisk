#ifndef USBCHECK_H
#define USBCHECK_H

#include <QObject>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

//#include <QDebug>
#include <QString>
#include <QStringList>
#include <asm/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include "head.h"

#define UEVENT_BUFFER_SIZE 4096

class usbCheck : public QObject
{
    Q_OBJECT
public:
    explicit usbCheck(QObject *parent = 0);

signals:
    void usbName(QStringList ,int statue);
public slots:
    void checking();
private:
    void getName(QString);
private:
    int sockfd;
    struct sockaddr_nl client;
    struct timeval tv;
    struct msghdr msg;
    struct iovec iov;
    fd_set fds;
    int receiveLenth,i,result;
    int buffersize;

};

#endif // USBCHECK_H
