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

#ifndef POTENTIALDUPLICATECONTACTSWIDGET_H
#define POTENTIALDUPLICATECONTACTSWIDGET_H

#include <QWidget>
#include <Akonadi/Item>

class PotentialDuplicateContactsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PotentialDuplicateContactsWidget(QWidget *parent=0);
    ~PotentialDuplicateContactsWidget();

    void setAddressList(const Akonadi::Item::List &list);

private:
    enum MatchType {
        None = 0,
        Name = 1,
        Emails = 2,
        Phone = 4,
        NickName = 8
    };

    void searchDuplicateContact();
    Akonadi::Item::List mContactList;
};

#endif // POTENTIALDUPLICATECONTACTSWIDGET_H
