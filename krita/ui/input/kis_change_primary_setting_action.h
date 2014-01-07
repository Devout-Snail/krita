/* This file is part of the KDE project
 * Copyright (C) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef KISCHANGEPRIMARYSETTINGACTION_H
#define KISCHANGEPRIMARYSETTINGACTION_H

#include "kis_abstract_input_action.h"

/**
 * \brief Change Primary Setting implementation of KisAbstractInputAction.
 *
 * The Change Primary Setting action changes a tool's "Primary Setting",
 * for example the brush size for the brush tool.
 */
class KisChangePrimarySettingAction : public KisAbstractInputAction
{
public:
    explicit KisChangePrimarySettingAction();
    virtual ~KisChangePrimarySettingAction();

    void activate();
    void deactivate();
    int priority() const;

    void begin(int shortcut, QEvent *event);
    void end(QEvent *event);
    void inputEvent(QEvent* event);
};

#endif // KISCHANGEPRIMARYSETTINGACTION_H
