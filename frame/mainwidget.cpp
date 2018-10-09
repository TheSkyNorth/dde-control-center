/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
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

#include "mainwidget.h"

#include "accounts/avatarwidget.h"
#include "updatenotifier.h"

#include <dimagebutton.h>

#include <com_deepin_daemon_accounts.h>
#include <com_deepin_daemon_accounts_user.h>

#include <QSettings>
#include <QApplication>
#include <QScreen>

#include <unistd.h>

using namespace dcc::accounts;
using AccountsInter = com::deepin::daemon::Accounts;
using UserInter = com::deepin::daemon::accounts::User;

DWIDGET_USE_NAMESPACE

static const int PluginsHeightMax = 380;
static const int PluginsHeightMin = 260;

MainWidget::MainWidget(FrameContentWrapper *parent)
    : FrameWidget(parent),

      m_pluginsController(new PluginsController(this)),

//      m_lastPluginWidget(nullptr),

      m_timeRefersh(new QTimer(this)),

      m_userAvatarBtn(nullptr),
      m_currentTimeLbl(new QLabel),
      m_currentDateLbl(new QLabel),
      m_pluginsLayout(new QStackedLayout),
#ifndef DISABLE_SYS_UPDATE
      m_updateNotifier(new UpdateNotifier),
#endif
      m_quickSettingsPanel(new QuickControlPanel(this))
{
    m_pluginsLayout->setMargin(0);
    m_pluginsLayout->setSpacing(0);

#ifndef DISABLE_ACCOUNT
    // TODO: get dbus data
    const int uid = getuid();
    AccountsInter accountsInter("com.deepin.daemon.Accounts", "/com/deepin/daemon/Accounts", QDBusConnection::systemBus(), this);
    for (auto user : accountsInter.userList())
    {
        UserInter *inter = new UserInter("com.deepin.daemon.Accounts", user, QDBusConnection::systemBus(), this);
        if (inter->uid().toInt() == uid)
        {
            m_userAvatarBtn = new AvatarWidget(inter->iconFile());
            m_userAvatarBtn->setAccessibleName(inter->iconFile());
            m_userAvatarBtn->setAccessibleDescription("UserAvatarButton");

            connect(inter, &UserInter::IconFileChanged, m_userAvatarBtn, &AvatarWidget::setAvatarPath);
            connect(m_userAvatarBtn, &AvatarWidget::clicked, this, [=] { emit showSettingPage("accounts", inter->userName(), false); });

            // keep pointer
            break;
        }
        inter->deleteLater();
    }
#endif

    m_timeRefersh->setInterval(1000);
    m_timeRefersh->setSingleShot(false);
    m_timeRefersh->start();

    QFont font = m_currentTimeLbl->font();
    font.setPixelSize(46);
    font.setWeight(QFont::Light);

    m_currentTimeLbl->setObjectName("CurrentTimeLabel");
    m_currentTimeLbl->setFont(font);
    m_currentDateLbl->setObjectName("CurrentDateLabel");
    m_currentDateLbl->setWordWrap(true);

    // Header
    TranslucentFrame *headerFrame = new TranslucentFrame;
    headerFrame->setFixedHeight(140);
    headerFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout *timedateLayout = new QVBoxLayout;
    timedateLayout->setSpacing(0);
    timedateLayout->setMargin(0);
    timedateLayout->addStretch();
    timedateLayout->addWidget(m_currentTimeLbl);
    timedateLayout->addWidget(m_currentDateLbl);
    timedateLayout->addStretch();

    QVBoxLayout *avatarLayout = new QVBoxLayout;
    avatarLayout->setSpacing(0);
    avatarLayout->setContentsMargins(0, 10, 0, 0);
    avatarLayout->addWidget(m_userAvatarBtn);

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->setSpacing(30);
    headerLayout->setContentsMargins(40, 0, 0, 10);
    headerLayout->addLayout(avatarLayout);
    headerLayout->addLayout(timedateLayout);
    headerLayout->addStretch();

    headerFrame->setLayout(headerLayout);

    // Plugins
    m_pluginWrapper = new TranslucentFrame;
    m_pluginWrapper->setLayout(m_pluginsLayout);
    m_pluginWrapper->setObjectName("HomePluginsFrame");

    QVBoxLayout *pluginWidgetLayout = new QVBoxLayout;
    pluginWidgetLayout->addWidget(m_pluginWrapper);
//    pluginWidgetLayout->addWidget(m_quickSettingsPanel);
    pluginWidgetLayout->setSpacing(0);
    pluginWidgetLayout->setMargin(0);

    m_quickSettingsPanel->hide();

    m_pluginWidget = new TranslucentFrame;
    m_pluginWidget->setLayout(pluginWidgetLayout);

#ifndef DISABLE_SYS_UPDATE
    m_updateNotifier->setObjectName("UpdateNotifier");

    connect(m_updateNotifier, &UpdateNotifier::notifierVisibleChanged, this, &MainWidget::updateMPRISEnable);
#endif

    QVBoxLayout *centralLayout = static_cast<QVBoxLayout *>(layout());
    centralLayout->addWidget(headerFrame);
#ifndef DISABLE_SYS_UPDATE
    centralLayout->addWidget(m_updateNotifier);
    centralLayout->addSpacing(1);
#endif
    centralLayout->addWidget(m_pluginWrapper);
//    centralLayout->addWidget(m_quickSettingsPanel);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    connect(m_pluginsController, &PluginsController::pluginAdded, this, &MainWidget::pluginAdded, Qt::QueuedConnection);
    connect(m_pluginsController, &PluginsController::requestModulePage, this, &MainWidget::showSettingPage, Qt::QueuedConnection);
    connect(m_quickSettingsPanel, &QuickControlPanel::requestDetailConfig, this, &MainWidget::showAllSettings);
    connect(m_quickSettingsPanel, &QuickControlPanel::requestPage, this, &MainWidget::showSettingPage);
    connect(this, &MainWidget::appear, m_quickSettingsPanel, &QuickControlPanel::appear);
    connect(this, &MainWidget::disappear, m_quickSettingsPanel, &QuickControlPanel::disappear);
    connect(m_timeRefersh, &QTimer::timeout, this, &MainWidget::refershTimedate);

#ifndef DISABLE_SYS_UPDATE
    connect(m_updateNotifier, &UpdateNotifier::clicked, this, [this] {
        showSettingPage("update", "available-updates", false);
    });
#endif

    m_pluginsController->loadPlugins();
    refershTimedate();
}

