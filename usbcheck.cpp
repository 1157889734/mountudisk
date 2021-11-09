#include "usbcheck.h"

usbCheck::usbCheck(QObject *parent) : QObject(parent)
{
    /* socket通信 使用 netLink方式获取内核消息 */
    sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
    memset(&client,0,sizeof(client));
    client.nl_family = AF_NETLINK;
    client.nl_pid = getpid();
    client.nl_groups = 1;
    buffersize = 1024;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF,&buffersize, sizeof(buffersize));

    bind(sockfd, (struct sockaddr *)&client,sizeof(client));

}

void usbCheck::checking()
{
    for(;;)
    {
        char buf[UEVENT_BUFFER_SIZE] = {0};
        FD_ZERO(&fds);
        FD_SET(sockfd,&fds);

        tv.tv_sec = 0;
        tv.tv_usec = 100*1000;
        result = select(sockfd+1,&fds, NULL,NULL, &tv);
        if(result <0)
            continue;
        if(!(result>0 && FD_ISSET(sockfd,&fds)))
            continue;

        receiveLenth = recv(sockfd,&buf,sizeof(buf),0);

        if(receiveLenth >0)
        {
           getName(buf);
        }
    }
}

void usbCheck::getName(QString buf)
{
    QString statue = buf.split("@").at(0);
    QStringList resultList;
    QRegExp rx("sd[a-z]{1}[0-9]{1,2}");
    int pos = 0;
    while( (pos = rx.indexIn(QString(buf),pos)) != -1)
    {
        resultList<<rx.cap(0);
        pos += rx.matchedLength();
    }

    if(statue == "remove")
    {
        /* 检测到usb移除 */
        emit usbName(resultList,0);
    }
    else if(statue == "add")
    {
        /* 检测到usb挂载 */
        emit usbName(resultList,1);
    }
}

