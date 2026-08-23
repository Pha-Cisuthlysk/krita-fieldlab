/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_GRAPH_VALIDATOR_H
#define FIELDLAB_FIELD_GRAPH_VALIDATOR_H

#include <QStringList>
#include <QVector>

#include "FieldGraph.h"
#include "NodeDescriptor.h"

struct FieldGraphValidationResult
{
    QStringList errors;

    bool isValid() const
    {
        return errors.isEmpty();
    }
};

class FieldGraphValidator
{
public:
    explicit FieldGraphValidator(
        QVector<NodeDescriptor> descriptors =
            NodeDescriptor::builtInScalarNodes());

    FieldGraphValidationResult validate(
        const FieldGraph &graph) const;

private:
    const NodeDescriptor *descriptorFor(
        const QString &typeId) const;

    QVector<NodeDescriptor> m_descriptors;
};

#endif
