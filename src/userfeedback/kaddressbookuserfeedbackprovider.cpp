/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaddressbookuserfeedbackprovider.h"
#include <KUserFeedback/ApplicationVersionSource>
#include <KUserFeedback/PlatformInfoSource>
#include <KUserFeedback/ScreenInfoSource>
#include <KUserFeedback/QtVersionSource>
#include <KUserFeedback/StartCountSource>
#include <KUserFeedback/UsageTimeSource>
#include <KUserFeedback/LocaleInfoSource>

KAddressBookUserFeedbackProvider::KAddressBookUserFeedbackProvider(QObject *parent)
    : KUserFeedback::Provider(parent)
{
    setProductIdentifier(QStringLiteral("org.kde.kaddressbook"));
    setFeedbackServer(QUrl(QStringLiteral("https://telemetry.kde.org/")));
    setSubmissionInterval(7);
    setApplicationStartsUntilEncouragement(5);
    setEncouragementDelay(30);

    addDataSource(new KUserFeedback::ApplicationVersionSource);
    addDataSource(new KUserFeedback::PlatformInfoSource);
    addDataSource(new KUserFeedback::ScreenInfoSource);
    addDataSource(new KUserFeedback::QtVersionSource);

    addDataSource(new KUserFeedback::StartCountSource);
    addDataSource(new KUserFeedback::UsageTimeSource);

    addDataSource(new KUserFeedback::LocaleInfoSource);
}

KAddressBookUserFeedbackProvider::~KAddressBookUserFeedbackProvider()
{
}
