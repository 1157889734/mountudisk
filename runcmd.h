#ifndef RUNCMD_H
#define RUNCMD_H

#include <QProcess>
#include <QDebug>

#include <QObject>

class runCmd : public QObject
{
    Q_OBJECT
public:
    explicit runCmd(QObject *parent = 0);
    ~runCmd();
    void setCmd(QString,QStringList);
    QString getString();
signals:

public slots:
    void readyRead();

private:
    QProcess *process;
    QString putout;
};

#endif // RUNCMD_H
