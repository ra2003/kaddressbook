/*
  Copyright (c) 2013 Montel Laurent <montel@kde.org>

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

#include "grantleeprintstyle.h"
#include "contactfields.h"
#include "printingwizard.h"
#include "printprogress.h"
#include "printstyle.h"
#include "contactgrantleeprintobject.h"

#include <grantlee/context.h>
#include <grantlee/engine.h>
#include <grantlee/templateloader.h>

#include <KABC/Addressee>

#include <KDebug>
#include <KLocale>

#include <QPrinter>
#include <QTextDocument>

using namespace KABPrinting;

QString GrantleePrintStyle::contactsToHtml( const KABC::Addressee::List &contacts )
{
    QList<ContactGrantleePrintObject*> lst;
    Q_FOREACH (const KABC::Addressee &address, contacts) {
        lst.append(new ContactGrantleePrintObject(address));
    }
    QVariantHash mapping;
    Grantlee::Context context( mapping );
    if (!mErrorMessage.isEmpty())
        return mErrorMessage;
    const QString content = mSelfcontainedTemplate->render( &context );
    qDeleteAll(lst);
    return content;
}

GrantleePrintStyle::GrantleePrintStyle( const QString &themePath, PrintingWizard *parent )
    : PrintStyle( parent )
{
    mEngine = new Grantlee::Engine;
    mTemplateLoader = Grantlee::FileSystemTemplateLoader::Ptr( new Grantlee::FileSystemTemplateLoader );
    //TODO themePath + preview.png ?
    //setPreview( QLatin1String("") );

    mTemplateLoader->setTemplateDirs( QStringList() << themePath );
    mEngine->addTemplateLoader( mTemplateLoader );

    mSelfcontainedTemplate = mEngine->loadByName( QLatin1String("print.html") );
    if ( mSelfcontainedTemplate->error() ) {
        mErrorMessage = mSelfcontainedTemplate->errorString() + QLatin1String("<br>");
    }

    setPreferredSortOptions( ContactFields::FormattedName, Qt::AscendingOrder );
}

GrantleePrintStyle::~GrantleePrintStyle()
{
    delete mEngine;
}

void GrantleePrintStyle::print( const KABC::Addressee::List &contacts, PrintProgress *progress )
{
    QPrinter *printer = wizard()->printer();
    printer->setPageMargins( 20, 20, 20, 20, QPrinter::DevicePixel );

    progress->addMessage( i18n( "Setting up document" ) );

    const QString html = contactsToHtml( contacts );

    QTextDocument document;
    document.setHtml( html );

    progress->addMessage( i18n( "Printing" ) );

    document.print( printer );

    progress->addMessage( i18nc( "Finished printing", "Done" ) );
}

GrantleeStyleFactory::GrantleeStyleFactory(const QString &themePath, PrintingWizard *parent )
    : PrintStyleFactory( parent ),
      mThemePath(themePath)
{
}

PrintStyle *GrantleeStyleFactory::create() const
{
    return new GrantleePrintStyle( mThemePath, mParent );
}

QString GrantleeStyleFactory::description() const
{
    return i18n( "Grantlee Printing Style" );
}

#include "grantleeprintstyle.moc"