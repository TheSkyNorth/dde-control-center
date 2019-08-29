/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     andywang <andywang_cm@deepin.com>
 *
 * Maintainer: andywang <andywang_cm@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "window/namespace.h"
#include "modules/bluetooth/device.h"

#include <DListView>

#include <QObject>

DWIDGET_USE_NAMESPACE

namespace dcc {
namespace bluetooth {
class Device;
}
}

namespace DCC_NAMESPACE {
namespace bluetooth {
class DeviceSettingsItem : public QObject
{
    Q_OBJECT
public:
    explicit DeviceSettingsItem(const dcc::bluetooth::Device *device, QStyle *style);
    DStandardItem *getStandardItem();
    DStandardItem *createStandardItem();
    const dcc::bluetooth::Device *device() const;

private:
    void setDevice(const dcc::bluetooth::Device *device);
    void initItemActionList(QStyle *style);

Q_SIGNALS:
    void requestConnectDevice(const dcc::bluetooth::Device *device) const;
    void requestShowDetail(const dcc::bluetooth::Device *device) const;

private Q_SLOTS:
    void onDeviceStateChanged(const dcc::bluetooth::Device::State &state);
    void onDevicePairedChanged(const bool &paired);

private:
    const dcc::bluetooth::Device *m_device;
    DStandardItem *m_deviceItem;
    DViewItemActionList m_dActionList;
    DViewItemAction *m_iconAction;
    DViewItemAction *m_textAction;
};
} // namespace bluetooth
} // namespace dcc