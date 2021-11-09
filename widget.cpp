#include "widget.h"
#include "ui_widget.h"
#include <QtDBus/QDBusConnection>
#include <QDBusInterface>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QDBusConnection::systemBus().connect(    "org.freedesktop.Hal",
                        "/org/freedesktop/Hal/Manager",
                        "org.freedesktop.Hal.Manager",
                        "DeviceAdded",
                        this,
                        SLOT(slotDeviceAdded(QString )));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotDeviceAdded(QString udi)
{

    QDBusInterface device("org.freedesktop.Hal", udi, "org.freedesktop.Hal.Device" , QDBusConnection::systemBus());

    qDebug()<<"****************udi="<<udi<<endl;

}

