#include "runCmd.h"

runCmd::runCmd(QObject *parent) : QObject(parent)
{
    process = new QProcess(this);
    connect(process, SIGNAL(readyRead()),this,SLOT(readyRead()));
}

runCmd::~runCmd()
{
    delete process;
}

QString runCmd::getString()
{
   while(false == process->waitForFinished());
   return putout;
}

void runCmd::setCmd(QString str,QStringList strList)
{
   if(strList.length()==0)
   {
       process->start(str);
   }
   else
   {
       process->start(str,strList);
   }
}

void runCmd::readyRead()
{
    putout = process->readAll();
}