void MainWidget::resizeEvent(QResizeEvent *e)
{
    FrameWidget::resizeEvent(e);

    QTimer::singleShot(1, this, &MainWidget::updatePluginsHeight);
}

int MainWidget::getPluginsHeight()
{
    return height() > 800 ? PluginsHeightMax : PluginsHeightMin;
}

void MainWidget::updatePluginsHeight()
{
    const bool b = height() > 650;
    m_pluginWidget->setVisible(b);
    m_quickSettingsPanel->setAllSettingsVisible(!b);

    updateMPRISEnable();
}

void MainWidget::pluginAdded(QWidget * const w)
{
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    const int idx = m_pluginsLayout->addWidget(w);
    const int count = m_pluginsLayout->count();
    m_pluginsLayout->setCurrentIndex(idx);
}

void MainWidget::showNextPlugin()
{
    const int index = m_pluginsLayout->currentIndex();
    const int count = m_pluginsLayout->count();

    m_pluginsLayout->setCurrentIndex((index + 1) % count);
}

void MainWidget::showPrevPlugin()
{
    const int index = m_pluginsLayout->currentIndex();
    const int count = m_pluginsLayout->count();

    m_pluginsLayout->setCurrentIndex((index + count - 1) % count);
}

void MainWidget::refershTimedate()
{
    const QDateTime tm = QDateTime::currentDateTime();
    m_currentTimeLbl->setText(tm.time().toString("HH:mm"));
    m_currentDateLbl->setText(tm.date().toString(Qt::SystemLocaleLongDate));
}

void MainWidget::updateMPRISEnable()
{
#ifndef DISABLE_SYS_UPDATE
    const bool update_visible = m_updateNotifier->isVisible();
#else
    const bool update_visible = false;
#endif
    const int screen_height = qApp->primaryScreen()->geometry().height();
    const bool is_768 = screen_height <= 768;

    m_quickSettingsPanel->setMPRISEnable(!(update_visible && is_768));
    m_quickSettingsPanel->setMPRISPictureEnable(screen_height > 1000);
}
