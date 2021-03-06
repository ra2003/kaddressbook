/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KCM_Kaddressbook_Config_Plugins_H
#define KCM_Kaddressbook_Config_Plugins_H

#include <KCModule>

#include <QVariant>
namespace KUserFeedback {
class FeedbackConfigWidget;
}

namespace KAddressBook {
class KCMKaddressbookUserFeedBackConfig : public KCModule
{
    Q_OBJECT
public:
    KCMKaddressbookUserFeedBackConfig(QWidget *parent, const QVariantList &args);
    void load() override;
    void save() override;
    void defaults() override;
private:
    KUserFeedback::FeedbackConfigWidget *mUserFeedbackWidget = nullptr;
};
}
#endif // KCM_Kaddressbook_Config_Plugins_H
