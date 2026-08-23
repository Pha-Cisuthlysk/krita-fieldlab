/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_NODE_DESCRIPTOR_H
#define FIELDLAB_NODE_DESCRIPTOR_H

#include <QString>
#include <QVector>

enum class FieldValueType
{
    Scalar,
    Vector2,
    Color,
    Raster,
    Geometry
};

enum class FieldPortDirection
{
    Input,
    Output
};

struct NodePortDescriptor
{
    QString id;
    QString displayName;
    FieldValueType valueType {FieldValueType::Scalar};
    FieldPortDirection direction {FieldPortDirection::Input};
};

struct NodeDescriptor
{
    QString typeId;
    QString displayName;
    QString category;

    QVector<NodePortDescriptor> inputs;
    QVector<NodePortDescriptor> outputs;

    static QVector<NodeDescriptor> builtInScalarNodes();
};

#endif