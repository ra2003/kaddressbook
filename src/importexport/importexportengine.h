/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef IMPORTEXPORTENGINE_H
#define IMPORTEXPORTENGINE_H

#include <QObject>
#include <AkonadiCore/Collection>

#include "kaddressbook_importexport_export.h"
#include "contactlist.h"

class QProgressDialog;
class KJob;

namespace KAddressBookImportExport {
class KADDRESSBOOK_IMPORTEXPORT_EXPORT ImportExportEngine : public QObject
{
    Q_OBJECT
public:
    explicit ImportExportEngine(QObject *parent = nullptr);
    ~ImportExportEngine();
    void setContactList(const ContactList &contacts);

    void importContacts();
    void setParentWidget(QWidget *parent);
    QWidget *parentWidget() const;
    void setDefaultAddressBook(const Akonadi::Collection &defaultAddressBook);

Q_SIGNALS:
    void finished();

private:
    void slotImportJobDone(KJob *);
    ContactList mContactsList;
    Akonadi::Collection mDefaultAddressBook;
    QWidget *mParentWidget = nullptr;
    QProgressDialog *mImportProgressDialog = nullptr;
    int mNumberElementToImport = -1;
    int mImportDone = 0;
};
}

#endif // IMPORTEXPORTENGINE_H
