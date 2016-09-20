/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kaddressbookconfigpluginlistwidget.h"
#include "../plugininterface/kaddressbookplugininterface.h"
#include <KLocalizedString>

KAddressBookConfigPluginListWidget::KAddressBookConfigPluginListWidget(QWidget *parent)
    : PimCommon::ConfigurePluginsListWidget(parent)
{

}

KAddressBookConfigPluginListWidget::~KAddressBookConfigPluginListWidget()
{

}

void KAddressBookConfigPluginListWidget::save()
{
    PimCommon::ConfigurePluginsListWidget::savePlugins(KAddressBookPluginInterface::self()->configGroupName(),
                KAddressBookPluginInterface::self()->configPrefixSettingKey(),
                mPluginGenericItems);
}

void KAddressBookConfigPluginListWidget::doLoadFromGlobalSettings()
{
    initialize();
}

void KAddressBookConfigPluginListWidget::doResetToDefaultsOther()
{
    Q_FOREACH (PluginItem *item, mPluginGenericItems) {
        item->setCheckState(0, item->mEnableByDefault ? Qt::Checked : Qt::Unchecked);
    }
}

void KAddressBookConfigPluginListWidget::initialize()
{
    mListWidget->clear();
    //Necessary to initialize pluging when we load it outside kmail
    //KAddressBookPluginInterface::self()->initializePlugins();
    PimCommon::ConfigurePluginsListWidget::fillTopItems(KAddressBookPluginInterface::self()->pluginsDataList(), i18n("Tools Plugins"),
                 KAddressBookPluginInterface::self()->configGroupName(),
                 KAddressBookPluginInterface::self()->configPrefixSettingKey(), mPluginGenericItems);
    mListWidget->expandAll();
}
