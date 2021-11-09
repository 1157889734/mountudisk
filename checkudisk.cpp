#include "checkudisk.h"

checkUdisk::checkUdisk(QObject *parent): QObject(parent)
{
    check = new usbCheck();
    thread = new QThread();

    connect(thread, SIGNAL(started()),check,SLOT(checking()));
    connect(thread, SIGNAL(finished()),check, SLOT(deleteLater()));
    connect(check,SIGNAL(usbName(QStringList,int)),this,SLOT(getName(QStringList,int)));
    check->moveToThread(thread);

}

void checkUdisk::started()
{
    int pos=0;
    bool fdiskU,dfU;
    QString cmd,path;
    QDir dir;
    QString checkResult;
    /* fdisk -l 检查/dev下是否识别U盘/sd[a-z][0-9]{1,2} */
    runCmd checkU;
    QString fidsk = "fdisk";
    QStringList fdisk_list;
    fdisk_list<<"-l";
    checkU.setCmd(fidsk,fdisk_list);
    checkResult = checkU.getString();

    fdisk_list.clear();
    QRegExp rx("sd[a-z][0-9]{1,2}");

    while( (pos = rx.indexIn(checkResult,pos)) != -1 )
    {
        fdisk_list<<rx.cap(0);
        pos += rx.matchedLength();
    }

    /* 检测到的 sd* 存于fdisk_list列表 */
    if(fdisk_list.length() == 0)
        fdiskU = false;
    else
        fdiskU = true;

    /* df -h 检查对应的U盘是否挂载; */
    checkResult.clear();
    runCmd chechDf;
    QString df = "df";
    QStringList df_list;
    df_list<<"-h";
    chechDf.setCmd(df,df_list);
    checkResult = chechDf.getString();


    df_list.clear();
    QRegExp rz("/dev/sd[a-z][0-9]{1,2}");
    pos = 0;
    while( (pos = rz.indexIn(checkResult,pos)) != -1 )
    {
        df_list<<rz.cap(0);
        pos += rz.matchedLength();
    }

    if(df_list.length() == 0)
        dfU = false;
    else
        dfU = true;

    if(fdiskU == true)
    {
        if(dfU == false)
        {
            for(int i=0; i<fdisk_list.length();i++)
            {
//                path = QString("/home/data/%1").arg(fdisk_list.at(i));
                path = "/media/usb0";
                dir.mkdir(path);
//                cmd = QString("mount /dev/%1 /home/data/%1").arg(fdisk_list.at(i));
                cmd = QString("mount /dev/%1 /media/usb0").arg(fdisk_list.at(i));
                system(cmd.toStdString().c_str());
            }
        }
    }


    thread->start();
}

checkUdisk::~checkUdisk()
{
    disconnect(thread, SIGNAL(started()),check,SLOT(checking()));
    disconnect(thread, SIGNAL(finished()),check, SLOT(deleteLater()));
    if(thread)
    {
        if(thread->isRunning())
        {
            thread->quit();
            thread->wait();
        }
        delete thread;
        thread = NULL;
    }
    if(check)
    {
        delete check;
        check = NULL;
    }
}

void checkUdisk::getName(QStringList strList,int statue)
{
    QString cmd,path;
    QDir dir;
    if(strList.length() == 0)
        return;
    if(statue == 0)
    {
        for(int i=0; i<strList.length();i++)
        {
//            path = QString("/home/data/%1").arg(strList.at(i));
            path = "/media/usb0";
//            cmd = QString("umount /home/data/%1").arg(strList.at(i));
            cmd = QString("umount /media/usb0");
            system(cmd.toStdString().c_str());
            dir.rmdir(path);
        }
    }
    else if(statue == 1)
    {
        for(int i=0; i<strList.length();i++)
        {
//            path = QString("/home/data/%1").arg(strList.at(i));
            path = "/media/usb0";
            dir.mkdir(path);
            usbPathList<<path;
//            cmd = QString("mount /dev/%1 /home/data/%1").arg(strList.at(i));
            cmd = QString("mount /dev/%1 /media/usb0").arg(strList.at(i));
            system(cmd.toStdString().c_str());
        }
    }
    else
    {
        for(int i=0; i<usbPathList.length();i++)
        {
            dir.rmdir(usbPathList.at(i));
        }
    }
}
