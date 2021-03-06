/*
 *  Copyright (c) 2017 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "buginfo.h"

#include <cmath>

#include <klocalizedstring.h>
#include <kis_debug.h>
#include <kpluginfactory.h>
#include <kis_icon.h>
#include <KisViewManager.h>
#include <kis_action.h>
#include "DlgKritaLog.h"
#include "DlgSysInfo.h"


K_PLUGIN_FACTORY_WITH_JSON(BugInfoFactory, "kritabuginfo.json", registerPlugin<BugInfo>();)



BugInfo::BugInfo(QObject *parent, const QVariantList &)
        : KisActionPlugin(parent)
{
    KisAction *actionBug  = createAction("buginfo");
    KisAction *actionSys  = createAction("sysinfo");
    connect(actionBug, SIGNAL(triggered()), this, SLOT(slotKritaLog()));
    connect(actionSys, SIGNAL(triggered()), this, SLOT(slotSysInfo()));

}


BugInfo::~BugInfo()
{
}

void BugInfo::slotKritaLog()
{
    DlgKritaLog dlgKritaLog(viewManager()->mainWindow());
    dlgKritaLog.exec();
}

void BugInfo::slotSysInfo()
{
    DlgSysInfo dlgSysInfo(viewManager()->mainWindow());
    dlgSysInfo.exec();
}


#include "buginfo.moc"
