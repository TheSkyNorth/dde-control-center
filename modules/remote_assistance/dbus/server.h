/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p server /home/liliqiang/workspace/deepin/dbus-factory/xml/com.deepin.daemon.Remoting.Server.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.daemon.Remoting.Server
 */
class ComDeepinDaemonRemotingServerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.daemon.Remoting.Server"; }

public:
    ComDeepinDaemonRemotingServerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~ComDeepinDaemonRemotingServerInterface();

    Q_PROPERTY(QString PeerId READ peerId)
    inline QString peerId() const
    { return qvariant_cast< QString >(property("PeerId")); }

    Q_PROPERTY(int Status READ status)
    inline int status() const
    { return qvariant_cast< int >(property("Status")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QString> GetPeerId()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetPeerId"), argumentList);
    }

    inline QDBusPendingReply<int> GetStatus()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetStatus"), argumentList);
    }

    inline QDBusPendingReply<> Start()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Start"), argumentList);
    }

    inline QDBusPendingReply<> Stop()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Stop"), argumentList);
    }

    inline QDBusPendingReply<> StopNotify()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("StopNotify"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void StatusChanged(int status);
};

namespace com
{
namespace deepin
{
namespace daemon
{
namespace Remoting
{
typedef ::ComDeepinDaemonRemotingServerInterface Server;
}
}
}
}
#endif
