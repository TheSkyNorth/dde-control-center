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
 * Command line was: qdbusxml2cpp -c DBusInputWacom -p dbusinputwacom com.deepin.daemon.InputDevice.Wacom.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUSINPUTWACOM_H_1444711198
#define DBUSINPUTWACOM_H_1444711198

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

struct DeviceListStruct {
    QString deviceName;
    int deviceId;
    bool deviceState;
};

struct ActionInfosStruct {
    QString actionInfo1;
    QString actionInfo2;
};

typedef QList<DeviceListStruct> DeviceStructList;
typedef QList<ActionInfosStruct> ActionInfosList;

Q_DECLARE_METATYPE(DeviceStructList)
Q_DECLARE_METATYPE(ActionInfosList)

/*
 * Proxy class for interface com.deepin.daemon.InputDevice.Wacom
 */
class DBusInputWacom: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage &msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count()) {
            return;
        }
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName != "com.deepin.daemon.InputDevice.Wacom") {
            return;
        }
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        foreach(const QString & prop, keys) {
            const QMetaObject *self = metaObject();
            for (int i = self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() == prop) {
                    QVariant v = p.read(this);
                    Q_EMIT p.notifySignal().invoke(this, QGenericArgument(v.typeName(), v.data()));
                }
            }
        }
    }
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.daemon.InputDevice.Wacom"; }

public:
    DBusInputWacom(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DBusInputWacom();

    Q_PROPERTY(ActionInfosList ActionInfos READ actionInfos NOTIFY ActionInfosChanged)
    inline ActionInfosList actionInfos() const
    { return qvariant_cast< ActionInfosList >(property("ActionInfos")); }

    Q_PROPERTY(bool CursorMode READ cursorMode WRITE setCursorMode NOTIFY CursorModeChanged)
    inline bool cursorMode() const
    { return qvariant_cast< bool >(property("CursorMode")); }
    inline void setCursorMode(bool value)
    { setProperty("CursorMode", QVariant::fromValue(value)); }

    Q_PROPERTY(DeviceStructList DeviceList READ deviceList NOTIFY DeviceListChanged)
    inline DeviceStructList deviceList() const
    { return qvariant_cast< DeviceStructList >(property("DeviceList")); }

    Q_PROPERTY(uint DoubleDelta READ doubleDelta WRITE setDoubleDelta NOTIFY DoubleDeltaChanged)
    inline uint doubleDelta() const
    { return qvariant_cast< uint >(property("DoubleDelta")); }
    inline void setDoubleDelta(uint value)
    { setProperty("DoubleDelta", QVariant::fromValue(value)); }

    Q_PROPERTY(bool Exist READ exist NOTIFY ExistChanged)
    inline bool exist() const
    { return qvariant_cast< bool >(property("Exist")); }

    Q_PROPERTY(QString KeyDownAction READ keyDownAction WRITE setKeyDownAction NOTIFY KeyDownActionChanged)
    inline QString keyDownAction() const
    { return qvariant_cast< QString >(property("KeyDownAction")); }
    inline void setKeyDownAction(const QString &value)
    { setProperty("KeyDownAction", QVariant::fromValue(value)); }

    Q_PROPERTY(QString KeyUpAction READ keyUpAction WRITE setKeyUpAction NOTIFY KeyUpActionChanged)
    inline QString keyUpAction() const
    { return qvariant_cast< QString >(property("KeyUpAction")); }
    inline void setKeyUpAction(const QString &value)
    { setProperty("KeyUpAction", QVariant::fromValue(value)); }

    Q_PROPERTY(bool LeftHanded READ leftHanded WRITE setLeftHanded NOTIFY LeftHandedChanged)
    inline bool leftHanded() const
    { return qvariant_cast< bool >(property("LeftHanded")); }
    inline void setLeftHanded(bool value)
    { setProperty("LeftHanded", QVariant::fromValue(value)); }

    Q_PROPERTY(uint PressureSensitive READ pressureSensitive WRITE setPressureSensitive NOTIFY PressureSensitiveChanged)
    inline uint pressureSensitive() const
    { return qvariant_cast< uint >(property("PressureSensitive")); }
    inline void setPressureSensitive(uint value)
    { setProperty("PressureSensitive", QVariant::fromValue(value)); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Reset()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Reset"), argumentList);
    }

Q_SIGNALS: // SIGNALS
// begin property changed signals
    void ActionInfosChanged();
    void CursorModeChanged(bool isChanged);
    void DeviceListChanged();
    void DoubleDeltaChanged(uint doubleDelta);
    void ExistChanged();
    void KeyDownActionChanged(QString keyDownStr);
    void KeyUpActionChanged(QString keyUpStr);
    void LeftHandedChanged(bool isChanged);
    void PressureSensitiveChanged(uint pressure);
};

namespace com
{
namespace deepin
{
namespace daemon
{
namespace InputDevice
{
typedef ::DBusInputWacom Wacom;
}
}
}
}
#endif
