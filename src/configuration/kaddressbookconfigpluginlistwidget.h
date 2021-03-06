/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KADDRESSBOOKCONFIGPLUGINLISTWIDGET_H
#define KADDRESSBOOKCONFIGPLUGINLISTWIDGET_H

#include <PimCommon/ConfigurePluginsListWidget>

class KAddressBookConfigPluginListWidget : public PimCommon::ConfigurePluginsListWidget
{
    Q_OBJECT
public:
    explicit KAddressBookConfigPluginListWidget(QWidget *parent = nullptr);
    ~KAddressBookConfigPluginListWidget() override;

    void save() override;
    void doLoadFromGlobalSettings() override;
    void doResetToDefaultsOther() override;
    void initialize() override;
private:
    void slotConfigureClicked(const QString &configureGroupName, const QString &identifier);
    QVector<PluginItem *> mPluginGenericItems;
    QVector<PluginItem *> mPluginImportExportItems;
};

#endif // KADDRESSBOOKCONFIGPLUGINLISTWIDGET_H
