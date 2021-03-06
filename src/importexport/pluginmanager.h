/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KADDRESSBOOKIMPORTEXPORTPLUGINMANAGER_H
#define KADDRESSBOOKIMPORTEXPORTPLUGINMANAGER_H

#include <QObject>
#include <PimCommon/PluginUtil>
#include "kaddressbook_importexport_export.h"

namespace KAddressBookImportExport {
class Plugin;
class PluginManagerPrivate;

/** Contact import/export plugin manager. */
class KADDRESSBOOK_IMPORTEXPORT_EXPORT PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = nullptr);
    ~PluginManager() override;

    static PluginManager *self();

    Q_REQUIRED_RESULT QVector<Plugin *> pluginsList() const;

    Q_REQUIRED_RESULT QVector<PimCommon::PluginUtilData> pluginsDataList() const;

    Q_REQUIRED_RESULT QString configGroupName() const;
    Q_REQUIRED_RESULT QString configPrefixSettingKey() const;
    Plugin *pluginFromIdentifier(const QString &id);
private:
    QScopedPointer<PluginManagerPrivate> const d;
};
}

#endif // KADDRESSBOOKIMPORTEXPORTPLUGINMANAGER_H
