/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldLabPlugin.h"

#include <kpluginfactory.h>

#include <KoDockFactoryBase.h>
#include <KoDockRegistry.h>

#include "FieldLabDocker.h"

K_PLUGIN_FACTORY_WITH_JSON(
    FieldLabPluginFactory,
    "kritafieldlab.json",
    registerPlugin<FieldLabPlugin>();
)

class FieldLabDockFactory : public KoDockFactoryBase
{
public:
    QString id() const override
    {
        return QStringLiteral("FieldLabDocker");
    }

    Qt::DockWidgetArea defaultDockWidgetArea() const
    {
        return Qt::RightDockWidgetArea;
    }

    QDockWidget *createDockWidget() override
    {
        FieldLabDocker *docker = new FieldLabDocker();
        docker->setObjectName(id());
        return docker;
    }

    DockPosition defaultDockPosition() const override
    {
        return DockMinimized;
    }
};

FieldLabPlugin::FieldLabPlugin(QObject *parent, const QVariantList &)
    : QObject(parent)
{
    KoDockRegistry::instance()->add(new FieldLabDockFactory());
}

FieldLabPlugin::~FieldLabPlugin() = default;

#include "FieldLabPlugin.moc"

