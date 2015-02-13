/*
  Copyright (c) 2014-2015 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "mergecontactstest.h"
#include <qtest.h>
#include "../job/mergecontacts.h"

using namespace KABMergeContacts;
using namespace KContacts;
MergeContactsTest::MergeContactsTest()
{
}

void MergeContactsTest::shouldReturnDefaultAddressWhenNoListItem()
{
    MergeContacts contacts;
    KContacts::Addressee result = contacts.mergedContact();
    QCOMPARE(result.isEmpty(), true);
}

void MergeContactsTest::shouldReturnDefaultAddressWhenOneItem()
{
    Akonadi::Item::List lst;
    Akonadi::Item item;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    item.setPayload<KContacts::Addressee>(address);
    lst << item;

    MergeContacts contacts(lst);
    KContacts::Addressee result = contacts.mergedContact();
    QCOMPARE(result.isEmpty(), true);
}

void MergeContactsTest::noNeedManualSelectionCheckWhenEmptyList()
{
    MergeContacts contacts;
    const MergeContacts::ConflictInformations result = contacts.needManualSelectInformations();
    QCOMPARE(result, MergeContacts::None);
}

void MergeContactsTest::noNeedManualSelectionCheckWhenOneItem()
{
    Akonadi::Item::List lst;
    KContacts::Addressee address;
    Akonadi::Item item;
    address.setName(QStringLiteral("foo1"));
    item.setPayload<KContacts::Addressee>(address);
    lst << item;
    MergeContacts contacts(lst);
    const MergeContacts::ConflictInformations result = contacts.needManualSelectInformations();
    QCOMPARE(result, MergeContacts::None);
}

void MergeContactsTest::shouldMergeNotes_data()
{
    QTest::addColumn<QString>("noteItemA");
    QTest::addColumn<QString>("noteItemB");
    QTest::addColumn<QString>("noteItemC");
    QTest::addColumn<QString>("note");
    QTest::newRow("noNotes") <<  QString() << QString() << QString() << QString();
    QTest::newRow("oneNotes") <<  QString(QLatin1String("one")) << QString() << QString() << QString(QLatin1String("one"));
    QTest::newRow("twoNotes") <<  QString() << QString(QLatin1String("one")) << QString(QLatin1String("one")) << QString(QLatin1String("one\none"));
    QTest::newRow("threeNotes") <<  QString(QLatin1String("one")) << QString(QLatin1String("one")) << QString(QLatin1String("one")) << QString(QLatin1String("one\none\none"));
}

void MergeContactsTest::shouldMergeNotes()
{
    QFETCH(QString, noteItemA);
    QFETCH(QString, noteItemB);
    QFETCH(QString, noteItemC);
    QFETCH(QString, note);

    Akonadi::Item::List lst;
    Addressee addressA;
    Akonadi::Item itemA;
    addressA.setName(QLatin1String("foo1"));
    addressA.setNote(noteItemA);
    itemA.setPayload<Addressee>(addressA);
    lst << itemA;

    Addressee addressB;
    Akonadi::Item itemB;
    addressB.setName(QLatin1String("foo1"));
    addressB.setNote(noteItemB);
    itemB.setPayload<Addressee>(addressB);
    lst << itemB;

    Addressee addressC;
    Akonadi::Item itemC;
    addressC.setName(QLatin1String("foo1"));
    addressC.setNote(noteItemC);
    itemC.setPayload<Addressee>(addressC);
    lst << itemC;

    MergeContacts contacts(lst);

    const Addressee result = contacts.mergedContact();
    QCOMPARE(result.note(), note);

}

void MergeContactsTest::shouldMergeEmails_data()
{
    QTest::addColumn<QStringList>("emailsItemA");
    QTest::addColumn<QStringList>("emailsItemB");
    QTest::addColumn<QStringList>("emailsItemC");
    QTest::addColumn<QStringList>("emails");
    QTest::newRow("noEmails") <<  QStringList() << QStringList() << QStringList() << QStringList();
    QStringList lst;
    lst << QLatin1String("foo");
    lst << QLatin1String("foo1");
    lst << QLatin1String("foo2");
    QTest::newRow("copyFromOnContact") << lst << QStringList() << QStringList() << lst;
    QTest::newRow("copyFromTwoIdenticContact") << lst << lst << QStringList() << lst;
    QStringList lst2;
    lst2 << QLatin1String("foo5");
    lst2 << QLatin1String("foo6");
    lst2 << QLatin1String("foo7");

    QTest::newRow("copyFromTwoDifferentContact") << lst << lst2 << QStringList() << (QStringList() << lst << lst2);
    QStringList lst3;
    lst3 << QLatin1String("foo2");
    lst3 << lst2;
    //Identic => we will return merge between lst and lst2
    QTest::newRow("copyWithSomeIdenticEmail") << lst << lst3 << QStringList() << (QStringList() << lst << lst2);
}

void MergeContactsTest::shouldMergeEmails()
{
    QFETCH(QStringList, emailsItemA);
    QFETCH(QStringList, emailsItemB);
    QFETCH(QStringList, emailsItemC);
    QFETCH(QStringList, emails);

    Akonadi::Item::List lst;
    Addressee addressA;
    Akonadi::Item itemA;
    addressA.setName(QLatin1String("foo1"));
    addressA.setEmails(emailsItemA);
    itemA.setPayload<Addressee>(addressA);
    lst << itemA;

    Addressee addressB;
    Akonadi::Item itemB;
    addressB.setName(QLatin1String("foo1"));
    addressB.setEmails(emailsItemB);
    itemB.setPayload<Addressee>(addressB);
    lst << itemB;

    Addressee addressC;
    Akonadi::Item itemC;
    addressC.setName(QLatin1String("foo1"));
    addressC.setEmails(emailsItemC);
    itemC.setPayload<Addressee>(addressC);
    lst << itemC;

    MergeContacts contacts(lst);

    const Addressee result = contacts.mergedContact();
    QCOMPARE(result.emails(), emails);
}

QTEST_MAIN(MergeContactsTest)
