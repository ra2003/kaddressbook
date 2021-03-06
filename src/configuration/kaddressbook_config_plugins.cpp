/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaddressbook_config_plugins.h"
#include "kaddressbookconfigpluginlistwidget.h"
#include <KAboutData>
#include <KPluginFactory>
#include <KLocalizedString>
#include <PimCommon/ConfigurePluginsWidget>
#include <PimCommon/ConfigurePluginsListWidget>
#include <QHBoxLayout>

using namespace KAddressBook;

K_PLUGIN_FACTORY(KCMKaddressbookPluginsConfigFactory, registerPlugin<KCMKaddressbookPluginsConfig>();
                 )

KCMKaddressbookPluginsConfig::KCMKaddressbookPluginsConfig(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
{
    auto *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);

    KAboutData *about = new KAboutData(QStringLiteral("kcmakrpluginsconfig"),
                                       i18n("Configure Plugins"),
                                       QString(), QString(), KAboutLicense::GPL,
                                       i18n("(c), 2016-2020 Laurent Montel"));

    about->addAuthor(i18n("Laurent Montel"), QString(), QStringLiteral("montel@kde.org"));

    setAboutData(about);
    mConfigurePluginWidget = new PimCommon::ConfigurePluginsWidget(new KAddressBookConfigPluginListWidget(this), this);
    connect(mConfigurePluginWidget, &PimCommon::ConfigurePluginsWidget::changed, this, &KCMKaddressbookPluginsConfig::slotConfigChanged);
    lay->addWidget(mConfigurePluginWidget);
}

void KCMKaddressbookPluginsConfig::slotConfigChanged()
{
    Q_EMIT changed(true);
}

void KCMKaddressbookPluginsConfig::save()
{
    mConfigurePluginWidget->save();
}

void KCMKaddressbookPluginsConfig::load()
{
    mConfigurePluginWidget->doLoadFromGlobalSettings();
}

void KCMKaddressbookPluginsConfig::defaults()
{
    mConfigurePluginWidget->doResetToDefaultsOther();
}

#include "kaddressbook_config_plugins.moc"
