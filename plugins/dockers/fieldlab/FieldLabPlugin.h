/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_PLUGIN_H
#define FIELDLAB_PLUGIN_H

#include <QObject>
#include <QVariant>

class FieldLabPlugin : public QObject
{
    Q_OBJECT

public:
    FieldLabPlugin(QObject *parent, const QVariantList &);
    ~FieldLabPlugin() override;
};

#endif
