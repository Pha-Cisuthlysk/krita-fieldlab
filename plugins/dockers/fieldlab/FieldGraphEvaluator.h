/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_GRAPH_EVALUATOR_H
#define FIELDLAB_FIELD_GRAPH_EVALUATOR_H

#include <QSet>
#include <QString>

#include "FieldGraph.h"

struct FieldEvaluationResult
{
    bool ok {false};
    double value {0.0};
    QString error;
};

class FieldGraphEvaluator
{
public:
    FieldEvaluationResult evaluateScalar(
        const FieldGraph &graph,
        int nodeId) const;

private:
    FieldEvaluationResult evaluateScalarInternal(
        const FieldGraph &graph,
        int nodeId,
        QSet<int> &visiting) const;

    FieldEvaluationResult evaluateInput(
        const FieldGraph &graph,
        const FieldNode &node,
        const QString &port,
        QSet<int> &visiting) const;
};

#endif