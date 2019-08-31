/*
 * Copyright (C) 2011 ~ 2019 Deepin Technology Co., Ltd.
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

#include "customcontent.h"
#include "modules/keyboard/keyboardcontrol.h"
#include "modules/keyboard/keyboardwork.h"
#include "modules/keyboard/shortcutmodel.h"
#include "modules/keyboard/keyboardmodel.h"
#include "modules/keyboard/customitem.h"
#include "widgets/translucentframe.h"
#include "widgets/buttontuple.h"
#include "widgets/lineeditwidget.h"
#include "widgets/settingsgroup.h"

#include <dimagebutton.h>

#include <QMap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPushButton>

DWIDGET_USE_NAMESPACE

using namespace dcc;
using namespace dcc::keyboard;
using namespace DCC_NAMESPACE;
using namespace DCC_NAMESPACE::keyboard;

CustomContent::CustomContent(ShortcutModel *model, QWidget *parent)
    : QWidget(parent)
    , m_conflict(nullptr)
    , m_model(model)
    , m_buttonTuple(new ButtonTuple)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(10);
    mainLayout->addSpacing(10);
    //~ contents_path /keyboard/Shortcuts/Custom Shortcut
    QLabel *shortCutTitle = new QLabel(tr("Add Custom Shortcut"));
    shortCutTitle->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(shortCutTitle);
    mainLayout->addSpacing(30);

    //~ contents_path /keyboard/Shortcuts/Custom Shortcut
    QLabel *shortCutName = new QLabel(tr("Name"));
    mainLayout->addWidget(shortCutName);
    m_shortCutNameEdit = new QLineEdit;
    m_shortCutNameEdit->setPlaceholderText(tr("Required"));
    mainLayout->addWidget(m_shortCutNameEdit);

    //~ contents_path /keyboard/Shortcuts/Custom Shortcut
    QLabel *shortCutCmd = new QLabel(tr("Command"));
    mainLayout->addWidget(shortCutCmd);
    QHBoxLayout *cmdHLayout = new QHBoxLayout;
    m_shortCutCmdEdit = new QLineEdit;
    m_shortCutCmdEdit->setPlaceholderText(tr("Required"));
    cmdHLayout->addWidget(m_shortCutCmdEdit);

    DImageButton *pushbutton = new DImageButton;
    pushbutton->setNormalPic(":/keyboard/themes/dark/icons/loadfile_normal.svg");
    pushbutton->setHoverPic(":/keyboard/themes/dark/icons/loadfile_hover.svg");
    pushbutton->setPressPic(":/keyboard/themes/dark/icons/loadfile_press.svg");
    cmdHLayout->addWidget(pushbutton);
    mainLayout->addLayout(cmdHLayout);

    m_shortcut = new CustomItem;
    m_shortcut->setShortcut("");
    mainLayout->addWidget(m_shortcut);

    QPushButton *cancel = m_buttonTuple->leftButton();
    //~ contents_path /keyboard/Shortcuts/Custom Shortcut
    cancel->setText(tr("Cancel"));
    QPushButton *ok = m_buttonTuple->rightButton();
    //~ contents_path /keyboard/Shortcuts/Custom Shortcut
    ok->setText(tr("Add"));

    m_bottomTip = new QLabel();
    m_bottomTip->setWordWrap(true);
    m_bottomTip->hide();

    mainLayout->addStretch();
    mainLayout->addWidget(m_buttonTuple);
    mainLayout->addWidget(m_bottomTip);
    setLayout(mainLayout);

    connect(cancel, &QPushButton::clicked, this, &CustomContent::back);
    connect(ok, &QPushButton::clicked, this, &CustomContent::onShortcut);
    connect(pushbutton, &DImageButton::clicked, this, &CustomContent::onOpenFile);
    connect(m_shortcut, &CustomItem::requestUpdateKey, this, &CustomContent::updateKey);
    connect(model, &ShortcutModel::keyEvent, this, &CustomContent::keyEvent);
}

void CustomContent::setBottomTip(ShortcutInfo *conflict)
{
    m_conflict = conflict;
    if (conflict) {
        QString accels = conflict->accels;
        accels = accels.replace("<", "");
        accels = accels.replace(">", "+");
        accels = accels.replace("_L", "");
        accels = accels.replace("_R", "");
        accels = accels.replace("Control", "Ctrl");

        QString str = tr("This shortcut conflicts with %1, click on Add to make this shortcut effective immediately")
                      .arg(QString("<span style=\"color: rgba(255, 90, 90, 1);\">%1 %2</span>").arg(conflict->name).arg(QString("[%1]").arg(accels)));
        m_bottomTip->setText(str);
        m_bottomTip->show();
    } else {
        m_bottomTip->clear();
        m_bottomTip->hide();
    }
}

void CustomContent::onShortcut()
{
    if (m_shortCutNameEdit->text().isEmpty() || m_shortCutCmdEdit->text().isEmpty() || m_shortcut->text().isEmpty()) {
        qDebug() << "Error text";
        return;
    }
    if (m_conflict)
        Q_EMIT requestForceSubs(m_conflict);

    Q_EMIT requestAddKey(m_shortCutNameEdit->text(), m_shortCutCmdEdit->text(), m_shortcut->text());
    Q_EMIT back();

}

void CustomContent::keyEvent(bool press, const QString &shortcut)
{
    if (!press) {
        if (shortcut.isEmpty() || shortcut == "BackSpace" || shortcut == "Delete") {
            m_shortcut->setShortcut("");
            setBottomTip(nullptr);
            return;
        }

        // check conflict
        ShortcutInfo *conflict = m_model->getInfo(shortcut);
        setBottomTip(conflict);
    }

    m_shortcut->setShortcut(shortcut);
}

void CustomContent::updateKey()
{
    Q_EMIT requestUpdateKey(nullptr);
}

void CustomContent::onOpenFile()
{
    QString file = QFileDialog::getOpenFileName(this, "", "/usr/bin");
    m_shortCutCmdEdit->setText(file);
}
