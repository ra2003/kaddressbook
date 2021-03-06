/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2007 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mainwindow.h"
#include "mainwidget.h"
#include "settings.h"
#include <KToolBar>
#include <KConfigGroup>
#include <QAction>
#include <KActionCollection>
#include <KEditToolBar>
#include <KShortcutsDialog>
#include <KStandardAction>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KMessageBox>
#include <QMenuBar>
#include <QPointer>
#ifdef WITH_KUSERFEEDBACK
#include <KUserFeedback/NotificationPopup>
#include <KUserFeedback/Provider>
#include "userfeedback/userfeedbackmanager.h"
#endif

MainWindow::MainWindow()
    : KXmlGuiWindow(nullptr)
{
    mMainWidget = new MainWidget(this, this);

    setCentralWidget(mMainWidget);

    initActions();

    setStandardToolBarMenuEnabled(true);

    toolBar()->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    setupGUI(Save | Create, QStringLiteral("kaddressbookui.rc"));

    setAutoSaveSettings();

    mHideMenuBarAction->setChecked(Settings::self()->showMenuBar());
    slotToggleMenubar(true);
#ifdef WITH_KUSERFEEDBACK
    auto *userFeedBackNotificationPopup = new KUserFeedback::NotificationPopup(this);
    userFeedBackNotificationPopup->setFeedbackProvider(UserFeedBackManager::self()->userFeedbackProvider());
#endif
}

MainWindow::~MainWindow()
{
}

MainWidget *MainWindow::mainWidget() const
{
    return mMainWidget;
}

void MainWindow::initActions()
{
    KStandardAction::quit(this, &MainWindow::close, actionCollection());
    mHideMenuBarAction = KStandardAction::showMenubar(this, &MainWindow::slotToggleMenubar, actionCollection());

    QAction *action
        = KStandardAction::keyBindings(this, &MainWindow::configureKeyBindings, actionCollection());
    action->setWhatsThis(
        i18nc("@info:whatsthis",
              "You will be presented with a dialog where you can configure "
              "the application-wide shortcuts."));
    KStandardAction::configureToolbars(this, &MainWindow::configureToolbars, actionCollection());
    KStandardAction::preferences(this, &MainWindow::configure, actionCollection());
}

void MainWindow::configure()
{
    mMainWidget->configure();
}

void MainWindow::configureKeyBindings()
{
    if (KShortcutsDialog::configure(actionCollection(), KShortcutsEditor::LetterShortcutsAllowed, this)) {
        mMainWidget->updateQuickSearchText();
    }
}

void MainWindow::configureToolbars()
{
    KConfigGroup grp = KSharedConfig::openConfig()->group("MainWindow");
    saveMainWindowSettings(grp);

    QPointer<KEditToolBar> dlg = new KEditToolBar(factory());
    connect(dlg.data(), &KEditToolBar::newToolBarConfig, this, &MainWindow::newToolbarConfig);
    dlg->exec();
    delete dlg;
}

void MainWindow::newToolbarConfig()
{
    createGUI(QStringLiteral("kaddressbookui.rc"));

    applyMainWindowSettings(KSharedConfig::openConfig()->group("MainWindow"));
}

void MainWindow::slotToggleMenubar(bool dontShowWarning)
{
    if (menuBar()) {
        if (mHideMenuBarAction->isChecked()) {
            menuBar()->show();
        } else {
            if (!dontShowWarning) {
                const QString accel = mHideMenuBarAction->shortcut().toString();
                KMessageBox::information(this,
                                         i18n("<qt>This will hide the menu bar completely."
                                              " You can show it again by typing %1.</qt>", accel),
                                         i18n("Hide menu bar"), QStringLiteral("HideMenuBarWarning"));
            }
            menuBar()->hide();
        }
        Settings::self()->setShowMenuBar(mHideMenuBarAction->isChecked());
    }
}
